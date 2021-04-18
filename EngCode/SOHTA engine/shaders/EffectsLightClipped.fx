#define  numlights 10

//this shader struct has to be in the same order as the one in the engine code
struct Light
{
    float3 dir;
    float range;
    float3 pos;
    float cone;
    float3 att;
    float4 ambient;
    float4 diffuse;
};

cbuffer cbPerFrame
{
    Light light[numlights];
};

cbuffer cbPerObject
{
    float4x4 WVP;
    float4x4 World;
};

Texture2D ObjTexture;
SamplerState ObjSamplerState;

struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float4 worldPos : POSITION;
    float2 TexCoord : TEXCOORD;
    float3 normal : NORMAL;
};

VS_OUTPUT VS(float4 inPos : POSITION, float2 inTexCoord : TEXCOORD, float3 normal : NORMAL)
{
    VS_OUTPUT output;

    output.Pos = mul(inPos, WVP);
    
    output.worldPos = mul(inPos, World);
    output.normal = mul(normal, World);

    output.TexCoord = inTexCoord;

    return output;
}

float4 PS(VS_OUTPUT input) : SV_TARGET
{
    input.normal = normalize(input.normal);

    float4 diffuse = ObjTexture.Sample( ObjSamplerState, input.TexCoord ); 
   
    clip(diffuse.a - .15);

    float3 finalColor, finalColor2;
    finalColor = float3(0.0f, 0.0f, 0.0f);
    finalColor2 = float3(0.0f, 0.0f, 0.0f);

    int x = 0;
    int x2 = 1;

    //Create the vector between light position and pixels position
    float3 lightToPixelVec = light[x].pos - input.worldPos;
    float3 lightToPixelVec2 = light[x2].pos - input.worldPos;

    //Find the distance between the light pos and pixel pos
    float d = length(lightToPixelVec);
    float d2 = length(lightToPixelVec2);

    //Create the ambient light
    float3 finalAmbient = diffuse * light[x].ambient;
    float3 finalAmbient2 = diffuse * light[x2].ambient;

    //If pixel is too far, return pixel color with ambient light
    if (d > light[x].range)
    {
        if (d2 > light[x2].range)
        {
            return float4((finalAmbient2 + finalAmbient), diffuse.a);
        }
        else
        {
            lightToPixelVec2 /= d2;

            float howMuchLight2 = dot(lightToPixelVec2, input.normal);

            if (howMuchLight2 > 0.0f)
            {
                //Add light to the finalColor of the pixel
                finalColor2 += howMuchLight2 * diffuse * light[x2].diffuse;

                //Calculate Light's Falloff factor
                finalColor2 /= light[x2].att[0] + (light[x2].att[1] * d2) + (light[x2].att[2] * (d2 * d2));
            }

            finalColor2 = saturate(finalColor2 + finalAmbient2);

            return float4((finalColor2 + finalAmbient), diffuse.a);
        }   
    }
    else
    {
        //Turn lightToPixelVec into a unit length vector describing
        //the pixels direction from the lights position
        lightToPixelVec /= d;

        //Calculate how much light the pixel gets by the angle
        //in which the light strikes the pixels surface

        float howMuchLight = dot(lightToPixelVec, input.normal);


        //If light is striking the front side of the pixel
        if (howMuchLight > 0.0f)
        {
            //Add light to the finalColor of the pixel
            finalColor += howMuchLight * diffuse * light[x].diffuse;

            //Calculate Light's Falloff factor
            finalColor /= light[x].att[0] + (light[x].att[1] * d) + (light[x].att[2] * (d * d));
        }


        //make sure the values are between 1 and 0, and add the ambient
        finalColor = saturate(finalColor + finalAmbient);

        if (d2 > light[x2].range)
        {
            return float4((finalAmbient2 + finalColor), diffuse.a);
        }
        else
        {
            lightToPixelVec2 /= d2;

            float howMuchLight2 = dot(lightToPixelVec2, input.normal);

            if (howMuchLight2 > 0.0f)
            {
                //Add light to the finalColor of the pixel
                finalColor2 += howMuchLight2 * diffuse * light[x2].diffuse;

                //Calculate Light's Falloff factor
                finalColor2 /= light[x2].att[0] + (light[x2].att[1] * d2) + (light[x2].att[2] * (d2 * d2));
            }

            finalColor2 = saturate(finalColor2 + finalAmbient2);

            return float4(finalColor + finalColor2, diffuse.a);
        }
    }    

    return float4((finalAmbient2 + finalAmbient), diffuse.a);

}

float4 D2D_PS(VS_OUTPUT input) : SV_TARGET
{
    input.normal = normalize(input.normal);

    float4 diffuse = ObjTexture.Sample( ObjSamplerState, input.TexCoord );

    return diffuse;
}
