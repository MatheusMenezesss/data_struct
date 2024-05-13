#include <iostream>
#include <string>

using namespace std;

typedef struct data
{
    string n;
    data *next;
}DATA;

class stack{
    private:
        int elemen_number = 0;
        DATA *head;
    public:
        bool test_sintax(); // verifica se existem duas pedra seguidas de msm valor
        void push(string n); // adiciona a pedra de numero n a stack
        DATA* pop();  // remove elemento
        int stack_empty(); //verifica se a stack esta vazia
};

int main(){
    int p; //numero de partidas
    cin>>p;
    for(int i = 0; i < p; i++){
        string final_condition = "END";


    }


    return 0;
}

bool stack::test_sintax(){
    if(!stack_empty()){
        return false;
    }

    if(stack_empty()){}
}

void stack::push(string n){
    DATA *aux = new DATA;
    aux->n = n;
    if(!stack_empty()){
        head = aux;
    }else{
        aux->next = head;
        head = aux;
    }
    elemen_number++;
}

DATA *stack::pop(){
    if(stack_empty()){
        DATA *aux = head;
        head = head->next;
        elemen_number--;
        return aux;
    }else{
        return nullptr;
    }

}

int  stack::stack_empty(){
    return elemen_number;
}
