#include "tictac.hpp"

using namespace std;

vector<string> tictac_board{
    " 1 | 2 | 3 ",
    " -----------",
    " 4 | 5 | 6 ",
    " -----------",
    " 7 | 8 | 9 "
};

static std::mt19937 rng((unsigned)chrono::system_clock::now().time_since_epoch().count());

bool playing(string yn)
{
    return (yn == "y" || yn == "Y" || yn == "yes" || yn == "Yes");
}

void display_board() {
    for (const auto& row : tictac_board) {
        cout << row << '\n';
    }
}

void player_input(int player, string mark)
{
    int place;

    while (true)
    {
        cout << "Player " << player << " choose a place to put your " << mark << " (1-9): ";
        cin >> place;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 9.\n";
            continue;
        }

        if (place < 1 || place > 9)
        {
            cout << "Invalid input. Please enter a number between 1 and 9.\n";
            continue;
        }

        if (update_board(place, mark))
        {
            break;
        }
        else
        {
            cout << "That spot is already taken. Please choose another spot.\n";
        }
    }
}

bool update_board(int place, string mark)
{
    auto [r,c] = board_index(place);
    if(r==-1) return false;

    if(!(tictac_board[r][c] >= '1' && tictac_board[r][c] <= '9')) return false;

    tictac_board[r].replace(c,1,mark);
    return true;
}

bool winner(int player)
{
    auto same = [](char a, char b, char c)->bool{
        return (a==b && b==c) && !(a>='1' && a<='9');
    };
    if (same(tictac_board[0][1], tictac_board[0][5], tictac_board[0][9])) return true;
    if (same(tictac_board[2][1], tictac_board[2][5], tictac_board[2][9])) return true;
    if (same(tictac_board[4][1], tictac_board[4][5], tictac_board[4][9])) return true;
    if (same(tictac_board[0][1], tictac_board[2][1], tictac_board[4][1])) return true;
    if (same(tictac_board[0][5], tictac_board[2][5], tictac_board[4][5])) return true;
    if (same(tictac_board[0][9], tictac_board[2][9], tictac_board[4][9])) return true;
    if (same(tictac_board[0][1], tictac_board[2][5], tictac_board[4][9])) return true;
    if (same(tictac_board[0][9], tictac_board[2][5], tictac_board[4][1])) return true;
    return false;
}

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

bool alchemist_swap() {
    int a,b;
    cout << "Enter first position to swap: ";
    cin >> a;
    cout << "Enter second position to swap: ";
    cin >> b;

    if(a<1||a>9||b<1||b>9) return false;
    if(a==b) return false;

    auto [r1,c1]=board_index(a);
    auto [r2,c2]=board_index(b);
    char &A=tictac_board[r1][c1], &B=tictac_board[r2][c2];
    if((A>='1'&&A<='9')||(B>='1'&&B<='9')) return false;
    if(A==B) return false;

    swap(A,B);
    display_board();
    return true;
}

bool paladin_shift() {
    int from,to;
    cout<<"Enter position to move: "; cin>>from;
    cout<<"Enter adjacent empty spot: "; cin>>to;
    if(from<1||from>9||to<1||to>9) return false;

    auto [r1,c1]=board_index(from);
    auto [r2,c2]=board_index(to);
    char &F=tictac_board[r1][c1], &T=tictac_board[r2][c2];

    if(F>='1'&&F<='9') return false;
    if(!(T>='1'&&T<='9')) return false;

    vector<pair<int,int>> adj{{r1-2,c1},{r1+2,c1},{r1,c1-4},{r1,c1+4}};
    bool ok=false;
    for(auto [r,c]:adj) if(r==r2&&c==c2) ok=true;
    if(!ok) return false;

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
            if(pos<1||pos>9) continue;
            auto [r,c]=board_index(pos);
            if(!(tictac_board[r][c]>='1' && tictac_board[r][c]<='9')) continue;
            update_board(pos,p.mark);
            valid=true;
            display_board();
        }
        else if(ch==2){
            if(p.archetype=="Alchemist") valid=alchemist_swap();
            else if(p.archetype=="Paladin") valid=paladin_shift();
        }
    }
}

