#include <iostream>
#include <conio.h>
#include <string>
#include<vector>
#include <stdlib.h>
#include <chrono>
#include<fstream>
#include<locale>
#include<codecvt>
#include "practice.h"
#include "game.h"
#include "util.h"
#include"rainDrop.h"
using namespace std;
void select(int a)
{
	switch (a)
	{
	case 1:
		StayThisWay();
		break;
	case 2:
		NationalSong();
		break;
	case 3:
		StarryNight();
	case 4:
		break;
	case 5:
		test();
		break;
	}
}

int main(void)
{
	int num = 0;
	int num_1 = 0;
	while (1) 
	{
		mainMenu();
		cin >> num;
		switch (num)
		{
		case 1:
			system("cls");
			cout << "1. 프로미스나인의 StayThisWay" << endl << endl << "2. 애국가" << endl << endl << "3. 별 헤는밤" << endl << endl << "4. 메뉴 선택으로 돌아갑니다." << endl << endl;


			cout << "연습하고 싶은 번호 선택" << endl << "번호 입력 : ";
			cin >> num_1;
			cout << endl << "종료 하고싶으면 exit를 쳐주세요." << endl << "4초후 시작합니다.";
			Sleep(4000);
			system("cls");
			select(num_1);
			break;

		case 2:
			clock_t g_start_time;                           // 기준 시각
			SetConsoleCP(949);   //한글출력
			SetConsoleOutputCP(949); // 한글출력
			SetCursorVisible(FALSE);
			g_start_time = clock();
			srand(time(NULL));
			StartGame();
			InitData();
			InitScreen();
			Run();
			break;
		case 3:
			system("cls");
			SetCursorVisible(FALSE);
			game();
			break;
		case 4:
			exit(1);
		}
	}
	
}
