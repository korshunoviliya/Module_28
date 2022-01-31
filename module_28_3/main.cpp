#include <iostream>
#include <thread>
#include <mutex>
#include <random>
#include <queue>
#include <ctime>

int getRandom(int min, int max) {
    static std::mt19937 gen(time(nullptr));
    std::uniform_int_distribution<> uid(min, max);
    return uid(gen);
}

class Kitchen {
    static int numberOfDeliveries;
    bool kitchenIsFree{true};
    std::mutex wait_for_kitchen;
    std::mutex wait_for_courier;
    std::mutex wait_for_cooking;
    const int timeOfDelivery = 30;
    const int totalDelivery = 3;
    std::queue<int> orderQueue;
    std::queue<int> deliveryQueue;


    enum Dish {
        PIZZA,
        SOUP,
        STEAK,
        SALAD,
        SUSHI,
    };

    std::string typeDish(int dish) {

        if (dish == PIZZA) return "Pizza";
        else if (dish == SOUP) return "Soup";
        else if (dish == STEAK) return "Steak";
        else if (dish == SALAD) return "Salad";
        else return "Sushi";
    }

    void delivery(){
        while (totalDelivery > numberOfDeliveries) {
            //std::lock_guard<std::mutex> lk{wait_for_courier};
            wait_for_courier.lock();
            std::this_thread::sleep_for(std::chrono::seconds(timeOfDelivery));
            if (!deliveryQueue.empty()){
                std::cout << "Order handed over to courier:" << std::endl;
                int sizeDeliveryQueue = deliveryQueue.size();
                for(int i = 0; i < sizeDeliveryQueue; ++i){
                    std::cout << "\t" << i + 1 << ")"
                              << typeDish(deliveryQueue.front()) << std::endl;
                    deliveryQueue.pop();
                }
                ++numberOfDeliveries;
            }
            wait_for_courier.unlock();
        }
    }
    void cooking(){
        while (totalDelivery > numberOfDeliveries) {
            wait_for_cooking.lock();
            if (kitchenIsFree && !orderQueue.empty()) {
                kitchenIsFree = false;
                std::cout << "The order has been sent to the kitchen: "
                          << typeDish(orderQueue.front()) << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(getRandom(5, 15)));
                std::cout << "The order: " << typeDish(orderQueue.front())
                          << " is ready!" << std::endl;
                deliveryQueue.push(orderQueue.front());
                orderQueue.pop();
                kitchenIsFree = true;
            }
            wait_for_cooking.unlock();
        }
    }

    void order() {
        while (totalDelivery > numberOfDeliveries){

            wait_for_kitchen.lock();
            std::this_thread::sleep_for(std::chrono::seconds(getRandom(5,10)));
            int newOrder = getRandom(0,4);
            std::cout << "New order accepted: " << typeDish(newOrder) << std::endl;
            orderQueue.push(newOrder);
            wait_for_kitchen.unlock();
        }
    }

public:
    void start(){
        std::thread orders (&Kitchen::order, this);
        std::thread  cook (&Kitchen::cooking, this);
        std::thread deliver (&Kitchen::delivery, this);

        orders.detach();
        cook.detach();
        deliver.join();

        std::cout << "The delivery is close!!!" << std::endl;
    }
};

int Kitchen::numberOfDeliveries = 0;

int main() {
    Kitchen kitchen;
    kitchen.start();
    return 0;
}
