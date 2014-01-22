#include "Texture.h"

Texture::Texture(string fichierImage)
{
	this->id=0;
	this->fichierImage=fichierImage;
}

Texture::~Texture()
{
}

bool Texture::charger(bool mipmapping)
{

	SDL_Surface *imageSDL = IMG_Load(fichierImage.c_str());

	if(imageSDL == 0)
	{
		return false;
    }

	SDL_Surface *imageInversee = inverserPixels(imageSDL);

	glGenTextures(1, &id);

	glBindTexture(GL_TEXTURE_2D, id);

	GLenum formatInterne(0);
	GLenum format(0);
 
	if(imageInversee->format->BytesPerPixel == 3)
	{
		formatInterne = GL_RGB;

		if(imageInversee->format->Rmask == 0xff)
		{
			format = GL_RGB;
		}
 
		else
		{
			format = GL_BGR;
		}
	}
 
	else if(imageInversee->format->BytesPerPixel == 4)
	{    
		formatInterne = GL_RGBA;

		if(imageInversee->format->Rmask == 0xff)
		{
			format = GL_RGBA;
		}
 
		else
		{
			format = GL_BGRA;
		}
	}
	else
	{
		return false;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, formatInterne, imageInversee->w, imageInversee->h, 0, format, GL_UNSIGNED_BYTE, imageInversee->pixels);

	if(mipmapping)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  
    glBindTexture(GL_TEXTURE_2D, 0);

	SDL_FreeSurface(imageInversee);

	return true;
}

SDL_Surface* Texture::inverserPixels(SDL_Surface *imageSource) const
{
    // Copie conforme de l'image source sans les pixels
 
    SDL_Surface *imageInversee = SDL_CreateRGBSurface(0, imageSource->w, imageSource->h, imageSource->format->BitsPerPixel, imageSource->format->Rmask, 
                                                         imageSource->format->Gmask, imageSource->format->Bmask, imageSource->format->Amask);
 
 
    // Tableau intermédiaires permettant de manipuler les pixels
 
    unsigned char* pixelsSources = (unsigned char*) imageSource->pixels;
    unsigned char* pixelsInverses = (unsigned char*) imageInversee->pixels;
 
 
    // Inversion des pixels
 
    for(int i = 0; i < imageSource->h; i++)
    {
        for(int j = 0; j < imageSource->w * imageSource->format->BytesPerPixel; j++)
		{
			pixelsInverses[(imageSource->w * imageSource->format->BytesPerPixel * (imageSource->h - 1 - i)) + j] = pixelsSources[(imageSource->w * imageSource->format->BytesPerPixel * i) + j];
		}
            
    }
 
 
    // Retour de l'image inversée
 
    return imageInversee;
}

GLuint Texture::getID() const
{
    return this->id;
}
 
void Texture::setID(int id)
{
	this->id=id;
}
 
void Texture::setFichierImage(const std::string &fichierImage)
{
    this->fichierImage = fichierImage;
}

string Texture::getFichierImage()
{
	return this->fichierImage;
}
