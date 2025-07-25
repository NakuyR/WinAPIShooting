#pragma once
#include "Actor.h"
class Enemy : public Actor
{
public:
	int GetHP() { return _hp; };
	void Shoot();
	void Init(int type, Vector pos);
	void Update(float deltaTime);
	void Render(HDC hdc);
	//void CheckAttack();
	int _type;
private:
	
	class TextureResource* _texture = nullptr;	// 리소스 매니저가 가지고 있는 원본 텍스쳐
	float AttackCooltime = 3;
	float CurrentCooltime = 0;
	class GameScene* gameScene = nullptr;
	float _speed = 30;
	int _moveDir = 1;
};

