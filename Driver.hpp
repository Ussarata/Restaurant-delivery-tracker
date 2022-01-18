
#include "Order.hpp"

using namespace std;

enum driverState {
  atRes, delivering, driving
};

class Driver {

  bool loggedIn;
  driverState state;
  string name;
  double totalTips;
  int totalDeliveries;
  int totalMinDriving;
  int totalMinDelivering;
  Time departTime;
  Time deliverTime;
  Time arriveTime;
  Order* order;

  public:
    explicit Driver(string name);
     //Driver(string name)	Post: Creates a logged-in driver with the given name. 
     
    void login();
    //Pre: Driver is not logged in. 
    //Post: Logs the driver in. 

    void logout();
    //Pre: Driver is logged in and at the restaurant. 
    //Post: Logs the driver out. 

    void depart(Time time,  Order* o);
    //Pre: Driver is logged in and at the restaurant. 
    //Post: Driver is delivering. Departure time is recorded. 

    void deliver(Time time, double tip);
    //Pre: Driver is delivering, tip >= 0. 
    //Post: Driver is not delivering. Driver’s stats are updated. 

    void arrive(Time time);
    //Pre: Driver is driving but not delivering. 
    //Post: Driver is at the restaurant. Driver’s stats are updated.

    string getName();
    //Post: Returns the driver’s name. 

    bool isLoggedIn() const;
    //Post: Returns true if and only if the driver is logged in. 

    int getTotalDeliveries() const;
    //Post: Returns the total number of completed deliveries. 

    int getTotalMinDelivering() const;
    //Post: Returns the total minutes spent delivering (i.e., between “depart” and “deliver” commands).

    int getTotalMinDriving() const;

    double getTotalTips() const;
    //Post: Returns the total tips received, in dollars. 

    Order* getOrder();
    //Pre: Driver is delivering. 
    //Post: Returns the order being delivered. 

    string toString();
    //Post: Returns a string containing the driver’s name, state (e.g., not logged in), and, if the driver is delivering an order, the departure time and toString of the order being delivered.


};

Driver::Driver(string name) {
    loggedIn = false;
    state = atRes;
    this->name = std::move(name);
    totalTips = 0;
    totalDeliveries = 0;
    totalMinDriving = 0;
    totalMinDelivering = 0;
    order = nullptr;

}

void Driver::login() {
  if (loggedIn) {
    throw logic_error("Driver is already logged in. ");
  }
  loggedIn = true;

  cout << name << " has logged in!" << endl;
}

void Driver::logout() {
  if (!loggedIn) {
    throw logic_error("Driver is already logged out");
  }
  loggedIn = false;
  cout << name << " has logged out. Thank you for your work!" << endl;
}

void Driver::depart(Time time,  Order* o) {

  if (!loggedIn || state != atRes) {
    throw logic_error("Driver is not logged in and/or not at the restaurant");
  }

  order = o;

  order->depart();

  state = delivering;

  departTime = time;
}

void Driver::deliver(Time time, double tip)  {
  if(state != delivering && tip < 0) {
    throw logic_error("Driver is not delivering or invalid tip.");
  }

  deliverTime = time;

  order->deliver(time);

  totalMinDelivering += Time::elapsedMin(departTime, deliverTime);

  state = driving;

  totalDeliveries++;

  totalTips += tip;

  order = nullptr;


}

void Driver::arrive(Time time)  {
  if (state != driving) {
    throw logic_error("Driver is not driving");
  }

  arriveTime = time;
  state = atRes;
  totalMinDriving += Time::elapsedMin(departTime, arriveTime);

  cout << name << " is back for more work! :D" << endl;
  
}

string Driver::getName() {
  return name;
}


bool Driver::isLoggedIn() const {
  return loggedIn;
}

int Driver::getTotalDeliveries() const {
  return totalDeliveries;
}

int Driver::getTotalMinDelivering() const {
  return totalMinDelivering;
}

int Driver::getTotalMinDriving() const {
  return totalMinDriving;
}


double Driver::getTotalTips() const {
  return totalTips;
}


Order* Driver::getOrder()  {
  return order;
}


string Driver::toString() {

  string driverString;

  driverString += "Name: " + name + "\n";

  driverString += "State: ";


    if (state == atRes) {
      driverString += "At restaurant.\n";
    }
    if (state == delivering) {
      driverString += "Delivering.\n";
      driverString += ("Departure time: " + departTime.toString() + "\n" + order->toString() + "\n");
    }
    if (state == driving) {
        driverString += "Driving\n";
    }


  return driverString;
}


