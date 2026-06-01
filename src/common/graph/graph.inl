#include "graph.h"


namespace dstr {


  // =====NodeSlot<> struct

  template<typename T, typename W>
  NodeSlot<T, W>::NodeSlot()
      : node{},
        occupied{false},
        generation{0} {}


  // =====Edge<> class

  template<typename T, typename W>
  Edge<T, W>::Edge() : weight_{W()}, target_{NodeId{0, 0}} {}

  template<typename T, typename W>
  Edge<T, W>::Edge(NodeId target, W weight )
    : weight_{ weight }, target_{ NodeId(target) } {}

  template<typename T, typename W>
  NodeId Edge<T,W>::target() const {
    return target_;
  }

  template<typename T, typename W>
  W Edge<T, W>::weight() const {
    return weight_;
  }

  template<typename T, typename W>
  void Edge<T, W>::set_weight(W weight) {
    weight_ = weight;
  }


  // =====Node<> class

  template<typename T, typename W>
  Node<T, W>::Node() : value_{ T() }, links_{ Array<Edge<T,W>>() } {}

  template<typename T, typename W>
  Node<T, W>::Node(T value) : value_{ value }, links_{ Array<Edge<T,W>>() } {}

  template<typename T, typename W>
  const T& Node<T, W>::value() const {
    return value_;
  }

  template<typename T, typename W>
  T& Node<T, W>::value() {
    return value_;
  }

  template<typename T, typename W>
  void Node<T, W>::set_value(T value) {
    value_ = value;
  }

  template<typename T, typename W>
  const Array<Edge<T, W>>& Node<T, W>::links() const {
    return links_;
  }

  template<typename T, typename W>
  Array<Edge<T, W>>& Node<T, W>::links() {
    return links_;
  }


  // =====Graph<> class

  template<typename T, typename W>
  Graph<T, W>::Graph()
      : slots_{ Array<NodeSlot<T,W>>() },
        default_weight_{ W() },
        size_{0} {}

  template<typename T, typename W>
  Graph<T, W>::Graph(W default_weight)
      : slots_{ Array<NodeSlot<T,W>>() },
        default_weight_{ default_weight },
        size_{0} {}

  template<typename T, typename W>
  Result<NodeId> Graph<T, W>::add_node(T value) {
    for (usize i = 0; i < slots_.size(); i++) {
      auto& slot = slots_.unchecked_at(i);
      if (!slot.occupied) {
        slot.node = Node<T, W>(value);
        slot.occupied = true;
        slot.generation++;
        size_++;
        return Ok(NodeId{i, slot.generation});
      }
    }

    NodeSlot<T, W> slot;
    slot.node = Node<T, W>(value);
    slot.occupied = true;
    slot.generation = 1;
    slots_.push_back(slot);
    size_++;
    return Ok(NodeId{slots_.size() - 1, slot.generation});
  }

