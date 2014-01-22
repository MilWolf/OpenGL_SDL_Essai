#include <string>
#include "SDL_ttf.h"

using namespace std;

class SDLTexte
{
public:
	SDLTexte(SDL_Surface*);
	SDLTexte(string texte,SDL_Surface*);
	SDLTexte(string texte,SDL_Color couleur);
	SDLTexte(string texte,SDL_Color couleur,int taillePolice);
	SDLTexte(string texte,SDL_Color couleur,int taillePolice,string font);
	SDLTexte(string texte,SDL_Color couleur,int taillePolice,string font,int positionX,int positionY);
	~SDLTexte();

	void afficher();
	void recharger();
	void effacer();

	void setPositionX(int positionX);
	void setPositionY(int positionY);
	void setCouleur(int r,int g,int b);
	void setTexte(string texte);

	int getPositionX();
	int getPositionY();
	int getLargeur();
	int getHauteur();
	string getTexte();

private:
	int positionX;
	int positionY;
	int largeur;
	int hauteur;
	string texte;
	TTF_Font *police;
	string sPolice;
	int taillePolice;
	SDL_Surface *text_surface;
	SDL_Color couleur;
	SDL_Surface* screenSurface;
	
	void initialiser();
};

