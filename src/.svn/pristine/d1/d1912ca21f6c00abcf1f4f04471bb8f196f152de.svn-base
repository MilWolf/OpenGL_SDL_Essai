#include "Input.h"

Input::Input(): x(0), y(0), xRel(0), yRel(0), terminer(false)
{ 
    for(int i(0); i < SDL_NUM_SCANCODES; i++)
	{
		touches[i] = false;
	}
 
    for(int i(0); i < 8; i++)
	{
		boutonsSouris[i] = false;
	}
        
}

void Input::updateEvenements()
{
	xRel = 0;
    yRel = 0;

    while(SDL_PollEvent(&evenements))
    {
		switch(evenements.type)
		{ 
			case SDL_KEYDOWN:
				touches[evenements.key.keysym.scancode] = true;
				break;

			case SDL_KEYUP:
				touches[evenements.key.keysym.scancode] = false;
				break;

			case SDL_MOUSEBUTTONDOWN:
                boutonsSouris[evenements.button.button] = true;
				break;
 
            case SDL_MOUSEBUTTONUP:
                boutonsSouris[evenements.button.button] = false;
				break;
 
            case SDL_MOUSEMOTION:
                x = evenements.motion.x;
                y = evenements.motion.y;
 
                xRel = evenements.motion.xrel;
                yRel = evenements.motion.yrel;
				break;
 
            case SDL_WINDOWEVENT:
                if(evenements.window.event == SDL_WINDOWEVENT_CLOSE)
				{
					terminer = true;
				}
				break;
 
			default:
				break;
		}
    }
}

void Input::afficherPointeur(bool reponse) const
{
    if(reponse)
        SDL_ShowCursor(SDL_ENABLE);
 
    else
        SDL_ShowCursor(SDL_DISABLE);
}

void Input::capturerPointeur(bool reponse) const
{
    if(reponse)
        SDL_SetRelativeMouseMode(SDL_TRUE);
 
    else
        SDL_SetRelativeMouseMode(SDL_FALSE);
}

bool Input::finish()
{
    return terminer;
}

bool Input::getTouche(const SDL_Scancode touche) const
{
    return touches[touche];
}

bool Input::getBoutonSouris(const Uint8 bouton) const
{
    return boutonsSouris[bouton];
}

bool Input::mouvementSouris() const
{
    if(xRel == 0 && yRel == 0)
        return false;
 
    else
        return true;
}

int Input::getX() const
{
    return x;
}
 
int Input::getY() const
{
    return y;
}
 
int Input::getXRel() const
{
    return xRel;
}
 
int Input::getYRel() const
{
    return yRel;
}

void Input::setTerminer(bool terminer)
{
	this->terminer=terminer;
}

Input::~Input()
{
}