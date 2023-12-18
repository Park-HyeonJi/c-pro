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
		return "��";
	case MARKLIST_SECOND:
		return "��";
	case MARKLIST_THIRD:
		return "��";
	case MARKLIST_FOURTH:
		return "��";
	}
}

string GameManager::GetStoneMarkForPlayer2(MARKLIST markList)
{
	switch (markList)
	{
	case MARKLIST_FIRST:
		return "��";
	case MARKLIST_SECOND:
		return "��";
	case MARKLIST_THIRD:
		return "��";
	case MARKLIST_FOURTH:
		return "��";
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
			MapDraw::ShowString("������ �޴��� ��ȣ�� �Է����ּ���.", m_iWidth, startY++);
			MapDraw::ShowString("��ȣ�� �ٽ� �Է��ϰ� �ʹٸ�", m_iWidth, startY++);
			MapDraw::ShowString("BackSpace ��ư�� �����ּ���.", m_iWidth, startY);
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
	MapDraw::ShowString("�� �� �� ��", m_iWidth, startY);
	startY += yInterval;
	MapDraw::ShowString("1.���� ����", m_iWidth, startY);
	startY += yInterval;
	MapDraw::ShowString("2.�ɼ� ����", m_iWidth, startY);
	startY += yInterval;
	MapDraw::ShowString("3.���� ����", m_iWidth, startY);
	startY += yInterval;
	MapDraw::DrawBox(startX, startY, startX, 3);
	MapDraw::Gotoxy(m_iWidth , startY + 1);

}

void GameManager::StartGame()
{
	//�÷��̾� �̸� �Է�
	InputPlayerName();

	//���� ����
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
				MapDraw::ShowString(controlPlayer->GetPlayerName() + " �÷��̾� �¸�!!", m_iWidth, startY);
				MapDraw::ShowString("\n������ �ٽ� �����ϰ� ������\nESC�� ������ ������ϼ���!", m_iWidth, startY);
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
	MapDraw::ShowString("P1 �̸�", m_iWidth, startY);
	MapDraw::ShowString("�Է� : ", m_iWidth, startY + 1);
	cin >> name;
	m_cPlayer1.SetPlayerName(name);

	startY = m_iHeight / 2;
	MapDraw::ShowString("P2 �̸�", m_iWidth, startY);
	MapDraw::ShowString("�Է� : ", m_iWidth, startY + 1);
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
	MapDraw::ShowString("====����Ű====", m_iWidth, startY++);
	MapDraw::ShowString("�̵� : �� �� �� �� �� ���� : ENTER", m_iWidth, startY++);
	MapDraw::ShowString("�ɼ� : P // ���� �޴� : ESC", m_iWidth, startY++);
}

void GameManager::ShowPlayerInfo(Player* player)
{
	int startY = m_iHeight + 3;
	MapDraw::ShowString(" ���� �÷��̾� : " + player->GetPlayerName(), m_iWidth, startY++);
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
	MapDraw::ShowString("= �ɼ� =", m_iWidth, startY);
	startY += yInterval;
	MapDraw::ShowString("1.������ ũ�� ���ϱ�", m_iWidth, startY);
	startY += yInterval;
	MapDraw::ShowString("2.Ŀ�� �� �� Ŀ����", m_iWidth, startY);
	startY += yInterval;
	MapDraw::ShowString("3.���ư���", m_iWidth, startY);
	startY += yInterval;
	MapDraw::ShowString("�Է� : ", m_iWidth, startY);
}

void GameManager::SetMapSize()
{
	while (true)
	{
		MapDraw::DrawBox(0, 0, m_iWidth, m_iHeight);

		int width, height;
		int startY = m_iHeight / 2.5f;
		int yInterval = m_iHeight / 5;
		MapDraw::ShowString("���� ĭ : ", m_iWidth, startY);
		cin >> width;
		MapDraw::ShowString("���� ĭ : ", m_iWidth, startY + yInterval);
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
			string str = "(���� : " + to_string(MAPRANGE_WIDTH_MIN) + " ~" + to_string(MAPRANGE_WIDTH_MAX) + ", ���� : "
				+ to_string(MAPRANGE_HEIGHT_MIN) + " ~ " + to_string(MAPRANGE_HEIGHT_MAX) + ")";
			MapDraw::ShowString("���� �Ұ���", m_iWidth, startY);
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
	MapDraw::ShowString("= �� ��� ���� =", m_iWidth, startY);
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
	MapDraw::ShowString("5.���ư���", m_iWidth, startY);
	startY += yInterval;
	MapDraw::ShowString("�Է� : ", m_iWidth, startY);
}