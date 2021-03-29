cbuffer CBuf
{
	matrix gWorldViewProj;	// the hlsl considers matrix as column majors
};

struct VS_VERTEX
{
	float4 pos : SV_POSITION;
	float4 col : COLOR;
};

VS_VERTEX VS(float3 pos : POSITION, float4 col : COLOR)
{
	VS_VERTEX outVertex;
	outVertex.pos = mul(float4(pos, 1.0f), gWorldViewProj);
	outVertex.col = col;
	return outVertex;
}

float4 PS(float4 pos : SV_POSITION, float4 color : COLOR) : SV_TARGET
{
	return color;
}

technique11 ColorTech
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}
}