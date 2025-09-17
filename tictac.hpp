#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string start(string yn);
void display_board();
void player_input(vector<string> board);
bool bounds(int pl);
void board_changes(vector<string>& board, int place, string symbol);
bool winner(vector<string> board);