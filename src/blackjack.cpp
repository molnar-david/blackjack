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

		// Dealer has less than 17, has to draw
		if (dealer.score() < MINIMUM_DEALER_SCORE)
		{
			std::cout << "The dealer draws ";
			dealer.drawCard(deck).print();
			std::cout << ", and now has score: " << dealer.score() << '\n';
		}
		else
			break;							// Dealer has 17 or more, stops drawing
	}

	// Dealer didn't go bust
	std::cout << "The dealer stands!\n\n";
	return false;
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
	std::cout << ", and now have score: " << player.score() << "\n\n";

	// Player goes first
	if (playerTurn(player, deck))
	{
		// Player went bust, player loses
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