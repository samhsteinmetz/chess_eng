#include <iostream>
#include <cstdint>
#include <iomanip>
#include <bitset>

void debug_bitboard(uint64_t bitboard) {
    // Print the raw hexadecimal format
    std::cout << "Hexadecimal: 0x" 
              << std::setfill('0') << std::setw(16) 
              << std::hex << std::uppercase << bitboard << "ULL\n";
              
    // Print the raw decimal format
    std::cout << "Decimal:     " << std::dec << bitboard << "\n\n";
    
    // Print the rank-by-rank binary breakdown
    std::cout << "Rank Breakdown (Binary):\n";
    for (int rank = 7; rank >= 0; rank--) {
        std::cout << "Rank " << rank + 1 << ": ";
        
        // Extract the 8 bits for the current rank
        uint8_t rank_bits = (bitboard >> (rank * 8)) & 0xFF;
        
        // Convert to binary string (8 bits)
        std::bitset<8> binary_row(rank_bits);
        
        // Print the bits separated by spaces for visual scanning
        std::string s = binary_row.to_string();
        for (char c : s) {
            std::cout << c << " ";
        }
        
        // Print the individual hex pair for this specific rank
        std::cout << " | Hex: 0x" << std::setw(2) << (int)rank_bits << "\n";
    }
}

int main() {
    uint64_t bitboard = 0x000000000000FFFFULL; // Example bitboard
    debug_bitboard(bitboard);
    return 0;
}
