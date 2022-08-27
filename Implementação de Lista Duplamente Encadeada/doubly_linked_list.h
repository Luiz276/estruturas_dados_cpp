//! Copyright [2022] <Luiz Maurício do Valle Pereira>
namespace structures {

template<typename T>
class DoublyLinkedList {
 public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    void clear();

    void push_back(const T& data);  // insere no fim
    void push_front(const T& data);  // insere no início
    void insert(const T& data, std::size_t index);  // insere na posição
    void insert_sorted(const T& data);  // insere em ordem

    T pop(std::size_t index);  // retira da posição
    T pop_back();  // retira do fim
    T pop_front();  // retira do início
    void remove(const T& data);  // retira específico

    bool empty() const;  // lista vazia
    bool contains(const T& data) const;  // contém

    T& at(std::size_t index);  // acesso a um elemento (checando limites)
    const T& at(std::size_t index) const;  // getter constante a um elemento

    std::size_t find(const T& data) const;  // posição de um dado
    std::size_t size() const;  // tamanho

 private:
    class Node {
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        Node(const T& data, Node* prev, Node* next):
            data_{data},
            next_{next},
            prev_{prev}
        {}

        T& data() {  // getter: dado
            return data_;
        }

        const T& data() const {  // getter const: dado
            return data_;
        }

        Node* prev() {
            return prev_;
        }

        const Node* prev() const {
            return prev_;
        }

        void prev(Node* node) {
            prev_ = node;
        }

         Node* next() {  // getter: próximo
            return next_;
        }

        const Node* next() const {  // getter const: próximo
            return next_;
        }

        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* prev_;
        Node* next_;
    };

    Node* position(std::size_t index) {
        Node* p{nullptr};
        if (index < size_) {
            p = head;
            for (int i = 1u; i <= static_cast<int>(index); i++) {
                p = p->next();
            }
        } else {
            throw std::out_of_range("Index de posição inválido");
        }
        return p;
    }

    Node* head;  // primeiro da lista
    Node* tail;  // ultimo da lista
    std::size_t size_;
};

}  //  namespace structures

template<typename T>
structures::DoublyLinkedList<T>::DoublyLinkedList() {
    head = nullptr;
    tail = nullptr;
    size_ = 0;
}

template<typename T>
structures::DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}
template<typename T>
void structures::DoublyLinkedList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}
template<typename T>
void structures::DoublyLinkedList<T>::push_back(const T& data) {
    Node* novo = new Node(data);
    if (novo == nullptr) {
        throw std::out_of_range("Stack Overflow, lista cheia");
    } else if (empty()) {
        head = novo;
        novo->next(nullptr);
        novo->prev(nullptr);
        tail = novo;
    } else {
        novo->next(nullptr);
        novo->prev(position(size()-1));
        position(size()-1)->next(novo);
        tail = novo;
    }
    size_++;
}

template<typename T>
void structures::DoublyLinkedList<T>::push_front(const T& data) {
    Node *novo = new Node(data);
    if (novo == nullptr) {
        throw std::out_of_range("Stack Overflow, lista cheia");
    } else if (empty()) {
        head = novo;
        tail = novo;
        novo->next(nullptr);
    } else {
        novo->next(head);
        head->prev(novo);
        head = novo;
        novo->prev(nullptr);
    }
    size_++;
}

template<typename T>
void structures::DoublyLinkedList<T>::insert(const T& data, std::size_t index) {
    Node *novo = new Node(data);
    if (novo == nullptr) {
        throw std::out_of_range("Stack Overflow, lista cheia");
    } else if (static_cast<int>(index) == 0) {
        push_front(data);
    } else if (index == size()) {
        push_back(data);
    } else {
        Node* p = position(index-1);
        novo->next(p->next());
        novo->prev(p);
        p->next()->prev(novo);
        p->next(novo);
        size_++;
    }
}

template<typename T>
void structures::DoublyLinkedList<T>::insert_sorted(const T& data) {
    if (empty()) {
        push_front(data);
    } else {
        Node *atual;
        int pos = 0;
        atual = head;
        while (data > atual->data()) {
            atual = atual->next();
            ++pos;
            if (pos > static_cast<int>(size())-1) {
                break;
            }
        }
        insert(data, static_cast<std::size_t>(pos));
    }
}

template<typename T>
T structures::DoublyLinkedList<T>::pop(std::size_t index) {
    if (empty() || index >= size_) {
        throw std::out_of_range("Lista vazia");
    } else if (size() == 1 || index == 0) {
        return (pop_front());
    } else if (size()-1 == index) {
        return pop_back();
    } else {
    Node* p = position(index-1);
    Node* t = p->next();
    p->next(t->next());
    t->next()->prev(p);
    T aux = t->data();
    size_--;
    delete t;
    return aux;
    }
}

template<typename T>
T structures::DoublyLinkedList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("Lista vazia");
    } else if (size() == 1) {
        return (pop_front());
    } else {
        Node* p;
        p = position(size_ - 2);
        tail = p;
        T aux = (p->next())->data();
        delete p->next();
        p->next(nullptr);
        size_--;
        return aux;
    }
}

template<typename T>
T structures::DoublyLinkedList<T>::pop_front() {
    if (empty() || static_cast<int>(size()) < 1) {
        throw std::out_of_range("lista vazia");
    } else if (static_cast<int>(size()) == 1) {
        // caso tenha apenas um
        Node* p = head;
        head = p->next();
        T aux = p->data();
        size_--;
        delete p;
        return aux;
    } else {
        Node* p = head;
        head = p->next();
        head->prev(nullptr);
        T aux = p->data();
        size_--;
        delete p;
        return aux;
    }
}

template<typename T>
void structures::DoublyLinkedList<T>::remove(const T& data) {
    int pos = find(data);
    pop(pos);
}

template<typename T>
bool structures::DoublyLinkedList<T>::empty() const {
    return (size() == 0);
}

template<typename T>
bool structures::DoublyLinkedList<T>::contains(const T& data) const {
    return(size() != find(data));
}

template<typename T>
T& structures::DoublyLinkedList<T>::at(std::size_t index) {
    return (position(index)->data());
}

template<typename T>
const T& structures::DoublyLinkedList<T>::at(std::size_t index) const {
    return (position(index)->data());
}

template<typename T>
std::size_t structures::DoublyLinkedList<T>::find(const T& data) const {
    Node* p = head;
    int i = 0;
    while (p != nullptr && p->data() != data) {
        i++;
        p = p->next();
    }
    return (static_cast<std::size_t>(i));
}

template<typename T>
std::size_t structures::DoublyLinkedList<T>::size() const {
    return (size_);
}
