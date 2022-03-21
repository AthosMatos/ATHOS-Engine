#define numlights 100

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

float4 CheckDist(float4 diffuse, float3 finalColor, float distance, float3 lightToPixelVec, float3 finalAmbient, VS_OUTPUT input )
{
    for (int x = 0;; x++)
    {
        if (light[x].range)
        {
            float3 lightToPixelVec = light[x].pos - input.worldPos;
            float3 TempColor = float3(0.0f, 0.0f, 0.0f);
            float3 TempAmbient = diffuse * light[x].ambient;
            distance = length(lightToPixelVec);

            if (distance <= light[x].range)
            {
            //Turn lightToPixelVec into a unit length vector describing
            //the pixels direction from the lights position
                lightToPixelVec /= distance;

            //Calculate how much light the pixel gets by the angle
            //in which the light strikes the pixels surface

                float howMuchLight = dot(lightToPixelVec, input.normal);


            //If light is striking the front side of the pixel
                if (howMuchLight > 0.0f)
                {
            //Add light to the finalColor of the pixel
                    TempColor += howMuchLight * diffuse * light[x].diffuse;

            //Calculate Light's Falloff factor
                    TempColor /= light[x].att[0] + (light[x].att[1] * distance) + (light[x].att[2] * (distance * distance));
                }

            //make sure the values are between 1 and 0, and add the ambient
                TempColor = saturate(TempColor + TempAmbient);

                finalColor += TempColor;
            }
            else
            {
                finalAmbient += TempAmbient;
            }
        }
        else
        {
            break;
        }

    }
    return float4(finalColor + finalAmbient, diffuse.a);
}

float4 PS(VS_OUTPUT input) : SV_TARGET
{
    input.normal = normalize(input.normal);

    float4 diffuse = ObjTexture.Sample( ObjSamplerState, input.TexCoord ); 

    return CheckDist(diffuse, float3(0.0f, 0.0f, 0.0f), 0, 0, float3(0.0f, 0.0f, 0.0f), input);

}

float4 D2D_PS(VS_OUTPUT input) : SV_TARGET
{
    input.normal = normalize(input.normal);

    float4 diffuse = ObjTexture.Sample( ObjSamplerState, input.TexCoord );

    return diffuse;
}
