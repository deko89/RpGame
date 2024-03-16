#ifndef Models_H
#define Models_H

#include "Std/MassivPtr.h"
#include "EnGreen/Base/Meta/Texture.h"
#include "EnGreen/Base/Meta/Model.h"

namespace EnG
{

/// Стандартная модель.
class ModelStd: public ModelVi
{	public:
	ModelStd(ShaderType shT, Texture& tex);
	virtual void Draw() const override;
protected:
	ShaderRef shader;
	TextureRef texture;
};

/// Модели.
class Models : public MassivPtr<Model>
{	public:
    typedef MassivPtr<Model> Base;
    void Draw() const;
};

}

#endif
