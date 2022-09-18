#pragma once

#include <optional>
#include <queue>
#include <shared_mutex>
#include <vector>
#include <thread>

#include "itask.hpp"

class ThreadPool {
    public:

        ThreadPool(std::optional<int> concurrency_level = std::nullopt);
        ~ThreadPool();

        void PushTask(std::shared_ptr<ITask>&& task);
        void Start();

        void WaitTillTasksDone();

    private:

        bool finished;
        int concurrency;

        std::shared_mutex queue_mutex;
        
        std::queue<std::shared_ptr<ITask>> tasks;
        std::vector<std::thread> threads;
        
};