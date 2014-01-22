// Version du GLSL

#version 150 core

in vec2 in_TexCoord0;

in vec3 lightVec; 
in vec3 eyeVec;
out vec2 texCoord;
in vec3 vTangent; 
					 

void main(void)
{
	gl_Position = modelviewProjection * vec4(in_Vertex, 1.0);
	texCoord = in_TexCoord0;
	
	vec3 n = normalize(gl_NormalMatrix * gl_Normal);
	vec3 t = normalize(gl_NormalMatrix * vTangent);
	vec3 b = cross(n, t);
	
	vec3 vVertex = vec3(gl_ModelViewMatrix * gl_Vertex);
	vec3 tmpVec = gl_LightSource[0].position.xyz - vVertex;

	lightVec.x = dot(tmpVec, t);
	lightVec.y = dot(tmpVec, b);
	lightVec.z = dot(tmpVec, n);

	tmpVec = -vVertex;
	eyeVec.x = dot(tmpVec, t);
	eyeVec.y = dot(tmpVec, b);
	eyeVec.z = dot(tmpVec, n);
	
}
