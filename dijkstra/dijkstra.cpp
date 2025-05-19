#include <bits/stdc++.h>
using namespace std;

// Implementação do algoritimo Dijkstra para o Problema dos Caminhos Mínimos //

const int INF = INT_MAX;

vector<int> dijkstra(vector<vector<pair<int, int>>> &adj, int start){

    vector<int> dist(adj.size(), INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});
    dist[start] = 0;

    while (!pq.empty()){

        int u = pq.top().second;
        int current_dist = pq.top().first;
        pq.pop();

        if (current_dist > dist[u]) continue;

        for (auto &edge : adj[u]){

            int v = edge.first;
            int w = edge.second;
            if (dist[v] > dist[u] + w){
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

int main(int argc, char *argv[]){

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
        if (!strcmp(argv[i], "-o") && i < argc - 1) output_file = argv[++i];
        if (!strcmp(argv[i], "-f") && i < argc - 1) input_file = argv[++i];
        if (!strcmp(argv[i], "-i") && i < argc - 1) start_vertex = atoi(argv[++i]);
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
    vector<vector<pair<int, int>>> adj(n + 1);

    for (int i = 0; i < m; i++){

        int u, v, w;
        fin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // Grafo não-direcionado
    }
    fin.close();

    vector<int> dist = dijkstra(adj, start_vertex);

    ostream &out = output_file.empty() ? cout : *(new ofstream(output_file));
    if (!output_file.empty() && !((ofstream&)out).is_open()){

        cerr << "Erro ao criar arquivo de saída" << endl;
        return 1;
    }

    for (int i = 1; i <= n; i++){

        out << i << ":" << (dist[i] == INF ? -1 : dist[i]) << (i == n ? "\n" : " ");
    }

    if (!output_file.empty()){
        
        ((ofstream&)out).close();
        delete &out;
    }

    return 0;
}