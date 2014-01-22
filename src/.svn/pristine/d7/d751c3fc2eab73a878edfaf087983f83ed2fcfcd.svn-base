#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>

class Input
{
	public:
		Input();
		~Input();

		void updateEvenements();
		bool finish();
		bool getTouche(const SDL_Scancode touche) const;
		bool getBoutonSouris(const Uint8 bouton) const;
		bool mouvementSouris() const;

		void afficherPointeur(bool reponse) const;
		void capturerPointeur(bool reponse) const;

		int getX() const;
		int getY() const;
 
		int getXRel() const;
		int getYRel() const;

		void setTerminer(bool terminer);

	private:
		SDL_Event evenements;
		bool touches[SDL_NUM_SCANCODES];
		bool boutonsSouris[8];
 
		int x;
		int y;
		int xRel;
		int yRel;
 
		bool terminer;
};

#endif