#ifndef DEF_FCTSPRITE
#define DEF_FCTSPRITE

#include "BmpLib.h"

#define SENS_HORAIRE 1 
#define SENS_ANTIHORAIRE -1

#define PAS_DE_BLOQUAGE -1

#define NBR_DIRECTION 2
#define DROITE 0
#define GAUCHE 1

//Pour simplifier l'utilisaition des fonctions on a define les sens et les directions
//On aura juste à écrire DROITE sans se soucier de la valeur de l'indice correspondant à droite quand on voudra effectuer l'animation de rotation vesr la droite



//Fonction pour enlever le background d'une image
int *BVR2ARVB_sansBackground(int largeur, int hauteur, const unsigned char *donnees,int hexacouleurBackground);

//Fonction pour afficher une image sans son background 
void afficheImageSansBackGround(DonneesImageRGB *image,int* imageSansBackGround,int hexacouleurBackground,int posx,int posy);

//structures pour l'animation des sprites :

//structure pour renseigner les sprites d'une animation dans un tableau ainsi que le délai de rafraichissement , l'image courante et le nb d'images  
//Par exemple : On rentre dans le tableau tous les sprite du vaisseau avec un délai de changement d'image de 20 ms la current image du vaisseau à la vertical(disons l'image 5) et 10 images
typedef struct  
{
	DonneesImageRGB* tabSprite;
	int** tabPixels;
	int delay;
	int currentImage;
	int nbrImages;
	int compteurDelay;
 
}animationSprite;
//structure pour stocker les animations possibles pour les sprites et l'etat des animations 
//Par exemple: pour le vaisseau on pourra avoir les animations "déplacement à droite","déplacement à gauche"  stockées dans un tableau
//si on est entrain de tourner à droite on aura current animation = 2 qui correspondra à l'animation tourner à droite 
typedef struct 
{
	animationSprite* tabanimation;
	int currentAnimation;
	int nbrAnimations;
	int sens;
	int indexBloquage;
	int indiceDirection;
}ensembleAnimation;


//fonction d'initialisation des sprites d'une animation 
//Elle prend en parametre une chaine de caractere correspondant à un sprite pattern par exemple:"SpaceShip_Sprite%d_%d.bmp"
//Toutes les sprites seront renommé suivant ce pattern on entrera un premier entier (0 ou 1) correspondant à la direction (vers la Gauche ou la Droite)
//les noms des autres parametres parlent d'eux même
animationSprite* initAnimationSprite(char* spritesPathPattern,int nbrImages,int delay,int indexStartingImage,int hexacouleurBackground);

// sprintf(str,"spaceShip%d_%d.bmp",0,0) => "spaceship0_0.bmp"
//0 pour gauche et 1 pour droite 

//fonction d'initialisation des animations 

ensembleAnimation initAnimations(animationSprite* listAnimation,int nbrAnimations);


//fonction pour démarrer une animation
void startAnimation(ensembleAnimation* animation ,int indiceDirection,int IDAnimation,int sens);

//fonction pour set le bloquage d'une animation
void bloquageAnimation(ensembleAnimation* animation,int indexBloquage);

//fonction next frame
void nextFrame(ensembleAnimation* animation);

//fonction pour récupérer l'image courrante
DonneesImageRGB* getImage(ensembleAnimation animation);
//Fonction pour récupérer les pixels de l'image courrante 
int* getPixels(ensembleAnimation animation);
#endif
