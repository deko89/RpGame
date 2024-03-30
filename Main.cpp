#include "EnGreen/EnGreen.h"

#ifdef One_Translation_Unit
	#include "EnGreen/EnGreen.cpp"
#endif

using namespace EnG;

int main()
{
	if (eng.Init() == false)
		return -1;

    // Настройка.
    View* view = eng.CreateViewWorld();
    // Установка камеры.
    view->cam.pos = {0, -3, 1};
    view->cam.angle = {0, 0, pi/2};
    // Создание текстуры.
    static Texture tex;
    tex.Load("SkyBox/clouds1_0.jpg");
	ModelCylinder* mod = new ModelCylinder(0.1, 1, 16, 4);
	mod->SetTexture(tex);
	mod->SetPos( Pos(3, 3, 1) );
	mod->SetAngle( Angle(glm::radians(90.0), glm::radians(90.0), glm::radians(45.0)) );
	mod->SetScale( Scale(0.5, 0.5, 3) );
	view->world->models.Add(mod);
	mod->Print();

	for (int x = 0; x < 5; ++x)
	{
		mod = view->world->models.Make<ModelCylinder>();
		mod->rad = 0.2;
		mod->modif.Make<Points::Modifs::Taper>(x / 5.0);
		mod->SetPos( Pos(x, 0, 0) );
		mod->SetTexture(tex);
		mod->Update();
		mod->Print();
	}

	eng.Execute();

	return 0;
}
