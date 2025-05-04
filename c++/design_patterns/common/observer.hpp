// Observer design patterns enables loose coupling and it is used to allow one object (subject)
// notify other objects (observers) about changes in its state. 
//
// Loose Coupling:
//   The subject and observers don't need to know about each other's implementations,
//   making the system more modular and easier to.
// Flexibility and Extensibility:
//   Adding or removing observers doesn't require modifying the subject, making the system easier to extend.
// Event Handling:
//  The pattern is well-suited for scenarios where you need to notify multiple objects about events 
//  or changes in the state of another object.
// 
// 
// Example:
// Consider a weather station (Subject) that collects temperature, humidity, and pressure. Multiple displays
// (Observers) need to display this data. Without the Observer pattern, each display would need to poll the 
// weather station constantly for updates. With the pattern, the weather station notifies the displays whenever 
// the data changes, and each display only receives the update.
//

#include <iostream>
#include <set>

class Observer{
public:
    virtual void update(float t) = 0;
};

class Subject{
public:
    virtual void addObserver(Observer& observer)=0;
    virtual void removeObserver(Observer& observer)=0;
    virtual void notifyObservers() = 0;
};

class Display: public Observer{
private:
    float m_t;
    int m_id;
public:

    Display(int id): m_id(id) {}

    virtual void update(float t) override
    {
        m_t = t;
    }

    void show()
    {
        std::cout<<"display "<<m_id<<" :"<< "temperatue: "<<m_t<<" °C"<<"\n";
    }
};


class WeatherStation: public Subject{
private:
    std::set<Observer*> m_observers;
    float m_t;
public:
    virtual void addObserver(Observer& observer) override
    {
        m_observers.insert(&observer);
    }

    virtual void removeObserver(Observer& observer) override
    {
        m_observers.erase(&observer);
    }

    virtual void notifyObservers() override
    {
        for(auto observer: m_observers)
        {
            observer->update(m_t);
        }
    }

    void setTemperature(float t)
    {
        m_t = t;
    }
};

int main()
{
    Display display1(1);
    Display display2(2);
    Display display3(3);

    WeatherStation weatherStation;
    weatherStation.addObserver(display1);
    weatherStation.addObserver(display2);
    weatherStation.addObserver(display3);
    weatherStation.setTemperature(23.3);
    weatherStation.notifyObservers();

    display1.show();
    display2.show();
    display3.show();

    return 0;
}