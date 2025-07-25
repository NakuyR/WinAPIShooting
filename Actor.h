#pragma once
enum Type {
	player,
	bullet,
	enemy,
	enemybullet
};

class Actor
{
public:
	Vector GetPos() { return _pos; };
	Type GetType() { return _actortype; };
protected:
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render(HDC hdc);
	void CheckGrid();
	void CheckAttack();
	void Destroy();
	void SetPos(Vector newpos);
	Vector _pos;
	int _hp;
	Type _actortype;
};

