#include "Driver.hpp"
using namespace std;


class Restaurant {

private:

    list<Order*> cooking;
    list<Order*> prepared;
    list<Order*> completed;
    list<Driver*> drivers;

    int totalDeliveries;
    int totalDeliveryTime;

public:
    Restaurant();
    //post: constructor.

    void clear();
    //post: frees dynamically allocated memory used in the lists.

    void status();
    //post: prints the status of the restauarant

    void summary();
    //post: prints the summary of all the events that occured.

    Driver* getDriver(const string& name);
    //post: returns a pointer to the driver corresponding to the name provided, otherwise returns nullptr

    void addDriver(Driver* driver);
    //post: adds the driver to the system.

    void addOrder(Time time, string info);
    //post: adds the order to the system

    void serveNextOrder() ;
    //pre: cooking queue is not empty
    //post: removes the oldest order from the cooking queue and enqueues it for departure.  

    void departNextOrder(Driver* driver, Time time);
    //pre: prepared queue is not empty
    //post: removes the oldest order from prepared queue and assigns it to an available driver to depart. Time of depature is recorded.
    
    void deliver(Driver* driver, Time time, double tip);
    //post: the order delivered by the driver is delivered at the given time. The driver receives the given tip.
};

Restaurant::Restaurant() {
    totalDeliveries = 0;
    totalDeliveryTime = 0;
}

void Restaurant:: status() {

    cout << "STATUS:" << endl;
    cout << "---------------------------------------------------------------------" << endl;

    cout << "ORDERS COOKING:" << endl;
    if (cooking.empty()) {
        cout << "Cooking queue is empty." << endl;
    } else {
        for (auto &it: cooking) {
            cout << "-----------" << endl;
            cout << it->toString() << endl;
        }
    }


    cout << "-----------------------------------------" << endl;
    cout << "ORDERS PREPARED:" << endl;

    if (prepared.empty()) {
        cout << "Prepared queue is empty." << endl;
    } else {
        for (auto &it: prepared) {
            cout << "-------" << endl;
            cout << it->toString() << endl;

        }
    }

    cout << "-----------------------------------------" << endl;
    cout << "ORDERS COMPLETED:" << endl;

    if (completed.empty()) {
        cout << "No orders completed yet." << endl;
    } else {
        for (auto &it: completed) {
            cout << "-------" << endl;
            cout << it->toString() << endl;
        }
    }

    cout << "-----------------------------------------" << endl;
    cout << "ONLINE DRIVERS:" << endl;

     bool empty = true;

    for (auto &driver: drivers) {
        if (driver->isLoggedIn()) {
            cout << "-------" << endl;
            cout << driver->toString();
            empty = false;
        }
    }
    if (empty) {
        cout << "No drivers are online" << endl;
    }
    cout << "-----------------------------------------" << endl;
}

void Restaurant ::summary() {

    cout << "SUMMARY:" << endl;
    cout << "---------------------------------------------------------------------" << endl;

    cout << "Restaurant stats:" << endl;
    cout << "Total deliveries completed: " << totalDeliveries << endl;
    if (totalDeliveries > 0) {
        cout << "Average time per delivery: " << (totalDeliveryTime / totalDeliveries) << endl;
    }

    cout << "---------------------------------" << endl;

    cout << "Individual driver stats:" << endl;
    
  for (auto & driver : drivers) {
      cout << "-------" << endl;
      cout << "Driver name: " << driver->getName() << endl;
      if(driver->getTotalDeliveries() > 0) {
          cout << "Number of deliveries completed: " << driver->getTotalDeliveries() << endl;
          cout << "Average delivery Time: " << (driver->getTotalMinDelivering()/(driver->getTotalDeliveries())) << endl;
          cout << "Total driving time: " << driver->getTotalMinDriving() << endl;
          cout << "Total tips: " << driver->getTotalTips() << endl;
      }
      else {
          cout << "No deliveries were made by this driver." << endl;
      }
      
  }
  cout << "-----------------------------------------" << endl;
}

Driver* Restaurant::getDriver(const string& name) {

   for (auto & driver : drivers) {
      if (name == driver->getName()) {
        return driver;
      }
   }
    return nullptr;
}


void Restaurant::addDriver(Driver* driver) {
  drivers.push_back(driver);
}

void Restaurant::addOrder(Time time, string info) {

    auto newOrder = new Order(time, info);

    cooking.push_back(newOrder);
    cout << "New order placed." << endl;

}

void Restaurant::serveNextOrder(){

  if (cooking.empty()) {
    throw logic_error("Cooking queue is empty.");
  }
  
  prepared.push_back(cooking.front());
  cooking.pop_front();

  cout << "Order is ready to be delivered." << endl;
  cout << prepared.back()->toString() << endl;

}

void Restaurant::departNextOrder(Driver* driver, Time time)  {

  if (prepared.empty()) {
      throw logic_error("No orders are currently ready to be delivered.");
  }
    
  auto nextOrder = prepared.front();
  prepared.pop_front();
  driver->depart(time, nextOrder);

  cout << "Order has departed." << endl;
}

void Restaurant::deliver(Driver *driver, Time time, double tip) {

    completed.push_back(driver->getOrder());
    driver->deliver(time, tip);
    totalDeliveryTime += completed.back()->getMinToDelivery();
    totalDeliveries++;

    cout << "Order has been delivered." << endl;

}

void Restaurant::clear() {
    for (auto & it : drivers) {
        delete it;
    }
    for (auto & it : cooking) {
        delete it;
    }
    for (auto & it : prepared) {
        delete it;
    }
    for (auto & it : completed) {
        delete it;
    }
}