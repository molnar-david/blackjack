#include "blackjack.h"
#include <iostream>

bool playerWantsHit()
{
	while (true)
	{
		std::cout << "Type (h) to hit or (s) to stand: ";
		char ch{};
		std::cin >> ch;

		if (std::cin.fail())
			std::cin.clear();

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		switch (ch)
		{
		case 'h':
			return true;
		case 's':
			return false;
		default:
			// In case the player enters something unexpected
			break;
		}
	}
}

bool playerTurn(Player& player, Deck& deck)
{
	std::cout << "Your turn!\n";

	while (true)
	{
		if (player.isBust())
		{
			std::cout << "You went bust!\n";
			return true;
		}

		if (playerWantsHit())
		{
			std::cout << "You draw ";
			player.drawCard(deck).print();
			std::cout << ", and now have score: " << player.score() << "\n\n";
		}
		else
		{
			// Player didn't go bust
			std::cout << '\n';
			return false;
		}
	}
}

bool dealerTurn(Player& dealer, Deck& deck)
{
	std::cout << "Dealer's turn!\n";

	while (true)
	{
		// Dealer went bust
		if (dealer.isBust())
		{
			std::cout << "\nThe dealer went bust!\n";
			return true;
		}

		// Dealer has less than MINIMUM_DEALER_SCORE, has to draw
		if (dealer.score() < scores::MINIMUM_DEALER_SCORE)
		{
			std::cout << "The dealer draws ";
			dealer.drawCard(deck).print();
			std::cout << ", and now has score: " << dealer.score() << '\n';
		}
		else
			break;							// Dealer has MINIMUM_DEALER_SCORE or more, stops drawing
	}

	// Dealer didn't go bust
	std::cout << "The dealer stands!\n\n";
	return false;
}

bool dealerDrewBlackjack(Player& dealer, Deck& deck)
{
	// If dealer has < MINIMUM_BLACKJACK_SCORE, he can't have a blackjack
	if (dealer.score() < scores::MINIMUM_BLACKJACK_SCORE)
		return false;

	std::cout << "Dealer's turn!\n";
	std::cout << "The dealer draws ";
	dealer.drawCard(deck).print();
	std::cout << ", and now has score: " << dealer.score() << '\n';

	return dealer.score() == scores::MAXIMUM_SCORE;
}

BlackjackResult playBlackjack(Deck& deck)
{
	// Create the dealer, give them 1 card
	Player dealer;
	std::cout << "The dealer draws ";
	dealer.drawCard(deck).print();
	std::cout << ", and now has score: " << dealer.score() << "\n\n";

	// Create the player, give them 2 cards
	Player player;
	std::cout << "You draw ";
	player.drawCard(deck).print();
	std::cout << ", and now have score: " << player.score() << '\n';

	std::cout << "You draw ";
	player.drawCard(deck).print();
	std::cout << ", and now have score: " << player.score() << '\n';

	// If the player gets a blackjack, the dealer can tie with a blackjack, otherwise the player wins automatically
	if (player.score() == scores::MAXIMUM_SCORE)
	{
		std::cout << "Blackjack!\n\n";

		if (dealerDrewBlackjack(dealer, deck))
		{
			std::cout << "Blackjack!\n\n";

			return BlackjackResult::TIE;
		}
		else
		{
			// formatting
			if(dealer.score() >= scores::MINIMUM_BLACKJACK_SCORE)
				std::cout << '\n';

			return BlackjackResult::PLAYER_WIN;
		}
	}

	// formatting
	std::cout << '\n';

	// Player goes first
	if (playerTurn(player, deck))
	{
		// Player went bust, player loses
		return BlackjackResult::PLAYER_LOSE;
	}

	// If dealer gets a blackjack when the player doesn't, the player loses automatically
	if (dealer.score() + deck.nextCard().value() == scores::MAXIMUM_SCORE)
	{
		std::cout << "The dealer draws ";
		dealer.drawCard(deck).print();
		std::cout << ", and now has score: " << dealer.score() << '\n';
		std::cout << "Blackjack!\n\n";

		return BlackjackResult::PLAYER_LOSE;
	}

	// Dealer goes after the player
	if (dealerTurn(dealer, deck))
	{
		// Dealer went bust, player wins
		return BlackjackResult::PLAYER_WIN;
	}

	if (player.score() > dealer.score())
		return BlackjackResult::PLAYER_WIN;		// Player wins
	else if (player.score() < dealer.score())
		return BlackjackResult::PLAYER_LOSE;	// Player loses
	else
		return BlackjackResult::TIE;			// Tie
}