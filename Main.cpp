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
    view->cam.pos = {1, -2, 0};
    view->cam.angle = {0, 0, pi/2};
    // Создание текстуры.
    static Texture tex;
    tex.Load("SkyBox/clouds1_0.jpg");

	ModelCylinder* mod;

	mod = view->world->models.Make<ModelCylinder>();
	mod->d = 0.001;
	mod->len = 2;
	mod->SetPos( Pos(0, 0, -1) );
	mod->SetTexture(tex);
	mod->Update();

	mod = view->world->models.Make<ModelCylinder>();
	mod->d = 0.001;
	mod->len = 2;
	mod->SetPos( Pos(-1, 0, 0) );
	mod->SetAngle( Angle(0, glm::radians(90.0), 0) );
	mod->SetTexture(tex);
	mod->Update();

	// Spline
	vector<Pos> aVetv { {0,0,0}, {1,1,1}, {2,0.0,0}, {3,0.0,0}, {4,0.0,0}, {5,0.0,0} };
	mod = view->world->models.Make<ModelStvol>(aVetv);
	mod->SetTexture(tex);

	mod = view->world->models.Make<ModelStvol>(aVetv);
	mod->SetAngle( Angle(glm::radians(-30.0), glm::radians(90.0), glm::radians(45.0)) );
	mod->SetTexture(tex);

	eng.Execute();

	return 0;
}
