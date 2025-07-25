#include "pch.h"
#include "TextureResource.h"
#include "Game.h"
#include "Camera.h"

void TextureResource::Load(wstring fileName, int32 alpha)
{
	// WinAPI 텍스처 로딩하는 방법
	{
		fs::path fullPath = fs::current_path() / fileName;

		HDC hdc = ::GetDC(Game::GetInstance()->GetHwnd());

		_textureHdc = ::CreateCompatibleDC(hdc);
		_bitmap = (HBITMAP)::LoadImageW(
			nullptr,
			fullPath.c_str(),
			IMAGE_BITMAP,
			0,
			0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION
		);
		if (_bitmap == 0)
		{
			::MessageBox(Game::GetInstance()->GetHwnd(), fullPath.c_str(), L"Invalid Texture Load", MB_OK);
			return;
		}

		_transparent = alpha;

		HBITMAP prev = (HBITMAP)::SelectObject(_textureHdc, _bitmap);
		::DeleteObject(prev);

		BITMAP bit = {};
		::GetObject(_bitmap, sizeof(BITMAP), &bit);

		_sizeX = bit.bmWidth;
		_sizeY = bit.bmHeight;
	}
}


void TextureResource::Render(HDC hdc, Vector pos)
{
	Vector screenPos = Camera::ConvertWorldToScreen(pos);

	if (_transparent == -1)
	{
		::BitBlt(hdc,	// 백버퍼에
			(int32)screenPos.x - (_sizeX / 2),	// 텍스처를 중심좌표로 그리기위해 size의 절반만큼 빼준다.
			(int32)screenPos.y - (_sizeY / 2),
			_sizeX,
			_sizeY,
			_textureHdc,	// 텍스쳐 그리기
			0,
			0,
			SRCCOPY);
	}
	else
	{
		::TransparentBlt(hdc,
			(int32)screenPos.x - (_sizeX / 2),
			(int32)screenPos.y - (_sizeY / 2),
			_sizeX,
			_sizeY,
			_textureHdc,
			0,
			0,
			_sizeX,
			_sizeY,
			_transparent);	// 어떤색상을 투명하게 그릴까
	}

}


void TextureResource::Render(HDC hdc, Vector pos, int Yframe,int Xframe, int framesize)
{
	Vector screenPos = Camera::ConvertWorldToScreen(pos);
	{
		::TransparentBlt(hdc,
			(int32)screenPos.x - framesize/2,
			(int32)screenPos.y - framesize/2,
			framesize,
			framesize,
			_textureHdc,
			Xframe * framesize,
			Yframe * framesize,
			framesize,
			framesize,
			_transparent);
	}
}

//테스트용
void TextureResource::RenderMap(HDC hdc, Vector pos)
{
	Vector _camerapos = Camera::GetCameraPos();
	{
		::BitBlt(hdc,	// 백버퍼에
			//(int32)pos.x - (size.x / 2),	// 텍스처를 중심좌표로 그리기위해 size의 절반만큼 빼준다.
			//(int32)pos.y - (size.y / 2),
			0,
			0,
			/*size.x,
			size.y,*/
			GWinSizeX,
			GWinSizeY,
			_textureHdc,	// 텍스쳐 그리기
			_camerapos.x-(GWinSizeX/2),
			_camerapos.y - (GWinSizeY / 2),
			SRCCOPY);
	}

}