#include "Models.h"

namespace EnG
{

// ModelStd /////////////////////////////////////////////////////////
ModelStd::ModelStd(ShaderType shT, Texture& tex) :
	shader(shT),
	texture(tex)
{
}
void ModelStd::SetTexture(Texture& tex)
{
	texture.Set(tex);
}
void ModelStd::Draw() const
{
	shader.Use();
	texture.Use();
	ModelVi::Draw();
}
// ModelCylinder /////////////////////////////////////////////////////
ModelCylinder::ModelCylinder(Val rad, Val height, ValN sgmC, ValN sgmH, bool bCloseBottom, bool bCloseUp) :
	rad(rad), height(height), sgmC(sgmC), sgmH(sgmH)
{
    Mesh mesh;
    mesh.MakeCylinder(rad, height, sgmC, sgmH, bCloseBottom, bCloseUp);
    PlaceTex plTex;
    plTex.SetCylinder(sgmC, sgmH, 2, 1);
    ModelStd::Make(mesh, plTex);
}
// BaseEngine ///////////////////////////////////////////////////////
void Models::Draw() const
{   for (Model* m : *this)
        m->Draw();
}

}
