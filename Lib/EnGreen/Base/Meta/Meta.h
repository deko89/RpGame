#ifndef META_HPP
#define META_HPP

/** \file
	\brief Абстрактные типы и данные.
	Обобщение типов, переменных и т.д. для разных платформ.
*/

#if defined(IMGUI_IMPL_OPENGL_ES2)
	#include <SDL_opengles2.h>
#else
	#define GL_GLEXT_PROTOTYPES
	#include <SDL_opengl.h>
	#include "SDL_opengl_glext.h"
#endif

#include "glm/glm.hpp"

// Системные константы.

#ifdef __linux__
	const char* cPathFont = "/usr/share/fonts/truetype/ubuntu/Ubuntu-R.ttf";
//#elif __WINDOWS__
#endif

// Простейшие типы.
typedef GLfloat		Val;				///< Число.
typedef GLuint		ValN;				///< Натуральное число 0, 1, 2...
typedef GLsizei		Size;				///< Тип размеров в памяти (массивов). //GLsizeiptr
typedef GLushort	Ind;				///< Тип индексов вершин (номеров).
const GLenum ValId = GL_FLOAT;			///< Код типа чисел (для команд рисования).
const GLenum IndId = GL_UNSIGNED_SHORT;	///< Код типа индексов вершин (для команд рисования).

// Простые 2d типы.
	/// Координата текстуры.
struct PosTex
{	Val u, v;
};

//typedef SDL_Rect	Rect;

// Простые 3d типы.
typedef glm::vec3 Pos;		///< Позиция.
typedef glm::vec3 Angle;	///< Угол (по локальным осям объекта yaw, pitch, roll).
typedef glm::vec3 Scale;	///< Масштаб.
typedef glm::vec3 Vec3;		///< Вектор с 3 числами.
typedef glm::vec4 Vec4;		///< Вектор с 4 числами.
typedef glm::mat4 Mat4;		///< Матрица 4х4.

// Константы.
const Val pi = (Val) M_PI, pi2 = (Val) M_PI_2, pi4 = (Val) M_PI_4;

#endif
