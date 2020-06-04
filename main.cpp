// Includes, defines e variáveis globais ============================
#include <iostream>

#include "myGraph.hpp"

using namespace std;

string regex;   // A expressão regular informada pelo usuário
string pattern; // Um padrão a ser verificado pela regex

// Declaração de funções ============================================

// Função main ======================================================
int main(int argc, char *argv[]) {
	cout << "Digite a expressão regular: ";
	getline(cin, regex);
	myGraph g(regex);

	cout << endl;
	cout << "Sua regex é:\n'" << regex << "'" << endl;

	for (int i = 0; i < g.V; i++) {
		cout << "i = " << i << " " << g.vertice[i] << " com arestas:" << endl;
		for (int j = 0; j < g.adj[i].size(); j++)
			cout << "\t" << g.adj[i][j].first << ' ' << g.adj[i][j].second << endl;
	}

	cout << "\nDigite um padrão para conferir se está na regex ou Ctrl+D para sair:" << endl;
	while (getline(cin, pattern)) {
		cout << endl;
		cout << "Seu padrão é:\n'" << pattern << "'" << endl;

		cout << "\nDigite um padrão para conferir se está na regex ou Ctrl+D para sair:" << endl;
	}

	cout << "Obrigado pela preferência!" << endl;

	return 0;
}

// Implementação das demais funções =================================
