
/**
 * @file LinkedList.h
 * University of Illinois CS 400, MOOC 2, Week 1: Linked Lists
 *
 * @author Eric Huber
 *
**/

#pragma once

#include <stdexcept> // for std::runtime_error
#include <iostream> // for std::cerr, std::cout
#include <ostream> // for std::ostream

template <typename T>
class LinkedList {
public:

  // Node type that is particular to the LinkedList<T> type
  class Node {
  public:
    // The next node in the list, or nullptr if this is the last node.
    Node* next;
    // The previous node in the list, or nullptr if this is the first node.
    Node* prev;
    // An actual data item that this node contains.
    T data;
    
    // Default constructor: This lets data be constructed by
    // the default constructor of the T type.
    Node() : next(nullptr), prev(nullptr) {}

    // Argument constructor: Specifies the data that should be copied into
    // the T data member variable.
    Node(const T& dataArg) : next(nullptr), prev(nullptr), data(dataArg) {}

    Node(const Node& other) : next(other.next), prev(other.prev),
      data(other.data) {}

    // Copy assignment operator: Please see the note above.
    Node& operator=(const Node& other) {
      next = other.next;
      prev = other.prev;
      data = other.data;
      return *this;
    }

    ~Node() {}

  };

private:

  Node* head_;
 
  Node* tail_;
 
  int size_;

public:

  static constexpr char LIST_GENERAL_BUG_MESSAGE[] = "[Error] Probable causes: wrong head_ or tail_ pointer, or some next or prev pointer not updated, or wrong size_";

  
  Node* getHeadPtr() { return head_; }
  Node* getTailPtr() { return tail_; }

  int size() const { return size_; }

  bool empty() const { return !head_; }

  T& front(){
    if (!head_) {
      throw std::runtime_error("front() called on empty LinkedList");
    }
    else {
      return head_->data;
    }
  }

  const T& front() const {
    if (!head_) {
      throw std::runtime_error("front() called on empty LinkedList");
    }
    else {
      return head_->data;
    }
  }

  T& back(){
    if (!tail_) {
      throw std::runtime_error("back() called on empty LinkedList");
    }
    else {
      return tail_->data;
    }
  }

  const T& back() const {
    if (!tail_) {
      throw std::runtime_error("back() called on empty LinkedList");
    }
    else {
      return tail_->data;
    }
  }

  void pushFront(const T& newData);

  void pushBack(const T& newData);

  void popFront();

  void popBack();
  
  
  void clear() {
    
    while (head_) {
      popBack();
    }

    if (0 != size_) throw std::runtime_error(std::string("Error in clear: ") + LIST_GENERAL_BUG_MESSAGE);
  }

  
  bool equals(const LinkedList<T>& other) const;
  bool operator==(const LinkedList<T>& other) const {
    return equals(other);
  }
  bool operator!=(const LinkedList<T>& other) const {
    return !equals(other);
  }

  
  std::ostream& print(std::ostream& os) const;

  void insertOrdered(const T& newData);

  bool isSorted() const;

  LinkedList<T> insertionSort() const;
 
  LinkedList<LinkedList<T>> splitHalves() const;
  
  LinkedList<LinkedList<T>> explode() const;
  
  LinkedList<T> merge(const LinkedList<T>& other) const;
  
  LinkedList<T> mergeSort() const;
  
  LinkedList<T> mergeSortRecursive() const;

  LinkedList<T> mergeSortIterative() const;

  LinkedList() : head_(nullptr), tail_(nullptr), size_(0) {}
  
  LinkedList<T>& operator=(const LinkedList<T>& other) {
 
    clear();

    const Node* cur = other.head_;
    while (cur) {
      
      pushBack(cur->data);

      cur = cur->next;
    }

    return *this;
  }
  
  LinkedList(const LinkedList<T>& other) : LinkedList() {
    *this = other;
  }

  ~LinkedList() {
    clear();
  }

  bool assertCorrectSize() const;
  
  bool assertPrevLinks() const;

};

template <typename T>
std::ostream& operator<<(std::ostream& os, const LinkedList<T>& list) {
  return list.print(os);
}


template <typename T>
constexpr char LinkedList<T>::LIST_GENERAL_BUG_MESSAGE[];

template <typename T>
void LinkedList<T>::pushFront(const T& newData) {

  
  Node* newNode = new Node(newData);

  if (!head_) {
    
    head_ = newNode;
    tail_ = newNode;
  }
  else {
   
    Node* oldHead = head_;
    oldHead->prev = newNode;
    newNode->next = oldHead;
    head_ = newNode;
  }

  
  size_++;
}

template <typename T>
void LinkedList<T>::pushBack(const T& newData) {

  
  Node* newNode = new Node(newData);

  if (!head_) {
   
    head_ = newNode;
    tail_ = newNode;
  }
  else {
    
    Node* oldTail = tail_;
    oldTail->next = newNode;
    newNode->prev = oldTail;
    tail_ = newNode;
  }

  
  size_++;
}


template <typename T>
void LinkedList<T>::popFront() {

  
  if (!head_) return;

  if (!head_->next) {

    delete head_;
   
    head_ = nullptr;
    tail_ = nullptr;
    
    size_--;
    if (0 != size_) throw std::runtime_error(std::string("Error in popFront: ") + LIST_GENERAL_BUG_MESSAGE);
    return;
  }

  Node* oldHead = head_;

  head_ = head_->next;

  head_->prev = nullptr;
 
  delete oldHead;

  oldHead = nullptr;

 
  size_--;
}


