#include "EnGreen/EnGreen.h"

#ifdef One_Translation_Unit
	#include "EnGreen/EnGreen.cpp"
#endif

using namespace EnG;

int main()
{
	if (eng.Init() == false)
		return -1;

	eng.Execute();

	return 0;
}
