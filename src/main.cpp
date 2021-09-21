#include <algorithm>
#include <array>
#include <ctime>
#include <iostream>
#include <limits>
#include <random>
#include <string>

enum class CardRank
{
	rank_2,
	rank_3,
	rank_4,
	rank_5,
	rank_6,
	rank_7,
	rank_8,
	rank_9,
	rank_10,
	rank_jack,
	rank_queen,
	rank_king,
	rank_ace,

	max_ranks
};

enum class CardSuit
{
	suit_club,
	suit_diamond,
	suit_heart,
	suit_spade,

	max_suits
};

enum class BlackjackResult
{
	player_win,
	player_lose,
	tie
};

struct Card
{
	CardRank rank{};
	CardSuit suit{};
};

struct Player
{
	int score{ 0 };
	int aceCount{ 0 };			// To keep track of aces dealt, and modify it's score to 1 if necessary
};

// Maximum score before losing
constexpr int maximumScore{ 21 };

// Minimum dealer score
constexpr int minimumDealerScore{ 17 };

using deck_type = std::array<Card, 52>;
using index_type = deck_type::size_type;

deck_type createDeck()
{
	deck_type deck{};
	index_type card{ 0 };

	int maxSuit{ static_cast<int>(CardSuit::max_suits) };
	int maxRank{ static_cast<int>(CardRank::max_ranks) };

	for (int suit{ 0 }; suit < maxSuit; ++suit)
	{
		for (int rank{ 0 }; rank < maxRank; ++rank)
		{
			deck[card].rank = static_cast<CardRank>(rank);
			deck[card].suit = static_cast<CardSuit>(suit);
			++card;
		}
	}

	return deck;
}

std::string getCardName(const Card& card)
{
	std::string cardName{};

	switch (card.rank)
	{
	case CardRank::rank_2:			cardName += '2';	break;
	case CardRank::rank_3:			cardName += '3';	break;
	case CardRank::rank_4:			cardName += '4';	break;
	case CardRank::rank_5:			cardName += '5';	break;
	case CardRank::rank_6:			cardName += '6';	break;
	case CardRank::rank_7:			cardName += '7';	break;
	case CardRank::rank_8:			cardName += '8';	break;
	case CardRank::rank_9:			cardName += '9';	break;
	case CardRank::rank_10:			cardName += 'T';	break;
	case CardRank::rank_jack:		cardName += 'J';	break;
	case CardRank::rank_queen:		cardName += 'Q';	break;
	case CardRank::rank_king:		cardName += 'K';	break;
	case CardRank::rank_ace:		cardName += 'A';	break;

	default:						cardName += '?';	break;
	}

	switch (card.suit)
	{
	case CardSuit::suit_club:		cardName += 'C';	break;
	case CardSuit::suit_diamond:	cardName += 'D';	break;
	case CardSuit::suit_heart:		cardName += 'H';	break;
	case CardSuit::suit_spade:		cardName += 'S';	break;

	default:						cardName += '?';	break;
	}

	return cardName;
}

int getCardValue(const Card& card)
{
	if (card.rank <= CardRank::rank_10)
	{
		return (static_cast<int>(card.rank) + 2);
	}

	switch (card.rank)
	{
	case CardRank::rank_jack:
	case CardRank::rank_queen:
	case CardRank::rank_king:
		return 10;
	case CardRank::rank_ace:
		return 11;

	default:
		return 0;
	}
}

void printDeck(const deck_type& deck)
{
	for (const auto& card : deck)
	{
		std::cout << getCardName(card);
		std::cout << ' ';
	}

	std::cout << '\n';
}

void shuffleDeck(deck_type& deck)
{
	static std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };

	std::shuffle(deck.begin(), deck.end(), mt);
}

// Draws the next card from the deck, increases the score to the one drawing the card
// Returns the drawn card
// Also increments nextCardIndex
Card drawCard(Player& player, const deck_type& deck, index_type& nextCardIndex)
{
	Card card{ deck[nextCardIndex++] };
	player.score += getCardValue(card);
	
	// If the drawn card is an ace
	if (card.rank == CardRank::rank_ace)
		++player.aceCount;

	return card;
}

// Returns true if player wants to hit, false if they want to stand
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
				// In case the player enter something unexpected
				break;
		}
	}
}

