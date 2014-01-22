#include "ObjLoader.h"

ObjLoader::ObjLoader(string modele)
{
	this->nom=modele;
	ifstream fichier(modele);
	listeSommets=new vector<double*>();
	listeCoordonneesTexture=new vector<float*>();

	tabCouleurDiffuse=new float[3];
	
	vectorVertices=new vector<float>();
	vectorMaterials=new vector<Material>();
	vectorFloatMaterials=new vector<float>();
	vectorCoordonneesTexture=new vector<float>();

	objetTexture=false;

	Material *material=new Material();

	vecTexMat=new vector<TexMat>();

	int indexMat;
 
    if (fichier)
    {
        string ligne;
 
        while (getline( fichier, ligne ))
        {
			if(ligne.find("mtllib ")==0) //lecture du fichier obj
			{
				string fichierMaterial=ligne.substr(ligne.find(' ')+1,ligne.length());

				ifstream fluxMaterial("modeles/"+fichierMaterial);

				if(fluxMaterial) //Lecture du fichier mtl
				{
					string ligneMaterial;

					while(getline( fluxMaterial, ligneMaterial ))
					{
						if(ligneMaterial.find("newmtl ")==0)
						{
							material=new Material();
							material->setNom(ligneMaterial.substr(ligneMaterial.find(' ')+1,ligneMaterial.length()));
						}
						else if(ligneMaterial.find("Ns ")==0) //dureté spéculaire
						{
							string sDureteSpeculaire=ligneMaterial.substr(ligneMaterial.find(' ')+1,ligneMaterial.length());
							material->setDureteSpeculaire(strtod(sDureteSpeculaire.c_str(),NULL));
						}
						else if(ligneMaterial.find("Ka ")==0) //couleur ambiante
						{
							float couleurAmbiante[3];
							int posEspace1=ligneMaterial.find(' ',3);
							int posEspace2=ligneMaterial.find(' ',posEspace1+1);
							couleurAmbiante[0]=atof(ligneMaterial.substr(3,posEspace1-1).c_str());
							couleurAmbiante[1]=atof(ligneMaterial.substr(posEspace1+1,posEspace2-1).c_str());
							couleurAmbiante[2]=atof(ligneMaterial.substr(posEspace2+1,ligneMaterial.length()).c_str());

							material->setCouleurAmbiante(couleurAmbiante);
						}
						else if(ligneMaterial.find("Kd ")==0) //couleur diffuse
						{
							float *couleurDiffuse=new float[3];
							int posEspace1=ligneMaterial.find(' ',3);
							int posEspace2=ligneMaterial.find(' ',posEspace1+1);
							couleurDiffuse[0]=atof(ligneMaterial.substr(3,posEspace1-1).c_str());
							couleurDiffuse[1]=atof(ligneMaterial.substr(posEspace1+1,posEspace2-1).c_str());
							couleurDiffuse[2]=atof(ligneMaterial.substr(posEspace2+1,ligneMaterial.length()).c_str());

							material->setCouleurDiffuse(couleurDiffuse);
						}
						else if(ligneMaterial.find("Ks ")==0) //couleur spéculaire
						{
							float couleurSpeculaire[3];
							int posEspace1=ligneMaterial.find(' ',3);
							int posEspace2=ligneMaterial.find(' ',posEspace1+1);
							couleurSpeculaire[0]=atof(ligneMaterial.substr(3,posEspace1-1).c_str());
							couleurSpeculaire[1]=atof(ligneMaterial.substr(posEspace1+1,posEspace2-1).c_str());
							couleurSpeculaire[2]=atof(ligneMaterial.substr(posEspace2+1,ligneMaterial.length()).c_str());

							material->setCouleurSpeculaire(couleurSpeculaire);
						}
						else if(ligneMaterial.find("Ni ")==0) //indice de réfraction
						{
							string sIndiceRefraction=ligneMaterial.substr(ligneMaterial.find(' ')+1,ligneMaterial.length());
							material->setIndiceRefraction(strtod(sIndiceRefraction.c_str(),NULL));
						}
						else if(ligneMaterial.find("d ")==0) //opacité
						{
							string sOpacite=ligneMaterial.substr(ligneMaterial.find(' ')+1,ligneMaterial.length());
							material->setOpacite(strtod(sOpacite.c_str(),NULL));
							material->setTexture("");
							vectorMaterials->push_back(*material);
						}
						else if(ligneMaterial.find("map_Kd ")==0) //texture
						{
							string sTexture=ligneMaterial.substr(ligneMaterial.find(' ')+1,ligneMaterial.length());
							(vectorMaterials->at(vectorMaterials->size()-1)).setTexture(sTexture);
						}
						else if(ligneMaterial.find("mipmap ")==0)
						{
							int mipmap=atoi(ligneMaterial.substr(ligneMaterial.find(' ')+1,ligneMaterial.length()).c_str());

							if(mipmap==0)
							{
								(vectorMaterials->at(vectorMaterials->size()-1)).setMipmap(false);
							}							
							else
							{
								(vectorMaterials->at(vectorMaterials->size()-1)).setMipmap(true);
							}
							
						}
					}
				}
			}
			else if(ligne.find("v ")==0)
			{
				coordonneesSommet=new double[3];
				int posEspace1=ligne.find(' ',2);
				int posEspace2=ligne.find(' ',posEspace1+1);
				coordonneesSommet[0]=strtod(ligne.substr(2,posEspace1-1).c_str(),NULL);
				coordonneesSommet[1]=strtod(ligne.substr(posEspace1+1,posEspace2-1).c_str(),NULL);
				coordonneesSommet[2]=strtod(ligne.substr(posEspace2+1,ligne.length()).c_str(),NULL);
				listeSommets->push_back(coordonneesSommet);
			}
			else if(ligne.find("vt ")==0)
			{
				objetTexture=true; 
				coordonneesTexture=new float[2];
				int posEspace1=ligne.find(' ',3);
				coordonneesTexture[0]=atof(ligne.substr(2,posEspace1-1).c_str());
				coordonneesTexture[1]=atof(ligne.substr(posEspace1+1,ligne.length()).c_str());
				listeCoordonneesTexture->push_back(coordonneesTexture);
			}
			else if(ligne.find("usemtl ")==0)
			{
				string nomMaterial=ligne.substr(ligne.find(' ')+1,ligne.length());
				
				for(int i=0;i<vectorMaterials->size();i++)
				{
					if(vectorMaterials->at(i).getNom().compare(nomMaterial)==0)
					{
						indexMat=i;
						i=vectorMaterials->size();
					}
				}

				TexMat t(vectorMaterials->at(indexMat).getTexture(),vectorVertices->size()/3);
				vecTexMat->push_back(t);
				
			}
			else if(ligne.find("f ")==0) //ligne décrivant des faces
			{
				int posEspace1,posEspace2;
				int posSlash1,posSlash2,posSlash3;
				int sommet1,sommet2,sommet3;
				int indice1,indice2,indice3;
				
				if(objetTexture==true) //des coordonnées de texture sont spécifiées
				{
					posEspace1=ligne.find(' ',2);
					posEspace2=ligne.find(' ',posEspace1+1);

					posSlash1=ligne.find('/',0);
					posSlash2=ligne.find('/',posSlash1+1);
					posSlash3=ligne.find('/',posSlash2+1);

					sommet1=atoi(ligne.substr(2,posSlash1-1).c_str());
					sommet2=atoi(ligne.substr(posEspace1+1,posSlash2-1).c_str());
					sommet3=atoi(ligne.substr(posEspace2+1,posSlash3-1).c_str());

					indice1=atoi(ligne.substr(posSlash1+1,posEspace1-1).c_str());
					indice2=atoi(ligne.substr(posSlash2+1,posEspace2-1).c_str());
					indice3=atoi(ligne.substr(posSlash3+1,ligne.length()).c_str());
					
					vectorCoordonneesTexture->push_back(listeCoordonneesTexture->at(indice1-1)[0]);
					vectorCoordonneesTexture->push_back(listeCoordonneesTexture->at(indice1-1)[1]);

					vectorCoordonneesTexture->push_back(listeCoordonneesTexture->at(indice2-1)[0]);
					vectorCoordonneesTexture->push_back(listeCoordonneesTexture->at(indice2-1)[1]);

					vectorCoordonneesTexture->push_back(listeCoordonneesTexture->at(indice3-1)[0]);
					vectorCoordonneesTexture->push_back(listeCoordonneesTexture->at(indice3-1)[1]);

				}
				else
				{
					posEspace1=ligne.find(' ',2);
					posEspace2=ligne.find(' ',posEspace1+1);

					sommet1=atoi(ligne.substr(2,posEspace1-1).c_str());
					sommet2=atoi(ligne.substr(posEspace1+1,posEspace2-1).c_str());
					sommet3=atoi(ligne.substr(posEspace2+1,ligne.length()).c_str());
				}

				vectorVertices->push_back(listeSommets->at(sommet1-1)[0]);
				vectorVertices->push_back(listeSommets->at(sommet1-1)[1]);
				vectorVertices->push_back(listeSommets->at(sommet1-1)[2]);					

				vectorVertices->push_back(listeSommets->at(sommet2-1)[0]);
				vectorVertices->push_back(listeSommets->at(sommet2-1)[1]);
				vectorVertices->push_back(listeSommets->at(sommet2-1)[2]);					

				vectorVertices->push_back(listeSommets->at(sommet3-1)[0]);
				vectorVertices->push_back(listeSommets->at(sommet3-1)[1]);
				vectorVertices->push_back(listeSommets->at(sommet3-1)[2]);
				
				tabCouleurDiffuse=new float[3];
				string nomCouleur=vectorMaterials->at(indexMat).getNom();
				tabCouleurDiffuse=vectorMaterials->at(indexMat).getCouleurDiffuse();

				vectorFloatMaterials->push_back(tabCouleurDiffuse[0]);
				vectorFloatMaterials->push_back(tabCouleurDiffuse[1]);
				vectorFloatMaterials->push_back(tabCouleurDiffuse[2]);

				vectorFloatMaterials->push_back(tabCouleurDiffuse[0]);
				vectorFloatMaterials->push_back(tabCouleurDiffuse[1]);
				vectorFloatMaterials->push_back(tabCouleurDiffuse[2]);

				vectorFloatMaterials->push_back(tabCouleurDiffuse[0]);
				vectorFloatMaterials->push_back(tabCouleurDiffuse[1]);
				vectorFloatMaterials->push_back(tabCouleurDiffuse[2]);
			}
        }
    }
	else
	{
		
	}

	//On transfère le vector de vertices dans le tableau de vertices
	tableauVertices=new float[vectorVertices->size()];
	nombreTriangles=vectorVertices->size()/3;
	nombreVertices=vectorVertices->size();
	for(int i=0;i<vectorVertices->size();i++)
	{
		tableauVertices[i]=vectorVertices->at(i);
	}

	//On transfère le vector de material dans le tableau de material
	tableauCouleurs=new float[vectorFloatMaterials->size()];
	nombreCouleurs=vectorFloatMaterials->size();
	for(int i=0;i<vectorFloatMaterials->size();i++)
	{
		tableauCouleurs[i]=vectorFloatMaterials->at(i);
	}


	tabCoordonneesTexture=new float[vectorCoordonneesTexture->size()];
	nombreCoordonnes=vectorCoordonneesTexture->size();
	for(int i=0;i<vectorCoordonneesTexture->size();i++)
	{
		tabCoordonneesTexture[i]=vectorCoordonneesTexture->at(i);
	}

}

int ObjLoader::getNombreVertices()
{
	return this->nombreVertices;		
}
int ObjLoader::getNombreCouleurs()
{
	return this->nombreCouleurs;
}
int ObjLoader::getNombreCoordonnees()
{
	return this->nombreCoordonnes;		
}
vector<TexMat>* ObjLoader::getTexMat()
{
	return this->vecTexMat;
}

float* ObjLoader::getTableauVertices()
{
	return this->tableauVertices;
}

float* ObjLoader::getTableauCouleurs()
{
	return this->tableauCouleurs;
}

float* ObjLoader::getTableauCoordTexture()
{
	return this->tabCoordonneesTexture;
}

int ObjLoader::getNombreTriangles()
{
	return this->nombreTriangles;
}

ObjLoader::~ObjLoader()
{
}