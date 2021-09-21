#include "blackjack.h"
#include <iostream>

int main()
{
	Deck deck;
	deck.shuffle();

	std::cout << "Let's play some Blackjack!\n\n";

	switch (playBlackjack(deck))
	{
	case BlackjackResult::PLAYER_WIN:	std::cout << "You win!\n";		break;
	case BlackjackResult::PLAYER_LOSE:	std::cout << "You lose!\n";		break;
	case BlackjackResult::TIE:			std::cout << "Tie!\n";			break;
	}

	return 0;
}