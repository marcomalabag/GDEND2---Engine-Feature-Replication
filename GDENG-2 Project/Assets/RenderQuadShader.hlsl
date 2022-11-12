struct VS_INPUT {
	float4 position : POSITION;
	float2 texCoord : TEXCOORD;
};

struct VS_OUTPUT {
	float4 position: SV_POSITION;
	float2 texCoord : TEXCOORD;
};

VS_OUTPUT vsmain(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	output.position = input.position;
	output.texCoord = input.texCoord;

	return output;
}

Texture2D t_Frame : register(t0);

SamplerState s_FrameSampler : register(s0);

struct PS_INPUT
{
	float4 position: SV_POSITION;
	float2 texCoord : TEXCOORD;
};

float4 psmain(PS_INPUT input) : SV_TARGET
{
	return t_Frame.Sample(s_FrameSampler, input.texCoord);
}