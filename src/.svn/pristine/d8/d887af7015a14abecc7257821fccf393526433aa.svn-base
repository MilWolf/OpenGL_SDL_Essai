#include "MapLoader.h"

vec3 conversionQuaternionEuler(quat quaternion);

MapLoader::MapLoader(string map)
{
	tableauMesh=new vector<Mesh*>();
	tableauObjLoader=new vector<ObjLoader*>();
	const char* title;
	doc=new XMLDocument();
	string chemin="Maps/"+map;
	doc->LoadFile(chemin.c_str());



	//mesh->charger();
	//title=textNode->Value();
	
}

void MapLoader::initialiser()
{
	vector<vector<TexMat>*> texMatsTemp;


	XMLNode *node=doc->FirstChild()->FirstChild();

	for( XMLNode* node2 = node->FirstChild(); node2; node2 = node2->NextSibling()) //parcourt de la liste des mesh
	{
		if ( node2->ToElement() )
		{
			XMLElement* elem = node2->ToElement();
			string element=elem->Value();
			string nom=elem->Attribute("name");

			

			int k=nom.find('.');

			if(k!=-1)
			{
				nom=nom.substr(0,k);
				int index=-1;
				for(int i=0;i<tableauObjLoader->size();i++)
				{
					if(tableauObjLoader->at(i)->nom=="modeles/"+nom+".obj")
					{
						index=i;
						i=tableauObjLoader->size();
					}
				}
				if(index==-1)
				{
					objLoader=new ObjLoader("modeles/"+nom+".obj");
					tableauObjLoader->push_back(objLoader);
				}
				else
				{
					objLoader=tableauObjLoader->at(index);
				}
				
			}
			else
			{
				objLoader=new ObjLoader("modeles/"+nom+".obj");
				tableauObjLoader->push_back(objLoader);
				cout<<"chargement de l'objet "<<nom<<".obj"<<endl;
			}


			//Si les textures ont déjà été chargées une fois, alors on récupère l'id de celles-ci pour les réutiliser
			int t=-1;

			for(int i=0;i<tableauMesh->size();i++)
			{
				
				if("Textures/"+objLoader->getTexMat()->at(0).texture==tableauMesh->at(i)->getTextures()->at(0).getFichierImage())
				{
					t=i;
					i=tableauMesh->size()-1;
				}
				int s=tableauMesh->at(i)->getTextures()->at(0).getID();
				s++;
			}

			texMatsTemp.push_back(objLoader->getTexMat());

			if(t!=-1)
			{
				mesh=new Mesh(objLoader->getTableauVertices(),objLoader->getNombreVertices(),objLoader->getTableauCouleurs(),objLoader->getNombreCouleurs(),objLoader->getTableauCoordTexture(),objLoader->getNombreCoordonnees(),objLoader->getNombreTriangles(),false,objLoader->getTexMat(),tableauMesh->at(t)->getTextures(),"Shaders/texture.vert", "Shaders/texture.frag");
			}
			else
			{
				if(nom=="terrain")
				{
					mesh=new Mesh(objLoader->getTableauVertices(),objLoader->getNombreVertices(),objLoader->getTableauCouleurs(),objLoader->getNombreCouleurs(),objLoader->getTableauCoordTexture(),objLoader->getNombreCoordonnees(),objLoader->getNombreTriangles(),true,objLoader->getTexMat(),"Shaders/texture.vert", "Shaders/texture.frag");
				}
				else
				{
					mesh=new Mesh(objLoader->getTableauVertices(),objLoader->getNombreVertices(),objLoader->getTableauCouleurs(),objLoader->getNombreCouleurs(),objLoader->getTableauCoordTexture(),objLoader->getNombreCoordonnees(),objLoader->getNombreTriangles(),false,objLoader->getTexMat(),"Shaders/texture.vert", "Shaders/texture.frag");
				}
			}
			
			
			mesh->setNom(nom);

			for( XMLNode* node3 = node2->FirstChild(); node3; node3 = node3->NextSibling()) //parcourt des données du mesh
			{
				if ( node3->ToElement() )
				{
					XMLElement* elem3 = node3->ToElement();
					string element3=elem3->Value();
					string name3=elem->Attribute("name");

					for ( const XMLAttribute* attr = elem3->FirstAttribute(); attr; attr = attr->Next() )
					{
						string nomAttribut=attr->Name();

						if(element3=="position")
						{
							if(nomAttribut=="z")
							{
								mesh->setPositionZ(-attr->FloatValue());
							}
							else if(nomAttribut=="x")
							{
								mesh->setPositionX(-attr->FloatValue());
							}
							else if(nomAttribut=="y")
							{
								mesh->setPositionY(attr->FloatValue());
							}
						}
						else if(element3=="rotation")
						{
							if(nomAttribut=="qz")
							{
								mesh->setRotationZ(attr->FloatValue());
							}
							else if(nomAttribut=="qy")
							{
								mesh->setRotationY(attr->FloatValue());
							}
							else if(nomAttribut=="qx")
							{
								mesh->setRotationX(-attr->FloatValue());
							}
							else if(nomAttribut=="qw")
							{
								mesh->setRotationW(attr->FloatValue());
							}
						}
						else if(element3=="scale")
						{
							if(nomAttribut=="y")
							{
								mesh->setScaleY(attr->FloatValue());
							}
							else if(nomAttribut=="x")
							{
								mesh->setScaleX(attr->FloatValue());
							}
							else if(nomAttribut=="z")
							{
								mesh->setScaleZ(attr->FloatValue());
							}
						}
						
					}
				}
				
			}

			tableauMesh->push_back(mesh);
		}
	}
}

void MapLoader::charger()
{
	for(int i=0;i<tableauMesh->size();i++)
	{
		tableauMesh->at(i)->charger();
	}

}

void MapLoader::afficher(mat4 &projection, mat4 &modelview)
{
	mat4 mv=modelview;

	for(int i=0;i<tableauMesh->size();i++)
	{
		/*
		float angle=2*acos(tableauMesh->at(i)->getRotationW());
		angle=(angle*360)/(2*pi<float>());
		vec3 vecteur=conversionQuaternionEuler(quat(tableauMesh->at(i)->getRotationW(),tableauMesh->at(i)->getRotationX(),tableauMesh->at(i)->getRotationY(),tableauMesh->at(i)->getRotationZ()));
		*/
		
		modelview =translate(modelview,vec3(tableauMesh->at(i)->getPositionX(),tableauMesh->at(i)->getPositionY(),tableauMesh->at(i)->getPositionZ()));
		modelview=rotate(modelview,tableauMesh->at(i)->getAngle(),tableauMesh->at(i)->getVecteurRotation());
		modelview=scale(modelview,vec3(tableauMesh->at(i)->getScaleX(),tableauMesh->at(i)->getScaleY(),tableauMesh->at(i)->getScaleZ()));
		
		tableauMesh->at(i)->afficher(projection,modelview);
		modelview=mv;
	}
}

vec3 conversionQuaternionEuler(quat quaternion)
{
	vec3 vecteur(0.0);
	float scale=sqrt(pow(quaternion.x,2)+pow(quaternion.y,2)+pow(quaternion.z,2));
	if(scale!=0)
	{
		vecteur.x=quaternion.x/scale;
		vecteur.y=quaternion.y/scale;
		vecteur.z=quaternion.z/scale;
	}
	else
	{
		vecteur.x=1.0;
		vecteur.y=1.0;
		vecteur.z=1.0;
	}
	

	return vecteur;
}

MapLoader::~MapLoader()
{
	delete doc;
	delete tableauMesh;
	delete tableauObjLoader;
}