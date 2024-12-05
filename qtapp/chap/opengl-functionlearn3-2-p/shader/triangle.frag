#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in vec4 vertexColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    FragColor = texture(texture1, texCoord)*vertexColor;
    // FragColor = vec4(1,0,0,1);
}
