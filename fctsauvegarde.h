#ifndef DEF_FCTSAUVEGARDE
#define DEF_FCTSAUVEGARDE

typedef struct
{
	char* nom;
	char* score;
}highscore;

void ecritureSauvegarde(int numeroVague,int xJoueur, int vieJoueur,int score);


int* lectureSauvegarde();


void saveHighscore(char* score,char* name);


highscore* loadLeaderbord();

#endif
