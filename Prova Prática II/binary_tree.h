//!  Copyright [2020] <Autor>

#ifndef STRUCTURES_BINARY_TREE_H
#define STRUCTURES_BINARY_TREE_H

#include "./array_list.h"


namespace structures {

//! Classe Árvore binária
template<typename T>
class BinaryTree {
 public:
    //! ...
    BinaryTree();
    //! ...
    ~BinaryTree();
    //! ...
    void insert(const T& data);
    //! ...
    void remove(const T& data);
    //! ...
    bool contains(const T& data) const;
    //! ...
    bool empty() const;
    //! ...
    std::size_t size() const;
    //! ...
    ArrayList<T> pre_order() const;
    //! ...
    ArrayList<T> in_order() const;
    //! ...
    ArrayList<T> post_order() const;

    //******************************************************************
    // Prova prática - implementações necessárias:

    // (1) determinação da altura da árvore:
    int height();

    // (2) contagem do número de folhas:
    int leaves();

    // (3) criação de uma lista com o menor (mínimo) e o maior (máximo)
    //     valor da árvore:
    ArrayList<T> limits();

    // (4) criação de uma duplicação, em memória, da árvore:
    BinaryTree<T> clone();

    // (5) remove nós pelo número de seus filhos:
    void filter(int n_child);

    // (6) criação de um nova árvore que tenha todos os valores e a
    //     menor altura possível, ou seja, balanceada com base apenas
    //     no estabelecimento de uma nova ordem de inserção:
    BinaryTree<T> balance();

    //******************************************************************


 private:
    struct Node {
        //! Construtor
        explicit Node(const T& data) :
        data_{data}
        {}

        //! Destrutor
        ~Node() {
            delete left_;
            delete right_;
        }

        T data_;
        Node* left_{nullptr};
        Node* right_{nullptr};

        //! Inserção
        void insert(const T& data) {
            if (data < data_) {
                if (left_ == nullptr) {
                    left_ = new Node(data);
                    if (left_ == nullptr)
                        throw std::out_of_range("Full tree!");
                } else {
                    left_->insert(data);
                }
            } else {
                if (right_ == nullptr) {
                    right_ = new Node(data);
                    if (right_ == nullptr)
                        throw std::out_of_range("Full tree!");
                } else {
                    right_->insert(data);
                }
            }
        }

        //! Remoção
        bool remove(const T& data) {
            bool deleted = false;
            if (data < data_ && left_ != nullptr) {
                left_ = remove(data, left_, deleted);
            } else if (data > data_ && right_ != nullptr) {
                right_ = remove(data, right_, deleted);
            } else {
                if (right_ != nullptr && left_ != nullptr) {
                    Node* temp = right_->minimum();
                    data_ = temp->data_;
                    right_ = remove(data_, right_, deleted);
                } else if (right_ != nullptr) {
                    Node* temp = right_;
                    data_ = temp->data_;
                    right_ = temp->right_;
                    left_ = temp->left_;
                    temp->right_ = temp->left_ = nullptr;
                    delete temp;
                    deleted = true;
                } else if (left_ != nullptr) {
                    Node* temp = left_;
                    data_ = temp->data_;
                    right_ = temp->right_;
                    left_ = temp->left_;
                    temp->right_ = temp->left_ = nullptr;
                    delete temp;
                    deleted = true;
                }
            }
            return deleted;
        }

        //! Contém
        bool contains(const T& data) const {
            if (data < data_)
                return left_ == nullptr? false : left_->contains(data);
            else if (data > data_)
                return right_ == nullptr? false : right_->contains(data);
            else
                return true;
        }

        //! Pré ordem
        void pre_order(ArrayList<T>& v) const {
            v.push_back(data_);
            if (left_ != nullptr)
                left_->pre_order(v);
            if (right_ != nullptr)
                right_->pre_order(v);
        }

