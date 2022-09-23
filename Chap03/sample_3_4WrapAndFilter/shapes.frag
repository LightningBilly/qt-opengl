#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCord;
uniform sampler2D textureWall;
uniform sampler2D textureSmile;
void main(){
    FragColor = texture(textureSmile, TexCord);
}
