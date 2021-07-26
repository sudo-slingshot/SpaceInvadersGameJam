#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <string.h>
#include "fctsauvegarde.h"

void ecritureSauvegarde(int numeroVague,int xJoueur, int vieJoueur,int score)
{
	FILE* sauvegarde=fopen("sauvegarde.txt","w+");
	fwrite(&numeroVague,sizeof(numeroVague),1,sauvegarde);
	fwrite(&xJoueur,sizeof(xJoueur),1,sauvegarde);
	fwrite(&vieJoueur,sizeof(vieJoueur),1,sauvegarde);
	fwrite(&score,sizeof(score),1,sauvegarde);
	fclose(sauvegarde);
}

int* lectureSauvegarde()
{
	FILE* sauvegarde=fopen("sauvegarde.txt","r");
	int *tab=NULL;
	tab=(int*)malloc(4*sizeof(int));
	fread(tab,sizeof(int),4,sauvegarde); 
	fclose(sauvegarde);
	return(tab);
}

void saveHighscore(char* score,char* name)
{
	int inLeaderbord=0;
	char* temposcore=score;
	char* temponame=name;
	FILE* saveHighscore=fopen("saveHighscore.txt","r");	
	
	highscore* tab=(highscore*)malloc(10*sizeof(highscore));
	
	for(int j=0;j<10;j++)
	{
		tab[j].nom=(char*)malloc(20*sizeof(char));
		tab[j].score=(char*)malloc(20*sizeof(char));
	}
	
	fscanf(saveHighscore,
				"%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"
				,tab[0].nom,tab[0].score,tab[1].nom,tab[1].score,tab[2].nom,tab[2].score,tab[3].nom,tab[3].score,tab[4].nom,tab[4].score,tab[5].nom,tab[5].score
				,tab[6].nom,tab[6].score,tab[7].nom,tab[7].score,tab[8].nom,tab[8].score,tab[9].nom,tab[9].score);
	//On considere que le tableau est déjà trié 
	
	
	for(int i=0;i<10;i++)
	{
		
		if (atoi(score)>atoi(tab[i].score))
		{
			
			if(strcmp(name,tab[i].nom)!=0)
			{
				temposcore=score;
				temponame=name;
				score=tab[i].score;
				name=tab[i].nom;
				tab[i].nom=temponame;
				tab[i].score=temposcore;
				inLeaderbord=1;			
				
			}
		}
		
	}
	
	fclose(saveHighscore);
	if (inLeaderbord==1)
	{
		saveHighscore=fopen("saveHighscore.txt","w+");
		fprintf(saveHighscore,
					"%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s",
					tab[0].nom,tab[0].score,tab[1].nom,tab[1].score,tab[2].nom,tab[2].score,tab[3].nom,tab[3].score,tab[4].nom,tab[4].score,tab[5].nom,tab[5].score
					,tab[6].nom,tab[6].score,tab[7].nom,tab[7].score,tab[8].nom,tab[8].score,tab[9].nom,tab[9].score);
			
	fclose(saveHighscore);
	}
	
}

highscore* loadLeaderbord()
{
	highscore* tab=(highscore*)malloc(10*sizeof(highscore));
	FILE* saveHighscore=fopen("saveHighscore.txt","r");
	for(int j=0;j<10;j++)
	{
		tab[j].nom=(char*)malloc(20*sizeof(char));
		tab[j].score=(char*)malloc(20*sizeof(char));
	}
	
	fscanf(saveHighscore,
				"%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s "
				,tab[0].nom,tab[0].score,tab[1].nom,tab[1].score,tab[2].nom,tab[2].score,tab[3].nom,tab[3].score,tab[4].nom,tab[4].score,tab[5].nom,tab[5].score
				,tab[6].nom,tab[6].score,tab[7].nom,tab[7].score,tab[8].nom,tab[8].score,tab[9].nom,tab[9].score);

	fclose(saveHighscore);
	return(tab);
}
/*
int main() 
{
	ecritureSauvegarde(1,500,5,1200);
	int *tab;
	tab=lectureSauvegarde();
	for(int i=0;i<4;i++)
	{
		printf("%d\n",tab[i]);
	}
	saveHighscore("11","slingshot");
	
	highscore* tabLead=(highscore*)malloc(10*sizeof(highscore));
	tabLead=loadLeaderbord();	
	printf("%s\n",tabLead[0].nom);
	return 0;
}
*/
