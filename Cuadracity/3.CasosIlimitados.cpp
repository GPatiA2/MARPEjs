
// Guillermo García Patiño Lenza

// Comentario general sobre la soluciÃ³n,
// explicando cÃ³mo se resuelve el problema

#include <iostream>
#include <fstream>
#include <cmath>
#include "Matriz.h"
#include "EnterosInf.h"
using namespace std;

const int DIR = 2;
const int CX[] = {0,1};
const int CY[] = {1,0};

/*
 * Almaceno los resultados de los subproblemas en una matriz M de N*M donde N es el numero de calles horizontales
 *    y M el numero de calles verticales. En cada celda almaceno la longitud del camino desde ese punto hasta el final
 *
 * Si una celda de la matriz contiene +infinito quiere decir que no existen caminos desde ese punto
 * Si una celda de la matriz contiene 0 quiere decir que el valor de esa posicion no ha sido calculado
 *
 * Cada subproblema viene definido por las dos coordenadas del punto desde el que comienza el camino.
 *
 *                      { 1    si i == 0 && j == 0 && d >= 0 && C[i][j] == '.'
 * cuadracity(i,j,d) =  {
 *                      { 0    si C[i][j] == 'P'
 *                      {
 *                      { 0    si ( i > 0 && j > 0 && d < 0 )
 *                      {
 *                      { sum(cuadracity(x,y,d-1)) si i > 0 && j > 0 && d > 0 && C[i][j] == '.'
 *
 * Donde (x,y) son las coordenadas de las adyacentes a [i][j] que están dentro de la matriz al sur y al
 *    este (que son las unicas direcciones a las que se puede ir)
 *
 * Hago programación diámica ascendente con 1 matriz, puesto que si relleno de izquierda a derecha y de
 *    arriba a abajo, tengo disponibles los valores de la matriz para el d anterior
 */

bool valido(int f, int c, int mx, int my){
	bool b1  = 0 <= f && f < mx;
	bool b2  = 0 <= c && c < my;

	return b1 && b2;
}

int resolver(Matriz<char> const & C, Matriz<int> & M, int d) {

	for(int k = 1; k <= d; k++){
		for(int i = 0; i < M.numfils(); i++){
			for(int j = 0; j < M.numcols(); j++){
				if(C[i][j] == 'P'){
					M[i][j] = 0;
				}
				else{
						for(int v = 0; v < DIR; v++){
							int x = i + CX[v];
							int y = j + CY[v];
							if(valido(x,y,M.numfils(),M.numcols())){
								M[i][j] += M[x][y];
							}
						}
				}
			}
		}
	}

	return M[0][0];
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuraciÃ³n, y escribiendo la respuesta
bool resuelveCaso() {
   
   // leer los datos de la entrada
   int f;
   int c;
   cin >> f;
   if (!std::cin)  // fin de la entrada
      return false;
   cin >> c;

   Matriz<char> C(f,c);
   for(int i = 0; i < f; i ++){
	   for(int j = 0; j < c; j++){
		   cin >> C[i][j];
	   }
   }
   
   Matriz<int> M(f, c, 0);
   f --;
   c --;
   M[f][c] = 1;
   int d = f+c;
   int sol = resolver(C, M, d);
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
