#include "list.h"

#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

// Node constructor
Node::Node(int val) : value(val), next(nullptr) {}

// List constructor
List::List() : head(nullptr) {}

// List destructor
List::~List() {
  while (head != nullptr) {
    Node* temp = head;
    head = head->next;
    delete temp;
  }
}

// Insert method with global lock
void List::insert(int value) {
  std::lock_guard<std::mutex> guard(listLock);  // Global lock
  Node* newNode = new Node(value);

  if (!head || value < head->value) {
    newNode->next = head;
    head = newNode;
  } else {
    Node* current = head;
    while (current->next && current->next->value < value) {
      current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
  }
}

// Insert method with fine-grained lock
void List::insertFineGrained(int value) {
  Node* newNode = new Node(value);

  if (!head || value < head->value) {
    std::lock_guard<std::mutex> headGuard(head->nodeLock);  // Lock head node
    newNode->next = head;
    head = newNode;
    return;
  }

  Node* prev = head;
  Node* current = prev->next;

  prev->nodeLock.lock();  // Lock the first node (head)

  while (current) {
    current->nodeLock.lock();  // Lock the current node

    if (current->value >= value) {
      newNode->next = current;
      prev->next = newNode;

      current->nodeLock.unlock();  // Unlock the current node
      prev->nodeLock.unlock();     // Unlock the previous node
      return;
    }

    prev->nodeLock.unlock();  // Unlock the previous node
    prev = current;
    current = current->next;
  }

  // Insert at the end of the list if current is null
  prev->next = newNode;
  prev->nodeLock.unlock();  // Unlock the last node
}

// Print the list
void List::printList() {
  Node* temp = head;
  while (temp != nullptr) {
    std::cout << temp->value << " ";
    temp = temp->next;
  }
  std::cout << std::endl;
}
