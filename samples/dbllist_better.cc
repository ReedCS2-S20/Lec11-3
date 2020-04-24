#include <iostream>
#include <memory>

class dnode {
public:
  int data;
  std::shared_ptr<dnode> next;
  std::shared_ptr<dnode> prev;
  dnode(int value) : data {value}, next {nullptr}, prev {nullptr} { }
  ~dnode(void) {
    std::cout << "'Bye!' says " << this << " holding " << data << std::endl;
  }
};

class dbllist {
private:
  std::shared_ptr<dnode> first;
  std::shared_ptr<dnode> last;
public:
  dbllist(void) : first {nullptr}, last {nullptr} { }
  ~dbllist(void) {
    for (std::shared_ptr<dnode> current = first; 
	 current != nullptr;
	 current = current->next) {
      current->prev = nullptr;
    }
  }

  void prepend(int value) {
    std::shared_ptr<dnode> newNode {new dnode {value}};
    newNode->next = first;
    if (first == nullptr) {
      last = newNode;
    } else {
      first->prev = newNode;
    }
    first = newNode;
  }  

  void append(int value) {
    std::shared_ptr<dnode> newNode {new dnode {value}};
    newNode->prev = last;
    if (last == nullptr) {
      first = newNode;
    } else {
      last->next = newNode;
    }
    last = newNode;
  }

  void remove(int value) {
    std::shared_ptr<dnode> current {first};
    while (current != nullptr && current->data != value) {
      current = current->next;
    }
    if (current != nullptr) {
      std::shared_ptr<dnode> prev = current->prev;
      std::shared_ptr<dnode> next = current->next;
      if (prev == nullptr) {
	first = next;
      } else {
	prev->next = next;
      }
      if (next == nullptr) {
	last = prev;
      } else {
	next->prev = prev;
      }
    }
  }      

  void output(void) {
    std::shared_ptr<dnode> current = first;
    while (current != nullptr) {
      std::cout << current->data << " ";
      current = current->next;
    }
    std::cout << std::endl;
  }
};

int main(void) {
  dbllist L {};
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
    
