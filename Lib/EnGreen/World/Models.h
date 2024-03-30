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
	virtual Pos   GetPos() const override;					///< Получить позицию.
	virtual void  SetPos(const Pos& p) override;			///< Установить позицию.
	virtual void  Move(const Vec3& v) override;				///< Передвинуть.
	virtual Angle GetAngle() const override;				///< Получить углы.
	virtual void  SetAngle(const Angle& a) override;		///< Установить углы.
	virtual Scale GetScale() const override;				///< Получить масштаб.
	virtual void  SetScale(const Scale& s) override;		///< Установить масштаб.
	void SetTexture(Texture& tex);
	virtual void Draw() const override;
	void Print() const;
protected:
	Pos pos = Pos(0, 0, 0);
	Angle angle = Angle(0, 0, 0);
	Scale scale = Scale(1, 1, 1);
	ShaderRef shader;
	TextureRef texture;
	Mat4 GetMatTrans() const; ///< Получить матрицу трансформации.
};

/// Модель цилинда.
class ModelCylinder : public ModelStd
{	public:
	Val rad = 0.1;	///< Радиус.
	Val height = 1;	///< Высота.
	ValN sgmC = 16;	///< Число сегментов в окружности.
	ValN sgmH = 1;	///< Число сигментов по высоте.
	bool bCloseBottom = 1;	///< Закрыто снизу.
	bool bCloseUp = 1;		///< Закрыто сверху.
	ModelCylinder(Val rad, Val height, ValN sgmC, ValN sgmH, bool bCloseBottom = 1, bool bCloseUp = 1);
protected:
};

/// Модели.
class Models : public MassivPtr<Model>
{	public:
    typedef MassivPtr<Model> Base;
    void Draw() const;
};

}

#endif
