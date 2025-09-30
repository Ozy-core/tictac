//have intro here
//connect with the header for tictac 
//make a function for thr rules after the game starts
#include "tictac.hpp"

//figure out what to do here 
int main()
{
    cout<< "Welcome players! Want to play a game of Tic Tac Toe? (y/n)" << endl;
    string yn;
    cin >> yn;
    if(playing(yn))
    {
        display_board();
        while(playing(yn))
        {
            //game loops 
            player_input(1);
            if(winner(1))
            {
                cout<<"We have a winner! Good job player 1"<<endl;
                break;
            }
            player_input(2);
            if(winner(2))
            {
                cout<<"We have a winner! Good job player 2"<<endl;
                break;    
            }
            if(winner(1)==false && winner(2)==false && 
               tictac_board[0][1]!='1' && tictac_board[0][5]!='2' && tictac_board[0][9]!='3' &&
               tictac_board[2][1]!='4' && tictac_board[2][5]!='5' && tictac_board[2][9]!='6' &&
               tictac_board[4][1]!='7' && tictac_board[4][5]!='8' && tictac_board[4][9]!='9')
            {
                cout<<"It's a tie!"<<endl;
                break;
            }
        }
        cout<< "Do you want to play again? (y/n)" << endl;
        cin >> yn;
        if(playing(yn))
        {
            tictac_board = {
                " 1 | 2 | 3 ",
                " -----------",
                " 4 | 5 | 6 ",
                " -----------",
                " 7 | 8 | 9 "
            };
            main();  
        }  
     }
    else if (playing(yn)==false)
    {
        cout<< "See you next time!" << endl;
        exit(0);
    }
}