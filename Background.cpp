#include "pch.h"
#include "Background.h"
#include "TextureResource.h"
#include "ResourceManager.h"
#include "Game.h"

void Background::Move() {

};

void Background::Init() {
	_pos = Vector(0, GWinSizeY / 2);
	_texture = ResourceManager::GetInstance()->GetTexture("Background");

}
void Background::Render(HDC hdc) {
	if (_texture)
	{
		if (_pos.y > GWinSizeY * 0.5f) {
			_texture->Render(hdc, _pos);
			_texture->Render(hdc, _pos-Vector(0, GWinSizeY));
		}
		else {
			_texture->Render(hdc, _pos);
			_texture->Render(hdc, _pos + Vector(0, GWinSizeY));
		}
	}
}
void Background::Update(float deltaTime) {
	_pos.y += speed * deltaTime;
	if (_pos.y > GWinSizeY * 1.5f) {
		_pos.y -= GWinSizeY*2;
	}
}

void Background::SetPos(Vector pos) {
	_pos = pos;
}