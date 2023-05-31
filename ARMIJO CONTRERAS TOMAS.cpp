#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <conio.h>

using namespace std;

const int agujero = -1;
const int resorte = -2;
const int tepe = -3;
const int tepe2 = -4;
const int vacio = 0;
const int TAMy = 20;
const int TAMx = 10;
const int bola = 777;


int iniciar(int matriz[TAMy][TAMx]) {
	for (int i = 0; i < TAMy; i++){
		for (int p = 0; p < TAMx; p++){
			matriz[i][p] = 0;
		}
	}
	return matriz[TAMy][TAMx];
}

int generaragujeros (int matriz[TAMy][TAMx]) {
	int c = 8;
	int i = 0;
	while (i < c) {
		int o = (rand() % 19) + 1;
		int u = rand() % 10;
		if (matriz[o][u] == vacio) {
			matriz[o][u] = resorte;
			i++;
		}
	}
	return matriz[TAMy][TAMx];
}

int generartepe (int matriz[TAMy][TAMx]) {
	int c = 1;
	int i = 0;
	while (i < c) {
		int o = (rand() % 19) + 1;
		int u = rand() % 10;
		if (matriz[o][u] == vacio) {
			matriz[o][u] = tepe;
			i++;
		}
	}
	return matriz[TAMy][TAMx];
}

int generartepe2 (int matriz[TAMy][TAMx]) {
	int c = 1;
	int i = 0;
	while (i < c) {
		int o = (rand() % 19) + 1;
		int u = rand() % 10;
		if (matriz[o][u] == vacio) {
			matriz[o][u] = tepe2;
			i++;
		}
	}
	return matriz[TAMy][TAMx];
}

int generarresortes (int matriz[TAMy][TAMx]) {
	int c = 8;
	int i = 0;
	while (i < c) {
		int o = (rand() % 19) + 1;
		int u = rand() % 10;
		if (matriz[o][u] == vacio) {
			matriz[o][u] = agujero;
			i++;
		}
	}
	return matriz[TAMy][TAMx];
}

int generarpuntos (int matriz[TAMy][TAMx]) {
	int c = 20;
	int i = 0;
	while (i < c) {
		int o = (rand() % 19) + 1;
		int u = rand() % 10;
		int punt = rand() % 10;
		if (matriz[o][u] == vacio) {
			matriz[o][u] = punt;
			i++;
		}
	}
	return matriz[TAMy][TAMx];
}

int traducirmatriz(int matriz[TAMy][TAMx]) {
	for (int i = 0; i < TAMy; i++) {
		for (int p = 0; p < TAMx; p++) {
			if (matriz[i][p] == vacio) {
				cout << "+";
			}
			else if (matriz[i][p] == agujero) {
				cout << "A";
			}
			else if (matriz[i][p] == resorte) {
				cout << "R";
			}
			else if (matriz[i][p] == tepe || matriz[i][p] == tepe2) {
				cout << "T";
			}
			else if ((matriz[i][p] == 1) or (matriz[i][p] == 2) or (matriz[i][p] == 3) or (matriz[i][p] == 4) or (matriz[i][p] == 5) or (matriz[i][p] == 6) or (matriz[i][p] == 7) or (matriz[i][p] == 8) or (matriz[i][p] == 9)) {
				cout << matriz[i][p];
			}
			else if (matriz[i][p] == bola) {
				cout << "X";
			}
		}
		cout << endl;
	}
	return matriz[TAMy][TAMx];
}




int main(){
	srand(time(NULL));
	
    int tablero[TAMy][TAMx];
    bool flag = true;
    int puntajet = 0;
    int posiy = 0, posix = rand() % 11;
    int b = 1;
    
    iniciar(tablero);
    generaragujeros(tablero);
    generarresortes(tablero);
    generartepe(tablero);
    generartepe2(tablero);
    generarpuntos(tablero);
    
    
    int tp1y = 0, tp1x = 0, tp2y = 0, tp2x = 0; //coordenadas de ambos teletransportes
    
    for (int i = 0; i < TAMy; i++){
		for (int p = 0; p < TAMx; p++){
			if (tablero[i][p] == tepe) {
				tp1y = i;
				tp1x = p;
			}
			
			if (tablero[i][p] == tepe2) {
				tp2y = i;
				tp2x = p;
			}
		}
	}
    
    auto start = chrono::steady_clock::now();
    
    int primeraejecucion = 0;
    
    while (flag) {
    	system("cls");
    	
    	tablero[posiy][posix] = bola;
    	
    	if (primeraejecucion == 0) {
    		traducirmatriz(tablero);
			cout << "Puntaje: " << puntajet << endl;
			getch();
			system("cls");
			primeraejecucion += 1;
		}
		
		tablero[posiy][posix] = vacio;
		posiy = posiy + b;
		int r = ((rand() % 3) - 1);
		posix = posix + r;
		while (posix == 10 or posix == -1) {
			posix = posix - r;
			r = ((rand() % 3) - 1);
			posix = posix + r;
			if (posix != 10 and posix != -1) {
				break;
			}
		}
		
		if (tablero[posiy][posix] == vacio) {
			tablero[posiy][posix] == bola;
		}
		if (tablero[posiy][posix] == resorte){
			while (posiy > 0) {
				posiy -= 1;
				if (tablero[posiy][posix] == resorte) {
					posiy += 1;
					break;
				}
				if (tablero[posiy][posix] == tepe) {
					posiy = (tp2y - 1); //check después, lo deje para tp y seguir volando como en portal. si genera problema cambiar a que se detenga (el - a un + y agregar break).
					posix = tp2x;
				}
				if (tablero[posiy][posix] == tepe2) {
					posiy = (tp1y - 1);
					posix = tp1x;
				}
				if (tablero[posiy][posix] == agujero) {
					tablero[posiy - b][posix - r] = vacio;
					cout << "GAME OVER. el resorte te lanzo a un agujero." << endl;
					flag = false;
				}
			}
		}
		if (tablero[posiy][posix] == tepe) {
			posiy = (tp2y + 1);
			posix = tp2x;
		}
		if (tablero[posiy][posix] == tepe2) {
			posiy = (tp1y + 1);
			posix = tp1x;
		}
		if ((tablero[posiy][posix] == 1) or (tablero[posiy][posix] == 2) or (tablero[posiy][posix] == 3) or (tablero[posiy][posix] == 4) or (tablero[posiy][posix] == 5) or (tablero[posiy][posix] == 6) or (tablero[posiy][posix] == 7) or (tablero[posiy][posix] == 8) or (tablero[posiy][posix] == 9)) {
			puntajet += tablero[posiy][posix];
			tablero[posiy][posix] = vacio;
		}
		if (tablero[posiy][posix] == agujero) {
			tablero[posiy - b][posix - r] = vacio;
			cout << "GAME OVER. caiste en un agujero." << endl;
			flag = false;
		}
		if (posiy == 20) {
			cout << "GAME OVER. la pelota llego al final" << endl;
			flag = false;
		}
		
		
		tablero[posiy][posix] = bola;
		traducirmatriz(tablero);
		cout << "Puntaje: " << puntajet << endl;
		
		
		getch();
	}
	auto end = chrono::steady_clock::now(); // detiene el temporizador
    auto diff = end - start; // calcula el tiempo transcurrido
    
    float tiempo = (chrono::duration<double, milli>(diff).count()) / 1000;
    
    cout << "Tiempo transcurrido: " << tiempo << " segundos" << endl;
	
	
	return 0;
}