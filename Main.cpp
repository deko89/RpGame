#include "EnGreen/EnGreen.cpp"

int main()
{
	if (eng.Init() == false)
		return -1;

	eng.Execute();

	return 0;
}