template <typename T>
void LinkedList<T>::popBack() {

 
  if (!head_) return;

  
  if (!tail_->prev) {
    
    delete tail_;
    
    head_ = nullptr;
    tail_ = nullptr;
    
    size_--;
    if (0 != size_) throw std::runtime_error(std::string("Error in popBack: ") + LIST_GENERAL_BUG_MESSAGE);
    return;
  }

  Node* oldTail = tail_;
  
  tail_ = tail_->prev;
  
  tail_->next = nullptr;
  
  delete oldTail;

  oldTail = nullptr;

  
  size_--;
}


template <typename T>
bool LinkedList<T>::isSorted() const {
 
  if (size_ < 2) return true;

  if (!head_) throw std::runtime_error(std::string("Error in isSorted: ") + LIST_GENERAL_BUG_MESSAGE);

  const Node* prev = nullptr;
  const Node* cur = head_;
  while (cur->next) {

    prev = cur;
    cur = cur->next;
    if (!(prev->data <= cur->data)) {
      return false;
    }
  }
  return true;
}

template <typename T>
bool LinkedList<T>::equals(const LinkedList<T>& other) const {

  if (size_ != other.size_) {
    return false;
  }

  const Node* thisCur = head_;
  const Node* otherCur = other.head_;

  while (thisCur) {
    if (!otherCur) {
      throw std::runtime_error(std::string("Error in equals: ") + "otherCur missing a node or wrong item count");
    }
    if (thisCur->data != otherCur->data) {
      return false;
    }
    thisCur = thisCur->next;
    otherCur = otherCur->next;
  }

  return true;
}

template <typename T>
LinkedList<T> LinkedList<T>::insertionSort() const {

  LinkedList<T> result;

  const Node* cur = head_;
  while (cur) {
    result.insertOrdered(cur->data);
    cur = cur->next;
  }

  return result;
}

template <typename T>
std::ostream& LinkedList<T>::print(std::ostream& os) const {
  os << "[";
  Node* cur = head_;
  while (cur) {
    os << "(" << cur->data << ")";
    cur = cur->next;
  }

  os << "]";

  return os;
}

template <typename T>
LinkedList<LinkedList<T>> LinkedList<T>::splitHalves() const {

  LinkedList<LinkedList<T>> halves;
  LinkedList<T> leftHalf = *this;
  LinkedList<T> rightHalf;

  if (size_ < 2) {
    halves.pushBack(leftHalf);
    halves.pushBack(rightHalf);
    return halves;
  }

  int rightHalfLength = size_ / 2;

  for (int i=0; i<rightHalfLength; i++) {

    T dataToCopy = leftHalf.back();
    rightHalf.pushFront(dataToCopy);
    leftHalf.popBack();
  }

  halves.pushBack(leftHalf);
  halves.pushBack(rightHalf);

  return halves;
}
template <typename T>
LinkedList<LinkedList<T>> LinkedList<T>::explode() const {

  LinkedList<T> workingCopy = *this;

  LinkedList< LinkedList<T> > lists;

  while (!workingCopy.empty()) {
    LinkedList<T> singletonList;
    singletonList.pushBack(workingCopy.front());
    workingCopy.popFront();
    lists.pushBack(singletonList);
  }

  return lists;
}

template <typename T>
LinkedList<T> LinkedList<T>::mergeSortRecursive() const {

  if (size_ < 2) {
    return *this;
  }

  LinkedList<LinkedList<T>> halves = splitHalves();
  LinkedList<T>& left = halves.front();
  LinkedList<T>& right = halves.back();

  left = left.mergeSortRecursive();
  right = right.mergeSortRecursive();

  return left.merge(right);
}

template <typename T>
LinkedList<T> LinkedList<T>::mergeSortIterative() const {

  if (size_ < 2) {
    return *this;
  }

  LinkedList< LinkedList<T> > workQueue = explode();

  while(workQueue.size() > 1) {
    LinkedList<T> left = workQueue.front();
    workQueue.popFront();
    LinkedList<T> right = workQueue.front();
    workQueue.popFront();
    LinkedList<T> merged = left.merge(right);
    workQueue.pushBack(merged);
  }
  return workQueue.front();
}

template <typename T>
LinkedList<T> LinkedList<T>::mergeSort() const {
  return mergeSortRecursive();
}

template <typename T>
bool LinkedList<T>::assertCorrectSize() const {
  int itemCount = 0;
  const Node* cur = head_;
  while (cur) {
    itemCount++;
    cur = cur->next;
  }
  if (itemCount != size_) throw std::runtime_error(std::string("Error in assertCorrectSize: ") + LIST_GENERAL_BUG_MESSAGE);
  else return true;
}

template <typename T>
bool LinkedList<T>::assertPrevLinks() const {

  LinkedList<const Node*> forwardPtrList;
  LinkedList<const Node*> reversePtrList;
  {
    const Node* cur = head_;
    while (cur) {
      forwardPtrList.pushBack(cur);
      cur = cur->next;
    }
  }
  {
    const Node* cur = tail_;
    while (cur) {
      reversePtrList.pushFront(cur);
      cur = cur->prev;
    }
  }

  if (forwardPtrList == reversePtrList) return true;
  else throw std::runtime_error(std::string("Error in assertPrevLinks: ") + LIST_GENERAL_BUG_MESSAGE);
}

#include "LinkedListExercises.h"

