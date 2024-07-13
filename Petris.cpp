/*
    obs: algum loop infinito
    debugar
*/
#include <iostream>
#include <string>

using namespace std;

struct rock{
    string value;
    rock* next;
};

class petris{
    private:
       rock *head;
       int num_element;
    public:
    petris(){
        head = nullptr;
        num_element = 0;
    }
    bool stackempty(){if(head) return false; else return true;}

    void push(char args[]);
    rock *pop();
    bool equal_elements(char value[]){
        if(stackempty()) return false;
        if(value == head->value) return true;
        else return false;
    }
    void end_game(){
        cout<<num_element<<" ";
        if(head){
            cout<<head->value;
        }else cout<<"-1";
        rock *assistant;
        while (head)
        {
            assistant = pop();
            delete assistant;
        }
        num_element = 0;
    }

    void verifica_stack(){
        rock* assitant = head;
        cout<<"num de elementos atual: "<< num_element<<"lita atual:"<<endl;
        if(assitant) cout<<"LISTA Vazia!!"<<endl;
        while (assitant){
            cout<<assitant->value<<endl;
            assitant = assitant->next;
        }
        cout<<"FINAL DA STACK"<<endl;
    }
};
class full_petris{
    private:
        petris** columns;
        int full_columns_number;
    public:
        void add_column_Right(){
            petris* new_columns = new petris[++full_columns_number];
            for(int i = 0; i < (full_columns_number - 1); i++){
                new_columns[i] = *columns[i];
            }
            *columns = new_columns;
        }
        void add_column_Left(){
            petris* new_columns = new petris[++full_columns_number];
            for(int i = 1; i < full_columns_number; i++){
                new_columns[i] = *columns[i];
            }
            *columns = new_columns;
        }
        petris* remove_column(int index){
            petris* new_columns = new petris[full_columns_number - 1];
            petris* aux;
            for(int i = 0; i < full_columns_number; i++){
                if(i != index)
                    new_columns[i] = *columns[i];
                else aux = columns[i]; //obs:aux apontando para um ponteiro de ponteiro
            }
            *columns = new_columns;
            return aux;
        }
        void add_rock(char *aux, int index){
            rock* cur;
            if(index == 0){
                add_column_Left();
                    columns[0]->push(aux);

            }else if(index >= full_columns_number){
                add_column_Right();
                    columns[full_columns_number]->push(aux);

            }else{
                if(columns[index]->equal_elements(aux)){
                    cur = columns[index]->pop();
                    delete cur;
                }else{
                    columns[index]->push(aux);
                }
            }
        }
        full_petris(){
            columns = nullptr;
            full_columns_number = 0;
        }
};
void match(petris *arg);
int i;
int main(){
    int num_matches = 0;
    cin>>num_matches;
    petris commence;
    for(i = 0; i < num_matches; i++){
        match(&commence);
    }
    return 0;
}

void petris::push(char args[]){
    rock *nw_elemen = new rock;
    nw_elemen->value = args;
    if(stackempty()){
        nw_elemen->next = nullptr;
        head = nw_elemen;
    }else{
        nw_elemen->next = head;
        head = nw_elemen;
    }
    num_element++;
    //cout<<"adiciona elemento:"<<endl;
    //verifica_stack();
}

rock *petris::pop(){
    if(!stackempty()){
        rock *remove = head;
        head = head->next;
        num_element--;
        //cout<<"exclui elemento:"<<endl;
        //verifica_stack();
        return remove;
    }

    return nullptr;
}

void match(petris *arg){
    string caracter = " ";
    petris *col = nullptr;
    full_petris full_columns; 
    int index, index_number;
    rock* curs;
    while (caracter != "END")
    {
        cin>>index>>caracter;
        if(caracter != "END"){
            char *aux = &caracter[0];
            full_columns.add_rock(aux, index);
        }
    }
    cout<<"caso "<<i<<": ";
    arg->end_game();
    cout<<endl;
}
