
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include "Matriz.h"  // propios o los de las estructuras de datos de clase
using namespace std;

enum L {a,b,c};
char T[3][3] = {{'b','b','a'},{'c','b','a'},{'a','c','c'}};
char C[3] = {'a','b','c'};
unordered_map<char, L> A({{'a',a},{'b',b},{'c',c}});

char operar(L op1, L op2){
	int t = T[op1][op2];
	return C[A[t]];
}

struct Letras{

	vector<bool> b ;

	Letras(){
		b = {false,false,false};
	}

	Letras(bool a1, bool b1, bool c1){
		b[0] = a1;
		b[1] = b1;
		b[2] = c1;
	}

	string texto () const {
		string s1 = (b[0])? "A" : "_";
		string s2 = (b[1])? "B" : "_";
		string s3 = (b[2])? "C" : "_";

		string s = "(" + s1 + "," + s2 + "," + s3 + ")";


		return s;
	}

	void set(char ch){
		b[A[ch]] = true;
	}
};

inline std::ostream & operator<<(std::ostream & out, Letras const& m) {
   out << m.texto() ;
   return out;
}


/*
 * Recurrencia:
 *             {  p[i]  si i+1 == j
 *             {
 * mult(i,j) = {  0 (vacio) si i >= j
 * 			   {
 *             {  U ( mult(i,t) , mult(t,j) ) para i < t < j en otro caso
 *
 * La idea es ver a qu� letras puedo llegar partiendo la cadena p por diferentes sitios
 */
bool resolver(string const & s, Matriz<Letras> & M) {

	for(int k = 2; k < M.numfils(); k++){
		int i = 0;
		for(int j = k; j < M.numcols(); j++){
			for(int l = i+1; l < j; l++){
				for(int o1 = 0; o1 < 3; o1++){
					if(M[i][l].b[o1]){
						for(int o2 = 0; o2 < 3; o2++){
							if(M[l][j].b[o2]){
								M[i][j].set(operar(L(o1), L(o2)));
							}
						}
					}
				}

			}

			i++;
		}
	}

	return M[0][M.numcols()-1].b[0];
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   
   // leer los datos de la entrada
   string s;
   cin >> s;
   if (!std::cin)  // fin de la entrada
      return false;
   
   Matriz<Letras> M(s.length()+1, s.length()+1);

   for(int i = 0 ; i < M.numfils()-1 ; i++){
	   M[i][i+1].set(s[i]);
   }

   string sol = (resolver(s,M))? "SI" : "NO" ;
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


/*
 * Codigo parecido al de los tablones, pero esta version usa una matriz de s.len + 2 x s.len + 2
 *
 * for(int k = 2; k < M.numfils(); k++){
		int i = 1;
		for(int j = k+1; j < M.numcols(); j++){
			cout << "Para la casilla " << i << "," << j << endl;
			for(int l = i+1; l < j; l++){
				// Mal estos calculos
				cout << "(" << i << "," << l << ")" << " y la (" << l << "," << j << ")" << endl;
				cout << M[i][l] <<  "," << M[l+1][j] << endl;
				for(int o1 = 0; o1 < 3; o1++){
					if(M[i][l].b[o1]){
						cout << "La primera tiene " << C[o1] << endl;
						for(int o2 = 0; o2 < 3; o2++){
							if(M[l][j].b[o2]){
								cout << "La segunda tiene " << C[o2] << endl;
								M[i][j].set(operar(L(o1), L(o2)));
								cout << M << endl;
							}
						}
					}
				}

			}

			i++;
		}
	}

	return M[1][M.numcols()-1].b[0];
 *
 *
 *
 */
