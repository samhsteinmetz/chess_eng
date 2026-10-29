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




*** FUTURE IDEAS

    - deploy on the web and have a continous chess game going that updates the training of the eval function
    - let people watch the chess game go on on the web. 
    - dowload all my chess .com games somehow and make a bot based on me
    - download friends bot and make a bot based on my friend

    **very bold ideas
        - do a crowdsoureced chess game, where users of the platform vote on the next move vs. a bot 
        - people have to login and prove theyre human and maybe their vote counts more based on what rating they are and maybe we could get that from chess.com?
        - chat function for that, no spam though
        - people get a limited amount of votes so no spam
        - votes refresh every day.
        - the pro bot gets a certain amount of baseline votes
        - this could turn into some sort of distributed systems project








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