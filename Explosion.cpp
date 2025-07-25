#include "pch.h"
#include "Explosion.h"
#include "GameScene.h"
#include "TextureResource.h"
#include "ResourceManager.h"
#include "Game.h"


void Explosion::Init(Vector pos,int maxxframe, int maxyframe, int maxframe) {
	_texture = ResourceManager::GetInstance()->GetTexture("Explosion");
	_curframe = 1;
	_curtime = 0;
	_Maxframe = maxframe;
	_MaxXframe = maxxframe;
	_MaxYframe = maxyframe;
	_animspeed = 0.1f;
	_pos = pos;
}

void Explosion::Update(float deltaTime) {
	GameScene* gameScene = GameScene::GetGameScene();
	if (gameScene == nullptr)
		return;

	_curtime += deltaTime;
	if (_curtime > _animspeed) {
		_curtime = 0;
		_curframe += 1;
		_Yframe = _curframe /_MaxXframe;
		_Xframe = _curframe % _MaxXframe;
	}
	if (_curframe > _Maxframe) {
		gameScene->DestroyExplosion(this);
	}
}

void Explosion::Render(HDC hdc) {
	if (_texture) {
		_texture->Render(hdc, _pos, _Yframe, _Xframe, 64);
		//_texture->Render(hdc, _pos);
	}
	else {
		fs::path fullPath = fs::current_path();
		::MessageBox(Game::GetInstance()->GetHwnd(), fullPath.c_str(), L"Invalid Texture Load", MB_OK);
	}
}