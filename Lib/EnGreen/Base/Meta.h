#ifndef META_HPP
#define META_HPP

/** \file
	\brief Абстрактные типы и данные.
	Обобщение типов, переменных и т.д. для разных платформ.
*/

#if defined(IMGUI_IMPL_OPENGL_ES2)
	#include <SDL_opengles2.h>
#else
	#include <SDL_opengl.h>
#endif

#ifdef __linux__
	const char* cPathFont = "/usr/share/fonts/truetype/ubuntu/Ubuntu-R.ttf";
//#elif __WINDOWS__
#endif

#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
#elif defined(__APPLE__)
    // GL 3.2 Core + GLSL 150
    const char* glsl_version = "#version 150";
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
#endif

// Простейшие типы.
typedef GLfloat		ValT;					///< Число.
typedef GLuint		ValNT;					///< Натуральное число 0, 1, 2...
typedef GLsizei		SizeT;					///< Тип размеров в памяти (массивов). //GLsizeiptr
typedef GLushort	IndT;					///< Тип индексов вершин (номеров).
const GLenum ValTId = GL_FLOAT;				///< Код типа чисел (для команд рисования).
const GLenum IndTId = GL_UNSIGNED_SHORT;	///< Код типа индексов вершин (для команд рисования).

#endif
