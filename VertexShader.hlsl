cbuffer CBuf
{
	matrix gWorldViewProj;	// the hlsl considers matrix as column majors
};

struct VS_VERTEX
{
	float4 pos : SV_POSITION;
	float4 col : COLOR;
};

VS_VERTEX main(float3 pos : POSITION, float4 col : COLOR)
{
	VS_VERTEX outVertex;
	outVertex.pos = mul(float4(pos, 1.0f), gWorldViewProj);
	outVertex.col = col;
	return outVertex;
}