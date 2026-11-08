#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D sceneTexture;
uniform sampler2D objectIdTexture;
uniform vec2 texelSize;

void main()
{
    vec3 sceneColor = texture(sceneTexture, TexCoord).rgb;
    float centerId = texture(objectIdTexture, TexCoord).r;
    bool edge = false;

    // Compara IDs vizinhos.
    if (centerId > 0.5) {
        for (int y = -1; y <= 1; ++y) {
            for (int x = -1; x <= 1; ++x) {
                if (x == 0 && y == 0) continue;

                vec2 offset = vec2(float(x), float(y)) * texelSize * 1.25;
                float neighborId = texture(objectIdTexture, TexCoord + offset).r;
                if (abs(neighborId - centerId) > 0.5) {
                    edge = true;
                }
            }
        }
    }

    // Contorno escuro
    vec3 outlineColor = vec3(0.025, 0.030, 0.040); 
    FragColor = vec4(edge ? outlineColor : sceneColor, 1.0);
}
