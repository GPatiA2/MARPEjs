
// Guillermo Garcia Pati駉 Lenza
// Comentario general sobre la soluci贸n,
// explicando c贸mo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include "Matriz.h"
#include "EnterosInf.h"
using namespace std;

struct Solucion {
	int cofres;
	int oro;
};

// funci贸n que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
Solucion resolver(vector<int> const & oro, vector<int> const & tiempos, Matriz<Solucion> & M, int tiempo, int tipos) {
	//Problema resuelto
	if(M[tipos][tiempo].oro != -1 && M[tipos][tiempo].cofres != -1){
		return M[tipos][tiempo];
	}
	//No es posible recoger ese cofre
	if(3*tiempos[tipos-1] > tiempo){
		Solucion aux = resolver(oro,tiempos,M,tiempo,tipos-1);
		M[tipos][tiempo] = aux;
	}
	//Se resuelven los dos subproblemas, y se elige la mejor de las dos soluciones
	else{
		Solucion tomar = resolver(oro,tiempos,M, tiempo-3*tiempos[tipos-1], tipos-1);
		tomar.oro += oro[tipos-1];
		tomar.cofres += 1;
		Solucion no_tomar = resolver(oro,tiempos,M,tiempo,tipos-1);
		M[tipos][tiempo] = (tomar.oro > no_tomar.oro)? tomar : no_tomar;

	}
	//Se devuelve el resultado de la solucion de este problema
	return M[tipos][tiempo];
}

Solucion resolverAscendente(vector<int> const & valores, vector<int> const & tiempos, Matriz<Solucion> & M, int j, int i){

	for(int f = 1; f <= i; f++){
		for(int c = 1; c <= j; c++){
			if(tiempos[i-1]*3 > c){
				M[f][c] = M[f-1][c];
			}
			else{
				if (M[f-1][c].oro > M[f-1][c - 3*tiempos[i-1]].oro){
					M[f][c] = M[f-1][c];
				}
				else{
					M[f][c].oro = M[f-1][c - 3*tiempos[i-1]].oro + valores[f-1];
					M[f][c].cofres = M[f-1][c - 3*tiempos[i-1]].cofres + 1;
				}
			}
		}
	}

	return M[i][j];
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuraci贸n, y escribiendo la respuesta
bool resuelveCaso() {
   

   // leer los datos de la entrada
   int tiempo;
   int n_cofres;
   vector<int> oro;
   vector<int> c_tiempo;
   cin >> tiempo;

   if (!std::cin)  // fin de la entrada
      return false;

   cin >> n_cofres;
   for(int i = 0; i < n_cofres; i++){
	   int t;
	   int o;
	   cin >> t;
	   cin >> o;
	   c_tiempo.push_back(t);
	   oro.push_back(o);
   }

   // Vector para marcar las soluciones
   vector<bool> marcado;
   for(int i = 0; i < n_cofres; i++){
	   marcado.push_back(false);
   }
   // Matriz con los resulados de los subproblemas
   Matriz<Solucion> M(n_cofres+1, tiempo+1, {-1,-1});

   // Inicializo casos base
   // Cuando ya no me quedan cofres
   for(int i = 0; i < tiempo+1; i++){
	   M[0][i] = {0,0};
   }
   // Cuando ya no me queda tiempo
   for(int j = 0; j < n_cofres+1; j++){
	   M[j][0] = {0,0};
   }


   // La funcion recursiva devuelve el oro total que se recoge y el numero de cofres que se recogen
   // La funcion me dice, para los tipos del 0 al i de cofres, y quedandome un tiempo T, el numero de cofres y el oro total que consigo recoger
   Solucion sol = resolver(oro, c_tiempo, M, tiempo, n_cofres);

   // escribir sol
   cout << sol.oro << endl;
   cout << sol.cofres << endl;

   // Recuperar la solucion desde la matriz
   int i = n_cofres;
   int j = tiempo;
   while( i > 0 && j > 0){

	   // Si la solucion del subproblema no es no coger el cofre
	   if(M[i][j].oro != M[i-1][j].oro ){
		   // La solucion es coger el cofre, asi que lo marco
		   marcado[i-1] = true;
		   // Gasto el tiempo
		   j -= 3*c_tiempo[i-1];
	   }

	   // En cualquier caso, se pasa al siguiente cofre
	   i--;
   }

   for(unsigned int i = 0; i < marcado.size(); i ++){
	   if(marcado[i]){
		   cout << c_tiempo[i] << " " << oro[i] << endl;
	   }
   }

   cout << "---" << endl;
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


//Solucion no_relleno = {-1,-1};
////	cout << "Resolviendo " << tipos << " " << tiempo << endl;
//if(tipos <= 0 && tiempo <= 0){
////		cout << "CASO BASE" << endl;
//	return {0,0};
//}
//else if(M[tipos][tiempo] != no_relleno){
////		cout << "YA RESUELTO CON SOL " << M[tipos][tiempo].cofres << " " << M[tipos][tiempo].oro << endl;
//	return M[tipos][tiempo];
//}
//else{
//	Solucion tomar = {0,0};
//	Solucion no_tomar;
////		cout << "RESOLVIENDO" << endl;
//
//	//Compruebo si me queda tiempo para recoger el cofre
//	if(tiempo > 3*tiempos[tipos-1] ){
//		// Si elijo el cofre de tipo tipos
//		if(M[tipos-1][tiempo - 3*tiempos[tipos-1]]  != no_relleno){
//			tomar = M[tipos-1][tiempo - 3*tiempos[tipos-1]];
//		}
//		else{
//			M[tipos-1][tiempo - 3*tiempos[tipos-1]] = resolver(oro,tiempos,marcado,M,tiempo-3*tiempos[tipos-1], tipos-1);
//			tomar = M[tipos-1][tiempo - 3*tiempos[tipos-1]];
//		}
//	}
//
//	// Si no elijo ese cofre
//	if( M[tipos-1][tiempo] != no_relleno){
//		no_tomar = M[tipos-1][tiempo];
//	}
//	else{
//		M[tipos-1][tiempo] = resolver(oro,tiempos,marcado,M,tiempo,tipos-1);
//		no_tomar = M[tipos-1][tiempo];
//	}
//
//	if(tomar.oro + oro[tipos-1] > no_tomar.oro){
//		M[tipos][tiempo].cofres = tomar.cofres+1;
//		M[tipos][tiempo].oro = tomar.oro + oro[tipos-1];
//		marcado[tipos-1] = true;
//		return tomar;
//	}
//	else{
//		M[tipos][tiempo] = no_tomar;
//		return no_tomar;
//	}
//}
