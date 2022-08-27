//! Copyright [2022] <Luiz Maurício do Valle Pereira>
#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>


namespace structures {

//! Classe LinkedList
template<typename T>
class LinkedList {
 public:
    //! ...
    LinkedList();  // construtor padrão
    //! ...
    ~LinkedList();  // destrutor
    //! ...
    void clear();  // limpar lista
    //! ...
    void push_back(const T& data);  // inserir no fim
    //! ...
    void push_front(const T& data);  // inserir no início
    //! ...
    void insert(const T& data, std::size_t index);  // inserir na posição
    //! ...
    void insert_sorted(const T& data);  // inserir em ordem
    //! ...
    T& at(std::size_t index);  // acessar um elemento na posição index
    //! ...
    T pop(std::size_t index);  // retirar da posição
    //! ...
    T pop_back();  // retirar do fim
    //! ...
    T pop_front();  // retirar do início
    //! ...
    void remove(const T& data);  // remover específico
    //! ...
    bool empty() const;  // lista vazia
    //! ...
    bool contains(const T& data) const;  // contém
    //! ...
    std::size_t find(const T& data) const;  // posição do dado
    //! ...
    std::size_t size() const;  // tamanho da lista
    // Método que retorna ponteiro para uma posição
    // Node* position(std::size_t index);

 private:
    class Node {  // Elemento
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {  // getter: dado
            return data_;
        }

        const T& data() const {  // getter const: dado
            return data_;
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
        Node* next_{nullptr};
    };

    Node* end() {  // retorna ponteiro para último nodo da lista
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

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

    Node* head{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures

#endif

template<typename T>
structures::LinkedList<T>::LinkedList() {
    head = nullptr;
    size_ = 0;
}

template<typename T>
structures::LinkedList<T>::~LinkedList() {
    clear();
}

template<typename T>
void structures::LinkedList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

template<typename T>
void structures::LinkedList<T>::push_back(const T& data) {
    Node* novo = new Node(data);
    Node* p;
    if (empty()) {
        head = novo;
    } else {
        p = end();
        p->next(novo);
    }
    size_++;
    novo->next(nullptr);
}

template<typename T>
void structures::LinkedList<T>::push_front(const T& data) {
    Node *novo = new Node(data);
    if (novo == nullptr) {
        throw std::out_of_range("Stack Overflow, lista cheia");
    }
    novo->next(head);
    head = novo;
    size_++;
}

template<typename T>
void structures::LinkedList<T>::insert(const T& data, std::size_t index) {
    Node *novo = new Node(data);
    if (novo == nullptr) {
        throw std::out_of_range("Stack Overflow, lista cheia");
    } else if (static_cast<int>(index) == 0) {
        push_front(data);
    } else {
        Node* p = position(index-1);
        novo->next(p->next());
        p->next(novo);
        size_++;
    }
}

template<typename T>
void structures::LinkedList<T>::insert_sorted(const T& data) {
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
T& structures::LinkedList<T>::at(std::size_t index) {
    return (position(index)->data());
}

template<typename T>
T structures::LinkedList<T>::pop(std::size_t index) {
    if (empty() || index >= size_) {
        throw std::out_of_range("Lista vazia");
    } else if (size() == 1 || index == 1) {
        return (pop_front());
    } else if (size()-1 == index) {
        return pop_back();
    }
    Node* p = position(index-1);
    Node* t = p->next();
    p->next(t->next());
    T aux = t->data();
    size_--;
    delete t;
    return aux;
}

template<typename T>
T structures::LinkedList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("Lista vazia");
    }
    if (size_ == 1) {
        return (pop_front());
    }
    Node* p;
    p = position(size_ - 2);
    T aux = (p->next())->data();
    delete p->next();
    p->next(nullptr);
    size_--;
    return aux;
}

template<typename T>
T structures::LinkedList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    }
    Node* p = head;
    head = p->next();
    T aux = p->data();
    size_--;
    delete p;
    return aux;
}

template<typename T>
void structures::LinkedList<T>::remove(const T& data) {
    int pos = find(data);
    pop(pos);
}

template<typename T>
bool structures::LinkedList<T>::empty() const {
    return (size_ == 0);
}

template<typename T>
bool structures::LinkedList<T>::contains(const T& data) const {
    return(size_ - find(data));
}

template<typename T>
std::size_t structures::LinkedList<T>::find(const T& data) const {
    Node* p = head;
    int i = 0;
    while (p != nullptr && p->data() != data) {
        i++;
        p = p->next();
    }
    return (static_cast<std::size_t>(i));
}

template<typename T>
std::size_t structures::LinkedList<T>::size() const {
    return (size_);
}
