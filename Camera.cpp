#include "pch.h"
#include "Camera.h"

Vector Camera::_camerapos = Vector(0, 0);

Vector Camera::ConvertWorldToScreen(Vector worldpos)
{
	Vector newpos;
	newpos.x = worldpos.x - (_camerapos.x - (GWinSizeX / 2));
	newpos.y = worldpos.y - (_camerapos.y - (GWinSizeY / 2));
	return newpos;
}

Vector Camera::ConvertScreenToWorld(Vector screenpos)
{
	Vector newpos;
	newpos.x = screenpos.x + (_camerapos.x + (GWinSizeX / 2));
	newpos.y = screenpos.y + (_camerapos.y + (GWinSizeY / 2));
	return newpos;
}

void Camera::Update(float delta) {

}
