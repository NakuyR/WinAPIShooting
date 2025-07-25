#include "pch.h"
#include "Enemy.h"
#include "TextureResource.h"
#include "ResourceManager.h"
#include "Game.h"
#include "Player.h"
#include "Bullet.h"
#include "GameScene.h"


void Enemy::Shoot() {

	if (gameScene == nullptr)
		return;
	gameScene->CreateBullet(this);
}
void Enemy::Init(int type, Vector pos) {
	_actortype = Type::enemy;
	AttackCooltime = 3;
	CurrentCooltime = 0;
	_hp = 1;
	_pos = pos;
	_type = type;
	_texture = ResourceManager::GetInstance()->GetTexture("Enemy"+to_string(type));
	gameScene = GameScene::GetGameScene();
}


void Enemy::Update(float deltaTime) {
	CurrentCooltime += deltaTime;
	CheckAttack();
	if (gameScene == nullptr)
		return;
	if (_hp <= 0) {
		gameScene->CreateExplosion(this->_pos,6,2,12);
		gameScene->SetScore(gameScene->GetScore() + 100);
		gameScene->DestroyEnemy(this);
		
	}
	if (CurrentCooltime > AttackCooltime) {
		Shoot();
		CurrentCooltime = 0;
	}
	if (_pos.x <= 0) {
		_moveDir = 1;
	}
	if (_pos.x >= GWinSizeX) {
		_moveDir = -1;
	}
	SetPos(Vector(_pos.x + (deltaTime * _speed * _moveDir), _pos.y));
}

void Enemy::Render(HDC hdc) {
	if (_texture)
	{
		_texture->Render(hdc, _pos);
	}
}

//void Enemy::CheckAttack() {
//	if (gameScene == nullptr)
//		return;
//	vector<Bullet*> bullet = gameScene->GetBullet();
//	for (auto it = bullet.begin(); it != bullet.end(); ) {
//		Vector pos = (*it)->GetPos();
//		if (!(*it)->CanAttackMonster()) {
//			if (pos.x <= _pos.x + 25 && pos.x >= _pos.x - 25 && pos.y <= _pos.y + 25 && pos.y >= _pos.y - 25) {
//				gameScene->RemoveBullet(*it);
//				_hp--;
//			}
//			else {
//				it++;
//			}
//		}
//		else {
//			it++;
//		}
//	}
//}