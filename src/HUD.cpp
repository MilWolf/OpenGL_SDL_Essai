#include "HUD.h"

HUD::HUD(int largeurEcran,int hauteurEcran)
{
	this->largeurEcran=largeurEcran;
	this->hauteurEcran=hauteurEcran;
}

HUD::~HUD()
{
}

void HUD::initialiser()
{
	/*
	float *v1=new float[12]();
	v1[0]=-0.79;v1[1]=-0.77;v1[2]=-0.48;v1[3]=-0.77;v1[4]=-0.48;v1[5]=-0.45;v1[6]=-0.79;v1[7]=-0.45;v1[8]=-0.79;v1[9]=-0.76;v1[10]=-0.48;v1[11]=-0.45;

	float *v2=new float[12]();
	v2[0]=90;v2[1]=60;v2[2]=70;v2[3]=60;v2[4]=90;v2[5]=90;v2[6]=70;v2[7]=60;v2[8]=90;v2[9]=90;v2[10]=70;v2[11]=90;
	
	float *v3=new float[12]();
	v3[0]=10;v3[1]=10;v3[2]=10;v3[3]=110;v3[4]=110;v3[5]=110;v3[6]=110;v3[7]=110;v3[8]=110;v3[9]=10;v3[10]=10;v3[11]=10;
	*/

	float *v4=new float[12]();

	//point inférieur gauche
	v4[0]=largeurEcran-200;
	v4[1]=100;

	//point supérieur gauche
	v4[2]=largeurEcran-200;
	v4[3]=200;

	//point supérieur droit
	v4[4]=largeurEcran-100;
	v4[5]=200;

	//point supérieur droit
	v4[6]=largeurEcran-100;
	v4[7]=200;

	//point inférieur droit
	v4[8]=largeurEcran-100;
	v4[9]=100;

	//point inférieur gauche
	v4[10]=largeurEcran-200;
	v4[11]=100;




	float *v5=new float[12]();

	//point inférieur gauche
	v5[0]=(largeurEcran/2)-20;
	v5[1]=(hauteurEcran/2)-20;

	//point supérieur gauche
	v5[2]=(largeurEcran/2)-20;
	v5[3]=(hauteurEcran/2)+20;

	//point supérieur droit
	v5[4]=(largeurEcran/2)+20;
	v5[5]=(hauteurEcran/2)+20;

	//point supérieur droit
	v5[6]=(largeurEcran/2)+20;
	v5[7]=(hauteurEcran/2)+20;

	//point inférieur droit
	v5[8]=(largeurEcran/2)+20;
	v5[9]=(hauteurEcran/2)-20;

	//point inférieur gauche
	v5[10]=(largeurEcran/2)-20;
	v5[11]=(hauteurEcran/2)-20;

	float *ct1 =new float[12]();
	ct1[0]=0;ct1[1]=0;ct1[2]=0;ct1[3]=1;ct1[4]=1;ct1[5]=1;ct1[6]=1;ct1[7]=1;ct1[8]=1;ct1[9]=0;ct1[10]=0;ct1[11]=0;

	miniMap=new ItemHUD(v4,ct1,12,12,6,"Arc.png","Shaders/texture.vert", "Shaders/texture.frag");
	cible=new ItemHUD(v5,ct1,12,12,6,"cible3.png","Shaders/texture.vert", "Shaders/texture.frag");
	//arme=new ItemHUD(v2,ct1,12,12,"test.png","Shaders/texture.vert", "Shaders/texture.frag");
	//fps=new ItemHUD();
	//sante=new ItemHUD();
}

void HUD::charger()
{
	//miniMap->charger();
	cible->charger();
	//arme->charger();
	//fps->charger(vertices,5,"fps.png");
	//sante->charger(vertices,5,"sante.png");
}

void HUD::afficher(mat4 &projection, mat4 &modelview)
{
	//miniMap->afficher(projection, modelview);
	cible->afficher(projection, modelview);
	//arme->afficher(projection, modelview);
	//fps->afficher(projection,modelview);
	//sante->afficher(projection,modelview);
}