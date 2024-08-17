#include<iostream>
#include<string>
#include<cstring>

using namespace std;

struct HashLOG
{
    long int ip, timestamps;
};

class HLOG{
private:
    HashLOG *clients;
    int size_curr;
    int index;

public:
    HLOG(){
        clients = new HashLOG[1000];
        size_curr = 1000;
        index = 0;
    }
    ~HLOG(){
        delete []clients;
    }

    void merge(HashLOG* vec ,int init, int middle, int end){
        int size_vec = end - init + 1;
        int a_index = init, b_index = middle + 1;
        HashLOG *aux = new HashLOG[size_vec];
        int i = 0;

        while(a_index <= middle && b_index <= end){
            if(vec[a_index].timestamps <= vec[b_index].timestamps){
                aux[i].timestamps = vec[a_index].timestamps;
                aux[i].ip = vec[a_index].ip;
                i++; a_index++;
            } else {
                aux[i].timestamps = vec[b_index].timestamps;
                aux[i].ip = vec[b_index].ip;
                i++; b_index++;
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

    void mergeSort(HashLOG *vec, int initV, int endV){
        if(initV < endV){
            int meddle = initV + (endV - initV) / 2;
            mergeSort(vec, initV, meddle);
            mergeSort(vec, meddle + 1, endV);
            merge(vec, initV, meddle, endV);
        }
    }

    void feed_vector(){
        int old_size = size_curr;
        size_curr = 2*size_curr + 1;
        HashLOG *new_vector = new HashLOG[size_curr];

        for(int i = 0; i < old_size; i++){
            new_vector[i] = clients[i];
        }

        delete []clients;
        clients = new_vector;
    }

    void ADD(long int new_ip, long int new_timestamps){
        if(index == size_curr) feed_vector();
        int i;
        for (i = index - 1; i >= 0 && clients[i].timestamps > new_timestamps; i--) {
            clients[i + 1] = clients[i];
        }

        clients[i + 1].ip = new_ip;
        clients[i + 1].timestamps = new_timestamps;
        index++;
    }

    int binary_Search(int init, int end, long int value){
        while(init <= end){
            int e = init + (end - init) / 2;
            if(clients[e].timestamps == value) return e;
            else if(value < clients[e].timestamps) end = e - 1;
            else init = e + 1;
        }
        return -1;
    }

    void QRY(long int& timestamps){
        //mergeSort(clients, 0, index - 1);
        int e =  binary_Search(0, index - 1, timestamps);
        if(e == -1){
            cout<<"-1 -1"<<endl;
        } else {
            cout<<clients[e].ip<<" "<<e<<endl;
        }
    }

    void PRT_SERVER(){
        for(int i = 0; i < index; i++){
            cout<<"ELEMENTO: "<<i<<" IP: "<<clients[i].ip<<" TIMESTAMPS: "<<clients[i].timestamps<<endl;
        }
    }
};

int main(){
    string operacao; 
    long int timestamps;
    HLOG server;
    do{
        cin>>operacao;
        if(operacao != "END"){
            if(operacao == "QRY"){
                cin>>timestamps;
                server.QRY(timestamps);
            }else if(operacao == "NEW"){
                long int new_ip;
                cin>>timestamps; 
                cin>>new_ip;
                server.ADD(new_ip, timestamps);
            }else if(operacao == "PRT"){
                server.PRT_SERVER();
            }
        }

    }while(operacao != "END");
    return 0;
}
