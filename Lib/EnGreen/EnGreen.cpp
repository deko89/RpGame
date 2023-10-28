#include "EnGreen/EnGreen.h"

#ifdef One_Translation_Unit
	#include "Base/Meta/Model.cpp"
	#include "Base/Types.cpp"
	#include "Context.cpp"
	#include "View/Wnd/WndGui.cpp"
#endif

Engine eng;

// Engine ///////////////////////////////////////////////////////////
Engine::Engine()
{
}

Engine::~Engine()
{
}

bool Engine::Init()
{
	if ( !IsEnvironment() ) return false;
    wnd.Wnd::Create("RpGame", SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
	context.Create(wnd);
	wnd.CreateGui();
	return true;
}

void Engine::Clear()
{
	wnd.ClearGui();
	context.Clear();
	wnd.Wnd::Clear();
}

int Engine::Execute()
{
    bRun = true;
	SDL_Event event;
	// Главный цикл.
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_MAINLOOP_BEGIN
#else
    while (bRun)
#endif
    {	// Обработка списка событий.
		while ( SDL_PollEvent(&event) )
		{	wnd.ProcessEvent(event);
			// Событие выхода.
			if ( event.type == SDL_QUIT ||
				 event.type == SDL_WINDOWEVENT &&
				 event.window.event == SDL_WINDOWEVENT_CLOSE &&
				 event.window.windowID == SDL_GetWindowID( wnd.NativeWnd() ) )
			{	bRun = false;
			}
		}
		// Рисование.
        wnd.Render();
    }
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_MAINLOOP_END;
#endif
    return 0;
}

Context& GetContext()
{	return eng.context;
}
