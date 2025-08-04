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
#include "chrono"

int main() {

    HashTable hashTable;
    //BPTree tree;
    std::chrono::duration<double> durationHash;
    std::chrono::duration<double> durationTree;

    bool hashCreated = false;
    bool treeCreated = false;


    while (true) {
        std::cout <<"|---------------------------------------------------------|\n";
        std::cout <<"|                        Main Menu                        |\n";
        std::cout <<"|---------------------------------------------------------|\n";
        std::cout <<"|                     1. Load Data (CSV)                  |\n";
        std::cout <<"|---------------------------------------------------------|\n";
        std::cout <<"|   B+ Tree Index            |       Hash Table Index     |\n";
        std::cout <<"|---------------------------------------------------------|\n";
        std::cout <<"|2. Build B+ Tree Index      | 7. Build Hash Table Index   |\n";
        std::cout <<"|3. Search Key in B+ Tree    | 8. Search Key in Hash Table|\n";
        std::cout <<"|4. Range Query              | 9. Display Hash Table      |\n";
        std::cout <<"|5. Display B+ Tree Structure|10. Hash Table Statistics   |\n";
        std::cout <<"|6. B+ Tree Performance      |11. Hash Table Performance  |\n";
        std::cout <<"|---------------------------------------------------------|\n";
        std::cout <<"|                 12. Compare Structures                  |\n";
        std::cout <<"|                       13. Exit                          |\n";
        std::cout <<"|---------------------------------------------------------|\n";

        int choice;
        std::cin >> choice;

        if (choice == 13) {
            break;
        }

        if (choice == 1) {
            std::ifstream data("people-100000.csv");
            std::cout << "Data loaded" << std::endl;
            std::cin >> choice;


            if (choice == 2) {
                std::string line;

                auto start = std::chrono::high_resolution_clock::now();
                while (std::getline(data, line)) {
                    //tree.insert(line);
                }
                auto end = std::chrono::high_resolution_clock::now();
                durationTree = end - start;
                std::cout << "B+ tree created" << std::endl;
                treeCreated = true;
                std::cin >> choice;
            }


            if (choice == 7) {
                std::string line;


                auto start = std::chrono::high_resolution_clock::now();
                while (std::getline(data, line)) {
                    hashTable.insert(line);
                }
                auto end = std::chrono::high_resolution_clock::now();
                durationHash = end - start;
                std::cout << "Hash table created" << std::endl;
                hashCreated = true;
                std::cin >> choice;
            }


            while ((choice == 3 || choice == 4 || choice == 5 || choice == 6) && treeCreated) {
                if (choice == 3) {
                    std::cout << "Enter Key: ";
                    std::string key;
                    std::cin >> key;
                    //std::cout << BPTree.getPerson(key);
                }
                if (choice == 4) {
                    //std::cout << BPTree.display();
                }
                if (choice == 5) {
                    //std::cout << BPTree.statistics();
                }
                if (choice == 6) {
                    std::cout << "It took " << durationTree.count() << " to insert all the data into the B+ tree." << std::endl;
                    //add time to retrieve value
                }
                std::cin >> choice;
            }

            while ((choice == 8 || choice == 9 || choice == 10 || choice == 11) && hashCreated) {
                if (choice == 8) {
                    std::cout << "Enter Key: " << std::endl;
                    std::string key;
                    std::cin >> key;
                    std::cout << hashTable.info(key);
                    std::cin >> choice;
                }
                if (choice == 9) {
                    auto start = std::chrono::high_resolution_clock::now();
                    std::cout << hashTable.display();
                    auto end = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> durationDisplay = end - start;
                    std::cout << "Display time: "<<durationDisplay.count();

                }
                if (choice == 10) {
                    std::cout << hashTable.statistics();
                }
                if (choice == 11) {
                    std::cout << "It took " << durationHash.count() << " to insert all the data into the hash table." << std::endl;


                    std::string a = "abcd";
                    auto start = std::chrono::high_resolution_clock::now();
                    hashTable.fakeRemove(a);
                    auto end = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> removeDuration = end - start;
                    std::cout << "It took " << removeDuration.count() << " seconds to remove an item.\n";

                    auto s = std::chrono::high_resolution_clock::now();
                    hashTable.info(a);
                    auto e = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> searchDuration = e - s;
                    std::cout << "It took " << searchDuration.count() << " seconds to search for an item.\n";

                }
                std::cin >> choice;
            }

            }
            else if (hashCreated && treeCreated && choice == 12) {

            }
            else {
                std::cout << "Invalid choice. Try again.\n";
            }

    }

    return 0;
}