export module Class;
import std;

template<typename T>
struct Node
{
    T data;
    Node* prev;
    Node* next;
};
export template<typename T>
class LinkedList
{
private:
    Node<T>* _head = nullptr;
    int _size = 0;
    int checkSize(int size) {
    if (size < 0) throw std::invalid_argument("size must be non-negative");
    return size;
}
public:
    LinkedList() = default;


    LinkedList(int size, T min, T max) requires std::integral<T>{
        _size = checkSize(size);
        if (_size == 0)return;
        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<T> dist(min, max);
        Node<T>* cur = new Node<T>{dist(gen), nullptr, nullptr};
        _head = cur;
        for(int i = 0; i < _size - 1; i++){
            Node<T>* previous = cur; 
            cur -> next = new Node<T>{dist(gen), nullptr, nullptr};
            cur = cur -> next;
            cur -> prev = previous;
        }
        cur -> next = _head;
        _head -> prev = cur;
    }

    LinkedList(int size, T min, T max) requires std::floating_point<T>{
        _size = checkSize(size);
        if (_size == 0)return;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<T> dist(min, max);
        Node<T>* cur = new Node<T>{dist(gen), nullptr, nullptr};
        _head = cur;
        for(int i = 0; i < _size - 1; i++){
            Node<T>* previous = cur; 
            cur -> next = new Node<T>{dist(gen), nullptr, nullptr};
            cur = cur -> next;
            cur -> prev = previous;
        }
        cur -> next = _head;
        _head -> prev = cur;
    }


    LinkedList(const LinkedList& other):_head(nullptr), _size(0){
        if (!other._head) return;
        Node<T>* src = other._head;
        _head = new Node<T>{src->data, nullptr, nullptr};
        Node<T>* dst = _head;
        src = src->next;
        while (src != other._head) {
            Node<T>* n = new Node<T>{src->data, dst, nullptr};
            dst->next = n;
            dst = n;
            src = src->next;
        }
        dst->next = _head;
        _head->prev = dst;
        _size = other._size;
    }


    ~LinkedList() {
        if (!_head) return;
        Node<T>* cur = _head->next;
        while (cur != _head) {
            Node<T>* next = cur->next;
            delete cur;
            cur = next;
        }
        delete _head;
        _head = nullptr;
        _size = 0;
}
    LinkedList operator=(const LinkedList& other){
        if (this == &other) return *this;
        this->~LinkedList();
        new (this) LinkedList(other);
        return *this;
    }

    LinkedList& push_tail(const T data){
        if(_head == nullptr){
            _head = new Node<T>{data, nullptr, nullptr};
            _size++;
            return *this;
        }
        Node<T>* previos = _head -> prev;
        Node<T>* tail = new Node<T>{data, previos, _head};
        _head -> prev = tail;
        previos -> next = tail;
        _size++;
        return *this;
    }
    LinkedList& push_tail(const LinkedList& other) {
        if (other._head == nullptr || other._size == 0) {
            return *this;
            }
        LinkedList Other(other);
        if (_head == nullptr) {
            _head = Other._head;
            _size = Other._size;
            Other._head = nullptr;
            Other._size = 0;
            return *this;
        }
        Node<T>* this_tail = _head->prev;
        Node<T>* Other_head = Other._head;
        Node<T>* Other_tail = Other_head->prev;
        this_tail->next = Other_head;
        Other_head->prev = this_tail;
        Other_tail->next = _head;
        _head->prev = Other_tail;
        _size += Other._size;
        Other._head = nullptr;
        Other._size = 0;
        return *this;
    }
    LinkedList& push_head(const T data){
        if(_head == nullptr){
            _head = new Node<T>{data, nullptr, nullptr};
            _size++;
            return *this;
        }
        Node<T>* copy = _head;
        Node<T>* last = copy -> prev;
        _head = new Node<T>{data, copy -> prev, copy};
        copy -> prev = _head;
        last -> next = _head;
        _size++;
        return *this;
    }
    LinkedList& push_head(const LinkedList& other){
        if (other._head == nullptr || other._size == 0) {
            return *this;
            }
        LinkedList Other(other);
        if (_head == nullptr) {
            _head = Other._head;
            _size = Other._size;
            Other._head = nullptr;
            Other._size = 0;
            return *this;
        }
        Node<T>* copy = _head;
        _head = Other._head;
        Node<T>* Other_prev = _head -> prev;
        Node<T>* xa_next = copy -> prev;
        _head -> prev = xa_next;
        copy -> prev = Other_prev;
        Other_prev -> next = copy;
        xa_next -> next = _head;
        _size += Other._size;
        Other._head = nullptr;
        Other._size = 0;
        return *this;
    }

    LinkedList& pop_head(){
        if(_size == 1){
            delete _head;
            _head = nullptr;
            _size--;
            return *this;
        }
        Node<T>* last = _head -> prev;
        Node<T>* second = _head -> next;
        delete _head;
        _head = second;
        _head -> prev = last;
        last -> next = _head;
        _size--;
        return *this;
    }

    LinkedList& pop_tail(){
        if(_size == 1){
            delete _head;
            _head = nullptr;
            _size--;
            return *this;
        }
        Node<T>* tail = _head -> prev;
        Node<T>* last = tail -> prev;
        delete tail;
        _head -> prev = last;
        last -> next = _head;
        _size--;
        return *this;
    }

    LinkedList& delete_note(T key){
        if(_head == nullptr)return *this;

        Node<T>* cur = _head;
        while(cur -> data == key){
            this -> pop_head();
            if(_head == nullptr)return *this;
            cur = _head;
        }
        cur = cur -> next;
        while (cur != _head)
        {
            Node<T>* next = cur -> next;
            if(cur -> data == key){
                cur -> next -> prev = cur -> prev;
                cur -> prev -> next = cur -> next;
                delete cur; 
                _size--;
            }
            cur = next;
        }
        
        return *this;
    }

    T& operator[](const int& index){
        int count_size = std::abs(index)/_size;
        int count = std::abs(index)-count_size*_size;
        if(count == 0)return _head -> data;
        Node<T>* cur = _head;
        if(index > 0){
            for(int i = 0; i < count; ++i)cur = cur -> next;
        }
        else{
            for(int i = 0; i < count; ++i)cur = cur -> prev;
        }
        return cur -> data;
    }

    const T& operator[](const int& index) const{
        int count_size = std::abs(index)/_size;
        int count = std::abs(index)-count_size*_size;
        if(count == 0)return _head -> data;
        Node<T>* cur = _head;
        if(index > 0){
            for(int i = 0; i < count; ++i)cur = cur -> next;
        }
        else{
            for(int i = 0; i < count; ++i)cur = cur -> prev;
        }
        return cur -> data;
    }

    friend std::ostream& operator<<(std::ostream& os, const LinkedList& list){
        if(list._head == nullptr){
            os << "[]";
            return os;
        }
        os << "[";

        Node<T>* cur = list._head;
        do{
            os << cur -> data;
            if(cur -> next != list._head) os << ", ";
            cur = cur -> next;
        }while(cur != list._head);

        os << "]";
        return os;
    }
};
