// task_queue.h
#pragma once

#include <common/array/array.h>
#include <common/queue.h>
#include <common/result.h>
#include <order_management/task.h>


namespace dstr {


  class TaskQueue {
   private:
    Queue<Task> pending_;
    Array<Task> assigned_;
    Array<Task> completed_;

   public:
    // =====Ctors

    TaskQueue();


    // =====Getters

    usize pending_size() const;
    usize assigned_size() const;
    usize completed_size() const;
    bool empty() const;


    // =====Domain methods

    Result<void> enqueue(Task task);
    Result<void> add_assigned(Task task);
    Result<void> add_completed(Task task);
    Result<Task> assign_next(robot_id robot);
    Result<void> complete(task_id id);
    Result<Task> pending_at(usize index) const;
    Result<Task> assigned_at(usize index) const;
    Result<Task> completed_at(usize index) const;
    void clear();
  };


} // namespace dstr
