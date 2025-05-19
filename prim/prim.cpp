#include <bits/stdc++.h>
using namespace std;

const int INF = INT_MAX;

struct Aresta {
    int u, v;
    int peso;
    bool operator>(const Aresta& outra) const {
        return peso > outra.peso;
    }
};

pair<int, vector<Aresta>> prim(vector<vector<pair<int, int>>>& adj, int start) {
    int n = adj.size() - 1;
    vector<bool> in_agm(n + 1, false);
    vector<int> key(n + 1, INF);
    vector<int> parent(n + 1, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    key[start] = 0;
    pq.push(make_pair(0, start));

    int custo_total = 0;
    vector<Aresta> arvore;

    while (!pq.empty()) {
        int u = pq.top().second;
        int current_key = pq.top().first;
        pq.pop();

        if (in_agm[u]) continue;
        in_agm[u] = true;
        custo_total += current_key;

        if (parent[u] != -1) {
            Aresta nova_aresta;
            nova_aresta.u = parent[u];
            nova_aresta.v = u;
            nova_aresta.peso = current_key;
            arvore.push_back(nova_aresta);
        }

        for (size_t i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i].first;
            int peso = adj[u][i].second;
            if (!in_agm[v] && peso < key[v]) {
                key[v] = peso;
                parent[v] = u;
                pq.push(make_pair(key[v], v));
            }
        }
    }

    return make_pair(custo_total, arvore);
}

int main(int argc, char* argv[]) {
    string input_file, output_file;
    bool show_solution = false;
    int start_vertex = 1;

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-h")) {
            cout << "Help:" << endl;
            cout << "-h : mostra o help" << endl;
            cout << "-o <arquivo> : redireciona a saida para o \"arquivo\"" << endl;
            cout << "-f <arquivo> : indica o \"arquivo\" que contém o grafo de entrada" << endl;
            cout << "-s : mostra a solução (árvore geradora mínima)" << endl;
            cout << "-i <v> : vértice inicial" << endl;
            return 0;
        }
        if (!strcmp(argv[i], "-o") && i < argc - 1) output_file = argv[++i];
        if (!strcmp(argv[i], "-f") && i < argc - 1) input_file = argv[++i];
        if (!strcmp(argv[i], "-s")) show_solution = true;
        if (!strcmp(argv[i], "-i") && i < argc - 1) start_vertex = atoi(argv[++i]);
    }

    if (input_file.empty()) {
        cerr << "Arquivo de entrada não especificado. Use -f" << endl;
        return 1;
    }

    ifstream fin(input_file);
    if (!fin) {
        cerr << "Erro ao abrir arquivo de entrada" << endl;
        return 1;
    }

    int n, m;
    fin >> n >> m;
    vector<vector<pair<int, int>>> adj(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v, peso;
        fin >> u >> v >> peso;
        adj[u].push_back(make_pair(v, peso));
        adj[v].push_back(make_pair(u, peso));
    }
    fin.close();

    pair<int, vector<Aresta>> result = prim(adj, start_vertex);
    int custo_total = result.first;
    vector<Aresta> arvore = result.second;

    ostream& out = output_file.empty() ? cout : *(new ofstream(output_file));
    if (!output_file.empty() && !((ofstream&)out).is_open()) {
        cerr << "Erro ao criar arquivo de saída" << endl;
        return 1;
    }

    if (show_solution) {
        for (size_t i = 0; i < arvore.size(); ++i) {
            out << "(" << arvore[i].u << "," << arvore[i].v << ")";
            if (i != arvore.size() - 1) out << " ";
        }
        out << endl;
    } else {
        out << custo_total << endl;
    }

    if (!output_file.empty()) {
        ((ofstream&)out).close();
        delete &out;
    }

    return 0;
}