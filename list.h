#ifndef LIST_H
#define LIST_H

#include <mutex>

// Node structure
struct Node {
  int value;
  Node* next;
  std::mutex nodeLock;
  Node(int val);
};

// List class
class List {
  Node* head;           // Head of the list
  std::mutex listLock;  // Mutex for global lock

 public:
  List();   // Constructor
  ~List();  // Destructor

  // Insertion methods
  void insert(int value);             // Insertion with global lock
  void insertFineGrained(int value);  // Insertion with fine-grained lock

  // Utility methods
  void printList();  // Print the contents of the list
  void clear();      // Clear the list
};

#endif
