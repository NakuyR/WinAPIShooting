#pragma once
#include "Actor.h"
class Player : public Actor
{
public:
	int GetHP() { return _hp; };
	void Shoot();
	void Init(Vector pos);
	void Update(float deltaTime);
	void Render(HDC hdc);
	//void CheckAttack();
	void HPbar(HDC hdc);
private:
	
	class TextureResource* _texture = nullptr;	// 리소스 매니저가 가지고 있는 원본 텍스처
	class TextureResource* _hptexture = nullptr;
	float _speed = 200;
	class GameScene* gameScene = nullptr;
};

