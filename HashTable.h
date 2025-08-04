//
// Created by smrut on 8/2/2025.
//

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include "string"
#include "vector"
#include "HashTable.h"
#include "Tree.h"
#include <fstream>
#include <sstream>

class HashTable {

    struct Person {
        std::string id;

        std::string fName;
        std::string lName;
        std::string sex;
        std::string email;
        std::string phone;
        std::string dob;
        std::string job;

        Person* next;

        Person(std::string i, std::string f, std::string l, std::string s, std::string e, std::string p, std::string d, std::string j)
        : id(i), fName(f), lName(l), sex(s), email(e), phone(p), dob(d), job(j), next(nullptr) {}
    };

    const int prime = 99991;
    std::vector<Person*> table;



    //source: https://github.com/SRombauts/cpp-algorithms/blob/master/src/algo/hash.cpp
    size_t hashFunction(std::string key) {
        //FNV-1a non-cryptographic hash function

        //64 bit offset_basis
        size_t hash = 14695981039346656037ULL;

        for (size_t i = 0; key[i] != 0; ++i) {
            //FNV_prime = 240 + 28 + 0xb3 = 1099511628211
            hash = 1099511628211ULL * (hash ^ static_cast<unsigned char>(key[i]));
        }

        return hash%prime;
    }

public:

    HashTable() : table(prime) {};

    void insert(std::string& line) {
        std::istringstream iss(line);
        std::string ind, id, f, l, s, e, p, d, j;
        std::getline(iss, ind, ',');
        std::getline(iss, id, ',');
        std::getline(iss, f, ',');
        std::getline(iss, l, ',');
        std::getline(iss, s, ',');
        std::getline(iss, e, ',');
        std::getline(iss, p, ',');
        std::getline(iss, d, ',');
        std::getline(iss, j, ',');

        Person* person = new Person(id, f, l, s, e, p, d, j);
        size_t index = hashFunction(id);

        Person* temp = table[index];
        while (temp != nullptr) {
            if (temp->id == id) {
                temp->fName = f;
                temp->lName = l;
                temp->sex = s;
                temp->email = e;
                temp->phone = p;
                temp->dob = d;
                temp->job = j;
                return;
            }
            temp = temp->next;
        }

        person->next = table[index];

        //Add person to table at index given by the hash function
        table[index] = person;
        //std::cout << id << " ";
    }



    void remove(const std::string& key) {
        size_t index = hashFunction(key);
        Person* curr = table[index];
        Person* prev = nullptr;

        while (curr != nullptr) {
            if (curr->id == key) {
                if (prev != nullptr) {
                    prev->next = curr->next;
                } else {
                    table[index] = curr->next;
                }
                delete curr;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    }


    Person* getPerson(const std::string& key) {
        size_t index = hashFunction(key);
        Person* temp = table[index];
        while (temp != nullptr) {
            if (temp->id == key) {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    std::string getName(const std::string key) {
        Person* p = getPerson(key);
        if (p != nullptr) {
            return p->fName + " " + p->lName;
        }
        return "Not found";
    }

    std::string getEmail(const std::string key) {
        Person* p = getPerson(key);
        if (p != nullptr) {
            return p->email;
        }
        return "Not found";
    }

    std::string getPhone(const std::string key) {
        Person* p = getPerson(key);
        if (p != nullptr) {
            return p->phone;
        }
        return "Not found";
    }

    std::string getDOB(const std::string key) {
        Person* p = getPerson(key);
        if (p != nullptr) {
            return p->dob;
        }
        return "Not found";
    }

    std::string getJob(const std::string key) {
        Person* p = getPerson(key);
        if (p != nullptr) {
            return p->job;
        }
        return "Not found";
    }

    std::string info(const std::string key) {
        Person* p = getPerson(key);
        if (p == nullptr) {
            return "Not found\n";
        }
        std::ostringstream info;
        info << "Name: " << p->fName << " " << p->lName << "\n"
            << "Sex: " << p->sex << "\n"
            << "Email: " << p->email << "\n"
            << "Phone: " << p->phone << "\n"
            << "DOB: " << p->dob << "\n"
            << "Job: " << p->job;

        return info.str();
    }


    int getCount() {
        int count = 0;
        for (const auto& head : table) {
            Person* curr = head;
            while (curr) {
                count++;
                curr = curr->next;
            }
        }
        return count;
    }

    double loadFactor() {
        return static_cast<double>(getCount()) / prime;
    }

    int collisionCount() {
        int collisions = 0;
        for (const auto& head : table) {
            int bucketCount = 0;
            Person* curr = head;
            while (curr) {
                bucketCount++;
                curr = curr->next;
            }
            if (bucketCount > 1) {
                collisions += bucketCount - 1;
            }
        }
        return collisions;
    }


    double averageChainLength() {
        int totalLength = 0;
        int notEmpty = 0;

        for (const auto& head : table) {
            if (head != nullptr) {
                notEmpty++;
                int length = 0;
                Person* temp = head;
                while (temp != nullptr) {
                    length++;
                    temp = temp->next;
                }
                totalLength += length;
            }
        }

        if (notEmpty != 0) {
            return static_cast<double>(totalLength) / notEmpty;
        }
        return 0.0;
    }

    std::string statistics() {
        std::ostringstream oss;
        oss << "Total Entries: " << getCount() << "\n"
            << "Load Factor: " << loadFactor() << "\n"
            << "Collisions: " << collisionCount() << "\n"
            << "Average Chain Length: " << averageChainLength() << "\n";
        return oss.str();
    }

    std::string display() {
        std::ostringstream oss;

        for (int i = 0; i < prime; ++i) {
            Person* temp = table[i];
            if (temp != nullptr) {
                oss << "Bucket " << i << ": ";
                while (temp != nullptr) {
                    oss << "[" << temp->id << "] -> ";
                    temp = temp->next;
                }
                oss << "nullptr\n";
            }
        }

        return oss.str();
    }


    void fakeRemove(const std::string& key) {
        size_t index = hashFunction(key);
        Person* curr = table[index];
        Person* prev = nullptr;

        while (curr != nullptr) {
            if (curr->id == key) {
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    }


    ~HashTable() {
        for (auto& head : table) {
            while (head) {
                Person* next = head->next;
                delete head;
                head = next;
            }
        }
    }



};



#endif //HASHTABLE_H
