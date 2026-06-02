# ``src/common/graph/graph.inl``

## Purpose
Graph data structure used by warehouse layout and pathfinding.

## Module
``common``

## File Kind
Inline implementation file: contains template method definitions included by headers.

## Includes
- ``graph.h``

## Namespaces
- ``dstr``

## Types
No class, struct, or enum declarations were detected.

## Fields
- ``target_``
- ``weight_``
- ``value_``
- ``links_``
- ``size_``

## Functions And Methods
- ``return Err(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_GRAPH_NODE_ID));``
- ``return Ok();``
- ``return Ok(slots_.unchecked_at(id.index).node.value());``
- ``return Ok(slots_.unchecked_at(raw_index).node.value());``
- ``return Ok(slots_.unchecked_at(id.index).node.links());``
- ``return set_node_value(id, value);``
- ``return Err(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_GRAPH_RAW_INDEX));``
- ``return valid_node_id(id);``
- ``return add_edge_directional(to, from, weight);``
- ``return add_edge(from, to, bidirectional, default_weight_);``
- ``return add_edge_bidirectional(from, to, weight);``
- ``return add_edge_directional(from, to, weight);``
- ``return edge_weight_directional(to, from, weight);``
- ``return edge_weight_bidirectional(from, to, weight);``
- ``return edge_weight_directional(from, to, weight);``
- ``return remove_edge_directional(to, from);``
- ``return remove_edge_bidirectional(from, to);``
- ``return remove_edge_directional(from, to);``
- ``return Ok(slots_.unchecked_at(from.index).node.links().unchecked_at(edge_index.value()).weight());``
- ``return find_edge_index(from, to).is_ok();``
- ``return Ok(i);``

## Notes
This file follows the project convention that all source code belongs to the ``dstr`` namespace, with helper implementation details kept local to their ``.cpp`` file when appropriate.
