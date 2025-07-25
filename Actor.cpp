#include "pch.h"
#include "Actor.h"
#include "Grid.h"
#include "GameScene.h"

void Actor::SetPos(Vector newpos) {
	Vector curpos = _pos;
	if (_actortype == Type::player) {
		if (newpos.x<25 || newpos.x>GameScene::GetGameScene()->GetMapSizeX() - 25) {
			return;
		}
		if (newpos.y<25 || newpos.y>GameScene::GetGameScene()->GetMapSizeY() - 25) {
			return;
		}
	}
	_pos = newpos;
	GameScene::GetGameScene()->GetGrid()->GetCellIndex(this, curpos, _pos);
}

void Actor::Destroy() {
	GameScene::GetGameScene()->GetGrid()->RemoveActorFromCell(this);
}

void Actor::CheckAttack() {
	int Xindex = GameScene::GetGameScene()->GetGrid()->CheckIndex(_pos.x);
	int Yindex = GameScene::GetGameScene()->GetGrid()->CheckIndex(_pos.y);
	//디버그용

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (Xindex + i < 0 || Yindex + j <0 || Xindex + i >= GameScene::GetGameScene()->GetGrid()->_sizeX || Yindex + j >= GameScene::GetGameScene()->GetGrid()->_sizeY) {
				continue;
			}
			vector<Actor*> actors = GameScene::GetGameScene()->GetGrid()->GetCellByIndex(Xindex+i, Yindex+j)->GetActor();
			for (auto it = actors.begin(); it != actors.end(); ) {
				Vector pos = (*it)->GetPos();
				if ((*it)->_actortype==Type::bullet&&_actortype==Type::enemy) {
					if (pos.x <= _pos.x + 25 && pos.x >= _pos.x - 25 && pos.y <= _pos.y + 25 && pos.y >= _pos.y - 25) {
						GameScene::GetGameScene()->RemoveBullet(*it);
						_hp--;
					}
					else {
						it++;
					}
				}
				else if ((*it)->_actortype == Type::enemybullet && _actortype == Type::player) {
					if (pos.x <= _pos.x + 25 && pos.x >= _pos.x - 25 && pos.y <= _pos.y + 25 && pos.y >= _pos.y - 25) {
						GameScene::GetGameScene()->RemoveBullet(*it);
						_hp--;
					}
					else {
						it++;
					}
				}
				else {
					it++;
				}
			}
		}
	}
}

void Actor::CheckGrid() {
	int Xindex = GameScene::GetGameScene()->GetGrid()->CheckIndex(_pos.x);
	int Yindex = GameScene::GetGameScene()->GetGrid()->CheckIndex(_pos.y);
	//디버그용
	if (_actortype == Type::bullet || _actortype == Type::player) {
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				if (Xindex + i < 0 || Yindex + j < 0 || Xindex + i >= GameScene::GetGameScene()->GetGrid()->_sizeX || Yindex + j >= GameScene::GetGameScene()->GetGrid()->_sizeY) {
					continue;
				}
				else {
					GameScene::GetGameScene()->GetGrid()->GetCellByIndex(Xindex + i, Yindex + j)->SetColor(RGB(0, 0, 255));
				}

			}
		}
	}
}

void Actor::Init() {

}

void Actor::Render(HDC hdc) {

}
void Actor::Update(float deltaTime) {

}