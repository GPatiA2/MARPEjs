
// Guillermo Garcia Patiño Lenza

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include "EnterosInf.h"
#include "Matriz.h"
using namespace std;

struct Nodo {
	int tiempo;          // El tiempo que llevo acumulado
	vector<bool> tasig;  // tasig[i] = true si el trabajo i ya ha sido asignado a un funcionario
	int k;               // Ultima posicion del vector tasig llena
	int est;

    Nodo(int n){
		tiempo = 0;
		tasig = vector<bool>(n, false);
		k = -1;
		est = 0;
    }

    Nodo(Nodo const & other){
    	tiempo = other.tiempo;
    	tasig = vector<bool>(other.tasig);
    	k = other.k;
    	est = other.est;
    }

    bool operator< (Nodo const & otro) const {
    	return this->est > otro.est;
    }

};

void calcularMinimos(Matriz<int> const & M, vector<int> & V){

	for(int i = M.numfils()-1 ; i >= 0; i--){
		int val = M[i][0];
		for(int j = 1; j < M.numcols(); j++){
			val = (M[i][j] < val)? M[i][j] : val;
		}
		if(i+1 < M.numfils()){
			val += V[i+1];
		}
		V[i] = val;
	}

}


// La solucion es el resultado de sumar los valores de la matriz que representa la tupla S
//   La tupla S = {S0,....,Sn-1} contiene en Si el trabajo al que asigno al funcionario i-ésimo
//   El valor obtenido por la tupla S es la suma de los valores M[i][Si] para cada Si de la matriz M
//
// Las restricciones implícitas, me dicen que no puede haber dos Si con el mismo trabajo asignado
//
// Para obtener una cota inferior suficientemente grande para que la poda sea efectiva, asumiré que los
//   funcionarios a los que aún no he asignado trabajo realicen el trabajo en el que menos tiempo tardan
//   de entre todos. Esta cota inferior no proporcionará valores demasiado altos, pero es muy eficiente de
//   calcular, ya que puedo guardar las estimaciones en un vector que calculo antes de empezar la búsqueda
//   en el espacio de estados en tiempo O(n^2).
//
// El factor de ramificacion del arbol del espacio de estados esta en [N,1] , puesto que para funcionario puedo
//   elegir entre N trabajos, N-1 para el siguiente funcionario... hasta que en el ultimo solo pueda elegir un trabajo
// Por otro lado, cualquier solucion al problema esta a profundidad N, puesto que tengo que dar un trabajo a cada
//   funcionario obligatoriamente
// Si resultara que la eleccion de la cota no poda nada, no habria perdido nada por calcularla, puesto que el coste del
//   algoritmo es O(n^2) igualmente.
// En otro caso, gastar O(n^2) de tiempo para calcular las estimaciones, reduce el numero de nodos generados por el
//   algoritmo

int resolver(Matriz<int> const & M) {

	int n = M.numcols();

	// Calculo de las estimaciones
	vector<int> sumaMins(M.numcols());
	calcularMinimos(M, sumaMins);

	Nodo Y(n);
	Y.est = sumaMins[Y.k + 1];

	priority_queue<Nodo> pq;
	pq.push(Y);

	int coste_mejor = EntInf::_intInf;

	while(!pq.empty() && pq.top().est < coste_mejor){
		Y = pq.top();
		pq.pop();

		for(int i = 0; i < n; i++){
			if(!Y.tasig[i]){
				Nodo X(Y);
				X.tasig[i] = true;
				X.k++;
				X.tiempo += M[X.k][i];
				if(X.k != n-1){
					X.est = X.tiempo + sumaMins[X.k+1];
					if(X.est < coste_mejor){
						pq.push(X);
					}
				}
				else{
					coste_mejor = (X.tiempo < coste_mejor)? X.tiempo : coste_mejor;
				}

			}
		}
	}

	return coste_mejor;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuraciÃ³n, y escribiendo la respuesta
bool resuelveCaso() {
   
   // leer los datos de la entrada
   int t;
   cin >> t;
   if (t == 0)
      return false;

   Matriz<int> M(t,t,0);
   for(int i = 0; i < t; i++){
	   for(int j = 0; j < t; j++){
		   cin >> M[i][j];
	   }
   }
   int sol = resolver(M);
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
