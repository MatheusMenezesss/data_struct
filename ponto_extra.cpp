#include<iostream>
#include<cstdlib>
#include<cstring>


using namespace std;
#define par_fecha ')'

struct stack{
    char value;
    stack *next = nullptr;
};

struct lista{
    char value;
    lista *proximo = nullptr;
    lista *anterior = nullptr;
};

class expr{
    private:
        stack* topo_pilha;
        lista* head;
    public:
        stack* pop();
        void push(char caracter);
        void bota_na_lista(char caracter){
            lista *cur = head;
            while (cur->proximo)
            {
                cur = cur->proximo;
            }            
            lista *e = new lista;
            e->value = caracter;
            e->proximo = nullptr;
            e->anterior =  cur;
            cur->proximo = e;
        }
        lista* tira_da_lista;
        bool stack_empty(){
            if(topo_pilha) return true;
            else return false;
        }
        float printa_lista(){
            lista *e = head;

            while (e != nullptr)
            {
                if(e->value < 48 and e->value > 57){                    
                    if(e->value == '+'){
                        float a = e->anterior->value;
                        int b = e->anterior->anterior->value;
                        return (b+a);
                    }else if(e->value == '-'){
                        float a = e->anterior->value;
                        int b = e->anterior->anterior->value;
                        return (b-a);

                    }else if(e->value == '/'){
                        float a = e->anterior->value;
                        int b = e->anterior->anterior->value;
                        return (b/a);

                    }else if(e->value == '*'){
                        float a = e->anterior->value;
                        int b = e->anterior->anterior->value;
                        return (b*a);
                    }
                }
                e = e->proximo;
            }
            return 0;
            
        }
};

int main(){
    string palavra;
    char * letras;
    expr calculo;
    cin>>palavra;
    int tam = palavra.size();
    letras = &palavra[0];
    for(int i = 0; i < tam; i++){
        if(letras[i] < 48 and letras[i] > 57 ){
            //adic na pilha
            calculo.push(letras[i]);

        }else{
            //adic na fila
            if(letras[i] == par_fecha){
                stack* aux;
                do{
                    aux = calculo.pop();
                    calculo.bota_na_lista(aux->value);
                }while(aux);
                
            }
            else
                calculo.bota_na_lista(letras[i]);

        }
    }
    float resposta = calculo.printa_lista();
    cout<<"resposta: "<<resposta<<endl;
}

stack* expr::pop(){
    if(stack_empty()){
        return nullptr;
    }
    stack* e = topo_pilha;
    topo_pilha = topo_pilha->next;
    return e;
}

void expr::push(char caracter){
        stack* e = new stack;
        e->value = caracter;
        e->next = topo_pilha;
        topo_pilha = e;
}
