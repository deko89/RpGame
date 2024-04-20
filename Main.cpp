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
    view->cam.pos = {10, -20, 0};
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

	mod = view->world->models.Make<ModelCylinder>();
	mod->rad = 0.03;
	mod->height = 25;
	mod->SetAngle( Angle(0, glm::radians(90.0), 0) );
	mod->SetTexture(tex);
	mod->Update();

	// Spline
	mod = view->world->models.Make<ModelCylinder>();
	mod->rad = 0.3;
	mod->height = 25;
	mod->sgmC = 6;
	mod->sgmH = 64;
	mod->modif.Make<Points::Modifs::Taper>(0.1);
	mod->modif.Make<Points::Modifs::Rotate>( Angle{0, glm::radians(90.0), 0} );
	vector<Pos> aKeySpline { {0,0,0}, {5,0.0,5.0}, {10,0.0,0.0}, {15,0.0,0.2}, {20,0.0,0.5}, {25,0.0,0.0}  };
	mod->modif.Make<Points::Modifs::Spline>(aKeySpline);
	mod->SetTexture(tex);
	mod->Update();

	eng.Execute();

	return 0;
}
