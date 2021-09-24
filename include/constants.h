#pragma once

namespace scores
{
	// Maximum score before losing
	constexpr int MAXIMUM_SCORE{ 21 };

	// Minimum dealer score
	constexpr int MINIMUM_DEALER_SCORE{ 17 };

	// Minimum score needed for a blackjack
	constexpr int MINIMUM_BLACKJACK_SCORE{ 10 };
}

enum class BlackjackResult
{
	PLAYER_WIN,
	PLAYER_LOSE,
	TIE
};