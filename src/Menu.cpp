#include "Menu.h"

#include <iostream>

using namespace std;

#define SDL_HINT_RENDER_VSYNC 0

Menu::Menu():input()
{
	syncVCheck=true;
	pleinEcranCheck=true;
	estQuitte=false;
	flecheGaucheResOn=false,flecheDroiteResOn=false,flecheGaucheQualiteOn=false,flecheDroiteQualiteOn=false;
	gScreenSurface = NULL;
	input.capturerPointeur(true);
	listeResolution=new vector<string>();
	listeQualite=new vector<string>();

	listeQualite->push_back("Maximum");
	listeQualite->push_back("Moyenne");
	listeQualite->push_back("Minimum");

	indexResolution=0;
	indexQualite=0;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_Quit();
    }


	mode=new SDL_DisplayMode();

	int nombreModesAffichage=SDL_GetNumDisplayModes(0);
	int widthTemp=0;
	int heightTemp=0;
	for(int i=0;i<nombreModesAffichage;i++)
	{
		SDL_GetDisplayMode(0,i,mode);
		if(widthTemp!=mode->w && heightTemp!=mode->h)
		{
			widthTemp=mode->w;
			heightTemp=mode->h;

			ostringstream oss;
			oss<<mode->w;
			oss<<" x ";
			oss<<mode->h;
		
			listeResolution->push_back(oss.str());
		}
		
	}
	


	SDL_GetDisplayMode(0,0,mode);
	largeurEcran=mode->w;
	hauteurEcran=mode->h;

	ecrireParametres();

	
	input.afficherPointeur(false);
	
	SDL_CreateWindowAndRenderer(largeurEcran,hauteurEcran,SDL_WINDOWPOS_UNDEFINED|SDL_WINDOWPOS_UNDEFINED|SDL_WINDOW_SHOWN, &screen, &sdlRenderer);
	if( screen)
    {
		gScreenSurface = SDL_GetWindowSurface( screen );
		
		this->chargerMenuPrincipal();
		
		/*
		unsigned char *pixels=static_cast<unsigned char*>(gImage->pixels);

		for(int i=0;i<gImage->w*gImage->h*3;i++)
		{
			cout<<(int)pixels[i]<<" ";
		}
		*/
		//SDL_BlitSurface( gImage, NULL, gScreenSurface, NULL );
		
	}
	else
    {
        fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
    }
}

