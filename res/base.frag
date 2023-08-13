#version 330 core

out vec4 FragColor;
uniform sampler2D Test_Texture;
in vec2 UV;

void main()
{
	//FragColor = texture(Test_Texture, gl_FragCoord.xy);
	
	//FragColor = vec4(UV.xy, 0, 0);
	FragColor = texture(Test_Texture, UV);
	//FragColor = vec4(normalize(gl_FragCoord).xy, 0, 0);
}