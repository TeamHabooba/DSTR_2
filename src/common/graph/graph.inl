#include "graph.h"


namespace dstr {


  // =====Edge<> class

  template<typename T, typename W>
  Edge<T, W>::Edge() : weight_{W()} {}

  template<typename T, typename W>
  Edge<T, W>::Edge(NodeId target, W weight )
    : weight_{ weight }, target_{ NodeId(target) } {}

  template<typename T, typename W>
  const NodeId Edge<T,W>::target() {
    return target_;
  }

  template<typename T, typename W>
  const W Edge<T, W>::weight() {
    return weight_;
  }


  // =====Node<> class

  template<typename T, typename W>
  Node<T, W>::Node() : value_{ T() }, links_{ Array<Edge<T,W>>() } {}

  template<typename T, typename W>
  Node<T, W>::Node(T value) : value_{ value }, links_{ Array<Edge<T,W>>() } {}


  // =====Graph<> class

  template<typename T, typename W>
  Graph<T, W>::Graph() : slots_{ Array<NodeSlot<T,W>>() }, default_weight_{ W() } {}

  template<typename T, typename W>
  Graph<T, W>::Graph(W default_weight) : slots_{ Array<NodeSlot<T,W>>() }, default_weight_{ default_weight } {}
}
