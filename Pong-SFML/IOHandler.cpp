#include "IOHandler.h"
#include "GameData.h"

sf::Uint32 IOHandler::lastInput;
std::string IOHandler::inputBuffer;


bool IOHandler::WithinBounds(int val, int min, int max) {
	// Make sure value is within boundaries
	return !(val < min || val > max);
}

void IOHandler::AlphaNumericInput(const unsigned maxLength) {
	// Only remove a character if the input buffer is not empty
	if (lastInput == GameConstants::BACKSPACE && inputBuffer.length() != 0) {
		inputBuffer.erase(inputBuffer.end() - 1);
	}
	else {
		if (WithinBounds(lastInput, GameConstants::NUM_MIN, GameConstants::ALPHA_LC_MAX) && inputBuffer.length() < maxLength) {
			inputBuffer += lastInput;
		}
	}
}

void IOHandler::AlphaInput(const unsigned maxLength) {
	// Only remove a character if the input buffer is not empty
	if (lastInput == GameConstants::BACKSPACE && inputBuffer.length() != 0) {
		inputBuffer.erase(inputBuffer.end() - 1);
	}
	else {
		if (WithinBounds(lastInput, GameConstants::ALPHA_UC_MIN, GameConstants::ALPHA_LC_MAX) && inputBuffer.length() < maxLength) {
			inputBuffer += lastInput;
		}
	}
}

void IOHandler::NumericInput(const unsigned maxLength) {
	if (lastInput == GameConstants::BACKSPACE) {
		if (inputBuffer.length() > 1)
			inputBuffer.erase(inputBuffer.end() - 1);	// Remove last character
		else
			inputBuffer = "0";							// Always make an empty numeric input buffer default to 0
	}
	// Only take numbers 0-9
	else if (WithinBounds(lastInput, GameConstants::NUM_MIN, GameConstants::NUM_MAX)) {
		// Check if the default needs to be replaced
		if (inputBuffer == "0" || inputBuffer.length() == maxLength)
			inputBuffer[inputBuffer.length() - 1] = lastInput;		// Remove proceeding 0 or replace last character when char limit is reached
		else
			inputBuffer += static_cast<char>(lastInput);			// Add number onto the end
	}
}

void IOHandler::Flush() {
	inputBuffer = "";
	lastInput = NULL;
}