#include "SceneOpenGL.h"

using namespace glm;

SceneOpenGL::SceneOpenGL():input()
{
	fenetre=0;
    contexteOpenGL=0;
	fps=0;
	terminer=false;
	//largeurFenetre=1680;
	//hauteurFenetre=1050;
	this->lireParametres();
}

bool SceneOpenGL::initialiserFenetre()
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
        SDL_Quit();
         
        return false;
    }

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
     
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
 
	if(pleinEcran)
	{
		fenetre = SDL_CreateWindow("Test SDL 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, largeurFenetre, hauteurFenetre, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL|SDL_WINDOW_FULLSCREEN);
	}
	else
	{
		fenetre = SDL_CreateWindow("Test SDL 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, largeurFenetre, hauteurFenetre, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	}

    if(fenetre == 0)
    {
        std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
        SDL_Quit();
 
        return false;
    }
 
    contexteOpenGL = SDL_GL_CreateContext(fenetre);
 
    if(contexteOpenGL == 0)
    {
        std::cout << SDL_GetError() << std::endl;
        SDL_DestroyWindow(fenetre);
        SDL_Quit();
 
        return false;
    }

	return true;
}

bool SceneOpenGL::initialiserGL()
{
	GLenum initialisationGLEW( glewInit() );
	//glDisable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	
	//glEnable
	//glEnable(GL_LIGHT0);
	//GLint glMaxTexDim;
	//glGetIntegerv(GL_MAX_TEXTURE_SIZE, &glMaxTexDim);

    if(initialisationGLEW != GLEW_OK)
    {
 
        std::cout << "Erreur d'initialisation de GLEW : " << glewGetErrorString(initialisationGLEW) << std::endl;
 
 
        SDL_GL_DeleteContext(contexteOpenGL);
        SDL_DestroyWindow(fenetre);
        SDL_Quit();
 
        return false;
    }

	return true;
}

void SceneOpenGL::chargerObjets()
{
	hud=new HUD(largeurFenetre,hauteurFenetre);
	map=new MapLoader("test12.scene");

	ObjLoader objArme("modeles/baril.obj");
	arme=new Mesh(objArme.getTableauVertices(),objArme.getNombreVertices(),objArme.getTableauCouleurs(),objArme.getNombreCouleurs(),objArme.getTableauCoordTexture(),objArme.getNombreCoordonnees(),objArme.getNombreTriangles(),false,objArme.getTexMat(),"Shaders/texture.vert", "Shaders/texture.frag");
	arme->charger();
	arme->setPositionX(10.0f);
	arme->setPositionY(10.0f);
	arme->setPositionZ(10.0f);

	map->initialiser();
	hud->initialiser();

	map->charger();	
	hud->charger();
}

void SceneOpenGL::bouclePrincipale()
{
	unsigned int frameRate (1000 / 50);
    Uint32 debutBoucle(0), finBoucle(0), tempsEcoule(0);


	mat4 projectionPerspective;
	mat4 projectionOrthographique;
	mat4 modelview;

	vec3 oeilCamera(1,1,10);
	vec3 pointLookCamera(0,0,0);
	
	
	modelview=mat4(1.0);

	Camera camera(vec3(3, 3, 3), vec3(-2, 3, 20), vec3(0, 1, 0));
    input.afficherPointeur(false);
    input.capturerPointeur(true);

	int lastUpdate=0,nbFrames=0;

	projectionPerspective=perspective(70.0, (double) largeurFenetre / hauteurFenetre, 1.0, 10000.0);
	projectionOrthographique=ortho(0.0f,(float) largeurFenetre,0.0f,(float) hauteurFenetre,-100.0f,100.0f);

	while(!input.finish())
    {
		
		debutBoucle = SDL_GetTicks();

		 // Compteur de FPS
		nbFrames++; 
		
		if ( SDL_GetTicks()-lastUpdate > 1000 ) 
		{ 
			fps=nbFrames;
			nbFrames = 0; 
			lastUpdate+=1000; 
		} 

		/********************Evenements***********************/

		input.updateEvenements();

		if(input.getTouche(SDL_SCANCODE_RETURN))
		{
			oeilCamera.z=10;
			oeilCamera.y=1;
		}

		if(input.getTouche(SDL_SCANCODE_1))
		{
			glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
		}
		if(input.getTouche(SDL_SCANCODE_2))
		{
			glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
		}
		if(input.getTouche(SDL_SCANCODE_ESCAPE))
		{
			break;
		}
		
        
		camera.deplacer(input,fps);

		/********************Nettoyage***********************/
        glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

		camera.lookAt(modelview);
		
		/*
		if(input.getBoutonSouris(SDL_BUTTON_LEFT))
		{
			
		}
		*/

		/********************Affichage de la scène***********************/
		map->afficher(projectionPerspective,modelview);

		/*
		modelview=translate(modelview,camera.getPosition().x+5,camera.getPosition().y-2,camera.getPosition().z);
		modelview=rotate(modelview,camera.getPhi(),vec3(1,0,0));
		modelview=rotate(modelview,camera.getTheta(),vec3(0,1,0));
		*/
		//arme->afficher(projectionPerspective,modelview);
		
		hud->afficher(projectionOrthographique,modelview);
		

		/****************On change de fenetre******************/
        SDL_GL_SwapWindow(fenetre);
		
		
        // Calcul du temps écoulé
        finBoucle = SDL_GetTicks();
        tempsEcoule = finBoucle - debutBoucle;
 
 
        // Si nécessaire, on met en pause le programme
        // if(tempsEcoule < frameRate)
        //   SDL_Delay(frameRate - tempsEcoule);


    }
 
}

void SceneOpenGL::lireParametres()
{
	ifstream fichier("config.cfg", ios::in);
	string contenu;

	
    if(fichier) 
    {
        while(getline(fichier, contenu))
		{
			if(contenu.find("plein ecran: ")==0)
			{
				int i=atoi(contenu.substr(13).c_str());

				if(i==0)
				{
					pleinEcran=false;
				}
				else
				{
					pleinEcran=true;
				}
			}
			else if(contenu.find("synchronisation verticale: ")==0)
			{
				int i=atoi(contenu.substr(27).c_str());

				if(i==0)
				{
					syncV=false;
				}
				else
				{
					syncV=true;
				}
			}
			else if(contenu.find("resolution: ")==0)
			{
				int pos=contenu.find('x');
				largeurFenetre=atoi(contenu.substr(12,pos-2).c_str());
				hauteurFenetre=atoi(contenu.substr(pos+2).c_str());
			}
			
		} 

		fichier.close();
    }
    else
            cerr << "Impossible d'ouvrir le fichier !" << endl;
}

void SceneOpenGL::setPleinEcran(bool pleinEcran)
{
	this->pleinEcran=pleinEcran;
}
void SceneOpenGL::setSyncV(bool syncV)
{
	this->syncV=syncV;
}

bool SceneOpenGL::getPleinEcran()
{
	return pleinEcran;
}
bool SceneOpenGL::getSyncV()
{
	return syncV;
}

SceneOpenGL::~SceneOpenGL()
{
	SDL_GL_DeleteContext(contexteOpenGL);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
}