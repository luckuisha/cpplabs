//
//  playMove.cpp
//  TicTacTo
//
//  Created by Tarek Abdelrahman on 2018-05-15.
//  Copyright © 2018 Tarek Abdelrahman. All rights reserved.
//

#include <iostream>
#include <tic-tac-toe/playMove.h>

using namespace std;

bool gameAvail (int board[3][3], int row, int col);
bool moveAvail (int board[3][3], int row, int col);
bool valid (int board[3][3], int row, int col);

bool gameAvail (int board[3][3], int row, int col)
{
    if(board [row][col] == 1 || board [row][col] == -1)
    {
        if ((board[row][0] == board[row][1]) && (board[row][0] == board[row][2]))
        {
            return false;
        }
        else if ((board[0][col] == board[1][col]) && (board[0][col] == board[2][col]))
        {
            return false;
        }
        else if ((row == col) && (board[0][0] == board [1][1] && board[0][0] == board[2][2]))
        {
            return false;
        }
        else if ((row + col == 2) && (board[0][2] == board[1][1] && board[0][2] == board [2][0]))
        {
            return false;
        }
    }
    return true;
}

bool moveAvail (int board[3][3], int row, int col)
{
    if (gameAvail (board, row, col))
    {
        for (int x = 0; x < 3; x++)
        {
            for (int y = 0; y < 3; y++)
            {
                if (board [x][y] == 0)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool valid (int board[3][3], int row, int col)
{
    if (board[row][col] == 0)
    {
        return true;
    }
    return false;
}


void playMove(int board[3][3], int row, int col, bool& turn, bool& validMove, bool& gameOver, int& winCode) {

    // If the game is over, do nothing
    if (gameOver) return;

    // Insert your code here
    if(!gameOver)
    {
        if (valid(board, row, col))
            validMove = true;
        else
            validMove = false;
              
        if (turn && validMove)
        {
            board [row][col] = X;
            turn=!turn;
        }
        else if (!turn && validMove)
        {
            board [row][col] = O;
            turn=!turn;
        }
        if (!moveAvail (board, row, col))
            gameOver = true;
    }
        
    if(gameOver)
    {
        if ((board[row][0] == board[row][1]) && (board[row][0] == board[row][2]))
        {
            if(row == 0)
                winCode = 1;
            else if (row == 1)
                winCode = 2;
            else winCode = 3;
        }
        else if ((board[0][col] == board[1][col]) && (board[0][col] == board[2][col]))
        {
             if(col == 0)
                winCode = 4;
            else if (col == 1)
                winCode = 5;
            else winCode = 6;
        }
        else if ((row + col == 2) && (board[0][2] == board[1][1] && board[0][2] == board [2][0]))
        {
            winCode = 8;
        }
        else if ((row == col) && (board[0][0] == board [1][1] && board[0][0] == board[2][2]))
        {
            winCode = 7;
        }
        else winCode = 0;
    }
    
    for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cout << board[i][j] << ' ' ;
            }
        }
    cout << row <<' '<< col << ' ' << turn << ' ' << validMove << ' ' << gameOver << ' ' << winCode << endl;
    

    // The function must always print the output specified in the handout before it exits
    // Use the standard output (i.e., cout) to print the output

    // Insert code to print the output below

}

