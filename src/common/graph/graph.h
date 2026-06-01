#pragma once


#include <common/aliases/aliases.h>
#include <common/enums.h>
#include <common/array/array.h>


namespace dstr {


  // Class prototypes

  template<typename T, typename W>
  class Link;

  template<typename T, typename W>
  class Node;

  template<typename T, typename W>
  class Graph;


  template<typename T, typename W>
  class Link {
    W weight_;
    wp<Node<T, W>> target_;

  public:
    Link();
    Link(sp<Node<T, W>> target, W weight = W());

    const wp<Node<T, W>> target();
    const W weight();

    Link<T, W>& operator=(const Link<T, W>& other);
    Link<T, W>& operator=(Link<T, W>&& other);
  };


  template<typename T, typename W>
  class Node {
    T value_;
    Array<Link<T, W>> links_;

  public:
    Node();
    Node(T value);

    //Node<T, W>& operator=(const Node<T, W>& other);
    //Node<T, W>& operator=(Node<T, W>&& other);
  };


  template<typename T, typename W = i32>
  class Graph {
    Array<sp<Node<T, W>>> nodes_;
    W default_weight_;

  public:
    Graph();
    Graph(W default_weight);

  };


}

#include "graph.inl"
