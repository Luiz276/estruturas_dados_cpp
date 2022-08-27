//! Copyright [2022] <Luiz Maurício do Valle Pereira>
namespace structures {

template<typename T>
class DoublyCircularList {
 public:
    DoublyCircularList();
    ~DoublyCircularList();

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

    Node* head;
    std::size_t size_;
};

// implementação

template<typename T>
structures::DoublyCircularList<T>::DoublyCircularList() {
    size_ = 0;
    Node* novo = new Node(0);
    head = novo;
}

template<typename T>
structures::DoublyCircularList<T>::~DoublyCircularList() {
    clear();
}

template<typename T>
void structures::DoublyCircularList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

template<typename T>
void structures::DoublyCircularList<T>::push_back(const T& data) {
    Node* novo = new Node(data);
    if (novo == nullptr) {
        throw std::out_of_range("Stack Overflow, lista cheia");
    } else if (empty()) {
        head->next(novo);
        novo->next(head);
        novo->prev(head);
        head->prev(novo);
    } else {
        head->prev()->next(novo);
        novo->next(head);
        novo->prev(head->prev());
        head->prev(novo);
    }
    size_++;
}

template<typename T>
void structures::DoublyCircularList<T>::push_front(const T& data) {
    Node *novo = new Node(data);
    if (novo == nullptr) {
        throw std::out_of_range("Stack Overflow, lista cheia");
    } else if (empty()) {
        head->next(novo);
        head->prev(novo);
        novo->next(head);
        novo->prev(head);
    } else {
        novo->next(head->next());
        head->next()->prev(novo);
        head->next(novo);
        novo->prev(head);
    }
    size_++;
}

template<typename T>
void structures::DoublyCircularList<T>::insert(const T& data,
                                                std::size_t index) {
    Node *novo = new Node(data);
    if (novo == nullptr || static_cast<int>(index) < 0 || index > size()) {
        throw std::out_of_range("ERRO");
    } else if (empty() || static_cast<int>(index) == 1) {
        push_front(data);
    } else {
        Node* p = head;  // anterior aonde será dado o insert
        for (int i = 0; i < static_cast<int>(index); i++) {
            p = p->next();
        }
        Node* pn = p->next();  // posterior aonde será dado o insert
        novo->next(pn);
        novo->prev(p);
        p->next(novo);
        pn->prev(novo);
    }
    size_++;
}

template<typename T>
void structures::DoublyCircularList<T>::insert_sorted(const T& data) {
    if (empty()) {
        push_front(data);
    } else {
        Node *atual = head->next();
        int pos = 0;
        while (data > atual->data() && pos < static_cast<int>(size())) {
            atual = atual->next();
            pos++;
        }
        std::cout << pos << std::endl;
        insert(data, static_cast<std::size_t>(pos));
    }
}

template<typename T>
T structures::DoublyCircularList<T>::pop(std::size_t index) {
    if (empty() || index >= size_) {
        throw std::out_of_range("Lista vazia");

    /* testando para ver se realmente precisa
    
    } else if (size() == 1 || index == 0) {
        return (pop_front());
    } else if (size()-1 == index) {
        return pop_back();
    */
    } else {
        T aux_data;
        Node* p = head;  // anterior aonde será dado o pop
        for (int i = 0; i < static_cast<int>(index); i++) {
            p = p->next();
        }
        Node* pn = p->next();  // aquele que será dado o pop
        aux_data = pn->data();
        pn->next()->prev(p);
        p->next(pn->next());
        size_--;
        delete pn;
        return aux_data;
    }
}

template<typename T>
T structures::DoublyCircularList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("Lista vazia");
    } else {
        /*
        T aux_data;
        Node* pn = head->prev();
        Node* p = pn->prev();
        aux_data = pn->data();
        p->next(head);
        head->prev(p);
        delete pn;
        size_--;
        return aux_data;
        */
        return(pop(size()-1));
    }
}

template<typename T>
T structures::DoublyCircularList<T>::pop_front() {
    if (empty() || static_cast<int>(size()) < 1) {
        throw std::out_of_range("lista vazia");
    } else {
        /*
        T aux_data;
        Node* p = head->next()->next();
        aux_data = head->next()->data();
        head->next(p);
        p->prev(head);
        size_--;
        delete head->next();
        return aux_data;
        */
        return (pop(0));
    }
}

template<typename T>
void structures::DoublyCircularList<T>::remove(const T& data) {
    int pos = find(data);
    pop(pos);
}

template<typename T>
bool structures::DoublyCircularList<T>::empty() const {
    return (size() == 0);
}

template<typename T>
bool structures::DoublyCircularList<T>::contains(const T& data) const {
    return(size() != find(data));
}

template<typename T>
T& structures::DoublyCircularList<T>::at(std::size_t index) {
    Node* p = head->next();
    if (static_cast<int>(index) < 0) {
        throw std::out_of_range("Index inválido");
    }
    for (int i = 0; i < static_cast<int>(index); i++) {
        p = p->next();
    }
    return (p->data());
}

template<typename T>
const T& structures::DoublyCircularList<T>::at(std::size_t index) const {
    Node* p = head->next();
    if (static_cast<int>(index) < 0) {
        throw std::out_of_range("Index inválido");
    }
    for (int i = 0; i < static_cast<int>(index); i++) {
        p = p->next();
    }
    return (p->data());
}

template<typename T>
std::size_t structures::DoublyCircularList<T>::find(const T& data) const {
    Node* p = head->next();
    int i = 0;
    while (p->data() != data && i < static_cast<int>(size())) {
        i++;
        p = p->next();
    }
    return (static_cast<std::size_t>(i));
}

template<typename T>
std::size_t structures::DoublyCircularList<T>::size() const {
    return (size_);
}

}  // namespace structures
