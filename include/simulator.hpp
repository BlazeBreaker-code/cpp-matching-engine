#pragma once

#include <cstdint>
#include <random>
#include <vector>

#include "order_book.hpp"

class Simulator {
public:
    explicit Simulator(OrderBook& orderBook);

    void run(int eventCount);
    void printSummary() const;

private:
    void processAdd();
    void processCancel();

    OrderBook& book_;

    std::mt19937 rng_;
    std::uint64_t nextOrderId_ = 1;

    std::vector<std::uint64_t> liveOrderIds_;

    int eventsProcessed_ = 0;
    int addsProcessed_ = 0;
    int cancelsAttempted_ = 0;
    int cancelsSucceeded_ = 0;
};