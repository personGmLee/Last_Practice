#pragma once
#ifndef MY_UTIL_H
#define MY_UTIL_H

#include <time.h>
#include <Windows.h>

void GotoXY(int x, int y);		            // Ŀ�� ��ġ �̵�
double GetDiffTime(clock_t start_time);     // �ð� ���� �˾Ƴ���(�� ����)
void SetCursorVisible(BOOL tf);             // Ŀ�� �Ⱥ��̰� �ϱ�
void mainMenu();
#endif