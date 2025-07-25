#include "pch.h"
#include "Lobby.h"
#include "InputManager.h"
#include "Game.h"
#include "Background.h"

void Lobby::Update(float deltatTime){
	_background->Update(deltatTime);

	if (InputManager::GetInstance()->GetButtonDown(KeyType::LeftMouse))
	{
		POINT mousePos = InputManager::GetInstance()->GetMousePos();
		//if (조건문) {
		//로비 넘기기
		Game::GetInstance()->LoadScene(SceneType::GameScene);
		//}

	}

	
}

void Lobby::Destroy() {
	SAFE_DELETE(_background);
}

void Lobby::Render(HDC hdc) {

	_background->Render(hdc);

	wstring str = L"Shooting Game!";

	// 🔸기존 폰트를 백업하고 새 폰트 적용
	HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

	// 🔸텍스트 중앙 정렬 + 출력
	SetTextAlign(hdc, TA_CENTER);
	::TextOut(hdc, GWinSizeX / 2, GWinSizeY / 4, str.c_str(), static_cast<int32>(str.size()));
	SetTextAlign(hdc, TA_LEFT);

	// 🔸원래 폰트 복원 + 리소스 해제
	SelectObject(hdc, hOldFont);

}

void Lobby::Init() {

	_background = new Background();
	_background->Init();

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