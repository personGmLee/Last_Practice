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
			cout << "1. ���ι̽������� StayThisWay" << endl << endl << "2. �ֱ���" << endl << endl << "3. �� ��¹�" << endl << endl << "4. �޴� �������� ���ư��ϴ�." << endl << endl;


			cout << "�����ϰ� ���� ��ȣ ����" << endl << "��ȣ �Է� : ";
			cin >> num_1;
			cout << endl << "���� �ϰ������ exit�� ���ּ���." << endl << "4���� �����մϴ�.";
			Sleep(4000);
			system("cls");
			select(num_1);
			break;

		case 2:
			clock_t g_start_time;                           // ���� �ð�
			SetConsoleCP(949);   //�ѱ����
			SetConsoleOutputCP(949); // �ѱ����
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
