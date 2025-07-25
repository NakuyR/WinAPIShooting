#pragma once
class Actor;

class Cell
{
public:
	void Update();
	void Init(int indexX, int indexY);
	void Render(HDC hdc);
	void AddActorToCell(Actor* actor);
	void RemoveActorFromCell(Actor* actor);
	vector<Actor*> GetActor() { return _actors; };
	void CheckActor();
	void SetColor(DWORD setcolor) { color = setcolor; };
	
private:
	DWORD color;
	int _indexX;
	int _indexY;
	vector<Actor*> _actors;
	
};

