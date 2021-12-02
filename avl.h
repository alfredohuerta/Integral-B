#ifndef AVL_H_
#define AVL_H_

#include "libros.h"
#include <utility>
#include <sstream>

class Node {
    private:
        Libros value;
        Node *left, *right;
        int level, balance;
        Node *predecesor();

    public:
        explicit Node(Libros);
        Node(Libros, Node *, Node *, int, int);

        void add(const Libros &);
        bool find(int);
        void remove(int);
        void removeChilds();
        void inorder(stringstream &) const;
        void preorder(stringstream &) const;
        int max_depth();

        Node *check_tree(Libros *, Node *, bool *);
        Node *balance_tree();

        static Node *rot_left(Node *);
        static Node *rot_right(Node *);
        static Node *rot_left_right(Node *);
        static Node *rot_right_left(Node *);
        friend class AVLLibros;
};

Node::Node(Libros lirbo) : value(std::move(lirbo)), left(0), right(0), level(0), balance(0) {}

Node::Node(Libros lirbo, Node *le, Node *ri, int lvl, int bal) : value(std::move(lirbo)), left(le), right(ri), 
           level(lvl), balance(bal) {}

void Node::add(const Libros &lirbo) {
    if (lirbo.numeroDeHojas < value.numeroDeHojas) {
        if (left != 0) {
            left->add(lirbo);
        } else {
            left = new Node(lirbo);
        }
    } else {
        if (right != 0) {
            right->add(lirbo);
        } else {
            right = new Node(lirbo);
        }
    }
}

bool Node::find(int id) {
    if (id == value.id) {
        return true;
    } else if (id < value.id) {
        return (left != 0 && left->find(id));
    } else if (id > value.id) {
        return (right != 0 && right->find(id));
    }
    return false;
}

Node *Node::predecesor() {
    Node *le, *ri;
    le = left;
    ri = right;

    if (left == 0) {
        if (right != 0) {
            right = 0;
        }
        return ri;
    }

    if (left->right == 0) {
        left = left->left;
        le->left = 0;
        return le;
    }

    Node *parent, *child;
    parent = left;
    child = left->right;
    while (child->right != 0) {
        parent = child;
        child = child->right;
    }
    parent->right = child->left;
    child->left = 0;
    return child;
}

void Node::removeChilds() {
    if (left != 0) {
        left->removeChilds();
        delete left;
        left = 0;
    }
    if (right != 0) {
        right->removeChilds();
        delete right;
        right = 0;
    }
}

void Node::inorder(stringstream &aux) const {
    if (left != 0) {
        left->inorder(aux);
    }
    if (aux.tellp() != 1) {
        aux << " ";
    }
    aux << "(" << value.nombre << " " << value.numeroDeHojas << ")";
    if (right != 0) {
        right->inorder(aux);
    }
}

void Node::preorder(std::stringstream &aux) const {
    aux << "(" << value.nombre << " " << value.numeroDeHojas << ")";
    if (left != 0) {
        aux << " ";
        left->preorder(aux);
    }
    if (right != 0) {
        aux << " ";
        right->preorder(aux);
    }
}

int Node::max_depth() {
    int le = 0, ri = 0;
    if (left != 0)
        le = left->max_depth() + 1;
    if (right != 0)
        ri = right->max_depth() + 1;
    if (le > ri)
        level = le;
    else
        level = ri;
    balance = le - ri;
    return level;
}

Node *Node::check_tree(Libros *lirbo, Node *parent, bool *checked) {
    Node *le = 0, *ri = 0, *a = 0;
    if (left != 0)
        le = left->check_tree(lirbo, this, checked);
    if (right != 0)
        ri = right->check_tree(lirbo, this, checked);
    if (!*checked) {
        if (balance > 1) {
            a = balance_tree();
            *lirbo = value;
            *checked = true;
            if (parent != 0) {
                parent->left = a;
            }
        } else if (balance < -1) {
            a = balance_tree();
            *lirbo = value;
            *checked = true;
            if (parent != 0) {
                parent->right = a;
            }
        }
    }
    return a;
}

Node *Node::balance_tree() {
    Node *a = this, *le = left, *ri = right;
    if (balance > 0) {
        if (le->balance > 0) {
            a = rot_right(a);
        } else {
            a = rot_left_right(a);
        }
    } else {
        if (ri->balance < 0) {
            a = rot_left(a);
        } else {
            a = rot_right_left(a);
        }
    }
    return a;
}

Node *Node::rot_left(Node *a) {
    Node *b, *temp = 0;
    if (a->right != 0) {
        b = a->right;
        if (b->left != 0)
            temp = b->left;
        b->left = a;
        if (temp != 0) {
            a->right = temp;
        } else {
            a->right = 0;
        }
    }
    return b;
}

Node *Node::rot_right(Node *a) {
    Node *b, *temp = 0;
    if (a->left != 0) {
        b = a->left;
        if (b->right != 0)
            temp = b->right;
        b->right = a;
        if (temp != 0) {
            a->left = temp;
        } else {
            a->left = 0;
        }
    }
    return b;
}

Node *Node::rot_left_right(Node *a) {
    a->left = rot_left(a->left);
    a = rot_right(a);
    return a;
}

Node *Node::rot_right_left(Node *a) {
    a->right = rot_right(a->right);
    a = rot_left(a);
    return a;
}

class AVLLibros {
private:
    Node *root;
public:
    AVLLibros();
    ~AVLLibros();

    bool empty() const;
    void add(const Libros &);
    bool find(int) const;
    void remove(int);
    void removeAll();
    string inorder() const;
    string preorder() const;
};

AVLLibros::AVLLibros() : root(0) {}

AVLLibros::~AVLLibros() {
    removeAll();
}

bool AVLLibros::empty() const {
    return root == 0;
}

void AVLLibros::add(const Libros &lirbo) {
    if (!empty()) {
        if (!root->find(lirbo.id)) {
            Node *temp;
            Libros check_val(lirbo);
            bool aux = false;
            root->add(lirbo);
            root->max_depth();
            temp = root->check_tree(&check_val, 0, &aux);
            if (check_val.id == root->value.id) {
                root = temp;
            }
            root->max_depth();
        }
    } else {
        root = new Node(lirbo);
    }
}

bool AVLLibros::find(int id) const {
    if (!empty()) {
        return root->find(id);
    } else {
        return false;
    }
}

void AVLLibros::removeAll() {
    if (!empty()) {
        root->removeChilds();
    }
    delete root;
    root = 0;
}

string AVLLibros::inorder() const {
    std::stringstream aux;
    aux << "[";
    if (!empty()) {
        root->inorder(aux);
    }
    aux << "]";
    return aux.str();
}

std::string AVLLibros::preorder() const {
    std::stringstream aux;
    aux << "[";
    if (!empty()) {
        root->preorder(aux);
    }
    aux << "]";
    return aux.str();
}

#endif