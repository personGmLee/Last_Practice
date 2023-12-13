#include <iostream>
#include <string>
#include <future>
#include <chrono>
#include <random>
#include <fstream>
#include <unordered_set>
#include <windows.h>

using namespace std;

int game() {
    string insert;
    string game[100];
    string rand[25];
    int i = 0, num = 0;
    random_device rd;
    mt19937 gen1(rd());
    uniform_int_distribution<> dis1(0, 72);               // �޸��忡 ����� �ܾ� 73��

    string line;
    fstream file("game.txt", ios::in);
    if (file.is_open()) {
        while (getline(file, line)) {
            game[i] = line;
            i++;
        }
        file.close();
    }

    int x = 5, y = 2;

    COORD pos[25];

    unordered_set<int> used_numbers;

    for (int j = 0; j < 25; j++) {
        int random_number;

        do {
            random_number = dis1(gen1);
        } while (used_numbers.find(random_number) != used_numbers.end());

        used_numbers.insert(random_number);

        COORD position = { x, y };

        pos[j] = position;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
        rand[j] = game[random_number];
        cout << game[random_number] << endl;
        x = x + 15;

        if (x > 65) {
            y = y + 4;
            x = 5;
        }
    }

    COORD position = { 21, 24 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
    cout << " ----------------------------------" << endl;
    COORD position1 = { 21, 25 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position1);
    cout << "|                                  |" << endl;
    COORD position2 = { 21, 26 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position2);
    cout << " ----------------------------------" << endl;

    string word1;
    string word2;

    auto start_time = chrono::steady_clock::now();
    auto end_time = start_time + chrono::seconds(40);
    chrono::seconds remaining_time;

    while (num < 25)
    {
        COORD position3 = { 22, 25 };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position3);
        auto future = async(launch::async, [&] {
            cin >> insert;
            });

        // remaining_time �ʱ�ȭ
        remaining_time = chrono::duration_cast<chrono::seconds>(end_time - chrono::steady_clock::now());



        while (remaining_time.count() > 0) {
            // ���� �ð� ���
            COORD position9 = { 4, 28 };  // ���� �ð��� ����� ��ġ
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position9);
            cout << "���� �ð�: " << remaining_time.count() << "��    " << std::flush;
            COORD position3 = { 22, 25 };
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position3);
            if (future.wait_for(chrono::seconds(1)) == future_status::ready) {
                break;
            }
            remaining_time = chrono::duration_cast<chrono::seconds>(end_time - chrono::steady_clock::now());
        }

        if (remaining_time.count() <= 0) {
            system("CLS");

            COORD position4 = { 32, 8 };
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position4);
            cout << "GAME OVER" << endl;
            COORD position5 = { 32, 10 };
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position5);
            cout << "�Է� ���� : " << num << endl;
            COORD position6 = { 32, 11 };
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position6);
            cout << "���Է� ���� : " << 25 - num << endl;
            return 0;
        }

        for (int i = 0; i < 25; i++) {
            word1 = rand[i];
            word2 = insert;

            int result = strcmp(word1.c_str(), word2.c_str());

            if (result == 0) {
                string targetStr = word1;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos[i]); // Move to the start of the string
                for (int j = 0; j < targetStr.length(); ++j) {
                    WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), L" ", 1, nullptr, nullptr); // Write a space for each character
                }

                num++;
            }
        }

        if (!insert.empty()) {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position3); // insert�� ��ǥ ����
            WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), L"                                   ", 34, nullptr, nullptr);
        }
    }

    system("CLS");

    if (num == 25) {
        COORD position7 = { 32, 8 };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position7);
        cout << "GAME CLEAR!" << endl;

        COORD position8 = { 32, 10 };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position8);
        cout << "���� �ð� : " << remaining_time.count() << "��" << endl << endl << endl << endl;

        return 0;
    }

    return 0;
}