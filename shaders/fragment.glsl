#version 330 core

layout (location = 0) out vec4 FragColor;
layout (location = 1) out float ObjectId;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform vec3 objectColor;
uniform sampler2D rockTexture;
uniform float rockStrength;
uniform sampler2D woodTexture;
uniform float woodStrength;
uniform vec3 viewPos;
uniform vec3 lightDirection;       // direção da superfície até a luz
uniform float materialShininess;
uniform float specularStrength;
uniform int objectId;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightDirection);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    vec3 baseColor = objectColor;

    if (rockStrength > 0.0) {
        vec3 rockColor = texture(rockTexture, TexCoord).rgb;

        float grain = (rockColor.r + rockColor.g + rockColor.b) / 3.0;
        float brightness = mix(1.0, 0.5 + grain, rockStrength);

        baseColor = objectColor * brightness;
    }

    if (woodStrength > 0.0) {
        vec3 woodColor = texture(woodTexture, TexCoord).rgb;

        float grain = (woodColor.r + woodColor.g + woodColor.b) / 3.0;
        float brightness = mix(1.0, 0.5 + grain, woodStrength);

        baseColor = objectColor * brightness;
    }

    // Use the material color for ambient and diffuse lighting.
    vec3 ambient = 0.28 * baseColor;
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = 0.72 * diff * baseColor;
    
    float spec = 0.0;
    if (diff > 0.0) {
        spec = pow(max(dot(norm, halfwayDir), 0.0), materialShininess);
    }
    vec3 specular = specularStrength * spec * vec3(1.0);

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);

    // Todas as primitivas de uma mesma peça recebem o mesmo ID.
    // O pós-processamento usa isso para contornar a peça inteira, sem desenhar linhas internas/juntas.
    ObjectId = float(objectId);
}
