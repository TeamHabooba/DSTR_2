#pragma once


#include <common/aliases/aliases.h>
#include <common/enums.h>
#include <common/array/array.h>


namespace dstr {

  template<typename T, typename W>
  class Link {
    W weight_;
    wp<Node<T, W>> target_;
    
  };


  template<typename T, typename W>
  class Node {
    T value_;
    Array<Link<T, W>> links_;
  };

  template<typename T, typename W = i32>
  class Graph {
    Array<sp<Node<T, W>>> container_;

  };


}
