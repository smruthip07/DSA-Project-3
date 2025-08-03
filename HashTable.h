//
// Created by smrut on 8/2/2025.
//

#ifndef HASHTABLE_H
#define HASHTABLE_H



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

        Person(std::string f, std::string l, std::string s, std::string e, std::string p, std::string d, std::string j)
        : fName(f), lName(l), sex(s), email(e), phone(p), dob(d), job(j) {}
    };

public:

    int hashFunction(std::string key) {

    }

    HashTable() = default;

    void insert(std::istringstream& iss) {

    }

    std::string info(std::string key) {

    }

    void remove(std::string key) {

    }

    std::string getName(std::string key) {

    }

    std::string getEmail(std::string key) {

    }

    std::string getPhone(std::string key) {

    }

    std::string getDOB(std::string key) {

    }

    std::string getJob(std::string key) {

    }






};



#endif //HASHTABLE_H
