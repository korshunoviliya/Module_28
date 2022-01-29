#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

static bool isBusy{false};
std::mutex wait_free_platform;

class Train{
private:
    char name;
    int travelTime;
public:
    Train() = default;
    Train(char inName, int inTravelTime): name(inName), travelTime(inTravelTime){}

    char getName() const {
        return name;
    }

    void setName(char name) {
        Train::name = name;
    }

    int getTravelTime() const {
        return travelTime;
    }

    void setTravelTime(int travelTime) {
        Train::travelTime = travelTime;
    }


};
void wait_to_arrive(Train train){
    std::this_thread::sleep_for(std::chrono::seconds(train.getTravelTime()));
    std::cout << "The train " << train.getName() << " pulled up to the station" << std::endl;
    if (isBusy) {
        std::cout << "The train " << train.getName() << " is waiting for a free platform" << std::endl;
    }
    wait_free_platform.lock();
    std::cout << "The train " << train.getName() << " arrived at the station" << std::endl;
    isBusy = true;
    std::string command;
    while (command != "d"){
    std::cin >> command;
    }
    std::cout << "the train " << train.getName() << " left the station" << std::endl;
    isBusy = false;
    wait_free_platform.unlock();
}

int main() {
    const int numberTrains = 3;
    Train *trains = new Train[numberTrains];
    trains[0].setName('A');
    trains[1].setName('B');
    trains[2].setName('C');
    int time;
    for (size_t i = 0; i < numberTrains; ++i){
        std::cout << "Enter the travel time to the station for the trains " <<
                  trains[i].getName() << ":";
        std::cin >> time;
        trains[i].setTravelTime(time);
    }

    std::vector<std::thread> trainTraffic;
    for(size_t i = 0; i < 3; ++i) {
        trainTraffic.emplace_back(wait_to_arrive, trains[i]);
    }
    trainTraffic[0].join();
    trainTraffic[1].join();
    trainTraffic[2].join();
    delete[] trains;
    return 0;
}
