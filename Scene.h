#pragma once
class Scene
{
public:
	int32 GetMapSizeX() { return _mapSizeX; }
	int32 GetMapSizeY() { return _mapSizeY; }
	virtual void Init() {}
	virtual void Destroy() {};
	virtual void Update(float deltatTime) {}
	virtual void Render(HDC hdc) {}
	int32 _mapSizeX = GWinSizeX;
	int32 _mapSizeY = GWinSizeY;

};