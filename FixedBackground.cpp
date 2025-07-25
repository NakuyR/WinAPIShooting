#include "pch.h"
#include "FixedBackground.h"
#include "ResourceManager.h"
#include "TextureResource.h"

FixedBackground::FixedBackground(Vector pos) {
	_pos = pos;
	_texture = ResourceManager::GetInstance()->GetTexture("Background2");
}

void FixedBackground::Init()
{
	Actor::Init();
}

void FixedBackground::Update(float deltaTime)
{
	Actor::Update(deltaTime);
}

void FixedBackground::Render(HDC hdc)
{
	if (_texture)
	{

			_texture->RenderMap(hdc, _pos);

	}
}	

int32 FixedBackground::GetTextureWidth() {
	if (_texture) {
		return _texture->_sizeX;
	}
	else {
		return GWinSizeX;
	}
}

int32 FixedBackground::GetTextureHeight() {
	if (_texture) {
		return _texture->_sizeY;
	}
	else {
		return GWinSizeX;
	}
}