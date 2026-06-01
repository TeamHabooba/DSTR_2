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

    bool operator==(NodeId other) const {
      return generation == other.generation && index == other.index;
    }

    bool operator!=(NodeId other) const {
      return !((*this) == other);
    }
  };


  // Node slot. Contains and owns a node directly without std::optional or pointers.
  template<typename T, typename W>
  struct NodeSlot {
    Node<T, W> node;
    bool occupied;
    u32 generation;

    NodeSlot();
  };


  // Graph edge. References a node using NodeId.
  template<typename T, typename W>
  class Edge {
    W weight_;
    NodeId target_;

  public:
    Edge();
    Edge(NodeId target, W weight = W());

    NodeId target() const;
    W weight() const;
    void set_weight(W weight);
  };


  template<typename T, typename W>
  class Node {
    T value_;
    Array<Edge<T, W>> links_;

  public:
    Node();
    Node(T value);

    const T& value() const;
    T& value();
    void set_value(T value);
    const Array<Edge<T, W>>& links() const;
    Array<Edge<T, W>>& links();
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
    usize size_;

  public:
    Graph();
    Graph(W default_weight);

    Result<NodeId> add_node(T value);
    Result<void> set_node_value(NodeId id, T value);
    Result<void> remove_node(NodeId id);

    usize size() const;
    usize raw_size() const;
    Result<T> at(NodeId id) const;
    Result<T> at(usize raw_index) const;
    Result<Array<Edge<T, W>>> edges(NodeId id) const;
    Result<void> update(NodeId id, T value);
    Result<void> update(usize raw_index, T value);
    bool valid_node_id(NodeId id) const;
    bool occupied(NodeId id) const;
    bool occupied(usize raw_index) const;
    NodeId node_id_at(usize raw_index) const;

    Result<void> add_edge_bidirectional(NodeId from, NodeId to, W weight);
    Result<void> add_edge_directional(NodeId from, NodeId to, W weight);
    Result<void> add_edge(NodeId from, NodeId to, bool bidirectional = false);
    Result<void> add_edge(NodeId from, NodeId to, bool bidirectional, W weight);
    Result<void> edge_weight_directional(NodeId from, NodeId to, W weight);
    Result<void> edge_weight_bidirectional(NodeId from, NodeId to, W weight);
    Result<void> edge_weight(NodeId from, NodeId to, W weight, bool bidirectional = false);
    Result<void> remove_edge_directional(NodeId from, NodeId to);
    Result<void> remove_edge_bidirectional(NodeId from, NodeId to);
    Result<void> remove_edge(NodeId from, NodeId to, bool bidirectional = false);
    Result<W> edge_weight(NodeId from, NodeId to) const;
    bool edge_exists(NodeId from, NodeId to) const;
    Result<void> clear_edges(NodeId id);
    void clear_edges();

  private:
    Result<usize> find_edge_index(NodeId from, NodeId to) const;
    Result<void> validate_pair(NodeId from, NodeId to) const;

  };


}

#include "graph.inl"
