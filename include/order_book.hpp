#pragma once

#include <cstdint>
#include <deque>
#include <map>
#include <vector>

#include "order.hpp"
#include "trade.hpp"

class OrderBook {
public:
    void addOrder(Order order);
    bool cancelOrder(std::uint64_t orderId);

    std::optional<int> bestBid() const;
    std::optional<int> bestAsk() const;

    void printBook() const;
    void printTrades() const;

private:
    void matchBuyOrder(Order& incomingOrder);
    void matchSellOrder(Order& incomingOrder);

    std::map<int, std::deque<Order>, std::greater<int>> bids_;
    std::map<int, std::deque<Order>> asks_;
    std::vector<Trade> trades_;
};
