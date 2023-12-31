#pragma once
#include "Mecro.h"
#include "MapDraw.h"
#include "Player.h"
#include "Enums.h"

#define DEFAULT_UNDOCOUNT 5

class GameManager
{
private:
	Player m_cPlayer1;
	Player m_cPlayer2;
	int m_iTurnCount;
	int m_iUndoCount;
	int m_iWidth;
	int m_iHeight;
	bool m_bIsPlaying;
	MARKLIST m_eStone;

	string GetStoneMarkForPlayer1(MARKLIST markList = MARKLIST_FIRST);
	string GetStoneMarkForPlayer2(MARKLIST markList = MARKLIST_FIRST);
	void ShowMainMenu();
	void OpenOptions();
	void ShowOptionMenu();
	void SetMapSize();
	void SetStone();
	void ShowStoneMenu();
	void Reset();
	void StartGame();
	void Playing();
	void SwapPlayer(Player** p1, Player** p2);
	void InputPlayerName();
	void DrawGameMap(int width, int height);
	void DrawPlayerStones();
	void ShowKeyInfo();
	void ShowPlayerInfo(Player* player);
	inline Stone GetCenterCoordinate()
	{
		return { m_iWidth / 2 , m_iHeight / 2 };
	}

public:
	GameManager();
	~GameManager() { }
	void OpenGame();
};
