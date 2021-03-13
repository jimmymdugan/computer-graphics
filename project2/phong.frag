#version 120

//
// Fragment shader for PHONG shading.
//
// @author  RIT CS Department
// @author  Jimmy Dugan
//

// Light position
varying vec3 lPos;

// Vertex position (in clip space)
varying vec3 vPos;

// Vertex normal
varying vec3 vNorm;

// Light color
uniform vec4 lightColor;
uniform vec4 ambientLight;

// Material properties
uniform vec4 diffuseColor;
uniform vec4 ambientColor;
uniform vec4 specularColor;
uniform float specExp;
uniform vec3 kCoeff;

void main()
{
    vec3 L = normalize( lPos - vPos );
    vec3 N = normalize( vNorm );
    vec3 R = normalize( reflect(-L, N) );
    vec3 V = normalize( -(vPos) );

    vec4 ambient  = vec4(0.0);  
    vec4 diffuse  = vec4(0.0);  
    vec4 specular = vec4(0.0);  
    float specDot;  

    ambient  = ambientLight * ambientColor * max(dot(N,L),0.0);
    diffuse  = lightColor * diffuseColor;
    specDot  = pow( max(dot(R,V),0.0), specExp );
    specular = lightColor * specularColor * specDot;

    gl_FragColor = (kCoeff.x * ambient) + (kCoeff.y * diffuse) + (kCoeff.z * specular);
}
