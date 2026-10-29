

#include <stdio.h>
#include <iostream>
#include <string.h>


// define bitboard as 64 bit long integer 
using U64 = std::uint64_t;


// not A file constant

/**
    8 | 0 1 1 1 1 1 1 1 
    7 | 0 1 1 1 1 1 1 1 
    6 | 0 1 1 1 1 1 1 1 
    5 | 0 1 1 1 1 1 1 1 
    4 | 0 1 1 1 1 1 1 1 
    3 | 0 1 1 1 1 1 1 1 
    2 | 0 1 1 1 1 1 1 1 
    1 | 0 1 1 1 1 1 1 1 
    _________________________
        a b c d e f g h
**/
const U64 not_a_file = 18374403900871474942ULL;


// not H file constant

/**
    8 | 1 1 1 1 1 1 1 0 
    7 | 1 1 1 1 1 1 1 0 
    6 | 1 1 1 1 1 1 1 0 
    5 | 1 1 1 1 1 1 1 0 
    4 | 1 1 1 1 1 1 1 0 
    3 | 1 1 1 1 1 1 1 0 
    2 | 1 1 1 1 1 1 1 0 
    1 | 1 1 1 1 1 1 1 0 
    _________________________
        a b c d e f g h
**/
const U64 not_h_file = 9187201950435737471ULL;

// not HG file constant

/**
    8 | 1 1 1 1 1 1 0 0 
    7 | 1 1 1 1 1 1 0 0 
    6 | 1 1 1 1 1 1 0 0 
    5 | 1 1 1 1 1 1 0 0 
    4 | 1 1 1 1 1 1 0 0 
    3 | 1 1 1 1 1 1 0 0 
    2 | 1 1 1 1 1 1 0 0 
    1 | 1 1 1 1 1 1 0 0 
    _________________________
        a b c d e f g h
**/
const U64 not_hg_file = 4557430888798830399ULL;

// not AB file constant

/**
    8 | 0 0 1 1 1 1 1 1 
    7 | 0 0 1 1 1 1 1 1 
    6 | 0 0 1 1 1 1 1 1 
    5 | 0 0 1 1 1 1 1 1 
    4 | 0 0 1 1 1 1 1 1 
    3 | 0 0 1 1 1 1 1 1 
    2 | 0 0 1 1 1 1 1 1 
    1 | 0 0 1 1 1 1 1 1 
    _________________________
        a b c d e f g h
**/
const U64 not_ab_file = 18229723555195321596ULL;

// macros for bit ops 

//get bit for specific square
inline U64 get_bit(U64 bitboard, int square) {
    return bitboard & (1ULL << square);
}

// set bit in specific square
inline void set_bit(U64& bitboard, int square) {
    bitboard |= (1ULL << square);
}

//update bit in specific square from 1 to 0
inline void pop_bit(U64& bitboard, int square) {
    get_bit(bitboard, square) ? bitboard ^= (1ULL << square): 0;
}


//function to count bits in a bit board
static inline int count_bits(U64 bitboard){
    int count = 0;
    while (bitboard){
        bitboard &= bitboard - 1;
        count++;
    }

    return count;
}

//get least sig first bit index
static inline int get_least_sig_first_index(U64 bitboard){
    //make sure bitboard is not zero
    if (bitboard) {
        //count trailing bits before least sig bit
        return count_bits((bitboard & -bitboard)-1);
    }else{
        //return illegal index
        return -1;
    }
}



// enum board squares
/*
a8, b8, c8, d8, e8, f8, g8, h8
a7, b7, c7, d7, e7, f7, g7, h7
a6, b6, c6, d6, e6, f6, g6, h6
a5, b5, c5, d5, e5, f5, g5, h5
a4, b4, c4, d4, e4, f4, g4, h4
a3, b3, c3, d3, e3, f3, g3, h3
a2, b2, c2, d2, e2, f2, g2, h2
a1, b1, c1, d1, e1, f1, g1, h1 
*/




enum board_squares {
    a8, b8, c8, d8, e8, f8, g8, h8,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a1, b1, c1, d1, e1, f1, g1, h1,
};

//sides to move
enum sides {white, black};

//bishop and rook
enum { rook, bishop };

//pawn attacks table [side][square]
U64 pawn_attacks[2][64];

// knight attacks table [square]
U64 knight_attacks[64];

// king attacks table [square]
U64 king_attacks[64];

//relevancy occupancy bit count for every square on board BISHOP
const int bishop_relevant_bits[64] = {
    6, 5, 5, 5, 5, 5, 5, 6, 
    5, 5, 5, 5, 5, 5, 5, 5, 
    5, 5, 7, 7, 7, 7, 5, 5, 
    5, 5, 7, 9, 9, 7, 5, 5, 
    5, 5, 7, 9, 9, 7, 5, 5, 
    5, 5, 7, 7, 7, 7, 5, 5, 
    5, 5, 5, 5, 5, 5, 5, 5, 
    6, 5, 5, 5, 5, 5, 5, 6,
};


