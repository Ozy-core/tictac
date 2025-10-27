#include "tictac.hpp"

int main() {
    cout << "Welcome players! Want to play a game of Tic Tac Toe? (y/n): ";
    string yn; cin >> yn;

    if (!playing(yn)) {
        cout << "See you next time!\n";
        return 0;
    }

    cout << "Select mode:\n1. Regular Tic Tac Toe\n2. Battle Tic Tac Toe\nChoice: ";
    int mode; cin >> mode;

    if (mode == 1) {
       
        display_board();
        while (true) {
            player_input(1);
            if (winner(1)) { cout << "Player 1 wins!\n"; break; }

            player_input(2);
            if (winner(2)) { cout << "Player 2 wins!\n"; break; }
        }
    } 
    else if (mode == 2) {
        
        Player p1, p2;
        cout << "Player 1, choose your mark: "; cin >> p1.mark;
        while (p1.mark.size() != 1) { cout << "One character only: "; cin >> p1.mark; }
        cout << "Player 1, choose archetype (Paladin/Alchemist): "; cin >> p1.archetype;

        cout << "Player 2, choose your mark: "; cin >> p2.mark;
        while (p2.mark.size() != 1) { cout << "One character only: "; cin >> p2.mark; }
        cout << "Player 2, choose archetype (Paladin/Alchemist): "; cin >> p2.archetype;

        p1.name="Player 1"; p2.name="Player 2";
        display_board();

        while (true) {
            player_battle_turn(p1);
            if (winner(1)) { cout << "Player 1 wins!\n"; break; }

            player_battle_turn(p2);
            if (winner(2)) { cout << "Player 2 wins!\n"; break; }
        }
    }

    cout << "Do you want to play again? (y/n): ";
    cin >> yn;
    if (playing(yn)) {
        tictac_board = {
            " 1 | 2 | 3 ",
            " -----------",
            " 4 | 5 | 6 ",
            " -----------",
            " 7 | 8 | 9 "
        };
        main(); // restart
    } else {
        cout << "Goodbye!\n";
    }
}
