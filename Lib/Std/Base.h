/** \file
	\brief Базовые типы.
	Самые простые и часто используемые типы, константы, функции...
*/

#ifndef BASE_H
#define BASE_H

#include <string>
#include <cstdio>

/// Макрос для перевода текста.
#define _(x) x

/// Привести к строке.
#define ToStr(x) std::to_string(x)

// Строки.
typedef std::string Str;
typedef char Sym;

// Константы.
const Sym gSep = '/';	///< Разделитель путей.

// Функции.
/// Печать в строку (обёртка printf).
template<typename... Arg> Str PrintF(const Str& fmt, Arg... arg)
{
    size_t size = std::snprintf(0, 0, fmt.c_str(), arg...);
    Str s;  s.resize(size + 1);
    std::sprintf(s.data(), fmt.c_str(), arg...);
    s.resize(size);
    return s;
}

#endif
