//! Copyright [2022] <Luiz Maurício do Valle Pereira>
#include "./array_list.h"

namespace structures {

template<typename T>
class BinaryTree {
 public:
    BinaryTree() {
        root = nullptr;
        size_ = 0;
    }

    ~BinaryTree() {
        auto aux = post_order();
        for (int i = 0; i < static_cast<int>(aux.size()); i++) {
            remove(aux[i]);
        }
    }

    void insert(const T& data) {
        if (empty()) {
            root = new Node(data);
        } else {
            root->insert(data);
        }
        size_++;
    }

    void remove(const T& data);

    bool contains(const T& data) const;

    bool empty() const;

    std::size_t size() const;

    ArrayList<T> pre_order() const;

    ArrayList<T> in_order() const;

    ArrayList<T> post_order() const;

 private:
    struct Node {
        explicit Node(const T& data):
            data{data}
        {}

        T data = T();
        Node* left = nullptr;
        Node* right = nullptr;

        void insert(const T& data_) {
            if (data_ > data) {
                if (right == nullptr) {
                    Node* novo = new Node(data_);
                    right = novo;
                } else {
                    right->insert(data_);
                }
            } else {
                if (left == nullptr) {
                    Node* novo = new Node(data_);
                    left = novo;
                } else {
                    left->insert(data_);
                }
            }
        }

        bool is_leaf(Node* root) {
            return ((root->left == nullptr) && (root->right == nullptr));
        }

        Node* min_node(Node* node) {
            while (node->left != nullptr) {
                node = node->left;
            }
            return node;
        }

        bool remove(const T& data_) {
            if (data_ == data) {
                // hit
                return true;
            } else if (data_ > data) {
                if (right != nullptr) {
                    bool teste = right->remove(data_);
                    if (teste) {
                        removerFilho(data_);
                    }
                }
            } else {
                if (left != nullptr) {
                    bool teste = left->remove(data_);
                    if (teste) {
                        removerFilho(data_);
                    }
                }
            }
            return false;
        }

        void removerFilho(const T& data_) {
            // função que remove o filho do nodo
            Node* del = nullptr;
            if (left != nullptr && left->data == data_) {
                // remover filho da esquerda
                del = left;
                if (is_leaf(del)) {
                    // nenhum filho
                    left = nullptr;
                } else if (left != nullptr && right != nullptr) {
                    // dois filhos
                    Node* subs = min_node(del->right);
                    remove(subs->data);
                    left = subs;
                } else {
                    // um filho
                    if (del->left != nullptr) {
                        left = del->left;
                    } else {
                        left = del->right;
                    }
                }
            } else {
                // remover filho da direita
                del = right;
                if (is_leaf(del)) {
                    right = nullptr;
                } else if (left != nullptr && right != nullptr) {
                    // dois filhos
                    Node* subs = min_node(del->right);
                    remove(subs->data);
                    right = subs;
                } else {
                    // um filho
                    if (del->left != nullptr) {
                        right = del->left;
                    } else {
                        right = del->right;
                    }
                }
            }
            delete del;
        }

        bool contains(const T& data_) const {
            if (data == data_) {
                return (true);
            } else if (right == nullptr && left == nullptr) {
                return (false);
            } else if (data_ < data && left != nullptr) {
                return (left->contains(data_));
            } else if (data_ > data && right != nullptr) {
                return (right->contains(data_));
            } else {
                return (false);
            }
        }

        void pre_order(ArrayList<T>& v) const {
            v.push_back(data);
            if (left != nullptr) {
                left->pre_order(v);
            }
            if (right != nullptr) {
                right->pre_order(v);
            }
        }

        void in_order(ArrayList<T>& v) const {
            if (left != nullptr) {
                left->in_order(v);
            }
            v.push_back(data);
            if (right != nullptr) {
                right->in_order(v);
            }
        }

        void post_order(ArrayList<T>& v) const {
            if (left != nullptr) {
                left->post_order(v);
            }
            if (right != nullptr) {
                right->post_order(v);
            }
            v.push_back(data);
        }
    };

    Node* root;
    std::size_t size_;
};

};  // namespace structures

template<typename T>
void structures::BinaryTree<T>::remove(const T& data) {
    if (!empty()) {
        root->remove(data);
    }
    if (!contains(data)) {
        size_--;
    }
}

template<typename T>
bool structures::BinaryTree<T>::contains(const T& data) const {
    if (empty()) {
        return (false);
    } else {
        return (root->contains(data));
    }
}

template<typename T>
bool structures::BinaryTree<T>::empty() const {
    return (size() == 0);
}

template<typename T>
std::size_t structures::BinaryTree<T>::size() const {
    return (size_);
}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::pre_order() const {
    structures::ArrayList<T> v{size_};
    if (!empty()) {
        root->pre_order(v);
    }
    return v;
}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::in_order() const {
    structures::ArrayList<T> v{size_};
    if (!empty()) {
        root->in_order(v);
    }
    return v;
}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::post_order() const {
    structures::ArrayList<T> v{size_};
    if (!empty()) {
        root->post_order(v);
    }
    return v;
}
