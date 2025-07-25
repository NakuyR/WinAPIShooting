#pragma once
class Background
{
public:
	void Init();
	void Move();
	void Update(float deltaTime);
	void Render(HDC hdc);
	void SetPos(Vector pos);
	Vector Getpos() { return _pos; };
private:
	float speed = 100;
	Vector _pos;
	class TextureResource* _texture = nullptr;	// 리소스 매니저가 가지고 있는 원본 텍스처

};

