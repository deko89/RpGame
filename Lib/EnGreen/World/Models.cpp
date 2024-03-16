#include "Models.h"

namespace EnG
{

// ModelStd /////////////////////////////////////////////////////////
ModelStd::ModelStd(ShaderType shT, Texture& tex) :
	shader(shT),
	texture(tex)
{
}
void ModelStd::Draw() const
{
	shader.Use();
	texture.Use();
	ModelVi::Draw();
}
// BaseEngine ///////////////////////////////////////////////////////
void Models::Draw() const
{   for (Model* m : *this)
        m->Draw();
}

}
