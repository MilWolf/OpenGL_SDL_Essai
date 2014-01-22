// Version du GLSL

#version 150 core


// Entrée

in vec2 coordTexture;


// Uniform

uniform sampler2D texColor;
uniform sampler2D texNormal;

// Sortie 

out vec4 out_Color;


// Fonction main

void main()
{
    // Couleur du pixel

	vec4 couleur=texture(texColor, coordTexture);
	if (couleur.a == 0) 
	discard;
	//couleur.x=1-couleur.x;
	//couleur.y=1-couleur.y;
	//couleur.z=1-couleur.z;
    out_Color = couleur;
}
