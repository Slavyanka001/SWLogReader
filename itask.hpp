#pragma once

class ITask {
    public:
        virtual ~ ITask(){};
        virtual void work() = 0;
};