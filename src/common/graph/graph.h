#pragma once


#include <common/aliases/aliases.h>
#include <common/enums.h>
#include <common/array/array.h>


namespace dstr {


  // Class prototypes

  template<typename T, typename W>
  class Edge;

  template<typename T, typename W>
  class Node;

  template<typename T, typename W>
  class Graph;


  // Unique node index
  struct NodeId {
    usize index;
    u32 generation;

    bool operator==(NodeId other) {
      return generation == other.generation && index == other.index;
    }

    bool operator!=(NodeId other) {
      return !((*this) == other);
    }
  };


  // Node slot. Contains and owns a node directly without std::optional or pointers.
  template<typename T, typename W>
  struct NodeSlot {
    Node<T, W> node;
    bool occupied;
    u32 generation;
  };


  // Graph edge. References a node using NodeId.
  template<typename T, typename W>
  class Edge {
    W weight_;
    NodeId target_;

  public:
    Edge();
    Edge(NodeId target, W weight = W());

    const NodeId target();
    const W weight();
  };


  template<typename T, typename W>
  class Node {
    T value_;
    Array<Edge<T, W>> links_;

  public:
    Node();
    Node(T value);
  };


  /// <summary>
  /// Graph class. Represented physically as a dynamic array. Physical representation is private.
  ///  
  /// </summary>
  /// <typeparam name="T">Node content type.</typeparam>
  /// <typeparam name="W">Weight type. dstr::i32 by default.</typeparam>
  template<typename T, typename W = i32>
  class Graph {
    Array<NodeSlot<T,W>> slots_;
    W default_weight_;

  public:
    Graph();
    Graph(W default_weight);

    Result<NodeId> add_node(T value);
    void set_node_value(NodeId id, T value);
    void remove_node(NodeId id);

    i32 size() const;
    T& at(NodeId id) const;
    T& at(usize id) const;
    T& operator[](NodeId id) const;
    T& operator[](usize id) const;
    bool valid_node_id(NodeId id) const;
    bool occupied(NodeId id) const;

    void add_edge_bidirectional(NodeId from, NodeId to, W weight = default_weight_);
    void add_edge_directional(NodeId from, NodeId to, W weight = default_weight_);
    Result<void> add_edge(NodeId from, NodeId to, bool bidirectional = false, W weight = default_weight_);
    void edge_weight_directional(NodeId from, NodeId to, W weight);
    void edge_weight_bidirectional(NodeId from, NodeId to, W weight);
    Result<void> edge_weight(NodeId from, NodeId to, W weight, bool bidirectional = false);
    void remove_edge_directional(NodeId from, NodeId to);
    void remove_edge_bidirectional(NodeId from, NodeId to);
    Result<void> remove_edge(NodeId from, NodeId to, bool bidirectional = false);
    W edge_weight(NodeId from, NodeId to) const;
    bool edge_exists(NodeId from, NodeId to) const;


  };


}

#include "graph.inl"
