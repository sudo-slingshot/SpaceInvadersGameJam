#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include "GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "ESLib.h" // Pour utiliser valeurAleatoire()

#include "fctsprite.h" //Pour utiliser les fonctions des sprites


//Fonction pour enlever le background d'une image

//int couleurBackgroundSpaceship=0x0F7;

//On reprend la fonction BVR2ARVB utilisée dans Gfxlib.c pour transformer les images de BVR à ARVB en rajoutant une condition pour effacer le background

int *BVR2ARVB_sansBackground(int largeur, int hauteur, const unsigned char *donnees,int hexacouleurBackground) {
	const unsigned char *ptrDonnees;
	unsigned char *pixels = (unsigned char*)malloc(largeur*hauteur*sizeof(int));
	unsigned char *ptrPixel;
	int index;
	ptrPixel = pixels;
	ptrDonnees = donnees;
	for
		(index = largeur*hauteur; index != 0; --index) /* On parcourt tous les pixels de l'image */
	{
		ptrPixel[0] = ptrDonnees[0];
		ptrPixel[1] = ptrDonnees[1];
		ptrPixel[2] = ptrDonnees[2];
		
		//Si les trois composantes du pixels sont égales à la couleur du Background que l'on veut effacer; Alors on définit la 4e composante du Pixel à 0x000 ce qui correspond à un pixel sans 				opacité donc transparant 
		if (ptrPixel[0]==ptrPixel[1] && ptrPixel[0]==ptrPixel[2] &&ptrPixel[0]==hexacouleurBackground) ptrPixel[3] = 0x00;
		
		// Sinon on laisse l'opacité initialement prévu 
		else ptrPixel[3] = 0xFF;
		
		ptrDonnees += 3; /* On passe a la premiere composante du pixel suivant */
		ptrPixel += 4; /* On passe au pixel suivant */
	}
	return (int*)pixels;
}

//Fonction pour afficher une image sans son background 
//Elle prend en parametre une chaine de caractere = au nom de l'image et un entier écris en hexa correspondant à la couleur du Baackground la positionn en x et la position en y où l'on souhaite l'afficher

void afficheImageSansBackGround(DonneesImageRGB *image,int* imageSansBackGround,int hexacouleurBackground,int posx,int posy)
{ 		
	//int* imageSansBackGround=BVR2ARVB_sansBackground(image->largeurImage,image->hauteurImage,image->donneesRGB,hexacouleurBackground);
	//Puis on écrit l'image grace à la fonction ecrisImageARVB
	ecrisImageARVB(posx,posy, image->largeurImage, image->hauteurImage, imageSansBackGround);
}	
	

//fonction d'initialisation des sprites d'une animation 
//Elle prend en parametre une chaine de caractere correspondant à un sprite pattern par exemple:"SpaceShip_Sprite%d_%d.bmp"
//Toutes les sprites seront renommé suivant ce pattern on entrera un premier entier (0 ou 1) correspondant à la direction (vers la Gauche ou la Droite) le deuxieme parametre correspond au numéro 
// de l'image 
//les noms des autres parametres parlent d'eux même
animationSprite* initAnimationSprite(char* spritesPathPattern,int nbrImages,int delay,int indexStartingImage,int hexacouleurBackground)
{
	int i=0;
	int dir=0;
	
	//On crée un tableau de pointeur vers la structure animation sprite 
	//On crée une case par direction 
	
	animationSprite* assets=(animationSprite*)malloc(NBR_DIRECTION*sizeof(animationSprite));
	for (dir=0;dir<NBR_DIRECTION;dir++)
	{
		//Dans chacune des cases de directions ont crées un tableau avec les sprites correspondant à ces directions 
		// Par exemple: dans la case de droite il y aura un tableau avec dans chacune de ces cases les donnees de chaque image qui compose l'animation de tourner vers la droite
		assets[dir].tabSprite=(DonneesImageRGB*)malloc(nbrImages*sizeof(DonneesImageRGB));
		
		assets[dir].tabPixels=(int**)malloc(nbrImages*sizeof(int*));
		
		//On crée un buffer pour y rentrer les noms des images qui suivent toute un patterne 
		char str[100];
		
		for(i=0;i<nbrImages;i++){
			
			
			//Chaque image est nommé avec deux indices : le premier correspond à la direction (Droite ou Gauche) et le deuxieme au numéro de l'image
			//Par exemple l'image 2 vers la droite du vaisseau est nommé "SpaceShip0_2.bmp"
			//grace à la fonction sprintf on va pouvoir "lire" les noms des images en fonction de leurs indices 
			// Pour comprendre plus son fonctionnement faites un man sprintf 
			//Mais pour résumer on va rentrer dans le buffer str déclaré au dessus la valeur de spritesPathPattern avec les bons indices 
			//concrétement pour le vaisseau spritesPathPattern = "SpaceShip_Sprite%d_%d.bmp"
			//la fonction sprintf va mettre dans le buffer le spritesPathPattern avec à la place des %d les idices dir et i 
			sprintf(str,spritesPathPattern,dir,i);
			
			//Puis on va rentrer dans notre dtableau d'assets les données de l'image lu par la fonction lisBMPRGB 
			assets[dir].tabSprite[i]=*lisBMPRGB(str);	
			
			assets[dir].tabPixels[i]=BVR2ARVB_sansBackground(
								assets[dir].tabSprite[i].largeurImage,
								assets[dir].tabSprite[i].hauteurImage,
								assets[dir].tabSprite[i].donneesRGB,
								hexacouleurBackground);
			
		}
		
		//On initialise les autres données de la structure 
		assets[dir].delay=delay;
		assets[dir].currentImage=indexStartingImage;
		assets[dir].nbrImages=nbrImages;
		assets[dir].compteurDelay=0;
	}
	return(assets);
}

