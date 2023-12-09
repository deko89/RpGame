#ifndef World_H
#define World_H

#include "Models.h"
#include "SkyBox.h"

namespace EnG
{

/// Мир.
class World
{	public:
    Models models; ///< Модели.
    SkyBox sky;    ///< Небо.
};

}

#endif
