#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"

namespace EnG
{

// Camera ///////////////////////////////////////////////////////////
void Camera::Create(SlotMemG slot)
{	mem.Create( sizeof(Mat4) );
    mem.SetSlot(slot);
}
void Camera::Update()
{
	UpdateLook();
	UpdateMemG();
}
void Camera::UpdateLook()
{
    float cosX = cos(angle.x);
    vLook.x = cosX * cos(angle.z);
    vLook.y = cosX * sin(angle.z);
    vLook.z = sin(angle.x);
    glm::normalize(vLook);
}
void Camera::UpdateMemG()
{
	Mat4 mCam = glm::perspective(fFov, fAspect, fNear, fFar) *
				glm::lookAt(pos, pos + vLook, vUp);
	mem.Copy(mCam);
}

}
