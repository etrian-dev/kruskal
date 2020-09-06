/* c++ template class to implements nodes of a linked list */

template<class T>
class Element {
private:
    T value;
    Element<T> *next;
    Element<T> *top; // points to the head of the list
public:
    // constructor
    Element<T>(T x);
    
    //getters & setters
    T get_element(void) {return value;}
    Element<T>* get_next(void) {return next;}
    Element<T>* get_top(void) {return top;}
    void set_next(Element<T> *new_next) {next = new_next;}
    void set_top(Element<T> *new_top) {top = new_top;}
};

template<class T>
Element<T>::Element(T x) {
    value = x;
    next = nullptr;
    top = nullptr;
}
