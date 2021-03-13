
// Guillermo Garcia Pati駉 Lenza

// Comentario general sobre la soluci贸n,
// explicando c贸mo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include "Matriz.h"  // propios o los de las estructuras de datos de clase
#include "EnterosInf.h"
using namespace std;

struct sol{
	EntInf minCoste;
	long long int formas;
	EntInf minCordeles;
};

struct tCordel{
	int longitud;
	int coste;
};

// funci贸n que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
sol resolver(vector<tCordel> const & T, int L) {
	Matriz<sol> M(1,L+1,{EntInf::_intInf , 0, EntInf::_intInf});
	M[0][0] = {0,1,0};
	int s = T.size();
	for(int i = 1; i < s+1; i++){
		for(int j = L; j >= T[i-1].longitud; j--){
			M[0][j].minCordeles = min(M[0][j].minCordeles , M[0][j - T[i-1].longitud].minCordeles + 1);
			M[0][j].minCoste =	min(M[0][j].minCoste , M[0][j - T[i-1].longitud].minCoste + T[i-1].coste);
			M[0][j].formas += M[0][j - T[i-1].longitud].formas;
		}
	}
	return M[0][L];
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuraci贸n, y escribiendo la respuesta
bool resuelveCaso() {
   
   // leer los datos de la entrada
	vector<tCordel> T;
	int n;
	int L;
	cin >> n;
	cin >> L;
	for(int i = 0; i < n; i++){
		int l;
		int c;
		cin >> l;
		cin >> c;
		T.push_back({l,c});
	}
    if (!std::cin)  // fin de la entrada
      return false;
   sol solucion = resolver(T,L);
   if(solucion.formas > 0){
	   cout << "SI " << solucion.formas << " " << solucion.minCordeles << " " << solucion.minCoste << "\n";
   }
   else {
	   cout << "NO \n";
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
