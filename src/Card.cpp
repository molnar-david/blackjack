#include "Card.h"
#include <cassert>
#include <iostream>

Card::Card(Rank rank, Suit suit) : m_rank{ rank }, m_suit{ suit }
{
}

int Card::value() const
{
	if (m_rank <= Rank::RANK_10)
	{
		return (static_cast<int>(m_rank) + 2);
	}

	switch (m_rank)
	{
	case Rank::RANK_JACK:
	case Rank::RANK_QUEEN:
	case Rank::RANK_KING:
		return 10;
	case Rank::RANK_ACE:
		return 11;

	default:
		assert(false && "should never happen");
		return 0;
	}
}

void Card::print() const
{
	switch (m_rank)
	{
	case Rank::RANK_2:			std::cout << '2';	break;
	case Rank::RANK_3:			std::cout << '3';	break;
	case Rank::RANK_4:			std::cout << '4';	break;
	case Rank::RANK_5:			std::cout << '5';	break;
	case Rank::RANK_6:			std::cout << '6';	break;
	case Rank::RANK_7:			std::cout << '7';	break;
	case Rank::RANK_8:			std::cout << '8';	break;
	case Rank::RANK_9:			std::cout << '9';	break;
	case Rank::RANK_10:			std::cout << 'T';	break;
	case Rank::RANK_JACK:		std::cout << 'J';	break;
	case Rank::RANK_QUEEN:		std::cout << 'Q';	break;
	case Rank::RANK_KING:		std::cout << 'K';	break;
	case Rank::RANK_ACE:		std::cout << 'A';	break;

	default:						std::cout << '?';	break;
	}

	switch (m_suit)
	{
	case Suit::SUIT_CLUB:		std::cout << 'C';	break;
	case Suit::SUIT_DIAMOND:	std::cout << 'D';	break;
	case Suit::SUIT_HEART:		std::cout << 'H';	break;
	case Suit::SUIT_SPADE:		std::cout << 'S';	break;

	default:						std::cout << '?';	break;
	}
}