#include<iostream> 
#include<cstring>

using namespace std;

struct node{
    int value;
    char nipe;
    node* next;
};

class stack{
    protected:
        node* head;
    public:
        stack(){
            head = nullptr;
        }

        bool stack_empty(){
            if(!head) return true;
            else return false;
        }

        void push(int value, char nipe){
            node* e = new node;
            e->next = head;
            e->nipe = nipe;
            e->value = value;
            head = e;
        }

        node* pop(){
            if(stack_empty()){
                return nullptr;
            }else{
                node* top = head;
                head = head->next;
                return top;
            }
        }
};

class queue{
    private:
        node* head;
        node* tail;
        int size;
    public:
        queue(){
            head = nullptr;
            tail = head;
            size = 0;
        }
        ~queue(){
            node* e;
            while (e)
            {
                e = head;
                head = head->next;
                delete e;
            }
            
        }

        void Enqueue(int value, char nipe){
            if(!size){
                head = new node;
                head->next = nullptr;
                head->nipe = nipe;
                head->value = value;
                tail = head;
            }else{
                node* new_element = new node;
                new_element->next = nullptr;
                new_element->nipe = nipe;
                new_element->value = value;
                tail->next = new_element;
                tail = tail->next;
            }
            size++;
        }

        node* Dequeue(){
            node* first_element = head;
            if(!size){
                return nullptr;
            }else{
                head = head->next;
                size--;
                return first_element;
            }
        }
        void print_queue(int i){
            node* curs = head;
            cout<<"Jogador: "<< i <<endl;
            while (curs)
            {
                cout<<curs->nipe<<" "<<curs->value<<endl;
                curs = curs->next;
            }
            
        }
};
class Cuscuz : public stack{
    public:
        void PRT(){
            node* curs = head;
            while (curs)
            {
                cout<<curs->value<<curs->nipe<<" ";
                curs = curs->next;
            }
        }
        void RND(int value, char nipe){
            push(value, nipe);
        }
        void printa_stack(){
            node* curs = head;
            while (curs)
            {
                cout<<curs->value<<curs->nipe<<endl;
                curs = curs->next;
            }
        }
        void END(){
            node* e;
            while (head)
            {
                e = pop();
                delete e;
            }
            
        }
};

int count = 0; //numero da rodada

struct card_win
{
    int value = 0; // valor do campeão
    char nipe = '\0'; // nipe do campeão
    int win_player = 0;//numero do jogador que ganhou a partida
    void compared(int value_aux,char  nipe_aux, int number_player){
        if(value_aux == value){
            if(nipe < nipe_aux){
                value = value_aux;
                nipe = nipe_aux;
                win_player = number_player;
            }else if(nipe == nipe_aux){
                win_player = -1;
            }
        }else if(value_aux > value){
            value = value_aux;
            nipe = nipe_aux;
            win_player = number_player;
        }
    }
};


int main(){
    int number_players = 0;
    cin>>number_players;//rebecebe o nuero de jogadores
    Cuscuz match;
    queue players[number_players];//cria as listas de cartas para cada jogador
    char operation[4]; //palavra contendo a operação a ser feita
    do{
        cin>>operation;
        if(!strcmp(operation, "DEA")){
            match.END();
            for(int i = 0; i < number_players; i++){
                int value; char nipe;
                char input[3];
                cin>>input;
                value = int(input[0]) - 48;
                nipe = input[1];
                players[i].Enqueue(value, nipe);
            }

        }else if(!strcmp(operation, "RND")){
            match.END();
            card_win winer;
            int value; char nipe;
            for(int i = 0; i < number_players; i++){
                node* assistent = players[i].Dequeue();
                value = assistent->value;
                nipe = assistent->nipe;
                winer.compared(value, nipe, i);
                match.RND(value, nipe);
            }
            cout<<count<<" "<<winer.win_player<<endl;
            //match.printa_stack();
            count++;

        }else if(!strcmp(operation, "PRT")){
            match.PRT();
            cout<<endl;;
            match.END();

        }  else{
            match.END();
        }  
    }while(strcmp(operation, "END"));
}
