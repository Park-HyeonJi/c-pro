#include "GameManager.h"

GameManager::GameManager() {
	m_MapSize.left = 0;
	m_MapSize.right = WIDTH;
	m_MapSize.top = 0;
	m_MapSize.bottom = HEIGHT;

	//아스키코드는 2칸 차지, 바둑판의 실제 너비는 원래 너비의 2배
	//센터 위치는 지정 너비와 같음
	m_CenterPosition.x = m_MapSize.right*0.5f;
	//y는 세로 길이를 반으로 나눈 위치
	m_CenterPosition.x = m_MapSize.right*0.5f;
}

void GameManager::RunGame() {
	m_DrawManager.GridDraw(0,0,m_MapSize.right, m_MapSize.bottom);
	MainMenu();
}

int GameManager::MainMenu() {
	int iSelect;
	m_DrawManager.DrawMidText("[ 오목 ]", m_CenterPosition.x, m_CenterPosition.y * 0.5f);
	m_DrawManager.DrawMidText("1. 게임 시작", m_CenterPosition.x, m_CenterPosition.y * 0.7f);
	m_DrawManager.DrawMidText("2. 옵션 설정", m_CenterPosition.x, m_CenterPosition.y * 0.9f);
	m_DrawManager.DrawMidText("3. 게임 종료", m_CenterPosition.x, m_CenterPosition.y * 1.1f);
	m_DrawManager.BoxDraw(m_CenterPosition.x * 0.5f, m_CenterPosition.y * 1.3f, 10, 3);
	m_DrawManager.gotoxy(m_CenterPosition.x, m_CenterPosition.y * 1.4f);
	cin >> iSelect;

	return iSelect;
}

GameManager::~GameManager() {

}