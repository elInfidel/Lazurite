#version 410

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

in vec3 position[];
in float lifetime[];
in float lifespan[];

out vec4 Color;

uniform mat4 projectionView;
uniform mat4 cameraTransform;

uniform float sizeStart;
uniform float sizeEnd;

uniform vec4 colorStart;
uniform vec4 colorEnd;

void main()
{
	Color = mix(colorStart, colorEnd, lifetime[0] / lifespan[0]);
	
	float halfSize = mix(sizeStart, sizeEnd, lifetime[0]/lifespan[0]) * 0.5f;
	
	vec3 corners[4];
	corners[0] = vec3( halfSize, -halfSize, 0);
	corners[1] = vec3( halfSize, halfSize, 0);
	corners[2] = vec3( -halfSize, -halfSize, 0);
	corners[3] = vec3( -halfSize, halfSize, 0);

	vec3 zAxis = normalize(cameraTransform[3].xyz - position[0]);
	vec3 xAxis = cross(cameraTransform[1].xyz, zAxis);
	vec3 yAxis = cross(zAxis, xAxis);
	mat3 billboard = mat3(xAxis, yAxis, zAxis);
	
	gl_Position = projectionView * vec4(billboard * corners[0] + position[0], 1);
	EmitVertex();
	
	gl_Position = projectionView * vec4(billboard * corners[1] + position[0], 1);
	EmitVertex();
	
	gl_Position = projectionView * vec4(billboard * corners[2] + position[0], 1);
	EmitVertex();
	
	gl_Position = projectionView * vec4(billboard * corners[3] + position[0], 1);
	EmitVertex();
}