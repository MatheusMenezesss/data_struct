#include<iostream>
#include<string>
#include<climits> // Para usar INT_MAX

using namespace std;

struct node
{
    bool value;    // Indica se existe uma conexão entre dois vértices
    bool visited;  // Indica se o vértice já foi visitado
};

struct node_queue{
    int x = -1;
    node_queue *next = nullptr;
};

class fila{
    private:
        node_queue *head = nullptr;
        node_queue *tail = nullptr;
    public:
    void enqueue(int x){
        // Enfileirar
        node_queue *aux = new node_queue;
        aux->x = x;
        aux->next = nullptr;

        if(!head){
            head = aux;
            tail = aux;
        } else {
            tail->next = aux;
            tail = aux;
        }
    }

    node_queue* dequeue(){
        if(!head) return nullptr;
        
        node_queue *aux = head;
        head = head->next;
        return aux;
    }

    bool isEmpty() {
        return head == nullptr;
    }

    void finalizar(){
        node_queue *aux = head;
        if(aux){
            int i = 0;
            while (aux){
                cout << "Elemento " << i++ << " : " << aux->x << endl;
                aux = aux->next;
            }
        } else {
            cout << "Não existem elementos na fila!" << endl;
        }
    }
};


class grafo{
    private:
        int size;
        node** conections;
        int melhorCaminho;  // Armazena o número mínimo de passos até o destino

        void dfs_util(int atual, int destino, int passos) {
            // Marca o nó atual como visitado
            conections[atual][atual].visited = true;

            // Se o nó atual for o destino, verifica se o caminho é o melhor
            if (atual == destino) {
                if (passos < melhorCaminho) {
                    melhorCaminho = passos;
                }
            } else {
                // Percorre os nós adjacentes
                for (int i = 0; i < size; i++) {
                    // Se há uma conexão e o nó adjacente não foi visitado
                    if (conections[atual][i].value && !conections[i][i].visited) {
                        dfs_util(i, destino, passos + 1);  // Incrementa o número de passos
                    }
                }
            }

            // Desmarca o nó como visitado para permitir outros caminhos (backtracking)
            conections[atual][atual].visited = false;
        }

    public:
        grafo(int n){
            this->size = n;
            this->conections = new node*[n];
            for(int i = 0; i < n; i++){
                conections[i] = new node[n];
                for(int j = 0; j < n; j++){
                    conections[i][j].value = false;
                    conections[i][j].visited = false;
                }
            }
            melhorCaminho = INT_MAX;  // Inicializa com um valor muito grande
        }

        void add_edges(int i, int j){
            conections[i][j].value = true;
            conections[j][i].value = true;
        }

        void sub_edges(int i, int j){
            conections[i][j].value = false;
            conections[j][i].value = false;
        }

        void visu_graf(){
            for(int i = 0; i < size; i++){
                for(int j = 0; j < size; j++){
                    cout << conections[i][j].value << " ";
                }
                cout << endl;
            }
        }

        void bfs(int inicio, int destino) {
            fila q;
            int *distancias = new int[size]; // Para armazenar as distâncias

            // Inicializa todas as distâncias como infinitas (INT_MAX)
            for(int i = 0; i < size; i++) {
                distancias[i] = INT_MAX;
            }
            distancias[inicio] = 0;  // Distância do início para ele mesmo é 0

            // Coloca o nó inicial na fila e marca como visitado
            q.enqueue(inicio);
            conections[inicio][inicio].visited = true;

            // Processa a fila
            while (!q.isEmpty()) {
                node_queue *atual = q.dequeue();
                int v = atual->x;

                // Para cada nó adjacente a 'v'
                for (int i = 0; i < size; i++) {
                    if (conections[v][i].value && !conections[i][i].visited) {
                        q.enqueue(i);
                        conections[i][i].visited = true;
                        distancias[i] = distancias[v] + 1;  // Atualiza a distância

                        // Se o destino for encontrado, imprime o resultado
                        if (i == destino) {
                            cout << "Caminho mais curto de " << inicio << " para " << destino << " tem " << distancias[i] << " passos." << endl;
                            return;
                        }
                    }
                }
            }

            // Se o destino não for encontrado
            cout << "Caminho impossível de " << inicio << " para " << destino << endl;
        }

        void dfs(int inicio, int destino){
            melhorCaminho = INT_MAX;  // Reseta o melhor caminho

            // Reseta os vértices visitados antes de começar a DFS
            for(int i = 0; i < size; i++) {
                for(int j = 0; j < size; j++) {
                    conections[i][j].visited = false;
                }
            }

            dfs_util(inicio, destino, 0);  // Começa a busca em profundidade

            if (melhorCaminho == INT_MAX) {
                cout << "Caminho impossível de " << inicio << " para " << destino << endl;
            } else {
                cout << "Melhor caminho de " << inicio << " para " << destino << " tem " << melhorCaminho << " passos." << endl;
            }
        }
};

int main(){
    grafo teste(5);
    teste.add_edges(0, 1);
    teste.add_edges(0, 2);
    teste.add_edges(1, 3);
    teste.add_edges(2, 3);
    teste.add_edges(3, 4);

    cout << "Matriz de adjacência do grafo:" << endl;
    teste.visu_graf();

    cout << "\nBuscando o melhor caminho de 0 para 4 com DFS:" << endl;
    teste.dfs(0, 4);  // Executa DFS para encontrar o melhor caminho de 0 até 4

    cout << "\nBuscando o melhor caminho de 0 para 4 com BFS:" << endl;
    teste.bfs(0, 4);  // Executa BFS para encontrar o caminho mais curto de 0 até 4

    return 0;
}
