#include "tictac.hpp"

int main() {
    cout << "Welcome! Want to play a game of Tic Tac Toe? (y/n): ";
    string yn;
    cin >> yn;

    if (!playing(yn)) {
        cout << "See you next time!\n";
        return 0;
    }

    cout << "Select mode:\n1. Regular Tic Tac Toe\n2. Campaign Battle Tic Tac Toe\nChoice: ";
    int mode;
    cin >> mode;

    if (mode == 1) {
        reset_board();
        display_board();
        while (true) {
            player_input(1, "X");
            if (winner(1)) 
            {   
                display_board();
                cout << "Player 1 wins!\n";
                break; }
            display_board();

            player_input(2, "O");
            if (winner(2)) 
            { 
                display_board();
                cout << "Player 2 wins!\n"; 
                break; }
            display_board();

            bool full=true;
            for(int i=1;i<=9;i++){
                auto [r,c]=board_index(i);
                if(tictac_board[r][c] >= '1' && tictac_board[r][c] <= '9') full=false;
            }
            if(full){ cout<<"Draw!\n"; break; }
        }
    }
    else if (mode == 2) {

        Player player;
        int step = 0;

        cout << "Load previous campaign? (y/n): ";
        string loadyn; cin >> loadyn;
        if(playing(loadyn)) {
            if(load_game(player, step, "savegame.txt")) {
                cout << "Resuming saved campaign at step " << step << ".\n";
            } else {
                cout << "No save found. Starting new campaign.\n";
            }
        }

        if(player.name.empty()) {
            cout << "Enter your character name: ";
            cin >> ws;
            getline(cin, player.name);
            if(player.name.empty()) player.name = "Hero";

            cout << "Choose class (Paladin / Alchemist): ";
            cin >> player.archetype;

            if(player.archetype != "Paladin" && player.archetype != "Alchemist") {
                player.archetype = "Paladin";
            }
            if(player.archetype == "Paladin") {
                player.health = 60; player.attack = 8; player.defense = 5; player.mark = "X";
            } else {
                player.health = 50; player.attack = 9; player.defense = 3; player.mark = "X";
            }
            player.gold = 20;
            step = 0;
        }

        vector<Player> foes;
        Player enmu; enmu.name="Enmu"; enmu.mark="E"; enmu.health=20; enmu.attack=4; enmu.defense=1; enmu.gold=5; enmu.abilities={"Berserk"};
        Player gyutaro; gyutaro.name="Gyutaro"; gyutaro.mark="G"; gyutaro.health=25; gyutaro.attack=6; gyutaro.defense=2; gyutaro.gold=8; gyutaro.abilities={"Regenerate"};
        Player daki; daki.name="Daki"; daki.mark="D"; daki.health=30; daki.attack=7; daki.defense=3; daki.gold=12; daki.abilities={"SwapMarks"};
        Player akaza; akaza.name="Akaza"; akaza.mark="A"; akaza.health=40; akaza.attack=9; akaza.defense=4; akaza.gold=20; akaza.abilities={"Shield","Berserk"};
        Player muzan; muzan.name="Muzan Kibutsuji"; muzan.mark="M"; muzan.health=80; muzan.attack=12; muzan.defense=6; muzan.gold=100; muzan.abilities={"BloodBash","Regenerate","ShadowStep"};

        foes.push_back(enmu);
        foes.push_back(gyutaro);
        foes.push_back(daki);
        foes.push_back(akaza);
        foes.push_back(muzan);

        const int total_battles = (int)foes.size();

        while(step < total_battles) {
            cout << "\n===== Campaign Step " << step+1 << " =====\n";
            cout << "You are: " << player.name << " (HP " << player.health << ", ATK " << player.attack << ", DEF " << player.defense << ", Gold " << player.gold << ")\n";

            play_single_battle(player, foes[step]);

            if(player.health <= 0) {
                cout << "You have been defeated. Restarting campaign...\n";
                remove("savegame.txt");
                main();
                return 0;
            } else {
                int reward = foes[step].gold;
                cout << "You loot " << reward << " gold.\n";
                player.gold += reward;
            }

            step++;

            if(step == 1) random_event(player);
            if(step == 2) shop_event(player);
            if(step == 4) choice_event(player);

            cout << "Current stats: HP " << player.health << " | ATK " << player.attack << " | DEF " << player.defense << " | Gold " << player.gold << "\n";

            cout << "Save campaign progress? (y/n): ";
            string sy; cin >> sy;
            if(playing(sy)) save_game(player, step, "savegame.txt");

            cout << "Continue? (y/n): ";
            string cont; cin >> cont;
            if(!playing(cont)) {
                cout << "Save before exiting? (y/n): ";
                string sy2; cin >> sy2;
                if(playing(sy2)) save_game(player, step, "savegame.txt");
                return 0;
            }
        }

        cout << "\nYou have defeated all foes! Congratulations, " << player.name << "!\n";
        remove("savegame.txt");
    }

    cout << "Do you want to play again? (y/n): ";
    cin >> yn;
    if (playing(yn)) {
        reset_board();
        main();
    }

    return 0;
}
