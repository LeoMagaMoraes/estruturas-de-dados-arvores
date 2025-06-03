#pragma once
#include <vector>

/**
 * @brief Classe que representa uma Árvore Binária de Busca (BST).
 *
 * Armazena elementos em ordem, permitindo operações eficientes de busca,
 * inserção e remoção.
 *
 * @tparam T Tipo dos elementos armazenados na árvore.
 */
template <class T>
class BST {
 public:
  /**
   * @brief Estrutura interna que representa um nó da árvore.
   */
  struct TreeNode {
    T data;           ///< Valor armazenado no nó.
    TreeNode* left;   ///< Ponteiro para o filho à esquerda.
    TreeNode* right;  ///< Ponteiro para o filho à direita.

    TreeNode(const T& value);
    ~TreeNode();

    TreeNode* max();
    TreeNode* min();
  };

 private:
  TreeNode* root;  ///< Ponteiro para a raiz da árvore.

  bool insert(TreeNode*& node, const T& value);
  bool remove(TreeNode*& node, const T& value);
  bool contain(const TreeNode* const node, const T& value) const;

  void in_order(const TreeNode* const node, std::vector<T>& result) const;
  void pre_order(const TreeNode* const node, std::vector<T>& result) const;
  void post_order(const TreeNode* const node, std::vector<T>& result) const;

  TreeNode* find_node(TreeNode* node, const T& value) const {
    if (!node) return nullptr;
    if (value < node->data)
      return find_node(node->left, value);
    else if (node->data < value)
      return find_node(node->right, value);
    else
      return node;
  }

 public:
  BST();
  ~BST();

  bool insert(const T& value);
  bool remove(const T& value);
  bool contain(const T& value) const;

  std::vector<T> in_order() const;
  std::vector<T> pre_order() const;
  std::vector<T> post_order() const;

  TreeNode* find_node(const T& value) const { return find_node(root, value); }
};

// === IMPLEMENTAÇÕES ===

template <class T>
BST<T>::TreeNode::TreeNode(const T& value)
    : data(value), left(nullptr), right(nullptr) {}

template <class T>
BST<T>::TreeNode::~TreeNode() {
  delete left;
  delete right;
}

template <class T>
typename BST<T>::TreeNode* BST<T>::TreeNode::max() {
  return right ? right->max() : this;
}

template <class T>
typename BST<T>::TreeNode* BST<T>::TreeNode::min() {
  return left ? left->min() : this;
}

template <class T>
BST<T>::BST() : root(nullptr) {}

template <class T>
BST<T>::~BST() {
  delete root;
}

template <class T>
bool BST<T>::insert(const T& value) {
  return insert(root, value);
}

template <class T>
bool BST<T>::insert(TreeNode*& node, const T& value) {
  if (!node) {
    node = new TreeNode(value);
    return true;
  }
  if (value < node->data)
    return insert(node->left, value);
  else if (node->data < value)
    return insert(node->right, value);
  return false;  // já existe
}

template <class T>
bool BST<T>::remove(const T& value) {
  return remove(root, value);
}

template <class T>
bool BST<T>::remove(TreeNode*& node, const T& value) {
  if (!node) return false;

  if (value < node->data) {
    return remove(node->left, value);
  } else if (node->data < value) {
    return remove(node->right, value);
  } else {
    if (!node->left) {
      TreeNode* temp = node;
      node = node->right;
      delete temp;
    } else if (!node->right) {
      TreeNode* temp = node;
      node = node->left;
      delete temp;
    } else {
      TreeNode* minRight = node->right->min();
      node->data = minRight->data;
      return remove(node->right, minRight->data);
    }
    return true;
  }
}

template <class T>
bool BST<T>::contain(const T& value) const {
  return contain(root, value);
}

template <class T>
bool BST<T>::contain(const TreeNode* const node, const T& value) const {
  if (!node) return false;
  if (value < node->data)
    return contain(node->left, value);
  else if (node->data < value)
    return contain(node->right, value);
  return true;
}

template <class T>
void BST<T>::in_order(const TreeNode* const node, std::vector<T>& result) const {
  if (!node) return;
  in_order(node->left, result);
  result.push_back(node->data);
  in_order(node->right, result);
}

template <class T>
std::vector<T> BST<T>::in_order() const {
  std::vector<T> result;
  in_order(root, result);
  return result;
}

template <class T>
void BST<T>::pre_order(const TreeNode* const node, std::vector<T>& result) const {
  if (!node) return;
  result.push_back(node->data);
  pre_order(node->left, result);
  pre_order(node->right, result);
}

template <class T>
std::vector<T> BST<T>::pre_order() const {
  std::vector<T> result;
  pre_order(root, result);
  return result;
}

template <class T>
void BST<T>::post_order(const TreeNode* const node, std::vector<T>& result) const {
  if (!node) return;
  post_order(node->left, result);
  post_order(node->right, result);
  result.push_back(node->data);
}

template <class T>
std::vector<T> BST<T>::post_order() const {
  std::vector<T> result;
  post_order(root, result);
  return result;
}