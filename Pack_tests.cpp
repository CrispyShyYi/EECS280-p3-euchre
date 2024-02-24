#include "Pack.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_pack_default_ctor) {
    Pack pack;
    Card first = pack.deal_one();
    ASSERT_EQUAL(NINE, first.get_rank());
    ASSERT_EQUAL(SPADES, first.get_suit());
}

TEST(test_shuffle){
    Pack pack;
    pack.shuffle();
    pack.deal_one();
    Card second_card = pack.deal_one();
    ASSERT_EQUAL(second_card, Card(JACK, HEARTS));
}

TEST_MAIN()
