/* c++ template class to implement disjoint sets with lists */
#include <iostream>
#include <element.h>

template<class T>
class Set {
private:
    Element<T> *list_head;  // pointer to the head of a list of elements
    Element<T> *list_tail;  // and to its tail as well
    int size;               // set size, updated when sets are merged
public:
    //constructor for an empty set
    Set<T>(void) {list_head = nullptr;list_tail = nullptr; size = 0;}
    
    // getters & setters
    Element<T>* get_head(void) {return list_head;}
    Element<T>* get_tail(void) {return list_tail;}
    int get_size(void) {return size;}
    void set_head(Element<T> *new_set_head) {list_head = new_set_head;}
    void set_tail(Element<T> *new_set_tail) {list_tail = new_set_tail;}
    void set_size(const int new_size) {size = new_size;}
    // initializes the set with the single element init
    void make_set(T init);
    // adds element el to the set
    void add_element(T el);
    // prints all the elements in the set
    void print_set(void);
    // returns whether the set is empty
    bool empty(void) {return list_head == nullptr;}
    // if it finds element el in set, returns list head
    Element<T>* find(T el);
};

template<class T>
void Set<T>::make_set(T init) {
    // make a new element
    list_head = new Element<T>(init);
    list_head->set_top(list_head);
    list_tail = list_head;
    size = 1;
}
template<class T>
void Set<T>::add_element(T el) {
    Element<T> *new_elem = new Element<T>(el);
    // adds new_elem either to a list already initialized or an empty list
    if(list_head == nullptr) {
        list_head = new_elem;
        new_elem->set_top(list_head);
        list_tail = new_elem;
    }
    else {
        new_elem->set_top(list_head);
        list_tail->set_next(new_elem);
        list_tail = new_elem;
    }
}
template<class T>
void Set<T>::print_set(void) {
    Element<T> *curr = list_head;
    std::cout << "Set " << this << ": ";
    while(curr != nullptr) {
        std::cout << curr->get_element() << " ";
        curr = curr->get_next();
    }
    std::cout << std::endl;
}
template<class T>
Element<T>* Set<T>::find(T el) {
    Element<T> *curr = list_head;
    while(curr != nullptr && curr->get_element() != el) {
        curr = curr->get_next();
    }
    if(curr == nullptr) {
        return nullptr;
    }
    else {
        return list_head;
    }
}

/* 
 * This is a standalone function to merge two sets into one
 * the shortest is appended to the longest for performace issues
 */
template<class T>
void merge_sets(Set<T> &a, Set<T> &b) {
    // if set a is shorter than b, then exchange them
    if(a.get_size() < b.get_size()) {
            merge_sets(b, a);
    }
    else {
        // now append each element to list pointed by a
        while(b.get_head() != nullptr) {
            // set a's tail's next to be b's head
            a.get_tail()->set_next(b.get_head());
            // set a's tail to b's head node
            a.set_tail(b.get_head());
            // and b's head node's top to a's head
            b.get_head()->set_top(a.get_head());
            // then advance b's head node
            b.set_head(b.get_head()->get_next());
        }
        // the the size as the sum of sizes for a and set b's to 0
        a.set_size(a.get_size() + b.get_size());
        b.set_size(0);
    }
}