int random_empty_position() {
    vector<int> empty;
    for(int i=1;i<=9;i++){
        auto [r,c]=board_index(i);
        if(tictac_board[r][c] >= '1' && tictac_board[r][c] <= '9') empty.push_back(i);
    }
    if(empty.empty()) return -1;
    uniform_int_distribution<int> dist(0, (int)empty.size()-1);
    return empty[dist(rng)];
}

void opponent_battle_turn(Player& foe, const Player& player) {
    uniform_int_distribution<int> d100(1,100);
    int roll = d100(rng);
    if(!foe.abilities.empty() && roll <= 20) {
        string ab = foe.abilities[rng()%foe.abilities.size()];
        cout << foe.name << " attempts to use special ability: " << ab << "!\n";
        if(ab == "Heal" || ab == "Regenerate") {
            int heal = 5 + rng()%6;
            foe.health += heal;
            cout << foe.name << " heals " << heal << " HP!\n";
        } else if(ab == "Shield") {
            foe.shielded = true;
            cout << foe.name << " raises a shield.\n";
        } else if(ab == "Berserk" || ab == "BloodBash") {
            int buff = 2 + rng()%4;
            foe.attack += buff;
            cout << foe.name << " gains +" << buff << " attack.\n";
        } else if(ab == "SwapMarks" || ab == "ShadowStep") {
            vector<int> filled;
            for(int i=1;i<=9;i++){
                auto [r,c]=board_index(i);
                if(!(tictac_board[r][c]>='1' && tictac_board[r][c]<='9')) filled.push_back(i);
            }
            if(filled.size()>=2){
                int i1 = filled[rng()%filled.size()];
                int i2 = filled[rng()%filled.size()];
                while(i2==i1) i2 = filled[rng()%filled.size()];
                auto [r1,c1]=board_index(i1);
                auto [r2,c2]=board_index(i2);
                swap(tictac_board[r1][c1], tictac_board[r2][c2]);
                cout << foe.name << " swaps marks.\n";
            }
        } else if(ab == "BreatheFire") {
            foe.attack += 2;
        } else if(ab == "TailWhip") {
        }
        display_board();
        return;
    }

    int pos = random_empty_position();
    if(pos == -1) return;
    update_board(pos, foe.mark);
    cout << foe.name << " places at " << pos << "\n";
    display_board();
}

