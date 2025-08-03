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

    std::ifstream data("organizations-10000.csv");
    std::string line;
    HashTable hashTable;

    while (std::getline(data, line)) {
        std::string iss(line);
        hashTable.insert(line);
    }








}