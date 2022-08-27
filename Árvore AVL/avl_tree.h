// Copyright [2022] <Luiz Maurício do Valle Pereira>
#include "array_list.h"


namespace structures {

template<typename T>
class AVLTree {
 public:
    AVLTree() {
        root = nullptr;
        size_ = 0;
    }

    ~AVLTree() {
        auto aux = post_order();
        for (int i = 0; i <static_cast<int>(aux.size()); i++) {
            remove(aux[i]);
        }
    }

    int maximo(int a, int b) {
        if (a > b) {
            return a;
        }
        return b;
    }

    void insert(const T& data);

    void remove(const T& data);

    bool contains(const T& data) const;

    bool empty() const;

    std::size_t size() const;

    int height() const;

    ArrayList<T> pre_order() const;

    ArrayList<T> in_order() const;

    ArrayList<T> post_order() const;

 private:
    struct Node {
        explicit Node(const T& data):
            data{data}
        {}

        T data = T();
        int height_ = 0;
        Node* left = nullptr;
        Node* right = nullptr;

        int maximo(int a, int b) {
            if (a > b) {
                return a;
            }
            return b;
        }

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
            // atualizando a altura após a inserção
            std::cout << "Update Height" << std::endl;
            updateHeight();
            // rebalanceando o nodo
             std::cout << "Rebalance" << std::endl;
            rebalance();
        }

        void rebalance_this() {
            // rebalanceia o próprio nodo
            std::cout << "iniciou rebalance root" << std::endl;
            if (right != nullptr && get_balance() == -2
                && right->get_balance() == -1) {
                // rotação r-r
                std::cout << "r-r" << std::endl;
                right = simpleRight(this);
            }
            if (right != nullptr && get_balance() == -2
            && right->get_balance() == 1) {
                // rotação r-l
                std::cout << "r-l" << std::endl;
                right = doubleRight(this);
            }
            if (left != nullptr && get_balance() == 2
            && left->get_balance() == -1) {
                // rotação l-r
                std::cout << "l-r" << std::endl;
                right = doubleLeft(this);
            }
            if (left != nullptr && get_balance() == 2
            && left->get_balance() == 1) {
                // rotação l-l
                std::cout << "l-l" << std::endl;
                right = simpleLeft(this);
            }
            std::cout << "Altura final: ";
            std::cout << height_ << std::endl;
            std::cout << "Finalizou rebalancer root" << std::endl;
        }

