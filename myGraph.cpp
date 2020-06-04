#include "myGraph.hpp"

#include <iostream>
#define debug(a) std::cout << a << std::endl

myGraph::myGraph() { V = 0; }

myGraph::myGraph(std::string regex) {
	std::stack<int> parens;
	std::vector<int> vbars;

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

					for (auto it = vbars.begin(); it != vbars.end(); it++)
						adj[*it].push_back(std::make_pair(i, 0));
					vbars.clear();

					if (vertice[i + 1] == '*')
						adj[i + 1].push_back(std::make_pair(parens.top(), 0));

					parens.pop();
					break;
				case '*':
					if (i == 0) throw "Regex inválida!";

					adj[i].push_back(std::make_pair(i + 1, 0));

					if (vertice[i - 1] != ')') adj[i].push_back(std::make_pair(i - 1, 0));
					break;
			}
		}
	}

	// Arestas e vértices feitos, grafo feito
}
