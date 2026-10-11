#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;
uniform float time;

out vec4 finalColor;

void main()
{
    vec2 uv = fragTexCoord;

    float strength = mix(0.0, 0.05, 1.0 - uv.y);             // 1 at top, 0 at bottom
    float amplitude = 0.03 * strength;       // max wobble at the top

    uv.x += sin(uv.y * 100.0 + time * 1.0) * amplitude;

    vec4 texel = texture(texture0, uv);
    finalColor = texel * colDiffuse * fragColor;
}