#pragma once

// Includes, defines e variáveis globais ============================
#include <stack>
#include <string>
#include <utility> // pair, make_pair etc
#include <vector>  // vector, vector::iterator

const int N = 1e3; // Tamanho máximo do texto

// Os caracteres especiais de uma regex
const std::string special = "+*[]()|";

// Definição da classe do grafo =====================================
class myGraph {
  private:
	// A lista do conteúdo de cada vértice (o char associado ao vértice)
	// Pode ser um char especial (tipo *, |, +, '(') ou não.
	std::vector<char> vertice;

	// As arestas possuem um índice indicando o vértice para o qual apontam
	// e possuem também um char que é o caracter lido na transição
	// se o char é 0, então é uma epsilon-transição (transição nula)
	std::vector<std::pair<int, char> > adj[N];

	long unsigned int V; // Tamanho do grafo (número de vértices)

  // dfs utilizada pelo método math
  void dfs(int source, std::vector<int> &v, std::vector<bool> &visited);

  // Função utilizada pelo método output
  std::string displayEdge(long unsigned int i);

  public:
	// O grafo é construíto a partir de uma regex dada
	myGraph();
	myGraph(std::string regex);

  // Método para ver se a palavra pertence à linguagem da regex ou não
  bool match(std::string word);

  // Função que imprime o grafo em texto
  void print();
  // Função que mostra visualmente o grafo
  void output();
};

