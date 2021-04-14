
// Nombre y Apellidos

// Comentario general sobre la soluciÃ³n,
// explicando cÃ³mo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include "EnterosInf.h"
#include "Matriz.h"
using namespace std;

struct Nodo{
	int k;         // Ultimo colocado
	int sat;       // Satisfaccion de la sol
	vector<bool> ocupado; // Sitios ocupados
	int est;       // Cota superior de la mejor solucion alcanzable desde este nodo
	int sup;       //

	Nodo(int l){
		sat = 0;
		k = -1;
		ocupado = vector<bool>(l,false);
		est = 0;
		sup = 0;
	}

	Nodo(Nodo const & other){
		k = other.k;
		sat = other.sat;
		ocupado = vector<bool>(other.ocupado);
		est = other.est;
		sup = other.sup;
	}

	bool operator< (Nodo const & other) const {
		return this->est < other.est;
	}
};

/*
 * Esta funcion estima que voy a obtener algo mejor a lo que realmente obtendre
 * Como el problema es de maximización, buscaré obtener una cota superior a la mejor solucion que
 *     puedo obtener desde este nodo.
 *
 * Este valor se usa para no explorar nodos cuyo beneficio optimista no sea superior al beneficio real
 *    de la mejor solucion encontrada
 */
int beneficioOptimista(Nodo e, Matriz<int> const & S){

	int sat = e.sat;

	for(int j = e.k; j < S.numcols(); j++){
		int psat = 0;
		for(int i = 0; i < S.numfils(); i++){
			if(!e.ocupado[i]){
				psat = max(psat, S[i][j]);
			}
		}
		sat += psat;
	}

	return sat;
}

/*
 * En cada etapa siento a alguien en un hueco, y paso a la siguiente persona
 * Voy iterando sobre los huecos que hay en la mesa y asigno una persona para que se siente en él
 * En el bucle que va mirando los diferentes huecos, itero una vez más para representar que nadie se siente
 *    en ese hueco.
 *
 * Para asegurarme de que el hermano siempre aparece, intercambio y pongo al hermano en la primera posicion y lo siento
 * en cada uno de los sitios
 */
int resolver(vector<int> const & N, vector<int> const & E, Matriz<int> const & S, int L, int num_huecos, int num_ninios) {
	priority_queue<Nodo> pq;
	int beneficio_mejor = 0;

	Nodo Y(num_huecos+1);
	Y.est = beneficioOptimista(Y,S);

	pq.push(Y);

	while(!pq.empty() && beneficioOptimista(pq.top(),S) >= beneficio_mejor){
		Y = pq.top();
		pq.pop();
		for(int i = 0; i < num_huecos+1 ; i++){
			Nodo X(num_huecos+1);
			if(!Y.ocupado[i] && (E[Y.k+1] != i || (E[Y.k+1] == i && Y.sup < L)) && S[i][Y.k+1] >= 0){
				if(Y.k == -1 && i == num_huecos){}
				else{
					X = Nodo(Y);
					X.k ++;
					X.sat += S[i][X.k];

					if(i != num_huecos){
						X.ocupado[i] = true;
					}

					X.est = beneficioOptimista(X,S);

					if(E[X.k] == i){
						X.sup++;
					}

					if(X.k == num_ninios-1){
						if(X.sat >= beneficio_mejor){
							beneficio_mejor = X.sat;
						}
					}
					else{
						if(X.est >= beneficio_mejor){
							pq.push(X);
						}
					}
				}
			}
		}
	}

	return beneficio_mejor;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuraciÃ³n, y escribiendo la respuesta
bool resuelveCaso() {
   
   // leer los datos de la entrada
   int num_ninos;
   int num_huecos;
   int num_hermano;

   cin >> num_ninos;
   if (num_ninos == -1)
      return false;
   
   cin >> num_huecos;
   cin >> num_hermano;

   // Matriz de satisfaccion de cada niño con cada sitio
   Matriz<int> S(num_huecos+1, num_ninos, 0);
   for(int i = 0; i < num_huecos; i++){
	   for(int j = 0; j < num_ninos; j++){
		   cin >> S[i][j];
	   }
   }

   // Cambio la posicion de las satisfacciones del primer niño con la del hermano
   for(int i = 0; i < num_huecos; i++){
	   int tmp;
	   tmp = S[i][num_hermano];
	   S[i][num_hermano] = S[i][0];
	   S[i][0] = tmp;
   }


   // Numeros de lista de cada uno
   vector<int> N(num_ninos,0);
   for(int i = 0; i < num_ninos; i++){
	   N[i] = i;
   }
   // Pongo el numero de lista del hermano el primero
   N[0] = N[num_hermano];
   N[num_hermano] = 0;



   // Calculo el sitio incomodo para cada uno
   vector<int> E(num_ninos,0);
   for(int i = 0; i < num_ninos; i++){
	   E[i] = N[i] % num_huecos;
   }

   // Calculo el numero de veces que alguien puede sentarse en un sitio incomodo
   int L = num_huecos/3;

   int sol = resolver(N,E,S,L, num_huecos, num_ninos);
   
   cout << sol << endl;
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
