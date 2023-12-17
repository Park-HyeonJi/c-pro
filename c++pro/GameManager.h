#pragma once
#include "DrawMap.h"

class GameManager
{
private:
	DrawMap m_DrawManager;
	Rect m_MapSize;
	int MainMenu();
	Position m_CenterPosition;

public:
	GameManager();
	~GameManager();

	void RunGame();
};

