#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCord;
uniform sampler2D textureWall;
uniform sampler2D textureSmile;
void main(){
    // FragColor = vec4(ourColor, 1.0f);
    // FragColor = texture(textureWall, TexCord)*vec4(1.0, 1,0.5,0.2);
    FragColor = mix(texture(textureWall, TexCord),
                    texture(textureSmile, TexCord),0.5);
}
