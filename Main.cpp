#include "EnGreen/EnGreen.hpp"

int main()
{
	if (eng.Init() == false)
		return -1;

	eng.Execute();

	return 0;
}
