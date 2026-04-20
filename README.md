# C++ Limit Order Book & Matching Engine

A deterministic, event-driven limit order book implemented in C++ with price-time priority matching.

The system supports order matching, partial fills, cancellations, and simulated order flow, along with performance metrics such as trade volume, spread, and throughput.

The goal of this project is to model the core behavior of a trading engine while emphasizing correctness, reproducibility, and measurable system performance.

---

# Features

### Price-Time Priority Matching
Orders are matched based on best price first, and FIFO (first-in-first-out) within each price level.

### Partial Fills
Orders can be partially filled across multiple price levels, with remaining quantities correctly preserved.

### Order Cancellation
Supports cancellation of resting orders within the book.

### Deterministic Simulation
Simulation runs are fully reproducible using a fixed random seed, enabling consistent debugging and benchmarking.

### Event-Driven Order Flow
Simulates a mix of order additions and cancellations to exercise the matching engine under realistic conditions.

### Engine Metrics
Tracks key performance metrics including:
- Total trades executed
- Total traded volume
- Average trade size
- Final spread
- Throughput (events per second)

---

# Example Run

    Seed: 42
    Events: 100000

    Trades Executed: 57956
    Total Traded Volume: 176130
    Final Spread: 1
    Average Trade Size: 3.04

    Elapsed Time: 0.381939s
    Throughput: 261821.68 events/sec

---

# Architecture

The system is structured into two main components:

### OrderBook
- Maintains bid and ask sides using ordered price levels
- Handles matching logic, partial fills, and trade recording
- Supports cancellation of resting orders
- Provides aggregate metrics (volume, trade count, spread)

### Simulator
- Generates randomized order flow (adds + cancels)
- Tracks active orders for cancellation
- Uses deterministic seeding for reproducible runs
- Drives the engine under simulated conditions

---

# Data Structures

- `std::map<int, std::deque<Order>>`
  - Maintains sorted price levels
  - Enables efficient best bid / best ask access
- `std::deque`
  - Preserves FIFO order within each price level

---

# Design Decisions

### Ordered Maps for Price Levels
Using `std::map` ensures:
- automatic sorting of price levels
- O(log N) insertion and lookup
- simple and correct top-of-book access

### FIFO Execution
`std::deque` is used to guarantee strict time priority within each price level.

### Cancellation Strategy
- Current implementation performs a linear scan to locate orders
- Simpler and sufficient for simulation scale
- Future improvement: indexed order lookup for O(1) cancellation

### Deterministic Simulation
A fixed random seed ensures:
- reproducible results
- consistent debugging
- reliable performance benchmarking

---

# Performance

The engine processes simulated order flow efficiently while maintaining correctness.

Example benchmark:

    ~260K events/sec (100K event simulation)

Performance is influenced by:
- map operations (O(log N))
- number of active price levels
- cancellation scan cost

---

# Build & Run

### Build

    mkdir build
    cd build
    cmake ..
    make

### Run

    ./engine

---

# Project Structure

    src/
      main.cpp
      order_book.cpp
      simulator.cpp

    include/
      order_book.hpp
      simulator.hpp

---

# Future Improvements

- Indexed order lookup for O(1) cancellation
- More cache-friendly data structures
- Reduced memory allocations
- Multi-threaded simulation
- Support for multiple instruments

---

# Motivation

Trading systems require fast, deterministic, and correct handling of large volumes of events.

This project focuses on modeling those core behaviors while maintaining clarity and measurability, providing a foundation for further exploration into low-latency system design.
