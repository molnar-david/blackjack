#pragma once

#include "constants.h"
#include "Deck.h"

class Player
{
private:
	int m_score{ 0 };
	int m_aceCount{ 0 };			// To keep track of aces dealt, and modify it's score to 1 if necessary

public:
	Player() = default;
	int score() { return m_score; }

	const Card& drawCard(Deck& deck);
	bool isBust();

	// Changes the value of one ace from 11 to 1
	void changeAceValue();
};