#pragma once


#include <common/aliases/aliases.h>
#include <common/result.h>
#include <common/array/array.h>


namespace dstr {


  template<typename T>
  class Queue {
   private:
    Array<T> items_;
    usize front_;

   public:
    Queue();

    usize size() const;
    bool empty() const;

    Result<void> enqueue(const T& value);
    Result<T> dequeue();
    Result<T> peek() const;
    Result<T> at(usize index) const;
    void clear();

  };


}


#include "queue.inl"
