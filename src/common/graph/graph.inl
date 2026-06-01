#include "graph.h"


namespace dstr {


  // =====Link<> class

  template<typename T, typename W>
  Link<T, W>::Link() : weight_{W()} {}

  template<typename T, typename W>
  Link<T, W>::Link(sp<Node<T, W>> target, W weight )
    : weight_{ weight }, target_{ wp<Node<T, W>>(target) } {}

  template<typename T, typename W>
  const wp<Node<T, W>> Link<T,W>::target() {
    return target_;
  }

  template<typename T, typename W>
  const W Link<T, W>::weight() {
    return weight_;
  }

  template<typename T, typename W>
  Link<T, W>& Link<T,W>::operator=(const Link<T, W>& other){
    weight_ = other.weight_;
    target_ = other.target_;
    return *this;
  }

  template<typename T, typename W>
  Link<T, W>& Link<T,W>::operator=(Link<T, W>&& other){
    weight_ = other.weight_;
    target_ = other.target_;
    other.weight_ = W();
    other.target_.reset();
    return *this;
  }


  // =====Node<> class

  template<typename T, typename W>
  Node<T, W>::Node() : value_{ T() }, links_{ Array<Link<T,W>>() } {}

  template<typename T, typename W>
  Node<T, W>::Node(T value) : value_{ value }, links_{ Array<Link<T,W>>() } {}
  /*
  template<typename T, typename W>
  Node<T, W>& Node<T, W>::operator=(const Node<T, W>& other) {
    value_ = other.value_;
    links_ = other.links_;
  }

  template<typename T, typename W>
  Node<T, W>& Node<T, W>::operator=(Node<T, W>&& other) {
    value_ = other.value_;
    links_ = move(other.links_);
    other.value_ = T();
  }
  */

  // =====Graph<> class

  template<typename T, typename W>
  Graph<T, W>::Graph() : nodes_{ Array<sp<Node<T, W>>>() }, default_weight_{ W() } {}

  template<typename T, typename W>
  Graph<T, W>::Graph(W default_weight) : nodes_{ Array<sp<Node<T, W>>>() }, default_weight_{ default_weight } {}
}
