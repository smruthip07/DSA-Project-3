//
// Created by smrut on 8/2/2025.
//
#include <iostream>
#include "string"
#include "vector"
#include "HashTable.h"
#include "Tree.h"
#include <fstream>
#include <sstream>

int main(){
    cout <<"|---------------------------------------------------------|\n";
    cout <<"|                        Main Menu                        |\n";
    cout <<"|---------------------------------------------------------|\n";
    cout <<"|                     1. Load Data (CSV)                  |\n";
    cout <<"|---------------------------------------------------------|\n";
    cout <<"|   B+ Tree Index            |       Hash Table Index     |\n";
    cout <<"|---------------------------------------------------------|\n";
    cout <<"|2. Build B+ Tree Index      | 7.Build Hash Table Index   |\n";
    cout <<"|3. Search Key in B+ Tree    | 8. Search Key in Hash Table|\n";
    cout <<"|4. Range Query              | 9. Display Hash Table      |\n";
    cout <<"|5. Display B+ Tree Structure| 10. Hash Table Statistics  |\n";
    cout <<"| 6. B+ Tree Performance     |11. Hash Table Performance  |\n";
    cout <<"|---------------------------------------------------------|\n";
    cout <<"|                 12. Compare Structures                  |\n";
    cout <<"|                       13. Exit                          |\n";
    cout <<"|---------------------------------------------------------|\n";
    int choice;
    std::cin >> choice;
    while (choice!=13) {
        if(choice == 1) {
            std::ifstream data("people-10000.csv");
            std::string line;
            HashTable hashTable;

            while (std::getline(data, line)) {
                std::string iss(line);
                hashTable.insert(line);
            }
        }
        else if(choice == 2) {}
        else if(choice == 3) {}
        else if(choice == 4) {}
        else if(choice == 5) {}
        else if(choice == 6) {}
        else if(choice == 7) {}
        else if(choice == 8) {}
        else if(choice == 9) {}
        else if(choice == 10) {}
        else if(choice == 11) {}
        else if(choice == 12) {}
    }






return 0;
}