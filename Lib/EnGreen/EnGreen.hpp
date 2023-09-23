#include "EnGreen/EnGreen.h"

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
    wnd.Create("RpGame");
	return true;
}

void Engine::Clear()
{
	wnd.Clear();
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
{	return eng.wnd.context;
}
