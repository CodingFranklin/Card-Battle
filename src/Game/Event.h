//
// Created by lll on 2026/5/27.
//

#ifndef CARDBATTLE_EVENT_H
#define CARDBATTLE_EVENT_H
#include <functional>
#include <vector>


class Event {
    private:
        std::vector<std::function<void ()>> listeners;

    public:
        Event() = default;

        void addListener(std::function<void ()> listener) {
            listeners.push_back(listener);
        };

        void invoke() {
            for (std::function<void ()> listener : listeners) {
                listener();
            }
        };
};


#endif //CARDBATTLE_EVENT_H
