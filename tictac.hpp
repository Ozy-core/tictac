#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

extern vector<string> tictac_board;
void display_board();
bool playing(string yn);
void player_input();
void update_board(int place, string mark);
bool winner();
bool winner(vector<string> board);
