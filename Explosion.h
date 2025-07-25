#pragma once
class TextureResource;

class Explosion
{
public:
	void Init(Vector pos, int maxxframe, int maxyframe, int maxframe);
	void Update(float deltaTime);
	void Render(HDC hdc);
private:
	TextureResource* _texture;
	float _animspeed = 0.1f;
	float _curtime;
	int _curframe;
	int _Maxframe;
	int _Xframe;
	int _Yframe;
	int _MaxXframe;
	int _MaxYframe;
	Vector _pos;

};

