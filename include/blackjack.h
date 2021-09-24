#pragma once

#include "Deck.h"
#include "Player.h"

// Returns true if player wants to hit, false if they want to stand
bool playerWantsHit();

// Returns true if player went bust, false otherwise
bool playerTurn(Player& player, Deck& deck);

// Returns true if dealer went bust, false otherwise
bool dealerTurn(Player& dealer, Deck& deck);

// Returns true if dealer drew blackjack, false otherwise
bool dealerDrewBlackjack(Player& dealer, Deck& deck);

// Returns player_win, dealer_win or tie
BlackjackResult playBlackjack(Deck& deck);