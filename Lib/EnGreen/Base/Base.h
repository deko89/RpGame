/** \file
	\brief Базовые типы.
	Самые простые и часто используемые типы, константы, функции...
*/

// Строки.
#include <string>
typedef std::string str; // Устарело.
typedef std::string Str;
typedef char Sym;

// Константы.
const Sym gSep = '/';	///< Разделитель путей.

/// Макрос для перевода текста.
#define _(x) x
