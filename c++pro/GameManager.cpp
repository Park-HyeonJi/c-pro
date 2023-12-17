#include "GameManager.h"

GameManager::GameManager() {
	m_MapSize.left = 0;
	m_MapSize.right = WIDTH;
	m_MapSize.top = 0;
	m_MapSize.bottom = HEIGHT;

	//�ƽ�Ű�ڵ�� 2ĭ ����, �ٵ����� ���� �ʺ�� ���� �ʺ��� 2��
	//���� ��ġ�� ���� �ʺ�� ����
	m_CenterPosition.x = m_MapSize.right*0.5f;
	//y�� ���� ���̸� ������ ���� ��ġ
	m_CenterPosition.x = m_MapSize.right*0.5f;
}

void GameManager::RunGame() {
	m_DrawManager.GridDraw(0,0,m_MapSize.right, m_MapSize.bottom);
	MainMenu();
}

int GameManager::MainMenu() {
	int iSelect;
	m_DrawManager.DrawMidText("[ ���� ]", m_CenterPosition.x, m_CenterPosition.y * 0.5f);
	m_DrawManager.DrawMidText("1. ���� ����", m_CenterPosition.x, m_CenterPosition.y * 0.7f);
	m_DrawManager.DrawMidText("2. �ɼ� ����", m_CenterPosition.x, m_CenterPosition.y * 0.9f);
	m_DrawManager.DrawMidText("3. ���� ����", m_CenterPosition.x, m_CenterPosition.y * 1.1f);
	m_DrawManager.BoxDraw(m_CenterPosition.x * 0.5f, m_CenterPosition.y * 1.3f, 10, 3);
	m_DrawManager.gotoxy(m_CenterPosition.x, m_CenterPosition.y * 1.4f);
	cin >> iSelect;

	return iSelect;
}

GameManager::~GameManager() {

}