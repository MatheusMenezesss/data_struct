#include <iostream>

using namespace std;

struct node {
    int value;
    node* father;
    node* left_son;
    node* rigth_son;
};

class BST {
protected:
    node* root;
    BST() {
        root = nullptr;
    }

    void tree_insert(node* node_insert) {
        node* node_aux = nullptr; // elemento de referência para o último node válido 
        node* curs = root; // referencia o próximo elemento
        while (curs) { // se curs == null, então node_aux é uma folha e não será atualizado para null pois a iteração não ocorrerá!
            node_aux = curs;
            if (node_insert->value < curs->value)
                curs = curs->left_son;
            else
                curs = curs->rigth_son;
        }
        node_insert->father = node_aux;
        if (!node_aux) root = node_insert; // se a tree estiver vazia, o elemento inserido será a raiz (root)
        else if (node_insert->value > node_aux->value)
            node_aux->rigth_son = node_insert;
        else
            node_aux->left_son = node_insert;
    }

    node* tree_search(int wanted_value, node* root_current) {
        if (!root_current || root_current->value == wanted_value)
            return root_current;
        if (wanted_value < root_current->value)
            return tree_search(wanted_value, root_current->left_son);
        else
            return tree_search(wanted_value, root_current->rigth_son);
    }

    node* tree_Minimum(node* root_current) {
        node* curs = root_current;
        while (curs && curs->left_son)
            curs = curs->left_son;
        return curs;
    }

    node* tree_Maximum(node* root_current) {
        node* curs = root_current;
        while (curs && curs->rigth_son)
            curs = curs->rigth_son;
        return curs;
    }

    node* tree_Successor(node* root_current) {
        if (root_current->rigth_son)
            return tree_Minimum(root_current->rigth_son);
        node* y = root_current->father;
        while (y && root_current == y->rigth_son) {
            root_current = y;
            y = y->father;
        }
        return y;
    }

    void transplant(node* u, node* v) {
        if (!u->father) {
            root = v;
        } else if (u == u->father->left_son) {
            u->father->left_son = v;
        } else {
            u->father->rigth_son = v;
        }
        if (v) {
            v->father = u->father;
        }
    }

    void remove(node* e) {
        if (!e) return;
        if (!e->left_son) {
            transplant(e, e->rigth_son);
        } else if (!e->rigth_son) {
            transplant(e, e->left_son);
        } else {
            node* aux = tree_Minimum(e->rigth_son);
            if (aux->father != e) {
                transplant(aux, aux->rigth_son);
                aux->rigth_son = e->rigth_son;
                aux->rigth_son->father = aux;
            }
            transplant(e, aux);
            aux->left_son = e->left_son;
            aux->left_son->father = aux;
        }
        delete e;
    }

    void print_in_order(node* init) {
        if (!init) {
            cout << "Nada" << endl;
            return;
        }
        if (init->left_son) print_in_order(init->left_son);
        cout << init->value << " ";
        if (init->rigth_son) print_in_order(init->rigth_son);
    }
};

class AVL : public BST {
public:
    int height(node* curr_root) {
        if (!curr_root) return 0;
        int right = 0;
        int left = 0;
        if (curr_root->rigth_son)
            right = 1 + height(curr_root->rigth_son);
        if (curr_root->left_son)
            left = 1 + height(curr_root->left_son);

        return max(left, right);
    }

    int balancing_factor(node* curr_root) {
        if (!curr_root) return 0;
        int bf_Right = 0;
        int bf_Left = 0;
        if (curr_root->rigth_son)
            bf_Right = height(curr_root->rigth_son);
        if (curr_root->left_son)
            bf_Left = height(curr_root->left_son);
        return (bf_Left - bf_Right);
    }

    void turn_left(node*& curr_root) {
        node* new_root = curr_root->rigth_son;
        node* son_left_new_root = new_root->left_son;

        new_root->left_son = curr_root;
        curr_root->rigth_son = son_left_new_root;

        if (son_left_new_root) {
            son_left_new_root->father = curr_root;
        }
        new_root->father = curr_root->father;
        curr_root->father = new_root;

        curr_root = new_root;
    }

    void turn_right(node*& curr_root) {
        node* new_root = curr_root->left_son;
        node* son_right_new_root = new_root->rigth_son;

        new_root->rigth_son = curr_root;
        curr_root->left_son = son_right_new_root;

        if (son_right_new_root) {
            son_right_new_root->father = curr_root;
        }
        new_root->father = curr_root->father;
        curr_root->father = new_root;

        curr_root = new_root;
    }

    void rebalance(node*& curr_root) {
        int bf = balancing_factor(curr_root);
        if (bf > 1) {
            if (balancing_factor(curr_root->left_son) < 0) {
                turn_left(curr_root->left_son);
            }
            turn_right(curr_root);
        } else if (bf < -1) {
            if (balancing_factor(curr_root->rigth_son) > 0) {
                turn_right(curr_root->rigth_son);
            }
            turn_left(curr_root);
        }
    }

    void insert(int value) {
        node* new_node = new node{value, nullptr, nullptr, nullptr};
        tree_insert(new_node);
        rebalance(root);
    }
    void print_tree(){
        print_in_order(root);
    }
};

int main() {
    AVL my_tree;

    // Inserindo valores na árvore AVL
    my_tree.insert(10);
    my_tree.insert(20);
    my_tree.insert(30);
    my_tree.insert(40);
    my_tree.insert(50);
    my_tree.insert(25);

    cout << "Árvore AVL em ordem:" << endl;
    my_tree.print_tree();
    cout << endl;

    return 0;
}
