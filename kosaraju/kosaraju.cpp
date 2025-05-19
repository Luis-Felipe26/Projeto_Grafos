#include <bits/stdc++.h>
using namespace std;

// Implementação do algoritimo Kosaraju para o Problema das Componentes fortemente conexas //

vector<vector<int>> grafo, grafoT;
vector<bool> visitado;
stack<int> pilha;
vector<vector<int>> sccs;

void dfs(int u, const vector<vector<int>>& g, vector<int>* componente = nullptr){

    visitado[u] = true;
    if (componente) componente->push_back(u);
    
    for (int v : g[u]){

        if (!visitado[v]){

            dfs(v, g, componente);
        }
    }
    if (!componente) pilha.push(u);
}

void kosaraju(int n){

// DFS no grafo transposto (reverso) //
    visitado.assign(n+1, false);
    for (int i = 1; i <= n; i++){

        if (!visitado[i]){
            dfs(i, grafoT);
        }
    }

// DFS no grafo original //
    visitado.assign(n+1, false);
    while (!pilha.empty()){

        int u = pilha.top();
        pilha.pop();

        if (!visitado[u]){

            vector<int> componente;
            dfs(u, grafo, &componente);
            sort(componente.begin(), componente.end());
            sccs.push_back(componente);
        }
    }
    sort(sccs.begin(), sccs.end());
}

int main(int argc, char* argv[]){

    string input_file, output_file;

    for (int i = 1; i < argc; i++){

        if (!strcmp(argv[i], "-h")){

            cout << "Help:" << endl;
            cout << "-h : mostra o help" << endl;
            cout << "-o <arquivo> : redireciona a saida para o \"arquivo\"" << endl;
            cout << "-f <arquivo> : indica o \"arquivo\" que contém o grafo de entrada" << endl;
            return 0;
        }
        if (!strcmp(argv[i], "-o") && i < argc - 1) output_file = argv[++i];
        if (!strcmp(argv[i], "-f") && i < argc - 1) input_file = argv[++i];
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

    int n, m, u, v;
    fin >> n >> m;
    
    grafo.resize(n+1);
    grafoT.resize(n+1);
    
    for (int i = 0; i < m; i++){

        fin >> u >> v;
        grafo[u].push_back(v);
        grafoT[v].push_back(u);
    }
    fin.close();

    kosaraju(n);

    ostream& out = output_file.empty() ? cout : *(new ofstream(output_file));
    if (!output_file.empty() && !((ofstream&)out).is_open()){

        cerr << "Erro ao criar arquivo de saída" << endl;
        return 1;
    }

    for (auto& componente : sccs){

        for (size_t i = 0; i < componente.size(); i++){
            out << componente[i] << (i == componente.size()-1 ? "" : " ");
        }
        out << endl;
    }

    if (!output_file.empty()){

        ((ofstream&)out).close();
        delete &out;
    }

    return 0;
}