#include "Deck.h"
#include <cassert>
#include <iostream>
#include <random>

Deck::Deck()
{
	int maxSuit{ static_cast<int>(Card::Suit::MAX_SUITS) };
	int maxRank{ static_cast<int>(Card::Rank::MAX_RANKS) };

	index_type card{ 0 };
	for (int suit{ 0 }; suit < maxSuit; ++suit)
	{
		for (int rank{ 0 }; rank < maxRank; ++rank)
		{
			m_deck[card] = { static_cast<Card::Rank>(rank), static_cast<Card::Suit>(suit) };
			++card;
		}
	}
}

void Deck::print() const
{
	for (const auto& card : m_deck)
	{
		card.print();
		std::cout << ' ';
	}

	std::cout << '\n';
}

void Deck::shuffle()
{
	static std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };

	std::shuffle(m_deck.begin(), m_deck.end(), mt);

	m_cardIndex = 0;
}

const Card& Deck::dealCard()
{
	assert(m_cardIndex < m_deck.size() && "out of cards");

	return m_deck[m_cardIndex++];
}