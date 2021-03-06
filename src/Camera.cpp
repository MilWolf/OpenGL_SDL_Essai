#include "Camera.h"

Camera::Camera(): phi(0.0), theta(0.0), orientation(), axeVertical(0, 0, 1), deplacementLateral(), position(), pointCible()
{
}

Camera::Camera(vec3 position, vec3 pointCible, vec3 axeVertical) : phi(0.0), theta(0.0), orientation(), axeVertical(axeVertical),deplacementLateral(), position(position), pointCible(pointCible)
{
	setPointcible(pointCible);
}

void Camera::orienter(int xRel, int yRel)
{
    // Modification des angles
 
    phi += -yRel * 0.8;
	theta += -xRel * 0.8;

	
    if(phi > 89.0)
	{
		phi = 89.0;
	}
    else if(phi < -89.0)
	{
		phi = -89.0;
	}

	
	float phiRadian = phi * M_PI / 180;
	float thetaRadian = theta * M_PI / 180;

	if(axeVertical.x == 1.0)
	{
		// Calcul des coordonn�es sph�riques
 
		orientation.x = sin(phiRadian);
		orientation.y = cos(phiRadian) * cos(thetaRadian);
		orientation.z = cos(phiRadian) * sin(thetaRadian);
	}
 
 
	// Si c'est l'axe Y
 
	else if(axeVertical.y == 1.0)
	{
		// Calcul des coordonn�es sph�riques
 
		orientation.x = cos(phiRadian) * sin(thetaRadian);
		orientation.y = sin(phiRadian);
		orientation.z = cos(phiRadian) * cos(thetaRadian);
	}
 
 
	// Sinon c'est l'axe Z
 
	else
	{
		// Calcul des coordonn�es sph�riques
 
		orientation.x = cos(phiRadian) * cos(thetaRadian);
		orientation.y = cos(phiRadian) * sin(thetaRadian);
		orientation.z = sin(phiRadian);
	}

	deplacementLateral = cross(axeVertical, orientation);
    deplacementLateral = normalize(deplacementLateral);
 
 
    // Calcul du point cibl� pour OpenGL
 
    pointCible = position + orientation;
        
}

void Camera::deplacer(Input const &input, int fps)
{
	float coeffVitesse=15.0f;

	if(input.mouvementSouris())
	{
		orienter(input.getXRel(), input.getYRel());
	}
	if(input.getTouche(SDL_SCANCODE_LSHIFT))
	{
		coeffVitesse=25.0f;
	}
	if(input.getTouche(SDL_SCANCODE_W))
	{
		position = position + orientation * (coeffVitesse/fps);
		pointCible = position + orientation;
	}
	if(input.getTouche(SDL_SCANCODE_S))
	{
		position = position - orientation * (coeffVitesse/fps);
		pointCible = position + orientation;
	}
	if(input.getTouche(SDL_SCANCODE_A))
	{
		position = position + deplacementLateral * (coeffVitesse/fps);
		pointCible = position + orientation;
	}
	if(input.getTouche(SDL_SCANCODE_D))
	{
		position = position - deplacementLateral * (coeffVitesse/fps);
		pointCible = position + orientation;
        
	}
}

void Camera::lookAt(mat4 &modelview)
{
    // Actualisation de la vue dans la matrice
 
    modelview = glm::lookAt(position, pointCible, axeVertical);
}

void Camera::setPointcible(glm::vec3 pointCible)
{
    // Calcul du vecteur orientation
 
    orientation = pointCible - position;
    orientation = normalize(orientation);
 
 
    // Si l'axe vertical est l'axe X
 
    if(axeVertical.x == 1.0)
    {
        // Calcul des angles
 
        phi = asin(orientation.x);
        theta = acos(orientation.y / cos(phi));
 
        if(orientation.y < 0)
            theta *= -1;
    }
 
 
    // Si c'est l'axe Y
 
    else if(axeVertical.y == 1.0)
    {
        // Calcul des angles
 
        phi = asin(orientation.y);
        theta = acos(orientation.z / cos(phi));
 
        if(orientation.z < 0)
            theta *= -1;
    }
 
 
    // Sinon c'est l'axe Z
 
    else
    {
        // Calcul des angles
 
        phi = asin(orientation.x);
        theta = acos(orientation.z / cos(phi));
 
        if(orientation.z < 0)
            theta *= -1;
    }
 
 
    // Conversion en degr�s
 
    phi = phi * 180 / M_PI;
    theta = theta * 180 / M_PI;
}

Camera::~Camera()
{
}

vec3 Camera::getPosition()
{
	return this->position;
}
vec3 Camera::getPointCible()
{
	return this->pointCible;
}
vec3 Camera::getAxeVertical()
{
	return this->axeVertical;
}
vec3 Camera::getOrientation()
{
	return this->orientation;
}
float Camera::getPhi()
{
	return this->phi;
}
float Camera::getTheta()
{
	return this->theta;
}