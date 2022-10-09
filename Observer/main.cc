#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// The interface to update observers.
class Observer {
    public:
        virtual void Update() = 0;
};

class StockObserver : public Observer {
    public:
        void Update() override {
            // Processes stock event.
        }
};

class FoodObserver : public Observer {
    public:
        void Update() override {
            // Processes food event.
        }
};

// The interface to notify observer..
class Notifier {
    public:
        virtual Register(int event, Observer* observer) = 0;

        virtual UnRegister(Observer* observer) = 0;

        virtual Notify(int event) = 0;
};

// The reason to have a `Notifier` interface is because`Secretary` is one of
// notifier but not the only one, it could also be a security guard, boss, etc.
class Secretary : public Notifier {
    public:
        // Each observer registers event to notify.
        void Register(int event, Observer* observer) override {
            if (observer == nullptr) {
                return;
            }
            event_table_[event].insert(observer);
        }

        void UnRegister(Observer* observer) override {
            for (auto& [event, observers] : observer) {
                auto it = observers.find(observer);

                if (it != observers.end()) {
                    observers.erase(observer);
                }
            }
        }

        // Notifies `event` to observers.
        void Notify(int event) override {
            auto it = event_table_.find(event);

            if (it == event_table_.end()) {
                return;
            }

            for (Observer* observer : it->second) {
                observer->Update();
            }
        }

    private:
        unordered_map<int, unordered_sete<Observer*>> event_table_;
}

int main(int argc, char *argv[]) {
    StockObserver stock;
    FoodObserver food;
    Secretary secretary;

    secretary.Register(/*event=*/0, &stock);
    secretary.Register(/*event=*/1, &food);

    secretary.Notify(/*event=*/1);

    return 0;
}

//  Notes
//  1.  Observer pattern can also be publisher/subscriber pattern.
