#include <iostream>

#include "order.hpp"
#include "order_book.hpp"

int main() {
    OrderBook book;

    book.addOrder(Order{1, Side::Buy, 100, 10});
    book.addOrder(Order{2, Side::Sell, 101, 5});
    book.addOrder(Order{3, Side::Sell, 100, 4});
    book.addOrder(Order{4, Side::Buy, 101, 6});

    book.printTrades();
    book.printBook();

    const auto bestBid = book.bestBid();
    const auto bestAsk = book.bestAsk();

    std::cout << "\n=== TOP OF BOOK ===\n";
    std::cout << "Best Bid: " << (bestBid ? std::to_string(*bestBid) : "None") << '\n';
    std::cout << "Best Ask: " << (bestAsk ? std::to_string(*bestAsk) : "None") << '\n';

    return 0;
}