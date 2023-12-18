#include "GameManager.h"

GameManager::GameManager()
{
		m_iWidth = MAPRANGE_WIDTH_MIN;
		m_iHeight = MAPRANGE_HEIGHT_MIN;
		m_iTurnCount = 1;
		m_iUndoCount = DEFAULT_UNDOCOUNT;
		m_bIsPlaying = false;
		m_eStone = MARKLIST_FIRST;
		m_cPlayer1 = Player(GetStoneMarkForPlayer1(), GetCenterCoordinate(), m_iWidth, m_iHeight);
		m_cPlayer2 = Player(GetStoneMarkForPlayer2(), GetCenterCoordinate(), m_iWidth, m_iHeight);
	
}

string GameManager::GetStoneMarkForPlayer1(MARKLIST markList)
{
	switch (markList)
	{
	case MARKLIST_FIRST:
		return "○";
	case MARKLIST_SECOND:
		return "♡";
	case MARKLIST_THIRD:
		return "□";
	case MARKLIST_FOURTH:
		return "①";
	}
}

string GameManager::GetStoneMarkForPlayer2(MARKLIST markList)
{
	switch (markList)
	{
	case MARKLIST_FIRST:
		return "●";
	case MARKLIST_SECOND:
		return "♥";
	case MARKLIST_THIRD:
		return "■";
	case MARKLIST_FOURTH:
		return "②";
	}
}


void GameManager::Reset()
{
	m_bIsPlaying = false;
	m_iTurnCount = 1;
	
	m_cPlayer1 = Player(GetStoneMarkForPlayer1(m_eStone), GetCenterCoordinate(), m_iWidth, m_iHeight);
	m_cPlayer2 = Player(GetStoneMarkForPlayer2(m_eStone), GetCenterCoordinate(), m_iWidth, m_iHeight);
}

void GameManager::OpenGame()
{
	while (true)
	{
		system("cls");
		MapDraw::DrawMap(m_iWidth, m_iHeight);
		ShowMainMenu();

		int label;
		cin >> label;
		switch (label)
		{
		case MAINMENU_START_GAME:
			StartGame();
			break;
		case MAINMENU_OPTIONS:
			OpenOptions();
			break;
		case MAINMENU_CLOSE:
			return;
		default:
		{
			int startY = m_iHeight;
			MapDraw::ShowString("지정된 메뉴의 번호만 입력해주세요.", m_iWidth, startY++);
			MapDraw::ShowString("번호를 다시 입력하고 싶다면", m_iWidth, startY++);
			MapDraw::ShowString("BackSpace 버튼을 눌러주세요.", m_iWidth, startY);
			if (_getch()) {}
		}
		}

	}
}

void GameManager::ShowMainMenu()
{
	int startX = m_iWidth / 2;
	int startY = m_iHeight / 4;
	int yInterval = m_iHeight / 10;
	MapDraw::ShowString("● 오 목 ○", m_iWidth, startY);
	startY += yInterval;
	MapDraw::ShowString("1.게임 시작", m_iWidth, startY);
	startY += yInterval;
	MapDraw::ShowString("2.옵션 설정", m_iWidth, startY);
	startY += yInterval;
	MapDraw::ShowString("3.게임 종료", m_iWidth, startY);
	startY += yInterval;
	MapDraw::DrawBox(startX, startY, startX, 3);
	MapDraw::Gotoxy(m_iWidth , startY + 1);

}

void GameManager::StartGame()
{
	//플레이어 이름 입력
	InputPlayerName();

	//게임 시작
	system("cls");
	m_bIsPlaying = true;
	DrawGameMap(m_iWidth, m_iHeight);
	m_cPlayer1.DrawHistory();
	m_cPlayer2.DrawHistory();
	ShowKeyInfo();
	Playing();
}

