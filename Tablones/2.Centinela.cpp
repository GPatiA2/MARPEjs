
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include "Matriz.h"  // propios o los de las estructuras de datos de clase
#include "EnterosInf.h"
using namespace std;

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
int resolver(Matriz<int> & M, vector<int> const & marcas) {

	// Empezando desde la primera diagonal, la primera diagonal tiene tantos
	//   elementos como filas/columnas (matriz cuadrada) tiene la matriz
	int num_diagonales = M.numcols();

	for(int d = 2; d < num_diagonales; d++){ // Recorrer las diferentes diagonales
		//cout << "D = " << d << endl;
		int i = 1;
		for(int j = d; j < M.numfils(); j++){ // Recorrer cada elemento de la diagonal por columnas
			//cout << "	Para i = " << i << " j = " << j << endl;
			M[i][j] = EntInf::_intInf;
			for(int k = i; k < j; k++){
				//cout << "	 	Estoy mirando (" << i << "," << k << ")" << " = " << M[i][k] << " y (" << k+1 << "," << j << ") = " << M[k+1][j] << endl;
				int tmp = M[i][k] + M[k+1][j] + 2*(marcas[j]-marcas[i-1]);
				//cout << "		La longitud entre las marcas " << marcas[j] << " y " << marcas[i-1] << " es " << marcas[j] - marcas[i-1] << endl;
				//cout << " 		El valor para " << i << " , " << j << " es " << M[i][k] << " + " << M[k+1][j] << " + " << 2*(marcas[j]-marcas[i-1]) << " = " << tmp << endl;
				if(tmp < M[i][j]){
					//cout << "		"<< tmp << " es menor que " << M[i][j] << endl;
					M[i][j] = tmp;
				}
				//cout << "		El valor de (" << i << "," << j << ") es : " << M[i][j] << endl;
			}
			//cout << "	Al final me da " << M[i][j] << endl;


			i++;
		}
	}

	return M[1][M.numcols()-1];





}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

   // leer los datos de la entrada
   int longitud;
   int num_marcas;
   cin >> longitud;
   cin >> num_marcas;
   if (longitud == 0 && num_marcas == 0){
      return false;
   }
   vector<int> marcas;
   marcas.push_back(0);
   for(int i = 0; i < num_marcas; i++){
	   int m;
	   cin >> m;
	   marcas.push_back(m);
   }
   marcas.push_back(longitud);
   Matriz<int> M(marcas.size(), marcas.size(), 0);


   int sol = resolver(M, marcas);
   //cout << M << endl;
   cout << sol << endl;

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

