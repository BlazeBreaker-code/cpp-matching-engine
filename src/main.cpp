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

    std::cout << "\n=== ENGINE METRICS ===\n";
    std::cout << "Trades Executed: " << book.tradeCount() << '\n';
    std::cout << "Total Traded Volume: " << book.totalTradedVolume() << '\n';

    const auto spread = book.spread();
    std::cout << "Final Spread: " << (spread ? std::to_string(*spread) : "None") << '\n';

    const auto tradeCount = book.tradeCount();
    const double averageTradeSize =
        tradeCount == 0 ? 0.0 : static_cast<double>(book.totalTradedVolume()) / tradeCount;

    std::cout << "Average Trade Size: " << averageTradeSize << '\n';
    
    return 0;
}