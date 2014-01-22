// Version du GLSL

#version 150 core


// Entrée

in vec2 coordTexture0;
in vec2 coordTexture1;


// Uniform

uniform sampler2D tex0;
uniform sampler2D tex1;

// Sortie 

out vec4 out_Color;


// Fonction main

void main()
{
    // Couleur du pixel

	vec4 couleur=texture2D(tex0, coordTexture0);
	couleur *= texture2D(tex1, coordTexture1);
	
    out_Color = couleur;
}
