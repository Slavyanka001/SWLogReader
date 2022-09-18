#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <memory>
#include <shared_mutex>
#include <queue>

#include "args.hpp"
#include "task.hpp"
#include "data.hpp"
#include "thread_pool.hpp"

int main(int argc, char **argv)
{
   Args args;
   if (!args.Initialize(argc, argv)) {
      return -1;
   }

   const int batch_count = ceil((double)args.GetFileCount() / args.GetConcurrency());
   const int task_count = ceil(args.GetFileCount() / batch_count);

   LogData common_data;
   std::shared_mutex common_mutex;

   ThreadPool thread_pool;
   auto file_number_start = 1;
   while(file_number_start <= args.GetFileCount()) {
      auto file_number_end = std::min(file_number_start + batch_count, args.GetFileCount() + 1);
      thread_pool.PushTask(std::make_shared<Task>(
         Task(
            common_data,
            common_mutex,
            args.GetPathToDir(), 
            file_number_start,
            file_number_end)));

      file_number_start = file_number_end;
   }

   thread_pool.Start();
   thread_pool.WaitTillTasksDone();

   static const std::string outfile = "/home/slavyanka/queue/args.txt";
   common_data.WriteToFile(outfile);   
   
   std::cout << "All tasks completed" <<std::endl;
   return 0;

   //cmake --build .
   //--concurrency 1 --path asas --file_count 0
}

