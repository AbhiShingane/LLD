#include<iostream>
#include<string>
#include<vector>
#include "User.h"

using namespace std;

class MeetingRoom {
    string id;
    string name;
    Location location;
    bool isAvailable;
    int capacity;
    shared_ptr<User> organizer;
    vector<shared_ptr<User>> participants;



    MeetingRoom(string id, string name, Location location, bool isAvailable, int capacity) {
        this->id = id;
        this->name = name;
        this->location = location;
        this->isAvailable = true;
        this->capacity = capacity;
        organizer = nullptr;
        participants.clear();
    }

    bool bIsRoomAvailable() {
        return isAvailable;
    }

    void setAvailability(bool availability) {
        isAvailable = availability;
    }

    string getId()
    {

    }

    int getcapacity()
    {
        return capacity;
    }

    void setOrganizer(shared_ptr<User> user) {
        organizer = user;
    }

    void addParticipant(std::vector<shared_ptr<User>> user) {
        for (auto& u : user) {
            participants.push_back(u);
        }
    }

    

};

class Location {
    string building;
    string floor;
    string roomNumber;

    Location(string building, string floor, string roomNumber) {
        this->building = building;
        this->floor = floor;
        this->roomNumber = roomNumber;
    }
};