#include <string>
#include "SDL_ttf.h"
#include <SDL_image.h>

using namespace std;

class SDLImage
{
public:
	SDLImage(SDL_Surface*,string nom);
	~SDLImage();

	void afficher();

	void setPositionX(int positionX);
	void setPositionY(int positionY);
	void setImage(string nom);
	void setCategorie(int categorie);
	int getCategorie();
	void effacer();

	int getPositionX();
	int getPositionY();
	int getLargeur();
	int getHauteur();

	enum type { dessin, checkbox, fleche_gauche,fleche_droite };

private:
	string nom;
	SDL_Surface* gImage;
	SDL_Surface* screenSurface;
	int positionX;
	int positionY;
	int largeur;
	int hauteur;
	int categorie;
	

	

	void charger();
};

