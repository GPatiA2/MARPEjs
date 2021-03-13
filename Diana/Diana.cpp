
// Guillermo Garcia Pati駉 Lenza

// Comentario general sobre la soluci贸n,
// explicando c贸mo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include "Matriz.h"
#include "EnterosInf.h"
using namespace std;

using Solucion = vector<int>;
using Datos = vector<int>;

// funci贸n que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
Solucion resolver(Datos datos, int P) {
	Matriz<int> M(1, P+1 , EntInf::_intInf);
	M[0][0] = 0;

	for(unsigned int i = 1; i < datos.size()+1 ; i++){
		for(int j = 1; j < P+1 ; j++){
			if(datos[i-1] == j){
				M[0][j] = 1;
			}
			else if(datos[i-1] < j){
				M[0][j] = min(M[0][j], M[0][j - datos[i-1]]+1);
			}
		}
	}
	Solucion sol;
	if(M[0][P] != EntInf::_intInf){
		int i = datos.size();
		int j = P;
		while(j > 0){
			if(datos[i-1] <= j && M[0][j] == M[0][j - datos[i-1]] + 1){
				sol.push_back(datos[i-1]);
				j -= datos[i-1];
			}
			else{
				i--;
			}
		}
	}
	return sol;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuraci贸n, y escribiendo la respuesta
bool resuelveCaso() {
   
   // leer los datos de la entrada
   Datos datos;
   int P;
   int n;
   int aux;
   cin >> P;
   cin >> n;
   for(int i = 0; i < n; i++){
	   cin >> aux;
	   datos.push_back(aux);
   }
   if (!std::cin){  // fin de la entrada
      return false;
   }

   Solucion sol = resolver(datos, P);
   if(sol.empty()){
	   cout << "Imposible \n";
   }
   else{
	   cout << sol.size() << ": ";
	   for(unsigned int i = 0; i < sol.size(); i++){
		   if(i != sol.size()-1){
			   cout << sol[i] << " ";
		   }
		   else{
			   cout << sol[i] << "\n";
		   }
	   }
   }
   
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
