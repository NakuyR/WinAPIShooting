#pragma once
#include "Cell.h"

class Grid 
{
	
public:
	void Update();
	int _sizeX;
	int _sizeY;
	void Init();
	void Render(HDC hdc);
	int CheckIndex(float pos);
	Cell** GetCell() { return _cell; };
	void GetCellIndex(class Actor* actor, Vector curpos, Vector prevpos);
	Cell* GetCellByIndex(int x, int y) { return &(_cell[x][y]); };
	void RemoveActorFromCell(class Actor* actor);
private:
	int _cellsize;
	Cell** _cell;
	
};

