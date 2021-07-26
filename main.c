#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "GfxLib.h" 
#include "BmpLib.h" 
#include "ESLib.h" 

#define LargeurFenetre 800
#define HauteurFenetre 400

typedef struct
{
	int hp;
	float posX;
	float posY;
	int vitesse;
	int score;
	
}vaisseau_joueur;

typedef struct
{
	float posX;
	float posY;
	float vitesse;
	bool state;
	

}vaisseau_tir;

typedef struct{
	int vitesse;
	int posX;
	int posY;
	bool state;
	int tx;
	int ty;
	
}ennemi;

typedef struct
{
	float posX;
	float posY;
	float vitesse;
	bool state;
	

}ennemis_tir;


/*void cercle(float centreX, float centreY, float rayon)
{
	const int Pas = 20; // Nombre de secteurs pour tracer le cercle
	const double PasAngulaire = 2.*M_PI/Pas;
	
	for (int index = 0; index < Pas; ++index) // Pour chaque secteur
	{
		const double angle = 2.*M_PI*index/Pas; // on calcule l'angle de depart du secteur
		triangle(centreX, centreY,
				 centreX+rayon*cos(angle), centreY+rayon*sin(angle),
				 centreX+rayon*cos(angle+PasAngulaire), centreY+rayon*sin(angle+PasAngulaire));
			// On trace le secteur a l'aide d'un triangle => approximation d'un cercle
	}
	
}
*/

void init_joueur(vaisseau_joueur*p)
{
	(*p).hp = 5;
	(*p).posX = 400.0; //ou p->posX
	(*p).posY = 25.0;
	(*p).vitesse = 15;
	(*p).score = 0;
}


//----------------------------------------MISSILES--------------------------------------

//missiles --> tableau de strucutre de missiles
int nombre_missile = 20;
vaisseau_tir missile[20];


void init_tir(vaisseau_tir missile[])
{
	for(int i=0; i < nombre_missile; i++)
	{
		missile[i].vitesse = 0.0125 * hauteurFenetre();
		missile[i].state = false;
	}

}

void affiche_tir(vaisseau_tir missile[])
{
	for (int i=0; i < nombre_missile; i++)
		if(missile[i].state == true)
		{
				couleurCourante(0, 255, 0);
				rectangle(missile[i].posX +4,missile[i].posY,missile[i].posX + 7,missile[i].posY + 10);
				//cercle(missile[i].po sX,missile[i].posY,5);
		}
}

void monter_tir(vaisseau_tir missile[])
{
	for( int i = 0; i < nombre_missile; i++)
	{
		if(missile[i].state == true)
		{
			missile[i].posY += missile[i].vitesse;
			if(missile[i].posY > hauteurFenetre())
				missile[i].state = false;
		}
		
	}
}


void lance_tir(vaisseau_tir missile[], vaisseau_joueur * p)
{
	for(int i = 0; i < nombre_missile; i++)
		{
			if (missile[i].state == false)
			{
				missile[i].state = true;
				missile[i].posX = (*p).posX;
				missile[i].posY = (*p).posY;
				break;
			}
		}
}

//------------------------------------------------TIR ENNEMIS---------------------------
int nombre_missile2 = 10;
ennemis_tir missile2[10];

void init_tir_ennemis(ennemis_tir missile2[])
{
	for(int i=0; i < nombre_missile2; i++)
	{
		missile2[i].vitesse = 0.0125 * hauteurFenetre();
		missile2[i].state = false;
	}

}

void affiche_tir_ennemis(ennemis_tir missile2[])
{
	for (int i=0; i < nombre_missile2; i++)
		if(missile2[i].state == true)
		{
				couleurCourante(255,0, 0);
				rectangle(missile2[i].posX +4,missile2[i].posY,missile2[i].posX + 7,missile2[i].posY + 10);
				//cercle(missile[i].po sX,missile[i].posY,5);
		}
}

void descendre_tir(ennemis_tir missile2[])
{
	for( int i = 0; i < nombre_missile2; i++)
	{
		if(missile2[i].state == true)
		{
			missile2[i].posY -= missile2[i].vitesse;
			if(missile2[i].posY < 0)  
				missile2[i].state = false;
		}
		
	}
}

void tir_ennemis(ennemis_tir missile2[],ennemi ennemis[], int k)
{
	
	//for(int i = 0; i < nombre_missile2; i++)
		if (ennemis[k].state == true)
		
			if (missile2[k].state == false)
			{
				missile2[k].state = true;
				missile2[k].posX = ennemis[k].posX;
				missile2[k].posY = ennemis[k].posY;
				//break;
			}
		
			
}

//----------------------------------------------ENNEMIS----------------------------------

//ennemis --> tableau de structure d'ennemis
const int nombremax_ennemis = 10;
ennemi ennemis[10];


void init_ennemis (ennemi ennemis[])
{
	for(int i = 0; i < nombremax_ennemis ; i++)
		{
			ennemis[i].state = false;
			ennemis[i].vitesse = 0;
			ennemis[i].posX = 0;
			ennemis[i].posY = 0;
			ennemis[i].tx = 15;
			ennemis[i].ty = 15;
		}
}

void affiche_ennemis (ennemi ennemis[])
{
	for(int i = 0; i < nombremax_ennemis ; i++)
		if (ennemis[i].state == true)
		{
			couleurCourante(255,0, 0);
			rectangle(ennemis[i].posX-ennemis[i].tx , ennemis[i].posY -ennemis[i].ty ,ennemis[i].posX+ennemis[i].tx , ennemis[i].posY +ennemis[i].ty);
		}
}


