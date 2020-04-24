#include <iostream>
#include <memory>

class node {
public:
  int data;
  std::shared_ptr<node> next;
  node(int value) : data {value}, next {nullptr} { }
  ~node(void) {
    std::cout << "'Bye!' says " << this << " holding " << data << std::endl;
  }
};

class llist {
private:
  std::shared_ptr<node> first;
  std::shared_ptr<node> last;
public:
  llist(void) : first {nullptr}, last {nullptr} { }

  void prepend(int value) {
    std::shared_ptr<node> newNode {new node {value}};
    newNode->next = first;
    first = newNode;
    if (last == nullptr) {
      last = first;
    }
  }  

  void append(int value) {
    std::shared_ptr<node> newNode {new node {value}};
    if (last == nullptr) {
      last = newNode;
      first = last;
    } else {
      last->next = newNode;
      last = newNode;
    }
  }

  void remove(int value) {
    std::shared_ptr<node> follow {nullptr};
    std::shared_ptr<node> current {first};
    while (current != nullptr && current->data != value) {
      follow = current;
      current = current->next;
    }
    if (current != nullptr) {
      if (follow == nullptr) {
	first = current->next;
	if (current->next == nullptr) {
	  last = first;
	}
      } else {
	follow->next = current->next;
	if (current->next == nullptr) {
	  last = follow;
	}
      }
    }
  }      

  void output(void) {
    std::shared_ptr<node> current = first;
    while (current != nullptr) {
      std::cout << current->data << " ";
      current = current->next;
    }
    std::cout << std::endl;
  }
};

int main(void) {
  llist L {};
  L.output();
  L.prepend(10);
  L.output();
  L.prepend(7);
  L.output();
  L.append(25);
  L.output();
  L.append(37);
  L.output();
  L.remove(25);
  L.output();
  L.remove(7);
  L.output();
  L.remove(10);
  L.output();
  L.append(85);
  L.prepend(1);
}
    
