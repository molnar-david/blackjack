#pragma once

// Maximum score before losing
constexpr int MAXIMUM_SCORE{ 21 };

// Minimum dealer score
constexpr int MINIMUM_DEALER_SCORE{ 17 };

enum class BlackjackResult
{
	PLAYER_WIN,
	PLAYER_LOSE,
	TIE
};