//fonction d'initialisation des animations 
//Elle prend en parametre une liste d'animation qui est un tableau de structure animationSprite et le nombre d'animations
//listAnimations aura déjà était initialisé grâce à la fonction précédente
ensembleAnimation initAnimations(animationSprite* listAnimation,int nbrAnimations)
{
	ensembleAnimation ensembleAsset;
	ensembleAsset.tabanimation=(animationSprite*)malloc(nbrAnimations*sizeof(animationSprite)*NBR_DIRECTION);
	for (int dir=0;dir<NBR_DIRECTION;dir++)
	{
		for(int i=0;i<nbrAnimations;i++)
		{
			ensembleAsset.tabanimation[dir*nbrAnimations+i]=listAnimation[dir*nbrAnimations+i];
			
		}	
	}
	ensembleAsset.currentAnimation=0;
	ensembleAsset.nbrAnimations=nbrAnimations;
	ensembleAsset.sens=SENS_HORAIRE;
	ensembleAsset.indexBloquage=-1;
	ensembleAsset.indiceDirection=0;
	
	return(ensembleAsset);

}

//fonction pour démarrer une animation
void startAnimation(ensembleAnimation* animation ,int indiceDirection,int IDAnimation,int sens)
{
	if (animation->currentAnimation!=IDAnimation || animation->indiceDirection!=indiceDirection) animation->tabanimation[animation->indiceDirection*animation->nbrAnimations+animation->currentAnimation].currentImage=0;
	animation->currentAnimation=IDAnimation;
	animation->sens=sens;
	animation->indiceDirection=indiceDirection;
	
}

//fonction pour set le bloquage d'une animation
void bloquageAnimation(ensembleAnimation* animation,int indexBloquage)
{
	animation->indexBloquage=indexBloquage;
	
}

//fonction pour passer à la frame suivante
void nextFrame(ensembleAnimation* animation)
{
	int index=animation->indiceDirection*animation->nbrAnimations+animation->currentAnimation;
	if(animation->tabanimation[index].currentImage==animation->indexBloquage) return ;
	
	animation->tabanimation[index].compteurDelay++;
	if(animation->tabanimation[index].compteurDelay<animation->tabanimation[index].delay) return;
	animation->tabanimation[index].compteurDelay=0;
	
	animation->tabanimation[index].currentImage+=animation->sens;
	if(animation->tabanimation[index].currentImage >= animation->tabanimation[index].nbrImages) 
		animation->tabanimation[index].currentImage=0 ;
	else if (animation->tabanimation[index].currentImage <0) 
		animation->tabanimation[index].currentImage=animation->tabanimation[index].nbrImages-1;
	
	
}

//fonction pour récupérer l'image courrante
DonneesImageRGB* getImage(ensembleAnimation animation){
	int index=animation.indiceDirection*animation.nbrAnimations+animation.currentAnimation;
	int currentImage=animation.tabanimation[index].currentImage;	
	return &(animation.tabanimation[index].tabSprite[currentImage]);
}
int* getPixels(ensembleAnimation animation){
	int index=animation.indiceDirection*animation.nbrAnimations+animation.currentAnimation;
	int currentImage=animation.tabanimation[index].currentImage;	
	return (animation.tabanimation[index].tabPixels[currentImage]);
}
