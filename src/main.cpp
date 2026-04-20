#include <chrono>
#include <iomanip>
#include <iostream>

#include "order_book.hpp"
#include "simulator.hpp"

int main() {
    OrderBook book;

    constexpr std::uint32_t seed = 42;
    constexpr int eventCount = 100000;

    Simulator simulator(book, seed);

    const auto start = std::chrono::high_resolution_clock::now();
    simulator.run(eventCount);
    const auto end = std::chrono::high_resolution_clock::now();

    const double elapsedSeconds = std::chrono::duration<double>(end - start).count();
    const double throughput =
        elapsedSeconds == 0.0 ? 0.0 : static_cast<double>(eventCount) / elapsedSeconds;

    simulator.printSummary();

    if (eventCount <= 200) {
        book.printTrades();
        book.printBook();
    }

    const auto bestBid = book.bestBid();
    const auto bestAsk = book.bestAsk();
    const auto spread = book.spread();

    const std::size_t tradeCount = book.tradeCount();
    const int totalTradedVolume = book.totalTradedVolume();
    const double averageTradeSize =
        tradeCount == 0 ? 0.0 : static_cast<double>(totalTradedVolume) / tradeCount;

    std::cout << "\n=== TOP OF BOOK ===\n";
    std::cout << "Best Bid: " << (bestBid ? std::to_string(*bestBid) : "None") << '\n';
    std::cout << "Best Ask: " << (bestAsk ? std::to_string(*bestAsk) : "None") << '\n';

    std::cout << std::fixed << std::setprecision(6);

    std::cout << "\n=== ENGINE METRICS ===\n";
    std::cout << "Trades Executed: " << tradeCount << '\n';
    std::cout << "Total Traded Volume: " << totalTradedVolume << '\n';

    std::cout << "Final Spread: ";
    if (spread) std::cout << *spread << '\n';
    else std::cout << "None\n";

    std::cout << "Average Trade Size: " << averageTradeSize << '\n';
    std::cout << "Elapsed Time (s): " << elapsedSeconds << '\n';
    std::cout << "Throughput (events/sec): " << throughput << '\n';

    return 0;
}