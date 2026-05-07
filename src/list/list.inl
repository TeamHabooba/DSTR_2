// list.inl
// Included at the bottom of list.h, do not include directly.

namespace dstr {

  // Node

  template <typename T>
  List<T>::Node::Node(const T& value, i32 lvl)
    : data(value), level(lvl) {
    for (i32 i = 0; i <= MAX_LEVEL; ++i)
      forward[i] = nullptr;
  }


  // Lifecycle

  template <typename T>
  List<T>::List() : currentLevel_(0), size_(0) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    head_ = up<Node>(new Node(T{}, MAX_LEVEL));
  }

  // Destructor walks forward[0] and deletes each node manually to avoid
  // recursive deletion chaining through up<Node>, which would stack overflow
  // on large lists.
  template <typename T>
  List<T>::~List() {
    Node* cur = head_->forward[0];
    while (cur) {
      Node* next = cur->forward[0];
      delete cur;
      cur = next;
    }
    head_->forward[0] = nullptr;
  }


  // Copy and move

  // Deep copy: re-inserts every element into a fresh list.
  // Insertion preserves sorted order so the skip structure rebuilds correctly.
  template <typename T>
  List<T>::List(const List& other) : currentLevel_(0), size_(0) {
    head_ = up<Node>(new Node(T{}, MAX_LEVEL));
    other.for_each([this](const T& val) { insert(val); });
  }

  template <typename T>
  List<T>& List<T>::operator=(const List& other) {
    if (this != &other) {
      Node* cur = head_->forward[0];
      while (cur) {
        Node* next = cur->forward[0];
        delete cur;
        cur = next;
      }
      head_->forward[0] = nullptr;
      currentLevel_ = 0;
      size_ = 0;
      other.for_each([this](const T& val) { insert(val); });
    }
    return *this;
  }

  // Move: steals the sentinel and metadata, leaves other in a valid empty state.
  template <typename T>
  List<T>::List(List&& other) noexcept
    : head_(move(other.head_)),
      currentLevel_(other.currentLevel_),
      size_(other.size_) {
    other.currentLevel_ = 0;
    other.size_         = 0;
    other.head_ = up<Node>(new Node(T{}, MAX_LEVEL));
  }

  template <typename T>
  List<T>& List<T>::operator=(List&& other) noexcept {
    if (this != &other) {
      Node* cur = head_->forward[0];
      while (cur) {
        Node* next = cur->forward[0];
        delete cur;
        cur = next;
      }
      head_           = move(other.head_);
      currentLevel_   = other.currentLevel_;
      size_           = other.size_;
      other.currentLevel_ = 0;
      other.size_         = 0;
      other.head_ = up<Node>(new Node(T{}, MAX_LEVEL));
    }
    return *this;
  }


  // Internal helpers

  template <typename T>
  i32 List<T>::randomLevel() {
    i32 level = 0;
    while (level < MAX_LEVEL &&
           (static_cast<float>(std::rand()) / RAND_MAX) < PROB)
      ++level;
    return level;
  }

  template <typename T>
  void List<T>::findUpdate(const T& value, Node* update[]) const {
    Node* cur = head_.get();
    for (i32 i = currentLevel_; i >= 0; --i) {
      while (cur->forward[i] && cur->forward[i]->data < value)
        cur = cur->forward[i];
      update[i] = cur;
    }
  }


  // Public operations

  template <typename T>
  void List<T>::insert(const T& value) {
    Node* update[MAX_LEVEL + 1];
    findUpdate(value, update);

    Node* candidate = update[0]->forward[0];
    if (candidate && candidate->data == value)
      return; // duplicate, skip

    i32 newLevel = randomLevel();
    if (newLevel > currentLevel_) {
      for (i32 i = currentLevel_ + 1; i <= newLevel; ++i)
        update[i] = head_.get();
      currentLevel_ = newLevel;
    }

    Node* newNode = new Node(value, newLevel);
    for (i32 i = 0; i <= newLevel; ++i) {
      newNode->forward[i]   = update[i]->forward[i];
      update[i]->forward[i] = newNode;
    }
    ++size_;
  }

  template <typename T>
  void List<T>::display() const {
    Node* cur = head_->forward[0];
    while (cur) {
      std::cout << cur->data << "\n";
      cur = cur->forward[0];
    }
  }

  template <typename T>
  void List<T>::search(const T& value) const {
    Node* cur = head_.get();
    for (i32 i = currentLevel_; i >= 0; --i)
      while (cur->forward[i] && cur->forward[i]->data < value)
        cur = cur->forward[i];
    cur = cur->forward[0];
    if (cur && cur->data == value)
      std::cout << "Found: " << cur->data << "\n";
    else
      std::cout << "Not found\n";
  }

  template <typename T>
  const T* List<T>::find(const T& value) const {
    Node* cur = head_.get();
    for (i32 i = currentLevel_; i >= 0; --i)
      while (cur->forward[i] && cur->forward[i]->data < value)
        cur = cur->forward[i];
    cur = cur->forward[0];
    if (cur && cur->data == value)
      return &cur->data;
    return nullptr;
  }

  template <typename T>
  bool List<T>::remove(const T& value) {
    Node* update[MAX_LEVEL + 1];
    findUpdate(value, update);

    Node* target = update[0]->forward[0];
    if (!target || target->data != value)
      return false;

    for (i32 i = 0; i <= currentLevel_; ++i) {
      if (update[i]->forward[i] != target) break;
      update[i]->forward[i] = target->forward[i];
    }
    target->forward[0] = nullptr;
    delete target;
    --size_;

    while (currentLevel_ > 0 && !head_->forward[currentLevel_])
      --currentLevel_;

    return true;
  }

  template <typename T>
  void List<T>::sort() {} // always sorted on insert

  template <typename T>
  bool List<T>::empty() const {
    return size_ == 0;
  }

  template <typename T>
  i32 List<T>::size() const {
    return size_;
  }

  template <typename T>
  template <typename Visitor>
  void List<T>::for_each(Visitor fn) const {
    Node* cur = head_->forward[0];
    while (cur) {
      fn(cur->data);
      cur = cur->forward[0];
    }
  }

} // namespace dstr
