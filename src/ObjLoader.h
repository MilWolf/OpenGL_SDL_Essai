#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "Material.h"
#include "TexMat.h"

using namespace std;

class ObjLoader
{
	public:
		ObjLoader(string modele);
		~ObjLoader();


		float* getTableauVertices();
		float* getTableauCouleurs();
		float* getTableauCoordTexture();
		int getNombreTriangles();
		int getNombreVertices();
		int getNombreCouleurs();
		int getNombreCoordonnees();
		vector<TexMat>* getTexMat();
		string nom;

	private:
		FILE *fichier;
		
		vector<TexMat> *vecTexMat;
		vector <int> *separateurs;
		vector<double*> *listeSommets;
		vector<float*> *listeCoordonneesTexture;
		double *coordonneesSommet;
		float *coordonneesTexture;
		void lireObj();
		float* tableauVertices;
		float* tableauCouleurs;
		float* tabCouleurDiffuse;
		float* tabCoordonneesTexture;
		vector<float> *vectorVertices;
		vector<Material> *vectorMaterials;
		vector<float> *vectorFloatMaterials;
		vector<float> *vectorCoordonneesTexture;
		int nombreTriangles;
		bool objetTexture;
		int nombreVertices;
		int nombreCouleurs;
		int nombreCoordonnes;
};

