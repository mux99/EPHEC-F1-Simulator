#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int get_time() {
	return rand() % ( + 1 - 25000) + 25000;
};

/* ----MAIN----*/
int main(int argc, char const *argv[])
{
	srand(time(NULL));
	//les paramètres sont	1 l'index de la voiture dans la mémoire partagée [int]
	//						2 la clef de mémoire partagée [int]
	//						3 multiplicateur de vitesse [int]
	//						4 nombre de tours [int]
	// le but ici est de génèrer un temp avec get time et de le rajouter a l'index correspondant de la mémoire partagée
	//		puis d'attentre le même temp divisé par le multiplicateur
	//		ensuite génerer le temps suivant etc... jusque a avoir fait le nombre de tours recu en paramètres
}