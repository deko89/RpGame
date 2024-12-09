#include "Models.h"

namespace EnG
{

// ModelStd /////////////////////////////////////////////////////////
ModelStd::ModelStd(ShaderType shT, Texture& tex) :
	shader(shT),
	texture(tex)
{
}
Pos ModelStd::GetPos() const
{
	return pos;
}
void ModelStd::SetPos(const Pos& p)
{
	pos = p;
}
void ModelStd::Move(const Pos& p)
{
	pos += p;
}
Angle  ModelStd::GetAngle() const
{
	return angle;
}
void ModelStd::SetAngle(const Angle& a)
{
	angle = a;
}
Scale ModelStd::GetScale() const
{
	return scale;
}
void ModelStd::SetScale(const Scale& s)
{
	scale = s;
}
void ModelStd::SetTexture(Texture& tex)
{
	texture.Set(tex);
}
void ModelStd::Draw() const
{
	shader.Use();
	shader.SetTrans( GetMatTrans() );
	texture.Use();
	ModelVi::Draw();
}
void ModelStd::Print() const
{
	std::cout << "ModelStd " << this << ": pos " << pos << ", angle " << angle << ", scale " << scale << std::endl;
}
Mat4 ModelStd::GetMatTrans() const
{
	Mat4 mat(1);
	mat = glm::translate(mat, pos);
	mat = glm::rotate(mat, angle.z, Vec3(0, 0, 1));
	mat = glm::rotate(mat, angle.y, Vec3(0, 1, 0));
	mat = glm::rotate(mat, angle.x, Vec3(1, 0, 0));
	mat = glm::scale(mat, scale);
	return mat;
}
// ModelCylinder /////////////////////////////////////////////////////
ModelCylinder::ModelCylinder(Val rad, Val height, ValN sgmC, ValN sgmH, bool bCloseBottom, bool bCloseUp) :
	rad(rad), height(height), sgmC(sgmC), sgmH(sgmH), bCloseBottom(bCloseBottom), bCloseUp(bCloseUp)
{
    Update();
}
void ModelCylinder::Update()
{
    Mesh mesh;
    mesh.MakeCylinder(rad, height, sgmC, sgmH, bCloseBottom, bCloseUp);

    Points::Data pointsData(mesh.aVert);
    pointsData.size = {height, rad, rad}; //TODO Должен быть размер диаметра.
    modif.Set(pointsData);

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
