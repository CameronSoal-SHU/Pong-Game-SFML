#pragma once
/*
Static class desinged to seed and generate random values
*/
class RandomNumberGenerator {
public:
	// Seeding for pseudo random
	static void GenerateSeed();
	static void GenerateSeed(unsigned s);

	// Generate a random unsigned integer between 2 optional given bounds
	static unsigned GenerateRandomUnsigned(unsigned min = 0, unsigned max = 0xffffffff);
};