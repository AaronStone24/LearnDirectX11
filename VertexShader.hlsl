cbuffer CBuf
{
	matrix transform;	// the hlsl considers matrix as column majors
};

float4 main(float3 pos : POSITION) : SV_Position
{
	return mul(float4(pos, 1.0f), transform);
}