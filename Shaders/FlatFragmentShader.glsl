#version 400

smooth in vec4 vertColour;

out vec4 outputColour;

void main()
{
	outputColour = vertColour;
	outputColour = vec4(1, 1, 1, 1);
}