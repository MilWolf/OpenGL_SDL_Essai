#include "Mesh.h"

#ifndef BUFFER_OFFSET
 
    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
 
#endif

vec3 conversionQuaternionEuler(vec3 quaternion);

Mesh::Mesh(float *vertices,int nombreVertices,float *couleurs,int nombreCouleurs,float *coordTexture,int nombreCoordonnees,int nombreTriangles,bool mipmapping,vector<TexMat>* vecTexMat,string const vertexShader, string const fragmentShader): shader(vertexShader, fragmentShader), vboID(0), vaoID(0)
{
	this->vertices=vertices;
	this->couleurs=couleurs;
	this->coordTexture=coordTexture;
	this->nombreTriangles=nombreTriangles;
	this->vecTexMat=vecTexMat;
	this->mipmapping=mipmapping;
	bool shaderCharge=shader.charger();

	textures=new vector<Texture>();

	tailleVerticesBytes=nombreVertices*sizeof(float);
	tailleCouleursBytes=nombreCouleurs*sizeof(float);
	tailleCoordonnesBytes=nombreCoordonnees*sizeof(float);

	for(int i=0;i<vecTexMat->size();i++)
	{
		if(vecTexMat->at(i).texture!="")
		{
			Texture t("Textures/"+vecTexMat->at(i).texture);
			if(mipmapping)
			{
				t.charger(true);
			}
			else
			{
				t.charger(false);
			}
			
			textures->push_back(t);
		}
		
	}
	/*
	texture=new Texture("Textures/rouille.jpg");
	texture2=new Texture("Textures/rouille2.jpg");
    texture->charger();
	texture2->charger();
	*/
}

Mesh::Mesh(float *vertices,int nombreVertices,float *couleurs,int nombreCouleurs,float *coordTexture,int nombreCoordonnees,int nombreTriangles,bool mipmapping,vector<TexMat>* vecTexMat,vector<Texture> *textures,string const vertexShader, string const fragmentShader): shader(vertexShader, fragmentShader), vboID(0), vaoID(0)
{
	this->vertices=vertices;
	this->couleurs=couleurs;
	this->coordTexture=coordTexture;
	this->nombreTriangles=nombreTriangles;
	this->vecTexMat=vecTexMat;
	this->mipmapping=mipmapping;
	bool shaderCharge=shader.charger();

	tailleVerticesBytes=nombreVertices*sizeof(float);
	tailleCouleursBytes=nombreCouleurs*sizeof(float);
 	tailleCoordonnesBytes=nombreCoordonnees*sizeof(float);

	this->textures=textures;

}

void Mesh::afficher(mat4 &projection, mat4 &modelview)
{
	glUseProgram(shader.getProgramID());

			glBindVertexArray(vaoID);

				mat4 modelviewProjection = projection * modelview;
				glUniformMatrix4fv(glGetUniformLocation(shader.getProgramID(), "modelviewProjection"), 1, GL_FALSE, value_ptr(modelviewProjection));
				
				

				int j=0;
				for(int i=0;i<vecTexMat->size();i++)
				{
					if(vecTexMat->at(i).texture!="")
					{
						int t=textures->at(j).getID();
						glBindTexture(GL_TEXTURE_2D, t);
						if(mipmapping)
						{
							glGenerateMipmapEXT(GL_TEXTURE_2D);
						}
						
						j++;
					}
				
					if(i<vecTexMat->size()-1)
					{
						int nbTriangles=(vecTexMat->at(i+1).debut)-(vecTexMat->at(i).debut);
						glDrawArrays(GL_TRIANGLES, vecTexMat->at(i).debut, nbTriangles);
					}
					else if(i==vecTexMat->size()-1)
					{
						int nbTriangles=(nombreTriangles)-(vecTexMat->at(i).debut);
						glDrawArrays(GL_TRIANGLES, vecTexMat->at(i).debut, nbTriangles);
						j=0;
					}

					if(vecTexMat->at(i).texture!="")
					{
						glBindTexture(GL_TEXTURE_2D, 0);
					}


				
				}

			glBindVertexArray(0);

		glUseProgram(0);
}

