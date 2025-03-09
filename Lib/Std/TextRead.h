#ifndef TextRead_H
#define TextRead_H

#include "Base.h"

struct TextRead : public Str
{
	using Str::Str;
	size_t pos = 0; ///< Текущая позиция.
	void SkipD(Sym d);	///< Пропустить до разделителя d включительно.
	/// Чтение до d (без d). Поставить позицию после d.
	StrV ReadD(Sym d);
	template<typename V>
	V ReadD(Sym d)
	{	StrV s = ReadD(d);
		return ToVal<V>(s);
	}
	void SkipSpace(); ///< Пропустить пробелы.
	bool Cmp(StrR s) const; ///< Текущий текст s?
	void GoTo(Sym c); ///< Перейти к символу c.
	operator bool() const {return pos < size();}
protected:
	Str& s = *this;
};

#endif



#ifdef M_IncludeCpp

void TextRead::SkipD(Sym d)
{
	GoTo(d);
	if ( pos < size() ) ++pos;
}
StrV TextRead::ReadD(char d)
{
	const size_t posBegin = pos;
	GoTo(d);
	StrV v(data() + posBegin, pos - posBegin);
	if ( pos < size() ) ++pos;
	return v;
}
void TextRead::SkipSpace()
{
	for (;	pos < size() &&
			std::isspace(s[pos]);
			++pos) {}
}
void TextRead::GoTo(Sym c)
{	for (; pos < size() && s[pos] != c; ++pos) {}
}
bool TextRead::Cmp(StrR s) const
{
	return compare(pos, s.size(), s) == 0;
}

#endif
