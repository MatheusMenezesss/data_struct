#include<iostream>

using namespace std;

struct node{
    int value;
    node* father;
    node* left_son;
    node* rigth_son; 
};
class tree{
    private:
        node* root;
    protected:

    public:
        tree(){
            root = nullptr;
        }
        void tree_insert(node* node_insert){
            node* node_aux = nullptr; //elemento de referência para o ultimo node valido 
            node* curs = root; //referencia o proximo elemento
            while (curs) //se curs == null, ent node_aux é uma folha e n será atualizado para null pois a interação n ocorrerá!
            {
                node_aux = curs;
                if(node_insert->value < curs->value) 
                    curs = curs->left_son;
                else
                    curs = curs->rigth_son;
            }
            node_insert->father = node_aux;
            if(!node_aux) root = node_insert; //se a tree estiver vazia, o elemento inserido sera a raiz(root)
            else if(node_insert->value > node_aux->value)
                node_aux->rigth_son = node_insert;  
            else
                node_aux->left_son = node_insert;
        }

        node* tree_search(int wanted_value, node* root_current){
            if(!root_current or root_current->value == wanted_value)
                return root_current;
            else if(wanted_value < root_current->value)
                tree_search(wanted_value, root_current->left_son);
            else
                tree_search(wanted_value, root_current->rigth_son);
        }
        node* tree_Minimum(node* root_current){
            node* curs = root_current;
            while (curs)
                curs = curs->left_son;
            return curs;
            
        }
        node* tree_Maximum(node* root_current){
            node* curs = root_current;
            while (curs)
            {
                curs = curs->rigth_son;
            }
            return curs;
        }
        node* tree_Succerssor(node* root_current){
            if(root_current->rigth_son)
                return tree_Minimum(root_current);
        }

};
int main(){


    return 0;
}
