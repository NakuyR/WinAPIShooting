#pragma once
#include "Scene.h"

class Lobby : public Scene
{
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update(float deltatTime) override;
	virtual void Render(HDC hdc) override;
	//파일 불러오기
	//버튼클릭
	//버튼생성
private:
	//버튼
	//스코어
	//백그라운드
	class Background* _background;
	HFONT hFont;
};

