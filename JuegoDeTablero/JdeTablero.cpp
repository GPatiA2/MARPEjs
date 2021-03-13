
// Guillermo Garcia Patiño Lenza

// Comentario general sobre la soluciÃ³n,
// explicando cÃ³mo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include "Matriz.h"  // propios o los de las estructuras de datos de clase
#include "EnterosInf.h"
using namespace std;

struct sol{
	int pos;
	int val;
};

// funciÃ³n que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
sol resolver(Matriz<int> const & M, int N) {
	vector<int> acu(N+2,0); // -> vector de tamaño n+2 inicializado todo a 0 que usaremos para guardar los valores acumulados al bajar por la matriz
	vector<int> act(N+2,0); // -> vector de tamaño n+2 que guardará la fila actual de la matriz que estamos mirando

	for(int i = 1; i <= N; i++){
	    for(int j = 1; j <= N; j++){
	    	act[j] = M[i-1][j-1] + max(acu[j-1], max( acu[j], acu[j+1]) );
	    }
	    acu = act;
	}

	int p = 1;
	int v = 0;
	for(int k = 1; k <= N; k++){
		p = (acu[k] > v)? k : p;
		v = (acu[k] > v)? acu[k] : v;
	}

	return {p,v};
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuraciÃ³n, y escribiendo la respuesta
bool resuelveCaso() {
   
   // leer los datos de la entrada
	int n;
	cin >> n;
	Matriz<int> M(n,n,0);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			cin >> M[i][j];
		}
	}
    if (!std::cin)  // fin de la entrada
      return false;
   sol solucion = resolver(M ,n);
   cout << solucion.val << " " << solucion.pos << endl;
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
