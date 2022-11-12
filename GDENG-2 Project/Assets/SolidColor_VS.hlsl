struct VS_INPUT {
	float4 position : POSITION;
};

struct VS_OUTPUT {
	float4 position: SV_POSITION;
};

cbuffer constant: register(b0)
{
	row_major float4x4 model;
	row_major float4x4 viewProjection;
	float4 albedoColor;
};

VS_OUTPUT vsmain(VS_INPUT input)
{
	VS_OUTPUT output;

	output.position = input.position;
	output.position = mul(output.position, model);
	output.position = mul(output.position, viewProjection);
	
	return output;
}