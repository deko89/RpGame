#ifndef META_HPP
#define META_HPP

/** \file
	\brief Метаданные

	Обобщение типов, переменных и т.п. для разных платформ.
*/

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

/// Макрос для перевода текста.
#define _(x) x

/// Строки.
#include <string>
typedef std::string str;

#endif
