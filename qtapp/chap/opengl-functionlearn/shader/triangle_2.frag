#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(0.1f, 1.0f, 0.2f, 1.0f); // 要用浮点，不能整数
}
