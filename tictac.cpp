#include "tictac.hpp"

vector<string> tictac_board{
    " 1 | 2 | 3 ",
    " -----------",
    " 4 | 5 | 6 ",
    " -----------",
    " 7 | 8 | 9 "
};

bool playing(string yn)
{
    return (yn == "y" || yn == "Y" || yn == "yes" || yn == "Yes");
}

void display_board()
{
    for (const auto& row : tictac_board)
        cout << row << endl;
}

void player_input(int player)
{
    int place;
    cout << "Player " << player << " choose a place to put your mark (1-9): ";
    cin >> place;

    while (cin.fail() || place < 1 || place > 9)
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
    switch (place)
    {
        case 1:
            while (tictac_board[0][1] == 'X' || tictac_board[0][1] == 'O')
            { cout << "That spot is taken. Choose another: "; cin >> pl; update_board(pl, mark); return; }
            tictac_board[0].replace(1, 1, mark); break;
        case 2:
            while (tictac_board[0][5] == 'X' || tictac_board[0][5] == 'O')
            { cout << "That spot is taken. Choose another: "; cin >> pl; update_board(pl, mark); return; }
            tictac_board[0].replace(5, 1, mark); break;
        case 3:
            while (tictac_board[0][9] == 'X' || tictac_board[0][9] == 'O')
            { cout << "That spot is taken. Choose another: "; cin >> pl; update_board(pl, mark); return; }
            tictac_board[0].replace(9, 1, mark); break;
        case 4:
            while (tictac_board[2][1] == 'X' || tictac_board[2][1] == 'O')
            { cout << "That spot is taken. Choose another: "; cin >> pl; update_board(pl, mark); return; }
            tictac_board[2].replace(1, 1, mark); break;
        case 5:
            while (tictac_board[2][5] == 'X' || tictac_board[2][5] == 'O')
            { cout << "That spot is taken. Choose another: "; cin >> pl; update_board(pl, mark); return; }
            tictac_board[2].replace(5, 1, mark); break;
        case 6:
            while (tictac_board[2][9] == 'X' || tictac_board[2][9] == 'O')
            { cout << "That spot is taken. Choose another: "; cin >> pl; update_board(pl, mark); return; }
            tictac_board[2].replace(9, 1, mark); break;
        case 7:
            while (tictac_board[4][1] == 'X' || tictac_board[4][1] == 'O')
            { cout << "That spot is taken. Choose another: "; cin >> pl; update_board(pl, mark); return; }
            tictac_board[4].replace(1, 1, mark); break;
        case 8:
            while (tictac_board[4][5] == 'X' || tictac_board[4][5] == 'O')
            { cout << "That spot is taken. Choose another: "; cin >> pl; update_board(pl, mark); return; }
            tictac_board[4].replace(5, 1, mark); break;
        case 9:
            while (tictac_board[4][9] == 'X' || tictac_board[4][9] == 'O')
            { cout << "That spot is taken. Choose another: "; cin >> pl; update_board(pl, mark); return; }
            tictac_board[4].replace(9, 1, mark); break;
        default:
            cout << "Invalid input. Try again." << endl;
    }
}

bool winner(int player)
{
    if (tictac_board[0][1]==tictac_board[0][5] && tictac_board[0][5]==tictac_board[0][9]) return true;
    if (tictac_board[2][1]==tictac_board[2][5] && tictac_board[2][5]==tictac_board[2][9]) return true;
    if (tictac_board[4][1]==tictac_board[4][5] && tictac_board[4][5]==tictac_board[4][9]) return true;
    if (tictac_board[0][1]==tictac_board[2][1] && tictac_board[2][1]==tictac_board[4][1]) return true;
    if (tictac_board[0][5]==tictac_board[2][5] && tictac_board[2][5]==tictac_board[4][5]) return true;
    if (tictac_board[0][9]==tictac_board[2][9] && tictac_board[2][9]==tictac_board[4][9]) return true;
    if (tictac_board[0][1]==tictac_board[2][5] && tictac_board[2][5]==tictac_board[4][9]) return true;
    if (tictac_board[0][9]==tictac_board[2][5] && tictac_board[2][5]==tictac_board[4][1]) return true;
    return false;
}


