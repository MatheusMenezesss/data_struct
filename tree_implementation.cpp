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
    public:
        tree(){
            root = nullptr;
        }
        node* root_return(){
            return root;
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
            while (curs && curs->left_son)
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
        void transplant(node* u, node* v){
            if(!u->father){
                root = v;
            }else if(u == u->father->left_son){
                u->father->left_son = v;
            }else{
                u->father->rigth_son = v;
            }
            if(!v){
                v->father = u->father;
            }
        }

        node* remove(node* e){
            if(!e) return nullptr;
            if(!e->left_son){ 
                transplant(e, e->rigth_son);
            }else if(!e->rigth_son){
                 transplant(e, e->rigth_son);
            }else{
                node* aux = tree_Minimum(e->rigth_son);
                if (aux->father != e){
                    transplant(aux, aux->rigth_son);
                    aux->rigth_son = e->rigth_son;
                    aux->rigth_son->father = aux; 
                }
                transplant(e, aux);
                aux->rigth_son = e->rigth_son;
                aux->left_son->father = aux;
            }
            delete e;
        }
        void printa_arvore_EmOrdem(node* init){
            node* e = init;
            if(!init){
                cout<<"Nada"<<endl;
            }
            if(init->left_son) printa_arvore_EmOrdem(init->left_son);
            cout<<init->value<<" ";
            if(init->rigth_son) printa_arvore_EmOrdem(init->rigth_son);
        }

};
int main(){
    tree my_tree;
    int aux = 0;
    cin>>aux;
    for(aux; aux > 0; aux--){
        node* new_element= new node;
        int x;
        cout<<"Qual o valor do elemento? : ";
        cin>>x;
        new_element->value = x;
        new_element->father = nullptr;
        new_element->left_son = nullptr;
        new_element->rigth_son = nullptr;
        my_tree.tree_insert(new_element);
    }
    cout<<endl;
    my_tree.printa_arvore_EmOrdem(my_tree.root_return());
    cout<<endl;
    node *e = my_tree.tree_search(60, my_tree.root_return());
    if(!e) cout<<"elemento n existe";
    else{
        cout<<"Elemento: "<<e->value<<endl;
        my_tree.remove(e);
    }
    my_tree.printa_arvore_EmOrdem(my_tree.root_return());
    cout<<endl;
    return 0;
}
