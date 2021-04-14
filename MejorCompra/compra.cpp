

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include "EnterosInf.h"
#include "Matriz.h"
using namespace std;

struct Nodo {
	int precio;              // El dinero que llevo gastado
	vector<int> prodsuper;  // prodsuper[i] numero de productos comprados en el supermercado i
	int k;                   // Ultimo producto comprado
	int est;                 // Estimacion del coste

    Nodo(int n){
		precio = 0;
		prodsuper = vector<int>(n, 0);
		k = -1;
		est = 0;
    }

    Nodo(Nodo const & other){
    	precio = other.precio;
    	prodsuper = vector<int>(other.prodsuper);
    	k = other.k;
    	est = other.est;
    }

    bool operator< (Nodo const & otro) const {
    	return this->est > otro.est;
    }

};

void calcularMinimos(Matriz<int> const & M, vector<int> & V){

	for(int i = M.numcols()-1 ; i >= 0; i--){
		int val = M[0][i];

		for(int j = 1; j < M.numfils(); j++){
			val = (M[j][i] < val)? M[j][i] : val;
		}


		if(i+1 < M.numcols()){
			val += V[i+1];
		}
		V[i] = val;
	}

}


int resolver(Matriz<int> const & M) {

	int supermercados = M.numfils();
	int productos = M.numcols();

	// Calculo de las estimaciones
	vector<int> sumaMins(M.numcols());
	calcularMinimos(M, sumaMins);

	Nodo Y(supermercados);
	Y.est = sumaMins[Y.k + 1];

	priority_queue<Nodo> pq;
	pq.push(Y);

	int coste_mejor = EntInf::_intInf;

	while(!pq.empty() && pq.top().est < coste_mejor){
		Y = pq.top();
		pq.pop();

		for(int i = 0; i < supermercados; i++){
			if(!(Y.prodsuper[i] >= 3)){
				Nodo X(Y);
				X.prodsuper[i]++;
				X.k++;
				X.precio += M[i][X.k];
				if(X.k != productos-1){
					X.est = X.precio + sumaMins[X.k+1];
					if(X.est < coste_mejor){
						pq.push(X);
					}
				}
				else{
					coste_mejor = (X.precio < coste_mejor)? X.precio : coste_mejor;
				}

			}
		}
	}

	return coste_mejor;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   
   // leer los datos de la entrada
	int cprueba;
	cin >> cprueba;
	for(int q = 0; q < cprueba; q++){
		int productos;
		int supermercados;
		cin >> supermercados;
		cin >> productos;

	   Matriz<int> M(supermercados,productos,0);
	   for(int i = 0; i < supermercados; i++){
		   for(int j = 0; j < productos; j++){
			   cin >> M[i][j];
		   }
	   }
	   int sol = resolver(M);
	   cout << sol << endl;
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
   
   resuelveCaso();
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}
