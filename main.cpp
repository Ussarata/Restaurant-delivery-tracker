#include "Restaurant.hpp"
using namespace std;

void print_help();

int main() {

    Restaurant d;

    print_help();

    bool run = true;

    do {
    string command, first, second, third, fourth;
    getline(cin, command);

    string commandCopy = command;

    size_t pos = command.find(' ');
    first = command.substr(0, pos);
    command.erase(0, pos + 1);

    size_t pos2 = command.find(' ');
    second = command.substr(0, pos2);
    command.erase(0, pos2 + 1);

    size_t pos3 = command.find(' ');
    third = command.substr(0, pos3);
    command.erase(0, pos3 + 1);

    size_t pos4 = command.find(' ');
    fourth = command.substr(0, pos4);
    command.erase(0, pos4 + 1);

    if (first == "login") {
        if(d.getDriver(second) == nullptr) {
            auto dr = new Driver(second);
            d.addDriver(dr);
            dr->login();
        }
        else {
            d.getDriver(second)->login();
        }
    }

    else if (first == "logout") {
        if (d.getDriver(second) == nullptr) {
            cout << "We dont have a driver called " << second << "." << endl;
        }
        else {
            d.getDriver(second)->logout();
        }
    }

    else if (first == "order" || first == "Order") {
        third = commandCopy.substr(pos + 7);
        string hours = second.substr(0, 2);
        string min = second.substr(3);
        int h = stoi(hours);
        int m = stoi(min);
        Time t1(h, m);
        d.addOrder(t1, third);
    }

    else if (first == "serve") {
        d.serveNextOrder();
    }

    else if (first == "depart") {
        string hours = second.substr(0, 2);
        string min = second.substr(3);
        int h = stoi(hours);
        int m = stoi(min);
        Time t(h, m);
        d.departNextOrder(d.getDriver(third), t);
    }

    else if (first == "deliver") {

        string hours = second.substr(0, 2);
        string min = second.substr(3);
        int h = stoi(hours);
        int m = stoi(min);
        float tip = stof(fourth);
        Time t(h, m);

        d.deliver(d.getDriver(third),t,tip);
    }

    else if (first == "arrive") {

        string hours = second.substr(0, 2);
        string min = second.substr(3);
        int h = stoi(hours);
        int m = stoi(min);
        Time t4(h, m);
        d.getDriver(third)->arrive(t4);
    }

    else if (first == "status") {
        d.status();
    }

    else if (first == "summary") {
        d.summary();
    }
    else if (first == "quit") {
      d.clear();
      run = false;
    }

    else if (first == "help") {
        print_help();
    }

    else {
      cout << "Invalid input" << endl;
    }

} while (cin && run);

    return 0;
}

void print_help() {
    cout << "Welcome to our delivery interface"<< endl;
    cout << "--------------------------------------------------------------------" << endl;
    cout << "Our times use the 24 hour system. No need to specify AM or PM."<< endl;
    cout << "All times must be entered in the following format: HH:MM" << endl;
    cout << "An order must be placed to be served, served to be departed and departed to be delivered."<< endl;
    cout << "--------------------------------------------------------------------" << endl;
    cout << "To login, enter: login [driver]." << endl;
    cout << "To logout, enter: logout [driver]." << endl;
    cout << "To place an order, enter: order [time] [info]." << endl;
    cout << "To serve an order, enter: serve [time]." << endl;
    cout << "To depart an order, enter: depart [time] [driver]." << endl;
    cout << "To deliver an order, enter: deliver [time] [driver] [tip]." << endl;
    cout << "To announce the return of the driver, enter: arrive [time] [driver]." << endl;
    cout << "To check the status of the restaurant, enter: status." << endl;
    cout << "To check the summary for the day, enter: summary." << endl;
    cout << "To leave the interface, enter: quit." << endl;
    cout << "To get these commands once more, enter: help"<< endl;
    cout << "--------------------------------------------------------------------" << endl;
}