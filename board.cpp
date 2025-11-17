#include "board.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>

void Board::CreateBoard()
{
    for (int i = 1; i < 10; i++)
    {
        board[i] = "-";
    }
}

void Board::PrintBoard() 
{    
    for (int i = 1; i < 10; i++)
    {
        if (i % 3 == 0)
        {
            std::cout << board[i] << std::endl;
        } else {
            std::cout << board[i] << " ";
        }
    }
}

std::vector<int> Board::GetAvilableMoves()
{
    std::vector<int> avilableMoves;
    for (int i = 1; i < 10; i++)
    {
        if (board[i] == "-")
        {
            avilableMoves.push_back(i);
        }
    }

    return avilableMoves;
}

std::string Board::BoardToString(std::map<int, std::string> board)
{
    std::string boardToString = "";
    for (int i = 1; i < 10; i++)
    {
        boardToString += board[i];
    }

    return boardToString;
}

bool Board::Place(int cell, std::string symbol)
{
    if (board[cell] == "-")
    {
        board[cell] = symbol;
        return true;
    }

    return false;
}

std::string Board::WhoWon()
{
    // Rows
    if ((board[1] == board[2]) && (board[2] == board[3]))
    {
        if (board[1] != "-")
        {
            return board[1];
        }
    }
    
    if ((board[4] == board[5]) && (board[5] == board[6]))
    {
        if (board[4] != "-")
        {
            return board[4];
        }
    }
    
    if ((board[7] == board[8]) && (board[8] == board[9]))
    {
        if (board[7] != "-")
        {
            return board[7];
        }
    }

    // Cols
    if ((board[1] == board[4]) && (board[4] == board[7]))
    {
        if (board[1] != "-")
        {
            return board[1];
        }
    }
    
    if ((board[2] == board[5]) && (board[5] == board[8]))
    {
        if (board[2] != "-")
        {
            return board[2];
        }
    }
    
    if ((board[3] == board[6]) && (board[6] == board[9]))
    {
        if (board[3] != "-")
        {
            return board[3];
        }
    }

    // Dia
    if ((board[1] == board[5]) && (board[5] == board[9]))
    {
        if (board[1] != "-")
        {
            return board[1];
        }
    }
    
    if ((board[3] == board[5]) && (board[5] == board[7]))
    {
        if (board[3] != "-")
        {
            return board[3];
        }
    }

    std::vector<int> avilableMoves = GetAvilableMoves();
    if (avilableMoves.size() == 0)
    {
        return "Draw";
    }

    return "No One.";
}