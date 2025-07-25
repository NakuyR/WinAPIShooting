#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "TextureResource.h"
#include "ResourceManager.h"
#include "Game.h"
#include "GameScene.h"
#include "Camera.h"

void Player::Init(Vector pos) {
	_actortype = Type::player;
	_pos = pos;
	_hp = 5;
	_texture = ResourceManager::GetInstance()->GetTexture("Player");
	_hptexture = ResourceManager::GetInstance()->GetTexture("HP");
	gameScene = GameScene::GetGameScene();
	Camera::SetCameraPos(_pos);
	
}

void Player::Shoot()
{
	if (gameScene == nullptr)
		return;
	gameScene->CreateBullet(this);
}

void Player::Update(float deltaTime)
{
	if (gameScene == nullptr)
		return;
	// W 키가 눌러졌으면 위로 이동.
// S 키가 눌러졌으면 아래로 이동.
	if (InputManager::GetInstance()->GetButtonPressed(KeyType::W))
	{
		// 이동 거리 = 시간 * 속도
		// 1초당 10만큼 이동한다.
		SetPos(Vector(_pos.x, _pos.y - (deltaTime * _speed)));
	}
	if (InputManager::GetInstance()->GetButtonPressed(KeyType::S))
	{
		SetPos(Vector(_pos.x, _pos.y + (deltaTime * _speed)));
	}
	if (InputManager::GetInstance()->GetButtonPressed(KeyType::A))
	{
		SetPos(Vector(_pos.x - (deltaTime * _speed), _pos.y));
	}
	if (InputManager::GetInstance()->GetButtonPressed(KeyType::D))
	{
		SetPos(Vector(_pos.x + (deltaTime * _speed), _pos.y));
	}
	if (InputManager::GetInstance()->GetButtonDown(KeyType::F2))
	{
		if (gameScene->IsDebug == true) {
			gameScene->IsDebug = false;
		}
		else {
			gameScene->IsDebug = true;
		}
	}
	if (InputManager::GetInstance()->GetButtonDown(KeyType::SpaceBar))
	{
		Shoot();
	}
	CheckGrid();
	CheckAttack();
	Vector camerapos= _pos;
	if (_pos.x < GWinSizeX / 2) {
		camerapos.x = (GWinSizeX / 2);
	}
	else if (_pos.x > GameScene::GetGameScene()->GetMapSizeX() - GWinSizeX / 2) {
		camerapos.x = (GameScene::GetGameScene()->GetMapSizeX() - GWinSizeX / 2);
	}
	if(_pos.y < GWinSizeY / 2)  {
		camerapos.y = (GWinSizeY / 2);
	}
	else if(_pos.y > GameScene::GetGameScene()->GetMapSizeY() - GWinSizeY / 2){
		camerapos.y = (GameScene::GetGameScene()->GetMapSizeY() - GWinSizeY / 2);
	}
	Camera::SetCameraPos(camerapos);
	if (_hp <= 0) {
		Destroy();
		gameScene->CreateExplosion(this->_pos,6,2,12);
	}
}

void Player::Render(HDC hdc) {
	if (_texture && _hp>0)
	{
		_texture->Render(hdc, _pos);
	}
	HPbar(hdc);
}

//void Player::CheckAttack() {
//	vector<Bullet*> bullet = gameScene->GetBullet();
//	for (auto it = bullet.begin(); it != bullet.end(); ) {
//		Vector pos = (*it)->GetPos();
//		if ((*it)->CanAttackMonster()) {
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

void Player::HPbar(HDC hdc) {
	if (_hptexture) {
		for (int i = 0; i < _hp; i++) {
			_hptexture->Render(hdc, Vector(Camera::GetCameraPos().x-(GWinSizeX/2)+(i*30)+30, Camera::GetCameraPos().y + (GWinSizeY / 2) - 50));
		}
	}
}
