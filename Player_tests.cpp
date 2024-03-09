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

  Player * alf = Player_factory("Alf", "Simple");
  Card up_card(ACE, HEARTS);
  trump = HEARTS;
  Card c1(JACK, HEARTS);
  Card c2(JACK, DIAMONDS);
  Card c3(TEN, SPADES);
  Card c4(NINE, DIAMONDS);
  Card c5(JACK, CLUBS);

  alf->add_card(c1);
  alf->add_card(c2);
  alf->add_card(c3);
  alf->add_card(c4);
  alf->add_card(c5);  

  ASSERT_TRUE(alf->make_trump(up_card, true, 1, trump)); 
  
  trump = CLUBS;
  up_card = Card(NINE, CLUBS);
  ASSERT_FALSE(alf->make_trump(up_card, true, 1, trump));
  ASSERT_TRUE(alf->make_trump(up_card, true, 2, trump));
  
  delete alf;

  // if the player is the dealer;
  Player * jason = Player_factory("Jason", "Simple");
  c1 = Card(TEN, HEARTS);
  c2 = Card(NINE, DIAMONDS);
  c3 = Card(TEN, SPADES);
  c4 = Card(NINE, DIAMONDS);
  c5 = Card(TEN, CLUBS);

  jason->add_card(c1);
  jason->add_card(c2);
  jason->add_card(c3);
  jason->add_card(c4);
  jason->add_card(c5);

  up_card = Card(ACE, HEARTS);
  trump = HEARTS;

  ASSERT_FALSE(jason->make_trump(up_card, true, 1, trump));
  ASSERT_TRUE(jason->make_trump(up_card, true, 2, trump));

  delete jason;

  // if the player is not the dealer;
  Player * jack = Player_factory("Jack", "Simple");
  c1 = Card(TEN, HEARTS);
  c2 = Card(NINE, DIAMONDS);
  c3 = Card(TEN, SPADES);
  c4 = Card(NINE, DIAMONDS);
  c5 = Card(TEN, CLUBS);

  jack->add_card(c1);
  jack->add_card(c2);
  jack->add_card(c3);
  jack->add_card(c4);
  jack->add_card(c5);

  up_card = Card(ACE, HEARTS);
  trump = HEARTS;

  ASSERT_FALSE(jack->make_trump(up_card, false, 1, trump));
  ASSERT_FALSE(jack->make_trump(up_card, false, 2, trump));
  ASSERT_TRUE(jack->make_trump(up_card, true, 2, trump));

  delete jack;

  Player * ann = Player_factory("Ann", "Simple");
  c1 = Card(JACK, DIAMONDS);
  c2 = Card(NINE, DIAMONDS);
  c3 = Card(TEN, SPADES);
  c4 = Card(NINE, DIAMONDS);
  c5 = Card(TEN, CLUBS);

  ann->add_card(c1);
  ann->add_card(c2);
  ann->add_card(c3);
  ann->add_card(c4);
  ann->add_card(c5);

  up_card = Card(JACK, HEARTS);
  ASSERT_FALSE(ann->make_trump(up_card, true, 1, trump));
  ASSERT_TRUE(ann->make_trump(up_card, true, 2, trump));
  ASSERT_TRUE(ann->make_trump(up_card, false, 2, trump));

  delete ann;

  Player * fiona = Player_factory("Bow", "Simple");
  fiona->add_card(Card(NINE, SPADES));
  fiona->add_card(Card(TEN, SPADES));
  fiona->add_card(Card(QUEEN, SPADES));
  fiona->add_card(Card(JACK, DIAMONDS));
  fiona->add_card(Card(JACK, HEARTS));

Player * sam = Player_factory("Bow2", "Simple");
  sam->add_card(Card(NINE, SPADES));
  sam->add_card(Card(TEN, SPADES));
  sam->add_card(Card(QUEEN, SPADES));
  sam->add_card(Card(ACE, CLUBS));
  sam->add_card(Card(JACK, DIAMONDS));

Card upcard(ACE, HEARTS);
Suit trump1;

ASSERT_TRUE(fiona->make_trump(upcard, true, 1, trump1));
ASSERT_EQUAL(trump1, HEARTS);

Suit trump2;

ASSERT_FALSE(sam->make_trump(upcard, false, 1, trump2));

ASSERT_TRUE(sam->make_trump(upcard, false, 2, trump2));
ASSERT_EQUAL(trump2, DIAMONDS);

delete fiona;
delete sam;
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
  
  // the upcard is less than all 5 cards on hand;
  Player * alf = Player_factory("Alf", "Simple");

  Card c1(JACK, HEARTS);
  Card c2(JACK, DIAMONDS);
  Card c3(QUEEN, HEARTS);
  Card c4(KING, HEARTS);
  Card c5(ACE, HEARTS);

  Card up_card (NINE, HEARTS);

  alf->add_card(c1);
  alf->add_card(c2);
  alf->add_card(c3);
  alf->add_card(c4);
  alf->add_card(c5);  
  alf->add_and_discard(up_card);
  for(int i = 0; i < 5; i++){
    ASSERT_FALSE(alf->lead_card(HEARTS) == up_card);
  }
  delete alf;
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

  // have the left bower;
  Player * alf = Player_factory("Alf", "Simple");
  alf->add_card(Card(JACK, CLUBS));
  alf->add_card(Card(TEN, DIAMONDS));
  ASSERT_TRUE(alf->lead_card(SPADES) == Card(TEN, DIAMONDS));
  // all trumps;
  alf->add_card(Card(JACK, SPADES));
  ASSERT_TRUE(alf->lead_card(SPADES) == Card(JACK, SPADES));
  
  delete alf;
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
