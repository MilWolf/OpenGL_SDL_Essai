#include <string>

using namespace std;

class Material
{
	public:
		Material();
		Material(string nom);
		Material(string nom,string texture,float couleurAmbiante[3],float couleurDiffuse[3],float couleurSpeculaire[3],double dureteSpeculaire,double indiceRefraction,double opacite);
		~Material();

		string getNom();
		string getTexture();
		float* getCouleurAmbiante();
		float* getCouleurDiffuse();
		float* getCouleurSpeculaire();
		double getDureteSpeculaire();
		double getIndiceRefraction();
		double getOpacite();
		bool getMipmap();

		void setNom(string);
		void setTexture(string texture);
		void setCouleurAmbiante(float couleurAmbiante[3]);
		void setCouleurDiffuse(float couleurDiffuse[3]);
		void setCouleurSpeculaire(float couleurSpeculaire[3]);
		void setDureteSpeculaire(double dureteSpeculaire);
		void setIndiceRefraction(double indiceRefraction);
		void setOpacite(double opacite);
		void setMipmap(bool mipmap);

	private:
		string nom;
		string texture;
		float couleurAmbiante[3];
		float* couleurDiffuse;
		float couleurSpeculaire[3];

		double dureteSpeculaire; //varie de 0 à 1000
		double indiceRefraction;
		double opacite;

		bool mipmap;
};

