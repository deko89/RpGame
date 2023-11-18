#include "Image.h"
#include <stdio.h>
#include "SDL2/SDL_image.h"

// Image ////////////////////////////////////////////////////////////
void Image::Init()
{
	if ( IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) !=
	             (IMG_INIT_JPG | IMG_INIT_PNG) )
    {   printf( _("Error IMG_Init") );
    }
}
void Image::DeInit()
{
    IMG_Quit();
}
Image::Image(const Str& path)
{   pSurf = IMG_Load( path.c_str() );
}
Image::~Image()
{	Clear();
}
void Image::Load(const Str& path)
{	Clear();
    pSurf = IMG_Load( path.c_str() );
	if (!pSurf)
		printf(_("Error: %s\n"), SDL_GetError());
}
void Image::Clear()
{	if ( pSurf && SDL_MUSTLOCK(pSurf) )
		SDL_UnlockSurface(pSurf);
	SDL_FreeSurface(pSurf);
}
void* Image::Get() const
{	if ( pSurf && SDL_MUSTLOCK(pSurf) )
	{	if ( SDL_LockSurface(pSurf) )
		{	printf(_("Error: %s\n"), SDL_GetError());
			return nullptr;
		}
	}
	return pSurf->pixels;
}
size_t Image::X() const
{   return pSurf->w;
}
size_t Image::Y() const
{   return pSurf->h;
}
