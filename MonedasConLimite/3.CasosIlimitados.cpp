
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

static const int _intInf = 1000000000;

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
int resolver(vector<int> const & valores, vector<int> const & cantidades, int C) {

	vector<int> V(C+1,_intInf);
	V[0] = 0;
	int tipos = valores.size();

	for(int i = 1; i < tipos+1 ; i++){
		for(int j = C ; j >= 0; j--){
			for(int k = 1; k <= cantidades[i-1] && (j - k*valores[i-1] >= 0); k++){
				int tmp = V[j - k*valores[i-1]] + k;
				V[j] = min(tmp, V[j]);
			}
		}
	}

	return V[C];
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   
   // leer los datos de la entrada
   int cant;
   cin >> cant;
   if (!std::cin)  // fin de la entrada
      return false;
   
   vector<int> valores;
   vector<int> cantidades;
   for(int i = 0; i < cant; i++){
	   int tmp;
	   cin >> tmp;
	   valores.push_back(tmp);
   }
   for(int i = 0; i < cant; i++){
	   int tmp;
   	   cin >> tmp;
   	   cantidades.push_back(tmp);
   }
   int C;
   cin >> C;
   int sol = resolver(valores, cantidades, C);
   if(sol == _intInf){
	   cout << "NO" << endl;
   }
   else{
	   cout << "SI " << sol << endl;
   }

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
