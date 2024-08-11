#include<iostream>
#include<string>
#include<cstring>
#include<random>

using namespace std;

bool search_element(int* vec, int value_search, int size_vec){
    for(int i = 0; i < size_vec; i++){
        if(vec[i] == value_search) return true;
    }
    return false;
}

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

int main(){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100);

    int* vec;
    int tam;
    cout << "Qual o tamanho do nosso vetor?" << endl;
    cin >> tam;
    vec = new int[tam];
    int random_number = 0;
    
    for(int i = 0; i < tam;){
        random_number = dis(gen);
        if(!search_element(vec, random_number, i)){
            vec[i++] = random_number;
        }
    }

    cout << "Vetor inicial:" << endl;
    for(int i = 0; i < tam; i++){
        cout << vec[i] << " ";
    }
    cout << endl;

    mergeSort(vec, 0, tam - 1);

    cout << "Vetor ordenado:" << endl;
    for(int i = 0; i < tam; i++){
        cout << vec[i] << " ";
    }
    cout << endl;

    delete []vec;
    
    return 0;
}
