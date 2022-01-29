#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>

const double max_distance = 50;
std::mutex swim_access;

class Swimmer{
private:
    std::string name{"none"};
    double speed{0.0};
    double total_time{0};
public:
    Swimmer() = default;
    Swimmer(std::string inName, double inSpeed) : name(inName), speed(inSpeed){}

    const std::string &getName() const {
        return name;
    }

    double getSpeed() const {
        return speed;
    }

    double getTotalTime() const {
        return total_time;
    }

    void setTotalTime(double totalTime) {
        Swimmer::total_time = totalTime;
    }
};

void startSwim(Swimmer* swimmer)
{
    double timer{0};
    double distance = max_distance;
    while(distance != 0) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        swim_access.lock();
        distance -= swimmer->getSpeed();
        ++timer;
        if (distance < 0) distance = 0;
        std::cout << swimmer->getName() << " swam " << max_distance - distance << " meters." << std::endl;
        swim_access.unlock();
    }
    swim_access.lock();
    swimmer->setTotalTime(timer);
    swim_access.unlock();
}

bool comp(Swimmer *a,Swimmer *b){
    return a->getTotalTime() < b->getTotalTime();
}

int main() {
    const int swimmingLane = 6;
    std::vector<Swimmer*> swimmers;
    Swimmer *swimmer;

    swimmer = new Swimmer{"ivan", 1.8};
    swimmers.push_back(swimmer);
    swimmer = new Swimmer{"alf", 1.5};
    swimmers.push_back(swimmer);
    swimmer = new Swimmer{"petr", 2.1};
    swimmers.push_back(swimmer);
    /*
    for(size_t i = 0; i < swimmingLane; ++i) {
        std::string swimmerName;
        std::cout << "Enter the name of the swimmer:";
        std::cin >> swimmerName;
        double swimmerSpeed;
        std::cout << "Enter the speed of the swimmer:";
        std::cin >> swimmerSpeed;
        swimmer = new Swimmer(swimmerName, swimmerSpeed);
        swimmers.push_back(swimmer);
    }*/
    std::vector<std::thread> swim;
    for(size_t i = 0; i < swimmers.size(); ++i) {
        swim.emplace_back(startSwim, swimmers[i]);
    }
    for(size_t i = 0; i < swim.size(); ++i) {
        swim[i].join();
    }
    std::sort(swimmers.begin(), swimmers.end(), comp);

    std::cout << "*******************************" << std::endl;
    for(size_t i = 0; i < swimmers.size(); ++i) {

        std::cout << i + 1 << " Name:" << swimmers[i]->getName() <<
                    " Total time:" << swimmers[i]->getTotalTime() << " sec." << std::endl;
    }
    delete swimmer;
    return 0;
}