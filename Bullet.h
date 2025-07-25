#pragma once
#include "Actor.h"
class Enemy;
class Player;
enum BulletType {
	PlayerBullet,
	EnemyBullet,
};

class Bullet : public Actor
{

public:
	void CheckCollision();
	void Init();
	void Init(Vector pos, int bullettype);
	void Init(Vector pos);
	void Update(float deltaTime);
	void Render(HDC hdc);
	bool CanAttackMonster() { return _type == BulletType::EnemyBullet; };
private:
	class TextureResource* _texture = nullptr;	// 리소스 매니저가 가지고 있는 원본 텍스처
	BulletType _type;
	float speed = 500;
	int _bullettype;
};

