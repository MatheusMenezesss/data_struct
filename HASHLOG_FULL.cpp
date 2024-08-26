#include <iostream>
#include <string>

using namespace std;

struct HashLOG {
    long int ip, timestamps;
};

bool r_verif = false;

class HLOG {
public:
    HashLOG* clients;
    int size_curr;
    int index;

    HLOG() {
        clients = new HashLOG[1000];
        size_curr = 1000;
        index = 0;
    }

    ~HLOG() {
        delete[] clients;
    }

    void merge(HashLOG* vec, int init, int middle, int end) {
        int size_vec = end - init + 1;
        int a_index = init, b_index = middle + 1;
        HashLOG* aux = new HashLOG[size_vec];
        int i = 0;

        while (a_index <= middle && b_index <= end) {
            if (vec[a_index].timestamps <= vec[b_index].timestamps) {
                aux[i].timestamps = vec[a_index].timestamps;
                aux[i].ip = vec[a_index].ip;
                i++; a_index++;
            }
            else {
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

    void mergeSort(HashLOG* vec, int initV, int endV) {
        if (initV < endV) {
            int middle = initV + (endV - initV) / 2;
            mergeSort(vec, initV, middle);
            mergeSort(vec, middle + 1, endV);
            merge(vec, initV, middle, endV);
        }
    }

    void feed_vector() {
        int old_size = size_curr;
        size_curr = 2 * size_curr + 1;
        HashLOG* new_vector = new HashLOG[size_curr];

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
        }
        else {
            cout << clients[e].ip << " " << e << endl;
        }
    }

    void PRT_SERVER() {
        for (int i = 0; i < index; i++) {
            cout << "ELEMENTO: " << i << " IP: " << clients[i].ip << " TIMESTAMPS: " << clients[i].timestamps << endl;
        }
    }
};

struct tables_elements {
    HLOG clients;
    bool verif = false;
    int nume_clients = 0;
};

class HashTable {
private:
    tables_elements* table;
    int size;
    int numElements;
    float charge_value = 0;

    void rehash() {
        int oldSize = size;
        size = 2 * size + 1;
        tables_elements* oldTable = table;

        table = new tables_elements[size];
        numElements = 0; // Reiniciar o número de elementos, será recontado durante a reinserção

        for (int i = 0; i < oldSize; i++) {
            if (oldTable[i].verif) {
                for (int j = 0; j < oldTable[i].clients.index; j++) {
                    r_verif = true;
                    insert(oldTable[i].clients.clients[j].ip, oldTable[i].clients.clients[j].timestamps);
                }
            }
        }

        delete[] oldTable;
    }

public:
    HashTable(int& n_table, float& new_chargeValue) {
        size = n_table;
        table = new tables_elements[size];
        charge_value = new_chargeValue;
        numElements = 0;
    }

    ~HashTable() {
        delete[] table;
    }

    int hash(long int key) {
        return key % size;
    }

    void insert(long int ip, long int timestamps) {
        if ((float)(numElements + 1) / size > charge_value) {
            rehash();
        }

        int index = hash(timestamps);
        if (!table[index].verif) table[index].verif = true;
        table[index].clients.ADD(ip, timestamps);
        table[index].nume_clients++;
        numElements++;
        if (!r_verif)
            cout << index << " " << table[index].clients.index << endl;
    }

    void display() {
        for (int i = 0; i < size; i++) {
            cout << "Posição " << i << ":\n";
            table[i].clients.PRT_SERVER();
        }
    }

    void QRY_HASH(long int& inp) {
        int a = hash(inp);
        table[a].clients.QRY(inp);
    }
};

int main() {
    string operacao;
    long int timestamps;
    int size_t;
    float charge_fact;

    cin >> size_t >> charge_fact;
    HashTable server(size_t, charge_fact);

    while (cin >> operacao && operacao != "END") {
        if (operacao == "QRY") {
            cin >> timestamps;
            server.QRY_HASH(timestamps);
        }
        else if (operacao == "NEW") {
            long int new_ip;
            cin >> timestamps >> new_ip;
            server.insert(new_ip, timestamps);
        }
        else if (operacao == "PRT") {
            server.display();
        }
    }

    return 0;
}
