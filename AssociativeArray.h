// Programmer: Dhanush Patel
// Programmer's ID: 1553428

#ifndef AssociativeArray_AssociativeArray_H
#define AssociativeArray_AssociativeArray_H

#include <queue>
using namespace std;

template <typename K, typename V>
class AssociativeArray{
  struct Node{
    K key;
    V value;
    Node* next;
  };

  Node* firstNode; // the head pointer
  int siz; // tracking the number of nodes
  Node* dummy;
  
  public:
  AssociativeArray();
  V operator[](const K&) const; // getter
  V& operator[](const K&); // setter
  bool containsKey(const K&) const; // getter
  void deleteKey(const K&); // setter
  int size() const {return siz;}
  void clear();
  queue<K> keys() const;
  ~AssociativeArray(){clear();}
  AssociativeArray<K, V>& operator=(const AssociativeArray<K, V>&);
  AssociativeArray(const AssociativeArray<K, V>&);
};

template <typename K, typename V>
AssociativeArray<K, V>::AssociativeArray(){
  firstNode = 0;
  siz = 0;
}

template <typename K, typename V>
void AssociativeArray<K, V>::clear(){
  while (firstNode){
    Node* p = firstNode;
    firstNode = firstNode->next;
    delete p;
    --siz;
  }
}

template <typename K, typename V>
AssociativeArray<K, V>::AssociativeArray(const AssociativeArray<K, V>& original){
  firstNode = 0;
  Node* lastNode = 0; // temporary tail
  siz = original.siz;
  for (Node* p = original.firstNode; p; p = p->next){
    Node* temp = new Node;
    temp->key = p->key;
    temp->value = p->value;
    temp->next = 0;
    if (lastNode) lastNode->next = temp;
    else firstNode = temp;
    lastNode = temp;
  }
}

template <typename K, typename V>
AssociativeArray<K, V>& AssociativeArray<K, V>::operator=(const AssociativeArray<K, V>& original){
  if (this != &original){
    // deallocate existing list
    while (firstNode){
      Node* p = firstNode->next;
      delete firstNode;
      firstNode = p;
    }

    // build new AssociativeArray
    Node* lastNode = 0; // temporary tail
    for (Node* p = original.firstNode; p; p = p->next){
      Node* temp = new Node;
      temp->key = p->key;
      temp->value = p->value;
      temp->next = 0;
      if (lastNode) lastNode->next = temp;
      else firstNode = temp;
      lastNode = temp;
    }
    siz = original.siz;
  }
  return *this;
}

template <typename K, typename V>
V AssociativeArray<K, V>::operator[](const K& key) const{
  for (Node* p = firstNode; p; p = p->next){
    if (p->key == key){
      return p->value;
    }
  }
  return dummy->value;
}

template <typename K, typename V>
V& AssociativeArray<K, V>::operator[](const K& key){
  
  for (Node* p = firstNode; p; p = p->next){
    if (p->key == key){
      return p->value;
    }
  }
  ++siz;
  Node* temp = new Node;
  temp->key = key;
  temp->value = V();
  temp->next = firstNode;
  firstNode = temp;
  return firstNode->value;
}

template <typename K, typename V>
void AssociativeArray<K, V>::deleteKey(const K& key){
  // find the matching node
  Node* p, *prev; // declare above loop so that it survives below the loop
  for (p = firstNode, prev = 0; p; prev = p, p = p->next){
    if (p->key == key){
      break;
    }
  }

  // if found (that is, p did not run off the end of the list)
  if (p){
    --siz;
    if (prev) prev->next = p->next; // skips over the node at p
    else firstNode = p->next; // there's a new head, possibly zero
    delete p; // we're done with this node
  }
}

template <typename K, typename V>
bool AssociativeArray<K, V>::containsKey(const K& key) const{
  // find the matching node
  Node* p; // declare above loop so that it survives below the loop
  for (p = firstNode; p; p = p->next){
    if (p->key == key){
      return true;
    }
  }

  // if found (that is, p did not run off the end of the list)
  return false;
}

template <typename K, typename V>
queue<K> AssociativeArray<K, V>::keys() const{
  queue<K> retQ;
  Node* p; // declare above loop so that it survives below the loop
  for (p = firstNode; p; p = p->next){
    retQ.push(p->key);
  }
  return retQ;
}

#endif //AssociativeArray_AssociativeArray_H