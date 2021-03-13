
// Guillermo Garcia Pati駉 Lenza

// Comentario general sobre la soluci贸n,
// explicando c贸mo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include "Matriz.h"
#include "EnterosInf.h"
using namespace std;

// funci贸n que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
EntInf resolver(Matriz<EntInf> & M, string const & palabra, int i, int j) {
	if(i > j){
		return EntInf::_intInf;
	}
	else{
		if(M[i][j] != EntInf::_intInf){
			return M[i][j];
		}
		else if(i == j){
			M[i][j] = 1;
			return M[i][j];
		}
		else if(palabra[i] == palabra[j]){
			M[i][j] = resolver(M,palabra, i+1, j-1);
			return M[i][j];
		}
		else{
			EntInf izq = resolver(M,palabra, i+1, j) + 1;
			EntInf der = resolver(M,palabra, i, j-1) + 1;
			M[i][j] = min(izq,der);
			return M[i][j];
		}
	}

}

void reconstruye(Matriz<EntInf> const & M, string const & palabra, string & pal){
	int i = 0;
	int j = palabra.size()-1;
	stack<char> pendientes;
	while(i < j){
		if(palabra[i] == palabra[j]){
			pendientes.push(palabra[j]);
			pal.push_back(palabra[i]);
			i++;
			j--;
		}
		else{
			if(M[i][j] == M[i+1][j]+1){
				pal.push_back(palabra[i]);
				pendientes.push(palabra[i]);
				i++;
			}
			else{
				pal.push_back(palabra[j]);
				pendientes.push(palabra[j]);
				j--;
			}
		}
	}
	if(i == j){
		pal.push_back(palabra[i]);
	}
	while(!pendientes.empty()){
		char c = pendientes.top();
		pendientes.pop();
		pal.push_back(c);
	}
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuraci贸n, y escribiendo la respuesta
bool resuelveCaso() {
   
   // leer los datos de la entrada
   string palabra;
   cin >> palabra;
   if (!std::cin)  // fin de la entrada
      return false;

   EntInf a = 0;
   Matriz<EntInf> M(palabra.size(), palabra.size(), a._intInf);

   // En el caso en el que tenga un palindromo de 1 letra, le a馻do 0 letras
   for(unsigned int i = 0; i < palabra.size(); i++){
	   M[i][i] = 0;
   }
   EntInf sol = resolver(M, palabra, 0, palabra.size()-1);

   cout << sol << " ";

   string palindromo = "";
   reconstruye(M, palabra, palindromo);

   cout << palindromo << endl;
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
