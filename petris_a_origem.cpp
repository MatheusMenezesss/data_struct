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
    rock* curs;
    while (caracter != "END")
    {
        cin>>caracter;
        if(caracter != "END"){
            char *aux = &caracter[0];
            if(arg->equal_elements(aux)){
                curs = arg->pop();
                delete curs;
            }else{
                arg->push(aux);
            }
        }
        else{
            cout<<"AAAAAAAAAAAAAAAAA"<<endl;
        }
    }
    cout<<"lista no final:"<<endl;arg->verifica_stack();
    cout<<"caso "<<i<<": "; arg->end_game();cout<<endl;
}