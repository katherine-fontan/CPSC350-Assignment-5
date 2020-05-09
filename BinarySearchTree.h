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
    ++size;

    TreeNode<T> *node = new TreeNode<T>(k,value);
    //check
    if(isEmpty()){
      //empty tree
      root = node;
    }
    else{
      //not empty
      TreeNode<T> *curr = root; //start at the root
      TreeNode<T> *parent; //previous

      //traverse the tree to find the spot
      while(true){
        parent = curr;

        if(node->key < curr->key){
          //go left
          curr = curr->left;
          if(curr == NULL){
            //insertion process
             parent->left = node;
             break;
          }

          else{
            //go right
            curr = curr->right;

            if(curr == NULL){
              parent->right = node;
              break;
            }
          }
        }
      }
    }
}

template <typename T>
bool BinarySearchTree<T>::remove(int k){
    //identify all of the cases //left//1 child//2 child

      if(isEmpty())
        return false;

      //keep track of parent and the current

      TreeNode<T> *parent = root;
      TreeNode<T> *current = root;
      bool isLeft = true;

      while(current->key != k){

        parent = current;
        if(k < current->key){
          isLeft = true;
          current = current->left;
        }
        else{
          isLeft = false;
          current = current->right;
        }

        if(current == NULL){
          return false;
        }
      }
      //if we make it here, we found the value now lets proceed to delete
      //check if its leaf, 1 child, 2 children




      if(current->left == NULL && current->right == NULL){
        //then we have a leaf node

        //determine if its the root and if its a left node or a right node
        if(current == root)
          root == NULL;
        else if (isLeft)
          parent->left = NULL;
        else
          parent->right = NULL;

    }

    //this else if determines positions of children of node to be deleted

    //nodes with one child
    else if(current->right == NULL){
      //we have a parent with 1 child
      //no right child so much be left child

    //these branching statements identify position of node to be deleted
        if(current == root)
          root = current->left;

        //determine the position of the node
        else if (isLeft)
          parent->left = current->left;
        else
          parent->right = current->left;


    }
    //nodes with one child
    else if(current->left == NULL){
      //we have a parent with 1 child
      //no right child so much be left child

      //these branching statements identify position of node to be deleted
        if(current == root)
          root = current->right;

        else if (isLeft)
          parent->left = current->right;
        else
          parent->right = current-> right;


    }

    else{
      //the node to be deleted has two children

      //at this point we begin to cry and bang our head on the keyboard

      TreeNode<T> *successor = getSuccessor(current);

      if(current == root)
        root = successor;
      else if (isLeft)
        parent->left = successor;
      else
        parent->right = successor;

      //connect/link successor to current's left child which is d
      successor->left = current->left;


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
  //the parameter d represents the node to be deleted

  TreeNode<T> *current = d->right; //using right once all the way left method
  TreeNode<T> *sp = d; //keep track of successor parent
  TreeNode<T> *successor = d;


  while(current != NULL){
    //all the way to the left

    sp = successor;
    successor = current;
    current = current->left; //going all the way left
  }

  if(successor != d->right){
    sp->left = successor->right;
    successor->right = d->right;

    //only executes if the successor is not the right child of node to be deleted
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
