#include "Pack.hpp"
#include "Card.hpp"
#include <array>
#include <sstream>
#include <iostream>
#include <array>
#include <cassert>
#include <vector>

using namespace std;

Pack::Pack(){
  Card temp;
  reset();
  int num = 0;
  for (int s = SPADES; s <= DIAMONDS; s++){
    Suit tempSuit = static_cast<Suit>(s);
    for (int r = NINE; r <= ACE; r++){
      Rank tempRank = static_cast<Rank>(r);
      cards[num] = Card(tempRank, tempSuit);
      num++;
    }
  }
}

Pack::Pack(std::istream& pack_input){
  reset();
  for(int num = 0; num < PACK_SIZE; num++){
    pack_input >> cards[num];
  }
}

Card Pack::deal_one(){
  next++;
  return cards[next - 1];
}

void Pack::reset() {
  next = 0;
  return;
}

void Pack::shuffle(){
  next = 0;
  std::array<Card, PACK_SIZE> temp;
  int num = 0;
  for (size_t i = 0; i < 7; i++){
    num = 0;
    for (size_t k = 1; k < PACK_SIZE; k += 2){
      temp[k] = cards[num];
      num++;
    }
    for (size_t j = 0; j < PACK_SIZE - 1; j += 2){
      temp[j] = cards[num];
      num++;
    }

    for(size_t i = 0; i < PACK_SIZE; i++){
      cards[i] = temp[i];
    }
  }
}

bool Pack::empty() const{
  return (next == PACK_SIZE);
}