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
struct ShapeData
{
	ShapeType type;
	Vec3 a = Vec3(0, 0, 1),
		 b = Vec3(0, 0, 1),
		 c = Vec3(0, 0, 1),
		 d = Vec3(0, 0, 1);
	Val w = 1.0;
	Color col = 0xff000000;
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

namespace Svg
{

using namespace pugi;

FunReadShape funRead; ///< Функция чтения фигуры.

struct SvgReadNode
{
	xml_node ndXml; ///< Читаемый узел.
	ShapeData shape; ///< Итоговые данные фигуры.

	SvgReadNode(xml_node ndXml) : ndXml(ndXml)
	{
		for (xml_attribute attr: ndXml.attributes())
		{
			//std::cout << " " << attr.name() << "=" << attr.value();
		}
		for (xml_node nd : ndXml.children())
		{
			const Str name = nd.name();
			if (name == "path")
			{	ReadPath(nd);
			} else if (name == "g")
			{	SvgReadNode r(nd);
			} else if (name == "defs")
			{	continue;
			}
		}
	}
	void ReadPath(xml_node ndPath)
	{
		Vec3 posSubPath(0, 0, 1); // Начальная позиция подпути.
		char cmd; // Текущая команда.
		Mat3 mTrans = ReadTransform(ndPath);
		std::istringstream ss( ndPath.attribute("d").value() );
		ss >> cmd;
		if (cmd == 'M')
		{
			ss >> posSubPath.x;  ss >> posSubPath.y;
			shape.a = posSubPath = mTrans * posSubPath;
		} else
			std::cout << "path: first no M -" << cmd << std::endl;
		while (ss)
		{
			char cmd = 0;
			ss >> cmd;
			switch (cmd)
			{
				case 0: // Конец у Path.
					break;
				case 'M':
				{	ss >> shape.a.x;  ss >> shape.a.y;
					shape.a = mTrans * shape.a;
				}	break;
				case 'L':
				{	shape.type = stLine;
					ss >> shape.b.x;  ss >> shape.b.y;
					shape.b = mTrans * shape.b;
					funRead(shape); // Чтение.
					shape.a = shape.b;
				}	break;
				case 'C':
				{
					ss >> shape.b.x;  ss >> shape.b.y;
					ss >> shape.c.x;  ss >> shape.c.y;
					ss >> shape.d.x;  ss >> shape.d.y;
				}	break;
				case 'z': case 'Z':
				{	if (shape.a != posSubPath)
					{
						shape.type = stLine; //tmp
						shape.b = posSubPath;
						funRead(shape);
					}
					ss >> cmd;
					if (cmd == 'M')
					{
						ss >> posSubPath.x;  ss >> posSubPath.y;
						posSubPath = mTrans * posSubPath;
					} else
					{
						ss.unget();
					}
					shape.a = posSubPath;
				}	break;
				default:
					std::cout << "Unknown path command: " << cmd << std::endl;
			}
		}
	}
	Mat3 ReadTransform(xml_node nd)
	{
		Mat3 mat(1);
		xml_attribute a = nd.attribute("transform");
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
				ss >> mat[0][0];  ss >> mat[0][1];
				ss >> mat[1][0];  ss >> mat[1][1];
				ss >> mat[2][0];  ss >> mat[2][1];
			} else
				std::cout << "Unknown transform: " << type << std::endl;
		}
		return mat;
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
	SvgReadNode( doc.child("svg") );
	return 1;
}

}

#endif
