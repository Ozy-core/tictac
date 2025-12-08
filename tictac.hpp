#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <random>
#include <chrono>
#include <fstream>



using namespace std;

extern vector<string> tictac_board;

void display_board();
bool playing(string yn);
void player_input(int player, string mark);
bool update_board(int place, string mark);
bool winner(int player);

struct Player
{
    string name;
    string mark;
    string archetype;
    int health = 0;
    int attack = 0;
    int defense = 0;
    int gold = 0;
    bool shielded = false;
    vector<string> abilities;
};

pair<int,int> board_index(int pos);
bool is_occupied(int pos);

bool alchemist_swap();
bool paladin_shift();

void player_battle_turn(Player& p);

int random_empty_position();
void opponent_battle_turn(Player& foe, const Player& player);
void apply_damage(Player& attacker, Player& defender);
void reset_board();
void play_single_battle(Player& player, Player& foe);

void save_game(const Player& player, int step, const string& filename);
bool load_game(Player& player, int& step, const string& filename);

void shop_event(Player& player);
void choice_event(Player& player);
void random_event(Player& player);

void pause_and_clear();
