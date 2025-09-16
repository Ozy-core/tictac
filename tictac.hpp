#include <iostream>
#include <string>
#include <vector>

using namespace std;

string start(string yn);
void display_board();
void player_input(vector<string> board);
bool bounds(int pl);
bool winner(vector<string> board);