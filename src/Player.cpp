#include "Player.h"
#include <iostream>

const Card& Player::drawCard(Deck& deck)
{
	Card card = deck.dealCard();

	int value{ card.value() };
	m_score += value;

	// We draw an ace
	if (value == 11)
		++m_aceCount;

	return card;
}

void Player::changeAceValue()
{
	m_score -= 10;
	--m_aceCount;
}

bool Player::isBust()
{
	// Player is over MAXIMUM_SCORE, but has aces
	while (m_score > scores::MAXIMUM_SCORE && m_aceCount > 0)
	{
		changeAceValue();
		std::cout << "The value of an ace was changed from 11 to 1!\n";
		std::cout << "New score: " << score() << "\n\n";
	}

	// Player goes bust
	if (m_score > scores::MAXIMUM_SCORE)
		return true;

	// Player doesn't go bust
	return false;
}