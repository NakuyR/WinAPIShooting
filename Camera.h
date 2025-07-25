#pragma once
class Camera
{

public:
	void Update(float delta);
	static Vector ConvertWorldToScreen(Vector worldpos);
	static Vector ConvertScreenToWorld(Vector screenpos);
	static void SetCameraPos(Vector pos) { _camerapos = pos; }
	static Vector GetCameraPos() {return _camerapos;};
private:
	static Vector _camerapos;
};

