#include "Shader.h"
#include <iostream> // Потоковый вывод (cout).

namespace EnG
{

// Shader ///////////////////////////////////////////////////////////
void Shader::Init()
{
}
void Shader::Create(const GStr sVertexShader, const GStr sGeometryShader, const GStr sFragmentShader)
{	id = glCreateProgram();
	CompileShader(sVertexShader,   GL_VERTEX_SHADER);
	CompileShader(sGeometryShader, GL_GEOMETRY_SHADER);
	CompileShader(sFragmentShader, GL_FRAGMENT_SHADER);
	glLinkProgram(id);
	// Проверяем.
	GLint iRes;   glGetProgramiv(id, GL_LINK_STATUS, &iRes);
	if (!iRes)
	{	GLchar infoLog[512];
		glGetProgramInfoLog(id, 512, NULL, infoLog);
		std::cout << "Error: Shader program link fail\n" << infoLog << std::endl;
	}
}
Shader::~Shader()
{	glDeleteProgram(id);
}
void Shader::Use() const { glUseProgram(id); }
void Shader::LinkMemG(SlotMemG uLinkPoint, const GStr blockName)
{	GLuint uBlockId = glGetUniformBlockIndex(id, blockName);
	glUniformBlockBinding(id, uBlockId, uLinkPoint);
}
bool Shader::CompileShader(const GStr pCode, GLenum const typeShader)
{	if (!pCode) return 1;
	GLuint uShader = glCreateShader(typeShader);
	glShaderSource(uShader, 1, &pCode, NULL);
	glCompileShader(uShader);
	// Добавляем к программе.
	GLint iRes;   glGetShaderiv(uShader, GL_COMPILE_STATUS, &iRes); // Проверка собраля ли?
	if (iRes) // Добавляем.
	{	glAttachShader(id, uShader);
	} else // Ошибка.
	{	GLchar infoLog[512];
		glGetShaderInfoLog(uShader, 512, NULL, infoLog);
		std::cout << "Error: Shader compilation fail\n" << infoLog << "\nSrc:\n" << pCode << std::endl;
	}
	glDeleteShader(uShader); // Удаляем - больше не нужен.
	return iRes != 0;
}

}
