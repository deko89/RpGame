#include <iostream>
#include "GEng/GEng.h"
#include "GEng/World/Plant.h"

using namespace GEng;

int main()
{
	if (eng.Init() == false)
		return -1;

    // Настройка.
    View* view = eng.CreateViewWorld();
	World& world = *view->world;
	Models& models = view->world->models;
	view->world->sky = make_unique<SkyBox>("SkyBox/clouds1_%zu.jpg");

	// Создание текстуры.
    static Texture texGrass;
    texGrass.Load("Res/Grass001.jpg", TexPar{
		.wX = TexWrap::Mirror,
		.wY = TexWrap::Mirror,});

	ModelPlane* ground = new ModelPlane;
	ground->size = {10000, 10000};
	ground->texN = {2000, 2000};
	ground->SetTexture(texGrass);
	ground->SetPos({-5000, -5000, 0});
	ground->Update();
	world.ground.reset(ground);

	// Загрузка растений.
	eng.aClass.Load("Plants");
    // Установка камеры.
    view->cam.pos = {0, -3, 5};
    view->cam.angle = {0, 0, pi/2};
	// Интерфейс.
		// Меню.
	Menu* menu = new Menu;
	Menu::Fold& mFile = menu->Add( _("Файл") );
	mFile.aItem.push_back( Menu::Item
	{	.name = _("Открыть"),
		.key = "Ctrl+O",
		.action = []() {GetEng().proj.Load();},
	} );
	mFile.aItem.push_back( Menu::Item
	{	.name = _("Сохранить"),
		.key = "Ctrl+S",
		.action = []() {GetEng().proj.Save();},
	} );
	mFile.aItem.push_back( Menu::Item
	{	.name = _("Сохранить как"),
		.action = []() {GetEng().proj.SaveAs();},
	} );
	mFile.aItem.push_back( Menu::Separator() );
	mFile.aItem.push_back( Menu::Item
	{	.name = _("Выход"),
		.action = []()
		{	GetEng().Exit();
		}
	} );
	Menu::Fold& mEdit = menu->Add( _("Правка") );
	Menu::Fold& mAdd = mEdit.AddFold(_("Добавить"));
	for (ClassModel* c : eng.aClass)
	{	mAdd.aItem.push_back( Menu::Item
		{	.name = c->Name(),
			.action = [c, &models]() {c->Instance(models);}
		} );
	}
	mEdit.aItem.push_back( Menu::Item
	{	.name = _("Удалить"),
		.key = "Delete",
		.action = [&world]()
		{	world.Delete();
		}
	} );
	view->aShape.Add(menu);
		//
	// const Val s = 50;
	// const Color col = 0xff00aa00;
	// const Val w = 4.0f;
	// view->aShape.Add( new Line({0, 0},	 {s*2, 0},   w, col) );
	// view->aShape.Add( new Line({s, 0},	 {s,   s*7}, w, col) );
	// view->aShape.Add( new Line({s, s*7}, {s*2, s*7}, w, col) );

	// Spline
	//vector<Pos> aVetv { {0,0,0}, {1,1,1}, {2,0.0,0}, {3,0.0,0}, {4,0.0,0}, {5,0.0,0} };
	//mod = view->world->models.Make<ModelStvol>(aVetv);
	//mod->SetTexture(tex);

	//mod = view->world->models.Make<ModelStvol>(aVetv);
	//mod->SetAngle( Angle(0, -pi2, 0) );
	//mod->SetTexture(tex);

	eng.Execute();

	return 0;
}
