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

    struct Contact {
        int   index;    // the index where all the info is recorded
        string line;    // entire CSV row
        // so overwriting operators so they can be managed as ints in the tree
        bool operator<(Contact const &o)  const { return index <  o.index; }
        bool operator>(Contact const &o)  const { return index >  o.index; }
        bool operator==(Contact const &o) const { return index == o.index; }
        bool operator<=(Contact const &o) const { return index <= o.index; }
        bool operator>=(Contact const &o) const { return index >= o.index; }
    };

    HashTable hashTable;
    BPTree<Contact> tree(30);
    std::chrono::duration<double> durationHash;
    std::chrono::duration<double> durationTree;
    long double HashInsert;
    long double HashSearch;
    long double HashDisplay;
    long double TreeInsert;
    long double TreeSearch;
    long double TreeDisplay;

    bool hashCreated = false;
    bool treeCreated = false;
    bool dataLoaded = false;
    ifstream data;

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
        switch (choice) {
                    case 13: {
                        cout << "DSA WAS FUN AND THIS PROJECT WAS COOL :)\n";
                        return 0;
                    }

                    case 1: {
                        data.open("people-10000.csv");
                        if (!data){
                            cout<< "Failed to open file\n";}
                        else {
                            std::cout << "Data loaded" << std::endl;
                        }
                        break;
                    }
            case 2: {
                        if (!data.is_open()) {
                            std::cout << "Please load data first (option 1).\n";
                            break;
                        }
                        data.clear(); //rewind the file & clear EOF/fail bits
                        data.seekg(0, std::ios::beg);
                        //skip the header line
                        std::string line;
                        if (!std::getline(data, line)) {
                            std::cerr << "File is empty—nothing to skip.\n";
                            break;
                        }
                        auto start = std::chrono::high_resolution_clock::now();
                        while (std::getline(data, line)) {
                            if (line.empty())
                                continue;
                            auto commaPos = line.find(',');
                            if (commaPos == std::string::npos)
                                continue;
                            try { // stoi was giving problems, decided to go with try and catch
                                int index = std::stoi(line.substr(0, commaPos));
                                tree.insert(Contact{ index, line });
                            } catch (const std::exception &) {
                                continue;
                            }
                        }
                        auto end = std::chrono::high_resolution_clock::now();
                        durationTree = end - start;
                        TreeInsert = durationTree.count();

                        std::cout << "B+ tree created\n";
                        treeCreated = true;
                        break;
            }


                    case 7: {
                            std::string line;


                            auto start = std::chrono::high_resolution_clock::now();
                            while (std::getline(data, line)) {
                                hashTable.insert(line);
                            }
                            auto end = std::chrono::high_resolution_clock::now();
                            durationHash = end - start;
                            std::cout << "Hash table created" << std::endl;
                            HashInsert = durationHash.count();
                            hashCreated = true;
                        break;
                        }

                    case 3: {
                            std::cout << "Enter Key: ";
                            int key;
                            std::cin >> key;
                            // Contact finding{ key,"" };
                            Contact searched = tree.search({key,""});
                            if (!searched.index != -1) {
                                cout << searched.line << endl;
                            } else {
                                std::cout << "Key not found" << endl;
                            }
                        break;
                        }
                    case 4:{
                            int high;
                            int low;
                            cout<<  "high: ";
                            cin >> high;
                            cout << endl;
                            cout <<"low: ";
                            cin >> low;
                            vector<Contact> keys = tree.rangeQuery(Contact{low,""},Contact{high,""});
                            for (auto it: keys) {
                                cout << it.line << endl;
                            }
                            break;
                        }
                    case 5: {
                        auto start = std::chrono::high_resolution_clock::now();
                        tree.print();
                        auto end = std::chrono::high_resolution_clock::now();
                        std::chrono::duration<double> durationDisplay = end - start;
                        std::cout << "Display time: "<<durationDisplay.count() << endl;
                        TreeDisplay = durationDisplay.count();
                        break;}
                    case 6:{
                        std::cout << "It took " << durationTree.count() << " to insert all the data into the B+ tree." << std::endl;
                        //add time to retrieve value
                        Contact TimeTrial {20,""};
                        auto start = std::chrono::high_resolution_clock::now();
                        tree.remove(TimeTrial);
                        auto end = std::chrono::high_resolution_clock::now();
                        std::chrono::duration<double> removeDuration = end - start;
                        std::cout << "It took " << removeDuration.count() << " seconds to remove an item.\n";
                        TreeDisplay = removeDuration.count();
                        auto s = std::chrono::high_resolution_clock::now();
                        tree.search(TimeTrial);
                        auto e = std::chrono::high_resolution_clock::now();
                        std::chrono::duration<double> searchDuration = e - s;
                        std::cout << "It took " << searchDuration.count() << " seconds to search for an item.\n";
                        TreeSearch = searchDuration.count();
                        break;
                }
                    case 8: {
                        std::cout << "Enter Key: " << std::endl;
                        std::string key;
                        std::cin >> key;
                        std::cout << hashTable.info(key);
                         break;
                    }
                    case 9:{
                        auto start = std::chrono::high_resolution_clock::now();
                        std::cout << hashTable.display();
                        auto end = std::chrono::high_resolution_clock::now();
                        std::chrono::duration<double> durationDisplay = end - start;
                        std::cout << "Display time: "<<durationDisplay.count()<<endl;
                        HashDisplay = durationDisplay.count();
                        break;
                    }
                    case 10: {
                        std::cout << hashTable.statistics();
                        break;
                    }
                    case 11:{
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
                        HashSearch = searchDuration.count();
                        break;
                    }
                    case 12: {
                        std::cout <<"|---------------------------------------------------------|\n";
                        std::cout <<"|                        Comparison                       |\n";
                        std::cout <<"|---------------------------------------------------------|\n";
                        std::cout <<"|   B+ Tree Index            |       Hash Table Index     |\n";
                        std::cout <<"|---------------------------------------------------------|\n";
                        std::cout <<"|Build B+ Tree Index = "<< TreeInsert <<"| 7. Build Hash Table Index"<<HashInsert<<"  |\n";
                        std::cout <<"|3. Search Key in B+ Tree"<<TreeSearch<<"    | 8. Search Key in Hash Table"<<HashSearch<<"|\n";
                        std::cout <<"|5. Display B+ Tree Structure"<<TreeDisplay<<"| 9. Display Hash Table"<<HashDisplay<<"      |\n";
                        std::cout <<"|---------------------------------------------------------|\n";
                        break;
                    }



            default:
                std::cout << "Invalid choice. Try again.\n";

        }
    }

    return 0;
}