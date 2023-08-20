/** \file
	\brief Базовые типы.
	Самые простые и часто используемые типы, константы, функции...
*/

#ifndef BASE_H
#define BASE_H

#include <string>

/// Макрос для перевода текста.
#define _(x) x

/// Привести к строке.
#define ToStr(x) std::to_string(x)

// Строки.
typedef std::string str; // Устарело.
typedef std::string Str;
typedef char Sym;

// Константы.
const Sym gSep = '/';	///< Разделитель путей.

#endif
