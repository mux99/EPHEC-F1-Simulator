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
	//						2 la clef de mémoire partagée (best lap) [int]
	//						3 la clef de mémoire partagée (best q1) [int]
	//						4 la clef de mémoire partagée (best q2) [int]
	//						5 la clef de mémoire partagée (best q3) [int]
	//						6 multiplicateur de vitesse [int]
	//						7 temp max [ms][int]

	//	le but est de générer trois temps et de mettre a jour si nécésaire les diférantes listes
	//		puis ajouter ces temps a un total et recommancer jusque a ce que le total atteigne le temps max
	// !! on ne peut pas dépasser le temps max!
}