#include "Meta.h"
#include "glm/gtx/string_cast.hpp"

namespace EnG
{

Val Vec2I::Ratio() const
{   return ( (Val) x ) / y;
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

}