//relevancy occupancy bit count for every square on board ROOK
const int rook_relevant_bits[64] = {
    12, 11, 11, 11, 11, 11, 11, 12, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    12, 11, 11, 11, 11, 11, 11, 12,
};


const char *square_to_cord[] = {
    "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
    "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
    "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
    "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
    "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
    "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
    "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
    "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1",
};

/*

preserve human readable for future use 

"a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
"a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
"a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
"a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
"a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
"a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
"a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1",


*/

// print bitboard

void print_bitboard(U64 bitboard){
    //loop over ranks
    for (int rank = 0; rank < 8; rank++){
        //loop over file
        for (int file = 0; file < 8; file++){
            int square = rank * 8 + file;

            if (file == 0) {
                printf("%d | ", 8 - rank);
            }
            
            printf("%d ", get_bit(bitboard, square) ? 1 : 0);
        }
        printf("\n");
    }
    printf("_________________________");
    printf("\n    a b c d e f g h\n\n");


    printf("Bitboard: %llud\n\n", bitboard);
}



//mask pawn attacks
U64 mask_pawn_attacks(int side, int square){
    
    //result attacks bitboard
    U64 attacks = 0ULL;
    
    // piece bitboard
    U64 bitboard = 0ULL;

    //set piece on board
    set_bit(bitboard, square);
    
    // if white else black
    if(!side){
        //white pawns attack two sides >> 9 and >> 7 if they dont fall off board
        if((bitboard >> 7) & not_a_file){
            attacks |= (bitboard >> 7);
        }
        if((bitboard >> 9) & not_h_file){
            attacks |= (bitboard >> 9);
        }
    }else{
        // swap files and offsets
        if((bitboard << 7) & not_h_file){
            attacks |= (bitboard << 7);
        }
        if((bitboard << 9) & not_a_file){
            attacks |= (bitboard << 9);
        }
    }

    return attacks;
}


//mask knight attacks
U64 mask_knight_attacks(int square){
    //result attacks bitboard
    U64 attacks = 0ULL;
    
    // piece bitboard
    U64 bitboard = 0ULL;

    //set piece on board
    set_bit(bitboard, square);

    if((bitboard >> 17) & not_h_file){
        attacks |= (bitboard >> 17);
    }
    if((bitboard >> 15) & not_a_file){
        attacks |= (bitboard >> 15);
    }
    if((bitboard >> 10) & not_hg_file){
        attacks |= (bitboard >> 10);
    }
    if((bitboard >> 6) & not_ab_file){
        attacks |= (bitboard >> 6);
    }
    if((bitboard << 17) & not_a_file){
        attacks |= (bitboard << 17);
    }
    if((bitboard << 15) & not_h_file){
        attacks |= (bitboard << 15);
    }
    if((bitboard << 10) & not_ab_file){
        attacks |= (bitboard << 10);
    }
    if((bitboard << 6) & not_hg_file){
        attacks |= (bitboard << 6);
    }

    return attacks;
}

//mask king attacks
U64 mask_king_attacks(int square){
    //result attacks bitboard
    U64 attacks = 0ULL;
    
    // piece bitboard
    U64 bitboard = 0ULL;

    //set piece on board
    set_bit(bitboard, square);

    //shift bits 1 7 8 9 for each side << >>

    if ((bitboard >> 8)) attacks |= (bitboard >> 8);
    if((bitboard >> 1) & not_h_file){
        attacks |= (bitboard >> 1);
    }
    if((bitboard >> 7) & not_a_file){
        attacks |= (bitboard >> 7);
    }
    if((bitboard >> 9) & not_h_file){
        attacks |= (bitboard >> 9);
    }


    if ((bitboard << 8)) attacks |= (bitboard << 8);
    if((bitboard << 1) & not_a_file){
        attacks |= (bitboard << 1);
    }
    if((bitboard << 7) & not_h_file){
        attacks |= (bitboard << 7);
    }
    if((bitboard << 9) & not_a_file){
        attacks |= (bitboard << 9);
    }

    return attacks;
}

