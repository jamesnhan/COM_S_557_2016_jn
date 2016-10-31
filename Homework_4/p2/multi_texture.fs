#version 410 core                                                 

uniform sampler2D tex1; //this is the texture
uniform sampler2D tex2; //this is the texture
uniform sampler2D tex3; //this is the texture

in vec2 pass_TexCoord; //this is the texture coord
in vec4 pass_Color;

out vec4 color;

uniform int texture_blend;

void main(void)                                                   
{
    // This function finds the color component for each texture coordinate. 
    vec4 texColor1 =  texture(tex1, pass_TexCoord);
    vec4 texColor2 =  texture(tex2, pass_TexCoord);
    vec4 texColor3 =  texture(tex3, pass_TexCoord);
    
    // This mixes the background color with the texture color.
    // The GLSL shader code replaces the former envrionment. It is now up to us
    // to figure out how we like to blend a texture with the background color.
    if(texture_blend == 0)
    {
        color = 0.1 * pass_Color + texColor1 + texColor2 + texColor3 ;
    }
    else if(texture_blend == 1)
    {
        color = texColor1 * texColor2 * texColor3;
    }
    else if(texture_blend == 2)
    {
        color = 0.33 * texColor1 + 0.33 * texColor2 + 0.33 * texColor3;
    }
    else
    {
        color = 0.1 * pass_Color + 0.3 * texColor1 + 0.3 * texColor2 + 0.3 * texColor3;
    }
    
}