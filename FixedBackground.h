#include "Actor.h"
#pragma once
class FixedBackground :public Actor
{
public:
	FixedBackground(Vector pos);
	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(HDC hdc) override;

	int32 GetTextureWidth();
	int32 GetTextureHeight();

private:
	Vector _pos;
	class TextureResource* _texture = nullptr;	// 리소스 매니저가 가지고 있는 원본 텍스처

};

