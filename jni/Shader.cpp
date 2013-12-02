#include <Shader.h>

#include <stdlib.h>
GLuint Shader::loadShader(GLenum shaderType, const char* pSource) {
    GLuint shader = glCreateShader(shaderType);
    if (shader) {
        glShaderSource(shader, 1, &pSource, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen) {
                char* buf = (char*) malloc(infoLen);
                if (buf) {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    LOGE("Could not compile shader %d:\n%s\n",
                            shaderType, buf);
                     
                         
                    free(buf);
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
} 

Shader::Shader()
{
	//write a parser for these and store as text files!
	static const char gVertexShader[] =
    "attribute vec3 vPosition;\n"
	"attribute vec2 vUv;\n"
	"uniform mat4	modelViewProj;\n"
//	"uniform mat4 Scale;\n"
//	"uniform mat4 Rotation;\n"
//	"uniform mat4 View;\n"
//	"uniform mat4 matProjection;\n"
	"varying vec2	Uv;\n"
    "void main() {\n"
	"  gl_Position = modelViewProj * vec4(vPosition,1.0);\n"
//	"  gl_Position *= Scale;\n"	
//	"  gl_Position *= Rotation;\n"	
//	"  gl_Position *= Translation;\n"	
//	"  gl_Position *= matProjection;\n"
	//"mat4 Model = Translation * Rotation * Scale ;\n"
	//"gl_Position *= Model * matProjection;\n"
	"  Uv = vUv;\n"
    "}\n";

	LOGI(gVertexShader);
 
    static const char gFragmentShader[] = 
	"precision mediump	float;\n"
	"varying vec2		Uv;\n"
	"uniform sampler2D	s_texture;\n"
    "void main() {\n"
    "  gl_FragColor =	texture2D(s_texture,Uv);\n"
    "}\n"; 


	//compile shader codes
	PS = loadShader(GL_FRAGMENT_SHADER,gFragmentShader);
	checkGlError("loadShader,gFragmentShader");
	VS = loadShader(GL_VERTEX_SHADER,gVertexShader);
	checkGlError("loadShader,gVertexShader");

	//make the shader program
	Program = glCreateProgram();
	checkGlError("glCreateProgram");

	//attach shaders to the program
	glAttachShader(Program, VS);
	checkGlError("glAttachShader,VS");
	glAttachShader(Program, PS);
	checkGlError("glAttachShader,PS");
	//finalize shader
	glLinkProgram(Program);
	checkGlError("glLinkProgram");
	glUseProgram(Program);
	checkGlError("glUseProgram");

	//bind position string to attrib at loc 0
	glBindAttribLocation(Program,0,"vPosition");
	checkGlError("glBindAttribLocation,vPosition");
	//bind color string to attriv at loc 1
	glBindAttribLocation(Program,1,"vUv");
	checkGlError("glBindAttribLocation,vUV");

	Position = glGetAttribLocation(Program,"vPosition");
	Uv = glGetAttribLocation(Program,"vUv");
	loc = glGetUniformLocation(Program, "s_texture");
	loc2 = glGetUniformLocation(Program, "Projection");

	//loc3 = glGetUniformLocation(Program, "Translation");
	//loc4 = glGetUniformLocation(Program, "Rotation");
	//loc5 = glGetUniformLocation(Program, "Scale");

}

Shader::~Shader()
{

}

void Shader::setUniformMatrix(const char* name, glm::mat4 matrix)
{
	GLuint MatrixID = glGetUniformLocation(Program, name);	
	checkGlError("glGetUniformLocation");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &matrix[0][0]);
	checkGlError("glUniformMatrix4fv");
}