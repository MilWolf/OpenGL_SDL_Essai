#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ItemHUD.h"

class HUD
{
public:
	HUD(int largeurEcran,int hauteurEcran);
	~HUD();

	void initialiser();
	void charger();
	void afficher(mat4 &projection, mat4 &modelview);

private:

	ItemHUD *miniMap;
	ItemHUD *arme;
	ItemHUD *fps;
	ItemHUD *sante;
	ItemHUD *cible;

	int largeurEcran,hauteurEcran;
};
