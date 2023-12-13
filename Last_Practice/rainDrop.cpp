#include <iostream>
#include <conio.h>
#include <string>
#include<vector>
#include <stdlib.h>
#include <chrono>
#include "util.h"
#include<fstream>
#include<locale>
#include<codecvt>
using namespace std;
#define KEY_ESC 27 //ESC(ASC)
#define KEY_ENTER '\r'//����(ASC)
#define KEY_BS '\b' // Backspace (ASC)

#define MAX_WORD_LENGTH 24  // �ִ�ܾ����
#define MAX_SCREEN_WORD_COUNT 19 //ȭ�鿡 ǥ���Ҽ��ִ� �ִ� �ܾ��
#define WORD_COUNT 3000      // Ȯ�� �� �ܾ��� �Ѱ���

int g_word_count = 3000;    // ���Ǵ� �ܾ��� ����
std::vector<std::string> rainDrop;  // txt���� ���Ϳ� ���ڿ�����
int g_fail_count = 0;                           // ������ ����
int g_score = 0;                                // ����
char g_input_word[MAX_WORD_LENGTH + 1]; // �Է� �ܾ� ����
int g_input_word_length = 0;                    // �Է� �ܾ� ����
int stage = 1;                                  // �������� �ܰ� ����

struct ScreenWord
{
	int index;   //txt������ �迭�� �ε���
	int x;  // x��ǥ
	int y;  //Y��ǥ
};
typedef struct ScreenWord ScreenWord;
ScreenWord g_screen_word[MAX_SCREEN_WORD_COUNT];// ȭ�鿡 ��Ÿ�� �ܾ��(g_words�� ���� index ����)
int g_screen_word_count = 0;                    // ȭ�鿡 ��Ÿ�� �ܾ� ����

clock_t g_start_time;                           // ���� �ð�
double g_falling_speed = 1.0;                   // �ܾ� ���� �ð�(�� ����)

void InitScreen(void);
void InitData(void);                            // ���� ���� ���� (Ȯ�� ����)
void Run(void);
void CompareWords(void);                        // ���ڿ� ��
void ProcessInput(int key);                     // �Է�
void DrawWord(int i);                           // ȭ�鿡 ��Ÿ�� i��° �ܾ� ���
void EraseWord(int i);                          // ȭ�鿡 ��Ÿ�� i��° �ܾ� �����
void UpdateScore(void);                         // ���� ī����
void UpdateFailCount(void);						// ���� ���� ī��Ƽ
void InitWord(int i);							//�ܾ� ������ġ ǥ�� �� �ܾ� ���� �ʱ�ȭ
void NextStage(void);                           //8���� �Ǹ� �����ܰ� ���� ������ 5���̵Ǹ� fail
void StageScreen(void);                         // ��ũ�� ui
void StartGame(void);							// ���� ����



void InitScreen(void)
{
	int i;

	system("cls");

	cout << ("������������������������������������������������������������������������������\n");
	for (i = 0; i < 19; i++)
		cout << ("��                                                                          ��\n");
	cout << ("������������������������������������������������������������������������������\n");

	// �Է�ĭ
	GotoXY(28, 21); cout << ("����������������������������");
	GotoXY(28, 22); cout << ("��                        ��");
	GotoXY(28, 23); cout << ("����������������������������");

	//score ĭ
	GotoXY(56, 21); cout << ("������������");
	GotoXY(56, 22); cout << "��    " << g_score << "    ��";
	GotoXY(56, 23); cout << ("������������");

	//fail ĭ
	GotoXY(68, 21); cout << ("����������");
	GotoXY(68, 22); cout << "��   " << g_fail_count << "   ��";
	GotoXY(68, 23); cout << ("����������");
}
void UpdateScore(void)
{
	GotoXY(61, 22); std::cout << g_score;
}

void UpdateFailCount(void)
{
	GotoXY(72, 22); std::cout << g_fail_count;
}

void DrawWord(int i)
{
	GotoXY(g_screen_word[i].x, g_screen_word[i].y);
	std::cout << rainDrop[g_screen_word[i].index];
}

void EraseWord(int i)
{
	if (g_screen_word[i].y > 0)
	{
		GotoXY(g_screen_word[i].x, g_screen_word[i].y);
		for (int count = 0; count < rainDrop[g_screen_word[i].index].length(); count++)
			std::cout << " ";
	}
}
void InitData(void)
{
	std::ifstream file("rainDropEng.txt");
	if (!file)
	{
		std::cerr << "������ �� �� �����ϴ�." << std::endl;
		return;
	}

	rainDrop.resize(WORD_COUNT + 1);
	for (int i = 0; i < WORD_COUNT; ++i)
	{
		std::getline(file, rainDrop[i]);
	}

	rainDrop[WORD_COUNT] = " ";
}

