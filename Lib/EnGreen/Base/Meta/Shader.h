#ifndef Shader_H
#define Shader_H

#include "EnGreen/Base/Meta/Meta.h"

namespace EnG
{

/// Программа рисования для видеокарты.
class Shader
{	public:
	static void Init();

	/// Конструктор считывает и собирает шейдер.
	void Create(const GStr sVertexShader, const GStr sGeometryShader, const GStr sFragmentShader);

	~Shader();

	void Use() const; ///< Использование программы.

	/** Привязать к глобальной памяти.
		param[in] uLinkPoint - точка привзяки. К ней же должен быть привязан и сам буфер (ubo).
		param[in] blockName - блок переменных в шейдере (uniform). */
	void LinkMemG(SlotMemG uLinkPoint, const GStr blockName);
protected:
	GLuint id = 0; ///< Идентификатор программы.

	/** Собрать.
		param[in] typeShader - тип шейжера (GL_VERTEX_SHADER, ...). */
	bool CompileShader(const GStr pCode, GLenum const typeShader);
};

}

#endif
