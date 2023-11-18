#ifndef Models_H
#define Models_H

#include "Std/MassivPtr.h"
#include "EnGreen/Base/Meta/Model.h"

namespace EnG
{

/// Модели.
class Models : public MassivPtr<Model>
{	public:
    Model* Add();
};

}

#endif
