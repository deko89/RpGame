#include "EnGreen/EnGreen.h"

#ifdef One_Translation_Unit
	#include "EnGreen/EnGreen.cpp"
#endif

int main()
{
	if (eng.Init() == false)
		return -1;

	eng.Execute();

	return 0;
}
