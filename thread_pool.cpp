#include "thread_pool.hpp"

#include <thread>

ThreadPool::ThreadPool(std::optional<int> concurrency_level)
    : finished(false),
      concurrency(concurrency_level.value_or(std::thread::hardware_concurrency())){}

ThreadPool::~ThreadPool() {
    if (!finished) {
        WaitTillTasksDone();
    }
}

void ThreadPool::PushTask(std::shared_ptr<ITask>&& task) {
    tasks.push(std::move(task));
}

void ThreadPool::Start() {
    threads.reserve(concurrency);
    for (auto i = 0;i<concurrency;++i) {
        std::shared_ptr<ITask> task;
        {
            std::unique_lock write_lock(queue_mutex);
            if (tasks.empty()) {
                return;
            }
            task = tasks.front();
            tasks.pop();
        }
        threads.emplace_back(&ITask::work, task);
    }
}

void ThreadPool::WaitTillTasksDone() {
    for (auto& thread: threads) {
        thread.join();
    }
    finished = true;
}