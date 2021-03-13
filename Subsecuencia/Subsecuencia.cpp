
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include "Matriz.h"
#include "EnterosInf.h"
using namespace std;

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
int resolver(Matriz<int> & M, string const & p1, string const & p2, unsigned int i, unsigned int j) {
   int & res = M[i][j];
   if(M[i][j] != -1){
	   return res;
   }
   if(p1[i] == p2[j]){
	   res = resolver(M, p1,p2, i+1, j+1) + 1;
   }
   else{
	   res = max(resolver(M,p1,p2,i+1,j), resolver(M,p1,p2,i,j+1));
   }

   return res;
}

void reconstruir(Matriz<int> & M, string const & p1, string const & p2){
	unsigned int i = 0;
	unsigned int j = 0;
	while(i < p1.length() && j < p2.length()){
		if(p1[i] == p2[j]){
			cout << p1[i];
			i++;
			j++;
		}
		else{
			if(M[i][j] == M[i][j+1]){
				j++;
			}
			else{
				i++;
			}
		}
	}
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   
   // leer los datos de la entrada
   string p1;
   string p2;
   cin >> p1;
   if (!std::cin)  // fin de la entrada
      return false;
   cin >> p2;
   
   Matriz<int> M(p1.length()+1, p2.length()+1, -1);
   for(unsigned int i = 0; i < p1.length()+1; i++){
	   M[i][p2.length()] = 0;
   }
   for(unsigned int j = 0; j < p2.length()+1; j++){
	   M[p1.length()][j] = 0;
   }

   int sol = resolver(M, p1, p2, 0, 0);


   // escribir sol
   reconstruir(M,p1,p2);
   cout << endl;
   
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
