#pragma once

#include <cstdint>

enum class Side {
    Buy,
    Sell
};

struct Order {
    std::uint64_t id;
    Side side;
    int price;
    int quantity;
};
