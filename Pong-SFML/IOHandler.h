#pragma once
#include "SFML/Graphics.hpp"
#include <string>

/* 
Static class to handle receiving and validating inputs by the user
*/
class IOHandler {
public:
	// Functions used to limit inputs
	//<param "maxLength"> Maximum character length of input buffer (256 chars default) </param>
	static void NumericInput(const unsigned maxLength = 256);
	static void AlphaInput(const unsigned maxLength = 256);
	static void AlphaNumericInput(const unsigned maxLength = 256);

	/* Used to clear both the lastInput and inputBuffer variables
	When the held data is no longer needed */
	static void Flush();

	/* Check if an input value is within a certain ascii boundary
	<param "val"> The value to be checked </param>
	<param "min"> The minimum bound </param>
	<param "max"> The maximum bound </param>
	<return> Returns true if val is within the given bounds </return>
	*/
	static bool WithinBounds(int val, int min, int max);

	// Hold the last known character inputted by the user
	static sf::Uint32 lastInput;
	// Hold cumulative input characters whenever necessary
	static std::string inputBuffer;
};
