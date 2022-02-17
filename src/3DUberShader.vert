#version 120
attribute vec3 Position;
attribute vec3 Normal;
attribute vec4 SourceColor;
attribute vec2 TexCoordIn;
attribute vec3 WorldPos;

varying vec3 lightIntensity;
varying vec4 DestinationColor;
varying vec2 TexCoordOut;

uniform vec4 lightPosition;

/****************************************************************
 *                  Lighting properties                         *
 ****************************************************************/
//Material properties
uniform vec3 Ka;  //Ambient reflectivity
uniform vec3 Kd;  //Diffuse reflectivity
uniform vec3 Ks;  //Specular reflectivity

//Light properties
uniform vec3 La;
uniform vec3 Ld;
uniform vec3 Ls;
uniform float shininess;

/****************************************************************
 *                  Matrices                                    *
 ****************************************************************/
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
    vec3 v = normalize(-eyeCoords.xyz);
    
    vec3 r = reflect( -s, tnorm );
    vec3 ambient = La * Ka;
    float sDotN = max( dot(s,tnorm), 0.0 );
    vec3 diffuse = Ld * Kd * sDotN;
    vec3 spec = vec3(0.0);
    
    if(sDotN > 0.0){
        spec = Ls * Ks * pow(max(dot(r,v), 0.0), shininess);
    }
    
    //lightIntensity = Ld * Kd * max(dot(s, tnorm), 0.0);
    lightIntensity = ambient + diffuse + spec;
    
    gl_Position = MVP * vec4(Position,1.0);
    TexCoordOut = TexCoordIn;
}