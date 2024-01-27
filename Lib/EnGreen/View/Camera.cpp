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
void Camera::ProcessStateInput(Val timeDelta)
{
	// Обновление позиции.
	Val dist = 1.0f * timeDelta;
	const Uint8* keys = SDL_GetKeyboardState(nullptr);
	if (keys[SDL_SCANCODE_RSHIFT])      dist *= 10;
	if (keys[SDL_SCANCODE_UP])          pos += vLook * dist;
	if (keys[SDL_SCANCODE_DOWN])        pos -= vLook * dist;
	if (keys[SDL_SCANCODE_RIGHT])       pos += glm::cross(vLook, vUp) * dist;
	if (keys[SDL_SCANCODE_LEFT])        pos -= glm::cross(vLook, vUp) * dist;
	if (keys[SDL_SCANCODE_PAGEUP])      pos += vUp * dist;
	if (keys[SDL_SCANCODE_PAGEDOWN])    pos -= vUp * dist;
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
