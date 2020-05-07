#include <iostream>
#include "TreeNode.h"
using namespace std;

template <typename T>
class BST{

  public:
    BST();
    ~BST();

    TreeNode<T> *root;

    int size;
    int getSize();
    bool isEmpty();
    bool contain(T d);

    T search (T d);
    void add(T d);
    bool remove(T d);

    TreeNode<T>* getSuccessor(TreeNode<T>* d);
    T getMin();
    T getMax();
    void printTree(TreeNode<T>* node);

};

template <typename T>
BST::BST(){
  root = NULL;
  size = 0;
}

template <typename T>
BST::~BST(){
  delete root;
}

template <typename T>
int BST<T>::getSize(){
    return size;
}

template <typename T>
bool BST<T>:: isEmpty(){
    return (root == NULL);
}

template <typename T>
T BST<T>::search(T d){

    T item;

    TreeNode<T> *curr = root;

    while(curr != NULL){
        if(d > curr -> data)
            curr = curr ->right;

        else if(d < curr -> data)
            curr = curr -> left;

        else{
            item = curr ->data;
            break;

        }

    }

    return item;
}

template <typename T>
void BST<T>::printTree(TreeNode<T> *node){
  //recursively
  if(node == NULL)
    return;

  printTree(node->left);

  cout<< node->data<<endl;

  printTree(node->right);

}

template <typename T>
T BST<T>::getMin(){
    //going all the way to the left
    //iterative

    TreeNode *curr = root; //keep track of where we're at

    if(root == NULL){
      return NULL; //empty tree
    }

    while(curr->left != NULL){
      curr = curr->left;
    }
    return curr->data;
}

template<typename T>
T BST<T>::getMax(){
    //going all the way to the right
    //iterative

    TreeNode *curr = root; //keep track of where we're at

    if(root == NULL){
      return NULL; //empty tree
    }

    while(curr->right != NULL){
      curr = curr->right;
    }
    return curr->data;
}

template<typename T>
void BST<T>::add(T d){
    ++size;
    TreeNode<T> *node = new TreeNode(d);


    //check
    if(isEmpty()){
      //empty tree
      root = node;
    }
    else{
      //not empty
      TreeNode *curr = root; //start at the root
      TreeNode *parent; //previous

      //traverse the tree to find the spot
      while(true){
        parent = curr;

        if(d < curr->data){
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
bool BST<T>::remove(T d){
    //identify all of the cases //left//1 child//2 child

      if(isEmpty())
        return false;

      //keep track of parent and the current

      TreeNode<T> *parent = root;
      TreeNode<T> *current = root;
      bool isLeft = true;

      while(current->data != d){

        parent = current;
        if(d < current->data){
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
        root = sucessor;
      else if (isLeft)
        parent->left = successor;
      else
        parent->right = successor;

      //connect/link successor to current's left child which is d
      successor->left = current->left;

      return true;
    }

}



template <typename T>
TreeNode<T>* BST<T>::getSuccessor(TreeNode<T>* d){
  //the parameter d represents the node to be deleted

  TreeNode *current = d->right; //using right once all the way left method
  TreeNode *sp = d; //keep track of sucessor parent
  TreeNode *successor = d;


  while(current != NULL){
    //all the way to the left

    sp = sucessor;
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
