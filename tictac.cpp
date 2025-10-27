#include "tictac.hpp"
#include <limits>

vector<string> tictac_board{
    " 1 | 2 | 3 ",
    " -----------",
    " 4 | 5 | 6 ",
    " -----------",
    " 7 | 8 | 9 "
};

bool playing(string yn) {
    return (yn == "y" || yn == "Y" || yn == "yes" || yn == "Yes");
}

void display_board() {
    for (auto &row : tictac_board)
        cout << row << endl;
}

void reset_board() {
    tictac_board = {
        " 1 | 2 | 3 ",
        " -----------",
        " 4 | 5 | 6 ",
        " -----------",
        " 7 | 8 | 9 "
    };
}

// helper to check if board is full
bool board_full() {
    string nums = "123456789";
    for (char n : nums)
        for (auto &row : tictac_board)
            if (row.find(n) != string::npos)
                return false;
    return true;
}



// Battle extentions

bool is_valid_mark(char c) {
    string allowed = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz?!*~$%#";
    return allowed.find(c) != string::npos;
}

bool is_valid_archetype(string a) {
    transform(a.begin(), a.end(), a.begin(), ::tolower);
    return (a == "paladin" || a == "alchemist" || a == "chronomage");
}

void setup_players(Player &p1, Player &p2) {
    cout << "PLAYER 1 setup:\n";
    p1.name = "1";
    cout << "Enter your mark: ";
    cin >> p1.mark;
    while (!is_valid_mark(p1.mark)) {
        cout << "Invalid mark. Try again: ";
        cin >> p1.mark;
    }
    cout << "Choose archetype (Paladin / Alchemist / Chronomage): ";
    cin >> p1.archetype;
    while (!is_valid_archetype(p1.archetype)) {
        cout << "Invalid choice. Try again: ";
        cin >> p1.archetype;
    }

    cout << "\nPLAYER 2 setup:\n";
    p2.name = "2";
    cout << "Enter your mark: ";
    cin >> p2.mark;
    while (!is_valid_mark(p2.mark)) {
        cout << "Invalid mark. Try again: ";
        cin >> p2.mark;
    }
    cout << "Choose archetype (Paladin / Alchemist / Chronomage): ";
    cin >> p2.archetype;
    while (!is_valid_archetype(p2.archetype)) {
        cout << "Invalid choice. Try again: ";
        cin >> p2.archetype;
    }
}


pair<int,int> board_index(int pos) {
    switch (pos) {
        case 1: return {0, 1};
        case 2: return {0, 5};
        case 3: return {0, 9};
        case 4: return {2, 1};
        case 5: return {2, 5};
        case 6: return {2, 9};
        case 7: return {4, 1};
        case 8: return {4, 5};
        case 9: return {4, 9};
        default: return {-1, -1};
    }
}

bool winner_mark(char mark) {
    
    vector<vector<int>> lines = {
        {1,2,3},{4,5,6},{7,8,9},
        {1,4,7},{2,5,8},{3,6,9},
        {1,5,9},{3,5,7}
    };
    for (auto &line : lines) {
        auto [r1,c1]=board_index(line[0]);
        auto [r2,c2]=board_index(line[1]);
        auto [r3,c3]=board_index(line[2]);
        if (tictac_board[r1][c1]==mark &&
            tictac_board[r2][c2]==mark &&
            tictac_board[r3][c3]==mark)
            return true;
    }
    return false;
}
//Alchemist 
void alchemist_swap() {
    int a, b;
    cout << "Enter two positions to swap (1-9): ";
    cin >> a >> b;
    if (a == b) {
        cout << "Cannot swap same mark.\n";
        return;
    }
    auto [r1,c1]=board_index(a);
    auto [r2,c2]=board_index(b);
    if (isdigit(tictac_board[r1][c1]) || isdigit(tictac_board[r2][c2])) {
        cout << "Cannot swap empty spaces!\n";
        return;
    }
    swap(tictac_board[r1][c1], tictac_board[r2][c2]);
    display_board();
}


bool are_adjacent(int a, int b) {
    static const vector<vector<int>> adjacency = {
        {2,4,5}, {1,3,4,5,6}, {2,5,6},
        {1,2,5,7,8}, {1,2,3,4,6,7,8,9}, {2,3,5,8,9},
        {4,5,8}, {4,5,6,7,9}, {5,6,8}
    };
    return find(adjacency[a-1].begin(), adjacency[a-1].end(), b) != adjacency[a-1].end();
}
//Paladin
void paladin_shift() {
    int from, to;
    cout << "Enter mark to shift (1-9): ";
    cin >> from;
    cout << "Enter adjacent empty space (1-9): ";
    cin >> to;

    if (!are_adjacent(from, to)) {
        cout << "Not adjacent!\n";
        return;
    }

    auto [r1,c1]=board_index(from);
    auto [r2,c2]=board_index(to);
    if (isdigit(tictac_board[r1][c1])) {
        cout << "No mark to move there!\n";
        return;
    }
    if (!isdigit(tictac_board[r2][c2])) {
        cout << "Destination occupied!\n";
        return;
    }

    tictac_board[r2][c2] = tictac_board[r1][c1];
    tictac_board[r1][c1] = ' ';
    display_board();
}