        void rebalance() {
            // rebalanceia os filhos do nodo
            // checando o fator de balanceamento após a inserção
            if (right != nullptr) {
                // checar os casos de balanceamento da direita
                if (right->right != nullptr && right->get_balance() == -2
                    && right->right->get_balance() == -1) {
                    // rotação r-r
                    std::cout << "r-r" << std::endl;
                    right = simpleRight(right);
                }
                if (right->right != nullptr && right->get_balance() == -2
                && right->right->get_balance() == 1) {
                    // rotação r-l
                    std::cout << "r-l" << std::endl;
                    right = doubleRight(right);
                }
                if (right->left != nullptr && right->get_balance() == 2
                && right->left->get_balance() == -1) {
                    // rotação l-r
                    std::cout << "l-r" << std::endl;
                    right = doubleLeft(right);
                }
                if (right->left != nullptr && right->get_balance() == 2
                && right->left->get_balance() == 1) {
                    // rotação l-l
                    std::cout << "l-l" << std::endl;
                    right = simpleLeft(right);
                }
            }
            if (left != nullptr) {
                if (left->left != nullptr) {
                    if (left->get_balance() == 2
                    && left->left->get_balance() == -1) {
                        // rotação l-r
                        std::cout << "l-r" << std::endl;
                        right = doubleLeft(right);
                    }
                    if (left->get_balance() == 2
                    && left->left->get_balance() == 1) {
                        // rotação l-l
                        std::cout << "l-l" << std::endl;
                        right = simpleLeft(right);
                    }
                }
                if (left->right != nullptr) {
                    if (left->get_balance() == -2
                    && left->right->get_balance() == -1) {
                        // rotação r-r
                        std::cout << "r-r" << std::endl;
                        right = simpleRight(right);
                    }
                    if (left->get_balance() == -2
                    && left->right->get_balance() == 2) {
                        // rotação r-l
                        std::cout << "r-l" << std::endl;
                        right = doubleRight(right);
                    }
                }
            }
            std::cout << height_ << std::endl;
            std::cout << "Finalizou rebalance" << std::endl;
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
            updateHeight();
            rebalance();
            std::cout << height_ << std::endl;
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

        void updateHeight() {
            /*
            if (!is_leaf(this)) {
                if (right != nullptr && left != nullptr) {
                    height_ = 1 + maximo(right->height_, left->height_);
                } else if (right != nullptr && left == nullptr) {
                    height_ = 1 + right->height_;
                } else if (right == nullptr && left != nullptr) {
                    height_ = 1 + left->height_;
                }
                height_ = -1;
            } else {
                height_ = 0;
            }
            */
            height_ = altura(this);
        }

        int altura(Node* raiz) {
            if (raiz == nullptr) {
                return (-1);
            }
            int he = altura(raiz->left);
            int hd = altura(raiz->right);
            return (1 + maximo(he, hd));
        }


        int get_balance() {
            // retorna o fator de balanceamento
            if (is_leaf(this)) {
                return (0);
            }
            if (left != nullptr && right != nullptr) {
                return (left->height_ - right->height_);
            } else if (left != nullptr && right == nullptr) {
                return left->height_;
            }
            return right->height_;
        }

        Node* simpleLeft(Node* node) {
            std::cout << "Simple left" << std::endl;
            // rotação left
            Node* filho = node->right;
            // std::cout << "1" << std::endl;
            node->right = filho->left;
            // std::cout << "2" << std::endl;
            filho->left = node;
            // std::cout << "3" << std::endl;
            filho->updateHeight();
            // std::cout << "4" << std::endl;
            node->updateHeight();
            std::cout << "Simple left fim" << std::endl;
            return filho;  // retorna o novo topo da subárvore
        }

        Node* simpleRight(Node* node) {
            std::cout << "Simple right" << std::endl;
            // rotação right
            Node* filho = node->right;
            node->left = filho->right;
            filho->right = node;
            filho->updateHeight();
            node->updateHeight();
            std::cout << "Simple right fim" << std::endl;
            return filho;  // retorna o novo topo da subárvore
        }

        Node* doubleLeft(Node* node) {
            // rotação left right
            node->left = simpleRight(node->left);
            return simpleLeft(node);
        }

        Node* doubleRight(Node* node) {
            // rotação right left
            node->right = simpleLeft(node->right);
            return simpleRight(node);
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

}  // namespace structures

// -----

template<typename T>
int structures::AVLTree<T>::height() const {
    root->updateHeight();
    return root->height_-1;
}

template<typename T>
void structures::AVLTree<T>::insert(const T& data) {
    if (empty()) {
        std::cout << "Criando root" << std::endl;
        root = new Node(data);
    } else {
        std::cout << "inserindo na arvore" << std::endl;
        root->insert(data);
    }
    root->rebalance_this();
    root->updateHeight();
    std::cout << "Chegou aqui" << std::endl;
    size_++;
}

template<typename T>
void structures::AVLTree<T>::remove(const T& data) {
    if (!empty()) {
        root->remove(data);
    }
    if (!contains(data)) {
        size_--;
    }
}

template<typename T>
bool structures::AVLTree<T>::contains(const T& data) const {
    if (empty()) {
        return (false);
    } else {
        return (root->contains(data));
    }
}

template<typename T>
bool structures::AVLTree<T>::empty() const {
    return (size() == 0);
}

template<typename T>
std::size_t structures::AVLTree<T>::size() const {
    return (size_);
}

template<typename T>
structures::ArrayList<T> structures::AVLTree<T>::pre_order() const {
    structures::ArrayList<T> v{size_};
    if (!empty()) {
        root->pre_order(v);
    }
    return v;
}

template<typename T>
structures::ArrayList<T> structures::AVLTree<T>::in_order() const {
    structures::ArrayList<T> v{size_};
    if (!empty()) {
        root->in_order(v);
    }
    return v;
}

template<typename T>
structures::ArrayList<T> structures::AVLTree<T>::post_order() const {
    structures::ArrayList<T> v{size_};
    if (!empty()) {
        root->post_order(v);
    }
    return v;
}
