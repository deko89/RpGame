#include "GEng/GEng.h"
#include "GEng/World/Plant.h"

using namespace GEng;

int main()
{
	if (eng.Init() == false)
		return -1;

    // Настройка.
    View* view = eng.CreateViewWorld();
	view->world->sky = make_unique<SkyBox>("SkyBox/clouds1_%zu.jpg");
    // Установка камеры.
    view->cam.pos = {1, -2, 0};
    view->cam.angle = {0, 0, pi/2};
	// Интерфейс.
	const Val s = 50;
	const Color col = 0xff00aa00;
	const Val w = 4.0f;
	view->aShape.Add( new Line({0, 0},	 {s*2, 0},   w, col) );
	view->aShape.Add( new Line({s, 0},	 {s,   s*7}, w, col) );
	view->aShape.Add( new Line({s, s*7}, {s*2, s*7}, w, col) );
    // Создание текстуры.
    static Texture tex;
    tex.Load("SkyBox/clouds1_0.jpg");

	ModelCylinder* mod;

	mod = view->world->models.Make<ModelCylinder>();
	mod->d = 0.001;
	mod->len = 2;
	mod->SetPos( Pos(-1, 0, 0) );
	mod->SetTexture(tex);
	mod->Update();

	mod = view->world->models.Make<ModelCylinder>();
	mod->d = 0.001;
	mod->len = 2;
	mod->SetPos( Pos(0, 0, 1) );
	mod->SetAngle( Angle(0, pi2, 0) );
	mod->SetTexture(tex);
	mod->Update();

	// Spline
	vector<Pos> aVetv { {0,0,0}, {1,1,1}, {2,0.0,0}, {3,0.0,0}, {4,0.0,0}, {5,0.0,0} };
	mod = view->world->models.Make<ModelStvol>(aVetv);
	mod->SetTexture(tex);

	mod = view->world->models.Make<ModelStvol>(aVetv);
	mod->SetAngle( Angle(0, -pi2, 0) );
	mod->SetTexture(tex);

	eng.Execute();

	return 0;
}
