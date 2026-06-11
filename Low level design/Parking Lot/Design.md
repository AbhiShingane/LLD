/* The parking lot is basically the singleton, managed the number of floors and allocate the spot*/

class ParkingLot
{
    std::vector<ParkingFloor> floorlist;
    string parkinglotid;
    string address;
    Displayboard dboard;
    public:
    void park(vehicle v1);

    void unpark(vehicle v2);

    void getAvailableParkingSpots();
};

class ParkingFloor
{
    std::vector<ParkingSpots> spotslist;
    int floorid;
    
    public:
    bool bIsFloorFull();
}

typedef enum
{
    2_Wheelar_parking_spot,
    4_Wheelar_parking_spot,
    loading_vehicle_parking_spot,
}Spottype;

class IParkingSpot
{
    Spottype *stype;
    string spotId;
    bool bIsOccupied;
    int floorid;

    public:
    bool bIsSpotEmpty();

    bool canVehicleFit(Vehicle obj);

    void parkVehicle(Vechile obj);

    void removeVehicle(Vechicle obj);
}

class I2WSpot: public IParkingSpot
{

};

class I4WSpot: public IParkingSpot
{

};

class LoadingVehicleSpot: public IParkingSpot
{

};


typedef enum
{
    2_Wheelar,
    4_wheelar,
    loading_vehicle,
}Vehicletype;

typedef enum
{
    PARKED,
    UNPARKED,

}VechileStatus;

class IVehicle
{
    string vehicleNumber;
    vehicletype;
    VehicleStatus vstatus;

    void registerVehicle();
    void updateVehicleStatus(VehicleStatus sts);
};

class MotarCycle: public IVehicle
{

}

class Car: public IVehicle
{

}

class Truck: public IVehicle
{

}

class Fare
{
    double motarcycleFarePerHr;
    double carFarePerHr;
    double truck;
}


Ticket
{
    string id;
    std::time_t starttime;
    std::time_t endtime;
    Vechile obj;
    ParkingSpot spotObj;
    Fare fareobj;
};

Lets focus on the Parking spot allocation strategy.

1) Scan all the spots 1 by 1 for all floors and returns the first available spot as per the vechile type.
complexity: o(n);

2. Maintain all the freespots with their type in the list as per the type and returns the spot.
    Eg..
            map<Spottype, queue<Parkingspot>> freespotlist;

    complexity O(1);


class ParkingManager
{
    void assignSpot();

    void releaseSpot();
}

class IParkingStrategy
{
    void findspot();
}

class ParkingStrategy1 : IParkingStrategy
{
    void findspot();
}

class ParkingStrategy2 : IParkingStrategy
{
    void findspot();
}


We can have same Interface and concrete implementaion for pricing stretegy also

class PaymentStrategy
{
    virtual PaymentStatus pay(double amount) = 0;
}

class cashPayment: PaymentStrategy
{
    PaymentStatus pay(double amount)
    {

    }
}

class cardPayment: PaymentStrategy
{
    PaymentStatus pay(double amount)
    {
        
    }
}

class UPIPayment: PaymentStrategy
{
    PaymentStatus pay(double amount)
    {
        
    }
}

class Displayboard
{
  
  int availableMotarCycleSpots;  
  int availableCarSpots;  
  int availabletruckSpots;

  public:
  std::vector<std::pair<std::String, int>> calculateAvailaleSpots(Parkinglot *parkinglot)
  {

  }  
};