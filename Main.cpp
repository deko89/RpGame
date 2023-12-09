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
    view->shaders.posTex.Use();
    // Установка камеры.
    view->cam.pos = {0, -3, 1};
    view->cam.angle = {0, 0, pi/2};
    view->cam.Update();
    // Создание текстуры.
    static Texture tex;
    tex.Load("SkyBox/clouds1_0.jpg");
    tex.Use();
    // Создание модели.
    Mesh mesh;
    mesh.MakeCylinder(0.3, 2, 8, 1);
    PlaceTex plTex;
    plTex.SetCylinder(8, 1, 2, 1);
    ModelVi* mod = new ModelVi;
    mod->Make(mesh, plTex);
    view->world->models.Add(mod);

	eng.Execute();

	return 0;
}