void apparition_ennemis(ennemi ennemis[])
{
	for(int i = 0; i < nombremax_ennemis ; i++)
		if (ennemis[i].state == false)
			{
				modePleinEcran();
				ennemis[i].posX = largeurFenetre() - 50*i ;
				ennemis[i].posY = hauteurFenetre()  ;
				ennemis[i].state = true;
				
			}
	
}


//--------------------------------COLLISIONS-------------------------
void test_collision(vaisseau_tir missile[],ennemi ennemis[], vaisseau_joueur*p)
{
for(int j = 0; j < nombremax_ennemis ; j++)
	if(ennemis[j].state == true)
		{
		for (int i = 0; i<nombre_missile; i++)
			{
			if(missile[i].state == true &&
			   ennemis[j].state == true &&
			  (ennemis[j].posX - ennemis[j].tx)<= missile[i].posX && 
			  (ennemis[j].posX + ennemis[j].tx)>= missile[i].posX &&
			  (ennemis[j].posY - ennemis[j].ty)<= missile[i].posY && 
			  (ennemis[j].posY + ennemis[j].ty)>= missile[i].posY)			  
			  	{
			  	missile[i].state = false;
			  	ennemis[j].state = false;
			  	(*p).score += 10;
			  	}
			} 
		}

}

void test_collision_vaisseau();

//----------------------------------------------------------------------------------------

int main(int argc, char **argv)
{

	//vaisseau_joueur vaisseau = {0,0,0,0,0};
	//init_joueur(&vaisseau);
	//printf(" hp = %d\n posX = %f\n posY = %f\n vitesse = %d\n score = %d\n", vaisseau.hp,vaisseau.posX,vaisseau.posY,vaisseau.vitesse,vaisseau.score);
	
	initialiseGfx(argc, argv);
	prepareFenetreGraphique("S.I.",LargeurFenetre ,HauteurFenetre);
	lanceBoucleEvenements();
	
	
	
	
	return 0;
}

void droite(vaisseau_joueur*p)
{
	
	(*p).posX += (*p).vitesse ;
	
	
	
	
}
void gauche(vaisseau_joueur*p)
{
	(*p).posX -= (*p).vitesse ;
}

//vaisseau
vaisseau_joueur vaisseau = {0,0,0,0,0};


void gestionEvenement(EvenementGfx evenement)
{
	srand(time(NULL));
	static DonneesImageRGB *image = NULL;
	image = lisBMPRGB("vaisseau_joueur.bmp");
	static bool pleinEcran = false; 
	//modePleinEcran();
	monter_tir(missile);
	descendre_tir(missile2);
	test_collision(missile,ennemis, &vaisseau);
	
	//printf("%d , %d\n",largeurFenetre(), hauteurFenetre() );

	//printf("%d \n",  pleinEcran);
	if (rand()%11 <5)
		{
			
			tir_ennemis(missile2,ennemis,rand()%11);
			demandeTemporisation(17);
		}
	rafraichisFenetre();
	switch (evenement)
	{
		
		case Initialisation:
			modePleinEcran();
			init_joueur(&vaisseau);
			init_ennemis (ennemis);
			apparition_ennemis(ennemis);
			init_tir(missile);
			init_tir_ennemis(missile2);
			printf("ca initialise tekas\n");
			demandeTemporisation(20);
			
			break;
	
			
		case Affichage:
		//apparition_ennemis(ennemis);
		//demandeTemporisation(50);
		affiche_tir_ennemis(missile2);
		affiche_tir(missile);
		if (image != NULL) 
		
				//ecrisImage((largeurFenetre()-image->largeurImage)/2, (hauteurFenetre()-image->hauteurImage)/2, image->largeurImage, image->hauteurImage, image->donneesRGB);
				ecrisImage(vaisseau.posX,vaisseau.posY, image->largeurImage, image->hauteurImage, image->donneesRGB);
				
		 	
		 	
		 	
			break;
			
		case Clavier:
			//printf("%c : ASCII %d\n", caractereClavier(), caractereClavier());
			//apparition_ennemis(ennemis);
			
			//TROUVER OU L'ENDROIT OU LE PLACER POUR QU'IL AILLE AU MILLIEU SANS PRESSER UNE TOUCHE SA MERE
			//apparition_ennemis(ennemis);
			switch (caractereClavier())
			{
			
				case 'Z':
				case 'z':
					lance_tir(missile,&vaisseau);
					//tir_ennemis(missile2,ennemis);
					rafraichisFenetre();
					break;
				case 'D':
				case 'd':
				if (vaisseau.posX + vaisseau.vitesse > largeurFenetre() - 1)
					break;
					
					droite(&vaisseau);
					
					rafraichisFenetre();
					
					break;
					
									
				case 'Q':
				case 'q':
				if (vaisseau.posX - vaisseau.vitesse < 0)
					break;
					
					gauche(&vaisseau);
					//printf("%f   %f\n",vaisseau.posX,vaisseau.posY);				
					//demandeTemporisation(17);
					rafraichisFenetre();

					break;
				
				
				
				
				
					
				case 'A': // Pour sortir quelque peu proprement du programme
				case 'a':
					// On libere la structure image,
						// c'est plus propre, meme si on va sortir du programme juste apres
					termineBoucleEvenements();
					break;

				case 'F':
				case 'f':
					pleinEcran = !pleinEcran; // Changement de mode plein ecran
					if (pleinEcran)
						modePleinEcran();
			
						
					else
						redimensionneFenetre(LargeurFenetre, HauteurFenetre);
					break;
			}
			break;

		case Souris: // Si la souris est deplacee
			break;
		
		case Inactivite: // Quand aucun message n'est disponible
			break;
		
	}
	affiche_ennemis(ennemis);

}


