
// Nombre y Apellidos

// Comentario general sobre la soluciÃ³n,
// explicando cÃ³mo se resuelve el problema

#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;

struct Cancion{
	int duracion;
	int calidad;
};

struct Nodo{
	int k;    // Ultima cancion puesta
	int h1;   // Hueco en la cara 1
	int h2;   // Hueco en la cara 2
	int cal;  // Calidad acumulada hasta ahora
	float est;  // Cota superior

	Nodo(int n){
		k = -1;
		h1 = n;
		h2 = n;
		cal = 0;
		est = 0;
	}

	Nodo(Nodo const & other){
		k = other.k;
		h1 = other.h1;
		h2 = other.h2;
		cal = other.cal;
		est = other.est;
	}

	bool operator< (Nodo const & other) const {
		return est < other.est;
	}
};

// Algoritmo voraz que elige canciones mientras quepan en la cinta y fracciona al final
//     contando el espacio de las dos caras juntas
float cotaOptimista(Nodo e,  vector<Cancion> const & c){

	int s = e.h1 + e.h2;
	float caux = e.cal;
	unsigned int k = e.k+1;

	while(k < c.size() && c[k].duracion <= s && s > 0){
		s -= c[k].duracion;
		caux += c[k].calidad;
		k++;
	}


	if(s != 0 && k < c.size()){
		caux += (float(s)/float(c[k].duracion))*c[k].calidad;
	}
	return caux;
}


// Completar una solucion
int cotaPesimista(Nodo e, vector<Cancion> const & c){
	unsigned int i = e.k+1;
	while(i < c.size()){
		// Si cabe en la primera cara
		if(e.h1 > 0 && e.h1 >= c[i].duracion){
			e.h1 -= c[i].duracion;
			e.cal += c[i].calidad;
		}
		// Si no, a la segunda
		else if(e.h2 > 0 && e.h2 >= c[i].duracion){
			e.h2 -= c[i].duracion;
			e.cal += c[i].calidad;
		}
		// No ponerla
		i++;
	}
	return e.cal;
}

// En cada etapa de la solucion decido si grabo o no la canción y si la grabo, en qué cara
//   El factor de ramificación es 3, y una solución se encuentra a profuncidad numCaciones
//   Entonces hay 3^numCanciones nodos
// Para generar un hijo se realizan operaciones en coste O(1), y la cota superior de la mejor
//   solucion que se puede alcanzar desde ese nodo se calcula en coste O(numCanciones)
// Además la cota inferior se calcula igualmente en O(numCanciones)
// En total, el coste para cada nodo es O(numCanciones)
int resolver(vector<Cancion> const & c , int dc, int nc) {
	priority_queue<Nodo> pq;

	Nodo Y(dc);
	int beneficio_mejor = cotaPesimista(Y,c);
	Y.est = cotaOptimista(Y,c);

	pq.push(Y);
	while(!pq.empty() && pq.top().est >= beneficio_mejor){
		Y = pq.top();
		pq.pop();
		// En la cara 1
		if(Y.h1 > 0 && Y.h1 >= c[Y.k+1].duracion){
			Nodo X(Y);
			X.k++;
			X.h1 -= c[X.k].duracion;
			X.cal += c[X.k].calidad;
			X.est = cotaOptimista(X,c);
			if(X.k == nc-1){
				if(X.cal >= beneficio_mejor){
					beneficio_mejor = X.cal;
				}
			}
			else{
				if(X.est >= beneficio_mejor){
					pq.push(X);
					int cp = cotaPesimista(X,c);
					if(cp > beneficio_mejor){
						beneficio_mejor = cp;
					}
				}
			}
		}
		// En la cara 2
		if(Y.h2 > 0 && Y.h1 != Y.h2 && Y.h2 >= c[Y.k+1].duracion){
			Nodo X(Y);
			X.k++;
			X.h2 -= c[X.k].duracion;
			X.cal += c[X.k].calidad;
			X.est = cotaOptimista(X,c);
			if(X.k == nc-1){
				if(X.cal >= beneficio_mejor){
					beneficio_mejor = X.cal;
				}
			}
			else{
				if(X.est >= beneficio_mejor){
					pq.push(X);
					int cp = cotaPesimista(X,c);
					if(cp > beneficio_mejor){
						beneficio_mejor = cp;
					}
				}
			}
		}
		// En ninguna cara
		Nodo X(Y);
		X.k++;
		X.est = cotaOptimista(X,c);

		if(X.k == nc-1){
			if(X.cal >= beneficio_mejor){
				beneficio_mejor = X.cal;
			}
		}
		else{
			if(X.est >= beneficio_mejor){
				pq.push(X);
				int cp = cotaPesimista(X,c);
				if(cp > beneficio_mejor){
					beneficio_mejor = cp;
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
   int numCanciones;
   cin >> numCanciones;
   int durCara;
   if (numCanciones == 0)
      return false;
   
   cin >> durCara;
   vector<Cancion> C;
   for(int i = 0; i < numCanciones; i++){
	  int dur;
	  cin >> dur;
	  int cal;
	  cin >> cal;
	  C.push_back({dur,cal});
   }

   // Ordenar las canciones por calidad por unidad de duracion
   sort(C.begin(), C.end(), [](Cancion const & a, Cancion const & b) { return a.calidad/a.duracion > b.calidad/b.duracion ;});

   int sol = resolver(C,durCara, numCanciones);
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