void Run(void)
{
	int count = 1;
	auto g_start_time = std::chrono::system_clock::now();

	for (int i = 0; i < 19; i++)
	{
		InitWord(i);
	}

	while (true)
	{
		if (_kbhit())
		{
			int key = _getch();
			ProcessInput(key);
		}

		auto current_time = std::chrono::system_clock::now();
		std::chrono::duration<double> diff = current_time - g_start_time;
		if (diff.count() > g_falling_speed)
		{
			for (int i = 0; i < count; i++)
			{
				EraseWord(i);
				g_screen_word[i].y++;

				if (g_screen_word[i].y == 20)
				{
					if (g_screen_word[i].index != WORD_COUNT)
					{
						g_fail_count++;
						UpdateFailCount();
						NextStage();
					}
					InitWord(i);
					g_screen_word[i].y++;
					DrawWord(i);
				}
				else
				{
					DrawWord(i);
				}
			}

			if (count < MAX_SCREEN_WORD_COUNT)
			{
				count++;
			}

			g_start_time = std::chrono::system_clock::now();
		}
	}
}

void InitWord(int i)
{
	g_screen_word[i].index = rand() % (WORD_COUNT);
	g_screen_word[i].x = rand() % 73 + 2;
	g_screen_word[i].y = 0;

	if (g_screen_word[i].x + rainDrop[g_screen_word[i].index].length() > 75)
	{
		while (1)
		{
			g_screen_word[i].x = rand() % 73 + 2;
			if (g_screen_word[i].x + rainDrop[g_screen_word[i].index].length() < 75)
				break;
		}
	}
}

void ProcessInput(int key)
{

	char ch = static_cast<char>(key);
	if (key == KEY_BS)
	{
		if (g_input_word_length != 0)
		{
			GotoXY(30 + g_input_word_length - 1, 22);
			g_input_word[g_input_word_length] = NULL;
			cout << " ";
			g_input_word_length--;
		}
	}
	else if (key != KEY_ENTER)
	{
		if (g_input_word_length != 24)
		{
			GotoXY(30 + g_input_word_length, 22);
			cout << std::string(1, ch); // Changed from wcout to cout
			g_input_word[g_input_word_length] = key;
			g_input_word_length++;

		}
	}
	else if (key == KEY_ENTER)
	{
		int count;
		CompareWords();
		GotoXY(30, 22);
		for (count = 0; count < strlen(g_input_word); count++)
		{
			cout << " ";
		}
		for (count = 0; count < g_input_word_length; count++)
		{
			g_input_word[count] = '\0';
		}
		g_input_word_length = 0;
	}

	NextStage();
}

void CompareWords(void)
{
	int i;
	int	Delete = -1;
	g_input_word[g_input_word_length] = '\0';
	std::string input_word(g_input_word);
	for (i = 0; i < 19; i++)
	{
		std::string str = rainDrop[g_screen_word[i].index];

		if (input_word.compare(str) == 0)  // Removed conversion to wide string
		{
			if (Delete != -1)
			{
				if (g_screen_word[i].y > g_screen_word[Delete].y)
					Delete = i;
			}
			if (Delete == -1)
				Delete = i;
		}
	}

	if (Delete != -1)
	{
		EraseWord(Delete);
		g_screen_word[Delete].index = WORD_COUNT;
		g_score++;
		UpdateScore();
	}
}


void NextStage(void)
{
	if (g_fail_count == 5)
	{
		system("cls");

		GotoXY(28, 10); cout << ("����������������������������");
		GotoXY(28, 11); cout << ("��       fail.sorry       ��");
		GotoXY(28, 12); cout << ("����������������������������");

		Sleep(3000);
		exit(0);
	}


	if (g_score == 8)
	{
		g_falling_speed -= 0.2;
		g_score = 0;
		g_fail_count = 0;
		UpdateScore();
		UpdateFailCount();
		StageScreen();
	}


}
void StageScreen(void)
{
	system("cls");

	if (stage < 5)
	{
		GotoXY(28, 10); cout << ("����������������������������");
		GotoXY(28, 11); cout << "��   " << stage << " Stage Clear!       ��";
		GotoXY(28, 12); cout << "��   Next Stage >> " << stage + 1 << "      ��";
		GotoXY(28, 13); cout << ("����������������������������");
		stage += 1;
		Sleep(3000);
		InitScreen();
		Run();
	}
	else
	{
		GotoXY(28, 10); cout << ("����������������������������");
		GotoXY(28, 11); cout << ("��   Success. thank you   ��");
		GotoXY(28, 12); cout << ("����������������������������");
		Sleep(3000);
		exit(0);
	}
}
void StartGame(void)
{
	std::cout << "������������������������������������������������������������������������������\n";
	for (int i = 0; i < 22; i++)
		std::cout << "��                                     ��\n";
	std::cout << "������������������������������������������������������������������������������\n";

	GotoXY(28, 10); std::cout << "    ����������������������������\n";
	GotoXY(28, 11); std::cout << "    �� If You Want Start ��\n";
	GotoXY(28, 12); std::cout << "    ��    key : enter    ��\n";
	GotoXY(28, 13); std::cout << "    ����������������������������\n";

	std::cout << "Press Enter to start...";
	std::cin.get();
}

