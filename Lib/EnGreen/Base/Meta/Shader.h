#ifndef Shader_H
#define Shader_H

#include "EnGreen/Base/Meta/Meta.h"

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

/// Стандартные шейдеры.
class Shaders
{   public:
    Shader posTex,      ///< Позиция (x,y,z) + текстура (u,v).
           posTexA,     ///< Позиция (x,y,z) + прозрачная текстура (u,v).
           cubeIn;      ///< Куб изнутри (заднего плана, неба).
	/** Собрать.
		param[in] uCamSlot - точка привязки камеры. */
    void Compile(SlotMemG uCamSlot);
};

}

#endif
