#include <Debug.h>
#ifdef _WIN32
#include <Windows.h>
#include <iostream>

void printDebug(bool error,const char* format, ...)
{
#ifndef NDEBUG
	va_list args;
	char message[10240];

	va_start(args,format);
	vsprintf(message,format,args);
	va_end(args);

	if(error == true)
		OutputDebugStringA("Error: ");
	else
		OutputDebugStringA("Info: ");

	OutputDebugStringA(message);
#endif
}
#endif

void printGLString(const char *name, GLenum s)
{
#ifndef NDEBUG
	const char *v = (const char *) glGetString(s);
	LOGI("GL %s = %s\n", name, v);
#endif
}

void checkGlError(const char* op)
{
#ifndef NDEBUG
	for (GLint error = glGetError(); error; error
			= glGetError()) {
		LOGE("before %s() glError (0x%x)\n", op, error);
	}
#endif
}