#include <bits/stdc++.h>
using namespace std;

// Implementação do algoritimo Bellman-Ford para o Problema dos Caminhos Mínimos (Grafo Ponderado) //

const int INF = INT_MAX;

struct Aresta{

    int u, v, peso;
};

vector<int> bellman_ford(int n, const vector<Aresta>& arestas, int start, bool& has_negative_cycle){

    vector<int> dist(n + 1, INF);
    dist[start] = 0;
    has_negative_cycle = false;

    for (int i = 1; i <= n - 1; i++){
        for (const auto& aresta : arestas){
            if (dist[aresta.u] != INF && dist[aresta.v] > dist[aresta.u] + aresta.peso){

                dist[aresta.v] = dist[aresta.u] + aresta.peso;
            }
        }
    }

    for (const auto& aresta : arestas){

        if (dist[aresta.u] != INF && dist[aresta.v] > dist[aresta.u] + aresta.peso){

            has_negative_cycle = true;
            break;
        }
    }

    return dist;
}

int main(int argc, char* argv[]){

    string input_file, output_file;
    int start_vertex = 1;

    for (int i = 1; i < argc; i++){

        if (!strcmp(argv[i], "-h")){

            cout << "Help:" << endl;
            cout << "-h : mostra o help" << endl;
            cout << "-o <arquivo> : redireciona a saida para o \"arquivo\"" << endl;
            cout << "-f <arquivo> : indica o \"arquivo\" que contém o grafo de entrada" << endl;
            cout << "-i : vértice inicial" << endl;
            return 0;
        } 
        else if (!strcmp(argv[i], "-o") && i < argc - 1){

            output_file = argv[++i];
        } else if (!strcmp(argv[i], "-f") && i < argc - 1){

            input_file = argv[++i];
        } else if (!strcmp(argv[i], "-i") && i < argc - 1){

            start_vertex = atoi(argv[++i]);
        }
    }

    if (input_file.empty()){

        cerr << "Arquivo de entrada não especificado. Use -f" << endl;
        return 1;
    }

    ifstream fin(input_file);
    if (!fin){

        cerr << "Erro ao abrir o arquivo de entrada." << endl;
        return 1;
    }

    int n, m;
    fin >> n >> m;
    vector<Aresta> arestas(m);

    for (int i = 0; i < m; i++){

        fin >> arestas[i].u >> arestas[i].v >> arestas[i].peso;
    }
    fin.close();

    bool has_negative_cycle;
    vector<int> dist = bellman_ford(n, arestas, start_vertex, has_negative_cycle);

    ostream& out = output_file.empty() ? cout : *(new ofstream(output_file));
    if (!output_file.empty() && !((ofstream&)out).is_open()){

        cerr << "Erro ao criar arquivo de saída." << endl;
        return 1;
    }

    if (has_negative_cycle){

        out << "O grafo contém um ciclo de peso negativo alcançável a partir do vértice inicial." << endl;
    } else{
        for (int i = 1; i <= n; i++){

            if (dist[i] == INF){

                out << i << ":-1" << (i == n ? "\n" : " ");
            } else{

                out << i << ":" << dist[i] << (i == n ? "\n" : " ");
            }
        }
    }

    if (!output_file.empty()){

        ((ofstream&)out).close();
        delete &out;
    }

    return 0;
}