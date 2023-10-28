#ifndef Model_H
#define Model_H

#include "EnGreen/Base/Types.h"

/// Базовый 3d объект.
class Model
{	public:
	virtual ~Model() {}
	virtual void Update() {};		///< Обновить в видеокарте.
	virtual void Draw() const = 0;	///< Рисование.
};

/** Модель с вершинами, и 3 индексами на треугольник.
	\details Это позволят отсекать невидимую сторону. А с GL_TRIANGLE_STRIP стороны меняются (по часовй/против).*/
class ModelVi: public Model
{	public:
	ModelVi();
	virtual ~ModelVi() override;
	void Make(const Mesh& mesh, const PlaceTex& placeTex);
	virtual void Draw() const override;
protected:
	GLuint vao;		///< Установщик атрибутов объекта перед рисованием.
	GLuint vb, ib;	///< Буфер вершин, и индексы порядка рисования.
	GLsizei nInd;	///< Число индексов.
};

#endif
