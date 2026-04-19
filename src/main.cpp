#include <iostream>
#include "order.hpp"

int main() {
    Order o{1, Side::Buy, 100, 10};
    
    std::cout   << "Order created -> "
                << "ID: " << o.id
                << " Price: " << o.price
                << " Quantity: " << o.quantity
                << std::endl;
    
    return 0;
}
