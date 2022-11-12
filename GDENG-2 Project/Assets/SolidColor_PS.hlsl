struct PS_INPUT
{
	float4 position: SV_POSITION;
};

cbuffer constant: register(b0)
{
	row_major float4x4 model;
	row_major float4x4 viewProjection;
	float4 albedoColor;
};

float4 psmain(PS_INPUT input) : SV_TARGET
{
	return albedoColor;
}