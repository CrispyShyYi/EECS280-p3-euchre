#include <iostream>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstring>
#include "Pack.hpp"
#include "Player.hpp"
#include "Card.hpp"

using namespace std;

class Game {
 public:
  Game(Pack pack_in, bool shuffle, int points,
    vector<Player*> &gamePlayer):
    do_shuffle(shuffle), pointsToWin(points){
        players = gamePlayer;

        pack = pack_in;
        t1Points = 0;
        t2Points = 0;
    };

  void play() {
    while (t1Points < pointsToWin && t2Points < pointsToWin){
        // which hand(s);
        cout << "Hand " << hand << endl;
        hand ++;

        Suit trump = SPADES;
        doShuffle();
        dealCard(players, upcard);
        // who is the dealer;
        cout << players[dealer % 4]->get_name() << " deals" << endl;
        // upcard;
        cout << upcard << " turned up" << endl;

        play_trick(trump, dealer);
        dealer++;
    }
    if (t1Points >= pointsToWin){
        cout << players[0]->get_name() << " and " <<
        players[2]->get_name() << " win!" << endl;
        return;
    }
    else {
        cout << players[1]->get_name() << " and " <<
        players[3]->get_name() << " win!" << endl;
        return;
    }
  }

 private:
  std::vector<Player*> players;
  Card upcard; // to make trump
  Pack pack;
  Suit trump;
  bool do_shuffle = false; // shuffle or not
  int pointsToWin; // how many rounds
  int dealer = 0; // player 1, 2, 3, or 4
  int t1Points; // team 1's points
  int t2Points; // team 2's points
  int hand = 0;
  
  
  void doShuffle(){
    if (do_shuffle == true){
        pack.shuffle();
    }
    else{
        pack.reset();
    }
  }
  
  void deal2Card(int player_index){
    players[player_index]->add_card(pack.deal_one());
    players[player_index]->add_card(pack.deal_one());
    return;
  }

  void deal3Card(int player_index){
    players[player_index]->add_card(pack.deal_one());
    players[player_index]->add_card(pack.deal_one());
    players[player_index]->add_card(pack.deal_one());
    return;
  }

  void dealCard(vector<Player*> players, Card &first){
    
    // first round;
    for (int i = 1; i <= 4; i++){
        if(i % 2 == 1){
            deal3Card((dealer + i) % 4);
        }
        else if (i % 2 == 0){
            deal2Card((dealer + i) % 4);
        }
    }

    // second round;
    for (int i = 1; i <= 4; i++){
        if (i % 2 == 1){
            deal2Card((dealer + i) % 4);
        }
        else if (i % 2 == 0){
            deal3Card((dealer + i) % 4);
        }
    }

    // upcard;
    first = pack.deal_one();
  };

  
   int makeTrump(int dealerIndex, const Card upcard, Suit &trump){
    
    // round 1;
    int round = 1;
    for(int i = 1; i <= 4; i++){
        int currPlayer = (dealerIndex + i) % 4;
        if (players[currPlayer]->make_trump(upcard, 
            dealerIndex % 4 == currPlayer, round, trump)){ 
                cout << players[currPlayer]->get_name() << " orders up " << trump 
                << endl;
                players[dealerIndex % 4]->add_and_discard(upcard);
                return currPlayer;
        }
        else{
            cout << players[currPlayer]->get_name() << 
                " passes" << endl;
        }
    }

    // round 2;
    round = 2;
    for (int i = 1; i <= 4; i++){
        int curr_player = (dealerIndex + i) % 4;
        if (players[curr_player]->make_trump(upcard,
            dealerIndex % 4 == curr_player, round, trump)){
                cout << players[curr_player]->get_name() << " orders up " << trump 
                    << "\n\n";
                return curr_player;
        }
        else{
            cout << players[curr_player]->get_name() <<
                " passes" << endl;
        }
    }
    return dealerIndex % 4;
  };

void print_message(int t1, int t2, int trumpTeam){
    if (t1 > t2){
        if (trumpTeam == 2){
            t1Points += 2;
            cout << players[0]->get_name() << " and " << players[2]->get_name() <<
                " win the hand" << endl;
            cout << "euchred!" << endl;
            cout << players[0]->get_name() << " and " << players[2]->get_name() <<
                " have " << t1Points << " points" << endl;
            cout << players[1]->get_name() << " and " << players[3]->get_name() <<
                " have " << t2Points << " points" << endl << endl;
        }
        else if(trumpTeam == 1){
            t1Points += 1;
            cout << players[0]->get_name() << " and " << players[2]->get_name() <<
                " win the hand" << endl;
            if (t1 == 5) {
                cout << "march!" << endl;
                t1Points++;
            }
            cout << players[0]->get_name() << " and " << players[2]->get_name() <<
                " have " << t1Points << " points" << endl;
            cout << players[1]->get_name() << " and " << players[3]->get_name() <<
                " have " << t2Points << " points" << endl << endl;
            
        }
    }
    else if (t2 > t1){
        if (trumpTeam == 1){
            t2Points += 2;
            cout << players[1]->get_name() << " and " << players[3]->get_name() <<
                " win the hand" << endl;
            cout << "euchred!" << endl;
            cout << players[0]->get_name() << " and " << players[2]->get_name() <<
                " have " << t1Points << " points" << endl;
            cout << players[1]->get_name() << " and " << players[3]->get_name() <<
                " have " << t2Points << " points" << endl << endl;
        }
        else if (trumpTeam == 2){
            t2Points ++;
            cout << players[1]->get_name() << " and " << players[3]->get_name() <<
                " win the hand" << endl;
            if (t2 == 5){
                cout << "march!" << endl;
                t2Points++;
            }
            cout << players[0]->get_name() << " and " << players[2]->get_name() <<
                " have " << t1Points << " points" << endl;
            cout << players[1]->get_name() << " and " << players[3]->get_name() <<
                " have " << t2Points << " points" << endl << endl;
        }
    }
    }

