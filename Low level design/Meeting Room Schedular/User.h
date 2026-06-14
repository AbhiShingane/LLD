#include<iostream>
#include<string>

using namespace std;

class User {
    string id;
    string name;
    string email;
    bool bIsOrganizer;

    User(string id, string name, string email) {
        this->id = id;
        this->name = name;
        this->email = email;
    }

    string getId() {
        return id;
    }

    string getName() {
        return name;
    }

    string getEmail() {
        return email;
    }

    void setOrganizer(bool isOrganizer) {
        bIsOrganizer = isOrganizer;
    }

    bool isOrganizer() {
        return bIsOrganizer;
    }
};