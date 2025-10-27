#include "tictac.hpp"

int main() {
    cout << "Welcome players! Want to play a game of Tic Tac Toe? (y/n): ";
    string yn; 
    cin >> yn;

    if (!playing(yn)) {
        cout << "See you next time!\n";
        return 0;
    }

    cout << "Select mode:\n1. Regular Tic Tac Toe\n2. Battle Tic Tac Toe\nChoice: ";
    int mode; 
    cin >> mode;

    if (mode == 1) {
       
        display_board();
        while (true) {
            player_input(1, "X");
            if (winner(1)) { cout << "Player 1 wins!\n"; break; }

            player_input(2, "O");
            if (winner(2)) { cout << "Player 2 wins!\n"; break; }
        }
    } 
    else if (mode == 2) {

        cout << "=====================\n";
        cout << "     Archetype Rules\n";
        cout << "=====================\n\n";

        // --- Alchemist Rules ---
        cout << "Alchemist:\n";
        cout << "An Alchemist is a potions master with arcane knowledge of transfiguration.\n";
        cout << "If a player chooses the Alchemist archetype, on their turn they can either:\n";
        cout << "  - Make a regular Tic-Tac-Toe move, OR\n";
        cout << "  - Swap two marks on the board.\n\n";

        cout << "Rules:\n";
        cout << "• On your turn, a formatted menu will appear allowing you to choose\n";
        cout << "  whether to make a regular move or swap marks.\n";
        cout << "• You will be prompted for which marks you want to swap.\n";
        cout << "• Marks do NOT have to be adjacent.\n";
        cout << "• You can activate this power once per turn and as many times as you want\n";
        cout << "  throughout the game.\n";
        cout << "• You CANNOT make a move AND swap marks in the same turn.\n";
        cout << "• The game will prevent you from swapping two marks of the same type\n";
        cout << "  (since that would be pointless).\n";
        cout << "• You cannot make an invalid special move (for example, you cannot swap marks\n";
        cout << "  during turns one or two, since there are zero or one marks on the board).\n\n";

        // --- Paladin Rules ---
        cout << "Paladin:\n";
        cout << "A Paladin is a stalwart guard that can force others around the battlefield.\n";
        cout << "If a player chooses the Paladin archetype, on their turn they can either:\n";
        cout << "  - Make a regular Tic-Tac-Toe move, OR\n";
        cout << "  - Shift one existing mark to an adjacent square.\n\n";

        cout << "Rules:\n";
        cout << "• You will see a menu allowing you to choose between a regular move or a special move.\n";
        cout << "  If you choose the special move, you will be asked which mark to shift and where.\n";
        cout << "• You may shift either your own mark or your opponent’s mark.\n";
        cout << "• The mark must move to an adjacent square (e.g., from space 1 to 2, 4, or 5).\n";
        cout << "• You CANNOT move a mark to a non-adjacent square (like 3, 6, 7, 8, or 9 from 1).\n";
        cout << "• You must shift the mark to an unoccupied square.\n";
        cout << "• Squares do NOT wrap around the board.\n";
        cout << "• You can activate this power once per turn and as many times as you want\n";
        cout << "  throughout the game.\n";
        cout << "• You CANNOT make a move AND shift a mark in the same turn.\n";
        cout << "• The game will stop you if you try to make an invalid special move\n";
        cout << "  (for example, shifting a mark on turn one when the board is empty).\n\n";
        
        Player p1, p2;
        cout << "Player 1, choose your mark: "; cin >> p1.mark;
        while (p1.mark.size() != 1) { cout << "One character only: "; cin >> p1.mark; }
        cout << "Player 1, choose archetype (Paladin/Alchemist): "; 
        cin >> p1.archetype;
        if(p1.archetype!="Paladin" && p1.archetype!="Alchemist"){
            cout<<"Invalid archetype. Defaulting to Paladin.\n"; p1.archetype="Paladin";
        }

        cout << "Player 2, choose your mark: "; cin >> p2.mark;
        while (p2.mark.size() != 1) { cout << "One character only: "; cin >> p2.mark; }
        cout << "Player 2, choose archetype (Paladin/Alchemist): "; 
        cin >> p2.archetype;
        if(p2.archetype!="Paladin" && p2.archetype!="Alchemist"){
            cout<<"Invalid archetype. Defaulting to Alchemist.\n"; p2.archetype="Alchemist";
        }

        p1.name="Player 1"; 
        p2.name="Player 2";

        display_board();

        while (true) {
            player_battle_turn(p1);
            display_board();
            if (winner(1)) { cout << "Player 1 wins!\n"; break; }

            player_battle_turn(p2);
            display_board();
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

    return 0;
}