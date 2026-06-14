#include<iostream>
#include<MeetingRoom.h>
#include<User.h>
#include<string>
#include<chrono>
#include<ctime>
using namespace std;

class ISchedular {
public:
    virtual vector<shared_ptr<MeetingRoom>> getAvailableRoom(std::time_t starttime, std::time_t endtime, const std::tm& date = std::tm(), int capacity = 2) = 0;
    virtual void getAllRooms(const struct tm& date = std::tm()) = 0;    
};


class BestFiltSchedular : public ISchedular {
public:
    vector<shared_ptr<MeetingRoom>> getAvailableRoom(std::time_t starttime, std::time_t endtime, const std::tm& date = std::tm(), int capacity = 2) override {
        vector<shared_ptr<MeetingRoom>> availableRooms;
        
        return availableRooms;
    }

    void getAllRooms(const struct tm& date = std::tm()) override {
        // Logic to retrieve and display all rooms for the given date
    }
};

class FirstFitSchedular : public ISchedular {
public:
    vector<shared_ptr<MeetingRoom>> getAvailableRoom(std::time_t starttime, std::time_t endtime, const std::tm& date = std::tm(), int capacity = 2) override {
        vector<shared_ptr<MeetingRoom>> availableRooms;
        // Logic to find the first available rooms based on the provided criteria
        return availableRooms;
    }

    void getAllRooms(const struct tm& date = std::tm()) override {
        // Logic to retrieve and display all rooms for the given date
    }
};