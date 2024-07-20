#include <iostream>
#include <string>
#include <cstring>

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
    bool stackempty(){return head == nullptr;}

    void push(char args[]);
    rock *pop();
    bool equal_elements(char value[]){
        if(stackempty()) return false;
        return head->value == value;
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
            if(e) cout<<" ";
            cout<<e->column.head->value;
            e = e->next;
        }
        cout<<endl;
    }
    void mostrar_colunas(){
        node* e = head;
        while (e)
        {
            e = e->next;
        }
    }
    node* Dequeue(node* arg){
        if(!head) return nullptr;
        if(arg->previus) arg->previus->next = arg->next;
        if(arg->next) arg->next->previus = arg->previus;
        if(arg == head) head = arg->next;
        if(arg == tail) tail = arg->previus;
        arg->next = nullptr;
        arg->previus = nullptr;
        return arg;
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
                tail = new_element;
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
                head->previus = new_element;
                head = new_element;
            }
            number_columns++;
        }else{
            node* e = head;
            for(int i = 1; i < index; i++){
                e = e->next;
            }
            if(e->column.equal_elements(arg)){
                rock* aux = e->column.pop();
                delete aux;
                if(e->column.stackempty()){
                    if(e == head){
                        head = head->next;
                    }else{
                        e = Dequeue(e);
                    }
                    delete e;
                    number_columns--;
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
}

rock *petris::pop(){
    if(!stackempty()){
        rock *remove = head;
        head = head->next;
        num_element--;
        return remove;
    }
    return nullptr;
}

int tratar_erro(char caracter[]){
    int i  = 0;
    int output = 0;
    while (caracter[i] != '\0')
    {
        if(i > 0){
            output = output*10;
            output = output + (int(caracter[i]) - 48);
        }else{
            output = (int(caracter[i]) - 48);
        }
        i++;
    }
    return output;
}

void match(){
    string caracter = " ";
    petris *col = nullptr;
    Queue full_columns;
    int index;
    string aux;
    while (caracter != "END")
    {
        cin>>aux;
        if(aux == "END"){
            break;
        }else{
            index = tratar_erro(&aux[0]);
        }
        cin>>caracter;
        if(caracter != "END"){
            char *aux = &caracter[0];
            full_columns.Enqueue(aux, index);
        }
    }
    cout<<"caso "<<i<<":";
    full_columns.END();
}
