#ifndef Svg_H
#define Svg_H

#include <functional>
#include "Base.h"
#include "File.h"

constexpr auto streamSizeMax = std::numeric_limits<std::streamsize>::max();

namespace Svg
{

#ifndef M_Svg_OwnTypes
	#include "glm/glm.hpp"
	typedef float Val;
	typedef glm::vec2 Pos2;
	typedef glm::vec3 Vec3;
	typedef glm::mat3 Mat3;
	typedef uint32_t Color;
#endif

/// Тип фигуры.
enum ShapeType : uint8_t
{
	stLine,
	stRect,
	//stCircle,
	//stBezier, ///< Кривая Безье.
};

/// Данные фигуры.
struct ShapeStyle
{
	Val w = 1.0;
	Color col = 0xff000000;
	Color colStroke = 0xff000000;
};

/// Данные фигуры.
struct ShapeData
{
	ShapeType type;
	Vec3 a = Vec3(0, 0, 1),
		 b = Vec3(0, 0, 1),
		 c = Vec3(0, 0, 1),
		 d = Vec3(0, 0, 1);
	ShapeStyle style;
};

typedef std::function<void(const ShapeData&)> FunReadShape;
/** Прочитать svg.
	param[in] path - Путь до файла svg.
	param[in] f - Функция чтения фигуры. */
bool SvgRead(FilePath path, FunReadShape f);

}

#endif



#ifdef M_IncludeCpp
#include <algorithm>
#include <sstream>
#include "pugixml/src/pugixml.hpp"
#include "Std/TextRead.h"

namespace Svg
{

using namespace pugi;

FunReadShape funRead; ///< Функция чтения фигуры.

/// Чтение из строки для Svg.
struct TextReadSvg : public TextRead
{
	using TextRead::TextRead;
	Color ReadColor()
	{	Color col = 0xff000000;
		if ( Cmp("rgb") )
		{
			SkipD('(');
			col.r = ReadColorPart(',');
			col.g = ReadColorPart(',');
			col.b = ReadColorPart(')');
		} else if ( Cmp("none") )
		{	return col;
		} else
			std::cout << "Unknown color: " << s.substr(pos, 16) << std::endl;
		return col;
	}
protected:
	uint8_t ReadColorPart(Sym d)
	{
		StrV s;  s = ReadD(d);
		if ( s.empty() ) return 0;
		Val v = ToVal<Val>(s);
		if (s.back() == '%') v = 255.0 * v / 100.0;
		return v;
	}
};

struct SvgReadNode
{
	xml_node ndXml; ///< Читаемый узел.
	SvgReadNode* parent = nullptr; ///< Родительский узел.
	ShapeData shape; ///< Итоговые данные фигуры.
	Mat3 mTrans = Mat3(1); ///< Итоговая трансформация.

	SvgReadNode(xml_node ndXml, SvgReadNode* parent = nullptr) :
		ndXml(ndXml), parent(parent)
	{
	}
	void ReadChilds()
	{
		for ( SvgReadNode n(ndXml.first_child(), this);
			  n.ndXml;
			  n.ndXml = n.ndXml.next_sibling() )
		{
			n.ReadNode();
		}
	}
	void ReadNode()
	{
		ReadTransform();
		ReadStyle();
		const Str name = ndXml.name();
		if (name == "path")
		{	ReadPath();
		} else if (name == "g")
		{	ReadChilds();
		} else if (name == "defs")
		{
		}
	}
	void ReadPath()
	{
		Vec3 posSubPath(0, 0, 1); // Начальная позиция подпути.
		textRead.Set( ndXml.attribute("d").value() );
		for (Sym cmd; textRead;)
		{
			// Начало подпути.
			cmd = textRead.ReadSym();
			if (cmd == 0) break;
			if (cmd == 'M')
			{	ReadPos(posSubPath);
			} else
				textRead.UnReadSym();
			shape.a = posSubPath;
			// Чтение подпути.
			for (bool bReadSubPath = 1; bReadSubPath && textRead;)
			{
				cmd = textRead.ReadSym();
				switch (cmd)
				{
					case 0: // Конец у Path.
						break;
					case 'M':
					{	ReadPos(shape.a);
					}	break;
					case 'L':
					{	shape.type = stLine;
						ReadPos(shape.b);
						funRead(shape); // Чтение.
						shape.a = shape.b;
					}	break;
					case 'C':
					{
						ReadPos(shape.b);
						ReadPos(shape.c);
						ReadPos(shape.d);
					}	break;
					case 'z': case 'Z':
					{	if (shape.a != posSubPath)
						{
							shape.type = stLine; //tmp
							shape.b = posSubPath;
							funRead(shape);
						}
						bReadSubPath = 0;
					}	break;
					default:
						std::cout << "Unknown path command: " << cmd << std::endl;
						textRead.End();
				}
			}
		}
	}
private:
	TextReadSvg textRead;
	void ReadTransform()
	{
		mTrans = parent? parent->mTrans : Mat3(1);
		xml_attribute a = ndXml.attribute("transform");
		std::istringstream ss( a.value() );
		while (ss)
		{
			while ( std::isspace(ss.peek()) ) ss.ignore(); // Пропуск пробелов.
			string type;  std::getline(ss, type, '(');
			if ( type.empty() ) break;
			string sTrans;  std::getline(ss, sTrans, ')');
			std::replace(sTrans.begin(), sTrans.end(), ',', ' ');
			if (type == "matrix")
			{
				std::istringstream ss(sTrans);
				Mat3 mat(1);
				ss >> mat[0][0];  ss >> mat[0][1];
				ss >> mat[1][0];  ss >> mat[1][1];
				ss >> mat[2][0];  ss >> mat[2][1];
				mTrans *= mat;
			} else
				std::cout << "Unknown transform: " << type << std::endl;
		}
	}
	void ReadStyle()
	{
		if (parent)
			shape.style = parent->shape.style;
		xml_attribute a = ndXml.attribute("style");
		if ( a.empty() ) return;
		TextReadSvg r( a.value() );
		while (r)
		{
			StrV name = r.ReadD(':');
			if (name == "fill")
			{	shape.style.col = r.ReadColor();
			} else if (name == "stroke")
			{	shape.style.colStroke = r.ReadColor();
			}
			r.SkipD(';');
		}
	}
	void ReadPos(Vec3& v)
	{
		v.x = textRead.ReadD<Val>();
		v.y = textRead.ReadD<Val>();
		v = mTrans * v;
	}
};

bool SvgRead(FilePath path, FunReadShape f)
{
	xml_document doc;
	xml_parse_result result = doc.load_file( path.c_str() );
	if (!result)
	{
		std::cerr << "Error load svg " << path << std::endl;
		return 0;
	}
	funRead = f;
	SvgReadNode r( doc.child("svg") );
	r.ReadChilds();
	return 1;
}

}

#endif
