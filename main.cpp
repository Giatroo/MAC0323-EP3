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
	// g.print();
	g.output();

	cout << "\nDigite um padrão para conferir se está na regex ou Ctrl+D para sair:" << endl;
	while (getline(cin, pattern)) {
		cout << endl;
		cout << "Seu padrão é:\n'" << pattern << "'" << endl;
		cout << (g.match(pattern) ? "Está na linguagem" : "Não está na linguagem") << endl;

		cout << "\nDigite um padrão para conferir se está na regex ou Ctrl+D para sair:" << endl;
	}

	cout << "Obrigado pela preferência!" << endl;

	return 0;
}

// Implementação das demais funções =================================