  template<typename T, typename W>
  Result<void> Graph<T, W>::set_node_value(NodeId id, T value) {
    if (!valid_node_id(id)) {
      return Err(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_GRAPH_NODE_ID));
    }
    slots_.unchecked_at(id.index).node.set_value(value);
    return Ok();
  }

  template<typename T, typename W>
  Result<void> Graph<T, W>::remove_node(NodeId id) {
    if (!valid_node_id(id)) {
      return Err(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_GRAPH_NODE_ID));
    }
    for (usize i = 0; i < slots_.size(); i++) {
      if (slots_.unchecked_at(i).occupied) {
        remove_edge_directional(node_id_at(i), id);
      }
    }
    auto& slot = slots_.unchecked_at(id.index);
    slot.occupied = false;
    slot.node = Node<T, W>();
    size_--;
    return Ok();
  }

  template<typename T, typename W>
  usize Graph<T, W>::size() const {
    return size_;
  }

  template<typename T, typename W>
  usize Graph<T, W>::raw_size() const {
    return slots_.size();
  }

  template<typename T, typename W>
  Result<T> Graph<T, W>::at(NodeId id) const {
    if (!valid_node_id(id)) {
      return Err<T>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_GRAPH_NODE_ID));
    }
    return Ok(slots_.unchecked_at(id.index).node.value());
  }

  template<typename T, typename W>
  Result<T> Graph<T, W>::at(usize raw_index) const {
    if (!occupied(raw_index)) {
      return Err<T>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_GRAPH_RAW_INDEX));
    }
    return Ok(slots_.unchecked_at(raw_index).node.value());
  }

  template<typename T, typename W>
  Result<Array<Edge<T, W>>> Graph<T, W>::edges(NodeId id) const {
    if (!valid_node_id(id)) {
      return Err<Array<Edge<T, W>>>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_GRAPH_NODE_ID));
    }
    return Ok(slots_.unchecked_at(id.index).node.links());
  }

  template<typename T, typename W>
  Result<void> Graph<T, W>::update(NodeId id, T value) {
    return set_node_value(id, value);
  }

  template<typename T, typename W>
  Result<void> Graph<T, W>::update(usize raw_index, T value) {
    if (!occupied(raw_index)) {
      return Err(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_GRAPH_RAW_INDEX));
    }
    slots_.unchecked_at(raw_index).node.set_value(value);
    return Ok();
  }

  template<typename T, typename W>
  bool Graph<T, W>::valid_node_id(NodeId id) const {
    if (id.index >= slots_.size()) {
      return false;
    }
    const auto& slot = slots_.unchecked_at(id.index);
    return slot.occupied && slot.generation == id.generation;
  }

  template<typename T, typename W>
  bool Graph<T, W>::occupied(NodeId id) const {
    return valid_node_id(id);
  }

  template<typename T, typename W>
  bool Graph<T, W>::occupied(usize raw_index) const {
    return raw_index < slots_.size() && slots_.unchecked_at(raw_index).occupied;
  }

  template<typename T, typename W>
  NodeId Graph<T, W>::node_id_at(usize raw_index) const {
    const auto& slot = slots_.unchecked_at(raw_index);
    return NodeId{raw_index, slot.generation};
  }

  template<typename T, typename W>
  Result<void> Graph<T, W>::add_edge_bidirectional(NodeId from, NodeId to, W weight) {
    auto first = add_edge_directional(from, to, weight);
    if (!first) {
      return first;
    }
    return add_edge_directional(to, from, weight);
  }

  template<typename T, typename W>
  Result<void> Graph<T, W>::add_edge_directional(NodeId from, NodeId to, W weight) {
    auto valid = validate_pair(from, to);
    if (!valid) {
      return valid;
    }
    auto& links = slots_.unchecked_at(from.index).node.links();
    auto existing = find_edge_index(from, to);
    if (existing) {
      links.unchecked_at(existing.value()).set_weight(weight);
      return Ok();
    }
    links.push_back(Edge<T, W>(to, weight));
    return Ok();
  }

  template<typename T, typename W>
  Result<void> Graph<T, W>::add_edge(NodeId from, NodeId to, bool bidirectional) {
    return add_edge(from, to, bidirectional, default_weight_);
  }

  template<typename T, typename W>
  Result<void> Graph<T, W>::add_edge(NodeId from, NodeId to, bool bidirectional, W weight) {
    if (bidirectional) {
      return add_edge_bidirectional(from, to, weight);
    }
    return add_edge_directional(from, to, weight);
  }

  template<typename T, typename W>
  Result<void> Graph<T, W>::edge_weight_directional(NodeId from, NodeId to, W weight) {
    auto edge_index = find_edge_index(from, to);
    if (!edge_index) {
      return Result<void>(edge_index);
    }
    slots_.unchecked_at(from.index).node.links().unchecked_at(edge_index.value()).set_weight(weight);
    return Ok();
  }

  template<typename T, typename W>
  Result<void> Graph<T, W>::edge_weight_bidirectional(NodeId from, NodeId to, W weight) {
    auto first = edge_weight_directional(from, to, weight);
    if (!first) {
      return first;
    }
    return edge_weight_directional(to, from, weight);
  }

  template<typename T, typename W>
  Result<void> Graph<T, W>::edge_weight(NodeId from, NodeId to, W weight, bool bidirectional) {
    if (bidirectional) {
      return edge_weight_bidirectional(from, to, weight);
    }
    return edge_weight_directional(from, to, weight);
  }

  template<typename T, typename W>
  Result<void> Graph<T, W>::remove_edge_directional(NodeId from, NodeId to) {
    auto edge_index = find_edge_index(from, to);
    if (!edge_index) {
      return Result<void>(edge_index);
    }
    return slots_.unchecked_at(from.index).node.links().remove(edge_index.value());
  }

  template<typename T, typename W>
  Result<void> Graph<T, W>::remove_edge_bidirectional(NodeId from, NodeId to) {
    auto first = remove_edge_directional(from, to);
    if (!first) {
      return first;
    }
    return remove_edge_directional(to, from);
  }

  template<typename T, typename W>
  Result<void> Graph<T, W>::remove_edge(NodeId from, NodeId to, bool bidirectional) {
    if (bidirectional) {
      return remove_edge_bidirectional(from, to);
    }
    return remove_edge_directional(from, to);
  }

  template<typename T, typename W>
  Result<W> Graph<T, W>::edge_weight(NodeId from, NodeId to) const {
    auto edge_index = find_edge_index(from, to);
    if (!edge_index) {
      return Err<W>(edge_index.error().code(), edge_index.error().message());
    }
    return Ok(slots_.unchecked_at(from.index).node.links().unchecked_at(edge_index.value()).weight());
  }

  template<typename T, typename W>
  bool Graph<T, W>::edge_exists(NodeId from, NodeId to) const {
    return find_edge_index(from, to).is_ok();
  }

  template<typename T, typename W>
  Result<void> Graph<T, W>::clear_edges(NodeId id) {
    if (!valid_node_id(id)) {
      return Err(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_GRAPH_NODE_ID));
    }
    slots_.unchecked_at(id.index).node.links().clear();
    return Ok();
  }

  template<typename T, typename W>
  void Graph<T, W>::clear_edges() {
    for (usize i = 0; i < slots_.size(); i++) {
      if (slots_.unchecked_at(i).occupied) {
        slots_.unchecked_at(i).node.links().clear();
      }
    }
  }

  template<typename T, typename W>
  Result<usize> Graph<T, W>::find_edge_index(NodeId from, NodeId to) const {
    auto valid = validate_pair(from, to);
    if (!valid) {
      return Err<usize>(valid.error().code(), valid.error().message());
    }
    const auto& links = slots_.unchecked_at(from.index).node.links();
    for (usize i = 0; i < links.size(); i++) {
      if (links.unchecked_at(i).target() == to) {
        return Ok(i);
      }
    }
    return Err<usize>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_GRAPH_EDGE_NOT_FOUND));
  }

  template<typename T, typename W>
  Result<void> Graph<T, W>::validate_pair(NodeId from, NodeId to) const {
    if (!valid_node_id(from) || !valid_node_id(to)) {
      return Err(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_GRAPH_NODE_ID));
    }
    return Ok();
  }
}
