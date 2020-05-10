#include <iostream>

using namespace std;

template <typename T>
class TreeNode{

  public:
    TreeNode(); //tree of integers, key and value
    TreeNode(int k, T *data);
    ~TreeNode();
    //virtual ~TreeNode();-when working with a template class
      //look up a virtual destructor when using template
      int key;
      T* data;
      TreeNode<T> *left;
      TreeNode<T> *right;
};

//treenode implementation
template <typename T>
TreeNode<T>:: TreeNode(){

    key = 0;
    left = NULL;
    right = NULL;

}
template <typename T>
TreeNode<T>::TreeNode(int k, T *d){
  key = k;
  data = d;
  left = NULL;
  right = NULL;

}

//destructor to you
template <typename T>
TreeNode<T>::~TreeNode(){
    delete left;
    delete right;
}




template <typename T>
class BinarySearchTree{

  public:
    BinarySearchTree();
    ~BinarySearchTree();

    TreeNode<T> *root;
    int size;

    int getSize();
    bool isEmpty();
    bool contain(int k);

    T* search(int k);
    void add(int k, T *value);
    bool remove(int k);

    TreeNode<T>* getRoot();
    TreeNode<T>* getSuccessor(TreeNode<T>* d);
    T getMin();
    T getMax();
    void printTree(TreeNode<T>* node);

};

template <typename T>
BinarySearchTree<T>::BinarySearchTree(){
  root = NULL;
  size = 0;
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree(){
  delete root;
}

template <typename T>
int BinarySearchTree<T>::getSize(){
    return size;
}

template <typename T>
bool BinarySearchTree<T>:: isEmpty(){
    return (root == NULL);
}

template <typename T>
T* BinarySearchTree<T>::search(int k){

    T* item;

    TreeNode<T> *curr = root;

    while(curr != NULL){
        if(k > curr -> key)
            curr = curr ->right;

        else if(k < curr -> key)
            curr = curr -> left;

        else{
            item = curr -> data;
            break;

        }

    }

    return item;
}

template <typename T>
void BinarySearchTree<T>::printTree(TreeNode<T> *node){
  //recursively
  if(node == NULL)
    return;

  printTree(node->left);

  cout<< node->key<<endl;


  printTree(node->right);

}

template <typename T>
T BinarySearchTree<T>::getMin(){
    //going all the way to the left
    //iterative

    TreeNode<T> *curr = root; //keep track of where we're at

    if(root == NULL){
      return NULL; //empty tree
    }

    while(curr->left != NULL){
      curr = curr->left;
    }
    return curr->key;
}

template<typename T>
T BinarySearchTree<T>::getMax(){
    //going all the way to the right
    //iterative

    TreeNode<T> *curr = root; //keep track of where we're at

    if(root == NULL){
      return NULL; //empty tree
    }

    while(curr->right != NULL){
      curr = curr->right;
    }
    return curr->key;
}

template<typename T>
void BinarySearchTree<T>::add(int k, T *value){


    TreeNode<T> *node = new TreeNode<T>(k,value);
    if(root == NULL) {
      root = node;
    }
    else {
      TreeNode<T> *curr = root;
      TreeNode<T> *parent;

      while(true) {
        parent = curr;
        if(node->key < curr->key) {
          curr = curr->left;
          if(curr == NULL) {
              parent->left = node;
              break;
          }
        }
        else {
          if(node->key > curr->key) {
            curr = curr->right;
            if(curr == NULL) {
              parent->right = node;
              break;
            }
          }
        }
      }
    }
    ++size;

}

template <typename T>
bool BinarySearchTree<T>::remove(int k){
    //identify all of the cases //left//1 child//2 child

    if(root == NULL) {
     return false;
 }

 TreeNode<T> *curr = root;
 TreeNode<T> *parent = root;
 bool isLeft = true;

 while(curr->key != k) {
   parent = curr;

   if(k < curr->key) {
     isLeft = true;
     curr = curr->left;
   }
   else {
     isLeft = false;
     curr = curr->right;
   }

   if(curr == NULL) {
     return false;
   }
 }

 //after we find the correct node, deletion depends on the number and type of children

 //When there are no children
 if(curr->left == NULL && curr->right == NULL) {
   if(curr == root) {
     root = NULL;
   }
   else if(isLeft) {
     parent->left = NULL;
   }
   else {
     parent->right = NULL;
   }
 }


 //A single left child
 else if(curr->right == NULL) {
     if(curr == root) {
       root = curr->left;
     }
     else if(isLeft) {
       parent->left = curr->left;
   }
     else {
       parent->right = curr->right;
     }
 }

 //A single right child
 else if(curr->left == NULL) {
   if(curr == root) {
       root = curr->right;
     }
     else if(isLeft) {
       parent->left = curr->right;
     }
   else {
       parent->right = curr->right;
     }
 }

 //2 children
 else {
   TreeNode<T> *successor = getSuccessor(curr);

   if(curr == root) {
       root = successor;
     }
     else if(isLeft) {
       parent->left = successor;
     }
     else {
       parent->right = successor;
     }
     successor->left = curr->left;
 }

 --size;
 return true;

}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::getRoot(){
  return root;
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::getSuccessor(TreeNode<T>* d){

  TreeNode<T>* parent = d;
	TreeNode<T>* successor = d;
	TreeNode<T>* curr = d->right;

	while(curr != NULL) {
		parent = successor;
		successor = curr;
		curr = curr->left;
	}

	if(successor != d->right) {
		parent->left = successor->right;
		successor->right = d->right;
	}
	return successor;

}
template <typename T>
bool BinarySearchTree<T>::contain(int k){

  if(root == NULL){
    return false;
  }

  TreeNode<T> *curr = root;

  while(curr->key != k){

    if(k <curr->key){
      curr = curr->left;
    }
    else{
      curr = curr->right;
    }
    if(curr == NULL){
      return false;
    }

  }
  return true;
}
