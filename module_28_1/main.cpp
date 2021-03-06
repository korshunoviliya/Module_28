#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>

struct Swimmer
{
    double total_time{0};
    double speed{0};
    std::string name{"none"};
    Swimmer(std::string name, double speed){
        this->name = name;
        this->speed = speed;
    }
};

class Swim
{
private:
    std::vector<Swimmer*> result;
    const int swimmingLane = 6;
    Swimmer *swimmer;
    std::vector<Swimmer*> swimmers;
    std::vector<std::thread> swim;
    std::mutex swim_access;
public:
    Swim() = default;

    void printResult(){
        std::cout << "*******************************" << std::endl;
        for (int i = 0; i < result.size(); ++i){
            std::cout << i + 1 << " Name:" << result[i]->name <<
                      " Total time:" << result[i]->total_time << " sec." << std::endl;
        }
        std::cout << "*******************************" << std::endl;
    }

    void startSwim(Swimmer *pSwimmer){
        const double max_distance = 20;
        double timer{0};
        double distance = max_distance;

        while(distance != 0) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            swim_access.lock();
            distance -= pSwimmer->speed;
            ++timer;
            if (distance <= 0) {
                distance = 0;
                std::cout << pSwimmer->name << " FINISH!" << std::endl;
            }
            else {
                std::cout << pSwimmer->name << " swam " << max_distance - distance << " meters." << std::endl;
            }
            swim_access.unlock();
        }
        pSwimmer->total_time = timer;

        swim_access.lock();
        result.push_back(pSwimmer);
        swim_access.unlock();
    }

    void init(){
        for(size_t i = 0; i < swimmingLane; ++i) {
            std::string swimmerName;
            std::cout << "Enter the name of the swimmer:";
            std::cin >> swimmerName;
            double swimmerSpeed;
            std::cout << "Enter the speed of the swimmer:";
            std::cin >> swimmerSpeed;
            swimmer = new Swimmer(swimmerName, swimmerSpeed);
            swimmers.push_back(swimmer);
        }
    }
    void initConst(){
        swimmer = new Swimmer{"ivan", 1.8};
        swimmers.push_back(swimmer);
        swimmer = new Swimmer{"alf", 1.5};
        swimmers.push_back(swimmer);
        swimmer = new Swimmer{"petr", 2.1};
        swimmers.push_back(swimmer);
    }

    void start(){

        for(auto & swimmer : swimmers) {
            swim.emplace_back(&Swim::startSwim, this, swimmer);
        }
        for(auto & i : swim) {
            i.join();
        }
    }
};

int main() {
    Swim *pSwim = new Swim;

    //pSwim->init();
    pSwim->initConst();
    pSwim->start();
    pSwim->printResult();

    delete pSwim;
    return 0;

}