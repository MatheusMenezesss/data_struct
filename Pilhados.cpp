#include<iostream>

using namespace std;

#define finaled 0

struct stack
{
    int value = 0;
    stack *next = nullptr;
};

class tower{
    private:
        stack *head;
    public:
        bool stack_empty(void){
            if(head) return true;
            return false;
        }
        stack* pop(void);
        void push(int i);
        bool compared(int arg){
            if(stack_empty()){
                 return false;
            }
            if(arg%2 == head->value%2){
                return true;
            }
            return false;
        }
        void printar_torre(){
            stack* cur = head;
            while (cur)
            {
                cout<<cur->value<<endl;
                cur = cur->next;
            }
        }
        ~tower(){
            while (head)
            {
                stack* e = head;
                head = head->next;
                delete e;
            }
            
        }




};

void match();

int main(){
    int input;
    cin>>input;
    for(int i = 0; i<input; i++){
        match();
    }
    return 0;
}

void match(){
    tower column;
    int carac;
    do{
        cin>>carac;
        if(carac)
            column.push(carac);
    }while(carac);
    column.printar_torre();

}

stack* tower::pop(void){
    if(stack_empty()){
        return nullptr;
    }
    stack* e = head;
    head = head->next;
    return e;
}

void tower::push(int i){
    if(compared(i)){
        stack* old_obj = pop();
        push((old_obj->value - i));
        delete old_obj;
    }
    stack* e = new stack;
    e->value = i;
    e->next = head;
    head = e;
}
