
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include "EnterosInf.h"
using namespace std;

struct Bombilla{
	int coste;
	int potencia;
};

struct Solucion{
	int potencia;
	EntInf coste;
};

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
Solucion resolver(int const pmin, int const pmax, vector<Bombilla> const & bombillas, vector<EntInf> & V) {

	int tam = bombillas.size() + 1;
	for(int i = 1; i < tam; i++){
		for(int j = 1; j < pmax+1 ; j++){
			if(j >= bombillas[i-1].potencia){
				V[j] = min(V[j], V[j - bombillas[i-1].potencia] + bombillas[i-1].coste);
			}
		}
	}

	// Obtener la solucion
	Solucion sol;
	sol.potencia = pmin;
	sol.coste = V[pmin];
	for(int i = pmin ; i <= pmax ; i++){
		if(V[i] < sol.coste){
			sol.potencia = i;
			sol.coste = V[i];
		}
	}

	return sol;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   
   // leer los datos de la entrada
   int num_tipos, pmin, pmax;
   cin >> num_tipos;

   if (!std::cin)  // fin de la entrada
      return false;
   
   cin >> pmax;
   cin >> pmin;
   vector<Bombilla> bombillas;
   for(int i = 0; i < num_tipos; i++){
	   int pot;
	   cin >> pot;
	   bombillas.push_back({0,pot});
   }
   for(int i = 0; i < num_tipos; i++){
	   int cost;
	   cin >> cost;
	   bombillas[i].coste = cost;
   }

   EntInf a;
   vector<EntInf> V(pmax+1, a._intInf);
   V[0] = 0;
   Solucion sol = resolver(pmin, pmax, bombillas, V);
   
   // escribir sol
   if(sol.coste != a._intInf){
	   cout << sol.coste << " " << sol.potencia << endl;
   }
   else{
	   cout << "IMPOSIBLE \n";
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
