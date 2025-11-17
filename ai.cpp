#include "ai.h"

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <random>
#include <algorithm>
#include <fstream>
#include <sstream>

void AI::Initialize(double _alpha, double _gamma, double _eps, char _marker)
{
    alpha = _alpha;
    gamma = _gamma;
    eps = _eps;
    marker = _marker;
}

int AI::ChooseAction(std::vector<int> availableMoves, std::string boardToString)
{
    std::random_device randomDevice;
    std::mt19937 gen(randomDevice());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    if (dis(gen) < eps) {
        std::uniform_int_distribution<> moveDis(0, availableMoves.size() - 1);
        return availableMoves[moveDis(gen)];
    }
    else
    {
        double maxQ = -1.0;
        int bestMove = -1;

        if (qTable.find(boardToString) == qTable.end()) {
            std::uniform_int_distribution<> moveDis(0, availableMoves.size() - 1);
            return availableMoves[moveDis(gen)];
        }

        for (int move : availableMoves) {
            if (qTable[boardToString].count(move) && qTable[boardToString][move] > maxQ) {
                maxQ = qTable[boardToString][move];
                bestMove = move;
            }
        }

        if (bestMove == -1) {
            std::uniform_int_distribution<> moveDis(0, availableMoves.size() - 1);
            return availableMoves[moveDis(gen)];
        }
        return bestMove;
    }
}

void AI::UpdateQTable(const std::string& oldState, int action, double reward, const std::string& newState, const std::vector<int>& nextAvailableMoves)
{
     double oldQ = qTable[oldState][action];

    double maxNextQ = 0.0;
    if (!nextAvailableMoves.empty() && qTable.count(newState)) {
        for (int move : nextAvailableMoves) {
            if (qTable[newState].count(move) && qTable[newState][move] > maxNextQ) {
                maxNextQ = qTable[newState][move];
            }
        }
    }

    qTable[oldState][action] = oldQ + alpha * (reward + gamma * maxNextQ - oldQ);
}

void AI::LoadProgress(const std::string& fileName)
{
    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cout << "Info: No saved progress file found at " << fileName << ". Starting fresh." << std::endl;
        return;
    }

    qTable.clear();

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string state;
        int action;
        double q_value;
        char comma;

        if (std::getline(ss, state, ',') && (ss >> action >> comma >> q_value) && comma == ',') {
            qTable[state][action] = q_value;
        }
    }

    file.close();
    std::cout << "Progress successfully loaded from " << fileName << std::endl;
}

void AI::SaveProgress(const std::string& fileName)
{
     std::ofstream file(fileName);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file to save progress: " << fileName << std::endl;
        return;
    }

    for (const auto& state_pair : qTable) {
        for (const auto& action_pair : state_pair.second) {
            file << state_pair.first << "," << action_pair.first << "," << action_pair.second << "\n";
        }
    }

    file.close();
    std::cout << "Progress saved to " << fileName << std::endl;
}