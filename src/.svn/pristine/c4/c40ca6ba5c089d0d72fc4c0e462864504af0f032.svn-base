#include "SDLImage.h"

SDLImage::SDLImage(SDL_Surface* screenSurface,string nom):positionX(0),positionY(0)
{
	this->nom=nom;
	this->charger();
	categorie=dessin;
	this->screenSurface=screenSurface;
}

void SDLImage::charger()
{
	gImage = IMG_Load(nom.c_str());
	this->largeur=gImage->w;
	this->hauteur=gImage->h;
}

void SDLImage::afficher()
{
	SDL_Rect rectDest;
	rectDest.x=positionX;
	rectDest.y=positionY;
	SDL_BlitSurface( gImage, NULL, screenSurface, &rectDest);
	//perhaps we can reuse it, but I assume not for simplicity.
	//SDL_FreeSurface(gImage);
}

void SDLImage::effacer()
{
	SDL_Rect *rect=new SDL_Rect();
	rect->x=positionX;
	rect->y=positionY;
	rect->w=largeur;
	rect->h=hauteur;
	SDL_FillRect(screenSurface,static_cast<const SDL_Rect*>(rect),NULL);
}

void SDLImage::setImage(string nom)
{
	this->nom=nom;
	this->charger();
}
void SDLImage::setCategorie(int categorie)
{
	this->categorie=categorie;
}
int SDLImage::getCategorie()
{
	return this->categorie;
}
int SDLImage::getPositionX()
{
	return this->positionX;
}

int SDLImage::getPositionY()
{
	return this->positionY;
}
int SDLImage::getLargeur()
{
	return this->largeur;
}
int SDLImage::getHauteur()
{
	return this->hauteur;
	
}

void SDLImage::setPositionX(int positionX)
{
	this->positionX=positionX;
}
void SDLImage::setPositionY(int positionY)
{
	this->positionY=positionY;
}

SDLImage::~SDLImage()
{
}