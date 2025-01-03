#version 330 core
out vec4 FragColor;
in vec2 TexCord;
uniform sampler2D textureWall;
uniform sampler2D textureSmile;
uniform float ratio;
void main(){
    FragColor = mix(texture(textureWall, TexCord),
                    texture(textureSmile, TexCord), ratio);
}
