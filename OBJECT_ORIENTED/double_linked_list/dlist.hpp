//-----------------------------------------------------------------------------
class node {
  public:
    ListSegment value;  // value stored in the node 
    node* next;         // pointer to next node 
    node* prev;         // pointer to previous node 
};

class dlist {
  public:
    node* front;  // pointer to front of list   
    node* back;   // pointer to back of list  

    dlist() {
      front = NULL;
      back = NULL;
    }

    node* insertFront(ListSegment value);             
    node* insertBack(ListSegment value);
    node* removeFront();
    node* removeBack();
    node* insertBefore(ListSegment value, node* nodeB);
    node* insertAfter(ListSegment value, node* nodeA);
    node* removeBefore(node* nodeB);
    node* removeAfter(node* nodeA);
    node* removeNode(node* newNode);
};

// insert a node before nodeB
node* dlist::insertBefore(ListSegment value, node* nodeB) {
  node* newNode;
  newNode = new node();
  newNode->prev = nodeB->prev;
  newNode->next = nodeB;
  newNode->value = value; 
  if(nodeB->prev == NULL) {
    this->front = newNode; 
  }
  nodeB->prev = newNode;
  return newNode;
}

// insert a node before the front node 
node* dlist::insertFront(ListSegment value) {
  node* newNode;
  if (this->front == NULL) {
    newNode = new node();
    this->front = newNode;
    this->back = newNode;
    newNode->prev = NULL;
    newNode->next = NULL;
    newNode->value = value;
  } else {
    insertBefore(value, this->front);
  }
  return newNode;
}

// insert a node after nodeB
node* dlist::insertAfter(ListSegment value, node* nodeB) {
  node* newNode;
  newNode = new node();
  newNode->next = nodeB->next ;
  newNode->prev  = nodeB;
  newNode->value = value;

  if (nodeB->next == NULL) {
    this->back = newNode; 
  }
  nodeB->next = newNode;
  return newNode;
}

// insert a node after the last node 
node* dlist::insertBack(ListSegment value) {          
  if (this->back == NULL) {
    return insertFront(value);
  } else {
    return insertAfter(value, this->back);
  }
}

// remove the front node 
node* dlist::removeFront() {
  return removeNode(this->front);
}

// remove a back node 
node* dlist::removeBack() {
  return removeNode(this->back);
}

// remove before a node 
node* dlist::removeBefore(node* nodeB) {
  if (nodeB->prev == this->front) {
    this->front = nodeB;
    this->front->prev = NULL;
    return front;
  } else {
    return removeNode(nodeB->prev);
  }
}

// remove after a node 
node* dlist::removeAfter(node* nodeA) {
  if (nodeA->next == this->back) {
    this->back = nodeA;
    this->back->next = NULL;
    return back;
  } else {
    return removeNode(nodeA->next);
  }
}

// remove a perticular node 
node* dlist::removeNode(node* nodeToRemove) {
  if (nodeToRemove == this->front) {
    this->front = this->front->next;
    this->front->prev = NULL;
    return front;
  } else if (nodeToRemove == this->back) {
    this->back = this->back->prev;
    this->back->next = NULL;
    return NULL;
  } else {
    nodeToRemove->prev->next = nodeToRemove->next;
    nodeToRemove->next->prev = nodeToRemove->prev;
  }
  return nodeToRemove;
}