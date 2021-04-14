
// Guillermo Garcia Patiño Lenza
// MAR235

// Comentario general sobre la soluciÃ³n,
// explicando cÃ³mo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <sstream>
#include "Matriz.h"
using namespace std;


struct Nodo{
	int k;               //Marca la último carro revisado
	vector<bool> usado;  //Marca qué caminos han sido ya limpiados
	int cal;
	int est;

	Nodo (int n) {
		k = -1;
		usado = vector<bool>(n,false);
		cal = 0;
		est = 0;
	}

	Nodo (Nodo const & other){
		k = other.k;
		usado = vector<bool>(other.usado);
		cal = other.cal;
		est = other.est;
	}

	bool operator< (Nodo const & other) const{
		return this->est < other.est;
	}
};


void calculaMaximos(Matriz<int> const & M, vector<int> & maximos){
	for(int i = M.numfils()-1; i >= 0; i--) {
		int maxtmp = -1;
		for(int j = 0; j < M.numcols(); j++){
			maxtmp = max(maxtmp, M[i][j]);
		}

		maximos[i] = maxtmp;
		if(i+1 < M.numfils()){
			maximos[i] += maximos[i+1];
		}
	}

}

/*
 * Para resolver el problema trato de explorar todas las posibles asignaciones de carros a carreteras
 *
 * La solucion es una tupla S = {S1,S2,....} donde cada Si representa el camino al que asigno el carro i-esimo
 * La restricción implícita es que en la tupla S no puede aparecer dos veces el mismo camino
 * La restricción explícita es que la solución se calcula sumando los valores de la matriz [i][Si] para cada elemento
 *    de la tupla S , y que no
 *
 * Para obtener una cota superior a las posibles soluciones a las que me pueda llevar una solucion parcial llena
 *   hasta k, calculo un vector que contiene en la posicion i la suma de las máximas calidades de los carros desde
 *   el carro i hasta el n. La estimación se calcula sumando al coste hasta ese punto con el contenido de la pos del vector
 *   correspondiente.
 *
 */
int resolver(int n_carros, vector<int> const & carros, vector<int> const & caminos, Matriz<int> const & calidad, vector<int> const & estim) {
	priority_queue<Nodo> pq;

	Nodo Y(caminos.size());
	Y.est = estim[Y.k + 1];

	pq.push(Y);
	int max_benef = 0;

	while(!pq.empty() && pq.top().est > max_benef){
		Y = pq.top();
		pq.pop();

		for(unsigned int i = 0; i < Y.usado.size(); i++){
			if(!Y.usado[i] && carros[Y.k+1] <= caminos[i]){
				Nodo X(Y);
				X.usado[i] = true;
				X.k ++;
				X.cal += calidad[X.k][i];

				if(X.k == n_carros-1){
					max_benef = max(max_benef, X.cal);
				}else{
					X.est = X.cal + estim[X.k + 1];
					if(X.est > max_benef){
						pq.push(X);
					}
				}
			}
		}
	}

	return max_benef;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuraciÃ³n, y escribiendo la respuesta
void resuelveCaso() {
   
   // leer los datos de la entrada
   vector<int> carros;
   vector<int> caminos;

   int n_carros;
   int n_caminos;

   cin >> n_carros;
   cin >> n_caminos;

   for(int i = 0; i < n_carros; i++){
	   int v;
	   cin >> v;
	   carros.push_back(v);
   }

   for(int i = 0; i < n_caminos; i++){
	   int v;
	   cin >> v;
	   caminos.push_back(v);
   }

   Matriz<int> M(carros.size(), caminos.size(), 0);
   for(unsigned int i = 0; i < carros.size(); i++){
	   for(unsigned int j = 0; j < caminos.size(); j++){
		   cin >> M[i][j];
	   }
   }

   vector<int> sumaMax(carros.size(),0);


   calculaMaximos(M, sumaMax);
   if(n_carros != 0){
	   int sol = resolver(n_carros, carros, caminos, M, sumaMax);

	   cout << sol << endl;
   }
   else{
	   cout << "0" << endl;
   }
   // escribir soluciÃ³n
}

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
   
   int numCasos;
   std::cin >> numCasos;
   for (int i = 0; i < numCasos; ++i)
      resuelveCaso();
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}
