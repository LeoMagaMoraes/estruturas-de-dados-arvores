#pragma once
#include <algorithm>
#include <vector>

template <class T>
class AVL {
 private:
  struct TreeNode {
    T data;
    TreeNode* left;
    TreeNode* right;
    int height;

    TreeNode(const T& value)
        : data(value), left(nullptr), right(nullptr), height(0) {}

    ~TreeNode() {
      delete left;
      delete right;
    }

    TreeNode* max() {
      return right ? right->max() : this;
    }

    TreeNode* min() {
      return left ? left->min() : this;
    }
  };

  TreeNode* root;

  int height(TreeNode* node) const {
    return node ? node->height : -1;
  }

  int balance_factor(TreeNode* node) const {
    return height(node->left) - height(node->right);
  }

  void update_height(TreeNode* node) {
    node->height = 1 + std::max(height(node->left), height(node->right));
  }

  void rotate_left(TreeNode*& node) {
    TreeNode* r = node->right;
    node->right = r->left;
    r->left = node;
    update_height(node);
    update_height(r);
    node = r;
  }

  void rotate_right(TreeNode*& node) {
    TreeNode* l = node->left;
    node->left = l->right;
    l->right = node;
    update_height(node);
    update_height(l);
    node = l;
  }

  void balance(TreeNode*& node) {
    update_height(node);
    int bf = balance_factor(node);

    if (bf > 1) {
      if (balance_factor(node->left) < 0)
        rotate_left(node->left);
      rotate_right(node);
    } else if (bf < -1) {
      if (balance_factor(node->right) > 0)
        rotate_right(node->right);
      rotate_left(node);
    }
  }

  bool insert(TreeNode*& node, const T& value) {
    if (!node) {
      node = new TreeNode(value);
      return true;
    }

    if (value < node->data) {
      if (!insert(node->left, value)) return false;
    } else if (value > node->data) {
      if (!insert(node->right, value)) return false;
    } else {
      return false;
    }

    balance(node);
    return true;
  }

  bool remove(TreeNode*& node, const T& value) {
    if (!node) return false;

    if (value < node->data) {
      if (!remove(node->left, value)) return false;
    } else if (value > node->data) {
      if (!remove(node->right, value)) return false;
    } else {
      TreeNode* temp = node;

      if (!node->left) {
        node = node->right;
        temp->right = nullptr;
        delete temp;
      } else if (!node->right) {
        node = node->left;
        temp->left = nullptr;
        delete temp;
      } else {
        TreeNode* minNode = node->right->min();
        node->data = minNode->data;
        remove(node->right, minNode->data);
      }
    }

    if (node) balance(node);
    return true;
  }

  bool contain(const TreeNode* const node, const T& value) const {
    if (!node) return false;
    if (value < node->data)
      return contain(node->left, value);
    else if (value > node->data)
      return contain(node->right, value);
    return true;
  }

  void in_order(const TreeNode* const node, std::vector<T>& result) const {
    if (!node) return;
    in_order(node->left, result);
    result.push_back(node->data);
    in_order(node->right, result);
  }

  void pre_order(const TreeNode* const node, std::vector<T>& result) const {
    if (!node) return;
    result.push_back(node->data);
    pre_order(node->left, result);
    pre_order(node->right, result);
  }

  void post_order(const TreeNode* const node, std::vector<T>& result) const {
    if (!node) return;
    post_order(node->left, result);
    post_order(node->right, result);
    result.push_back(node->data);
  }

 public:
  AVL() : root(nullptr) {}

  ~AVL() { delete root; }

  bool insert(const T& value) {
    return insert(root, value);
  }

  bool remove(const T& value) {
    return remove(root, value);
  }

  bool contain(const T& value) const {
    return contain(root, value);
  }

  std::vector<T> in_order() const {
    std::vector<T> result;
    in_order(root, result);
    return result;
  }

  std::vector<T> pre_order() const {
    std::vector<T> result;
    pre_order(root, result);
    return result;
  }

  std::vector<T> post_order() const {
    std::vector<T> result;
    post_order(root, result);
    return result;
  }

  bool is_balanced() const {
    return is_balanced(root).first;
  }

  std::pair<bool, int> is_balanced(TreeNode* node) const {
    if (!node) return {true, -1};

    auto left = is_balanced(node->left);
    auto right = is_balanced(node->right);

    bool balanced =
        left.first && right.first && std::abs(left.second - right.second) <= 1;
    int node_height = 1 + std::max(left.second, right.second);

    return {balanced, node_height};
  }
};
