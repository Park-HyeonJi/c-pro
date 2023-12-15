#pragma once
#include "DrawMap.h"

class GameManager
{
private:
	DrawMap m_DrawManager;
	Rect m_MapSize;

public:
	GameManager();
	~GameManager();

	void RunGame();
};

