#pragma once

#include <string>
#include <map>

class AI
{
public:
    std::map<std::string, std::map<int, double>> qTable;

    double alpha;
    double gamma;
    double eps;

    char marker;

    void Initialize(double _alpha, double _gamma, double _eps, char _marker);
    int ChooseAction(std::vector<int> availableMoves, std::string boardToString);

    void UpdateQTable(const std::string& oldState, int action, double reward, const std::string& newState, const std::vector<int>& nextAvailableMoves);

    void LoadProgress(const std::string& fileName);
    void SaveProgress(const std::string& fileName);
};