#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "GfxLib.h" 
#include "BmpLib.h" 
#include "ESLib.h" 
#include <string.h>//Pour utiliser strlen()
#include <glut.h> //Pour utiliser les fonctions de touches release
//#include "SDL/SDL.h"//La librairie SDL_mixer a besoin de SDL pour fonctionner
//#include "SDL/SDL_mixer.h" //Pour etre capabale de jouer des sons



#include "fctsprite.h" //Pour animer les entités et l'arrière plan
#include "fctsauvegarde.h"//Pour afficher leaderboard + sauvegarde

#define LargeurFenetre 1920
#define HauteurFenetre 1000

ensembleAnimation Spaceship;
//Création de l'ensemble d'animation du Background
ensembleAnimation Background;
ensembleAnimation Invader;
ensembleAnimation Invader2;
typedef struct
{
	int hp;
	float posX;
	float posY;
	int vitesse;
	int score;
	int tx;
	int ty;
	
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

//---------------------------------------------Menu-------------------------------------

/*========================================GENERATION DES TEXTES POUR LE MENU PRINCIPAL===========================================*/

//on définit les variables allant stocker les chaines de caractère qui afficheront le menu
//ces variables sont sujet a modification suivant le menu dans lequel nous choisirons d'aller
char *chainetitre = "SPACE INVADERS";
char *chaineplay = "PLAY";
char *chaineleaderboard = "LEADERBOARD";
char *chainemusique = "";
char *chaineonoff = "";
char *chaineonoff2 = "";
char *chainesfx = "";
char *chainequit = "QUIT";
char *entrerpseudo="";
char *pseudo="";


/*====================================CREATION DES CHAINES POUR LE LEADERBOARD==================================================*/
//chaines qui seront actualisées en fonction du classement dans le HOF
char *chainefirst ="";
char *scorefirst="";
char *chainesecond="";
char *scoresecond="";
char *chainethird= "";
char *scorethird="";
char *chaine4="";
char *score4="";
char *chaine5="";
char *score5="";
char *chaine6="";
char *score6="";
char *chaine7="";
char *score7="";
char *chaine8="";
char *score8="";
char *chaine9="";
char *score9="";
char *chaine10="";
char *score10="";

//chaines de caractères pour le rank du leaderboard
char *un="";
char *deux="";
char *trois="";
char *quatre="";
char *cinq="";
char *six="";
char *sept="";
char *huit="";
char *neuf="";
char *dix ="";


/*=======================CREATION DES VARIABLES GLOBALES POUR SAVOIR DANS QUELLES SECTIONS ON SE TROUVE========================*/
int music = 1;
int sfx = 1;
int vague= 0;
int mort;
//on introduit la variable i, qui nous permettra de savoir dans quelle partie du menu nous sommes pour faire les choix en conséquence
int defrubrique = 0;
int lancejeu=0;
//si defrubrique = 0 ==> on est dans les choix du menu principal
//si defrubrique = 1 ==> on est dans les choix du leaderboard
//si defrubrique = 2 ==> on est dans le menu de choix de sauvegarde
//si defrubrique = 3 ==> on joue au jeu, plus aucune hitbox de menu n'est créée

//Création de l'ensemble d'animation du Background
ensembleAnimation Background;

void gestionEvenement(EvenementGfx evenement);

//Fonction pour jouer de la musique

/*void JouerSon(char *nom)
{
	SDL_INIT_AUDIO;
	static Mix_Music *musique;
	Mix_FreeMusic(musique);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024); //Initialisation de l'API Mixer
	musique = Mix_LoadMUS(nom);
	Mix_PlayMusic(musique, 1);
}
//Fonction pour mettre une musique en pause ou reprendre la musique
void PauseSon()
{
	if (Mix_PausedMusic() == 1) //Si la musique est en pause
	{
		Mix_ResumeMusic(); //Reprendre la musique
	}
	else
		{
			Mix_PauseMusic(); //Mettre en pause la musique
		}
}*/

/*=======================FONCTION NOUS PROPOSANT DE REPRENDRE UNE PARTIE SAUVEGARDÉE SI UNE SAUVEGARDE EST STOCKÉE QUAND ON APPUIE SUR PLAY=======================*/

void chargesauvegarde (int wave)
{
	if (wave!=0)
	{
		defrubrique=2;
		chainemusique = "Charger la sauvegarde?";
		chaineonoff = "OUI  NON";
		rafraichisFenetre();
	}//la variable vague communiquera avec le reste du jeu ==> CHANGEMENTS A VENIR AVEC L'INTEGRATION
		else
		//Sinon on lance le jeu
		{
			chainemusique = "";
			chaineonoff = "";
			
			/*if (music==1)//on regarde les préférences utilisateur pour savoir si on joue la musique ou non
			{
				JouerSon("pacman_beginning.wav");
			}
			*/
			
			defrubrique=3;
			lancejeu=1;
		}
		
}

//fonction nous permettant de choisir si on veut charger une partie sauvegardée ou non
void choixsauvegarde(void)
{
	//on regarde si on est dans la zone de clic de la charge de la sauvegarde
	if (ordonneeSouris()<hauteurFenetre()/2 - 40)
			{
				if (ordonneeSouris()>hauteurFenetre()/2 - 80)
				{
					printf("Curseur sur la zone CHARGESAUVEGARDE\n");
					if (abscisseSouris()<largeurFenetre()/2)//on regarde si on clique sur "oui"
					{
						printf("Charger sauvegarde\n");
						//on clear la page
						chainemusique = "";
						chaineonoff = "";
						rafraichisFenetre();
						//charger la sauvegarde
						
						/*if (music==1)//on regarde les préférences utilisateur pour savoir si on joue la musique ou non
						{
							JouerSon("sounds/gamemusic/gamemusic.wav");
						}
						*/
						
						defrubrique=3;
						lancejeu=1;
					}
					if (abscisseSouris()>=largeurFenetre()/2)//on regarde si on clique sur "non"
					{
						printf("Recommencer une partie\n");
						//on clear la page
						chainemusique="";
						chaineonoff="";
						rafraichisFenetre();
						//recommencer a 0
						vague=0;
						
						/*
						if (music==1)//on regarde les préférences utilisateur pour savoir si on joue la musique ou non
						{
							JouerSon("sounds/gamemusic/gamemusic.wav");
							//on lance le jeu du début
						}
						*/
						defrubrique=3;
						lancejeu=1;
					}
				}
			}
}
void genleaderboard()
{
	//on créé tab leaderboard
	highscore* tabLeaderboard=(highscore*)malloc(20*sizeof(highscore));
	tabLeaderboard= loadLeaderbord();
	chainetitre = "LEADERBOARD";
	chaineplay = "";
	chaineleaderboard = "";
	chainemusique ="";
	chaineonoff="";
	chaineonoff2="";
	chainesfx="";
	chainequit="MAIN MENU";
	defrubrique=1;
	
	
	chainefirst=tabLeaderboard[0].nom;
	chainesecond=tabLeaderboard[1].nom;
	chainethird=tabLeaderboard[2].nom;
	chaine4=tabLeaderboard[3].nom;
	chaine5=tabLeaderboard[4].nom;
	chaine6=tabLeaderboard[5].nom;
	chaine7=tabLeaderboard[6].nom;
	chaine8=tabLeaderboard[7].nom;
	chaine9=tabLeaderboard[8].nom;
	chaine10=tabLeaderboard[9].nom;
	scorefirst=tabLeaderboard[0].score;
	scoresecond=tabLeaderboard[1].score;
	scorethird=tabLeaderboard[2].score;
	score4=tabLeaderboard[3].score;
	score5=tabLeaderboard[4].score;
	score6=tabLeaderboard[5].score;
	score7=tabLeaderboard[6].score;
	score8=tabLeaderboard[7].score;
	score9=tabLeaderboard[8].score;
	score10=tabLeaderboard[9].score;
	
	un="1-";
	deux="2-";
	trois="3-";
	quatre="4-";
	cinq="5-";
	six="6-";
	sept="7-";
	huit="8-";
	neuf="9-";
	dix ="10-";
	
	rafraichisFenetre();
	//free(tabLeaderboard);
	
}
//Fonction nous permettant d'afficher l'endroit ou l'utilisateur veut aller dans le menu principal
void choixmenu (void)
{
	if (abscisseSouris()>(largeurFenetre()/2) - 120)
	{
		if (abscisseSouris()<(largeurFenetre()/2) + 120)
		{
			
			//CAS 1 : Le Joueur appuie sur PLAY
			if (ordonneeSouris()<(hauteurFenetre()/2+170))
			{
				if (ordonneeSouris()>(hauteurFenetre()/2)+130)
				{
					printf("Curseur sur zone PLAY\n");
					//on enlève toutes les chaine de caractères présentes, afin de laisser toute la fenetre pour le jeu
					chainetitre="";
					chaineplay="";
					chaineleaderboard="";
					chaineonoff="";
					chaineonoff2="";
					chainemusique="";
					chainesfx="";
					chainequit="";
					chargesauvegarde(vague);
					
					//mettre en lien la fonction permettant de lancer le jeu
				}
			}
			
			//CAS 2 : Le Joueur Appuie sur LEADERBOARD
			if (ordonneeSouris()<((hauteurFenetre()/2)+100))
			{
				if (ordonneeSouris()>((hauteurFenetre()/2)+60))
				{
					printf("Curseur sur la zone LEADERBOARD\n");
					//afficher la page du leaderboard
					//la page devient la page leaderboard
					genleaderboard();
				}
			}
			
			//CAS 3 : Le Joueur appuie sur l'une des deux options proposées par la case musique
			if (ordonneeSouris()<hauteurFenetre()/2 - 40)
			{
				if (ordonneeSouris()>hauteurFenetre()/2 - 80)
				{
					printf("Curseur sur la zone MUSIQUE\n");
					if (abscisseSouris()<largeurFenetre()/2)
					{
						printf("Musique ON\n");
						//activer la musique si elle est désactivée
						
						/*if (sfx==1)
						{
							JouerSon("Sounds/GameMusic/GameMusic2.ogg");
						}
						*/
						music = 1;
						
					}
					if (abscisseSouris()>=largeurFenetre()/2)
					{
						printf("Musique OFF\n");
						//désactiver la musique si elle est activée
						music = 0;
					}
				}
			}
			
			//CAS 4 : Le Joueur appuie sur l'une des deux options proposées par la case SFX
			if(ordonneeSouris()<hauteurFenetre()/2 - 180)
			{
				if(ordonneeSouris()>hauteurFenetre()/2 - 220)
				{
					printf("Curseur sur la zone SFX\n");
					if (abscisseSouris()<largeurFenetre()/2)
					{
						printf("SFX ON\n");
						//activer les SFX si ils sont désactivés
						//JouerSon("Sounds/SFXON/SFXONTEST.wav");
						sfx = 1;
					}
					if (abscisseSouris()>=largeurFenetre()/2)
					{
						printf("SFX OFF\n");
						//désactiver les SFX si ils sont activés
						sfx = 0;
					}
				}
			}
			
			//CAS 5 : Le joueur appuie sur Quit
			if(ordonneeSouris()<hauteurFenetre()/2 - 270)
			{
				if(ordonneeSouris()>hauteurFenetre()/2 - 310)
				{
					printf("Curseur sur la zone QUIT\n");
					//on quitte le jeu
					//Mix_CloseAudio();
					
					termineBoucleEvenements();
				}
			}
		}
	}
	
	
}


void choixleaderboard (void)
{
	if(ordonneeSouris()<hauteurFenetre()/2 - 270)
			{
				if(ordonneeSouris()>hauteurFenetre()/2 - 310)
				{
					printf("Curseur sur la zone MAIN MENU\n");
					//on affiche le menu principal
					chainetitre="SPACE INVADERS";
					chaineplay="PLAY";
					chaineleaderboard="LEADERBOARD";
					chainemusique="";
					chaineonoff="";
					chaineonoff2="";
					chainesfx="";
					chainequit="QUIT";
					
					chainefirst="";
					chainesecond="";
					chainethird="";
					chaine4="";
					chaine5="";
					chaine6="";
					chaine7="";
					chaine8="";
					chaine9="";
					chaine10="";
					scorefirst="";
					scoresecond="";
					scorethird="";
					score4="";
					score5="";
					score6="";
					score7="";
					score8="";
					score9="";
					score10="";
					
					un="";
					deux="";
					trois="";
					quatre="";
					cinq="";
					six="";
					sept="";
					huit="";
					neuf="";
					dix ="";
					
					defrubrique=0;
					rafraichisFenetre();
				}
			}
}

void generationmenu (void)
{
			// On part d'un fond d'ecran noir
			effaceFenetre (0, 0, 0);
			
			afficheImageSansBackGround(getImage(Background),getPixels(Background),0x00,0,0);
				
			//Affichage du titre du jeu
			couleurCourante(210, 210, 210);
			epaisseurDeTrait(3);
			afficheChaine(chainetitre, 40, (largeurFenetre()/2)-strlen(chainetitre)*12, hauteurFenetre() - 120);


			//Affichage du texte play du menu
			
			couleurCourante(210,210,210);
			afficheChaine(chaineplay, 30, (largeurFenetre()/2)- strlen(chaineplay)*10, hauteurFenetre()/2 +140);
			
			//affichage du texte leaderboard du menu
			
			couleurCourante(210,210,210);
			afficheChaine(chaineleaderboard, 30, (largeurFenetre()/2) -strlen(chaineleaderboard)*9.5, (hauteurFenetre()/2)+70);
			
			//affichage du texte pour gérér la musique du jeu
			
			couleurCourante(210,210,210);
			afficheChaine(chainemusique, 30, (largeurFenetre()/2) -strlen(chainemusique)*9.5, (hauteurFenetre()/2)-20);
				
				//affichage de la section permettant d'activer ou de désactiver la musique du jeu
				
				couleurCourante(210,210,210);
				afficheChaine(chaineonoff, 30, (largeurFenetre()/2) -strlen(chaineonoff)*11, hauteurFenetre()/2 -70);
			
			//affichage du texte pour gérer les effets du jeu
			
			couleurCourante(210,210,210);
			afficheChaine(chainesfx, 30, (largeurFenetre()/2) - strlen(chainesfx)*10, hauteurFenetre()/2 - 160);
			
				//affichage de la section permettant d'activer ou de désactiver les sons du jeu
				
				couleurCourante(210,210,210);
				afficheChaine(chaineonoff2, 30, (largeurFenetre()/2) - strlen(chaineonoff)*11, hauteurFenetre()/2 - 210);
			//affichage du bouton quit
			
			couleurCourante(210,210,210);
			afficheChaine(chainequit, 30, largeurFenetre()/2 - strlen(chainequit)*8.5, hauteurFenetre()/2 - 300);
			
			
			
			
			//GESTION DU LEADERBOARD
			
			//création de la chaine de caractère du premier du classement du leaderboard
			couleurCourante(255,215,0);
			afficheChaine(chainefirst, 30, (largeurFenetre()/2)- strlen(chainefirst)*5, hauteurFenetre()/2 +300);
				//création du rank du premier
				couleurCourante(255,215,0);
				afficheChaine(un, 30, (largeurFenetre()/2)- strlen(chainefirst)*5 - 70, hauteurFenetre()/2 +300);
					//affichage du score du premier
						couleurCourante(255,215,0);
						afficheChaine(scorefirst, 30, (largeurFenetre()/2) + strlen(chainefirst)*15, hauteurFenetre()/2 +300);
			
			
			//création de la chaine de caractère du 2nd du classement du leaderboard
			couleurCourante(96,96,96);
			afficheChaine(chainesecond, 30, (largeurFenetre()/2)-strlen(chainesecond)*5 - 500, hauteurFenetre()/2 +250);
				//affichage du rank du 2eme
				couleurCourante(96,96,96);
				afficheChaine(deux, 30, (largeurFenetre()/2)-strlen(chainesecond)*5 - 500 -70, hauteurFenetre()/2 +250);
					//affichage du score du 2eme
					couleurCourante(96,96,96);
					afficheChaine(scoresecond, 30, (largeurFenetre()/2)+strlen(chainesecond)*15 - 500, hauteurFenetre()/2 +250);
			
			//création de la chaine de caractère du 3eme du classement du leaderboard
			couleurCourante(97,78,26);
			afficheChaine(chainethird, 30, (largeurFenetre()/2)-strlen(chainesecond)*5 + 500, hauteurFenetre()/2 +250);
				//affichage du rank du 3eme
				couleurCourante(97,78,26);
				afficheChaine(trois, 30, (largeurFenetre()/2)-strlen(chainesecond)*5 + 500 -70, hauteurFenetre()/2 +250);
					//affichage du score du 3eme
					couleurCourante(97,78,26);
					afficheChaine(scorethird, 30, (largeurFenetre()/2)+strlen(chainethird)*15 + 500, hauteurFenetre()/2 +250);
			
			//création des channels de la place 4 a 10
			//P4
			couleurCourante(210,210,210);
			afficheChaine(chaine4, 30, (largeurFenetre()/2)-strlen(chainesecond)*5 - 650, hauteurFenetre()/2 +100);
				//affichage du rang 4
				couleurCourante(210,210,210);
				afficheChaine(quatre, 30, (largeurFenetre()/2)-strlen(chainesecond)*5 - 650 - 70, hauteurFenetre()/2 +100);
					//affichage du score du 4eme
					couleurCourante(210,210,210);
					afficheChaine(score4, 30, (largeurFenetre()/2)+strlen(chaine4)*15 -500 , hauteurFenetre()/2 +100);
			//P5
			couleurCourante(210,210,210);
			afficheChaine(chaine5, 30, (largeurFenetre()/2)-strlen(chainesecond)*5 - 650, hauteurFenetre()/2 +40);
				////affichage du rang 5
				couleurCourante(210,210,210);
				afficheChaine(cinq, 30, (largeurFenetre()/2)-strlen(chainesecond)*5 - 650 - 70, hauteurFenetre()/2 +40);
					//affichage du score du 5
					couleurCourante(210,210,210);
					afficheChaine(score5, 30, (largeurFenetre()/2)+strlen(chaine5)*15 - 500, hauteurFenetre()/2 +40);
			
			//P6
			couleurCourante(210,210,210);
			afficheChaine(chaine6, 30, (largeurFenetre()/2)-strlen(chainesecond)*5 - 650, hauteurFenetre()/2 -20);
				//affichage du rang 6
				couleurCourante(210,210,210);
				afficheChaine(six, 30, (largeurFenetre()/2)-strlen(chainesecond)*5 - 650 - 70, hauteurFenetre()/2 -20);
					//affichage du score du 6
					couleurCourante(210,210,210);
					afficheChaine(score6, 30, (largeurFenetre()/2)+strlen(chaine6)*15 - 500, hauteurFenetre()/2 -20);
			
			//P7
			couleurCourante(210,210,210);
			afficheChaine(chaine7, 30, (largeurFenetre()/2)-strlen(chainesecond)*5 - 650, hauteurFenetre()/2 -80);
				//affichage du rang 7
				couleurCourante(210,210,210);
				afficheChaine(sept, 30, (largeurFenetre()/2)-strlen(chainesecond)*5 - 650 - 70, hauteurFenetre()/2 -80);
					//affichage du score du 7
					couleurCourante(210,210,210);
					afficheChaine(score7, 30, (largeurFenetre()/2)+strlen(chaine7)*15 - 500, hauteurFenetre()/2 -80);
				
			
			//P8
			couleurCourante(210,210,210);
			afficheChaine(chaine8, 30, (largeurFenetre()/2)-strlen(chainesecond)*5 +450, hauteurFenetre()/2 +100);
				//affichage du rang 8
				couleurCourante(210,210,210);
				afficheChaine(huit, 30, (largeurFenetre()/2)-strlen(chainesecond)*5 + 450 - 70, hauteurFenetre()/2 +100);
					//affichage du score du 8
					couleurCourante(210,210,210);
					afficheChaine(score8, 30, (largeurFenetre()/2)+strlen(chaine8)*15 + 500, hauteurFenetre()/2 +100);
			
			//P9
			couleurCourante(210,210,210);
			afficheChaine(chaine9, 30, (largeurFenetre()/2)-strlen(chainesecond)*5 +450, hauteurFenetre()/2 +40);
				//affichage du rang 9
				couleurCourante(210,210,210);
				afficheChaine(neuf, 30, (largeurFenetre()/2)-strlen(chainesecond)*5 + 450 - 70, hauteurFenetre()/2 + 40);
					//affichage du score du 9
					couleurCourante(210,210,210);
					afficheChaine(score9, 30, (largeurFenetre()/2)+strlen(chaine9)*15 + 500, hauteurFenetre()/2 +40);
			//P10
			couleurCourante(210,210,210);
			afficheChaine(chaine10, 30, (largeurFenetre()/2)-strlen(chainesecond)*5 +450, hauteurFenetre()/2 -20);
				//affichage du rang 10
				couleurCourante(210,210,210);
				afficheChaine(dix, 30, (largeurFenetre()/2)-strlen(chainesecond)*5 + 450 - 90, hauteurFenetre()/2 -20);
					//affichage du score du 10
					couleurCourante(210,210,210);
					afficheChaine(score10, 30, (largeurFenetre()/2)+strlen(chaine10)*15 + 500, hauteurFenetre()/2 -20);
			
			
			//Chaine informative pour entrer le nom du joueur
			couleurCourante(210,210,210);
			afficheChaine(entrerpseudo, 50, (largeurFenetre()/2)-strlen(entrerpseudo)*25, hauteurFenetre()/2);
}


//---------------------------------------------Outils---------------------------------

// Conversion d'une image (largeur*hauteur pixels) de la forme rouge, vert, bleu en entiers rouge, vert, bleu, opacité et rend transparent les pixels noirs

void afficheVar(char *chaine, float taille, float x, float y)
{
    char *pointeurChaine = (char *)chaine;
    const float tailleScaling = taille/120.f;
    
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(tailleScaling, tailleScaling, tailleScaling);
    while (*pointeurChaine)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *pointeurChaine++);
    glPopMatrix();
}
void affiche_hp(vaisseau_joueur*p)
{
    char buffer[10];
    sprintf(buffer, "%d",(*p).hp + 1);
    afficheVar(buffer, 30, 50, 50);
    
}
void affiche_score(vaisseau_joueur*p)
{
    char buffer[10];
    sprintf(buffer, "%d",(*p).score);
    afficheVar(buffer, 30, 1800, 50);
    
}
static int *effaceFond(int largeur, int hauteur, const unsigned char *donnees) {
               const unsigned char *ptrDonnees;
               unsigned char *pixels = (unsigned char*)malloc(largeur*hauteur*sizeof(int));
               unsigned char *ptrPixel;
               int index;
               ptrPixel = pixels;
               ptrDonnees = donnees;
               for (index = largeur*hauteur; index != 0; --index) // On parcourt tous les pixels de l'image
               {
                              ptrPixel[0] = ptrDonnees[0];
                              ptrPixel[1] = ptrDonnees[1];
                              ptrPixel[2] = ptrDonnees[2];
                              ptrPixel[3] = (ptrDonnees[0] == 255 && ptrDonnees[1] == 255 && ptrDonnees[2] == 255) ? 0 : 255;
                              ptrDonnees += 3; // On passe à la première composante du pixel suivant
                              ptrPixel += 4; // On passe au pixel suivant
               }
               return (int*)pixels;
}
// Ecrit dans la fenêtre une image BVR couvrant largeur*hauteur et démarrant en (x, y)
void dessinePiece(int x, int y, int largeur, int hauteur, const unsigned char *donnees)
{
               int *pixels = effaceFond(largeur, hauteur, donnees);
               ecrisImageARVB(x, y, largeur, hauteur, pixels);
               free(pixels);
}