  int trick_winner(const Suit trump, int dealer){
     
    // play a trick

    // first player leads a card;
    Card card1 = players[dealer % 4]->lead_card(trump);
    cout << card1 << " led by " << players[dealer % 4]->get_name() << endl;
    // second player leads a card;
    Card card2 = players[(dealer + 1) % 4]->play_card(card1, trump);
    cout << card2 << " played by " << players[(dealer + 1) % 4]->get_name() << endl;
    // third player leads a card;
    Card card3 = players[(dealer + 2) % 4]->play_card(card1, trump);
    cout << card3 << " played by " << players[(dealer + 2) % 4]->get_name() << endl;
    // forth player leads a card;
    Card card4 = players[(dealer + 3) % 4]->play_card(card1, trump);
    cout << card4 << " played by " << players[(dealer + 3) % 4]->get_name() << endl;

    // find the winning card
    Card maxCard = card1;

    if (Card_less(maxCard, card2, card1, trump)){
        maxCard = card2;
    }
    if (Card_less(maxCard, card3, card1, trump)){
        maxCard = card3;
    }
    if (Card_less(maxCard, card4, card1, trump)){
        maxCard = card4;
    }

    // find the card owner;
    if (maxCard == card1) return dealer % 4;
    else if (maxCard == card2) return (dealer + 1) % 4;
    else if (maxCard == card3) return (dealer + 2) % 4;
    else if (maxCard == card4) return (dealer + 3) % 4;
    return -1;
  };

  void play_trick(Suit trump, int dealer){
    int trick_winner_player;
    int trick_winner_point1 = 0;
    int trick_winner_point2 = 0;
    int trump_team = 0;
    // make trump;
    int trump_maker = makeTrump(dealer, upcard, trump);
    // which is trump maker's team;
    if (trump_maker == 0 || trump_maker == 2){
        trump_team = 1;
    }
    else if (trump_maker == 1 || trump_maker == 3){
        trump_team = 2;
    }
    // for first round; first left player of dealer leads;
    trick_winner_player = trick_winner(trump, (dealer + 1) % 4);
    //cout << trick_winner_player << endl;
    cout << players[trick_winner_player]->get_name() << " takes the trick" << 
        endl << endl;
    if (trick_winner_player == 0 || trick_winner_player == 2){
        trick_winner_point1++;
    }
    else if(trick_winner_player == 1 || trick_winner_player == 3){
        trick_winner_point2++;
    }
    // for the next 4 rounds;
    for(int i = 1; i < 5; i++){
        trick_winner_player = trick_winner(trump, trick_winner_player);
        cout << players[trick_winner_player]->get_name() << " takes the trick" << 
            endl << endl;
        if (trick_winner_player == 0 || trick_winner_player == 2){
            trick_winner_point1++;
        }
        else if(trick_winner_player == 1 || trick_winner_player == 3){
            trick_winner_point2++;
        }
    }
    // find hand winners;

    print_message(trick_winner_point1, trick_winner_point2, trump_team);
  }
};

 

void warning() {
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
}


int main(int argc, char **argv) {
  // Read command line args and check for errors
  /*
  if (argc != 12){
    warning();
  }
  if (atoi(argv[3]) < 1 || atoi(argv[3]) > 100){
    warning();
  }
  if (strcmp(argv[2], "noshuffle") != 0 || strcmp(argv[2], "shuffle") != 0){
    warning();
  }
  if (strcmp(argv[5], "Simple") != 0 || strcmp(argv[5], "Human") != 0){
    warning();
  }
  if (strcmp(argv[7], "Simple") != 0 || strcmp(argv[7], "Human") != 0){
    warning();
  }
  if (strcmp(argv[9], "Simple") != 0 || strcmp(argv[9], "Human") != 0){
    warning();
  }
  if (strcmp(argv[11], "Simple") != 0 || strcmp(argv[11], "Human") != 0){
    warning();
  }
*/

  // check input file;
  string filename = argv[1];
  ifstream inf(argv[1]);
  if (!inf.is_open()){
    cout << "Error opening " << filename << endl;
  }
  Pack pack_in(inf);


  // read win points;
  int points_to_win = atoi(argv[3]);

  // check shuffle or not;
  string shuffle = argv[2];
    bool do_shuffle;
    if(shuffle == "shuffle"){
        do_shuffle = true;
    }
    else{
        do_shuffle = false;
    }
  
  // read players;  
  vector<Player*> gamePlayers;
    gamePlayers.push_back(Player_factory(argv[4], argv[5]));
    gamePlayers.push_back(Player_factory(argv[6], argv[7]));
    gamePlayers.push_back(Player_factory(argv[8], argv[9]));
    gamePlayers.push_back(Player_factory(argv[10], argv[11]));

    // give command;
    cout << "./euchre.exe " << filename << " " <<
    argv[2] << " " << points_to_win << " " << 
    gamePlayers[0]->get_name() << " " << argv[5] << " " << 
    gamePlayers[1]->get_name() << " " << argv[7] << " " << 
    gamePlayers[2]->get_name() << " " << argv[9] << " " << 
    gamePlayers[3]->get_name() << " " << argv[11] << " " << endl;

    // set up game;
    Game *game = new Game(pack_in, do_shuffle, points_to_win,
                        gamePlayers); 
    
    // play the game;    
    game->play();

    // delete dynamics;
    for (int i = 0; i < 4; i++) {
		delete gamePlayers[i];
	}
	
    delete game;
    return 0;
}