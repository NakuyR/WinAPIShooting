#include "pch.h"
#include "Bullet.h"
#include "TextureResource.h"
#include "ResourceManager.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "GameScene.h"

void Bullet::CheckCollision()
{
}

void Bullet::Init() {

}
void Bullet::Init(Vector pos, int bullettype) {
	_actortype = Type::enemybullet;
	_type = BulletType::EnemyBullet;
	_bullettype = bullettype;
	_pos = pos;
	_texture = ResourceManager::GetInstance()->GetTexture("EnemyBullet");

}
void Bullet::Init(Vector pos) {
	_actortype = Type::bullet;
	_type = BulletType::PlayerBullet;
	_pos = pos;
	_texture = ResourceManager::GetInstance()->GetTexture("PlayerBullet");
}

void Bullet::Update(float deltaTime) {
	if (_type == BulletType::EnemyBullet) {
		SetPos(Vector(_pos.x, _pos.y + (deltaTime * speed)));
	}

	else if (_type == BulletType::PlayerBullet) {
		SetPos(Vector(_pos.x, _pos.y - (deltaTime * speed)));
	}

	//화면 밖으로 나가면 삭제
	if ( _pos.y < 0 || _pos.y > GameScene::GetGameScene()->GetMapSizeY()) {
 		GameScene::GetGameScene()->RemoveBullet(this);
		return;
	}
	CheckGrid();
}

void Bullet::Render(HDC hdc) {
	if (_texture)
	{
		if (_type == BulletType::PlayerBullet) {
			_texture->Render(hdc, _pos);
		}
		else if (_type == BulletType::EnemyBullet) {
			_texture->Render(hdc, _pos, 0, _bullettype,8);
		}
	}
}