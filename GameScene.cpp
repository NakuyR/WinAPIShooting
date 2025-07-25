#include "pch.h"
#include "GameScene.h"
#include "Bullet.h"
#include "Game.h"



void GameScene::Init() {
	_background = new Background();
	_background->Init();

	_fixedbackground = new FixedBackground(Vector(0, 0));
	_fixedbackground->Init();

	_mapSizeX = _fixedbackground->GetTextureWidth();
	_mapSizeY = _fixedbackground->GetTextureHeight();

	// 플레이어 생성
	Vector initPos = Vector(GetMapSizeX() / 2, GetMapSizeY() - 200);
	_player = new Player();
	_player->Init(initPos);
	_score = 0;
	// 적 생성

	
	for (int i = 1; i < 5; i++) {
		for (int j = 1; j < 5; j++) {
			Enemy* enemy = new Enemy();
			enemy->Init(i, Vector(j*100-i*20, i*100));
			_enemy.push_back(enemy);
		}
	}
	_grid = new Grid();
	_grid->Init();
	//Cell** cell = _grid->GetCell();
	//cell[2][2].AddCell(_player);
	

	
		//_background.push_back(bg);
	//{
	//	Background* bg = new Background();
	//	bg->Init();
	//	bg->SetPos(Vector((GWinSizeX) / 2, (-GWinSizeY) / 2));
	//	_background.push_back(bg);
	//}

	hFont = CreateFont(
		48,                // Height
		0,                 // Width (0이면 자동)
		0, 0,              // Escapement, Orientation
		FW_NORMAL,         // Weight (FW_BOLD 하면 두꺼워짐)
		FALSE, FALSE, FALSE, // Italic, Underline, StrikeOut
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		L"굴림"        // 폰트 이름
	);

}

void GameScene::Update(float deltaTime) {
	if (_grid != nullptr) {
		_grid->Update();
	}
	for (auto it : _enemy) {
		it->Update(deltaTime);
	}

	auto copyBullet = _bullet;
	for (auto it : copyBullet) {
		it->Update(deltaTime);
	}

	//for (auto it : _background) {
	//	it->Update(deltaTime);
	//}
	_background->Update(deltaTime);
	

	for (auto it : _explosion) {
		it->Update(deltaTime);
	}
	if (_enemy.empty()) {
		
	}
	else if (_player->GetHP() <= 0) {

	}
	else {
		_player->Update(deltaTime);
	}
	
}

void GameScene::Render(HDC hdc) {


	//for (auto it : _background) {
	//	it->Render(hdc);
	//}
	_background->Render(hdc);
	_fixedbackground->Render(hdc);
	for (auto it : _enemy) {
		it->Render(hdc);
	}

	for (auto it : _bullet) {
		it->Render(hdc);
	}

	for (auto it : _explosion) {
		it->Render(hdc);
	}
	if (_grid != nullptr && IsDebug == true) {
		_grid->Render(hdc);
	}
	if (_player) {
		_player->Render(hdc);
	}
	if (_enemy.empty()) {
		GameClear(hdc);
	}
	if (_player->GetHP() <= 0) {
		GameOver(hdc);

	}
	
	Score(hdc);
}

void GameScene::Destroy()
{
	SAFE_DELETE(_player);

	for (auto iter : _bullet)
	{
		delete iter;
	}
	_bullet.clear();
	for (auto iter : _enemy)
	{
		delete iter;
	}
	_enemy.clear();
	//for (auto iter : _background)
	//{
	//	delete iter;
	//}
	//_background.clear();
	SAFE_DELETE(_background);
	for (auto iter : _explosion)
	{
		delete iter;
	}
	_explosion.clear();
}


void GameScene::CreateBullet(Player * player) {
	Bullet* bullet = new Bullet();
	bullet->Init(player->GetPos());
	_bullet.push_back(bullet);
};
void GameScene::CreateBullet(Enemy* enemy) {
	Bullet* bullet = new Bullet();
	bullet->Init(enemy->GetPos(),enemy->_type);
	_bullet.push_back(bullet);
};

void GameScene::CreateExplosion(Vector pos,int maxxframe, int maxyframe, int maxframe) {
	Explosion* explosion = new Explosion();
	explosion->Init(pos, maxxframe, maxyframe, maxframe);
	_explosion.push_back(explosion);
};

void GameScene::RemoveBullet(Actor* bullet) {
	_grid->RemoveActorFromCell(bullet);

	auto it = std::find(_bullet.begin(), _bullet.end(), bullet);
	if (it != _bullet.end()) {
		_bullet.erase(it);
		SAFE_DELETE(bullet);
	}

	//SAFE_DELETE(bullet);
};

void GameScene::DestroyEnemy(Enemy* enemy) {
	_grid->RemoveActorFromCell(enemy);
	auto it = std::find(_enemy.begin(), _enemy.end(), enemy);
	_enemy.erase(it);

	SAFE_DELETE(enemy);
};
void GameScene::DestroyPlayer(Player* player) {
	_player = nullptr;
	SAFE_DELETE(player);
};

void GameScene::DestroyExplosion(Explosion* explosion) {
	auto it = std::find(_explosion.begin(), _explosion.end(), explosion);
	_explosion.erase(it);

	SAFE_DELETE(explosion);
};

void GameScene::GameClear(HDC hdc) {
	wstring str = L"Game Clear!";

	// 🔸기존 폰트를 백업하고 새 폰트 적용
	HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

	// 🔸텍스트 중앙 정렬 + 출력
	SetTextAlign(hdc, TA_CENTER);
	::TextOut(hdc, GWinSizeX / 2, GWinSizeY / 2, str.c_str(), static_cast<int32>(str.size()));
	SetTextAlign(hdc, TA_LEFT);

	// 🔸원래 폰트 복원 + 리소스 해제
	SelectObject(hdc, hOldFont);

}

void GameScene::GameOver(HDC hdc) {
	wstring str = L"Game Over!";

	// 🔸기존 폰트를 백업하고 새 폰트 적용
	HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

	// 🔸텍스트 중앙 정렬 + 출력
	SetTextAlign(hdc, TA_CENTER);
	::TextOut(hdc, GWinSizeX / 2, GWinSizeY / 2, str.c_str(), static_cast<int32>(str.size()));
	SetTextAlign(hdc, TA_LEFT);
	// 🔸원래 폰트 복원 + 리소스 해제
	SelectObject(hdc, hOldFont);
}

void GameScene::Score(HDC hdc) {
	wstring str = std::format(L"Score : {0}", _score);
	// 🔸텍스트 중앙 정렬 + 출력
	SetTextAlign(hdc, TA_CENTER);
	::TextOut(hdc, GWinSizeX / 2, 0, str.c_str(), static_cast<int32>(str.size()));
	SetTextAlign(hdc, TA_LEFT);
}

void GameScene::SetScore(int score) {
	_score = score;
}

GameScene* GameScene::GetGameScene()
{
	return dynamic_cast<GameScene*>(Game::GetInstance()->GetCurrScene());
}