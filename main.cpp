#include <iostream>
#include <fstream>
#include <string>

int sector(int sec, bool* pMoves) {
    int move;
    std::cout << "You move: ";
    std::cin >> move;
    sec += move % 13;
    if (sec > 13) sec -= 13;
    while (*(pMoves + sec - 1)) {
        ++sec;
        if (sec > 13) sec -= 13;
    }
    *(pMoves + sec - 1) = 1;
    return sec;
}

std::string question(int sec) {
    std::ifstream sectors;
    std::string question;
    sectors.open("..\\sectors.txt");
    int line = 1;
    std::getline(sectors, question);
    while (line != sec && std::getline(sectors, question)) {
        ++line;
    }
    sectors.close();
    return question;
}

bool checking(std::string answer, int sec) {
    std::ifstream file;
    std::string path = "..\\";
    path += std::to_string(sec);
    path += ".txt";
    file.open(path);
    std::string original;
    file >> original;
    file.close();
    return original == answer;
}

int main() {
    int sec = 1;
    int experts = 0;
    int viewers = 0;
    bool moves[13] = {0,0,0,0,0,0,0,0,0,0,0,0,0};
    std::string answer;
    while (experts != 6 && viewers != 6) {
        sec = sector(sec, moves);
        std::cout << question(sec) << "?" << std::endl;
        std::cout << "Answer: ";
        std::cin >> answer;
        checking(answer, sec) ? ++experts : ++viewers;
    }
    std::cout << (experts == 6 ? "Experts" : "Viewers") << " won!" << std::endl;
    return 0;
}
