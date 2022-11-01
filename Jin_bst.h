#pragma once
#ifndef JIN_BST_H
#define JIN_BST_H

#include <stdlib.h>
#include <iostream>

template <typename T>
struct Node{
  T data;
  Node(){data = NULL;}
  Node(T input){data = input;}
  ~Node(){}
  
  //R = larger; L = smaller;
  Node<T>* right = NULL;
  Node<T>* left = NULL;
};

template <typename T>
struct BST{
  
  Node<T>* root = NULL;
  BST(){}
  //Destructor calls recursive delete method
  ~BST(){DeleteRecur(root);};

  Node<T>* Insert(T input);
  void Remove(T input);
  bool ElementExists(T input);
  Node<T>* Find(T input);
  T* ToArray();
  void Empty();
  int Count();

protected:
  void DeleteRecur(Node<T>* treeRoot);
  void ToArrayRecur(Node<T>* treeRoot,T arr[]);
  int CountRecur(Node<T>* treeRoot);
};


//BST METHODS

template <typename T>
void BST<T>::DeleteRecur(Node<T>* treeRoot){
  if(treeRoot){
    DeleteRecur(treeRoot->left);
    DeleteRecur(treeRoot->right);
    delete treeRoot;
  }
}

//If input Node already exists, return a pointer to it
template <typename T>
Node<T>* BST<T>::Insert(T input){

  Node<T>* pos = root;
  bool done = false;
  if(root == NULL){
    root = new Node(input);
    pos = root;
    done = true;
  }
  
  while(!done){
    
    if(input == pos->data){
      done = true;
    }
    else if(input > pos->data){
      if(pos->right == NULL){
	pos->right = new Node(input);
	done = true;
      }
      pos = pos->right;
    }
    else if(input < pos->data){
      if(pos->left == NULL){
	pos->left = new Node(input);
	done = true;
      }
      pos = pos->left;
    }
  }
  return pos;
}

template <typename T>
void BST<T>::Remove(T input){
  Node<T>* last = NULL;
  Node<T>* pos = root;
  
  //Find the node to be removed then place in pos
  while(pos != NULL){
    if(input > pos->data){
      last = pos;
      pos = pos->right;
    }
    else if(input < pos->data){
      last = pos;
      pos = pos->left;
    }
    else{
      break;
    }
  }
  
  //If not found, return
  if(pos == NULL)
    return;
  
  //Remove No Child Node;
  if(pos->left == NULL && pos->right == NULL){
    if(pos == last->left){
      last->left = NULL;
    }
    else if(pos == last->right){
      last->right = NULL;
    }
    delete pos;
  }

  //Remove when only has 1 child
  else if((pos->left == NULL && pos->right != NULL) || (pos->right == NULL && pos->left != NULL)){
    if(pos == last->left){
      if(pos->right == NULL)
	last->left = pos->left;
      else if(pos->left == NULL)
	last->left = pos->right;
    }
    else if(pos == last->right){
      if(pos->right == NULL)
	last->right = pos->left;
      else if(pos->left == NULL)
	last->right = pos->right;
    }
    delete pos;
  }

  //Remove when have 2 child
  else if(pos->left != NULL && pos->right != NULL){
    //Replace the Node to be removed with the largest value of the left branch
    Node<T>* temp = pos->left;
    while(temp->right != NULL){
      temp = temp->right;
    }
    T storage  = temp->data;
    Remove(temp->data);
    pos->data = storage;
  }
  
}

template <typename T>
bool BST<T>::ElementExists(T input){
  Node<T>* pos = root;
  while(pos != NULL){
    if(input < pos->data){
      std::cout << pos->data << " -Left" << std::endl;
      pos = pos->left;
    }
    else if(input > pos->data){
      std::cout << pos->data << " -Right" <<  std::endl;
      pos = pos->right;
    }
    else{
      break;
    }
  }

  if(pos == NULL)
    return false;
  else
    return true;
}

template <typename T>
Node<T>* BST<T>::Find(T input){
  Node<T>* pos = root;
  while(pos != NULL){
    if(input < pos->data){
      pos = pos->left;
    }
    else if(input > pos->data){
      pos = pos->right;
    }
    else{
      return pos;
    }
  }

  return pos;
}

template <typename T>
T* BST<T>::ToArray(){
  int size = CountRecur(root);
  T* arr = new T[size];
  ToArrayRecur(root, arr);

  return arr;
}

//Recursive method to assemble the array that ToArray returns
template <typename T>
void BST<T>::ToArrayRecur(Node<T>* treeRoot, T arr[]){
  static int pos = 0;
  if(treeRoot == NULL)
    return;

  //In Order Travel
  ToArrayRecur(treeRoot->left, arr);
  arr[pos] = treeRoot->data;
  pos++;
  ToArrayRecur(treeRoot->right, arr);
}

template <typename T>
int BST<T>::Count(){
  return CountRecur(root);
}

//Recursive Count() Helper Method
template <typename T>
int BST<T>::CountRecur(Node<T>* treeRoot){
  if(treeRoot == NULL){
    return 0;
  }
  else{
    return 1 + CountRecur(treeRoot->left) + CountRecur(treeRoot->right);
  }
}

template <typename T>
void BST<T>::Empty(){
  delete root;
}

#endif
