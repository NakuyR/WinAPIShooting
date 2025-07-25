#pragma once
#include "Singleton.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#include "Background.h"
#include "Explosion.h"
#include "Scene.h"
#include "Grid.h"
#include "Cell.h"
#include "Actor.h"
#include "FixedBackground.h"

class GameScene : public Scene
{

public:
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update(float deltatTime) override;
	virtual void Render(HDC hdc) override;
	void CreateBullet(Player* player);
	void CreateBullet(Enemy* enemy);
	void RemoveBullet(Actor* bullet);
	void DestroyEnemy(Enemy* enemy);
	void CreateExplosion(Vector pos, int maxxframe, int maxyframe, int maxframe);
	void DestroyExplosion(Explosion* explosion);
	void DestroyPlayer(Player* player);
	void GameOver(HDC hdc);
	void GameClear(HDC hdc);
	void Score(HDC hdc);
 	int GetScore() { return _score; };
	void SetScore(int score);
	Grid* GetGrid() { return _grid; };
	Background* GetBackground() { return _background; };
	vector<Bullet*> GetBullet() { return _bullet; };
	static GameScene* GetGameScene();
	bool IsDebug = false;
private:
	
	Player* _player = nullptr;
	vector<Enemy*> _enemy;
	vector<Bullet*> _bullet;
	Background* _background;
	FixedBackground* _fixedbackground;
	vector<Explosion*> _explosion;
	int _score = 0;
	HFONT hFont;
	Grid* _grid;
	
};