void GameManager::Playing()
{
	bool isPlayer1Turn = m_iTurnCount % 2 == 1;
	Player* controlPlayer = isPlayer1Turn ? &m_cPlayer1 : &m_cPlayer2;
	Player* opponentPlayer = isPlayer1Turn ? &m_cPlayer2 : &m_cPlayer1;

	ShowPlayerInfo(controlPlayer);

	while (true)
	{
		switch (controlPlayer->Playing(opponentPlayer))
		{
		case INPUTKEY_ENTER:
			if (controlPlayer->CheckVictory())
			{
				int startY = m_iHeight / 2;
				MapDraw::ShowString(controlPlayer->GetPlayerName() + " 플레이어 승리!!", m_iWidth, startY);
				MapDraw::ShowString("\n게임을 다시 시작하고 싶으면\nESC를 눌러서 재시작하세요!", m_iWidth, startY);
				if (_getch()) {}
				Reset();
				return;
			}
			else
			{
				m_iTurnCount++;
				SwapPlayer(&controlPlayer, &opponentPlayer);
				ShowPlayerInfo(controlPlayer);
			}
			break;
		case INPUTKEY_UNDO:
			m_iTurnCount--;
			SwapPlayer(&controlPlayer, &opponentPlayer);
			ShowPlayerInfo(controlPlayer);
			break;
		case INPUTKEY_OPTION:
			OpenOptions();
			DrawGameMap(m_iWidth, m_iHeight);
			ShowKeyInfo();
			ShowPlayerInfo(controlPlayer);
			opponentPlayer->DrawHistory();
			controlPlayer->DrawHistory();
			break;
		case INPUTKEY_ESC:
				Reset();
			return;
		}
	}
}

void GameManager::SwapPlayer(Player** p1, Player** p2)
{
	Player* temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}

void GameManager::InputPlayerName()
{
	MapDraw::DrawBox(0, 0, m_iWidth, m_iHeight);

	string name;
	int startY = m_iHeight / 3;
	MapDraw::ShowString("P1 이름", m_iWidth, startY);
	MapDraw::ShowString("입력 : ", m_iWidth, startY + 1);
	cin >> name;
	m_cPlayer1.SetPlayerName(name);

	startY = m_iHeight / 2;
	MapDraw::ShowString("P2 이름", m_iWidth, startY);
	MapDraw::ShowString("입력 : ", m_iWidth, startY + 1);
	cin >> name;
	m_cPlayer2.SetPlayerName(name);
}

void GameManager::DrawGameMap(int width, int height)
{
	system("cls");
	MapDraw::DrawMap(width, height);
}

void GameManager::DrawPlayerStones()
{
	m_cPlayer1.DrawHistory();
	m_cPlayer2.DrawHistory();
}

void GameManager::ShowKeyInfo()
{
	int startY = m_iHeight;
	MapDraw::ShowString("====조작키====", m_iWidth, startY++);
	MapDraw::ShowString("이동 : ← ↑ ↓ → 돌 놓기 : ENTER", m_iWidth, startY++);
	MapDraw::ShowString("옵션 : P // 메인 메뉴 : ESC", m_iWidth, startY++);
}

void GameManager::ShowPlayerInfo(Player* player)
{
	int startY = m_iHeight + 3;
	MapDraw::ShowString(" 현재 플레이어 : " + player->GetPlayerName(), m_iWidth, startY++);
	MapDraw::ShowString(" Turn : " + to_string(m_iTurnCount) + " ", m_iWidth, startY);
}

void GameManager::OpenOptions()
{
	while (true)
	{
		MapDraw::DrawBox(0, 0, m_iWidth, m_iHeight);
		ShowOptionMenu();

		int label;
		cin >> label;
		switch (label)
		{
		case OPTIONS_SIZE:
			SetMapSize();
			break;
		case OPTIONS_STONE:
			SetStone();
			break;
		case OPTIONS_END:
			return;
		}
	}
}

void GameManager::ShowOptionMenu()
{
	int startY = m_iHeight / 5;
	int yInterval = m_iHeight / 10;
	MapDraw::ShowString("= 옵션 =", m_iWidth, startY);
	startY += yInterval;
	MapDraw::ShowString("1.오목판 크기 정하기", m_iWidth, startY);
	startY += yInterval;
	MapDraw::ShowString("2.커서 및 돌 커스텀", m_iWidth, startY);
	startY += yInterval;
	MapDraw::ShowString("3.돌아가기", m_iWidth, startY);
	startY += yInterval;
	MapDraw::ShowString("입력 : ", m_iWidth, startY);
}

