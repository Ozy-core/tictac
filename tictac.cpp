#include "tictac.hpp"

vector<string> tictac_board{
        " 1 | 2 | 3 ",
        " -----------",
        " 4 | 5 | 6 ",
        " -----------",
        " 7 | 8 | 9 "
};

//starting the game only if the user wants to play
string start(string yn)
{
    if(yn=="y"||yn=="Y"||yn=="yes"||yn=="Yes")
    {
        display_board();
        player_input(tictac_board);
    }
    return "Thank you for playing!";
}

void display_board()
{
    for(int i=0; i<tictac_board.size(); i++)
    {
        cout<<tictac_board[i]<<endl;
    }
}

//figure out a way you can change the board and the array itself to create a new one where the players added their X or O
//use the users input of 1-9 to change the board
//theres 2 players, player 1 is X always
//reject anything that already has an X or O in it
//make sure it doesnt go out of bounds, if it does, reject it
void player_input(vector<string> board)
{
    board = tictac_board;
    cout<< "Player 1, choose a number from 1-9 to place your X" << endl;
    int place;
    cin >> place;
    while(!bounds(place))
    {
        cin >> place;
    }
    //now try to change the board to where it places the X
    //figure out how to change the string in the vector
    
}

bool bounds(int pl)
{
    if(pl<1||pl>9)
    {
        cout<< "Out of bounds. Please enter a number from 1-9" << endl;
        return false;
    }
    return true;
}

//checking the who is the winner by going through if the 3 rows have equal strings in it
bool winner(vector<string> board)
{
    return false;
}