void toucheUp(unsigned char touche, int x, int y)
{
	switch (touche) 
	{
		case 'd' : 
		//si on relache la touche d : On commence l'animation de retour de la position droite à la vertical 
		startAnimation(&Spaceship,0,1,SENS_ANTIHORAIRE);
		//On bloque l'animation quand on est revenu au sprite n°0
		bloquageAnimation(&Spaceship,0);			
		break;
		case 'q' : 
		//Pareil que pour la touche d mais lorsqu'on vient de la gauche
		startAnimation(&Spaceship,1,1,SENS_ANTIHORAIRE);
		bloquageAnimation(&Spaceship,0);			
		break;

	}
}

void init_joueur(vaisseau_joueur*p)
{
	(*p).hp = 1;
	(*p).posX = 400.0; //ou p->posX
	(*p).posY = 25.0;
	(*p).vitesse = 15;
	(*p).score = 0;
	(*p).tx = 60;
	(*p).ty = 60;
}


//----------------------------------------MISSILES--------------------------------------

//missiles --> tableau de strucutre de missiles
int nombre_missile = 2;
vaisseau_tir missile[2];


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
				missile[i].posX = (*p).posX + (*p).tx/2 - 6;
				missile[i].posY = (*p).posY + (*p).ty/2 ;
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
		missile2[i].vitesse = 0.0025 * hauteurFenetre();
		missile2[i].state = false;
	}

}

