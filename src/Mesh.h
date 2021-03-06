#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <vector>

#include "Shader.h"
#include "Texture.h"
#include "TexMat.h"

using namespace glm;
using namespace std;

class Mesh
{
	public:
		Mesh(float *vertices,int nombreVertices,float *couleurs,int nombreCouleurs,float *coordTexture,int nombreCoordonnees,int nombreTriangles,bool mipmapping,vector<TexMat>* vecTexMat,string const vertexShader, string const fragmentShader);
		Mesh(float *vertices,int nombreVertices,float *couleurs,int nombreCouleurs,float *coordTexture,int nombreCoordonnees,int nombreTriangles,bool mipmapping,vector<TexMat>* vecTexMat,vector<Texture> *textures,string const vertexShader, string const fragmentShader);
		~Mesh();

		void afficher(mat4 &projection, mat4 &modelview);
		void updateVBO(void *donnees, int tailleBytes, int decalage);
		void charger();
		
		
		void setPositionX(float);
		void setPositionY(float);
		void setPositionZ(float);
		
		void setRotationX(float);
		void setRotationY(float);
		void setRotationZ(float);
		void setRotationW(float);

		void setScaleX(float);
		void setScaleY(float);
		void setScaleZ(float);

		void setNom(string);

		float getPositionX();
		float getPositionY();
		float getPositionZ();
		
		float getRotationX();
		float getRotationY();
		float getRotationZ();
		float getRotationW();

		float getScaleX();
		float getScaleY();
		float getScaleZ();

		vec3 getVecteurRotation();
		float getAngle();

		string getNom();

		vector<Texture>* getTextures();

	private:
		float *vertices;
		float *couleurs;
		float *coordTexture;

		int nombreTriangles;
		vector<TexMat> *vecTexMat;

		Shader shader;
		vector<Texture> *textures;
		Texture *texture;
		Texture *texture2;
		bool possedeTexture;
		bool mipmapping;
		GLuint vboID;

		int tailleVerticesBytes;
		int tailleCouleursBytes;
		int tailleCoordonnesBytes;

		GLuint vaoID;

		float positionX;
		float positionY;
		float positionZ;
		
		float rotationX;
		float rotationY;
		float rotationZ;
		float rotationW;

		float scaleX;
		float scaleY;
		float scaleZ;

		float angle;
		vec3 vecteurRotation;

		string nom;
};

