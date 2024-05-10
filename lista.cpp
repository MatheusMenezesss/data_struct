#include <iostream>
#include <string>

using namespace std;

struct nos{
    int x = -1;
    nos *next = nullptr;
};

class fila{
    private:
        nos *head = nullptr;
        nos *tail = nullptr;
    public:
    void enqueue(int x);
    nos* dequeue();
    void finalizar(){
        nos *aux = head;
        if(aux){
            int i = 0;
            while (aux){
                cout<<"elemento "<<i++<<" : "<<aux->x<<endl;
                aux = aux->next;
            }
        }else cout<<"nao existem elementos na fila!!!"<<endl;
    }
};


int main(){
    fila fila_object;
    char carac_aux;
    do{
        cout<<"adicionar no? (s/n): ";
        cin>>carac_aux;
        if(carac_aux != 'n' and carac_aux != 'N'){
            int x = 0;
            cout<<"numero a adicionar no novo no: "; cin>>x;
            fila_object.enqueue(x);
        }
        else fila_object.finalizar();
    }while(carac_aux != 'n' or carac_aux != 'N');

    return 0;
}

void fila::enqueue(int x){
    //enfileirar
    nos *aux = new nos;
    aux->next = nullptr;
    aux->x = x;
    if(head){
        nos **atual = &head;
        while ((*atual)->next){
            *atual = (*atual)->next;
        }
        (*atual)->next = aux;
    }else{
        head = aux;
        tail = aux->next;
    }
}

nos* fila::dequeue(){
    nos *aux = head;
    if(aux){
        head = head->next;
        return aux;
    }
    return nullptr;
}
