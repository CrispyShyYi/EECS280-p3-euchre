#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

// Add more test cases
TEST(test_Card_suit_trump){
    Card J_C(JACK, SPADES);
    ASSERT_EQUAL(CLUBS, J_C.get_suit(CLUBS));
    ASSERT_EQUAL(SPADES, J_C.get_suit(HEARTS));
}

TEST(test_Card_is_face_or_ace){
    Card j(JACK, CLUBS);
    ASSERT_TRUE(j.is_face_or_ace());

    Card q(QUEEN, DIAMONDS);
    ASSERT_TRUE(q.is_face_or_ace());

    Card k(KING, HEARTS);
    ASSERT_TRUE(k.is_face_or_ace());

    Card a(ACE, SPADES);
    ASSERT_TRUE(a.is_face_or_ace());

    Card n(NINE, SPADES);
    ASSERT_FALSE(n.is_face_or_ace());
}

TEST(test_Card_is_right_bower){
    Card jack_of_trump(JACK, SPADES);
    ASSERT_TRUE(jack_of_trump.is_right_bower(SPADES));

    Card jack_not_trump(JACK, CLUBS);
    ASSERT_FALSE(jack_not_trump.is_right_bower(SPADES));

    Card not_jack_of_trump(QUEEN, SPADES);
    ASSERT_FALSE(not_jack_of_trump.is_right_bower(SPADES));

    Card not_jack_not_trump(QUEEN, CLUBS);
    ASSERT_FALSE(not_jack_not_trump.is_right_bower(SPADES));
}

TEST(test_Card_is_left_bower){
    Card jack_of_hearts(JACK, HEARTS);
    ASSERT_TRUE(jack_of_hearts.is_left_bower(DIAMONDS));

    Card jack_of_diamonds(JACK, DIAMONDS);
    ASSERT_TRUE(jack_of_diamonds.is_left_bower(HEARTS));

    Card jack_of_clubs(JACK, CLUBS);
    ASSERT_TRUE(jack_of_clubs.is_left_bower(SPADES));

    Card jack_of_spades(JACK, SPADES);
    ASSERT_TRUE(jack_of_spades.is_left_bower(CLUBS));

    Card not_left_bower_jack(JACK, HEARTS);
    ASSERT_FALSE(not_left_bower_jack.is_left_bower(HEARTS));

    Card not_jack_of_trump(QUEEN, SPADES);
    ASSERT_FALSE(not_jack_of_trump.is_left_bower(SPADES));
}

TEST(test_Card_is_trump){
    Card trump_card(KING, DIAMONDS);
    ASSERT_TRUE(trump_card.is_trump(DIAMONDS));

    Card left_bower_jack(JACK, HEARTS);
    ASSERT_TRUE(left_bower_jack.is_trump(DIAMONDS));

    Card non_trump_card(QUEEN, CLUBS);
    ASSERT_FALSE(non_trump_card.is_trump(DIAMONDS));

    Card right_bower_jack(JACK, DIAMONDS);
    ASSERT_TRUE(right_bower_jack.is_trump(DIAMONDS));

    Card not_left_bower_here(JACK, SPADES);
    ASSERT_FALSE(not_left_bower_here.is_trump(DIAMONDS));
}

TEST(test_Card_stream_operator){

}

TEST(test_Card_less_operator){
    Card lower_card(NINE, CLUBS);
    Card higher_card(JACK, CLUBS);

    ASSERT_TRUE(lower_card < higher_card);

    Card same_rank_lower_suit(TEN, DIAMONDS);
    Card same_rank_higher_suit(TEN, HEARTS);

    ASSERT_FALSE(same_rank_lower_suit < same_rank_higher_suit);

    Card equal_card1(QUEEN, SPADES);
    Card equal_card2(QUEEN, SPADES);

    ASSERT_FALSE(equal_card1 < equal_card2);
    ASSERT_FALSE(equal_card2 < equal_card1);

    Card king_card(KING, DIAMONDS);
    Card ace_card(ACE, DIAMONDS);

    ASSERT_TRUE(king_card < ace_card);
}

TEST(test_Card_less_or_equal_operator){
    Suit trump = CLUBS;

    Card lower_card(NINE, CLUBS);
    Card higher_card(JACK, CLUBS);
    ASSERT_TRUE(Card_less(lower_card, higher_card, trump) || lower_card == higher_card);

    Card equal_card1(QUEEN, SPADES);
    Card equal_card2(QUEEN, SPADES);
    ASSERT_TRUE(Card_less(equal_card1, equal_card2, trump) || equal_card1 == equal_card2);
    ASSERT_TRUE(Card_less(equal_card2, equal_card1, trump) || equal_card2 == equal_card1);

    Card king_card(KING, DIAMONDS);
    Card ace_card(ACE, DIAMONDS);
    ASSERT_TRUE(Card_less(king_card, ace_card, trump) || king_card == ace_card);
    ASSERT_FALSE(Card_less(ace_card, king_card, trump) || ace_card == king_card);
}

TEST(test_Card_greater_operator){
    Card card1(KING, CLUBS);
    Card card2(QUEEN, DIAMONDS);
    ASSERT_TRUE(card1 > card2);
    ASSERT_FALSE(card2 > card1);
}