void Menu::chargerMenuPrincipal()
{
	SDL_FillRect(gScreenSurface,NULL,NULL);
	input.setTerminer(false);
	menu=0;
	listeSDLTexteMenu0=new vector<SDLTexte*>();

	SDLImage *curseur=new SDLImage(gScreenSurface,"Bitmaps/cible5.png");
	curseur->setPositionX(input.getX());
	curseur->setPositionY(input.getY());
	curseur->afficher();
	

	SDLTexte *texteCommencer=new SDLTexte("Commencer une nouvelle partie",gScreenSurface);
	texteCommencer->setPositionX(30);
	texteCommencer->setPositionY(hauteurEcran*0.3);
	texteCommencer->afficher();
	listeSDLTexteMenu0->push_back(texteCommencer);
		
	SDLTexte *texteReprendre=new SDLTexte("Reprendre une partie",gScreenSurface);
	texteReprendre->setPositionX(30);
	texteReprendre->setPositionY(hauteurEcran*0.4);
	texteReprendre->afficher();
	listeSDLTexteMenu0->push_back(texteReprendre);

	SDLTexte *texteOptions=new SDLTexte("Options",gScreenSurface);
	texteOptions->setPositionX(30);
	texteOptions->setPositionY(hauteurEcran*0.5);
	texteOptions->afficher();
	listeSDLTexteMenu0->push_back(texteOptions);

	SDLTexte *texteCredits=new SDLTexte("Crédits",gScreenSurface);
	texteCredits->setPositionX(30);
	texteCredits->setPositionY(hauteurEcran*0.6);
	texteCredits->afficher();
	listeSDLTexteMenu0->push_back(texteCredits);

	SDLTexte *texteQuitter=new SDLTexte("Quitter",gScreenSurface);
	texteQuitter->setPositionX(30);
	texteQuitter->setPositionY(hauteurEcran*0.7);
	texteQuitter->afficher();
	listeSDLTexteMenu0->push_back(texteQuitter);
	
	while(!input.finish())
	{
		input.updateEvenements();

		SDL_FillRect(gScreenSurface,NULL,NULL);
		
		if(input.getTouche(SDL_SCANCODE_ESCAPE))
		{
			break;
		}
		for(int i=0;i<listeSDLTexteMenu0->size();i++)
		{
			if((input.getX()>listeSDLTexteMenu0->at(i)->getPositionX())
				&&(input.getY()>listeSDLTexteMenu0->at(i)->getPositionY())
				&&(input.getY()<listeSDLTexteMenu0->at(i)->getPositionY()+listeSDLTexteMenu0->at(i)->getHauteur())
				&&(input.getX()<listeSDLTexteMenu0->at(i)->getPositionX()+listeSDLTexteMenu0->at(i)->getLargeur()))
			{
				listeSDLTexteMenu0->at(i)->setCouleur(255,0,0);
				listeSDLTexteMenu0->at(i)->recharger();
				listeSDLTexteMenu0->at(i)->afficher();

				if(input.getBoutonSouris(1)) //clic gauche souris
				{
					if(listeSDLTexteMenu0->at(i)->getTexte()=="Commencer une nouvelle partie")
					{
						menu=1;
						input.setTerminer(true);
						
					}
					else if(listeSDLTexteMenu0->at(i)->getTexte()=="Reprendre une partie")
					{
						menu=2;
						//input.setTerminer(true);
					}
					else if(listeSDLTexteMenu0->at(i)->getTexte()=="Options")
					{
						menu=3;
						input.setTerminer(true);
					}
					else if(listeSDLTexteMenu0->at(i)->getTexte()=="Crédits")
					{
						menu=4;
						//input.setTerminer(true);
					}
					else if(listeSDLTexteMenu0->at(i)->getTexte()=="Quitter")
					{
						menu=0;
						input.setTerminer(true);
					}
				}
			}
			else
			{
					
				listeSDLTexteMenu0->at(i)->setCouleur(255,255,255);
				listeSDLTexteMenu0->at(i)->recharger();
				listeSDLTexteMenu0->at(i)->afficher();
				
			}
		}

		curseur->setPositionX(input.getX());
		curseur->setPositionY(input.getY());
		curseur->afficher();

		SDL_UpdateWindowSurface( screen );
		
	
    }

	switch(menu)
	{
		case 0:
			estQuitte=true;
			//SDL_Quit();
			SDL_DestroyWindow(screen);
			break;
		case 1:
			//first=new thread(&Menu::commencerPartie,this);
			//first->join();
			this->commencerPartie();
			break;
		case 2:
			this->chargerMenuChargementPartie();
			break;
		case 3:
			this->chargerMenuOptions();
			break;
		case 4:
			this->chargerMenuCredits();
			break;
	}

	
}
void Menu::chargerMenuOptions()
{
	

	SDL_FillRect(gScreenSurface,NULL,NULL);
	input.setTerminer(false);
	listeSDLTexteMenu1=new vector<SDLTexte*>();
	listeSDLImageMenu1=new vector<SDLImage*>();

	

	SDLImage *curseur=new SDLImage(gScreenSurface,"Bitmaps/cible5.png");
	curseur->setPositionX(input.getX());
	curseur->setPositionY(input.getY());
	curseur->afficher();

	

	SDLImage *imageGauche=new SDLImage(gScreenSurface,"Bitmaps/gauche.png");
	imageGauche->setPositionX(largeurEcran*0.5);
	imageGauche->setPositionY(hauteurEcran*0.3);
	imageGauche->setCategorie(SDLImage::type::fleche_gauche);
	imageGauche->afficher();
	listeSDLImageMenu1->push_back(imageGauche);

	SDLImage *imageDroite=new SDLImage(gScreenSurface,"Bitmaps/droite.png");
	imageDroite->setPositionX(largeurEcran*0.68);
	imageDroite->setPositionY(hauteurEcran*0.3);
	imageDroite->setCategorie(SDLImage::type::fleche_droite);
	imageDroite->afficher();
	listeSDLImageMenu1->push_back(imageDroite);

	SDLImage *imageCheckBoxCheck=new SDLImage(gScreenSurface,"Bitmaps/checkbox_check.png");
	imageCheckBoxCheck->setPositionX(largeurEcran*0.5);
	imageCheckBoxCheck->setPositionY(hauteurEcran*0.4);
	imageCheckBoxCheck->setCategorie(SDLImage::type::checkbox);
	imageCheckBoxCheck->afficher();
	listeSDLImageMenu1->push_back(imageCheckBoxCheck);

	SDLImage *imageCheckBoxCheck2=new SDLImage(gScreenSurface,"Bitmaps/checkbox_check.png");
	imageCheckBoxCheck2->setPositionX(largeurEcran*0.5);
	imageCheckBoxCheck2->setPositionY(hauteurEcran*0.5);
	imageCheckBoxCheck2->setCategorie(SDLImage::type::checkbox);
	imageCheckBoxCheck2->afficher();
	listeSDLImageMenu1->push_back(imageCheckBoxCheck2);

	SDLImage *imageGauche2=new SDLImage(gScreenSurface,"Bitmaps/gauche.png");
	imageGauche2->setPositionX(largeurEcran*0.5);
	imageGauche2->setPositionY(hauteurEcran*0.6);
	imageGauche2->setCategorie(SDLImage::type::fleche_gauche);
	imageGauche2->afficher();
	listeSDLImageMenu1->push_back(imageGauche2);

	SDLImage *imageDroite2=new SDLImage(gScreenSurface,"Bitmaps/droite.png");
	imageDroite2->setPositionX(largeurEcran*0.68);
	imageDroite2->setPositionY(hauteurEcran*0.6);
	imageDroite2->setCategorie(SDLImage::type::fleche_droite);
	imageDroite2->afficher();
	listeSDLImageMenu1->push_back(imageDroite2);

	SDLTexte *texteResolution=new SDLTexte("Résolution de l'écran",gScreenSurface);
	texteResolution->setPositionX(30);
	texteResolution->setPositionY(hauteurEcran*0.3);
	texteResolution->afficher();
	listeSDLTexteMenu1->push_back(texteResolution);

	SDLTexte *texteResolutionValeur=new SDLTexte(listeResolution->at(indexResolution),gScreenSurface);
	texteResolutionValeur->setPositionX(largeurEcran*0.55);
	texteResolutionValeur->setPositionY(hauteurEcran*0.3);
	texteResolutionValeur->afficher();
	listeSDLTexteMenu1->push_back(texteResolutionValeur);
		
	SDLTexte *texteSyncV=new SDLTexte("Synchronisation verticale",gScreenSurface);
	texteSyncV->setPositionX(30);
	texteSyncV->setPositionY(hauteurEcran*0.4);
	texteSyncV->afficher();
	listeSDLTexteMenu1->push_back(texteSyncV);

	SDLTexte *textePleinEcran=new SDLTexte("Plein écran",gScreenSurface);
	textePleinEcran->setPositionX(30);
	textePleinEcran->setPositionY(hauteurEcran*0.5);
	textePleinEcran->afficher();
	listeSDLTexteMenu1->push_back(textePleinEcran);

	SDLTexte *texteQualite=new SDLTexte("Qualité visuelle",gScreenSurface);
	texteQualite->setPositionX(30);
	texteQualite->setPositionY(hauteurEcran*0.6);
	texteQualite->afficher();
	listeSDLTexteMenu1->push_back(texteQualite);

	SDLTexte *texteQualiteValeur=new SDLTexte(listeQualite->at(indexQualite),gScreenSurface);
	texteQualiteValeur->setPositionX(largeurEcran*0.55);
	texteQualiteValeur->setPositionY(hauteurEcran*0.6);
	texteQualiteValeur->afficher();
	listeSDLTexteMenu1->push_back(texteQualiteValeur);

	SDLTexte *texteRetour=new SDLTexte("Retour",gScreenSurface);
	texteRetour->setPositionX(30);
	texteRetour->setPositionY(hauteurEcran*0.9);
	texteRetour->afficher();
	listeSDLTexteMenu1->push_back(texteRetour);

	SDLTexte *texteAppliquer=new SDLTexte("Appliquer",gScreenSurface);
	texteAppliquer->setPositionX(largeurEcran*0.45);
	texteAppliquer->setPositionY(hauteurEcran*0.9);
	texteAppliquer->afficher();
	listeSDLTexteMenu1->push_back(texteAppliquer);
	
	
	while(!input.finish())
	{
		input.updateEvenements();

		SDL_FillRect(gScreenSurface,NULL,NULL);

		if(input.getTouche(SDL_SCANCODE_ESCAPE))
		{
			break;
		}
		for(int i=0;i<listeSDLTexteMenu1->size();i++)
		{

			if((input.getX()>listeSDLTexteMenu1->at(i)->getPositionX())
				&&(input.getY()>listeSDLTexteMenu1->at(i)->getPositionY())
				&&(input.getY()<listeSDLTexteMenu1->at(i)->getPositionY()+listeSDLTexteMenu1->at(i)->getHauteur())
				&&(input.getX()<listeSDLTexteMenu1->at(i)->getPositionX()+listeSDLTexteMenu1->at(i)->getLargeur()))
			{
				listeSDLTexteMenu1->at(i)->setCouleur(255,0,0);
				listeSDLTexteMenu1->at(i)->recharger();
				listeSDLTexteMenu1->at(i)->afficher();

				if(input.getBoutonSouris(1)) //clic gauche souris
				{
					if(listeSDLTexteMenu1->at(i)->getTexte()=="Résolution de l'écran")
					{
						//menu=1;
						//input.setTerminer(true);
						
					}
					else if(listeSDLTexteMenu1->at(i)->getTexte()=="Synchronisation verticale")
					{
						//menu=2;
						//input.setTerminer(true);
					}
					else if(listeSDLTexteMenu1->at(i)->getTexte()=="Plein écran")
					{
						//menu=3;
						//input.setTerminer(true);
					}
					else if(listeSDLTexteMenu1->at(i)->getTexte()=="Qualité visuelle")
					{
						//menu=4;
						//input.setTerminer(true);
					}
					else if(listeSDLTexteMenu1->at(i)->getTexte()=="Retour")
					{
						menu=0;
						input.setTerminer(true);
					}
					else if(listeSDLTexteMenu1->at(i)->getTexte()=="Appliquer")
					{
						this->ecrireParametres();
						SDL_DestroyWindow(screen);
						string res=listeResolution->at(indexResolution);
						int posCarX=res.find('x');
						largeurEcran=atoi(res.substr(0,posCarX-1).c_str());
						hauteurEcran=atoi(res.substr(posCarX+1).c_str());

						SDL_CreateWindowAndRenderer(largeurEcran,hauteurEcran,SDL_WINDOWPOS_UNDEFINED|SDL_WINDOWPOS_UNDEFINED|SDL_WINDOW_SHOWN, &screen, &sdlRenderer);
						if( screen)
						{
							int t=SDL_SetWindowFullscreen(screen,pleinEcranCheck);
							gScreenSurface = SDL_GetWindowSurface( screen );
							
							chargerMenuOptions();
							input.setTerminer(true);
							goto stop;
						}
						//menu=5;
						//input.setTerminer(true);
					}
				}
			}
			else
			{
					
				listeSDLTexteMenu1->at(i)->setCouleur(255,255,255);
				listeSDLTexteMenu1->at(i)->recharger();
				listeSDLTexteMenu1->at(i)->afficher();
					
			}
		}

		for(int i=0;i<listeSDLImageMenu1->size();i++)
		{

			if((input.getX()>listeSDLImageMenu1->at(i)->getPositionX())
				&&(input.getY()>listeSDLImageMenu1->at(i)->getPositionY())
				&&(input.getY()<listeSDLImageMenu1->at(i)->getPositionY()+listeSDLImageMenu1->at(i)->getHauteur())
				&&(input.getX()<listeSDLImageMenu1->at(i)->getPositionX()+listeSDLImageMenu1->at(i)->getLargeur()))
			{
				if(listeSDLImageMenu1->at(i)->getCategorie()==SDLImage::type::fleche_gauche)
				{
					if(!flecheGaucheResOn && i==0)
					{
						listeSDLImageMenu1->at(i)->effacer();
						listeSDLImageMenu1->at(i)->setImage("Bitmaps/gauche_clic.png");
						listeSDLImageMenu1->at(i)->afficher();
						flecheGaucheResOn=true;
					}
					else if(!flecheGaucheQualiteOn && i==4)
					{
						listeSDLImageMenu1->at(i)->effacer();
						listeSDLImageMenu1->at(i)->setImage("Bitmaps/gauche_clic.png");
						listeSDLImageMenu1->at(i)->afficher();
						flecheGaucheQualiteOn=true;
					}
				}
				else if(listeSDLImageMenu1->at(i)->getCategorie()==SDLImage::type::fleche_droite)
				{
					if(!flecheDroiteResOn && i==1)
					{
						listeSDLImageMenu1->at(i)->effacer();
						listeSDLImageMenu1->at(i)->setImage("Bitmaps/droite_clic.png");
						listeSDLImageMenu1->at(i)->afficher();
					}
					else if(!flecheDroiteQualiteOn && i==5)
					{
						listeSDLImageMenu1->at(i)->effacer();
						listeSDLImageMenu1->at(i)->setImage("Bitmaps/droite_clic.png");
						listeSDLImageMenu1->at(i)->afficher();
					}
					
				}
				

				if(input.getBoutonSouris(1)) //clic gauche souris
				{
					switch(i)
					{
						case 0:
							listeSDLTexteMenu1->at(1)->effacer();
							if(indexResolution==0)
							{
								indexResolution=listeResolution->size();
							}
							listeSDLTexteMenu1->at(1)->setTexte(listeResolution->at(--indexResolution));
							listeSDLTexteMenu1->at(1)->recharger();
							listeSDLTexteMenu1->at(1)->afficher();
							SDL_Delay(200);
							break;
						case 1:
							listeSDLTexteMenu1->at(1)->effacer();
							if(indexResolution==listeResolution->size()-1)
							{
								indexResolution=-1;
							}
							listeSDLTexteMenu1->at(1)->setTexte(listeResolution->at(++indexResolution));
							listeSDLTexteMenu1->at(1)->recharger();
							listeSDLTexteMenu1->at(1)->afficher();
							SDL_Delay(200);
							break;
						case 2:
							listeSDLImageMenu1->at(i)->effacer();

							if(!syncVCheck)
							{
								listeSDLImageMenu1->at(i)->setImage("Bitmaps/checkbox_check.png");
								syncVCheck=true;
								SDL_Delay(200);
							}
							else
							{
								listeSDLImageMenu1->at(i)->setImage("Bitmaps/checkbox_non_check.png");
								syncVCheck=false;
								SDL_Delay(200);
							}
							
							listeSDLImageMenu1->at(i)->afficher();

							break;
						case 3:
							listeSDLImageMenu1->at(i)->effacer();

							if(!pleinEcranCheck)
							{
								listeSDLImageMenu1->at(i)->setImage("Bitmaps/checkbox_check.png");
								pleinEcranCheck=true;
								SDL_Delay(200);
							}
							else
							{
								listeSDLImageMenu1->at(i)->setImage("Bitmaps/checkbox_non_check.png");
								pleinEcranCheck=false;
								SDL_Delay(200);
							}
							
							listeSDLImageMenu1->at(i)->afficher();
							break;
						case 4:
							listeSDLTexteMenu1->at(5)->effacer();

							if(indexQualite==0)
							{
								indexQualite=listeQualite->size();
							}
							
							listeSDLTexteMenu1->at(5)->setTexte(listeQualite->at(--indexQualite));
							listeSDLTexteMenu1->at(5)->recharger();
							listeSDLTexteMenu1->at(5)->afficher();
							SDL_Delay(200);
							break;
						case 5:
							listeSDLTexteMenu1->at(5)->effacer();

							if(indexQualite==listeQualite->size()-1)
							{
								indexQualite=-1;
							}
							

							listeSDLTexteMenu1->at(5)->setTexte(listeQualite->at(++indexQualite));
							listeSDLTexteMenu1->at(5)->recharger();
							listeSDLTexteMenu1->at(5)->afficher();
							SDL_Delay(200);
							break;
					}
				}
				

			}
			else
			{
				flecheGaucheResOn=false,flecheDroiteResOn=false,flecheGaucheQualiteOn=false,flecheDroiteQualiteOn=false;

				if(i==0||i==4)
				{
					listeSDLImageMenu1->at(i)->effacer();
					listeSDLImageMenu1->at(i)->setImage("Bitmaps/gauche.png");
					listeSDLImageMenu1->at(i)->afficher();
				}
				else if(i==1||i==5)
				{
					listeSDLImageMenu1->at(i)->effacer();
					listeSDLImageMenu1->at(i)->setImage("Bitmaps/droite.png");
					listeSDLImageMenu1->at(i)->afficher();
				}
				else
				{
					
				}
			}
			listeSDLImageMenu1->at(i)->effacer();
			listeSDLImageMenu1->at(i)->afficher();
		}

		curseur->setPositionX(input.getX());
		curseur->setPositionY(input.getY());
		curseur->afficher();
		
		SDL_UpdateWindowSurface( screen );
	
    }

	

	switch(menu)
	{
		case 0:
			this->chargerMenuPrincipal();
			break;
		case 1:
			//this->commencerPartie();
			break;
		case 2:
			//this->chargerMenuChargementPartie();
			break;
		case 3:
			//this->chargerMenuOptions();
			break;
		case 4:
			//this->chargerMenuCredits();
			break;
	}
	stop:;

}
void Menu::chargerMenuCredits()
{

}
void Menu::chargerMenuChargementPartie()
{

}
void Menu::commencerPartie()
{
	
	SDL_HideWindow(screen);
	//SDL_Rect *rect=new SDL_Rect();
	//SDL_FillRect(gScreenSurface,NULL,NULL);
	//SDL_UpdateWindowSurface( screen );
	/*
	SDLTexte *texteInitFenetre=new SDLTexte("Initialisation de la fenetre",gScreenSurface);
	texteInitFenetre->setPositionX(30);
	texteInitFenetre->setPositionY(hauteurEcran*0.6);
	texteInitFenetre->afficher();
	
	SceneOpenGL scene;
	thread *t=new thread(&SceneOpenGL::initialiserFenetre,scene);

	
	
	SDL_UpdateWindowSurface( screen );
	
	t->join();
	t->detach();
	t=new thread(&SceneOpenGL::initialiserGL,scene);

	
	SDLTexte *texteInitGL=new SDLTexte("Initialisation d'OpenGL",gScreenSurface);
	texteInitGL->setPositionX(30);
	texteInitGL->setPositionY(hauteurEcran*0.7);
	texteInitGL->afficher();

	t->join();
	t->detach();
	t=new thread(&SceneOpenGL::chargerObjets,scene);

	
	SDLTexte *texteChargementDecor=new SDLTexte("Chargement du décor",gScreenSurface);
	texteChargementDecor->setPositionX(30);
	texteChargementDecor->setPositionY(hauteurEcran*0.7);
	texteChargementDecor->afficher();

	t->join();
	t->detach();
	/*
	if(scene.initialiserFenetre()==false)
	{
		
	}
	if(scene.initialiserGL()==false)
	{
		
	}
	


	//scene.chargerObjets();
	scene.bouclePrincipale();
	*/
}

void Menu::ecrireParametres()
{
	ofstream fichier("config.cfg", ios::out | ios::trunc);
  
	if(fichier)
	{
		fichier << "plein ecran: " << pleinEcranCheck<< endl;
		fichier << "synchronisation verticale: " << syncVCheck<< endl;
		fichier << "resolution: " << listeResolution->at(indexResolution)<< endl;
		fichier.close();
	}
	else
			cerr << "Impossible d'ouvrir le fichier !" << endl;
}

Menu::~Menu()
{
	SDL_Quit();
	TTF_Quit();
}