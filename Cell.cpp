#include "pch.h"
#include "Cell.h"
#include "Actor.h"
#include "Camera.h"
void Cell::Init(int indexX, int indexY) {
	_indexX = indexX;
	_indexY = indexY;
    color = RGB(255, 0, 0);
}

void Cell::Update() {
    color = RGB(255, 0, 0);
}

void Cell::Render(HDC hdc) {
    // 셀의 월드 중심 위치 계산
    Vector worldPos = Vector(_indexX * 64 + 32, _indexY * 64 + 32); // 중심 좌표 (64는 셀 크기)
    Vector screenPos = Camera::ConvertWorldToScreen(worldPos);

    HPEN pen = ::CreatePen(PS_SOLID, 2, color);
    HPEN oldPen = (HPEN)::SelectObject(hdc, pen);

    HBRUSH brush = (HBRUSH)GetStockObject(NULL_BRUSH);
    HBRUSH oldbrush = (HBRUSH)::SelectObject(hdc, brush);

    // 중심 좌표 기준으로 사각형 그리기
    int half = 32; // 셀 크기 절반
    Rectangle(hdc,
        (int32)(screenPos.x - half),
        (int32)(screenPos.y - half),
        (int32)(screenPos.x + half),
        (int32)(screenPos.y + half)
    );

    ::SelectObject(hdc, oldPen);
    ::DeleteObject(pen);
    ::SelectObject(hdc, oldbrush);
    ::DeleteObject(brush);
}

void Cell::AddActorToCell(Actor* actor) {
    _actors.push_back(actor);
}

void Cell::RemoveActorFromCell(Actor* actor) {
    auto it = std::find(_actors.begin(), _actors.end(), actor);
    if (it != _actors.end()) {
        _actors.erase(it);
    }
}

void Cell::CheckActor() {
    color = RGB(255, 0, 0);
    for (auto it : _actors) {
        if ((it)->GetType() == Type::bullet || (it)->GetType() == Type::player) {
            color = RGB(0, 0, 255);
        }
    }
}