void apply_damage(Player& attacker, Player& defender) {
    int dmg = attacker.attack - defender.defense;
    if(dmg < 0) dmg = 0;
    if(defender.shielded) {
        cout << defender.name << "'s shield negates the damage!\n";
        defender.shielded = false;
        return;
    }
    defender.health -= dmg;
    cout << attacker.name << " deals " << dmg << " damage to " << defender.name << "!\n";
    if(defender.health < 0) defender.health = 0;
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

void play_single_battle(Player& player, Player& foe) {
    cout << "A battle begins: " << player.name << " vs " << foe.name << "!\n";
    cout << player.name << " HP: " << player.health << " | "
         << foe.name << " HP: " << foe.health << "\n";

    if(player.mark == foe.mark) {
        foe.mark = (player.mark == "X") ? "O" : "Z";
    }

    while(player.health > 0 && foe.health > 0) {
        reset_board();
        display_board();

        while(true) {
            cout << "\n-- " << player.name << "'s move --\n";
            if(player.archetype=="Alchemist" || player.archetype=="Paladin"){
                player_battle_turn(player);
            } else {
                int pos;
                while(true){
                    cout << "Enter position (1-9): ";
                    cin >> pos;
                    if(cin.fail()){
                        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }
                    if(pos<1||pos>9) continue;
                    auto [r,c]=board_index(pos);
                    if(!(tictac_board[r][c]>='1' && tictac_board[r][c]<='9')) continue;
                    break;
                }
                update_board(pos, player.mark);
                display_board();
            }

            if(winner(1)) {
                cout << player.name << " wins the match!\n";
                apply_damage(player, foe);
                break;
            }

            bool full=true;
            for(int i=1;i<=9;i++){
                auto [r,c]=board_index(i);
                if(tictac_board[r][c] >= '1' && tictac_board[r][c] <= '9') full=false;
            }
            if(full){
                cout << "Match is a draw.\n";
                break;
            }

            cout << "\n-- " << foe.name << "'s move --\n";
            opponent_battle_turn(foe, player);

            if(winner(2)) {
                cout << foe.name << " wins the match!\n";
                apply_damage(foe, player);
                break;
            }

            full=true;
            for(int i=1;i<=9;i++){
                auto [r,c]=board_index(i);
                if(tictac_board[r][c] >= '1' && tictac_board[r][c] <= '9') full=false;
            }
            if(full){
                cout << "Match is a draw.\n";
                break;
            }
        }

        cout << player.name << " HP: " << player.health << " | "
             << foe.name << " HP: " << foe.health << "\n";

        if(player.health <= 0) break;
        if(foe.health <= 0) break;
    }
}

void save_game(const Player& player, int step, const string& filename) {
    ofstream ofs(filename);
    if(!ofs) return;
    ofs << player.name << '\n';
    ofs << player.archetype << '\n';
    ofs << player.mark << '\n';
    ofs << player.health << ' ' << player.attack << ' ' << player.defense << '\n';
    ofs << player.gold << '\n';
    ofs << step << '\n';
}

bool load_game(Player& player, int& step, const string& filename) {
    ifstream ifs(filename);
    if(!ifs) return false;
    Player p;
    if(!getline(ifs, p.name)) return false;
    if(!getline(ifs, p.archetype)) return false;
    if(!getline(ifs, p.mark)) return false;
    if(!(ifs >> p.health >> p.attack >> p.defense)) return false;
    ifs >> p.gold;
    ifs >> step;
    player = p;
    return true;
}

void shop_event(Player& player) {
    cout << "\n--- You find a traveling merchant ---\n";
    cout << "You have " << player.gold << " gold.\n";
    vector<pair<string,int>> items = {
        {"Minor Health Potion (+15 HP)", 10},
        {"Iron Sword (+2 ATK)", 15},
        {"Steel Shield (+2 DEF)", 15}
    };
    while(true){
        cout << "Shop:\n";
        for(size_t i=0;i<items.size();i++) cout << i+1 << ". " << items[i].first << " - " << items[i].second << " gold\n";
        cout << items.size()+1 << ". Leave shop\n";
        cout << "Choose: ";
        int ch; cin>>ch;
        if(ch<1 || ch> (int)items.size()+1) continue;
        if(ch == (int)items.size()+1) break;
        if(player.gold < items[ch-1].second) continue;
        player.gold -= items[ch-1].second;
        if(ch==1){ player.health += 15; }
        else if(ch==2){ player.attack += 2; }
        else if(ch==3){ player.defense += 2; }
    }
}

void choice_event(Player& player) {
    cout << "\n--- Crossroads ---\n";
    cout << "1. Left (heal)\n2. Right (risk)\nSelect: ";
    int ch; cin>>ch;
    if(ch==1) {
        int heal = 8 + rng()%8;
        player.health += heal;
    } else {
        int roll = rng()%100;
        if(roll < 50) {
            int gold = 10 + rng()%21;
            player.gold += gold;
        } else {
            int dmg = 5 + rng()%8;
            player.health -= dmg;
            if(player.health < 0) player.health = 0;
        }
    }
}

void random_event(Player& player) {
    cout << "\n--- A small event occurs ---\n";
    int r = rng()%3;
    if(r==0){
        int heal = 5 + rng()%6;
        player.health += heal;
    } else if(r==1){
        int atk = 1 + rng()%2;
        player.attack += atk;
    } else {
        int gold = 5 + rng()%11;
        player.gold += gold;
    }
}

void pause_and_clear() {
    cout << "\nPress enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cin.get();
}
