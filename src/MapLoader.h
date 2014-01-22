#include <tinyxml2\tinyxml2.h>
#include <string>
#include <vector>

#include "ObjLoader.h"
#include "Mesh.h"

using namespace tinyxml2;
using namespace std;

class MapLoader
{
public:
	MapLoader(string map);
	~MapLoader();
	void initialiser();
	void charger();
	void afficher(mat4 &projection, mat4 &modelview);

private:
	XMLDocument *doc;
	vector<Mesh*> *tableauMesh;
	vector<ObjLoader*> *tableauObjLoader;
	Mesh *mesh;
	ObjLoader *objLoader;
};

