/**
 * @file avl.h
 * @author Erick Alfredo García Huerta
 * @brief Función que recibe una serie de libros y los acomoda en función de su número de págias
 * @date 2021-12-02
 */
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

/**
 * @brief Construct a new Node:: Node object
 * 
 * @param lirbo estructura que será el principal valor del AVL
 */
Node::Node(Libros lirbo) : value(lirbo), left(0), right(0), level(0), balance(0) {}


/**
 * @brief Construct a new Node:: Node object
 * 
 * @param lirbo estructura que será el valor del nodo
 * @param le valor izquierdo
 * @param ri valor derecho
 * @param lvl nivel de profundidad
 * @param bal factor de balance
 */
Node::Node(Libros lirbo, Node *le, Node *ri, int lvl, int bal) : value(lirbo), left(le), right(ri), 
           level(lvl), balance(bal) {}

/**
 * @brief Función que agrega un nodo más al árbol, asignándole su posición dependiendo de su número de páginas.
 * 
 * @complejidad: O(log n) debido a que el ciclo recursivo puede llegar a recorrer todo el lado izquierdo o derecho del 
 * árbol, pero no ambos.
 * 
 * @param lirbo valor del nodo
 */
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

/**
 * @brief Función que busca un libro en base a su número de identificación
 * 
 * @complejidad: O(log n) debido a que por la validación, no se pueden recorrer ambas ramas del árbol.
 * 
 * @param numeroDeHojas del libro
 * @return true se encontró el libro
 * @return false no se encontró el libro
 */
bool Node::find(int numeroDeHojas) {
    if (numeroDeHojas == value.numeroDeHojas) {
        return true;
    } else if (numeroDeHojas < value.numeroDeHojas) {
        return (left != 0 && left->find(numeroDeHojas));
    } else if (numeroDeHojas > value.numeroDeHojas) {
        return (right != 0 && right->find(numeroDeHojas));
    }
    return false;
}

/**
 * @brief función que busca el predecesor del nodo
 * 
 * @return Node* nodo padre
 */

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

/**
 * @brief Función que remueve todos los hijos del nodo.
 */
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

/**
 * @brief FUnción que imprime los datos del AVL en forma inorder.
 * 
 * @complejidad: O(n) debido a que recorre todo el árbol.
 * 
 * @param aux datos del árbol.
 */
void Node::inorder(stringstream &aux) const {
    if (left != 0) {
        left->inorder(aux);
    }
    if (aux.tellp() != 1) {
        aux << " ";
    }
    aux << "(" << value.nombre << " Numero de paginas: " << value.numeroDeHojas << ")";
    if (right != 0) {
        right->inorder(aux);
    }
}

/**
 * @brief Función que imprime los datos del árbol en forma preorder
 * 
 * @complejidad: O(n) debido a que recorre todo el árbol
 * 
 * @param aux datos del árbol.
 */
void Node::preorder(std::stringstream &aux) const {
    aux << "(" << value.nombre << " Numero de paginas: " << value.numeroDeHojas << ")";
    if (left != 0) {
        aux << " ";
        left->preorder(aux);
    }
    if (right != 0) {
        aux << " ";
        right->preorder(aux);
    }
}

/**
 * @brief Función que regresa el valor de profundidad del árbol.
 * 
 * @return int valor de profundidad
 */
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

/**
 * @brief Función que revisa el balance del árbol
 * 
 * @param lirbo valor del nodo
 * @param parent nodo padre del árbol
 * @param checked valor que marca si el nodo ha sido revisado o no
 * @return Node* nodo revisado
 */
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

/**
 * @brief Función que balancea el árbol, deciciendo en base al valor de balance qué tipo de rotación se necesita
 * 
 * @return Node* nodo balanceado.
 */
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

/**
 * @brief Función que rota a la izquerda el nodo
 * 
 * @param a nodo a rotar
 * @return Node* nodo rotado
 */
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

/**
 * @brief Función que rota a la derecha el nodo
 * 
 * @param a 
 * @return Node* nodo rotado
 */
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

/**
 * @brief Función que rota a la izquierda y a la derecha un nodo
 * 
 * @param a nodo a rotar
 * @return Node*  nodo rotado
 */
Node *Node::rot_left_right(Node *a) {
    a->left = rot_left(a->left);
    a = rot_right(a);
    return a;
}

/**
 * @brief Función que rota a la derecha y a la izquierda un nodo
 * 
 * @param a nodo a rotar
 * @return Node* nodo rotado
 */
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

/**
 * @brief Construct a new AVLLibros::AVLLibros object
 * 
 */
AVLLibros::AVLLibros() : root(0) {}

/**
 * @brief Destroy the AVLLibros::AVLLibros object
 * 
 */
AVLLibros::~AVLLibros() {
    removeAll();
}

/**
 * @brief Función que devuelve si el árbol está vacío o no
 * 
 * @return true el árbol no está vacío
 * @return false el árbol está vacío
 */
bool AVLLibros::empty() const {
    return root == 0;
}

/**
 * @brief Función que agrega un nodo al árbol
 * 
 * @param lirbo valor a ingresar en el árbol.
 */
void AVLLibros::add(const Libros &lirbo) {
    if (!empty()) {
        if (!root->find(lirbo.numeroDeHojas)) {
            Node *temp;
            Libros check_val(lirbo);
            bool aux = false;
            root->add(lirbo);
            root->max_depth();
            temp = root->check_tree(&check_val, 0, &aux);
            if (check_val.numeroDeHojas == root->value.numeroDeHojas) {
                root = temp;
            }
            root->max_depth();
        }
    } else {
        root = new Node(lirbo);
    }
}

/**
 * @brief Función que busca un nodo en el árbol
 * 
 * @param numeroDeHojas numero de páginas del libro
 * @return true se encontró el nodo
 * @return false no se encontró el nodo
 */
bool AVLLibros::find(int numeroDeHojas) const {
    if (!empty()) {
        return root->find(numeroDeHojas);
    } else {
        return false;
    }
}

/**
 * @brief FUnción que ayuda a borrar todo el árbol.
 * 
 */
void AVLLibros::removeAll() {
    if (!empty()) {
        root->removeChilds();
    }
    delete root;
    root = 0;
}

/**
 * @brief Función que imprime en forma inorder los nodos del árbol
 * 
 * @return string datos del árbol
 */
string AVLLibros::inorder() const {
    std::stringstream aux;
    aux << "[";
    if (!empty()) {
        root->inorder(aux);
    }
    aux << "]";
    return aux.str();
}

/**
 * @brief FUnción que imprime en forma preorder los nodos del árbol
 * 
 * @return string datos del árbol
 */
string AVLLibros::preorder() const {
    std::stringstream aux;
    aux << "[";
    if (!empty()) {
        root->preorder(aux);
    }
    aux << "]";
    return aux.str();
}

#endif