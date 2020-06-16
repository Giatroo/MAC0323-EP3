#include "myGraph.hpp"

#include <fstream>
#include <iostream>
#define debug(a) std::cout << a << std::endl
#define debugv(a) std::cout << #a << " " << a << std::endl

myGraph::myGraph() { V = 0; }

myGraph::myGraph(std::string regex) {
	std::stack<int> parens;
	std::vector<int> vbars;
	std::vector<int>::iterator it1, it2;

	this->V = regex.size() + 1; // +1 por conta do estado final

	// Construindo os vértices
	vertice.resize(V);
	for (long unsigned int i = 0; i < regex.size(); i++) vertice[i] = regex[i];
	vertice[V - 1] = 0;

	// Construindo as arestas
	for (long unsigned int i = 0; i < V - 1; i++) {
		// 1) Primeiro as básicas, quando o caracter não é especial
		if (special.find(vertice[i]) == std::string::npos)
			adj[i].push_back(std::make_pair(i + 1, vertice[i]));
		// Construímos uma aresta de i para i+1
		// A transição consome o i-ésimo caracter (vertice[i])

		// 2) Depois as definidas para caracteres especiais
		else {
			// Aqui teremos casos especiais para cada caracter especial
			// (é aqui que a mágica acontece)

			switch (vertice[i]) {
				case '(':
					parens.push(i);
					adj[i].push_back(std::make_pair(i + 1, 0));
					break;
				case '|':
					if (parens.empty()) throw "Regex inválida!";

					vbars.push_back(i);

					adj[parens.top()].push_back(std::make_pair(i + 1, 0));
					break;
				case ')':
					if (parens.empty()) throw "Regex inválida!";

					adj[i].push_back(std::make_pair(i + 1, 0));

					if (!vbars.empty()) {
						it1 = vbars.end();
						it1--;
						for (; it1 != vbars.begin() && *it1 > parens.top();) {
							adj[*it1].push_back(std::make_pair(i, 0));
							it2 = it1;
							it1--;
							vbars.erase(it2);
						}
						if (it1 == vbars.begin() && *it1 > parens.top()) {
							adj[*it1].push_back(std::make_pair(i, 0));
							vbars.erase(it1);
						}
					}

					if (vertice[i + 1] == '*') {
						adj[i + 1].push_back(std::make_pair(parens.top(), 0));
						adj[parens.top()].push_back(std::make_pair(i + 1, 0));
					}

					parens.pop();
					break;
				case '*':
					if (i == 0) throw "Regex inválida!";

					adj[i].push_back(std::make_pair(i + 1, 0));

					if (vertice[i - 1] != ')') {
						adj[i].push_back(std::make_pair(i - 1, 0));
						adj[i - 1].push_back(std::make_pair(i, 0));
					}
					break;
        case '.':
          // Criaremos uma aresta para frente sem custo
          adj[i].push_back(std::make_pair(i+1, 0));
          break;
			}
		}
	}

	// Arestas e vértices feitos, grafo feito
}

void myGraph::dfs(int source, std::vector<int> &v, std::vector<bool> &visited) {
	std::stack<int> s;
	int cur;

	visited[source] = true;
	s.push(source);

	while (!s.empty()) {
		cur = s.top();
		s.pop();
		v.push_back(cur);

		for (long unsigned int i = 0; i < adj[cur].size(); i++) {
			// Visitamos que ainda não foi visto e só usando epsilon-transições
			if (!visited[adj[cur][i].first] && adj[cur][i].second == 0) {
				visited[adj[cur][i].first] = true;
				s.push(adj[cur][i].first);
			}
		}
	}
}

bool myGraph::match(std::string word) {
	// Os conjuntos S e T, como mencionados em aula
	std::vector<int> S, T;
	std::vector<bool> visited(V, false); // vector para as dfs
	long unsigned int i;                 // índice em word
	long unsigned int j;                 // índice auxiliar
	bool any;                            // indica se achamos transição
	bool finalstate;                     // indica se chegamos ao estado final

	// Sempre começamos por 0
	S.push_back(0);

	for (i = 0; i < word.size(); i++) {
		for (j = 0; j < visited.size(); j++) visited[j] = false;

		for (j = 0; j < S.size(); j++) dfs(S[j], T, visited);
		S.clear();

		any = false;
		for (j = 0; j < T.size(); j++) {
			if (vertice[T[j]] == word[i] || vertice[T[j]] == '.') {
				S.push_back(T[j] + 1);
				any = true;
			}
		}
		T.clear();

		if (!any) return false;
	}

  for (j = 0; j < visited.size(); j++) visited[j] = false;
	for (j = 0; j < S.size(); j++) dfs(S[j], T, visited);

	finalstate = false;
	for (j = 0; j < T.size() && !finalstate; j++) finalstate = (T[j] == V - 1);
	return finalstate;
}

void myGraph::print() {
	std::cout << "Grafo :" << std::endl;
	for (long unsigned int i = 0; i < V; i++) {
		std::cout << "i = " << i << " " << vertice[i] << " com arestas:" << std::endl;
		for (long unsigned int j = 0; j < adj[i].size(); j++)
			std::cout << "\t" << adj[i][j].first << ' ' << adj[i][j].second << std::endl;
	}
}

std::string myGraph::displayEdge(long unsigned int i) {
	std::string ret = "";
	ret += "\"";
	ret += std::to_string(i);
	ret += " - ";
	ret += (vertice[i] != 0 ? vertice[i] : ' ');
	ret += "\"";
	return ret;
}

void myGraph::output() {
	std::ofstream out("graph.gv");
	out << "digraph foo {\n";
	for (long unsigned int i = 0; i < V; i++)
		for (long unsigned int j = 0; j < adj[i].size(); j++)
			out << '\t' << displayEdge(i) << " -> " << displayEdge(adj[i][j].first) << " [label=\""
			    << (adj[i][j].second == 0 ? ' ' : adj[i][j].second) << "\""
			    << (adj[i][j].second == 0 ? "; color=grey" : "") << "];\n";

	out << "}\n";
	out.close();
	system("dot -Tpng graph.gv -o graph.png");
	system("display graph.png");
}