//mask bishop relevant occupancy bits for attacks
U64 mask_bishop_attacks(int square){
    //result attacks bitboard
    U64 attacks = 0ULL;
    
    //init rank and files
    int rank, file;

    //init target rank and files
    int target_r, target_f;
    target_r = square / 8;
    target_f = square % 8;

    //mask relevancty bishop occupancy squares
    for(rank = target_r+1, file = target_f+1; rank <= 6 && file <=6; rank++, file++){
        attacks |= (1ULL << (rank*8 + file));
    }
    for(rank = target_r-1, file = target_f+1; rank >=1 && file <=6; rank--, file++){
        attacks |= (1ULL << (rank*8 + file));
    }
    for(rank = target_r+1, file = target_f-1; rank <=6  && file >= 1; rank++, file--){
        attacks |= (1ULL << (rank*8 + file));
    }
    for(rank = target_r-1, file = target_f-1; rank >=1  && file >= 1; rank--, file--){
        attacks |= (1ULL << (rank*8 + file));
    }


    return attacks;
}

//mask rook relevant attacks
U64 mask_rook_attacks(int square){
    //result attacks bitboard
    U64 attacks = 0ULL;
    
    //init rank and files
    int rank, file;

    //init target rank and files
    int target_r, target_f;
    target_r = square / 8;
    target_f = square % 8;

    //mask relevancty rook occupancy squares

    // right and down
    for (rank = target_r+1; rank<=6; rank++){
        attacks |= (1ULL << (rank*8 + target_f));
    }
    for (file = target_f+1; file<=6; file++){
        attacks |= (1ULL << (target_r*8 + file));
    }
    //left and up
    for (rank = target_r-1; rank>=1; rank--){
        attacks |= (1ULL << (rank*8 + target_f));
    }
    for (file = target_f-1; file>=1; file--){
        attacks |= (1ULL << (target_r*8 + file));
    }

    
    return attacks;
}

// generate bish attacks on the fly
U64 bishop_attacks_on_the_fly(int square, U64 blockers){
    //result attacks bitboard
    U64 attacks = 0ULL;
    
    //init rank and files
    int rank, file;

    //init target rank and files
    int target_r, target_f;
    target_r = square / 8;
    target_f = square % 8;

    // gen bishop attacks
    for(rank = target_r+1, file = target_f+1; rank <= 7 && file <=7; rank++, file++){
        attacks |= (1ULL << (rank*8 + file));
        if ((1ULL << (rank*8 + file)) & blockers) break;
    }
    for(rank = target_r-1, file = target_f+1; rank >=0 && file <=7; rank--, file++){
        attacks |= (1ULL << (rank*8 + file));
        if ((1ULL << (rank*8 + file)) & blockers) break;
    }
    for(rank = target_r+1, file = target_f-1; rank <=7  && file >= 0; rank++, file--){
        attacks |= (1ULL << (rank*8 + file));
        if ((1ULL << (rank*8 + file)) & blockers) break;
    }
    for(rank = target_r-1, file = target_f-1; rank >=0  && file >= 0; rank--, file--){
        attacks |= (1ULL << (rank*8 + file));
        if ((1ULL << (rank*8 + file)) & blockers) break;
    }


    return attacks;
}


//generate rook attacks on the fly
U64 rook_attacks_on_the_fly(int square, U64 blockers){
    //result attacks bitboard
    U64 attacks = 0ULL;
    
    //init rank and files
    int rank, file;

    //init target rank and files
    int target_r, target_f;
    target_r = square / 8;
    target_f = square % 8;

    //mask relevancty rook occupancy squares and break for blockers

    // right and down
    for (rank = target_r+1; rank<=7; rank++){
        attacks |= (1ULL << (rank*8 + target_f));
        if((1ULL << (rank*8 + target_f)) & blockers) break;
    }
    for (file = target_f+1; file<=7; file++){
        attacks |= (1ULL << (target_r*8 + file));
        if((1ULL << (target_r*8 + file)) & blockers) break;
    }
    //left and up
    for (rank = target_r-1; rank>=0; rank--){
        attacks |= (1ULL << (rank*8 + target_f));
        if((1ULL << (rank*8 + target_f)) & blockers) break;
    }
    for (file = target_f-1; file>=0; file--){
        attacks |= (1ULL << (target_r*8 + file));
        if((1ULL << (target_r*8 + file)) & blockers) break;
    }

    return attacks;
}



//init leapers attacks (king knight pawns)
void init_leapers_attacks(){
    //loop over 64 squares

    for (int square = 0; square < 64; square++){
        //init pawn attacks
        pawn_attacks[white][square] = mask_pawn_attacks(white, square);
        pawn_attacks[black][square] = mask_pawn_attacks(black, square);

        //init knight attacks
        knight_attacks[square] = mask_knight_attacks(square);

        //init king attacks
        king_attacks[square] = mask_king_attacks(square);
    }

}


