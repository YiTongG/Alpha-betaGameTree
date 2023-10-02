#include "MinimaxGameTree.h"

int main(int argc, char* argv[]) {
    bool verbose = false, useAB = false;
    int range = INT_MAX;
    std::string inputFile = "input.txt";  // Default filename for simplicity
    bool isMaxPlayer = true;              // Default is max player

    // Simplified command line parsing for demonstration.
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "-v") verbose = true;
        else if (arg == "-ab") useAB = true;
        else if (arg == "-range" && i + 1 < argc) range = std::stoi(argv[++i]);
        else if (arg == "min" || arg == "max") isMaxPlayer = (arg == "max");
        else inputFile = arg;
    }

    MinimaxGameTree tree(inputFile);
    tree.executeMinimax(isMaxPlayer, range, verbose, useAB);

    return 0;
}
