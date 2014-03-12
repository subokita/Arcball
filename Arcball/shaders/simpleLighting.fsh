#version 410 core

out vec3 color;

in vec3 position_w;
in vec3 normal_c;
in vec3 eye_direction_c;
in vec3 light_direction_c;

uniform vec3 light_color;
uniform vec3 light_position_w;

void main() {
    float light_power = 180.0f;
    
    vec3 material_diffuse  = vec3( 0.2 );
    vec3 material_ambient  = vec3( 0.12 ) * material_diffuse;
    vec3 material_specular = vec3( 0.3 );
    
    float dist  = length( light_position_w - position_w );
    
    /* Angle of incidence (between normal and light direction) */
    vec3 n      = normalize( normal_c );
    vec3 l      = normalize( light_direction_c );
    float cos_theta = clamp( dot( n, l ), 0, 1 );
    
    /* Amount of light reflected to camera / eye */
    vec3 e          = normalize( eye_direction_c );
    vec3 r          = reflect( -l, n );
    float cos_alpha = clamp( dot( e, r ), 0, 1 );
    
    color.rgb = material_ambient;
    color.rgb += material_diffuse  * light_color * light_power * cos_theta / (dist * dist);
    color.rgb += material_specular * light_color * light_power * pow( cos_alpha , 5 ) / (dist * dist);
    
    
    
    
}