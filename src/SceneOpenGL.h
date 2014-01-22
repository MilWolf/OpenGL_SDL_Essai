#ifndef SCENE_OPENGL_H
#define SCENE_OPENGL_H
 

#include <SDL.h>
#include <glew.h>
#include <stdio.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"
#include "MapLoader.h"
#include "HUD.h"

class SceneOpenGL
{
	public:
		SceneOpenGL();
		~SceneOpenGL();

		bool initialiserFenetre();
		bool initialiserGL();
		void bouclePrincipale();
		void chargerObjets();
		void lireParametres();

		void setPleinEcran(bool pleinEcran);
		void setSyncV(bool syncV);

		bool getPleinEcran();
		bool getSyncV();

		int fps;

	private:
		SDL_Window* fenetre;
		SDL_GLContext contexteOpenGL;
		SDL_Event evenements;
		bool terminer;
		int largeurFenetre;
		int hauteurFenetre;
		Input input;
		bool pleinEcran;
		bool syncV;

		Mesh *arme;
		MapLoader *map;
		HUD *hud;
};

#endif