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
	"uniform mat4 modelViewProj;\n"
//	"uniform mat4 Scale;\n"
//	"uniform mat4 Rotation;\n"
//	"uniform mat4 View;\n"
//	"uniform mat4 matProjection;\n"
	"varying vec2 Uv;\n"
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
	"precision mediump float;\n"
	"varying vec2 Uv;\n"
	"uniform sampler2D s_texture;\n"
    "void main() {\n"
    "  gl_FragColor = texture2D(s_texture,Uv);\n"
    "}\n"; 


	//compile shader codes
	PS = loadShader(GL_FRAGMENT_SHADER,gFragmentShader);
	checkGlError("Shader");
	VS = loadShader(GL_VERTEX_SHADER,gVertexShader);
	checkGlError("Shader2");

	//make the shader program
	Program = glCreateProgram();
	checkGlError("Shader3");

	//attach shaders to the program
	glAttachShader(Program, VS);
	checkGlError("Shader4");
	glAttachShader(Program, PS);
	//finalize shader
	glLinkProgram(Program);

	glUseProgram(Program);

	//bind position string to attrib at loc 0
	glBindAttribLocation(Program,0,"vPosition");
	//bind color string to attriv at loc 1
	glBindAttribLocation(Program,1,"vUv");
	checkGlError("Shader5");

	Position = glGetAttribLocation(Program,"vPosition");
	Uv = glGetAttribLocation(Program,"vUv");
	loc = glGetUniformLocation(Program, "s_texture");
	loc2 = glGetUniformLocation(Program, "Projection");
	//loc3 = glGetUniformLocation(Program, "Translation");
	//loc4 = glGetUniformLocation(Program, "Rotation");
	//loc5 = glGetUniformLocation(Program, "Scale");

//
//	///////////////////Testing/////////////////
//
//glm::mat4 translate = glm::translate(10.0f, 0.0f, 0.0f);
//glm::vec4 originalVector(10.0f, 10.0f, 10.0f, 0.0f);
//glm::mat4 scaling = glm::scale(2.0f, 2.0f, 2.0f);
//glm::vec3 myRotationAxis(0,0,1.0f);
//glm::mat4 rotation = glm::rotate(90.0f, myRotationAxis);
//glm::mat4 ViewMatrix = glm::translate(-3.0f, 0.0f, 0.0f);
//
//
//	///////////////////////////////////////////
////glm::vec4 transformedVector = translate * rotation * scaling  * originalVector;
//glm::mat4 ModelMatrix = translation * rotation * scale;
//// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
//glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
//// Camera matrix
//glm::mat4 View       = glm::lookAt(
//    glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
//    glm::vec3(0,0,0), // and looks at the origin
//    glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
//);
//// Model matrix : an identity matrix (model will be at the origin)
//glm::mat4 Model      = glm::mat4(1.0f);  // Changes for each model !
//// Our ModelViewProjection : multiplication of our 3 matrices
//glm::mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around

// Get a handle for our "MVP" uniform.
// Only at initialisation time.
//
 
// Send our transformation to the currently bound shader,
// in the "MVP" uniform
// For each model you render, since the MVP will be different (at least the M part)
//

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