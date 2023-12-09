#ifndef SKYBOX_H
#define SKYBOX_H

#include "EnGreen/Base/Meta/Texture.h"

namespace EnG
{

/// Задний план (небо).
class SkyBox
{   public:
    /** Создать.
        param[in] path - шаблон пути до текстур. Формат: "Path/Name%zu.Ext".
    */
    void Create(const Str& path);
    void Draw() const;
private:
    ModelVi model;  ///< Модель.
    Texture tex;    ///< Текстура.
};

}

#endif
