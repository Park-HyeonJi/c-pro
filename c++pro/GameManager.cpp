#include "GameManager.h"

GameManager::GameManager() {
	m_MapSize.left = 0;
	m_MapSize.right = WIDTH;
	m_MapSize.top = 0;
	m_MapSize.bottom = HEIGHT;
}

void GameManager::RunGame() {
	m_DrawManager.GridDraw(0,0,m_MapSize.right, m_MapSize.bottom);
}

GameManager::~GameManager() {

}