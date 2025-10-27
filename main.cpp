#include "tictac.hpp"

int main()
{
    cout << "Welcome players! Want to play a game of Tic Tac Toe? (y/n)" << endl;
    string yn;
    cin >> yn;

    if (!playing(yn)) {
        cout << "See you next time!" << endl;
        return 0;
    }
    cout << "Select game type:\n";
    cout << "1. Regular Tic Tac Toe\n";
    cout << "2. Battle Tic Tac Toe\n";
    int mode;
    cin >> mode;

    if (mode == 1) {
        display_board();
        while (true) {
            player_input(1);
            if (winner(1)) {
                cout << "We have a winner! Good job player 1\n";
                break;
            }
            if (winner(1) == false && winner(2) == false && board_full()) {
                cout << "It's a tie!\n";
                break;
            }

            player_input(2);
            if (winner(2)) {
                cout << "We have a winner! Good job player 2\n";
                break;
            }
            if (winner(1) == false && winner(2) == false && board_full()) {
                cout << "It's a tie!\n";
                break;
            }
        }
    }
    else if (mode == 2) {

        Player p1, p2;
        setup_players(p1, p2);
        display_board();
        int turn = 1;

        while (true) {
            Player &current = (turn % 2 == 1) ? p1 : p2;
            player_battle_turn(current);

            if (winner_mark(current.mark)) {
                cout << "Player " << current.name << " wins!\n";
                break;
            }
            if (board_full()) {
                cout << "It's a tie!\n";
                break;
            }
            turn++;
        }
    }

   
    cout << "Do you want to play again? (y/n)\n";
    cin >> yn;
    if (playing(yn)) {
        reset_board();
        main(); 
    } else {
        cout << "Goodbye!\n";
        exit(0);
    }
}
