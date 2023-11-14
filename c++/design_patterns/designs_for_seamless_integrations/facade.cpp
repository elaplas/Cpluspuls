/***
 * The "Facade" design pattern is used to provide a simplified and unified interface
 * to a complex subsystem, making it easier for clients to interact with the system. 
 * In this example, we'll create a simple audio system that consists of multiple sub-components,
 * and then we'll implement a facade to simplify its usage.
 * 
*/


#include <iostream>

// Subsystem classes

class Amplifier {
public:
    void on() {
        std::cout << "Amplifier is on" << std::endl;
    }

    void off() {
        std::cout << "Amplifier is off" << std::endl;
    }
};

class CDPlayer {
public:
    void play() {
        std::cout << "CDPlayer is playing" << std::endl;
    }

    void stop() {
        std::cout << "CDPlayer is stopped" << std::endl;
    }
};

class Speakers {
public:
    void on() {
        std::cout << "Speakers are on" << std::endl;
    }

    void off() {
        std::cout << "Speakers are off" << std::endl;
    }
};

// Facade class

class AudioSystem {
private:
    Amplifier amplifier;
    CDPlayer cdPlayer;
    Speakers speakers;

public:
    void turnOn() {
        amplifier.on();
        cdPlayer.play();
        speakers.on();
    }

    void turnOff() {
        speakers.off();
        cdPlayer.stop();
        amplifier.off();
    }
};

// Client code

int main() {
    // Using the AudioSystem facade to control the audio system
    AudioSystem audioSystem;
    audioSystem.turnOn();

    // ... Perform some actions with the audio system ...

    audioSystem.turnOff();

    return 0;
}
