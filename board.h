#pragma once

#include <map>
#include <vector>
#include <string>

class Board
{
public:
    std::map<int, std::string> board;

    void CreateBoard();
    void PrintBoard();

    std::vector<int> GetAvilableMoves();
    std::string BoardToString(std::map<int, std::string> board);

    bool Place(int cell, std::string symbol);
    std::string WhoWon();
};