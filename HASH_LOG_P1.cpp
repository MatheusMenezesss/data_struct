#include<iostream>
#include<string>
#include<cstring>

using namespace std;
/*
    a ideia aqui é criar uma hash table ordenada pelo valor de timestamps
    os elementos apontam para uma nova hash table que está ordenada pelo valor de ip
    está dará acesso aos elementos que estarão nu vetor dinámico ordenado por mergesort
    e são encontrados através de binary search
*/ 
class HLOG{
    private:
        int *ip_vector;
        int size_curr;
        int index;
        int number_space_all;
        HLOG(){
            ip_vector = nullptr;
            size_curr = 0;
            number_space_all = 0;
            index = 0;
        }

    public:
        void merge(int* vec ,int init, int middle, int end){
            int size_vec = end - init + 1;
            int a_index = init, b_index = middle + 1;
            int *aux = new int[size_vec];

            int i = 0;

            while(a_index <= middle && b_index <= end){
                if(vec[a_index] <= vec[b_index]){
                    aux[i++] = vec[a_index++];
                } else {
                    aux[i++] = vec[b_index++];
                }
            }

            while(a_index <= middle){
                aux[i++] = vec[a_index++];
            }

            while(b_index <= end){
                aux[i++] = vec[b_index++];
            }

            for(i = 0; i < size_vec; i++){
                vec[init + i] = aux[i];
            }

            delete []aux;
        }

        void mergeSort(int* vec, int initV, int endV){
            if(initV < endV){
                int meddle = initV + (endV - initV) / 2;
                mergeSort(vec, initV, meddle);
                mergeSort(vec, meddle + 1, endV);
                merge(vec, initV, meddle, endV);
            }
        }
        void feed_vector(){
            number_space_all = 2*size_curr + 1;
            int *new_vector = new int[2*size_curr + 1];
            int i;
            for( i = 0; i < size_curr; i++){
                new_vector[i] = ip_vector[i];
            }
            for(i; i < number_space_all; i++){
                new_vector[i] = 0;
            }
            delete []ip_vector;
            ip_vector = new_vector;
        }
        void ADD(int &new_value){
            if(index == size_curr) feed_vector;
            ip_vector[index] = new_value;
            index++;
            mergeSort(ip_vector, 0, index);
        }
        int binary_Search(int init, int end, int &value){
            if (init > end) {
                return -1; // Elemento não encontrado
            }
            int e = init + (end - init) / 2;
            if(ip_vector[e] == value) {
                return e; // Elemento encontrado
            }
            else if(value < ip_vector[e]) {
                return binary_Search(init, e - 1, value); // Busca na metade esquerda
            }
            else {
                return binary_Search(e + 1, end, value); // Busca na metade direita
            }

        }


};
class HASH{
    private:
        int *hashTable;



    public:
};

int main(){
    string operacao; int timestamps;
    do{
        cin>>operacao;
        if(operacao != "END"){
            if(operacao == "QRY"){
                cout<<" AAAAAAAA"<<endl;

            }else if(operacao == "NEW"){
                cout<<"BBBBBBBBB"<<endl;
            }
        }else{
            cout<<"CABO!!"<<endl;
        }

    }while(operacao != "END");
    return 0;
}
