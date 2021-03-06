// arrayuthor: shiyi
#ifndef BASE_H
#define BASE_H
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

#ifndef RB_PARENT
#define rb_parent(r) ((r)->parent)
#endif

#ifndef RB_COLOR
#define rb_color(r) ((r)->color)
#endif

#ifndef RB_IS_RED
#define rb_is_red(r) ((r)->color == red)
#endif

#ifndef RB_IS_BLACK
#define rb_is_black(r) ((r)->color == black)
#endif

#ifndef RB_SET_BLACK
#define rb_set_black(r) ((r)->color = black)
#endif

#ifndef RB_SET_RED
#define rb_set_red(r) ((r)->color = red)
#endif

#ifndef RB_SET_PARENT
#define rb_set_parent(r, p) ((r)->parent = (p))
#endif

#ifndef RB_SET_COLOR
#define rb_set_color(r, c) ((r)->color = (c))
#endif

#ifndef LEN
#define len(x) sizeof(x) / sizeof(x[0])
#endif

enum Color { red, black };

void add(vector<int> &array, int a[], int n) {
  for (int i = 0; i < n; i++) array.push_back(a[i]);
}

void disp(vector<int> array) {
  for (vector<int>::iterator i = array.begin(); i != array.end(); i++)
    cout << *i << " ";
}

template <class T>
class RBTNode {
 public:
  Color color;      // 颜色
  T key;            // 关键字(键值)
  RBTNode *left;    // 左孩子
  RBTNode *right;   // 右孩子
  RBTNode *parent;  // 父结点

  RBTNode(T value, Color c, RBTNode *p, RBTNode *l, RBTNode *r)
      : key(value), color(c), parent(), left(l), right(r) {}
};

template <class T>
class RBTree {
 private:
  RBTNode<T> *root;  // 根结点

 public:
  RBTree();
  ~RBTree();

  // 前序遍历"红黑树"
  void preOrder();
  // 中序遍历"红黑树"
  void inOrder();
  // 后序遍历"红黑树"
  void postOrder();

  // (递归实现)查找"红黑树"中键值为key的节点
  RBTNode<T> *search(T key);
  // (非递归实现)查找"红黑树"中键值为key的节点
  RBTNode<T> *iterativeSearch(T key);

  // 查找最小结点：返回最小结点的键值。
  T minimum();
  // 查找最大结点：返回最大结点的键值。
  T maximum();

  // 找结点(x)的后继结点。即，查找"红黑树中数据值大于该结点"的"最小结点"。
  RBTNode<T> *successor(RBTNode<T> *x);
  // 找结点(x)的前驱结点。即，查找"红黑树中数据值小于该结点"的"最大结点"。
  RBTNode<T> *predecessor(RBTNode<T> *x);

  // 将结点(key为节点键值)插入到红黑树中
  void insert(T key);

  // 删除结点(key为节点键值)
  void remove(T key);

  // 销毁红黑树
  void destroy();

  // 打印红黑树
  void print();

 private:
  // 前序遍历"红黑树"
  void preOrder(RBTNode<T> *tree) const;
  // 中序遍历"红黑树"
  void inOrder(RBTNode<T> *tree) const;
  // 后序遍历"红黑树"
  void postOrder(RBTNode<T> *tree) const;

  // (递归实现)查找"红黑树x"中键值为key的节点
  RBTNode<T> *search(RBTNode<T> *x, T key) const;
  // (非递归实现)查找"红黑树x"中键值为key的节点
  RBTNode<T> *iterativeSearch(RBTNode<T> *x, T key) const;

  // 查找最小结点：返回tree为根结点的红黑树的最小结点。
  RBTNode<T> *minimum(RBTNode<T> *tree);
  // 查找最大结点：返回tree为根结点的红黑树的最大结点。
  RBTNode<T> *maximum(RBTNode<T> *tree);

  // 左旋
  void leftRotate(RBTNode<T> *&root, RBTNode<T> *x);
  // 右旋
  void rightRotate(RBTNode<T> *&root, RBTNode<T> *y);
  // 插入函数
  void insert(RBTNode<T> *&root, RBTNode<T> *node);
  // 插入修正函数
  void insertFixUp(RBTNode<T> *&root, RBTNode<T> *node);
  // 删除函数
  void remove(RBTNode<T> *&root, RBTNode<T> *node);
  // 删除修正函数
  void removeFixUp(RBTNode<T> *&root, RBTNode<T> *node, RBTNode<T> *parent);

  // 销毁红黑树
  void destroy(RBTNode<T> *&tree);

  // 打印红黑树
  void print(RBTNode<T> *tree, T key, int direction);
};

// 构造函数
template <class T>
RBTree<T>::RBTree() : root(NULL) {
  root = NULL;
}

// 析构函数
template <class T>
RBTree<T>::~RBTree() {
  destroy();
}

/*
 * 销毁红黑树
 */
template <class T>
void RBTree<T>::destroy(RBTNode<T> *&tree) {
  if (tree == NULL) return;

  if (tree->left != NULL) return destroy(tree->left);
  if (tree->right != NULL) return destroy(tree->right);

  delete tree;
  tree = NULL;
}

template <class T>
void RBTree<T>::destroy() {
  destroy(root);
}

/*
 * 打印"二叉查找树"
 *
 * key        -- 节点的键值
 * direction  --  0，表示该节点是根节点;
 *               -1，表示该节点是它的父结点的左孩子;
 *                1，表示该节点是它的父结点的右孩子。
 */
template <class T>
void RBTree<T>::print(RBTNode<T> *tree, T key, int direction) {
  if (tree != NULL) {
    if (direction == 0)  // tree是根节点
      cout << setw(2) << tree->key << "(B) is root" << endl;
    else  // tree是分支节点
      cout << setw(2) << tree->key << (rb_is_red(tree) ? "(R)" : "(B)")
           << " is " << setw(2) << key << "'s " << setw(12)
           << (direction == 1 ? "right child" : "left child") << endl;

    print(tree->left, tree->key, -1);
    print(tree->right, tree->key, 1);
  }
}

template <class T>
void RBTree<T>::print() {
  if (root != NULL) print(root, root->key, 0);
}

#endif