void affiche_tir_ennemis(ennemis_tir missile2[])
{
	for (int i=0; i < nombre_missile2; i++)
		if(missile2[i].state == true)
		{
				couleurCourante(255,0, 0);
				rectangle(missile2[i].posX +2,missile2[i].posY,missile2[i].posX + 8,missile2[i].posY + 10);
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
const int nombre_ligne = 5;
const int nombre_ennemis_par_ligne = 8;
const int nombremax_ennemis = nombre_ennemis_par_ligne*nombre_ligne;
int vitesse_ennemi=20;
int comptTempo=0;
int nbrTempo=30;

ennemi ennemis[40];


void deplacements_ennemis(ennemi ennemis[])
{
	
	int indice=0;
	
	if(comptTempo==nbrTempo)
	{
		comptTempo = 0;
		
		for(int i =0; i< nombremax_ennemis;i++)
		{
			if (ennemis[i].state == true)
			{
				ennemis[i].posX += ennemis[i].vitesse;
			
				if (ennemis[i].posX+ennemis[i].vitesse >= largeurFenetre()-ennemis[i].tx )
				{
					
					for(int k=0;k<nombre_ennemis_par_ligne;k++)
					{
						indice=i-k;
						ennemis[indice].posX-=ennemis[indice].vitesse+ennemis[indice].tx;
					}
					for(int j=0; j< nombremax_ennemis;j++)
					{
				
					ennemis[j].posY -= ennemis[j].ty; 				
					ennemis[j].vitesse = -ennemis[j].vitesse;
					}
				}
				if (ennemis[i].posX+ennemis[i].vitesse <= 0 )
				{
					/*for(int k=0;k<nombre_ennemis_par_ligne;k++)
					{
						indice=i+k;
						//ennemis[indice].posX+=-ennemis[indice].vitesse;
						ennemis[indice].posX+=-2*ennemis[indice].vitesse;
					}
					*/
					ennemis[i].posX+=-ennemis[i].vitesse+ennemis[i].tx;
					for(int j=0; j< nombremax_ennemis;j++)
					{
				
					ennemis[j].posY -= ennemis[j].ty; 			
					ennemis[j].vitesse = -ennemis[j].vitesse;
				
					}
				}
			}
			if(ennemis[i].posY<=0)
			{
				termineBoucleEvenements();
			} 
		}
	}
	
}

void init_ennemis (ennemi ennemis[])
{
	
	for(int i = 0; i < nombremax_ennemis ; i++)
		{
			ennemis[i].state = false;
			ennemis[i].vitesse = -vitesse_ennemi;
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

int comptMort=0;
void apparition_ennemis(ennemi ennemis[])
{
	int index=0;
	
	for (int j=0;j<nombre_ligne;j++)
	
		
	
		for(int i = 0; i < nombre_ennemis_par_ligne ; i++)
		{	
			index=i+nombre_ennemis_par_ligne*j;
			
			if (ennemis[index].state == false)
			{
				
				ennemis[index].posX = (largeurFenetre()/nombre_ennemis_par_ligne) *i + 100;
				ennemis[index].posY = 900 - 100*j;
				ennemis[index].state = true;
				
					
				
				
			}
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
			  	comptMort++;
			  	(*p).score += 10;
			  	}
			} 
		}

}
int cptfin=0;
int fin=0;

void test_collision_vaisseau(ennemis_tir missile2[],vaisseau_joueur*p)
{

for(int j = 0; j < nombre_missile2 ; j++)
	if((*p).hp != -1)
		{
		if(missile2[j].state == true &&
		  ((*p).posX)<= missile2[j].posX && 
		  ((*p).posX + (*p).tx)>= missile2[j].posX &&
		  ((*p).posY)<= missile2[j].posY && 
		  ((*p).posY + (*p).ty)>= missile2[j].posY)			  
			  	{
			  	missile2[j].state = false;
			  	(*p).hp -= 1;
			  	(*p).score -= 100;
			  	printf("%d\n", (*p).hp);
			  	}
			} 
	else
	{
		fin=1;
		startAnimation(&Spaceship,DROITE,2,SENS_HORAIRE);
		bloquageAnimation(&Spaceship,7);
		
		if(cptfin>=30) 
		{
			char name[10]="Player";
			char str[20];
			sprintf(str,"%d",(*p).score);
			saveHighscore(str,strcat(name,str));
			termineBoucleEvenements();
		}
	}

}


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
vaisseau_joueur vaisseau = {0,0,0,0,0,0,0};

int init=0;

void gestionEvenement(EvenementGfx evenement)
{
	static bool pleinEcran = true; 
	
			
	modePleinEcran();
	srand(time(NULL));
	//if(lancejeu==1)
	//	      {	
			static DonneesImageRGB* image=NULL;
			//static int comptTempo=0;
			
			monter_tir(missile);
			descendre_tir(missile2);
			test_collision(missile,ennemis, &vaisseau);
			test_collision_vaisseau(missile2,&vaisseau);
			
			
			//printf("%d , %d\n",largeurFenetre(), hauteurFenetre() );

			
			if (rand()%11 <5)
				{
					
					tir_ennemis(missile2,ennemis,rand()%11);
					//demandeTemporisation(17);
				}
			
			
		//	}
			rafraichisFenetre();
		
	switch (evenement)
	{
		
		case Initialisation:
			
				
				printf("ca initialise tekas\n");
				image=lisBMPRGB("heart.bmp");
				printf("lecture image coeur\n");
				init_joueur(&vaisseau);
				init_ennemis (ennemis);
				apparition_ennemis(ennemis);
				init_tir(missile);
				init_tir_ennemis(missile2);
				printf("ca initialise tekas\n");
							//on utilise la fonction glut pour observer lorsqu'on arrete d'appuyer sur une touche		
				{
				glutKeyboardUpFunc(&toucheUp);
				
				animationSprite listAnim[6];
				
				animationSprite* listAnimIDLE;
				animationSprite* listAnimMouve;
				animationSprite* listAnimExplosion;
				//Tous les sprites ont un pattern dans leur nom
				//Par exemple si on veut la rotation n°2 du vaisseau et vers la droite on aura le nom : "SpaceShip_Sprite0_2.bmp" 
				//Les animations de vers la droite ont l'indice 0 et vers la gauche l'indice 1 
				//To do : DEFINE droite et gauche 
				
				//On initialise l'animations d'IDLE 
				listAnimIDLE=initAnimationSprite("SpaceShip_Sprite%d_%d.bmp",1,6,0,0xFF);
				//On initialise l'animation Du mouvement donc: 6 images , un délai de 2*20ms , on commence à l'indice 0 
				listAnimMouve=initAnimationSprite("SpaceShip_Sprite%d_%d.bmp",6,2,0,0xFF);
				
				listAnimExplosion=initAnimationSprite("SpaceShip_Explosion%d_%d.bmp",8,3,0,0xAA);
				//dans la premiere case de notre liste d'animation on va mettre la premiere case de la liste d'animations des IDLE qui correspond à celle de l'IDLE droite
				listAnim[0]=*listAnimIDLE;
				// dans la deuxieme case de notre liste d'animation on va mettre la premiere case de la liste d'animations du mouvement qui correspond à celle de mouvement droit
				listAnim[1]=*listAnimMouve;
				// dans la troisieme case de notre liste d'animation on va mettre la deuxieme case de la liste d'animations des IDLE qui correspond à celle de l'IDLE gauche
				listAnim[2]=*listAnimExplosion;
				// dans la quatrieme case de notre liste d'animation on va mettre la deuxieme case de la liste d'animations du mouvement qui correspond à celle de mouvement gauche
				listAnim[3]=*(listAnimIDLE+1);
				
				listAnim[4]=*(listAnimMouve+1);
				
				listAnim[5]=*(listAnimExplosion+1);
				// On met à jour l'ensemble d'animation du vaisseau avec notre liste d'animations et le nombre d'animation différente donc ici 2 :IDLE et mouvement
				Spaceship=initAnimations(listAnim,3);
				
				
				//Animation Background:
				animationSprite* listAnimBackground;
				
				listAnimBackground=initAnimationSprite("background%d_%d.bmp",8,4,0,0x00);
				
				Background=initAnimations(listAnimBackground,1);
				startAnimation(&Background,DROITE,0,SENS_HORAIRE);
				
				animationSprite* listAnimInvader;
				listAnimInvader=initAnimationSprite("invader%d_%d.bmp",2,nbrTempo,0,0xAA);
				Invader=initAnimations(listAnimInvader,1);
				startAnimation(&Invader,DROITE,0,SENS_HORAIRE);
				
				animationSprite* listAnimInvader2;
				listAnimInvader2=initAnimationSprite("invaders%d_%d.bmp",2,50,0,0xAA);
				Invader2=initAnimations(listAnimInvader2,1);
				startAnimation(&Invader2,DROITE,0,SENS_HORAIRE);
				
				init=1;
				
				demandeTemporisation(20);
				
			
		 		modePleinEcran();
				
				demandeTemporisation(20);
		 		
		 	
		 	break;
		 	
		case Temporisation:
			//A chaque temporisation on va mettre à jour l'image du vaisseau en passant à la frame suivante s'il le faut
			switch (lancejeu)
			{
				case 1 :
					
					nextFrame(&Spaceship);
					nextFrame(&Background);
					nextFrame(&Invader);
					nextFrame(&Invader2);
					comptTempo++;
					
					// il faut redessiner la fenetre :
					deplacements_ennemis(ennemis);
					if (fin==1) cptfin++;
					
					if (comptMort==nombremax_ennemis) 
					{
						comptMort=0;
						nbrTempo-=10;
						comptTempo=0;
						if (nbrTempo<=0)
						{
							nbrTempo=5;
							
							//vitesse_ennemi+=10;
						}
						apparition_ennemis(ennemis) ;
					}
					rafraichisFenetre();
					
				break;	
				case 0 :
					//A chaque temporisation on va mettre à jour l'image du vaisseau en passant à la frame suivante s'il le faut
					nextFrame(&Background);
				
					// il faut redessiner la fenetre :
					rafraichisFenetre();
					break;
			}
			break;
			
		case Affichage:
		//apparition_ennemis(ennemis);
		//demandeTemporisation(50);
			switch (lancejeu)
			{
				case 1:
					if (init==1)
					{
						effaceFenetre (255, 255, 255);
						couleurCourante(0, 255, 255);
						epaisseurDeTrait(10);
						
						afficheImageSansBackGround(getImage(Background),getPixels(Background),0x00,0,0);
						affiche_tir_ennemis(missile2);
						affiche_tir(missile);
						couleurCourante(255,255,255);
						affiche_hp(&vaisseau);
						affiche_score(&vaisseau);
						dessinePiece(70,37,90,50,image->donneesRGB);
					
						
					//accolade pour définir un bloc de commande à executer (il y avait des erreurs sinon)
						for (int ii=0;ii<nombremax_ennemis;ii++)
						{
							if (ennemis[ii].state==true)
							{
								afficheImageSansBackGround(getImage(Invader),getPixels(Invader),0xAA,ennemis[ii].posX-ennemis[ii].tx,ennemis[ii].posY-ennemis[ii].ty);
							}
						}
						afficheImageSansBackGround(getImage(Spaceship),getPixels(Spaceship),0xFF,vaisseau.posX,vaisseau.posY);	 	
				 	}
					break;
				case 0:
					generationmenu();
					break;
			}
		break;
			
		case Clavier:
			//printf("%c : ASCII %d\n", caractereClavier(), caractereClavier());
			//apparition_ennemis(ennemis);
			
			//TROUVER OU L'ENDROIT OU LE PLACER POUR QU'IL AILLE AU MILLIEU SANS PRESSER UNE TOUCHE SA MERE
			//apparition_ennemis(ennemis);
			switch (lancejeu)
			{
				case 1 :
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
						if (vaisseau.posX + vaisseau.vitesse > largeurFenetre() - 1){
							break;}
							
							droite(&vaisseau);
							startAnimation(&Spaceship,DROITE,1,SENS_HORAIRE);
							
							bloquageAnimation(&Spaceship,5);	
							rafraichisFenetre();
							break;
							
											
						case 'Q':
						case 'q':
						if (vaisseau.posX - vaisseau.vitesse < 0){
							break;}
							
							gauche(&vaisseau);
							startAnimation(&Spaceship,GAUCHE,1,SENS_HORAIRE);
							bloquageAnimation(&Spaceship,5);
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
				case 0:
					switch (caractereClavier())
					{
					case 'Q': // Pour sortir quelque peu proprement du programme
					case 'q':
					
						//Mix_CloseAudio();
						termineBoucleEvenements();
						break;

					//DECOMMENTER LE CASE F POUR EFFECTUER LES TESTS 
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
			}
		break;	
		
		case ClavierSpecial:
			
			break;
		case BoutonSouris:
			switch(lancejeu)
			{
				case 1:
					break;
				case 0:
					if (etatBoutonSouris() == GaucheAppuye)
				{
					printf("Bouton gauche appuye en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
					// Si le bouton gauche de la souris est appuye, on regarde ou le joueur clique pour définir les actions suivantes
					//c'est ici que i nous sert pour savoir dans quel menu nous sommes
					if (defrubrique==0)
						choixmenu();
					if (defrubrique==1)
						choixleaderboard();
					if (defrubrique==2)
					{
						choixsauvegarde();
					}
				
				}
				else if (etatBoutonSouris() == GaucheRelache)
				{
					printf("Bouton gauche relache en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
				}
				break;
			}
		break;
		case Redimensionnement:
			switch(lancejeu)
			{
			case 1:
				break;
			break;
			case 0:
				printf("Largeur : %d\t", largeurFenetre());
				printf("Hauteur : %d\n", hauteurFenetre());
				break;
			}
			break;
		case Souris: // Si la souris est deplacee
			break;
		case Inactivite: // Quand aucun message n'est disponible

			break;
		
	}
	//affiche_ennemis(ennemis);

	}
}
