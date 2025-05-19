#include <bits/stdc++.h>
using namespace std;

// Implementação do algoritimo Kruskal para o Problema da Árvore Geradora Mínima (AGM) //

struct Aresta{

    int u, v, peso;
    bool operator<(const Aresta& outra) const{

        return peso < outra.peso;
    }
};

// Union-Find (DSU) // 
struct DSU{
    vector<int> parent, rank;
    
    DSU(int n){

        parent.resize(n+1);
        rank.resize(n+1, 0);
        for (int i = 1; i <= n; i++)
            parent[i] = i;
    }
    
    int find(int u){
        return parent[u] == u ? u : parent[u] = find(parent[u]);
    }
    
    void unite(int u, int v){

        u = find(u), v = find(v);
        if (rank[u] > rank[v]) parent[v] = u;
        else{

            parent[u] = v;
            if (rank[u] == rank[v]) rank[v]++;
        }
    }
};

int main(int argc, char* argv[]){

    string input_file, output_file;
    bool show_solution = false;

    for (int i = 1; i < argc; i++){

        if (!strcmp(argv[i], "-h")){

            cout << "Help:" << endl;
            cout << "-h : mostra o help" << endl;
            cout << "-o <arquivo> : redireciona a saida para o \"arquivo\"" << endl;
            cout << "-f <arquivo> : indica o \"arquivo\" que contém o grafo de entrada" << endl;
            cout << "-s : mostra a solução (árvore geradora mínima)" << endl;
            return 0;
        }
        if (!strcmp(argv[i], "-o") && i < argc - 1) output_file = argv[++i];
        if (!strcmp(argv[i], "-f") && i < argc - 1) input_file = argv[++i];
        if (!strcmp(argv[i], "-s")) show_solution = true;
    }

    if (input_file.empty()){

        cerr << "Arquivo de entrada não especificado. Use -f" << endl;
        return 1;
    }

    ifstream fin(input_file);
    if (!fin){

        cerr << "Erro ao abrir arquivo de entrada" << endl;
        return 1;
    }

    int n, m;
    fin >> n >> m;
    vector<Aresta> arestas(m);

    for (int i = 0; i < m; i++){

        fin >> arestas[i].u >> arestas[i].v >> arestas[i].peso;
    }
    fin.close();

    sort(arestas.begin(), arestas.end());
    DSU dsu(n);
    int custo_total = 0;
    vector<Aresta> arvore;

    for (auto& aresta : arestas){

        if (dsu.find(aresta.u) != dsu.find(aresta.v)){

            dsu.unite(aresta.u, aresta.v);
            custo_total += aresta.peso;
            arvore.push_back(aresta);
        }
    }

    ostream& out = output_file.empty() ? cout : *(new ofstream(output_file));
    if (!output_file.empty() && !((ofstream&)out).is_open()){

        cerr << "Erro ao criar arquivo de saída" << endl;
        return 1;
    }

    if (show_solution){

        for (auto& aresta : arvore){

            out << "(" << aresta.u << "," << aresta.v << ") ";
        }
        out << endl;
    } else{
        out << custo_total << endl;
    }

    if (!output_file.empty()){

        ((ofstream&)out).close();
        delete &out;
    }

    return 0;
}