void Mesh::charger()
{
	angle=2*acos(this->rotationW);
	angle=(angle*360)/(2*pi<float>());
	vecteurRotation=conversionQuaternionEuler(vec3(rotationX,rotationY,rotationZ));


	if(glIsBuffer(vboID) == GL_TRUE)
	{
		glDeleteBuffers(1, &vboID);
	}

	if(this->nom=="terrain2")
	{
		GLuint t0Location = glGetUniformLocation(shader.getProgramID(), "tex0");
		GLuint t1Location = glGetUniformLocation(shader.getProgramID(), "tex1");

		glUniform1i(t0Location, textures->at(0).getID());
		glUniform1i(t1Location, textures->at(1).getID());
	}
	
        
	//vbo
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

		//on alloue la mémoire à la carte graphique
		glBufferData(GL_ARRAY_BUFFER, tailleVerticesBytes + tailleCoordonnesBytes, 0, GL_STATIC_DRAW); 

		//on transfère les vertices à la carte graphique
		glBufferSubData(GL_ARRAY_BUFFER, 0, tailleVerticesBytes, vertices);

		//on transfère les couleurs à la carte graphique
        //glBufferSubData(GL_ARRAY_BUFFER, tailleVerticesBytes, tailleCouleursBytes, couleurs);

		//on transfère les coordonnées de texture à la carte graphique
		glBufferSubData(GL_ARRAY_BUFFER, tailleVerticesBytes, tailleCoordonnesBytes, coordTexture); 
		
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	if(glIsVertexArray(vaoID) == GL_TRUE)
        glDeleteVertexArrays(1, &vaoID);

	//vao
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);

				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
				glEnableVertexAttribArray(0);

				//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(tailleCouleursBytes));
				//glEnableVertexAttribArray(1);

				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(tailleVerticesBytes));
				glEnableVertexAttribArray(2);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glDisableVertexAttribArray(2);
	//glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
}

vec3 conversionQuaternionEuler(vec3 vecteurXYZ)
{
	vec3 vecteur(0.0);
	float scale=sqrt(pow(vecteurXYZ.x,2)+pow(vecteurXYZ.y,2)+pow(vecteurXYZ.z,2));
	if(scale!=0)
	{
		vecteur.x=vecteurXYZ.x/scale;
		vecteur.y=vecteurXYZ.y/scale;
		vecteur.z=vecteurXYZ.z/scale;
	}
	else
	{
		vecteur.x=1.0;
		vecteur.y=1.0;
		vecteur.z=1.0;
	}
	

	return vecteur;
}

void Mesh::updateVBO(void *donnees, int tailleBytes, int decalage)
{
    // Verrouillage du VBO

    glBindBuffer(GL_ARRAY_BUFFER, vboID);


        // Récupération de l'adresse du VBO

        void *adresseVBO = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);


        // Si l'adresse retournée est nulle alors on arrête le transfert

        if(adresseVBO == NULL)
        {
            std::cout << "Erreur au niveau de la récupération du VBO" << std::endl;
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            return;
        }


        // Mise à jour des données

        memcpy((char*)adresseVBO + decalage, donnees, tailleBytes);


        // Annulation du pointeur

        glUnmapBuffer(GL_ARRAY_BUFFER);
        adresseVBO = 0;


    // Déverrouillage du VBO

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Mesh::~Mesh()
{
	delete textures;
	delete vertices;
	delete couleurs;
	delete vecTexMat;

	glDeleteBuffers(1, &vboID);
	glDeleteVertexArrays(1, &vaoID);
}

void Mesh::setPositionX(float positionX)
{
	this->positionX=positionX;
}
void Mesh::setPositionY(float positionY)
{
	this->positionY=positionY;
}
void Mesh::setPositionZ(float positionZ)
{
	this->positionZ=positionZ;
}	
void Mesh::setRotationX(float rotationX)
{
	this->rotationX=rotationX;
}
void Mesh::setRotationY(float rotationY)
{
	this->rotationY=rotationY;
}
void Mesh::setRotationZ(float rotationZ)
{
	this->rotationZ=rotationZ;
}
void Mesh::setRotationW(float rotationW)
{
	this->rotationW=rotationW;
}
void Mesh::setScaleX(float scaleX)
{
	this->scaleX=scaleX;
}
void Mesh::setScaleY(float scaleY)
{
	this->scaleY=scaleY;
}
void Mesh::setScaleZ(float scaleZ)
{
	this->scaleZ=scaleZ;
}
void Mesh::setNom(string nom)
{
	this->nom=nom;
}

float Mesh::getPositionX()
{
	return this->positionX;
}
float Mesh::getPositionY()
{
	return this->positionY;
}
float Mesh::getPositionZ()
{
	return this->positionZ;
}		
float Mesh::getRotationX()
{
	return this->rotationX;
}
float Mesh::getRotationY()
{
	return this->rotationY;
}
float Mesh::getRotationZ()
{
	return this->rotationZ;
}
float Mesh::getRotationW()
{
	return this->rotationW;
}
float Mesh::getScaleX()
{
	return this->scaleX;
}
float Mesh::getScaleY()
{
	return this->scaleY;
}
float Mesh::getScaleZ()
{
	return this->scaleZ;
}
vec3 Mesh::getVecteurRotation()
{
	return this->vecteurRotation;
}
float Mesh::getAngle()
{
	return this->angle;
}
string Mesh::getNom()
{
	return this->nom;
}

vector<Texture>*  Mesh::getTextures()
{
	return this->textures;
}