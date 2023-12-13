#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include<chrono>
#include <windows.h>
#include "practice.h"
using namespace std;

size_t countMismatch(const string& correct, const string& user)
{
    size_t mismatchCount = 0;
    for (size_t i = 0; i < correct.size() && i < user.size(); ++i)
    {
        if (correct[i] != user[i])
        {
            ++mismatchCount;
        }
    }
    mismatchCount += abs(static_cast<int>(correct.size() - user.size()));
    return mismatchCount;
}
void displayError(const std::string& correct, const std::string& user) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    const WORD default_color = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
    const WORD error_color = FOREGROUND_RED | FOREGROUND_INTENSITY;

    for (size_t i = 0; i < correct.size() && i < user.size(); ++i) {
        if (correct[i] != user[i]) {
            SetConsoleTextAttribute(hConsole, error_color);
        }
        std::cout << user[i];
        SetConsoleTextAttribute(hConsole, default_color);
        if (correct[i] == user[i]) {
            SetConsoleTextAttribute(hConsole, default_color);
        }
    }
    if (user.size() < correct.size()) {
        SetConsoleTextAttribute(hConsole, error_color);
        std::cout << correct.substr(user.size());
        SetConsoleTextAttribute(hConsole, default_color);
    }
    std::cout << std::endl;
}


void StayThisWay()
{
    string file_path = "C:\\Users\\Administrator\\Desktop\\visual studio\\Last_Practice\\Last_Practice\\staythisway.txt";
    ifstream file(file_path);

    if (file.is_open())
    {
        string line;
        string user_input;
        size_t totalMismatchCount = 0;
        size_t totalLength = 0;
        size_t totalElapsedTime = 0;
        size_t totalTypedChars = 0;
        while (getline(file, line))
        {
            cout << endl << line << endl;
            user_input.clear(); // 사용자 입력 초기화

            auto start = std::chrono::steady_clock::now();  // 시작 시간
            getline(cin, user_input);
            auto end = std::chrono::steady_clock::now();
            auto diff = end - start;
            long long elapsed_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();

            if (user_input == "exit")
            {
                break;
            }
            totalElapsedTime += elapsed_milliseconds;
            totalTypedChars += user_input.size();
            // 전체 오타 수와 전체 길이 계산
            totalMismatchCount += countMismatch(line, user_input);
            totalLength += line.size();
        }
        double accuracy = static_cast<double>(totalLength - totalMismatchCount) / totalLength;
        int avgTypingSpeed = static_cast<int>(totalTypedChars * 60000 / totalElapsedTime); // 분당 타수
        cout << "걸린 시간: " << totalElapsedTime << " ms" << endl;
        cout << "타수 : " << avgTypingSpeed << endl;
        cout << "정답율 : " << accuracy * 100 << '%' << endl;
        file.close(); // 파일을 닫음
    }
    else
    {
        cout << "파일을 열 수 없습니다." << endl;
    }
}
void NationalSong()
{
    string file_path = "C:\\Users\\Administrator\\Desktop\\NationalSong.txt";
    ifstream file(file_path);

    if (file.is_open())
    {
        string line;
        string user_input;
        size_t totalMismatchCount = 0;
        size_t totalLength = 0;
        cin.ignore();
        while (getline(file, line))
        {
            int avg = 0;
            int count = 0;
            cout << endl << line << endl;

            user_input.clear(); // 사용자 입력 초기화

            auto start = std::chrono::steady_clock::now();  // 시작 시간

            char c;
            while ((c = cin.get()) != '\n')
            {
                user_input += c;
                count++;
            }
            auto end = std::chrono::steady_clock::now();
            auto diff = end - start;
            long long elapsed_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();

            if (user_input == line)
            {
                cout << endl;
            }
            else if (user_input == "exit")
            {
                break;
            }
            else
            {
                displayError(line, user_input);
                // 일치하지 않을 때 처리
            }
            std::cout << "걸린 시간: " << elapsed_milliseconds << " ms" << std::endl;
            avg = static_cast<int>(count * 60000 / elapsed_milliseconds); // 분당 타수
            cout << "타수 : " << avg << endl;
            // 전체 오타 수와 전체 길이 계산
            totalMismatchCount += countMismatch(line, user_input);
            totalLength += line.size();
        }

        double typoRate = static_cast<double>(totalLength - totalMismatchCount) / totalLength;
        cout << endl << "정답율 : " << (typoRate) * 100 << '%';
        Sleep(3000);
        file.close(); // 파일을 닫음
    }
}
void StarryNight()
{
    string file_path = "C:\\Users\\Administrator\\Desktop\\StarryNight.txt";
    ifstream file(file_path);

    if (file.is_open())
    {
        string line;
        string user_input;
        size_t totalMismatchCount = 0;
        size_t totalLength = 0;
        cin.ignore();
        while (getline(file, line))
        {
            int avg = 0;
            int count = 0;
            cout << endl << line << endl;

            user_input.clear(); // 사용자 입력 초기화

            auto start = std::chrono::steady_clock::now();  // 시작 시간

            char c;
            while ((c = cin.get()) != '\n')
            {
                user_input += c;
                count++;
            }
            auto end = std::chrono::steady_clock::now();
            auto diff = end - start;
            long long elapsed_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();

            if (user_input == line)
            {
                cout << endl;
            }
            else if (user_input == "exit")
            {
                break;
            }
            else
            {
                displayError(line, user_input);
                // 일치하지 않을 때 처리
            }
            std::cout << "걸린 시간: " << elapsed_milliseconds << " ms" << std::endl;
            avg = static_cast<int>(count * 60000 / elapsed_milliseconds); // 분당 타수
            cout << "타수 : " << avg << endl;
            // 전체 오타 수와 전체 길이 계산
            totalMismatchCount += countMismatch(line, user_input);
            totalLength += line.size();
        }

        double typoRate = static_cast<double>(totalLength - totalMismatchCount) / totalLength;
        cout << endl << "정답율 : " << (typoRate) * 100 << '%';
        Sleep(3000);
        file.close(); // 파일을 닫음
    }
}

void test()
{
    string file_path = "C:\\Users\\Administrator\\Desktop\\test.txt";
    ifstream file(file_path);

    if (file.is_open())
    {
        cin.ignore();
        string line;
        string user_input;
        size_t totalMismatchCount = 0;
        size_t totalLength = 0;
        size_t totalElapsedTime = 0;
        size_t totalTypedChars = 0;
        while (getline(file, line))
        {
            cout << line << endl;
            user_input.clear(); // 사용자 입력 초기화

            auto start = std::chrono::steady_clock::now();  // 시작 시간
            getline(cin, user_input);
            auto end = std::chrono::steady_clock::now();
            auto diff = end - start;
            long long elapsed_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();

            if (user_input == "exit")
            {
                break;
            }
            totalElapsedTime += elapsed_milliseconds;
            totalTypedChars += user_input.size();
            // 전체 오타 수와 전체 길이 계산
            totalMismatchCount += countMismatch(line, user_input);
            totalLength += line.size();
        }
        double accuracy = static_cast<double>(totalLength - totalMismatchCount) / totalLength;
        int avgTypingSpeed = static_cast<int>(totalTypedChars * 60000 / totalElapsedTime); // 분당 타수
        cout << endl;
        cout << "걸린 시간: " << totalElapsedTime << " ms" << endl;
        cout << "타수 : " << avgTypingSpeed << endl;
        cout << "정답율 : " << accuracy * 100 << '%' << endl;
        Sleep(4000);
        file.close(); // 파일을 닫음
    }
    else
    {
        cout << "파일을 열 수 없습니다." << endl;
    }
}