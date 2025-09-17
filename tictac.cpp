#include "tictac.hpp"
#include <limits>

vector<string> tictac_board{
        " 1 | 2 | 3 ",
        " -----------",
        " 4 | 5 | 6 ",
        " -----------",
        " 7 | 8 | 9 "
};

bool playing(string yn)
{
    if(yn == "y" || yn == "Y"|| yn == "yes" || yn == "Yes")
    {
        return true;
    }
    else
    {
        return false;
    }
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
void player_input()
{
    int place;
    cout<<"Player 1, choose a place to put your X (1-9): ";
    cin>>place;

    while(cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
        cout << "Invalid input. Please enter a number between 1 and 9." << endl;
        cin>>place;
    }

    //figure out how to reject invalid inputs
    update_board(place, "X");
    display_board();
    if(winner())
    {
        cout<<"We have a winner! Good job player 1"<<endl;
        exit(0);
    }
    cout<<"Player 2, choose a place to put your O (1-9): ";
    cin>>place;

    while(cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
        cout << "Invalid input. Please enter a number between 1 and 9." << endl;
        cin>>place;
    }
    update_board(place, "O");
    display_board();
    if(winner())
    {
        cout<<"We have a winner! Good job player 2"<<endl;
        exit(0);
    }
}

void update_board(int place, string mark)
{
    //figure out how to change the string in the vector
    switch(place)
    {
        case 1:
            tictac_board[0].replace(1,1,mark);
            break;
        case 2:
            tictac_board[0].replace(5,1,mark);
            break;
        case 3:
            tictac_board[0].replace(9,1,mark);
            break;
        case 4:
            tictac_board[2].replace(1,1,mark);
            break;
        case 5:
            tictac_board[2].replace(5,1,mark);
            break;
        case 6:
            tictac_board[2].replace(9,1,mark);
            break;
        case 7:
            tictac_board[4].replace(1,1,mark);
            break;
        case 8:
            tictac_board[4].replace(5,1,mark);
            break;
        case 9:
            tictac_board[4].replace(9,1,mark);
            break;
        default:
            cout<<"Invalid input. Please try again."<<endl;
    }
}




//checking the who is the winner by going through if the 3 rows have equal strings in it
bool winner()
{
    if(tictac_board[0][1]==tictac_board[0][5] && tictac_board[0][5]==tictac_board[0][9])
    {
        return true;
    }
    if(tictac_board[2][1]==tictac_board[2][5] && tictac_board[2][5]==tictac_board[2][9])
    {
        return true;
    }
    if(tictac_board[4][1]==tictac_board[4][5] && tictac_board[4][5]==tictac_board[4][9])
    {
        return true;
    }
    return false;
}