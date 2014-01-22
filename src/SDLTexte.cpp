#include "SDLTexte.h"

SDLTexte::SDLTexte(SDL_Surface* screenSurface)
	:texte("Hello world!"),couleur(couleur),taillePolice(16),sPolice("Fonts/ARLRDBD.TTF"),positionX(0),positionY(0)
{
	couleur.r=255;
	couleur.g=255;
	couleur.b=255;

	this->initialiser();
}

SDLTexte::SDLTexte(string texte,SDL_Surface* screenSurface)
	:texte(texte),taillePolice(16),sPolice("Fonts/ARLRDBD.TTF"),positionX(0),positionY(0)
{
	couleur.r=255;
	couleur.g=255;
	couleur.b=255;

	this->screenSurface=screenSurface;

	this->initialiser();
}
SDLTexte::SDLTexte(string texte,SDL_Color couleur)
	:texte(texte),couleur(couleur),taillePolice(16),sPolice("Fonts/ARLRDBD.TTF"),positionX(0),positionY(0)
{
	this->initialiser();
}
SDLTexte::SDLTexte(string texte,SDL_Color couleur,int taillePolice)
	:texte(texte),couleur(couleur),taillePolice(taillePolice),sPolice("Fonts/ARLRDBD.TTF"),positionX(0),positionY(0)
{
	this->initialiser();
}
SDLTexte::SDLTexte(string texte,SDL_Color couleur,int taillePolice,string sPolice)
	:texte(texte),couleur(couleur),taillePolice(taillePolice),sPolice(sPolice),positionX(0),positionY(0)
{
	this->initialiser();
}
SDLTexte::SDLTexte(string texte,SDL_Color couleur,int taillePolice,string sPolice,int positionX,int positionY)
	:texte(texte),couleur(couleur),taillePolice(taillePolice),sPolice(sPolice),positionX(positionX),positionY(positionY)
{
	this->initialiser();
}

void SDLTexte::initialiser()
{
	if(TTF_Init()==-1)
	{
		printf("TTF_Init: %s\n", TTF_GetError());
		exit(2);
	}

	police=TTF_OpenFont(sPolice.c_str(), 30);
	if(!police)
	{
		printf("TTF_OpenFont: %s\n", TTF_GetError());
		// handle error
	}

	if(!(text_surface=TTF_RenderText_Solid(police,texte.c_str(),couleur)))
	{
		printf("La conversion du texte en image a echouee.");
	}
}

void SDLTexte::recharger()
{
	if(!(text_surface=TTF_RenderText_Solid(police,texte.c_str(),couleur)))
	{
		printf("La conversion du texte en image a echouee.");
	}
}

void SDLTexte::afficher()
{
	SDL_Rect rectDest;
	rectDest.x=positionX;
	rectDest.y=positionY;
	largeur=text_surface->w;
	hauteur=text_surface->h;
	
	SDL_BlitSurface(text_surface,NULL,screenSurface,&rectDest);
	//perhaps we can reuse it, but I assume not for simplicity.
	SDL_FreeSurface(text_surface);
}

void SDLTexte::effacer()
{
	SDL_Rect *rect=new SDL_Rect();
	rect->x=positionX;
	rect->y=positionY;
	rect->w=largeur;
	rect->h=hauteur;
	SDL_FillRect(screenSurface,static_cast<const SDL_Rect*>(rect),NULL);
}

void SDLTexte::setPositionX(int positionX)
{
	this->positionX=positionX;
}
void SDLTexte::setPositionY(int positionY)
{
	this->positionY=positionY;
}
void SDLTexte::setCouleur(int r,int g,int b)
{
	this->couleur.r=r;
	this->couleur.g=g;
	this->couleur.b=b;
}
void SDLTexte::setTexte(string texte)
{
	this->texte=texte;
}

int SDLTexte::getPositionX()
{
	return this->positionX;
}

int SDLTexte::getPositionY()
{
	return this->positionY;
}

int SDLTexte::getLargeur()
{
	return this->largeur;
}
int SDLTexte::getHauteur()
{
	return this->hauteur;
}
string SDLTexte::getTexte()
{
	return this->texte;
}

SDLTexte::~SDLTexte()
{
	TTF_Quit();
}