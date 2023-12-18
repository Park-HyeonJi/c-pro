#pragma once
#include "Mecro.h"
#include "MapDraw.h"
#include "Enums.h"

#define VICTORY 5

struct Stone
{
	int m_iX;
	int m_iY;
};

class Player
{
private:
	string m_strName;
	string m_strStone;
	int m_iMapWidht;
	int m_iMapHeight;
	Stone m_sCursorCoord;
	list<Stone> m_listHistory;
	list<Stone> m_listReplayHistory;

	int CalculateStones(int x, int y, DIR dir = DIR_START);
	int GetDirX(DIR dir);
	int GetDirY(DIR dir);
	bool CheckStoneCoordinate(Stone coord);
	bool FindStone(int x, int y);
	bool CanPlayGo(Stone coord);
	void DrawStone(Stone coord);
	void ConvertStringToList(string history);

	inline bool CheckStoneList()
	{
		return m_listHistory.size() > 0;
	}

public:
	Player() { }
	Player(string stone, Stone coord, int width, int height, string name = "", string history = "");
	~Player() { }
	INPUTKEY Playing(Player* opponent);
	string GetHistoryString();
	string GetReplayHistoryString();
	bool CheckVictory();
	void MovePoint(Player* opponent);
	void DrawHistory();
	void Reset(Stone coord, int width, int height);

	inline string GetPlayerName()
	{
		return m_strName;
	}
	inline void SetPlayerName(string name)
	{
		m_strName = name;
	}
	inline void ChangeStoneMark(string stone)
	{
		m_strStone = stone;
	}
};
