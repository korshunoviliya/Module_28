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

struct OrderType{
    int orderNumber{0};
    int dish;

    enum Dish {
        PIZZA,
        SOUP,
        STEAK,
        SALAD,
        SUSHI,
    };

    static std::string typeDish(int dish) {
        if (dish == PIZZA) return "Pizza";
        else if (dish == SOUP) return "Soup";
        else if (dish == STEAK) return "Steak";
        else if (dish == SALAD) return "Salad";
        else return "Sushi";
    }
    friend std::ostream& operator<< (std::ostream &out, const OrderType &orderType);
};

std::ostream& operator<< (std::ostream &out, const OrderType &orderType){
    out << "#" << orderType.orderNumber << " - " << OrderType::typeDish(orderType.dish);
    return out;
}

class Kitchen {
    static int numberOfDeliveries;
    bool kitchenIsFree{true};
    const int timeOfDelivery = 30;
    const int totalDelivery = 10;

    std::queue<OrderType> orderQueue;
    std::queue<OrderType> deliveryQueue;

    std::mutex wait_orderQueue;
    std::mutex wait_deliveryQueue;

    void delivery(){
        while (totalDelivery > numberOfDeliveries) {

            std::this_thread::sleep_for(std::chrono::seconds(timeOfDelivery));

            if (!deliveryQueue.empty()){
                std::cout << "Order handed over to courier:" << std::endl;
                int sizeDeliveryQueue = deliveryQueue.size();
                for(int i = 0; i < sizeDeliveryQueue; ++i){
                    std::cout << "\t" << i + 1 << ")"
                              << deliveryQueue.front() << std::endl;
                    wait_deliveryQueue.lock();
                    deliveryQueue.pop();
                    wait_deliveryQueue.unlock();
                }
                ++numberOfDeliveries;
            }
        }
    }
    void cooking(){
        while (totalDelivery > numberOfDeliveries) {

            if (kitchenIsFree && !orderQueue.empty()) {
                kitchenIsFree = false;
                wait_orderQueue.lock();
                OrderType temp = orderQueue.front();
                orderQueue.pop();
                wait_orderQueue.unlock();
                std::cout << "The order has been sent to the kitchen: "
                          << temp << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(getRandom(5, 15)));
                std::cout << "The order: " << temp
                          << " is ready!" << std::endl;

                wait_deliveryQueue.lock();
                deliveryQueue.push(temp);
                wait_deliveryQueue.unlock();
                kitchenIsFree = true;
            }
        }
    }

    void order() {
        OrderType newOrder;
        while (totalDelivery > numberOfDeliveries){
            std::this_thread::sleep_for(std::chrono::seconds(getRandom(5,10)));
            newOrder.dish= getRandom(0,4);
            ++newOrder.orderNumber;
            if (newOrder.orderNumber == 100) newOrder.orderNumber = 1;
            std::cout << "New order accepted: " << newOrder << std::endl;

            wait_orderQueue.lock();
            orderQueue.push(newOrder);
            wait_orderQueue.unlock();
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
