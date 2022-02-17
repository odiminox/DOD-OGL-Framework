#version 120

varying vec4 DestinationColor;
varying vec2 TexCoordOut;

varying vec3 lightIntensity;

uniform sampler2D Texture;

void main(void) {
    

    
    vec4 diffuse = texture2D(Texture, TexCoordOut);
    //vec3 incident = normalize();
    
    //gl_FragColor = DestinationColor * texture2D(Texture, TexCoordOut);
    
    gl_FragColor = DestinationColor * texture2D(Texture, TexCoordOut)*vec4(lightIntensity, 1.0);
    
    //gl_FragColor  = vec4(lightIntensity, 1.0);
}