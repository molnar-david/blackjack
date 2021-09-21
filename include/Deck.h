#pragma once

#include "Card.h"
#include <array>

class Deck
{
public:
	using array_type = std::array<Card, 52>;
	using index_type = array_type::size_type;

private:
	array_type m_deck;
	index_type m_cardIndex{ 0 };				// Holds the index of the next card to be dealt

public:
	Deck();

	void print() const;
	void shuffle();
	const Card& dealCard();
};