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
	ModelStd(ShaderType shT = shPosTex, Texture& tex = gTex0);
	void SetTexture(Texture& tex);
	virtual void Draw() const override;
protected:
	ShaderRef shader;
	TextureRef texture;
};

/// Модель цилинда.
class ModelCylinder : public ModelStd
{	public:
	ModelCylinder(Val rad, Val height, ValN sgmC, ValN sgmH, bool bCloseBottom = 1, bool bCloseUp = 1);
protected:
	Val rad;	///< Радиус.
	Val height;	///< Высота.
	ValN sgmC;	///< Число сегментов в окружности.
	ValN sgmH;	///< Число сигментов по высоте.
};

/// Модели.
class Models : public MassivPtr<Model>
{	public:
    typedef MassivPtr<Model> Base;
    void Draw() const;
};

}

#endif
