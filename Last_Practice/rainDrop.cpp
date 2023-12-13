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
#define KEY_ENTER '\r'//엔터(ASC)
#define KEY_BS '\b' // Backspace (ASC)

#define MAX_WORD_LENGTH 24  // 최대단어길이
#define MAX_SCREEN_WORD_COUNT 19 //화면에 표시할수있는 최대 단어수
#define WORD_COUNT 3000      // 확장 값 단어의 총개수

int g_word_count = 3000;    // 사용되는 단어의 개수
std::vector<std::string> rainDrop;  // txt파일 벡터에 문자열저장
int g_fail_count = 0;                           // 실패한 개수
int g_score = 0;                                // 정수
char g_input_word[MAX_WORD_LENGTH + 1]; // 입력 단어 저장
int g_input_word_length = 0;                    // 입력 단어 길이
int stage = 1;                                  // 스테이지 단계 저장

struct ScreenWord
{
	int index;   //txt파일의 배열의 인덱스
	int x;  // x좌표
	int y;  //Y좌표
};
typedef struct ScreenWord ScreenWord;
ScreenWord g_screen_word[MAX_SCREEN_WORD_COUNT];// 화면에 나타난 단어들(g_words의 원소 index 저장)
int g_screen_word_count = 0;                    // 화면에 나타난 단어 개수

clock_t g_start_time;                           // 기준 시각
double g_falling_speed = 1.0;                   // 단어 낙하 시각(초 단위)

void InitScreen(void);
void InitData(void);                            // 아직 내용 없음 (확장 가능)
void Run(void);
void CompareWords(void);                        // 문자열 비교
void ProcessInput(int key);                     // 입력
void DrawWord(int i);                           // 화면에 나타난 i번째 단어 출력
void EraseWord(int i);                          // 화면에 나타난 i번째 단어 지우기
void UpdateScore(void);                         // 점수 카운팅
void UpdateFailCount(void);						// 실패 점수 카운티
void InitWord(int i);							//단어 랜덤위치 표시 및 단어 상태 초기화
void NextStage(void);                           //8점이 되면 다음단계 실패 점수가 5점이되면 fail
void StageScreen(void);                         // 스크린 ui
void StartGame(void);							// 게임 시작



void InitScreen(void)
{
	int i;

	system("cls");

	cout << ("┌─────────────────────────────────────┐\n");
	for (i = 0; i < 19; i++)
		cout << ("│                                                                          │\n");
	cout << ("└─────────────────────────────────────┘\n");

	// 입력칸
	GotoXY(28, 21); cout << ("┌────────────┐");
	GotoXY(28, 22); cout << ("│                        │");
	GotoXY(28, 23); cout << ("└────────────┘");

	//score 칸
	GotoXY(56, 21); cout << ("┌────┐");
	GotoXY(56, 22); cout << "│    " << g_score << "    │";
	GotoXY(56, 23); cout << ("└────┘");

	//fail 칸
	GotoXY(68, 21); cout << ("┌───┐");
	GotoXY(68, 22); cout << "│   " << g_fail_count << "   │";
	GotoXY(68, 23); cout << ("└───┘");
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
		std::cerr << "파일을 열 수 없습니다." << std::endl;
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

		GotoXY(28, 10); cout << ("┌────────────┐");
		GotoXY(28, 11); cout << ("│       fail.sorry       │");
		GotoXY(28, 12); cout << ("└────────────┘");

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
		GotoXY(28, 10); cout << ("┌────────────┐");
		GotoXY(28, 11); cout << "│   " << stage << " Stage Clear!       │";
		GotoXY(28, 12); cout << "│   Next Stage >> " << stage + 1 << "      │";
		GotoXY(28, 13); cout << ("└────────────┘");
		stage += 1;
		Sleep(3000);
		InitScreen();
		Run();
	}
	else
	{
		GotoXY(28, 10); cout << ("┌────────────┐");
		GotoXY(28, 11); cout << ("│   Success. thank you   │");
		GotoXY(28, 12); cout << ("└────────────┘");
		Sleep(3000);
		exit(0);
	}
}
void StartGame(void)
{
	std::cout << "┌─────────────────────────────────────┐\n";
	for (int i = 0; i < 22; i++)
		std::cout << "│                                     │\n";
	std::cout << "└─────────────────────────────────────┘\n";

	GotoXY(28, 10); std::cout << "    ┌────────────┐\n";
	GotoXY(28, 11); std::cout << "    │ If You Want Start │\n";
	GotoXY(28, 12); std::cout << "    │    key : enter    │\n";
	GotoXY(28, 13); std::cout << "    └────────────┘\n";

	std::cout << "Press Enter to start...";
	std::cin.get();
}

