#ifndef ROUTEPLANNER_H
#define ROUTEPLANNER_H

#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <string>

class RoutePlanner
{
public:
	static enum location
	{
		A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, TR_1, TR_2, TR_3
	};
	static std::unordered_map<std::string, location> stringToLocation;
	static std::unordered_map<location, std::string> locationToString;

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

	std::unordered_map<RoutePlanner::location, Sat*> satMap;
	std::vector<Sat> sats;
	std::vector<location> toVisit;
	std::vector<location> bestRoute;
	float bestDist;

	void initDistances();
	void initLocations();

public:
	RoutePlanner();
	~RoutePlanner();

	std::vector<location> getToVisit();
	bool contains(location loc);
	std::string toString();
	bool empty();

	void calculateBest();
	void add(location loc);
	void remove(location loc);
	void clear();

	std::string getBestString();
	float getBestDistance();
};

#endif