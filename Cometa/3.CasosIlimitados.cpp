
// Guillermo Garcia Pati�o Lenza

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include "Matriz.h"  // propios o los de las estructuras de datos de clase
using namespace std;

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
Solucion resolver(Datos datos) {
   ...
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   
   // leer los datos de la entrada
	vector<pair<int,int>> T;
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
   
   //Solucion sol = resolver(datos);
   
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