// battle turns
void player_battle_turn(Player &p) {
    cout << "\nPlayer " << p.name << " (" << p.archetype << ")'s turn!\n";
    cout << "1. Regular move\n";
    if (p.archetype == "Alchemist") cout << "2. Swap two marks\n";
    if (p.archetype == "Paladin") cout << "2. Shift a mark\n";
    cout << "Choice: ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        int place;
        cout << "Choose a place (1-9): ";
        cin >> place;
        update_board(place, string(1,p.mark));
        display_board();
    }
    else if (choice == 2) {
        if (p.archetype == "Alchemist") alchemist_swap();
        else if (p.archetype == "Paladin") paladin_shift();
        else cout << "No special ability yet!\n";
    } else {
        cout << "Invalid choice.\n";
    }
}

// Original functions
void player_input(int player)
{
    int place;
    cout << "Player " << player << " choose a place to put your mark (1-9): ";
    cin >> place;

    while(cin.fail() || place < 1 || place > 9)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number between 1 and 9." << endl;
        cin >> place;
    }

    string mark = (player == 1) ? "X" : "O";
    update_board(place, mark);
    display_board();
}

void update_board(int place, string mark)
{
    int pl;
    switch(place)
    {
        case 1:
            while (tictac_board[0][1]=='X' || tictac_board[0][1]=='O')
            { cout<<"That spot is already taken. Choose another: "; cin>>pl; update_board(pl,mark); return; }
            tictac_board[0].replace(1,1,mark); break;
        case 2:
            while (tictac_board[0][5]=='X' || tictac_board[0][5]=='O')
            { cout<<"That spot is already taken. Choose another: "; cin>>pl; update_board(pl,mark); return; }
            tictac_board[0].replace(5,1,mark); break;
        case 3:
            while (tictac_board[0][9]=='X' || tictac_board[0][9]=='O')
            { cout<<"That spot is already taken. Choose another: "; cin>>pl; update_board(pl,mark); return; }
            tictac_board[0].replace(9,1,mark); break;
        case 4:
            while (tictac_board[2][1]=='X' || tictac_board[2][1]=='O')
            { cout<<"That spot is already taken. Choose another: "; cin>>pl; update_board(pl,mark); return; }
            tictac_board[2].replace(1,1,mark); break;
        case 5:
            while (tictac_board[2][5]=='X' || tictac_board[2][5]=='O')
            { cout<<"That spot is already taken. Choose another: "; cin>>pl; update_board(pl,mark); return; }
            tictac_board[2].replace(5,1,mark); break;
        case 6:
            while (tictac_board[2][9]=='X' || tictac_board[2][9]=='O')
            { cout<<"That spot is already taken. Choose another: "; cin>>pl; update_board(pl,mark); return; }
            tictac_board[2].replace(9,1,mark); break;
        case 7:
            while (tictac_board[4][1]=='X' || tictac_board[4][1]=='O')
            { cout<<"That spot is already taken. Choose another: "; cin>>pl; update_board(pl,mark); return; }
            tictac_board[4].replace(1,1,mark); break;
        case 8:
            while (tictac_board[4][5]=='X' || tictac_board[4][5]=='O')
            { cout<<"That spot is already taken. Choose another: "; cin>>pl; update_board(pl,mark); return; }
            tictac_board[4].replace(5,1,mark); break;
        case 9:
            while (tictac_board[4][9]=='X' || tictac_board[4][9]=='O')
            { cout<<"That spot is already taken. Choose another: "; cin>>pl; update_board(pl,mark); return; }
            tictac_board[4].replace(9,1,mark); break;
        default:
            cout<<"Invalid input. Please try again."<<endl;
    }
}

bool winner(int player)
{
    if(tictac_board[0][1]==tictac_board[0][5] && tictac_board[0][5]==tictac_board[0][9]) return true;
    if(tictac_board[2][1]==tictac_board[2][5] && tictac_board[2][5]==tictac_board[2][9]) return true;
    if(tictac_board[4][1]==tictac_board[4][5] && tictac_board[4][5]==tictac_board[4][9]) return true;
    if(tictac_board[0][1]==tictac_board[2][1] && tictac_board[2][1]==tictac_board[4][1]) return true;
    if(tictac_board[0][5]==tictac_board[2][5] && tictac_board[2][5]==tictac_board[4][5]) return true;
    if(tictac_board[0][9]==tictac_board[2][9] && tictac_board[2][9]==tictac_board[4][9]) return true;
    if(tictac_board[0][1]==tictac_board[2][5] && tictac_board[2][5]==tictac_board[4][9]) return true;
    if(tictac_board[0][9]==tictac_board[2][5] && tictac_board[2][5]==tictac_board[4][1]) return true;
    return false;
}