        //! Em ordem
        void in_order(ArrayList<T>& v) const {
            if (left_ != nullptr)
                left_->in_order(v);
            v.push_back(data_);
            if (right_ != nullptr)
                right_->in_order(v);
        }

        //! Pós ordem
        void post_order(ArrayList<T>& v) const {
            if (left_ != nullptr)
                left_->post_order(v);
            if (right_ != nullptr)
                right_->post_order(v);
            v.push_back(data_);
        }

        int height() {
            if (left_ != nullptr && right_ == nullptr) {
                return (1 + left_->height());
            } else if (left_ == nullptr && right_ != nullptr) {
                return (1 + right_->height());
            } else if (left_ != nullptr && right_ != nullptr) {
                if (left_->height() > right_->height()) {
                    return (1 + left_->height());
                } else {
                    return (1 + right_->height());
                }
            }
            return 0;
        }

        Node* node_minimum() {
            return this->minimum();
        }

        Node* node_maximum() {
            return this->maximum();
        }

        int leaves() {
            if (left_ == nullptr && right_ == nullptr) {
                return 1;
            }
            int n_leaves = 0;
            if (left_ != nullptr) {
                n_leaves += left_->leaves();
            }
            if (right_ != nullptr) {
                n_leaves += right_->leaves();
            }
            return n_leaves;
        }

        void filter(int n_child, ArrayList<T>& L) {
            int aux_child = 0;
            if (left_ == nullptr && right_ == nullptr) {
                aux_child = 0;
            } else if (left_ != nullptr && right_ != nullptr) {
                aux_child = 2;
                left_->filter(n_child, L);
                right_->filter(n_child, L);
            } else {
                aux_child = 1;
                if (left_ != nullptr) {
                    left_->filter(n_child, L);
                } else {
                    right_->filter(n_child, L);
                }
            }
            if (aux_child == n_child) {
                L.push_back(this->data_);
            }
        }

        void balance(int start, int end, ArrayList<T>& L) {
            if (start != end) {
                int central = (start+end)/2;
                insert(L[central]);
                this->balance(start, central-1, L);
                this->balance(central+1, end, L);
            } else {
                insert(L[end]);
            }
        }

     private:
        //! Complemento da funcão de remoção
        Node* remove(const T& data, Node* arv, bool& deleted) {
            deleted = false;
            if (arv == nullptr)
                return arv;
            if (data < arv->data_) {
                arv->left_ = remove(data, arv->left_, deleted);
                return arv;
            }
            if (data > arv->data_) {
                arv->right_ = remove(data, arv->right_, deleted);
                return arv;
            }
            // doi filhos
            if (arv->right_ != nullptr && arv->left_ != nullptr) {
                Node* temp = arv->right_->minimum();
                arv->data_ = temp->data_;
                arv->right_ = remove(data, arv->right_, deleted);
                return arv;
            }
            // um filho ou folha
            Node* temp = nullptr;
            if (arv->right_ != nullptr)
                temp = arv->right_;
            else
                temp = arv->left_;

            arv->right_ = arv->left_ = nullptr;
            delete arv;
            deleted = true;
            return temp;
        }

        //! Encontrar o menor
        Node* minimum() {
            if (left_ == nullptr)
                return this;
            return left_->minimum();
        }

        Node* maximum() {
            if (right_ == nullptr)
                return this;
            return right_->maximum();
        }
    };

