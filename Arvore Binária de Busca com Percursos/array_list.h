// Copyright [2022] <Luiz Maurício do Valle Pereira>
#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>


namespace structures {

template<typename T>
class ArrayList {
 public:
    ArrayList();
    explicit ArrayList(std::size_t max_size);
    ~ArrayList();

    void clear();
    void push_back(const T& data);
    void push_front(const T& data);
    void insert(const T& data, std::size_t index);
    void insert_sorted(const T& data);
    T pop(std::size_t index);
    T pop_back();
    T pop_front();
    void remove(const T& data);
    bool full() const;
    bool empty() const;
    bool contains(const T& data) const;
    std::size_t find(const T& data) const;
    std::size_t size() const;
    std::size_t max_size() const;
    T& at(std::size_t index);
    T& operator[](std::size_t index);
    const T& at(std::size_t index) const;
    const T& operator[](std::size_t index) const;
    // descricao do 'operator []' na FAQ da disciplina

 private:
    static const auto DEFAULT_MAX = 10u;
    T* contents;
    std::size_t size_;
    std::size_t max_size_;
    // const static auto DEFAULT_MAX = 10u;
};

}  // namespace structures

#endif

template<typename T>
structures::ArrayList<T>::ArrayList() {
    size_ = 0;
    max_size_ = DEFAULT_MAX;
    contents = new T[max_size_];
}

template<typename T>
structures::ArrayList<T>::ArrayList(std::size_t max_size) {
    size_ = 0;
    max_size_ = max_size;
    contents = new T[max_size_];
}

template<typename T>
structures::ArrayList<T>::~ArrayList() {
    delete [] contents;
}

template<typename T>
void structures::ArrayList<T>::clear() {
    size_ = 0;
}

template<typename T>
void structures::ArrayList<T>::push_back(const T& data) {
    // inserir no fim da lista
    if (size() == max_size()) {
        throw std::out_of_range("Lista cheia");
    } else {
        insert(data, size());
    }
}

template<typename T>
void structures::ArrayList<T>::push_front(const T& data) {
    // inserir no início da lista
    if (size() == max_size()) {
        throw std::out_of_range("Lista cheia");
    } else {
        insert(data, 0);
    }
}

template<typename T>
void structures::ArrayList<T>::insert(const T& data, std::size_t index) {
    if (index <= size() && size() < max_size()) {
        for (int i = size()-1; i >= static_cast<int>(index); i--) {
            contents[i+1] = contents[i];
        }
        contents[index] = data;
        size_++;
    } else {
        throw std::out_of_range("Função insert: full list or index problems");
    }
}

template<typename T>
void structures::ArrayList<T>::insert_sorted(const T& data) {
    if (size() == max_size()) {
        throw std::out_of_range("Lista cheia");
    } else {
        int i = 0;
        while (i < static_cast<int>(size()) && contents[i] < data) {
            i++;
        }
        insert(data, i);
    }
}

template<typename T>
T structures::ArrayList<T>::pop(std::size_t index) {
    if (index < size()) {
        T return_aux = contents[index];
        for (int i = index; i < static_cast<int>(size()-1); i++) {
            contents[i] = contents[i + 1];
        }
        size_--;
        return return_aux;
    } else {
        throw std::out_of_range("Index fora do escopo");
    }
}

template<typename T>
T structures::ArrayList<T>::pop_back() {
    // pop do último membro da lista
    return pop(size()-1);
}

template<typename T>
T structures::ArrayList<T>::pop_front() {
    // pop do primeiro membro da lista
    return pop(0);
}

template<typename T>
void structures::ArrayList<T>::remove(const T& data) {
    for (int i = 0; i < static_cast<int>(size()); i++) {
        if (contents[i] == data) {
            pop(i);
        }
    }
}

template<typename T>
bool structures::ArrayList<T>::full() const {
    return (size() == max_size());
}

template<typename T>
bool structures::ArrayList<T>::empty() const {
    return (size() == 0);
}

template<typename T>
bool structures::ArrayList<T>::contains(const T& data) const {
    bool aux_bool = 0;
    if (empty() == 0) {
        for (int i = 0; i < static_cast<int>(size()); i++) {
            if (contents[i] == data) {
                aux_bool = 1;
            }
        }
    }
    return (aux_bool);
}

template<typename T>
std::size_t structures::ArrayList<T>::find(const T& data) const {
    int aux = size();
    if (empty() == 0) {
        for (int i = 0; i < static_cast<int>(size()); i++) {
            if (contents[i] == data) {
                aux = i;
                break;
            }
        }
    } else {
        throw std::out_of_range("Lista vazia");
    }
    return (aux);
}

template<typename T>
std::size_t structures::ArrayList<T>::size() const {
    return size_;
}

template<typename T>
std::size_t structures::ArrayList<T>::max_size() const {
    return max_size_;
}

template<typename T>
T& structures::ArrayList<T>::at(std::size_t index) {
    if (index < max_size()) {
        return contents[index];
    } else {
        throw std::out_of_range("Index fora do escopo");
    }
}

template<typename T>
T& structures::ArrayList<T>::operator[](std::size_t index) {
    return (at(index));
}

template<typename T>
const T& structures::ArrayList<T>::at(std::size_t index) const {
    if (index < max_size()) {
        return (contents[index]);
    } else {
        throw std::out_of_range("Index fora do escopo");
    }
}

template<typename T>
const T& structures::ArrayList<T>::operator[](std::size_t index) const {
    if (index < max_size()) {
        return (contents[index]);
    } else {
        throw std::out_of_range("Index fora do escopo");
    }
}
