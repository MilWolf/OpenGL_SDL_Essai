#include "SceneOpenGL.h"
#include "Menu.h"
#include <stdlib.h>
#include <thread>

using namespace std;

int main(int argc, char **argv)
{   
	Menu menu;

	if(!menu.estQuitte)
	{
		SceneOpenGL scene;
		

		if(scene.initialiserFenetre()==false)
		{
			return -1;
		}
		if(scene.initialiserGL()==false)
		{
			return -2;
		}


		scene.chargerObjets();
		scene.bouclePrincipale();
	}
	

    return 0;
}