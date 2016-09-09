#include "Header.h"

const char* getCardSign(enum sign signs)				// getter for the sign od the card
	switch (signs)							// switch case of signs
		case Hearts: return "Hearts";
		case Diamonds: return "Diamonds";
		case Clubs: return "Clubs";
		case Spades: return "Spades";
	}
}

const char* getCardColor(enum color colors)				// getter for the color od the card
	switch (colors)							// switch case of colors
		case Red: return "Red";
		case Black: return "Black";
	}
}