// Changes the value of one ace from 11 to 1
void changeAceValue(Player& player)
{
	player.score -= 10;
	--player.aceCount;
}

// Returns true if player went bust, false otherwise
bool playerTurn(Player& player, const deck_type& deck, index_type& nextCardIndex)
{
	std::cout << "Your turn!\n";

	while (true)
	{
		if (player.score > maximumScore)
		{
			// Player has aces, so we have to change their score to 1 to avoid busting
			if (player.aceCount != 0)
			{
				changeAceValue(player);

				std::cout << "Value of an ace was changed from 11 to 1!\n" <<
					"You now have score: " << player.score << "\n\n";

				continue;
			}

			std::cout << "You went bust!\n";
			return true;
		}
		else
		{
			if (playerWantsHit())
			{
				Card currentCard{ drawCard(player, deck, nextCardIndex) };
				std::cout << "You were dealt the card " << getCardName(currentCard) <<
					", and now have score: " << player.score << "\n\n";
			}
			else
			{
				// Player didn't go bust
				std::cout << '\n';
				return false;
			}
		}
	}
}

// Returns true if dealer went bust, false otherwise
bool dealerTurn(Player& dealer, const deck_type& deck, index_type& nextCardIndex)
{
	std::cout << "Dealer's turn!\n";

	// Dealer draws cards until they reach the minimum score (17)
	// If they draw too much, but have aces, they are still in play
	while (dealer.score < minimumDealerScore || ((dealer.score > maximumScore) && (dealer.aceCount != 0)))
	{
		Card currentCard{ drawCard(dealer, deck, nextCardIndex) };
		std::cout << "The dealer draws the card " << getCardName(currentCard) <<
			", and now has score: " << dealer.score << '\n';

		// Dealer has aces, so we have to change their score to 1 to avoid busting
		if ((dealer.score > maximumScore) && (dealer.aceCount != 0))
		{
			changeAceValue(dealer);

			std::cout << "\nThe value of an ace was changed from 11 to 1!\n" <<
				"The dealer now has score: " << dealer.score << '\n';
		}
	}

	if (dealer.score > maximumScore)
	{
		// Dealer went bust
		std::cout << "\nThe dealer went bust!\n";
		return true;
	}

	// Dealer didn't go bust
	std::cout << "The dealer stands!\n\n";
	return false;
}

// Returns player_win, dealer_win or tie
BlackjackResult playBlackjack(/*const*/ deck_type& deck)
{
	index_type nextCardIndex{ 0 };

	// Create the dealer, give them 1 card
	Player dealer{ 0 };
	Card currentCard{ drawCard(dealer, deck, nextCardIndex) };
	std::cout << "The dealer draws the card " << getCardName(currentCard) <<
		", and now has score: " << dealer.score << '\n';

	// Create the player, give them 2 cards
	Player player{ 0 };
	currentCard = drawCard(player, deck, nextCardIndex);
	std::cout << "You were dealt the cards " << getCardName(currentCard);

	currentCard = drawCard(player, deck, nextCardIndex);
	std::cout << " and " << getCardName(currentCard) <<
		", and now have score: " << player.score << "\n\n";

	// Player goes first
	if (playerTurn(player, deck, nextCardIndex))
	{
		// Player went bust, player loses
		return BlackjackResult::player_lose;
	}

	// Dealer goes after the player
	if (dealerTurn(dealer, deck, nextCardIndex))
	{
		// Dealer went bust, player wins
		return BlackjackResult::player_win;
	}

	if (player.score > dealer.score)
		return BlackjackResult::player_win;		// Player wins
	else if (player.score < dealer.score)
		return BlackjackResult::player_lose;	// Player loses
	else
		return BlackjackResult::tie;			// Tie
}

int main()
{
	deck_type deck{ createDeck() };
	shuffleDeck(deck);

	std::cout << "Let's play some Blackjack!\n\n";

	switch (playBlackjack(deck))
	{
		case BlackjackResult::player_win:	std::cout << "You win!\n";		break;
		case BlackjackResult::player_lose:	std::cout << "You lose!\n";		break;
		case BlackjackResult::tie:			std::cout << "Tie!\n";			break;
	}

	return 0;
}