#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

// Add more tests here

TEST(test_player_insertion) {
  Player *alice = Player_factory("Alice", "Human");

  ostringstream oss1;
  oss1 << *alice;

  ASSERT_EQUAL(oss1.str(), "Alice");

  Player *bob = Player_factory("Bob", "Simple");

  ostringstream oss2;
  oss2 << *bob;
  ASSERT_EQUAL(oss2.str(), "Bob");

  delete alice;
  delete bob;
}

TEST(test_player_add_card){
    Player * albert = Player_factory("Albert", "Simple");
    const Card card1 = Card(QUEEN, SPADES);
    const Card card2 = Card(KING, HEARTS);
    albert->add_card(card1);
    albert->add_card(card2);

    delete albert;
}

TEST(test_player_make_trump) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, CLUBS));
  bob->add_card(Card(TEN, CLUBS));
  bob->add_card(Card(QUEEN, HEARTS));
  bob->add_card(Card(KING, DIAMONDS));
  bob->add_card(Card(ACE, DIAMONDS));

  Card nine_hearts(NINE, HEARTS);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_hearts,    
    true,           
    1,              
    trump           
  );

  ASSERT_FALSE(orderup);
  delete bob;
}

TEST(test_player_add_and_discard){
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  
  bob->add_and_discard(
    Card(NINE, HEARTS) 
  );

  Card card_led = bob->lead_card(HEARTS);

  Card ace_spades(ACE, SPADES);
  ASSERT_EQUAL(card_led, ace_spades); 

  delete bob;
} 

TEST(test_lead_card) {
  Player * bob = Player_factory("Bob", "Simple");

  bob->add_card(Card(JACK, CLUBS));
  bob->add_card(Card(JACK, SPADES));

  Card card_played = bob->lead_card(CLUBS);
  ASSERT_EQUAL(card_played, Card(JACK, CLUBS));

  card_played = bob->lead_card(SPADES);
  ASSERT_EQUAL(card_played, Card(JACK, SPADES));

  bob->add_card(Card(KING, SPADES));
  card_played = bob->lead_card(DIAMONDS);
  ASSERT_EQUAL(card_played, Card(KING, SPADES));

  delete bob;
}

TEST(test_player_play_card){
    Player *Alice = Player_factory("Alice", "Simple");

    const Card card1 = Card(ACE, HEARTS);
    const Card card2 = Card(JACK, DIAMONDS);
    const Card card3 = Card(NINE, DIAMONDS);
    const Card card4 = Card(JACK, CLUBS);
    const Card card5 = Card(JACK, SPADES);

    Alice->add_card(card1);
    Alice->add_card(card2);
    Alice->add_card(card3);
    Alice->add_card(card4);
    Alice->add_card(card5);

    const Card upcard1 = Card(TEN, DIAMONDS);
    ASSERT_EQUAL(card2, Alice->play_card(upcard1, SPADES));

    const Card upcard2 = Card(NINE, SPADES);
    ASSERT_EQUAL(card5, Alice->play_card(upcard2, SPADES));

    const Card upcard3 = Card(QUEEN, SPADES);
    ASSERT_EQUAL(card4, Alice-> play_card(upcard3, SPADES));

    const Card upcard4 = Card(QUEEN, HEARTS);
    ASSERT_EQUAL(card1, Alice->play_card(upcard4, DIAMONDS));

    delete Alice;
}

TEST_MAIN()
