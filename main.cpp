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
        }
     }
    else if (playing(yn)==false)
    {
        cout<< "See you next time!" << endl;
        exit(0);
    }
}