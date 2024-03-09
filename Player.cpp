#include "Player.hpp"
#include <vector>
#include <iostream>
#include <cassert>
#include <algorithm>

using namespace std;

class SimplePlayer : public Player{

private:
  string name;
  std::vector<Card> playCard;

public:
  SimplePlayer(string name_in):
  name(name_in){  }
 
  const std::string & get_name() const override {
    return name;
  }

  void add_card(const Card &c) override {
    assert(playCard.size() < MAX_HAND_SIZE);
    playCard.push_back(c);
  }

  bool make_trump(const Card &upcard, bool is_dealer,
                          int round, Suit &order_up_suit) const override{
    assert(round == 1 || round == 2);
    if (round == 1){
      Suit potenTrump = upcard.get_suit();
      int trumpFace = 0;
      for (int i = 0; i < MAX_HAND_SIZE; i++){
        if (playCard[i].is_trump(potenTrump) && playCard[i].is_face_or_ace()){
          trumpFace++;
        }
      }      
      if (trumpFace >= 2){
          order_up_suit = potenTrump;
          return true;
        }
    }
    else if (round == 2){
      Suit potenTrump = Suit_next(upcard.get_suit());
      for (int i = 0; i < MAX_HAND_SIZE; i++){
        if (playCard[i].is_trump(potenTrump) && playCard[i].is_face_or_ace()){
          order_up_suit = potenTrump;
          return true;
        }
      }
      if (is_dealer){
        order_up_suit = potenTrump;
        return true;
      }
    }
    return false;
  }
  

  void add_and_discard(const Card &upcard) override {
    assert(playCard.size() >= 1);
    Card lowestCard = playCard[0];
    int index = 0;
    for (int i = 1; i < playCard.size(); i++){
      if (Card_less(playCard[i], lowestCard, upcard.get_suit())){
        lowestCard = playCard[i];
        index = i;
      }
    }
    cout << endl;
    if (Card_less(playCard[index], upcard, upcard.get_suit())){
      playCard[index] = upcard;
      return;
    }
  }


  Card lead_card(Suit trump) override{
    assert(playCard.size() >= 1);
    int numOfTrump = 0;
    int indexOfNonTrump = 0;
    int indexOfTrump = 0;
    Card highestNonTrump = Card(EIGHT, Suit_next(trump));
    Card highestTrump = Card(EIGHT, trump);

    for (int i = 0; i < playCard.size(); i++){
      if (!playCard[i].is_trump(trump)){
        if (Card_less(highestNonTrump, playCard[i], trump)){
          highestNonTrump = playCard[i];
          indexOfNonTrump = i;
        }
      }
      else if(playCard[i].is_trump(trump)){
        numOfTrump++;
        if (Card_less(highestTrump, playCard[i], trump)){
          highestTrump = playCard[i];
          indexOfTrump = i;
        }
      }
    }
    if (numOfTrump == playCard.size()){
      playCard.erase(playCard.begin() + indexOfTrump);
      return highestTrump;
    }
    else {
      playCard.erase(playCard.begin() + indexOfNonTrump);
      return highestNonTrump;
    }
  }


  Card play_card(const Card &led_card, Suit trump) override{
    assert(playCard.size() >= 1);
    Suit ledSuit = led_card.get_suit(trump);
    int numOfSuit = 0;
    Card maxCard = Card(EIGHT, ledSuit);
    Card minCard;
    int index = 0;

    for (int i = 0; i < playCard.size(); i++){
      if (playCard[i].get_suit(trump) == ledSuit){
        numOfSuit++;
      }
    }
    if (numOfSuit > 0){
      for (int j = 0; j < playCard.size(); j++){
        if (Card_less(maxCard, playCard[j], led_card, trump) && 
        playCard[j].get_suit(trump) == ledSuit){
          maxCard = playCard[j];
          index = j;
        }
      }
      playCard.erase(playCard.begin() + index);
      return maxCard;
    }
    else {
      minCard = playCard[0];
      for (int k = 1; k < playCard.size(); k++){
        if (Card_less(playCard[k], minCard, led_card, trump)){
          minCard = playCard[k];
          index = k;
        }
      }
      playCard.erase(playCard.begin() + index);
      return minCard;
    }
  }

  ~SimplePlayer() override{ };
};

class HumanPlayer : public Player{
  private:
  std::string name;
  vector<Card> hand;

  void print_hand() const {
  for (size_t i=0; i < hand.size(); ++i)
    cout << "Human player " << name << "'s hand: "
         << "[" << i << "] " << hand[i] << "\n";
  }

  void sort_hand() {
    sort(hand.begin(), hand.end());
  }

  public:
  HumanPlayer(string name_in):
  name(name_in) { }

  const std::string & get_name() const override {
    return name;
  }

  void add_card(const Card &c) override {
		assert(hand.size() < MAX_HAND_SIZE);
		hand.push_back(c);
		sort_hand();
	}
  
  bool make_trump(const Card &upcard, bool is_dealer,
                          int round, Suit &order_up_suit) const override{
    print_hand();
    cout << "Human player " << name << ", please enter a suit, or \"pass\":\n";
    string decision;
    cin >> decision;

    if (decision != "pass") {
      order_up_suit = string_to_suit(decision);
      return true;
    }
    else {
      return false;
    }
  }

  void add_and_discard(const Card &upcard) override{
    assert(hand.size() > 0);
    print_hand();
    cout << "Discard upcard: [-1]\n";
    cout << "Human player " << name << 
            ", please select a card to discard:\n\n";
    int index;
    cin >> index;
    if (index == -1) {
      return;
    }
    else {
      hand.push_back(Card(upcard));
      hand.erase(hand.begin() + index);
      sort_hand();
    }
  }

  Card lead_card(Suit trump) override{
    print_hand();
    cout << "Human player " << name << ", please select a card:\n";
    int index;
    Card leadCard;
    cin >> index;
    leadCard = hand[index];
    hand.erase(hand.begin() + index);
    return leadCard;
  }

  Card play_card(const Card &led_card, Suit trump) override{
    print_hand();
    cout << "Human player " << name << ", please select a card:\n";
    int index;
    cin >> index;
    Card playCard = hand[index];
    hand.erase(hand.begin() + index);
    return playCard;
  }

  ~HumanPlayer() override{};
};

std::ostream & operator<<(std::ostream &os, const Player &p) {
  os << p.get_name(); 
  return os;
}

Player * Player_factory(const std::string &name, 
                        const std::string &strategy) {
  // We need to check the value of strategy and return 
  // the corresponding player type.
  if (strategy == "Simple") {
    // The "new" keyword dynamically allocates an object.
    return new SimplePlayer(name);
  }
  // Repeat for each other type of Player
  if (strategy == "Human"){
    return new HumanPlayer(name);
  }
  // Invalid strategy if we get here
  assert(false);
  return nullptr;
}