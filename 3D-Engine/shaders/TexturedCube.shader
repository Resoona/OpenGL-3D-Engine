#shader vertex
#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec4 color;

uniform mat4 VP;
uniform mat4 M;

out DATA
{
	vec4 position;
vec4 color;
vec2 UV;

} vs_out;

void main()
{
	gl_Position = VP * M * vec4(vertexPosition_modelspace, 1);
	vs_out.position = gl_Position;
	vs_out.color = color;
	vs_out.UV = vertexUV;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 colour;
uniform vec2 light_pos;
uniform sampler2D myTextureSampler;

in DATA
{
	vec4 position;
	vec4 color;
	vec2 UV;

} fs_in;

void main()
{
	float intensity = 1.0 / length(fs_in.position.xy - light_pos);
	color = (texture(myTextureSampler, fs_in.UV).rgba + fs_in.color);// *intensity;
}