#ifndef HEARDER_H
#define HEARDER_H
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum sign { Hearts, Diamonds, Clubs, Spades };
enum color { Red, Black };


const char* getCardSign(enum sign signs);				// getter for the sign of the card
const char* getCardColor(enum color colors);			// getter for the color of the card










#endif