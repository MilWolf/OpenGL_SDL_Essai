#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Texture.h"
#include "TexMat.h"

using namespace glm;

class ItemHUD
{
public:
	ItemHUD(float *vertices,float *coordTexture,int nombreVertices,int nombreCoordonnees,int nombreTriangles,string tex,string const vertexShader, string const fragmentShader);
	~ItemHUD();

	void afficher(mat4 &projection, mat4 &modelview);
	void updateVBO(void *donnees, int tailleBytes, int decalage);
	void charger();
private:
	float *vertices;
	float *coordTexture;
	Texture *texture;
	Shader shader;
	GLuint vboID;
	GLuint vaoID;
	int tailleVerticesBytes;
	int tailleCoordonnesBytes;
	int nombreTriangles;

};

