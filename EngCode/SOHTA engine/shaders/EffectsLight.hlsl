#define numlights 100

//this shader struct has to be in the same order as the one in the engine code
struct Light
{
    float3 pos;
    float range;
    float3 dir;
    float cone;
    float3 att;
    float specularPower;
    float4 ambient;
    float4 diffuse;
    float4 specular;
};

cbuffer cbPerFrame
{
    Light light[numlights];
};

cbuffer cbPerObject
{
    float4x4 WVP;
    float4x4 World;
    float3 cameraPosition;
    
    float4 difColor;
    bool hasTexture;
};

Texture2D ObjTexture;
SamplerState ObjSamplerState;

struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float4 worldPos : POSITION;
    float2 TexCoord : TEXCOORD;
    float3 normal : NORMAL;
    float3 viewDirection : TEXCOORD1;
};

VS_OUTPUT VS(float4 inPos : POSITION, float2 inTexCoord : TEXCOORD, float3 normal : NORMAL)
{
    float4 worldPosition;
    VS_OUTPUT output;

    output.Pos = mul(inPos, WVP);
    
    output.worldPos = mul(inPos, World);
    output.normal = mul(normal, World);

    output.TexCoord = inTexCoord;

    // Calculate the position of the vertex in the world.
    worldPosition = mul(inPos, World);

    // Determine the viewing direction based on the position of the camera and the position of the vertex in the world.
    output.viewDirection = cameraPosition.xyz - worldPosition.xyz;
	
    // Normalize the viewing direction vector.
    output.viewDirection = normalize(output.viewDirection);
    
    return output;
}

float4 CheckDist(float4 TexColor, VS_OUTPUT input)
{
    float3 finalColor = float3(0.0f, 0.0f, 0.0f);
    float distance = 0;
    float3 finalAmbient = float3(0.0f, 0.0f, 0.0f);
    float3 finalSpecular = float3(0.0f, 0.0f, 0.0f);
    
    for (int x = 0;; x++)
    {
        if (light[x].range)
        {
            float3 lightToPixelVec = light[x].pos - input.worldPos;
            float3 TempColor = float3(0.0f, 0.0f, 0.0f);
            float3 TempSpecular = float3(0.0f, 0.0f, 0.0f);
            float3 TempAmbient = TexColor * light[x].ambient;
            distance = length(lightToPixelVec);

            if (distance <= light[x].range)
            {
            //Turn lightToPixelVec into a unit length vector describing
            //the pixels direction from the lights position
                lightToPixelVec /= distance;

            //Calculate how much light the pixel gets by the angle
            //in which the light strikes the pixels surface

                float howMuchLight = dot(lightToPixelVec, input.normal);
                float3 reflection = normalize(2 * howMuchLight * input.normal - (-lightToPixelVec));
                
            //If light is striking the front side of the pixel
                if (howMuchLight > 0.0f)
                {
                    // Calculate the reflection vector based on the light intensity, normal vector, and light direction.
                    TempSpecular += light[x].specular * pow(saturate(dot(reflection, input.viewDirection)), light[x].specularPower);
                    
                    //Add light to the finalColor of the pixel
                    TempColor += howMuchLight * TexColor * light[x].diffuse;

                    //Calculate Light's Falloff factor
                    TempColor /= light[x].att[0] + (light[x].att[1] * distance) + (light[x].att[2] * (distance * distance));
                    
                    TempSpecular /= light[x].att[0] + (light[x].att[1] * distance) + (light[x].att[2] * (distance * distance));
                }

            //make sure the values are between 1 and 0, and add the ambient
                TempColor = saturate(TempColor + TempAmbient);
                TempSpecular = saturate(TempSpecular + TempAmbient);
          
                finalSpecular += TempSpecular;
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
    return float4(finalColor + finalAmbient + finalSpecular, TexColor.a);
 
}

float4 PS(VS_OUTPUT input) : SV_TARGET
{
    input.normal = normalize(input.normal);

    //Set diffuse color of material
    float4 TexColor = difColor;

    //If material has a diffuse texture map, set it now
    if (hasTexture == true)
        TexColor = ObjTexture.Sample(ObjSamplerState, input.TexCoord);
    
    TexColor = ObjTexture.Sample(ObjSamplerState, input.TexCoord);
    
    return CheckDist(TexColor, input);

}

float4 D2D_PS(VS_OUTPUT input) : SV_TARGET
{
    input.normal = normalize(input.normal);

    float4 diffuse = ObjTexture.Sample( ObjSamplerState, input.TexCoord );

    return diffuse;
}
