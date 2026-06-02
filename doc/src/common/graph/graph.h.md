# ``src/common/graph/graph.h``

## Purpose
Graph data structure used by warehouse layout and pathfinding.

## Module
``common``

## File Kind
Header file: contains declarations and public API contracts.

## Includes
- ``common/aliases/aliases.h``
- ``common/enums.h``
- ``common/array/array.h``
- ``graph.inl``

## Namespaces
- ``dstr``

## Types
- ``class Edge``
- ``class Node``
- ``class Graph``
- ``struct NodeId``
- ``struct NodeSlot``

## Fields
- ``target_``
- ``size_``

## Functions And Methods
- ``NodeId target() const;``
- ``void set_weight(W weight);``
- ``const T& value() const;``
- ``T& value();``
- ``void set_value(T value);``
- ``Result<NodeId> add_node(T value);``
- ``Result<void> set_node_value(NodeId id, T value);``
- ``Result<void> remove_node(NodeId id);``
- ``usize size() const;``
- ``usize raw_size() const;``
- ``Result<T> at(NodeId id) const;``
- ``Result<T> at(usize raw_index) const;``
- ``Result<void> update(NodeId id, T value);``
- ``Result<void> update(usize raw_index, T value);``
- ``bool valid_node_id(NodeId id) const;``
- ``bool occupied(NodeId id) const;``
- ``bool occupied(usize raw_index) const;``
- ``NodeId node_id_at(usize raw_index) const;``
- ``Result<void> add_edge_bidirectional(NodeId from, NodeId to, W weight);``
- ``Result<void> add_edge_directional(NodeId from, NodeId to, W weight);``
- ``Result<void> add_edge(NodeId from, NodeId to, bool bidirectional = false);``
- ``Result<void> add_edge(NodeId from, NodeId to, bool bidirectional, W weight);``
- ``Result<void> edge_weight_directional(NodeId from, NodeId to, W weight);``
- ``Result<void> edge_weight_bidirectional(NodeId from, NodeId to, W weight);``
- ``Result<void> edge_weight(NodeId from, NodeId to, W weight, bool bidirectional = false);``
- ``Result<void> remove_edge_directional(NodeId from, NodeId to);``
- ``Result<void> remove_edge_bidirectional(NodeId from, NodeId to);``
- ``Result<void> remove_edge(NodeId from, NodeId to, bool bidirectional = false);``
- ``Result<W> edge_weight(NodeId from, NodeId to) const;``
- ``bool edge_exists(NodeId from, NodeId to) const;``
- ``Result<void> clear_edges(NodeId id);``
- ``void clear_edges();``
- ``Result<usize> find_edge_index(NodeId from, NodeId to) const;``
- ``Result<void> validate_pair(NodeId from, NodeId to) const;``

## Notes
This file follows the project convention that all source code belongs to the ``dstr`` namespace, with helper implementation details kept local to their ``.cpp`` file when appropriate.
