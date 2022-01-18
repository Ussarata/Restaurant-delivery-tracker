#include "Time.hpp"

enum orderState {
  inRes, outRes, delivered
};


class Order {

  string info;
  orderState state; 
  Time timePlaced;
  int timeTaken = 0;

public:
  Order();
  //post: default constructor

  Order(Time time, string &info);
  //post: copy constructor

  void depart();
  //pre: order is at the restaurant.
  //post: order is out of the restaurant.

  void deliver(Time time);
  //pre: order is out of the restaurant
  //post: order is delivered. Time of delivery is recorded.

  int getMinToDelivery();
  //pre: Order is delivered
  //post: returns the time taken for delivery in minutes.

  string toString();
  //post: returns a string of the order details.

  Order& operator=(const Order& order);
  //post: assignment operator.
};


Order::Order() {
  state = inRes;
  info = "Null";
}

Order::Order(Time time, string &info) {
    state = inRes;
    timePlaced = time;
    this->info = info;

}



void Order::depart()  {

  if (state != inRes) {
    throw logic_error("Order is either out for delivery or delivered.");
  }
  else {
    state = outRes;
  }
}


void Order:: deliver(Time time) {
  if (state != outRes){
    throw logic_error("Order is either still in restaurant or delivered.");
  }
  else {
    state = delivered;
    timeTaken = Time::elapsedMin(timePlaced, time);
  }  
}

int Order::getMinToDelivery(){
    if (state != delivered) {
        throw logic_error("Order is not delivered");
    }
    return timeTaken;
}

string Order::toString() {
    return  + "Order info: " + info + ", Ordered time: " + timePlaced.toString();
}

Order &Order::operator=(const Order& o) = default;
