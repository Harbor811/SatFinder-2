#ifndef ROUTEPLANNER_H
#define ROUTEPLANNER_H

#include "Button.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <string>

class RoutePlanner
{
// Static methods
public:
	static enum location
	{
		A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, TR_1, TR_2, TR_3
	};
	static enum calculationMethod
	{
		AUTO,
		BRUTE_FORCE,
		NEAREST_NEIGHBOR,
		SIMULATED_ANNEALING
	};
	static std::unordered_map<std::string, location> stringToLocation;
	static std::unordered_map<location, std::string> locationToString;
	static std::unordered_map<sf::Keyboard::Key, RoutePlanner::location> keyToLocation;

// Non-static methods
private:
	struct Sat 
	{
	public:
		std::unordered_map<RoutePlanner::location, float> distances;
		RoutePlanner::location loc;
		std::string name;
		float x, y;

		Sat() {}
		Sat(RoutePlanner::location loc, std::string name, float x, float y) : loc(loc), name(name), x(x), y(y) {}
		std::string toString()
		{
			return name + " at " + std::to_string(x) + ", " + std::to_string(y);
		}
	};

	calculationMethod calcMethod;
	std::unordered_map<RoutePlanner::location, Sat*> satMap;
	std::vector<Sat> sats;
	std::vector<location> toVisit;
	std::vector<location> bestRoute;
	float bestDist;

	void initDistances();
	void initLocations();
	void calcBruteForce();
	void calcNearestNeighbor();
	void calcSimulatedAnnealing();

public:
	RoutePlanner();
	~RoutePlanner();

	std::vector<location> getToVisit();
	bool contains(location loc);
	std::string toString();
	bool empty();

	void calculateBest(const calculationMethod& method = AUTO);
	void add(location loc);
	void remove(location loc);
	void clear();

	size_t getSize() const;
	std::string getBestString();
	float getBestDistance();
	std::vector<location> getBestOrder();
	
};

#endif