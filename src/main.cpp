#include <iostream>

#include "order_book.hpp"
#include "simulator.hpp"

int main() {
    OrderBook book;
    Simulator simulator(book);

    simulator.run(100);
    simulator.printSummary();

    book.printTrades();
    book.printBook();

    const auto bestBid = book.bestBid();
    const auto bestAsk = book.bestAsk();

    std::cout << "\n=== TOP OF BOOK ===\n";
    std::cout << "Best Bid: " << (bestBid ? std::to_string(*bestBid) : "None") << '\n';
    std::cout << "Best Ask: " << (bestAsk ? std::to_string(*bestAsk) : "None") << '\n';

    return 0;
}