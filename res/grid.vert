#version 330 core

layout (location = 0) in vec3 pos;

uniform mat4 Cam_Matrix;
out mat4 frag_Cam_Matrix;

out vec3 nearPoint;
out vec3 farPoint;

out mat4 mv_Mat;
out mat4 proj_Mat;

vec3 UnprojectPoint(float x, float y, float z) 
{
    vec4 unprojectedPoint =  inverse(Cam_Matrix) * vec4(x, y, z, 1.0);
    return unprojectedPoint.xyz / unprojectedPoint.w;
}

void main()
{
	vec3 p = pos;
	nearPoint = UnprojectPoint(p.x, p.y, 0.0).xyz;
	farPoint = UnprojectPoint(p.x, p.y, 1.0).xyz;

	gl_Position = vec4(p, 1.0);
	frag_Cam_Matrix = Cam_Matrix;
}