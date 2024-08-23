#include <iostream>
#include <string>
#include <cstring>

using namespace std;




struct HashLOG {
    long int ip, timestamps;
};

class HLOG {
protected:
    HashLOG *clients;
    int size_curr;
    int index;

public:
    HLOG() {
        clients = new HashLOG[10000];
        size_curr = 10000;
        index = 0;
    }
    ~HLOG() {
        delete[] clients;
    }

    void merge(HashLOG* vec, int init, int middle, int end) {
        int size_vec = end - init + 1;
        int a_index = init, b_index = middle + 1;
        HashLOG *aux = new HashLOG[size_vec];
        int i = 0;

        while (a_index <= middle && b_index <= end) {
            if (vec[a_index].timestamps <= vec[b_index].timestamps) {
                aux[i].timestamps = vec[a_index].timestamps;
                aux[i].ip = vec[a_index].ip;
                i++; a_index++;
            } else {
                aux[i].timestamps = vec[b_index].timestamps;
                aux[i].ip = vec[b_index].ip;
                i++; b_index++;
            }
        }

        while (a_index <= middle) {
            aux[i++] = vec[a_index++];
        }
        while (b_index <= end) {
            aux[i++] = vec[b_index++];
        }

        for (i = 0; i < size_vec; i++) {
            vec[init + i] = aux[i];
        }

        delete[] aux;
    }

    void mergeSort(HashLOG *vec, int initV, int endV) {
        if (initV < endV) {
            int meddle = initV + (endV - initV) / 2;
            mergeSort(vec, initV, meddle);
            mergeSort(vec, meddle + 1, endV);
            merge(vec, initV, meddle, endV);
        }
    }

    void feed_vector() {
        int old_size = size_curr;
        size_curr = 2 * size_curr + 1;
        HashLOG *new_vector = new HashLOG[size_curr];

        for (int i = 0; i < old_size; i++) {
            new_vector[i] = clients[i];
        }

        delete[] clients;
        clients = new_vector;
    }

    void ADD(long int new_ip, long int new_timestamps) {
        if (index == size_curr) feed_vector();
        int i;
        for (i = index - 1; i >= 0 && clients[i].timestamps > new_timestamps; i--) {
            clients[i + 1] = clients[i];
        }

        clients[i + 1].ip = new_ip;
        clients[i + 1].timestamps = new_timestamps;
        index++;
    }

    int binary_Search(int init, int end, long int value) {
        while (init <= end) {
            int e = init + (end - init) / 2;
            if (clients[e].timestamps == value) return e;
            else if (value < clients[e].timestamps) end = e - 1;
            else init = e + 1;
        }
        return -1;
    }

    void QRY(long int& timestamps) {
        int e = binary_Search(0, index - 1, timestamps);
        if (e == -1) {
            cout << "-1 -1" << endl;
        } else {
            cout << clients[e].ip << " " << e << endl;
        }
    }

    void PRT_SERVER() {
        for (int i = 0; i < index; i++) {
            cout << "ELEMENTO: " << i << " IP: " << clients[i].ip << " TIMESTAMPS: " << clients[i].timestamps << endl;
        }
    }
};

class HashTable {
private:
    HashLOG* table;
    int size;
    int numElements;
    float charge_value = 0;

    void rehash() {
        int oldSize = size;
        size = 2 * size; // Novo tamanho, geralmente dobrado
        HashLOG* oldTable = table;

        // Criar uma nova tabela com o novo tamanho
        table = new HashLOG[size];
        for (int i = 0; i < size; i++) {
            table[i].ip = -1;  // Inicializando a nova tabela
            table[i].timestamps = -1;
        }

        // Reinserir todos os elementos na nova tabela
        for (int i = 0; i < oldSize; i++) {
            if (oldTable[i].timestamps != -1) { // Verifica se há um elemento válido
                insert(oldTable[i].ip, oldTable[i].timestamps);
            }
        }

        delete[] oldTable; // Liberar a memória da antiga tabela
    }

public:
    // Construtor para inicializar a tabela
    HashTable(int m, float new_chargeValue) {
        size = m;
        table = new HashLOG[size];
        charge_value = new_chargeValue;
        numElements = 0;
        for (int i = 0; i < size; i++) {
            table[i].ip = -1; // Indicando slot vazio
            table[i].timestamps = -1; // Indicando slot vazio
        }
    }

    // Destrutor para liberar a memória alocada
    ~HashTable() {
        delete[] table;
    }

    // Função hash h(T) = T mod M
    int hash(long int key) {
        return key % size;
    }

    // Inserir um valor na tabela usando sondagem linear
    void insert(long int ip, long int timestamps) {
        // Calcular fator de carga antes de inserir
        if ((float)(numElements + 1) / size > charge_value) { // 0.6 é o limite do fator de carga
            rehash(); // Rehashing se necessário
        }

        int index = hash(timestamps);

        while (table[index].timestamps != -1) {
            index = (index + 1) % size;
        }

        table[index].ip = ip;
        table[index].timestamps = timestamps;
        numElements++; // Incrementar o número de elementos após a inserção
        cout<<index<<" ";
    }

    // Procurar um valor na tabela
    bool search(long int timestamps, HashLOG &result) {
        int index = hash(timestamps);
        int startIndex = index;

        // Sondagem linear para procurar o valor
        while (table[index].timestamps != -1) {
            if (table[index].timestamps == timestamps) {
                result = table[index];
                return true;
            }
            index = (index + 1) % size;

            // Se retornarmos ao índice de partida, o valor não está presente
            if (index == startIndex) {
                return false;
            }
        }

        return false;
    }

    // Exibir a tabela hash
    void display() {
        for (int i = 0; i < size; i++) {
            if (table[i].timestamps == -1) {
                std::cout << i << ": \n";
            } else {
                std::cout << i << ": IP: " << table[i].ip << ", Timestamps: " << table[i].timestamps << "\n";
            }
        }
    }
};

int main() {
    string operacao; 
    long int timestamps;
    HLOG server;
    int table_size_init; float table_charge_value_init;
    cin>>table_size_init>>table_charge_value_init;


    HashTable hashTable(table_size_init,table_charge_value_init); // cria a hashTable a partir do input do term

    do {
        cin >> operacao;
        if (operacao != "END") {
            if (operacao == "QRY") {
                cin >> timestamps;
                server.QRY(timestamps);
            } else if (operacao == "NEW") {
                long int new_ip;
                cin >> timestamps; 
                cin >> new_ip;
                server.ADD(new_ip, timestamps);
                hashTable.insert(new_ip, timestamps); // Inserção na tabela hash
            } else if (operacao == "PRT") {
                server.PRT_SERVER();
                hashTable.display(); // Exibição da tabela hash
            }
        }

    } while (operacao != "END");

    return 0;
}
