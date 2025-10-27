#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

extern vector<string> tictac_board;

// Original functions
void display_board();
bool playing(string yn);
void player_input(int player, string mark);
bool update_board(int place, string mark);
bool winner(int player);

// Battle mode
struct Player
{
    string name;
    string mark;
    string archetype;
};
pair<int,int> board_index(int pos);
bool is_occupied(int pos);
bool alchemist_swap(Player& player);
bool paladin_shift(Player& player);
void player_battle_turn(Player& p);