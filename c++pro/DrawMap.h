#pragma once
#include "Mecro.h"

class DrawMap
{
public:
	DrawMap();
	~DrawMap();

	inline void gotoxy(int x, int y) {
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}

	//�ٵ��� �׸���
	void GridDraw(int Start_x, int Start_y, int Width, int Height);
	//�� �ڽ� �׸���
	void BoxDraw(int Start_x, int Start_y, int Width, int Height);

	void DrawPoint(string str, int x, int y);
	void DrawMidText(string str, int x, int y);
	void TextDraw(string str, int x, int y);
	void ErasePoint(int x, int y);
};
