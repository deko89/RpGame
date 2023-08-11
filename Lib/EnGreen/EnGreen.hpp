#include "EnGreen/EnGreen.h"

Engine eng;

Engine::Engine()
{
}

Engine::~Engine()
{	//Clear();
}

bool Engine::Init()
{
	if ( !context.Init() ) return false;
    wnd.Create("RpGame");
    context.Create(wnd);
	wnd.CreateGui();
	return true;
}

int Engine::Execute()
{
    bRun = true;
	SDL_Event event;
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_MAINLOOP_BEGIN
#else
    while (bRun)
#endif
    {
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
        wnd.Render();
    }
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_MAINLOOP_END;
#endif

    return 0;
}

void Engine::Clear()
{
	wnd.ClearGui();
	context.Clear();
	wnd.Clear();
    SDL_Quit();
}

Context& GetContext()
{	return eng.context;
}
