//
// Created by IT on 2023-03-14.
//

#ifndef LINE_COUNTER_THREADPOOL_H
#define LINE_COUNTER_THREADPOOL_H


#include <queue>
#include <condition_variable>
#include <thread>
#include <functional>
#include <future>
#include <iostream>

class ThreadPool {
public:
    ThreadPool(size_t thread_count): stop(false) {
        for (size_t i = 0; i < thread_count; ++i) {
            workers.emplace_back(
                    [this] {
                        while(true) {
                            std::function<void()> task;
                            {
                                std::unique_lock<std::mutex> lock(this->queue_mutex);
                                this->condition.wait(lock, [this] { return this->stop || !this->tasks.empty(); });
                                if (this->stop && this->tasks.empty()) {
                                    return;
                                }
//                            std::cout<<std::this_thread::get_id()<<std::endl;
                                task = std::move(this->tasks.front());
                                this->tasks.pop();
                            }
                            task();
                            taskCounter--;
                        }
                    }
            );
        }
    }
    virtual ~ThreadPool(){
        stop = true;
        condition.notify_all();
        for (std::thread &worker : workers) {
            worker.join();
        }
    }
    template<typename Func, typename... Args>
    void enqueue(Func&& func, Args&&... args) {
        auto task = std::make_shared<std::packaged_task<void()>>(std::bind(std::forward<Func>(func), std::forward<Args>(args)...));
        {
            std::unique_lock<std::mutex> lock(queue_mutex);

            if (stop) {
                throw std::runtime_error("enqueue on stopped ThreadPool");
            }

            tasks.emplace([task]() { (*task)(); });
        }
        condition.notify_one();
        taskCounter++;
    }
    void wait_all() const {
        while(taskCounter!=0);
    }
private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    int taskCounter = 0;
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};


#endif //LINE_COUNTER_THREADPOOL_H
