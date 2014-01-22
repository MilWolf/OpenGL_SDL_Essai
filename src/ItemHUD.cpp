#include "ItemHUD.h"

#ifndef BUFFER_OFFSET
 
    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
 
#endif

ItemHUD::ItemHUD(float *vertices,float *coordTexture,int nombreVertices,int nombreCoordonnees,int nombreTriangles,string tex,string const vertexShader, string const fragmentShader): shader(vertexShader, fragmentShader), vboID(0), vaoID(0)
{
	this->vertices=vertices;
	this->coordTexture=coordTexture;
	this->nombreTriangles=nombreTriangles;

	tailleVerticesBytes=nombreVertices*sizeof(float);
	tailleCoordonnesBytes=nombreCoordonnees*sizeof(float);

	bool shaderCharge=shader.charger();

	texture=new Texture("Textures/"+tex);
	if(!texture->charger(false))
	{
		cout<<"La texture "<<tex<<"ne peut pas etre chargee"<<endl;
	}
}

ItemHUD::~ItemHUD()
{
	delete vertices;
	delete coordTexture;

	glDeleteBuffers(1, &vboID);
	glDeleteVertexArrays(1, &vaoID);
}

void ItemHUD::charger()
{
	if(glIsBuffer(vboID) == GL_TRUE)
	{
		glDeleteBuffers(1, &vboID);
	}
	
	//vbo
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

		//allocation de la mémoire dans la carte graphique
		glBufferData(GL_ARRAY_BUFFER, tailleVerticesBytes+tailleCoordonnesBytes, 0, GL_STATIC_DRAW); 

		//envoi des données de vertices dans la carte graphique
		glBufferSubData(GL_ARRAY_BUFFER, 0, tailleVerticesBytes, vertices); 
        //glBufferSubData(GL_ARRAY_BUFFER, tailleVerticesBytes, tailleCouleursBytes, couleurs);

		//envoi des coordonnées de texture dans la carte graphique
		glBufferSubData(GL_ARRAY_BUFFER, tailleVerticesBytes, tailleCoordonnesBytes, coordTexture); 
		
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	if(glIsVertexArray(vaoID) == GL_TRUE)
        glDeleteVertexArrays(1, &vaoID);

	//vao
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);

				glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
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
	//float vertices[] = {-0.5, -0.5,   0.0, 0.5,   0.5, -0.5};

	//Texture t("Textures/"+texture);
	//t.charger();
}

void ItemHUD::afficher(mat4 &projection, mat4 &modelview)
{
	glDisable(GL_DEPTH_TEST);

	glUseProgram(shader.getProgramID());

		glBindVertexArray(vaoID);

			mat4 modelviewProjection = projection ;
			glUniformMatrix4fv(glGetUniformLocation(shader.getProgramID(), "modelviewProjection"), 1, GL_FALSE, value_ptr(modelviewProjection));

				glBindTexture(GL_TEXTURE_2D, texture->getID());

					glDrawArrays(GL_TRIANGLES, 0, nombreTriangles);

				glBindTexture(GL_TEXTURE_2D, 0);

		glBindVertexArray(0);

	glUseProgram(0);

	glEnable(GL_DEPTH_TEST);

	
	/*
	glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	projection=ortho(0.0, (double) largeurFenetre / hauteurFenetre, 0.0, 10000.0);
	glMatrixMode(GL_MODELVIEW);
  
	/* etape 4 */
	//glPushMatrix();
	/*
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glEnableVertexAttribArray(0);
 
 
	// On affiche le triangle
 
	glDrawArrays(GL_TRIANGLES, 0, 3);
 
 
	// On désactive le tableau Vertex Attrib puisque l'on n'en a plus besoin
 
	glDisableVertexAttribArray(0);
	
	//glPopMatrix();
	*/
}