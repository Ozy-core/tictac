#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

extern vector<string> tictac_board;

struct Player {
    string name;
    char mark;
    string archetype;
};

// your original declarations
void display_board();
bool playing(string yn);
void player_input(int player);
void update_board(int place, string mark);
bool winner(int player);

// helpers and new functions
void reset_board();
bool board_full();

bool is_valid_mark(char c);
bool is_valid_archetype(string a);
pair<int,int> board_index(int pos);
bool winner_mark(char mark);

void setup_players(Player &p1, Player &p2);
void player_battle_turn(Player &p);

void alchemist_swap();
void paladin_shift();
bool are_adjacent(int a, int b);
