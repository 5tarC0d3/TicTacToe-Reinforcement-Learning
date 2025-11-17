#include <iostream>
#include <string>

#include "board.h"
#include "ai.h"

void train(Board newBoard, AI& agent1, AI& agent2, int episodes)
{
    for (int i = 0; i < episodes; i++)
    {
        std::cout << i << std::endl;
        std::string oldBoard;
        int action;

        std::string whosTurn = "X";

        while (newBoard.WhoWon() == "No One.")
        {
            AI& currentAgent = (whosTurn == "X") ? agent1 : agent2;

            oldBoard = newBoard.BoardToString(newBoard.board);
            action = currentAgent.ChooseAction(newBoard.GetAvilableMoves(), newBoard.BoardToString(newBoard.board));
            newBoard.Place(action, whosTurn);

            std::string winner = newBoard.WhoWon();
            if (winner != "No One.")
            {
                double agent1Reward = 0;
                double agent2Reward = 0;

                if (winner == "X")
                {
                    agent1Reward = 1.0;
                    agent2Reward = -1.0;
                }
                else if (winner == "O")
                {
                    agent1Reward = -1.0;
                    agent2Reward = 1.0;
                }
                else if (winner == "Draw")
                {
                    agent1Reward = 0.5;
                    agent2Reward = 0.5;
                }

                agent1.UpdateQTable(oldBoard, action, agent1Reward, newBoard.BoardToString(newBoard.board), {});
                agent2.UpdateQTable(oldBoard, action, agent2Reward, newBoard.BoardToString(newBoard.board), {});
            }
            else
            {
                currentAgent.UpdateQTable(oldBoard, action, 0.0, newBoard.BoardToString(newBoard.board), newBoard.GetAvilableMoves());
            }

            whosTurn = "O";
        }
    }
}

int main()
{
    const std::string qTableFile = "qtable_progress.csv";

    Board newBoard;
    newBoard.CreateBoard();

    AI agent1;
    AI agent2;

    agent1.Initialize(0.1, 0.9, 0.8, 'X');
    agent2.Initialize(0.1, 0.9, 0.8, 'O');

    agent1.LoadProgress(qTableFile);
    agent2.qTable = agent1.qTable;

    std::cout << "Training model..." << std::endl;
    train(newBoard, agent1, agent2, 100000);
    std::cout << "Completed..." << std::endl;

    agent1.SaveProgress(qTableFile);
    std::cout << std::endl;

    agent1.eps = 0;

    bool hasAnyoneWon = false;
    std::string whosTurn = "X";

    while (hasAnyoneWon == false)
    {
        newBoard.PrintBoard();

        int move;
        if (whosTurn == "X")
        {
            std::cout << "AI's move..." << std::endl;
            move = agent1.ChooseAction(newBoard.GetAvilableMoves(), newBoard.BoardToString(newBoard.board));
            newBoard.Place(move, "X");

            whosTurn = "O";
        }
        else
        {
            std::cout << "Your move (enter a number 0-8): ";
            std::cin >> move;

            if (!newBoard.Place(move, "O"))
            {
                std::cout << "Invalid move. Try again." << std::endl;
            }

            whosTurn = "X";
        }

        std::string winner = newBoard.WhoWon();
        if (winner == "Draw")
        {
            std::cout << "It's a draw!" << std::endl;

            newBoard.PrintBoard();
            break;
        }
        else if (winner == "No One.")
        {
            continue;
        }
        else
        {
            std::cout << "Winner is " << winner << "!" << std::endl;
            newBoard.PrintBoard();
            break;
        }
    }
}