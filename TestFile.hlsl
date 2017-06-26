
float4x4 WVPMat;

struct VS_OUTPUT {
float4 pos : POSITION;
float2 tex : TEXCOORD0;
};

struct VS_INPUT {
float4 pos : POSITION0;
float2 tex : TEXCOORD0;
};

VS_OUTPUT VS_Main(VS_INPUT In)
{
VS_OUTPUT Out = (VS_OUTPUT)0;

float4 clipPos = mul(WVPMat,In.pos);
Out.pos = clipPos;
Out.tex = In.tex;

return Out;
}


texture NanoTex;

sampler SamplerNano = sampler_state
{
Texture = NanoTex;
AddressU = WRAP;
AddressV = WRAP;
AddressW = WRAP;
MipFilter = NONE;
MinFilter = NONE;
MagFilter = NONE;
};

struct PS_OUTPUT {
float4 col : COLOR;
};

struct PS_INPUT {
float4 pos : POSITION;
float2 tex : TEXCOORD0;
};

PS_OUTPUT PS_Main(PS_INPUT In) : COLOR
{
PS_OUTPUT Out = (PS_OUTPUT)0;

float4 Nano = tex2D(SamplerNano, In.tex);
Out.col = Nano.rgba;

return Out;
}

technique DefaultTech 
{
pass P0
{
AlphaBlendEnable = True;
DestBlend = InvSrcAlpha;
FillMode = WireFrame;
ZEnable = True;
 VertexShader = compile vs_2_0 VS_Main();
 PixelShader = compile ps_2_0 PS_Main();
}
}
