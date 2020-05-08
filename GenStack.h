#include <iostream>
using namespace std;

template <typename T>
class GenStack
{

  int top;
  int size;

  T *stackArray;
  T *newStackArray;
  public:
    GenStack(); //default constructor
    GenStack (int maxSize); //overloaded constructor
    ~GenStack(){
      delete[] stackArray;
    }; //destructor

    //core functions
    void push(T data); //insert an item
    void memoryAllocator();
    T pop(); //remove

    //aux/helper funcitons
    T peak(); //AKA top
    bool isEmpty();
    bool isFull();


     //represent the memory address of the first block of this array.
    //Because then we know that everythign else is gonna be one byte over

};


template<typename T>
GenStack<T>:: GenStack(int maxSize){

  stackArray = new T[maxSize]; // on the heap because it is dynamic.
  size = maxSize;
  top = -1;
}



template <typename T>
void GenStack<T>::push(T data){

  //always check if its full before attempting to push/insert
  if(isFull()){
    //double size of stack
    memoryAllocator();
  }
  //assuming its not isFull
  stackArray[++top] = data;
}
template <typename T>
T GenStack<T>::pop(){
  //chekc if empty before attempting to remove
  if(isEmpty()){
    throw  "The Stack is empty."; //throw exception if stack is empty
  }
  else
    return stackArray[top--];
}

template <typename T>
T GenStack<T>::peak(){
  return stackArray[top];
}
template <typename T>
bool GenStack<T>::isFull(){
  return (top == size-1);
}
template <typename T>
bool GenStack<T>::isEmpty(){
  return (top == -1);
}

template<typename T>
void GenStack<T>:: memoryAllocator(){
  size *= 2; //this would double the size of the array
  newStackArray = new T[size];

  for(int i=0; i<=top; ++i){
    newStackArray[i] = stackArray[i];
  }
  stackArray = newStackArray;
}
