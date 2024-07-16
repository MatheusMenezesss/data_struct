#include <iostream>
#include <string>

using namespace std;

struct rock{
    string value;
    rock* next;
};

class petris{
    public:
    rock *head;
    int num_element;
    petris(){
        head = nullptr;
        num_element = 0;
    }
    ~petris(){
        rock* e = head;
        while (head)
        {
            head = head->next;
            delete e;
            e = head;
        }
        
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

struct node{
    petris column;
    node* next;
    node* previus;
};

class Queue{
    private:
        node* head;
        node* tail;
        int number_columns;
    public:
        Queue(){
            head = nullptr;
            tail = head;
            number_columns = 0;
        }
        ~Queue(){
            node* e = head;
            while (e)
            {
                head = head->next;
                delete e;
                e = head;
            }
            
        }

        void END(){
            node* e = head;
            while (e)
            {
                cout<<e->column.head->value<<" ";
                e = e->next;
            }
            cout<<endl;
            
        }
        node* Dequeue(int index){
            if(!head) return nullptr;
            node* e = head;
            for(int i = 1; i< index; i++){
                e = e->next;
            }
            node* aux = e->previus;
            aux->next = e->next;
            e->next = nullptr;
            number_columns--;
            return e;
        }
        void Enqueue(char* arg, int index){
            if(index > number_columns){
                if(!number_columns){
                    head = new node;
                    head->next = nullptr;
                    head->previus = nullptr;
                    head->column.push(arg);
                    tail = head;
                }else{
                    node* new_element = new node;
                    new_element->next = nullptr;
                    new_element->previus = tail;
                    new_element->column.push(arg);
                    tail->next = new_element;
                    tail = tail->next;
                }
                number_columns++;


            }else if(index == 0){
                if(!number_columns){
                    head = new node;
                    head->next = nullptr;
                    head->previus = nullptr;
                    head->column.push(arg);
                    tail = head;
                }else{
                    node* new_element = new node;
                    new_element->next = head;
                    new_element->previus = nullptr;
                    new_element->column.push(arg);
                    head = new_element;
                }
                number_columns++;

            }else{
                node* e = head;
                for(int i = 1; i < index; i++){
                    e = e->next;
                }
                if( e->column.equal_elements(arg)){
                    rock* aux = e->column.pop();
                    delete aux;
                    if(e->column.stackempty()){

                    }
                }else{
                    e->column.push(arg);
                }
            }
        }


};


void match();
int i;
int main(){
    int num_matches = 0;
    cin>>num_matches;
    for(i = 0; i < num_matches; i++){
        match();
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

void match(){
    string caracter = " ";
    petris *col = nullptr;
    Queue full_columns; 
    int index;
    rock* curs;
    while (caracter != "END")
    {
        cin>>index>>caracter; //index tá pegando o END
        if(caracter != "END"){
            char *aux = &caracter[0];
            full_columns.Enqueue(aux, index);
            full_columns.END();
        }
    }
    full_columns.END();
    cout<<"caso "<<i<<": ";
    cout<<endl;
}
