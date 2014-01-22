#include "Material.h"

Material::Material()
{
	couleurDiffuse=new float[3];
}

Material::Material(string nom)
{
	this->nom=nom;
}

Material::Material(string nom,string texture,float couleurAmbiante[3],float couleurDiffuse[3],float couleurSpeculaire[3],double dureteSpeculaire,double indiceRefraction,double opacite)
{
	this->nom=nom;
	this->texture=texture;
	this->couleurAmbiante[3]=couleurAmbiante[3];
	this->couleurDiffuse[3]=couleurDiffuse[3];
	this->couleurSpeculaire[3]=couleurSpeculaire[3];
	this->dureteSpeculaire=dureteSpeculaire;
	this->indiceRefraction=indiceRefraction;
	this->opacite=opacite;
}

Material::~Material()
{
}

string Material::getNom()
{
	return this->nom;
}
string Material::getTexture()
{
	return this->texture;
}
float* Material::getCouleurAmbiante()
{
	return this->couleurAmbiante;
}
float* Material::getCouleurDiffuse()
{
	return this->couleurDiffuse;
}
float* Material::getCouleurSpeculaire()
{
	return this->couleurSpeculaire;
}
double Material::getDureteSpeculaire()
{
	return this->dureteSpeculaire;
}
double Material::getIndiceRefraction()
{
	return this->indiceRefraction;
}
double Material::getOpacite()
{
	return this->opacite;
}
bool Material::getMipmap()
{
	return this->mipmap;
}

void Material::setNom(string nom)
{
	this->nom=nom;
}
void Material::setTexture(string texture)
{
	this->texture=texture;
}
void Material::setCouleurAmbiante(float couleurAmbiante[3])
{
	this->couleurAmbiante[3]=couleurAmbiante[3];
}
void Material::setCouleurDiffuse(float *couleurDiffuse)
{
	this->couleurDiffuse=couleurDiffuse;
}
void Material::setCouleurSpeculaire(float couleurSpeculaire[3])
{
	this->couleurSpeculaire[3]=couleurSpeculaire[3];
}
void Material::setDureteSpeculaire(double dureteSpeculaire)
{
	this->dureteSpeculaire=dureteSpeculaire;
}
void Material::setIndiceRefraction(double indiceRefraction)
{
	this->indiceRefraction=indiceRefraction;
}
void Material::setOpacite(double opacite)
{
	this->opacite=opacite;
}
void Material::setMipmap(bool mipmap)
{
	this->mipmap=mipmap;
}