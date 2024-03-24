#ifndef Shader_H
#define Shader_H

#include <array>
#include "EnGreen/Base/Meta/MemG.h"

namespace EnG
{

/// Программа рисования для видеокарты.
class Shader
{	public:
	/// Конструктор считывает и собирает шейдер. 0 - нет шейдера.
	void Compile(StrCG sVertexShader, StrCG sGeometryShader, StrCG sFragmentShader);

	~Shader();

	void Use() const; ///< Использование программы.

	/** Привязать к глобальной памяти.
    	param[in] blockName - блок переменных в шейдере (uniform).
		param[in] uLinkPoint - точка привзяки. К ней же должен быть привязан и сам буфер (ubo). */
	void LinkMemG(StrCG blockName, SlotMemG uLinkPoint);
protected:
	GLuint id = 0; ///< Идентификатор программы.

	/** Собрать.
		param[in] typeShader - тип шейжера (GL_VERTEX_SHADER, ...). */
	bool CompileShader(StrCG pCode, GLenum const typeShader);
};

/// Тип шейдера.
enum ShaderType
{
	shPosTex,		///< Позиция (x,y,z) + текстура (u,v).
	shPosTexA,		///< Позиция (x,y,z) + прозрачная текстура (u,v).
	shCubeIn,		///< Куб изнутри (заднего плана, неба).
};

const size_t gShaderCount = 3; ///< Число шейдеров.

/// Стандартные шейдеры. Последовательность в массиве соответствует ShaderType.
class Shaders : public std::array<Shader, gShaderCount>
{   public:
	MemG	memCam;	///< Видеопамять камеры (позиция).
	/** Собрать. */
	void Compile();
};

/// Получить шейдеры.
Shaders& GetShaders(); // Реализовано в Engine.cpp

/// Сссылка на шеёдер.
class ShaderRef
{	public:
	ShaderRef(ShaderType shT = shPosTex);
	/// Установить.
	void Set(ShaderType shT);
	/// Сделать активным.
	void Use() const;
protected:
	ShaderType t;
	Shader& Get() const;
};

}

#endif
