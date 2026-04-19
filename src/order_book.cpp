#include "order_book.hpp"

#include <algorithm>
#include <iostream>

void OrderBook::addOrder(Order order) {
    if (order.side == Side::Buy) {
        matchBuyOrder(order);
        if (order.quantity > 0) bids_[order.price].push_back(order);
        return;
    }

    matchSellOrder(order);
    if (order.quantity > 0) asks_[order.price].push_back(order);
}

std::optional<int> OrderBook::bestBid() const {
    if (bids_.empty()) return std::nullopt;
    return bids_.begin()->first;
}

std::optional<int> OrderBook::bestAsk() const {
    if (asks_.empty()) return std::nullopt;
    return asks_.begin()->first;
}

void OrderBook::matchBuyOrder(Order& incomingOrder) {
    while (incomingOrder.quantity > 0 && !asks_.empty()) {
        auto bestAskLevelIt = asks_.begin();
        const int bestAskPrice = bestAskLevelIt->first;
        if (incomingOrder.price < bestAskPrice) break;

        auto& restingSellOrders = bestAskLevelIt->second;

        while (incomingOrder.quantity > 0 && !restingSellOrders.empty()) {
            Order& restingSellOrder = restingSellOrders.front();
            const int fillQuantity = std::min(incomingOrder.quantity, restingSellOrder.quantity);

            trades_.push_back({
                incomingOrder.id,
                restingSellOrder.id,
                bestAskPrice,
                fillQuantity
            });

            incomingOrder.quantity -= fillQuantity;
            restingSellOrder.quantity -= fillQuantity;

            if (restingSellOrder.quantity == 0) restingSellOrders.pop_front();
        }

        if (restingSellOrders.empty()) asks_.erase(bestAskLevelIt);
    }
}

void OrderBook::matchSellOrder(Order& incomingOrder) {
    while (incomingOrder.quantity > 0 && !bids_.empty()) {
        auto bestBidLevelIt = bids_.begin();
        const int bestBidPrice = bestBidLevelIt->first;
        if (incomingOrder.price > bestBidPrice) break;

        auto& restingBuyOrders = bestBidLevelIt->second;

        while (incomingOrder.quantity > 0 && !restingBuyOrders.empty()) {
            Order& restingBuyOrder = restingBuyOrders.front();
            const int fillQuantity = std::min(incomingOrder.quantity, restingBuyOrder.quantity);

            trades_.push_back({
                restingBuyOrder.id,
                incomingOrder.id,
                bestBidPrice,
                fillQuantity
            });

            incomingOrder.quantity -= fillQuantity;
            restingBuyOrder.quantity -= fillQuantity;

            if (restingBuyOrder.quantity == 0) restingBuyOrders.pop_front();
        }

        if (restingBuyOrders.empty()) bids_.erase(bestBidLevelIt);
    }
}

bool OrderBook::cancelOrder(std::uint64_t orderId) {
    for (auto levelIt = bids_.begin(); levelIt != bids_.end(); ++levelIt) {
        auto& orders = levelIt->second;
        auto it = std::find_if(orders.begin(), orders.end(),
            [orderId](const Order& o) { return o.id == orderId; });
        
        if (it == orders.end()) continue;
        orders.erase(it);
        if (orders.empty()) bids_.erase(levelIt);
        return true;
    }

    for (auto levelIt = asks_.begin(); levelIt != asks_.end(); ++levelIt) {
        auto& orders = levelIt->second;
        auto it = std::find_if(orders.begin(), orders.end(),
            [orderId](const Order& o) { return o.id == orderId; });
        
        if (it == orders.end()) continue;
        orders.erase(it);
        if (orders.empty()) asks_.erase(levelIt);
        return true;
    }

    return false;
}

void OrderBook::printBook() const {
    std::cout << "\n=== ORDER BOOK ===\n";

    std::cout << "Asks:\n";
    for (const auto& [price, orders] : asks_) {
        int totalQuantity = 0;
        for (const auto& order : orders) totalQuantity += order.quantity;

        std::cout << "Price: " << price
                  << " Qty: " << totalQuantity
                  << " Orders: " << orders.size()
                  << '\n';
    }

    std::cout << "\nBids:\n";
    for (const auto& [price, orders] : bids_) {
        int totalQuantity = 0;
        for (const auto& order : orders) totalQuantity += order.quantity;

        std::cout << "Price: " << price
                  << " Qty: " << totalQuantity
                  << " Orders: " << orders.size()
                  << '\n';
    }

    std::cout << "========================\n";
}

void OrderBook::printTrades() const {
    std::cout << "\n=== TRADES ===\n";

    for (const auto& trade : trades_) {
        std::cout << "BuyOrderId: " << trade.buyOrderId
                  << " SellOrderId: " << trade.sellOrderId
                  << " Price: " << trade.price
                  << " Qty: " << trade.quantity
                  << '\n';
    }

    std::cout << "========================\n";
}