void GameManager::SetMapSize()
{
	while (true)
	{
		MapDraw::DrawBox(0, 0, m_iWidth, m_iHeight);

		int width, height;
		int startY = m_iHeight / 2.5f;
		int yInterval = m_iHeight / 5;
		MapDraw::ShowString("가로 칸 : ", m_iWidth, startY);
		cin >> width;
		MapDraw::ShowString("세로 칸 : ", m_iWidth, startY + yInterval);
		cin >> height;

		if (width >= MAPRANGE_WIDTH_MIN && width <= MAPRANGE_WIDTH_MAX
			&& height >= MAPRANGE_HEIGHT_MIN && height <= MAPRANGE_HEIGHT_MAX)
		{
			m_iWidth = width;
			m_iHeight = height;

			system("cls");
			return;
		}
		else
		{
			MapDraw::DrawBox(0, 0, m_iWidth, m_iHeight);

			yInterval = m_iHeight / 10;
			string str = "(가로 : " + to_string(MAPRANGE_WIDTH_MIN) + " ~" + to_string(MAPRANGE_WIDTH_MAX) + ", 세로 : "
				+ to_string(MAPRANGE_HEIGHT_MIN) + " ~ " + to_string(MAPRANGE_HEIGHT_MAX) + ")";
			MapDraw::ShowString("변경 불가능", m_iWidth, startY);
			MapDraw::ShowString(str, m_iWidth, startY + yInterval);

			MapDraw::Gotoxy(0, m_iHeight);
			if (_getch()) {}
		}
	}
}


void GameManager::SetStone()
{
	while (true)
	{
		MapDraw::DrawBox(0, 0, m_iWidth, m_iHeight);
		ShowStoneMenu();
		int label;
		cin >> label;

		switch (label)
		{
		case MARKLIST_FIRST:
		case MARKLIST_SECOND:
		case MARKLIST_THIRD:
		case MARKLIST_FOURTH:
			m_eStone = (MARKLIST)label;
			m_cPlayer1.ChangeStoneMark(GetStoneMarkForPlayer1(m_eStone));
			m_cPlayer2.ChangeStoneMark(GetStoneMarkForPlayer2(m_eStone));
			system("pause");
			return;
		case MARKLIST_END:
			return;
		}
	}
}

void GameManager::ShowStoneMenu()
{
	int startY = m_iHeight / 5;
	int yInterval = m_iHeight / 10;
	MapDraw::ShowString("= 돌 모양 고르기 =", m_iWidth, startY);
	startY += yInterval;
	MapDraw::ShowString(
		"1." + GetStoneMarkForPlayer1(MARKLIST_FIRST) + "," + GetStoneMarkForPlayer2(MARKLIST_FIRST),
		m_iWidth, startY);
	startY += yInterval;
	MapDraw::ShowString(
		"2." + GetStoneMarkForPlayer1(MARKLIST_SECOND) + "," + GetStoneMarkForPlayer2(MARKLIST_SECOND),
		m_iWidth, startY);
	startY += yInterval;
	MapDraw::ShowString(
		"3." + GetStoneMarkForPlayer1(MARKLIST_THIRD) + "," + GetStoneMarkForPlayer2(MARKLIST_THIRD),
		m_iWidth,
		startY);
	startY += yInterval;
	MapDraw::ShowString(
		"4." + GetStoneMarkForPlayer1(MARKLIST_FOURTH) + "," + GetStoneMarkForPlayer2(MARKLIST_FOURTH),
		m_iWidth, startY);
	startY += yInterval;
	MapDraw::ShowString("5.돌아가기", m_iWidth, startY);
	startY += yInterval;
	MapDraw::ShowString("입력 : ", m_iWidth, startY);
}