struct Player {
    string name;
    string mark;
    string archetype;
};

pair<int,int> board_index(int pos) {
    switch(pos) {
        case 1: return {0,1};
        case 2: return {0,5};
        case 3: return {0,9};
        case 4: return {2,1};
        case 5: return {2,5};
        case 6: return {2,9};
        case 7: return {4,1};
        case 8: return {4,5};
        case 9: return {4,9};
        default: return {-1,-1};
    }
}

bool is_occupied(int pos) {
    auto [r,c] = board_index(pos);
    if(r==-1) return true;
    return !(tictac_board[r][c] >= '1' && tictac_board[r][c] <= '9');
}

bool alchemist_swap(Player& player) {
    int a,b;
    cout << "Enter first position to swap: ";
    cin >> a;
    cout << "Enter second position to swap: ";
    cin >> b;

    if(a<1||a>9||b<1||b>9){ cout<<"Invalid positions.\n"; return false; }
    if(a==b){ cout<<"Cannot swap same position.\n"; return false; }

    auto [r1,c1]=board_index(a);
    auto [r2,c2]=board_index(b);
    char &A=tictac_board[r1][c1], &B=tictac_board[r2][c2];
    if((A>='1'&&A<='9')||(B>='1'&&B<='9')){ cout<<"Both positions must contain marks.\n"; return false; }
    if(A==B){ cout<<"Swapping identical marks does nothing.\n"; return false; }

    swap(A,B);
    display_board();
    return true;
}

bool paladin_shift(Player& player) {
    int from,to;
    cout<<"Enter position to move: "; cin>>from;
    cout<<"Enter adjacent empty spot: "; cin>>to;
    if(from<1||from>9||to<1||to>9){ cout<<"Invalid positions.\n"; return false; }

    auto [r1,c1]=board_index(from);
    auto [r2,c2]=board_index(to);
    char &F=tictac_board[r1][c1], &T=tictac_board[r2][c2];

    if(F>='1'&&F<='9'){ cout<<"No mark there.\n"; return false; }
    if(!(T>='1'&&T<='9')){ cout<<"Destination occupied.\n"; return false; }

    // Check adjacency
    vector<pair<int,int>> adj{{r1-2,c1},{r1+2,c1},{r1,c1-4},{r1,c1+4}};
    bool ok=false;
    for(auto [r,c]:adj) if(r==r2&&c==c2) ok=true;
    if(!ok){ cout<<"Must move to adjacent square.\n"; return false; }

    T=F;
    F='0'+from;
    display_board();
    return true;
}

void player_battle_turn(Player& p) {
    bool valid=false;
    while(!valid){
        cout<<"\n"<<p.name<<" ("<<p.archetype<<")'s turn.\n";
        cout<<"1. Regular move\n2. Use special ability\nSelect: ";
        int ch; cin>>ch;

        if(ch==1){
            int pos; cout<<"Enter position (1-9): "; cin>>pos;
            if(pos<1||pos>9){ cout<<"Invalid.\n"; continue; }
            auto [r,c]=board_index(pos);
            if(!(tictac_board[r][c]>='1'&&tictac_board[r][c]<='9')){ cout<<"Spot taken.\n"; continue; }
            update_board(pos,p.mark); valid=true;
        }
        else if(ch==2){
            if(p.archetype=="Alchemist") valid=alchemist_swap(p);
            else if(p.archetype=="Paladin") valid=paladin_shift(p);
            else { cout<<"This archetype not implemented.\n"; }
        }
        else cout<<"Invalid option.\n";
    }
}