//set occupancy function
U64 set_occupancy(int index, int bits_in_mask, U64 attack_mask){
    //init occupancy map
    U64 occupancy = 0ULL;

    for (int count = 0; count < bits_in_mask; count++){
        //get least sig first bit index of attack mask
        int square = get_least_sig_first_index(attack_mask);

        //pop that bit back to 0
        pop_bit(attack_mask, square);

        //make sure occupancy is on board
        if(index & (1 << count)){
            //populate occupancy map
            occupancy |= (1ULL << square);
        }

    }
    
    //return occupancy
    return occupancy;
};


unsigned int random_state = 1804289383;

// get 32-bit pseudo legal numbers
unsigned int get_random_U32_number(){

    // get curr state
    unsigned int number = random_state;

    //XOR aglorithm
    number ^=  number << 13;
    number ^=  number >> 17;
    number ^=  number << 5;

    //update random number state
    random_state = number;

    return number;
}

// get 64-bit pseudo legal numbers
U64 get_random_U64_number(){
    
    U64 n1, n2, n3, n4;


    n1 = (U64)(get_random_U32_number() & 0xFFFF);
    n2 = (U64)(get_random_U32_number() & 0xFFFF);
    n3 = (U64)(get_random_U32_number() & 0xFFFF);
    n4 = (U64)(get_random_U32_number() & 0xFFFF);

    //return random number
    return n1 | (n2 << 16)| (n3 << 32) | (n4 << 48);
}

//generate magic number candidate
U64 generate_magic_number(){
    return get_random_U64_number() & get_random_U64_number() & get_random_U64_number();
}


// find the appropriate magic number
U64 find_magic_number(int square, int relevant_bits, int bishop){
    //init occs
    U64 occupancies[4096];

    //init attack tables
    U64 attacks[4096];

    //init used attacks
    U64 used_attacks[4096];

    //init attack mask for a current piece
    U64 attack_mask = bishop ? mask_bishop_attacks(square) : mask_rook_attacks(square);

    //init occ indices
    int occupancy_indicies = 1 << relevant_bits;

    for (int index = 0; index < occupancy_indicies; index++){
        // init occupancies
        occupancies[index] = set_occupancy(index, relevant_bits, attack_mask);

        //init attacks
        attacks[index] = bishop ? bishop_attacks_on_the_fly(square, occupancies[index]) : rook_attacks_on_the_fly(square, occupancies[index]);
    }

    //test magic numbers
    for (int random_count = 0; random_count < 100000000; random_count++){
        //generate magic number candidates
        U64 magic_number = generate_magic_number();

        if (count_bits((attack_mask * magic_number) & 0xFF00000000000000) < 6) continue;

        memset(used_attacks, 0ULL, sizeof(used_attacks));

        //init index and fail flag
        int index, fail;

        //test magic index loop
        for (index = 0, fail = 0; !fail && index < occupancy_indicies; index++){
            //get magic index
            int magic_index = (int)((occupancies[index] * magic_number) >> (64 - relevant_bits));

            //check if used attacks is empty
            if (used_attacks[magic_index] == 0ULL){
                used_attacks[magic_index] = attacks[index];
            }else if (used_attacks[magic_index] != attacks[index]){
                fail = 1;
            }
        }

        if (!fail) {
            //if magic number works then return it
            return magic_number;
        }



    }

    printf("___________magic number fails!!!____________");
    return 0ULL;
}


//init magic numbers

void init_magic_numbers(){

    //loop over 64 square
    for (int square = 0; square < 64; square++){
        //init rook magic numbers
        printf("0x%llxULL\n", find_magic_number(square, rook_relevant_bits[square], rook));
    }
}

int main(int argc, char* argv[]){

    //set initial bitboards
    U64 bboard = 0ULL;
    
    //practice masking pawn attacks



    // print pawn attack table for white to verify
    // for (int square = 0; square < 64; square++){
    //     print_bitboard(mask_rook_attacks(square));
    // }

    printf("\ncount: %d\n", 5);
    

    init_leapers_attacks();


    // printf("%ud\n",get_random_number());


    init_magic_numbers();
    


    //init occupancy
    // U64 occupancy = set_occupancy(4095, count_bits(attack_mask), attack_mask);

    
    // print_bitboard((U64)get_random_U32_number());
    // print_bitboard((U64)get_random_U32_number() & 0xFFFF); //slice upper /most significant 16 bits

    

    // print_bitboard(get_random_U64_number());
    // print_bitboard(get_random_U64_number() & get_random_U64_number() & get_random_U64_number());

    // //xor shift random number generator
    print_bitboard(generate_magic_number());
    

    //bryan kernighan's algorithms to remove the smallest releavant bit from a bitboard
    // print_bitboard(bitboard & -bitboard);


    // for (int rank = 8; rank >= 1; rank--){
    //     printf("a%d, b%d, c%d, d%d, e%d, f%d, g%d, h%d\n", rank, rank, rank, rank, rank, rank, rank, rank);
    // }

    




}