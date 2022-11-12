struct VS_INPUT
{
	float4 position : POSITION;
	float4 color : COLOR;
};

struct VS_OUTPUT
{
	float4 position: SV_POSITION;
	float4 color : COLOR;
};

VS_OUTPUT vsmain(VS_INPUT input)
{
	VS_OUTPUT output;
	output.position = input.position;
	output.color = input.color;
	return output;
}

struct PS_INPUT
{
	float4 position: SV_POSITION;
	float4 color : COLOR;
};

float4 psmain(PS_INPUT input) : SV_TARGET
{
	return float4(input.color.x, input.color.y, 0.0f, 1.0f);
}