    Node* root_{nullptr};
    std::size_t size_{0};
};




//******************************************************************
// Prova prática - implementações necessárias:

//! (1) determinação da altura da árvore:
template<typename T>
int BinaryTree<T>::height() {
    /*
        COLOQUE SEU CÓDIGO AQUI ...
    */
    if (!empty()) {
        return root_->height();
    }
    return -1;
}

//! (2) contagem do número de folhas:
template<typename T>
int BinaryTree<T>::leaves() {
    /*
        COLOQUE SEU CÓDIGO AQUI ...
    */
    if (!empty()) {
        return root_->leaves();
    }
    return 0;
}

//! (3) criação de uma lista com o menor (mínimo) e o maior (máximo)
//!     valor da árvore:
template<typename T>
ArrayList<T> BinaryTree<T>::limits() {
    ArrayList<T> L(2);
    /*
        COLOQUE SEU CÓDIGO AQUI ...
    */
    L.push_back(root_->node_minimum()->data_);
    L.push_back(root_->node_maximum()->data_);
    return L;
}

//! (4) criação de uma duplicação, em memória, da árvore:
template<typename T>
BinaryTree<T> BinaryTree<T>::clone() {
    BinaryTree<T> C;
    /*
        COLOQUE SEU CÓDIGO AQUI ...
    */
    for (int i = 0; i < static_cast<int>(size_); i++) {
        C.insert(pre_order()[i]);
    }
    return C;
}

//! (5) remove nós pelo número de seus filhos:
template<typename T>
void BinaryTree<T>::filter(int n_child) {
    /*
        COLOQUE SEU CÓDIGO AQUI ...
    */
    ArrayList<T> L{size_};
    root_->filter(n_child, L);
    for (int i = 0; i < static_cast<int>(L.size()); i++) {
        root_->remove(L[i]);
    }
}

//! (6) criação de um nova árvore que tenha todos os valores e a
//!     menor altura possível, ou seja, balanceada com base apenas
//!     no estabelecimento de uma nova ordem de inserção:
template<typename T>
BinaryTree<T> BinaryTree<T>::balance() {
    BinaryTree<T> B;
    /*
        COLOQUE SEU CÓDIGO AQUI ...
    */
    ArrayList<T> L{size_};
    for (int i = 0; i < static_cast<int>(in_order().size()); i++) {
        L.push_back(in_order()[i]);
    }
    int start_index = 0;
    int end_index = size_-1;
    int central_index = (start_index+end_index)/2;
    std::cout << central_index;
    B.insert(in_order()[central_index]);
    B.root_->balance(start_index, central_index-1, L);
    B.root_->balance(central_index+1, end_index, L);
    return B;
}

//******************************************************************



//! Construtor
template<typename T>
BinaryTree<T>::BinaryTree()
{}

//! Destrutor
template<typename T>
BinaryTree<T>::~BinaryTree() {
    delete root_;
}

//! Inserção
template<typename T>
void BinaryTree<T>::insert(const T& data) {
    if (empty()) {
        root_ = new Node(data);
        if (root_ == nullptr)
            throw std::out_of_range("FUll tree!");
    } else {
            root_->insert(data);
    }
    ++size_;
}

// Remoção
template<typename T>
void BinaryTree<T>::remove(const T& data) {
    if (empty())
        throw std::out_of_range("Empty tree");

    if (size() != 1u) {
        if (root_->remove(data))
            --size_;
    } else {
        if (root_->data_ == data) {
            delete root_;
            root_ = nullptr;
            --size_;
        }
    }
}

//! Contém
template<typename T>
bool BinaryTree<T>::contains(const T& data) const {
    if (empty())
        return false;
    return root_->contains(data);
}

//! Vazio
template<typename T>
bool BinaryTree<T>::empty() const {
    return size() == 0;
}

//! Tamanho
template<typename T>
std::size_t BinaryTree<T>::size() const {
    return size_;
}

//! Pré ordem
template<typename T>
ArrayList<T> BinaryTree<T>::pre_order() const {
    ArrayList<T> v{size_};
    if (!empty())
        root_->pre_order(v);
    return v;
}

//! Em ordem
template<typename T>
ArrayList<T> BinaryTree<T>::in_order() const {
    ArrayList<T> v{size_};
    if (!empty())
        root_->in_order(v);
    return v;
}

//! Pós ordem
template<typename T>
ArrayList<T> BinaryTree<T>::post_order() const {
    ArrayList<T> v{size_};
    if (!empty())
        root_->post_order(v);
    return v;
}

}  // namespace structures

#endif
