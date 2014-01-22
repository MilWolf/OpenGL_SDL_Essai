#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL_image.h>
#include <string>
#include <glew.h>

using namespace std;

class Texture
{
	public:
		Texture(string fichierImage);
		~Texture();

		bool charger(bool mipmapping);

		string getFichierImage();
		GLuint getID() const;


		void setID(int id);
		void setFichierImage(const string &fichierImage);

	private:
		GLuint id;
		string fichierImage;
		SDL_Surface* inverserPixels(SDL_Surface *imageSource) const;
};

#endif