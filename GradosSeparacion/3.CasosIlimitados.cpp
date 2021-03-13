
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <unordered_set>
#include <vector>
#include "Grafo.h"
#include "Matriz.h"
#include "EnterosInf.h"
using namespace std;

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
void resolver(Matriz<int> & M) {
	int v = M.numfils();
	for(int k = 0; k < v; k++){
		for(int i = 0; i < v; i++){
			for(int j = 0; j < v; j++){
				// Pasar por k
				int tmp = M[i][k] + M[k][j];
				if(tmp < M[i][j]){
					M[i][j] = tmp;
				}
			}
		}
	}
}

int encuentra(string const & s, vector<string> const & v){
	unsigned int i = 0;
	while(i < v.size() && v[i] != s){
		i++;
	}
	return i;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   
	// leer los datos de la entrada
	int V;
	int E;
	cin >> V;
	if (!std::cin)  // fin de la entrada
	  return false;
	cin >> E;
	unordered_set<string> nombres;
	Matriz<int> M (V, V, EntInf::_intInf);
	for(int i = 0; i < V; i++){ M[i][i] = 0; }


	vector<pair<string,string>> pares;
	string nombre_orig;
	string nombre_dest;
	for(int i = 0; i < E; i++){
		cin >> nombre_orig;
		cin >> nombre_dest;
		pair<string,string> p = {nombre_orig, nombre_dest};
		pares.push_back(p);
		nombres.insert(nombre_orig);
		nombres.insert(nombre_dest);
	}

	vector<string> nombres_a_numeros;
	for(string s : nombres){
		nombres_a_numeros.push_back(s);
	}

	for(pair<string,string> p : pares){
		int ind1 = encuentra(p.first , nombres_a_numeros);
		int ind2 = encuentra(p.second, nombres_a_numeros);
		M[ind1][ind2] = 1;
		M[ind2][ind1] = 1;
	}

	resolver(M);

	int maximo = -1;
    for(int i = 0; i < M.numfils(); i++){
    	for(int j  = 0; j < M.numcols(); j++){
    		maximo =  max(maximo,M[i][j]);
    	}
    }

    EntInf m(maximo);
    string s = (m == Infinito)? "DESCONECTADA" : std::to_string(maximo);
    cout << s << endl;
   // escribir sol
   
   return true;
}

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
   
   while (resuelveCaso());
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}
