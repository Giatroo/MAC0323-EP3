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

	// Vamos fazer um pre-processamento do texto antes de inseri-lo no
	// grafo para cuidar dos casos em que temos + e conjuntos
	int baberto = -1;
	vector<char> latters;
	stack<char> st;
	for (int i = 0; i < regex.size(); i++) {
		string news;
		switch (regex[i]) {
			case '(': st.push(i); break;
			case ')':
				if (st.empty()) throw "Regex inválida";

				if (regex.size() > i + 1 && regex[i + 1] == '+') {
					news = "";
					for (int j = st.top(); j <= i; j++) news += regex[j];

					regex.insert(st.top(), news);
					i += news.size();
					regex[i + 1] = '*';
				}

				st.pop();
				break;
			case '[': baberto = i; break;
			case ']':
				if (baberto == -1) throw "Regex inválida";

				for (int j = baberto + 1; j < i; j++) latters.push_back(regex[j]);

				regex.erase(baberto, i - baberto + 1);
				i -= (i - baberto + 1);

				news = "";
				news += "(";
				for (char latter : latters) {
					news += latter;
					news += '|';
				}
				news.pop_back();
				news += ")";

        latters.clear();

				regex.insert(baberto, news);
				i += news.size();

				if (regex.size() > i + 1 && regex[i + 1] == '+') {
					news = "";
					for (int j = baberto; j <= i; j++) news += regex[j];

					regex.insert(baberto, news);
					i += news.size();
					regex[i + 1] = '*';
        }

				baberto = -1;
				break;
			case '+':
				if (i == 0) throw "Regex inválida";
				if (regex[i - 1] != ')') {
					news = regex[i - 1];
					regex.insert(i, news);
					i++;
					regex[i] = '*';
				}
				break;
		}
	}

	cout << endl;
	cout << "Sua regex é:\n'" << regex << "'" << endl;

	myGraph g(regex);

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
