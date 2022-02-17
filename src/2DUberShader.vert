#version 120
attribute vec3 Position;
attribute vec4 SourceColor;
attribute vec3 Normal;
attribute vec2 TexCoordIn;
attribute vec3 WorldPos;

varying vec3 lightIntensity;
varying vec4 DestinationColor;
varying vec2 TexCoordOut;

uniform vec4 lightPosition;

uniform vec3 Kd;
uniform vec3 Ld;

uniform mat3 normalMatrix;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform mat4 modelViewMatrix;
uniform mat4 MVP;

uniform float red;
uniform float green;
uniform float blue;
uniform float alpha;

uniform vec3 cameraPosition;

uniform float lightColourR;
uniform float lightColourG;
uniform float lightColourB;
uniform float lightColourA;


void main(void) {
    
    
    DestinationColor = SourceColor;
    DestinationColor.x = red;
    DestinationColor.y = green;
    DestinationColor.z = blue;
    DestinationColor.w = alpha;
    
    
    //Convert position and normal to eyecoords
    vec3 tnorm = normalize(normalMatrix * Normal);
    vec4 eyeCoords = MVP * vec4(Position, 1.0);
    
    vec3 s = normalize(vec3(lightPosition - eyeCoords));
    
    lightIntensity = Ld * Kd * max(dot(s, tnorm), 0.0);
    
    gl_Position = MVP * vec4(Position,1.0);
    TexCoordOut = TexCoordIn;
}