#include "pch.h"
#include "ResourceManager.h"
#include "TextureResource.h"

void ResourceManager::Init()
{
    // 모~든 라인메시를 다 로드해서 가지고 있자.
    //플레이어
    {
        TextureResource* texture = new TextureResource();
        texture->Load(L"Resource\\Player.bmp", RGB(252, 0, 255));
        _textures["Player"] = texture;
    }
    //적1
    {
        TextureResource* texture = new TextureResource();
        texture->Load(L"Resource\\Enemy1.bmp", RGB(255, 0, 255));
        _textures["Enemy1"] = texture;
    } 
    //적2
    {
        TextureResource* texture = new TextureResource();
        texture->Load(L"Resource\\Enemy2.bmp",RGB(255, 0, 255));
        _textures["Enemy2"] = texture;
    }
    //적3
    {
        TextureResource* texture = new TextureResource();
        texture->Load(L"Resource\\Enemy3.bmp", RGB(255, 0, 255));
        _textures["Enemy3"] = texture;
    }
    //적4
    {
        TextureResource* texture = new TextureResource();
        texture->Load(L"Resource\\Enemy4.bmp", RGB(255, 0, 255));
        _textures["Enemy4"] = texture;
    }
    //적 총알
    {
        TextureResource* texture = new TextureResource();
        texture->Load(L"Resource\\EnemyBullet.bmp",RGB(252, 0, 255));
        _textures["EnemyBullet"] = texture;
    }
    //플레이어 총알
    {
        TextureResource* texture = new TextureResource();
        texture->Load(L"Resource\\PlayerBullet.bmp", RGB(252, 0, 255));
        _textures["PlayerBullet"] = texture;
    }
    //배경
    {
        TextureResource* texture = new TextureResource();
        texture->Load(L"Resource\\BG.bmp", RGB(252, 0, 255));
        _textures["Background"] = texture;
    }
    //배경
    {
        TextureResource* texture = new TextureResource();
        texture->Load(L"Resource\\Stage_2.bmp", RGB(252, 0, 255));
        _textures["Background2"] = texture;
    }
    //HP
    {
        TextureResource* texture = new TextureResource();
        texture->Load(L"Resource\\PlayerHP.bmp", RGB(252, 0, 255));
        _textures["HP"] = texture;
    }
    //이펙트
    {
        TextureResource* texture = new TextureResource();
        texture->Load(L"Resource\\explosion.bmp", RGB(0, 0, 0));
        _textures["Explosion"] = texture;
    }
}

void ResourceManager::Destroy()
{

    for (auto iter : _textures) 
    {
        delete iter.second;
    }
    _textures.clear();
}


TextureResource* ResourceManager::GetTexture(string meshName)
{
    // 전체적으로 관리하고 있는 모든 라인메시중에 meshName 해당하는 리소스를 반환한다.
    auto iter = _textures.find(meshName);
    if (iter != _textures.end())
    {
        return iter->second;
    }
    // 로딩이 안됐거나, 이름이 잘못됐거나
    return nullptr;
}
