#include "pch.h"
#include "Grid.h"
#include "Cell.h"
#include "Actor.h"
#include "GameScene.h"
#include <cmath>

void Grid::Init() {
    //1칸당 사이즈
    _cellsize = 64;
    //셀 사이즈로 나눈 후 올림처리

    _sizeX = ceil((float)GameScene::GetGameScene()->GetMapSizeX()/ _cellsize);
    _sizeY = ceil((float)GameScene::GetGameScene()->GetMapSizeY() / _cellsize);

    _cell = new Cell*[_sizeX]; // 행
    for (int i = 0; i < _sizeX; ++i) {
        _cell[i] = new Cell[_sizeY]; // 열   
    }

    for (int i = 0; i < _sizeX; ++i) {
        for (int j = 0; j < _sizeY; ++j) {
            _cell[i][j].Init(i,j); // 열
        }
    }
}

void Grid::Render(HDC hdc) {
    for (int i = 0; i < _sizeX; ++i) {
        for (int j = 0; j < _sizeY; ++j) {
            _cell[i][j].Render(hdc); // 열
        }
    }   
}
void Grid::Update() {
    for (int i = 0; i < _sizeX; ++i) {
        for (int j = 0; j < _sizeY; ++j) {
            _cell[i][j].Update(); // 열
        }
    }
}

void Grid::GetCellIndex(class Actor* actor, Vector prevpos, Vector curpos) {
    int previndexX = (prevpos.x / _cellsize);
    int previndexY = (prevpos.y / _cellsize);
    int curindexX = (curpos.x / _cellsize);
    int curindexY = (curpos.y / _cellsize);
    if (previndexX == curindexX && previndexY == curindexY) {
        return;
    }
    else {
        _cell[(int)previndexX][(int)previndexY].RemoveActorFromCell(actor);
        _cell[(int)curindexX][(int)curindexY].AddActorToCell(actor);
    }
}

void Grid::RemoveActorFromCell(Actor* actor) {
    Vector pos = actor->GetPos();
    int indexX = CheckIndex(pos.x);
    int indexY = CheckIndex(pos.y);
     _cell[(int)indexX][(int)indexY].RemoveActorFromCell(actor);
}
    
int Grid::CheckIndex(float pos) {
    return (int)(pos / _cellsize);
}