#include "GameManager.h"

//오목판이 찌그러져 보이는 경우 콘솔 설정 바꾸는 방법
//1. 콘솔을 윈도우 11 제공 콘솔이 아닌 Microsoft Visual Studio 디버그 콘솔로 변경
//2. 변경한 콘솔창의 상태표시줄에서 마우스 우클릭한 후, 속성 메뉴 선택
//3. 레거시 콘솔 사용에 체크 표시 후 확인
//4. 다시 실행

void main()
{
	GameManager gameManager;
	gameManager.OpenGame();
}