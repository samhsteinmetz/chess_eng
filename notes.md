### functions to write
PerfTest functionality to check if move generation is accurate




** features List ** 

    - bit board representation
        - how I understand: encoded as US_64 which makes it faster lookup for max depth searching

    - pre calculated attack tables
        - how I understand: store all positions that can be attacked so

    - magic bitboards for sliding pieces (maybe..)

    - encoding moves as integers (see screenshot on desktop)

    - copy/make approach for making moves

    - negamax search with alpha beta pruning

    - PV/Killer/History move ordering

    - iterative deepening 

    - Transposition tables

    - Material/Position/pawns/mobility/king safety eval function

    - UCI Protocol

    * possible ML training pipeline on eval function or move gen





MoveGeneration function

eval board function

isStalemateFunction

isCheckmateFunction

isInsufficientMaterial Function


BitBoard Representation of a chess board class 

class Board{
public:

private:

};