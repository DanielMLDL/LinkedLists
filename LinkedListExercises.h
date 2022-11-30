
/**
 * @file LinkedListExercises.h
 * University of Illinois CS 400, MOOC 2, Week 1: Linked List
 * Spring 2019
 *                        STUDENT STARTER FILE
 *
 * @author Eric Huber - University of Illinois staff
 *
**/

#pragma once
#include <iostream>
#include <string>

#include "LinkedList.h"
#define PAUSE printf("Press Enter key to continue..."); fgetc(stdin);

template <typename T>
void LinkedList<T>::insertOrdered(const T& newData) {

    Node* newnode = new Node(newData);

    if (!head_) {
        head_ = newnode;
        tail_ = newnode;
    }

    else if (head_->data >= newnode->data) {
        newnode->next = head_;
        head_->prev = newnode;
        head_ = newnode;
    }

    else if (newnode->data >= tail_->data) {
        tail_->next = newnode;
        newnode->prev = tail_;
        tail_ = newnode;
    }

    else {
        Node* current = head_;
        Node* previousnode = nullptr;
        while (newData > current->data && current != nullptr) {
            current = current->next;
            previousnode = current->prev;
        }
        if (newData <= current->data) {
            previousnode->next = newnode;
            newnode->prev = previousnode;
            newnode->next = current;
            current->prev = newnode;
        }
    }
    size_++;
}


template <typename T>
LinkedList<T> LinkedList<T>::merge(const LinkedList<T>& other) const {


  LinkedList<T> left = *this;
  LinkedList<T> right = other;

  LinkedList<T> merged;

  while (!left.empty() && !right.empty()) {
      if (left.front() <= right.front()) {
          merged.pushBack(left.front());
          left.popFront();
      }
      else {
          merged.pushBack(right.front());
          right.popFront();
      }
  }
  if (left.empty()) {
     while (!right.empty()) {
            merged.pushBack(right.front());
            right.popFront();
          }
      }
  if (right.empty()) {
     while (!left.empty()) {
            merged.pushBack(left.front());
            left.popFront();
          }
      }

  return merged;
}
