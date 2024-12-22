#include "Meta.h"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

namespace EnG
{

Val Vec2I::Ratio() const
{   return ( (Val) x ) / y;
}

std::ostream& operator<<(std::ostream& os, const Vec2& v)
{
	return os << glm::to_string(v);
}

std::ostream& operator<<(std::ostream& os, const Vec3& v)
{
	return os << glm::to_string(v); //v.x << " " << v.y << " " << v.z;
}

std::ostream& operator<<(std::ostream& os, const Vec4& v)
{
	return os << glm::to_string(v); //v.x << " " << v.y << " " << v.z << " " << v.w;
}

std::ostream& operator<<(std::ostream& os, const Mat4& m)
{
	return os << glm::to_string(m);
}

void SetPolygonMode(PolygonMode mode)
{
	GLenum m;
	switch (mode)
	{	case PolygonMode::Point:	m = GL_POINT;	break;
		case PolygonMode::Line:		m = GL_LINE;	break;
		case PolygonMode::Fill:		m = GL_FILL;	break;
	}
	glPolygonMode(GL_FRONT_AND_BACK, m);
}

}
