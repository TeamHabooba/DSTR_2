# `src/common/graph/graph.h`

## Purpose
Generic graph declaration with generation-checked node handles, edge objects, node slots, and weighted adjacency operations.

## Module
`common/graph`

## File Kind
Header file: declares public API, types, aliases, constants, or inline template entry points.

## Includes
### Standard Library
- (none)

### Project Files
- `<common/aliases/aliases.h>`
- `<common/enums.h>`
- `<common/array/array.h>`
- `"graph.inl"`

## Namespaces
- `dstr`

## How It Works
Graph stores nodes in an Array of NodeSlot values. Each NodeId contains a slot index and generation; validation checks both, so removed/reused slots cannot be accessed through old ids. Edges live in each Node as adjacency arrays.

## Types, Structs, Enums, And Aliases
- `class Edge`: Weighted graph adjacency record. It stores the target NodeId and edge weight used by layout/navigation.
- `class Node`: Graph node wrapper containing the node value and an Array of outgoing edges.
- `class Graph`: Array-backed graph. Public callers use NodeId handles; internals validate index/generation and manage edge arrays per node.
- `struct NodeId`: Generation-aware graph handle. The index addresses a raw slot, while generation prevents stale handles from silently referring to reused nodes.
- `struct NodeSlot`: Internal graph slot that stores a Node value directly plus occupancy and generation metadata.

## Fields
- `index`: Internal state used by the file API or domain object.
- `generation`: Internal state used by the file API or domain object.
- `occupied`: Internal state used by the file API or domain object.
- `weight_`: Internal state used by the file API or domain object.
- `target_`: Internal state used by the file API or domain object.
- `value_`: Internal state used by the file API or domain object.
- `default_weight_`: Internal state used by the file API or domain object.
- `size_`: Tracks the number of currently active elements.

## Functions And Methods
- `NodeSlot();`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Edge();`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Edge(NodeId target, W weight = W());`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `NodeId target() const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `W weight() const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `void set_weight(W weight);`: Updates one field directly; callers keep validation at higher-level workflow boundaries when required.
- `Node();`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Node(T value);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `const T& value() const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `T& value();`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `void set_value(T value);`: Updates one field directly; callers keep validation at higher-level workflow boundaries when required.
- `const Array<Edge<T, W>>& links() const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Array<Edge<T, W>>& links();`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Graph();`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Graph(W default_weight);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Result<NodeId> add_node(T value);`: Uses raw slots plus generation counters to distinguish live nodes from stale or removed handles.
- `Result<void> set_node_value(NodeId id, T value);`: Updates one field directly; callers keep validation at higher-level workflow boundaries when required.
- `Result<void> remove_node(NodeId id);`: Uses raw slots plus generation counters to distinguish live nodes from stale or removed handles.
- `usize size() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `usize raw_size() const;`: Returns stored state directly without extra allocation or ownership transfer.
- `Result<T> at(NodeId id) const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Result<T> at(usize raw_index) const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Result<Array<Edge<T, W>>> edges(NodeId id) const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Result<void> update(NodeId id, T value);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Result<void> update(usize raw_index, T value);`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `bool valid_node_id(NodeId id) const;`: Checks the raw slot and generation fields so stale NodeId values are rejected.
- `bool occupied(NodeId id) const;`: Uses raw slots plus generation counters to distinguish live nodes from stale or removed handles.
- `bool occupied(usize raw_index) const;`: Uses raw slots plus generation counters to distinguish live nodes from stale or removed handles.
- `NodeId node_id_at(usize raw_index) const;`: Converts the 2D position to a raw slot and returns the stored generation-aware NodeId.
- `Result<void> add_edge_bidirectional(NodeId from, NodeId to, W weight);`: Validates both NodeId handles, finds matching adjacency entries, then mutates one or both edge arrays depending on directionality.
- `Result<void> add_edge_directional(NodeId from, NodeId to, W weight);`: Validates both NodeId handles, finds matching adjacency entries, then mutates one or both edge arrays depending on directionality.
- `Result<void> add_edge(NodeId from, NodeId to, bool bidirectional = false);`: Validates both NodeId handles, finds matching adjacency entries, then mutates one or both edge arrays depending on directionality.
- `Result<void> add_edge(NodeId from, NodeId to, bool bidirectional, W weight);`: Validates both NodeId handles, finds matching adjacency entries, then mutates one or both edge arrays depending on directionality.
- `Result<void> edge_weight_directional(NodeId from, NodeId to, W weight);`: Validates both NodeId handles, finds matching adjacency entries, then mutates one or both edge arrays depending on directionality.
- `Result<void> edge_weight_bidirectional(NodeId from, NodeId to, W weight);`: Validates both NodeId handles, finds matching adjacency entries, then mutates one or both edge arrays depending on directionality.
- `Result<void> edge_weight(NodeId from, NodeId to, W weight, bool bidirectional = false);`: Validates both NodeId handles, finds matching adjacency entries, then mutates one or both edge arrays depending on directionality.
- `Result<void> remove_edge_directional(NodeId from, NodeId to);`: Validates both NodeId handles, finds matching adjacency entries, then mutates one or both edge arrays depending on directionality.
- `Result<void> remove_edge_bidirectional(NodeId from, NodeId to);`: Validates both NodeId handles, finds matching adjacency entries, then mutates one or both edge arrays depending on directionality.
- `Result<void> remove_edge(NodeId from, NodeId to, bool bidirectional = false);`: Validates both NodeId handles, finds matching adjacency entries, then mutates one or both edge arrays depending on directionality.
- `Result<W> edge_weight(NodeId from, NodeId to) const;`: Validates both NodeId handles, finds matching adjacency entries, then mutates one or both edge arrays depending on directionality.
- `bool edge_exists(NodeId from, NodeId to) const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Result<void> clear_edges(NodeId id);`: Resets the backing container state so later operations start from an empty collection.
- `void clear_edges();`: Resets the backing container state so later operations start from an empty collection.
- `Result<usize> find_edge_index(NodeId from, NodeId to) const;`: Participates in the file API using project aliases and Result-based control flow where failures are possible.
- `Result<void> validate_pair(NodeId from, NodeId to) const;`: Validates both endpoint NodeId handles before an edge operation touches adjacency arrays.

## Project Convention Compliance
- Namespace: follows the project-wide dstr namespace convention.
- String ownership: follows; no standalone user-facing string literals are introduced here.
- Type vocabulary: follows; public surfaces prefer project aliases and domain id aliases where applicable.

