// Version du GLSL

#version 150 core


in vec3 lightVec;
in vec3 eyeVec;
in vec2 coordTexture;

uniform sampler2D colorMap;
uniform sampler2D normalMap;
uniform float invRadius;

out vec4 out_Color;

void main (void)
{
	float distSqr = dot(lightVec, lightVec);
	float att = clamp(1.0 - invRadius * sqrt(distSqr), 0.0, 1.0);
	vec3 lVec = lightVec * inversesqrt(distSqr);

	vec3 vVec = normalize(eyeVec);
	
	vec4 base = texture2D(colorMap, coordTexture);
	
	vec3 bump = normalize( texture2D(normalMap, coordTexture).xyz * 2.0 - 1.0);

	vec4 vAmbient = gl_LightSource[0].ambient * gl_FrontMaterial.ambient;

	float diffuse = max( dot(lVec, bump), 0.0 );
	
	vec4 vDiffuse = gl_LightSource[0].diffuse * gl_FrontMaterial.diffuse * 
					diffuse;	

	float specular = pow(clamp(dot(reflect(-lVec, bump), vVec), 0.0, 1.0), 
	                 gl_FrontMaterial.shininess );
	
	vec4 vSpecular = gl_LightSource[0].specular * gl_FrontMaterial.specular * 
					 specular;	
	
	
	out_Color = ( vAmbient*base +  vDiffuse*base + vSpecular) * att;
}
