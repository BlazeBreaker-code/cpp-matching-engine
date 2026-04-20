#include "simulator.hpp"

#include <iostream>

#include "order.hpp"

Simulator::Simulator(OrderBook& orderBook) 
    : book_(orderBook), rng_(std::random_device{}()) {}

void Simulator::run(int eventCount) {
    std::uniform_int_distribution<int> actionDist(1, 100);

    for (int i = 0; i < eventCount; ++i) {
        ++eventsProcessed_;

        const int action = actionDist(rng_);
        if (action <= 80 || liveOrderIds_.empty()) {
            processAdd();
            continue;
        }

        processCancel();

    }
}

void Simulator::processAdd() {
    std::uniform_int_distribution<int> sideDist(0, 1);
    std::uniform_int_distribution<int> priceDist(90, 110);
    std::uniform_int_distribution<int> quantityDist(1, 10);

    const Side side = sideDist(rng_) == 0 ? Side::Buy : Side::Sell;
    const int price = priceDist(rng_);
    const int quantity = quantityDist(rng_);

    const std::uint64_t orderId = nextOrderId_++;
    const bool rested = book_.addOrder(Order{orderId, side, price, quantity});
    if (rested) liveOrderIds_.push_back(orderId);
    ++addsProcessed_;
}

void Simulator::processCancel() {
    if (liveOrderIds_.empty()) return;

    ++cancelsAttempted_;

    std::uniform_int_distribution<std::size_t> indexDist(0, liveOrderIds_.size() - 1);
    const std::size_t index = indexDist(rng_);
    const std::uint64_t orderId = liveOrderIds_[index];

    const bool cancelled = book_.cancelOrder(orderId);
    if (cancelled) {
        liveOrderIds_[index] = liveOrderIds_.back();
        liveOrderIds_.pop_back();
        ++cancelsSucceeded_;
    }
}

void Simulator::printSummary() const {
    std::cout << "\n=== SIMULATION SUMMARY ===\n";
    std::cout << "Total Events Processed: " << eventsProcessed_ << '\n';
    std::cout << "Add Orders Processed: " << addsProcessed_ << '\n';
    std::cout << "Cancel Attempts: " << cancelsAttempted_ << '\n';
    std::cout << "Successful Cancels: " << cancelsSucceeded_ << '\n';
}