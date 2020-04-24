#include <iostream>
#include <memory>

class dnode {
public:
  int data;
  std::shared_ptr<dnode> next;
  std::weak_ptr<dnode> prev;
  dnode(int value) : data {value}, next {nullptr}, prev {} { }
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
      if (current == first) {
	first = current->next;
      } else {
	std::shared_ptr<dnode> prev {current->prev};
	prev->next = current->next;
      }
      if (current == last) {
	last = std::shared_ptr<dnode>{current->prev};
      } else {
	std::shared_ptr<dnode> next {current->next};
	next->prev = current->prev;
      }
    }
  }      

  void output(void) {
    std::shared_ptr<dnode> current {first};
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
  std::cout << "prepend 10" << std::endl;
  L.prepend(10);
  L.output();
  std::cout << "prepend 7" << std::endl;
  L.prepend(7);
  L.output();
  std::cout << "append 25" << std::endl;
  L.append(25);
  L.output();
  std::cout << "append 37" << std::endl;
  L.append(37);
  L.output();
  std::cout << "remove 25" << std::endl;
  L.remove(25);
  L.output();
  std::cout << "remove 7" << std::endl;
  L.remove(7);
  L.output();
  std::cout << "remove 10" << std::endl;
  L.remove(10);
  L.output();
  std::cout << "append 85" << std::endl;
  L.append(85);
  std::cout << "prepend 1" << std::endl;
  L.prepend(1);
}
    