TEST(test_Card_greater_or_equal_operator){
    Suit trump = SPADES;

    Card higher_card(ACE, SPADES);
    Card lower_card(KING, SPADES);
    ASSERT_TRUE(!Card_less(higher_card, lower_card, trump) || higher_card == lower_card);
    ASSERT_FALSE(!Card_less(lower_card, higher_card, trump) || lower_card == higher_card);
}

TEST(test_Card_equal_operator){
    Card card1(NINE, HEARTS);
    Card same_rank_different_suit(NINE, DIAMONDS);
    ASSERT_TRUE(card1.get_rank() == same_rank_different_suit.get_rank()); 

    Card different_rank_card(TEN, HEARTS);
    ASSERT_FALSE(card1.get_rank() == different_rank_card.get_rank());

    Card identical_card(NINE, HEARTS);
    ASSERT_TRUE(card1.get_rank() == identical_card.get_rank());
}

TEST(test_Card_not_equal_operator){
    Card card1(NINE, HEARTS);
    Card different_rank_card(TEN, HEARTS);
    ASSERT_TRUE(card1.get_rank() != different_rank_card.get_rank());

    Card same_rank_different_suit(NINE, DIAMONDS);
    ASSERT_FALSE(card1.get_rank() != same_rank_different_suit.get_rank());

    Card identical_card(NINE, HEARTS);
    ASSERT_FALSE(card1.get_rank() != identical_card.get_rank());
}


TEST(test_Suit_next){
    ASSERT_EQUAL(HEARTS, Suit_next(DIAMONDS));
    ASSERT_EQUAL(DIAMONDS, Suit_next(HEARTS));
    ASSERT_EQUAL(SPADES, Suit_next(CLUBS));
    ASSERT_EQUAL(CLUBS, Suit_next(SPADES));
}

TEST(test_Card_less_function){
    Card a(JACK, CLUBS);
    Card b(KING, SPADES);
    ASSERT_FALSE(Card_less(a, b, SPADES));

    Card c(QUEEN, DIAMONDS);
    Card d(ACE, DIAMONDS);
    ASSERT_TRUE(Card_less(c, d, CLUBS));

    Card e(JACK, SPADES);
    Card f(JACK, CLUBS);
    ASSERT_FALSE(Card_less(e, f, SPADES));

    Card g(TEN, HEARTS);
    Card h(TEN, DIAMONDS);
    ASSERT_FALSE(Card_less(g, h, HEARTS));

    Card i(NINE, CLUBS);
    Card j(TEN, CLUBS);
    ASSERT_TRUE(Card_less(i, j, DIAMONDS));

    Card x(KING, CLUBS);
    Card y(JACK, DIAMONDS);
    ASSERT_TRUE(Card_less(x, y, DIAMONDS))

    Card x1(KING, CLUBS);
    Card y1(JACK, HEARTS);
    ASSERT_TRUE(Card_less(x1, y1, DIAMONDS));

    Card x2(KING, CLUBS);
    Card y2(NINE, DIAMONDS);
    ASSERT_TRUE(Card_less(x2, y2, DIAMONDS));
}

TEST(test_Card_less_with_led){
    Suit trump = SPADES;
    Card led_card(TEN, HEARTS);

    Card right_bower(JACK, SPADES);
    Card left_bower(JACK, CLUBS);
    Card trump_card(NINE, SPADES);
    Card led_suit_card(KING, HEARTS);
    Card off_suit_card(QUEEN, DIAMONDS);

    ASSERT_FALSE(Card_less(right_bower, off_suit_card, led_card, trump));
    ASSERT_TRUE(Card_less(off_suit_card, right_bower, led_card, trump));

    ASSERT_FALSE(Card_less(left_bower, off_suit_card, led_card, trump));
    ASSERT_TRUE(Card_less(off_suit_card, left_bower, led_card, trump));

    ASSERT_FALSE(Card_less(trump_card, off_suit_card, led_card, trump));
    ASSERT_TRUE(Card_less(off_suit_card, trump_card, led_card, trump));

    ASSERT_FALSE(Card_less(led_suit_card, off_suit_card, led_card, trump));
    ASSERT_TRUE(Card_less(off_suit_card, led_suit_card, led_card, trump));

    ASSERT_TRUE(Card_less(off_suit_card, led_suit_card, led_card, trump));
    ASSERT_FALSE(Card_less(led_suit_card, off_suit_card, led_card, trump));


    Suit Trump = HEARTS;
    Card card1(JACK, HEARTS);
    Card card2(TEN, SPADES);
    Card card3(JACK, DIAMONDS);
    Card card4(ACE, SPADES);
    Card card5(ACE, HEARTS);
    Card card6(ACE, DIAMONDS);
    Card card7(NINE, HEARTS);

    Card ledcard = card4;

    ASSERT_EQUAL(true, Card_less(card4, card1, ledcard, Trump));
    ASSERT_EQUAL(true, Card_less(card4, card3, ledcard, Trump));
    ASSERT_EQUAL(true, Card_less(card4, card7, ledcard, Trump));
    ASSERT_EQUAL(true, Card_less(card6, card4, ledcard, Trump));
    ASSERT_EQUAL(true, Card_less(card6, card2, ledcard, Trump));
}

TEST_MAIN()