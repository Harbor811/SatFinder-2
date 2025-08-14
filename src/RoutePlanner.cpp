#include "RoutePlanner.h"

std::unordered_map<std::string, RoutePlanner::location> RoutePlanner::stringToLocation = {
		{"A", A}, {"B", B}, {"C", C}, {"D", D}, {"E", E}, {"F", F}, {"G", G}, {"H", H}, {"I", I}, {"J", J}, {"K", K}, {"L", L}, {"M", M}, {"N", N}, {"O", O}, {"P", P}, {"Q", Q}, {"R", R}, {"S", S}, {"T", T}, {"U", U}, {"V", V}, {"W", W}, {"X", X}, {"Y", Y}, {"1", TR_1}, {"2", TR_2}, {"3", TR_3}
};
std::unordered_map<RoutePlanner::location, std::string> RoutePlanner::locationToString = {
	{A, "A"}, {B, "B"}, {C, "C"}, {D, "D"}, {E, "E"}, {F, "F"}, {G, "G"}, {H, "H"}, {I, "I"}, {J, "J"}, {K, "K"}, {L, "L"}, {M, "M"}, {N, "N"}, {O, "O"}, {P, "P"}, {Q, "Q"}, {R, "R"}, {S, "S"}, {T, "T"}, {U, "U"}, {V, "V"}, {W, "W"}, {X, "X"}, {Y, "Y"}, {TR_1, "1"}, {TR_2, "2"}, {TR_3, "3"}
};

std::unordered_map<sf::Keyboard::Key, RoutePlanner::location> RoutePlanner::keyToLocation = {
	{sf::Keyboard::A, A}, {sf::Keyboard::B, B}, {sf::Keyboard::C, C}, {sf::Keyboard::D, D}, {sf::Keyboard::E, E}, {sf::Keyboard::F, F}, {sf::Keyboard::G, G}, {sf::Keyboard::H, H}, {sf::Keyboard::I, I}, {sf::Keyboard::J, J}, {sf::Keyboard::K, K}, {sf::Keyboard::L, L}, {sf::Keyboard::M, M}, {sf::Keyboard::N, N}, {sf::Keyboard::O, O}, {sf::Keyboard::P, P}, {sf::Keyboard::Q, Q}, {sf::Keyboard::R, R}, {sf::Keyboard::S, S}, {sf::Keyboard::T, T}, {sf::Keyboard::U, U}, {sf::Keyboard::V, V}, {sf::Keyboard::W, W}, {sf::Keyboard::X, X}, {sf::Keyboard::Y, Y}, {sf::Keyboard::Num1, TR_1}, {sf::Keyboard::Num2, TR_2}, {sf::Keyboard::Num3, TR_3}
};

void RoutePlanner::initDistances()
{
	// Initialize all location distances from each other in data_dist.bin
	std::ifstream in("assets/data_dist.bin", std::ios::binary);
	if (!in) { throw std::runtime_error("Failed to open data_dist.bin!"); }

	uint32_t satCount = 0;
	in.read(reinterpret_cast<char*>(&satCount), sizeof(satCount));
	//sats.resize(satCount);
	
	for (auto& sat : sats)
	{
		uint32_t mapSize = 0;
		in.read(reinterpret_cast<char*>(&mapSize), sizeof(mapSize));

		sat.distances.clear();
		for (uint32_t i = 0; i < mapSize; i++)
		{
			RoutePlanner::location loc;
			float dist;

			// Read enum as string
			uint32_t locLen;
			std::string curLoc;
			in.read(reinterpret_cast<char*>(&locLen), sizeof(locLen));
			curLoc.resize(locLen);
			in.read(&curLoc[0], locLen);
			loc = stringToLocation.at(curLoc);

			// Read dist
			in.read(reinterpret_cast<char*>(&dist), sizeof(dist));

			// Emplace
			sat.distances.emplace(loc, dist);
		}
	}
	in.close();

	// Add sats to satmap
	for (Sat& sat : sats)
	{
		satMap.emplace(sat.loc, &sat);
	}

	// Calculate distances
	/*for (auto& satA : sats)
	{
		satA.distances.clear();
		for (const auto& satB : sats)
		{
			float dx = satA.x - satB.x;
			float dy = satA.y - satB.y;
			float dist = std::sqrt(dx * dx + dy * dy);
			satA.distances.emplace(satB.loc, dist);
		}
	}*/

	// Write distances to data_dist.bin
	/*
	std::ofstream out("assets/data_dist.bin", std::ios::binary);
	if (!out) { throw std::runtime_error("Failed to open data_dist.bin!"); }

	uint32_t satCount = sats.size();
	out.write(reinterpret_cast<const char*>(&satCount), sizeof(satCount));

	for (const auto& sat : sats)
	{
		uint32_t mapSize = sat.distances.size();
		out.write(reinterpret_cast<const char*>(&mapSize), sizeof(mapSize));

		for (const auto& pair : sat.distances)
		{
			// Enum written as string
			uint32_t locLen = locationToString.at(pair.first).size();
			out.write(reinterpret_cast<const char*>(&locLen), sizeof(locLen));
			out.write(locationToString.at(pair.first).c_str(), locLen);

			// Write float as float URRRR
			out.write(reinterpret_cast<const char*>(&pair.second), sizeof(pair.second));
		}
	}

	out.close();
	*/

	// Write distances to data_dist.txt (OLD)
	/*
	std::ofstream out("assets/data_dist.txt");
	if (!out) { throw std::runtime_error("Failed to open data_dist.txt!"); }

	for (const auto& sat : sats)
	{
		out << "Satellite " << sat.name << " (" << sat.x << ", " << sat.y << ")\n";
		for (const auto& pair : sat.distances)
		{
			out << "  To " << RoutePlanner::locationToString.at(pair.first) << " = " << std::fixed << std::setprecision(2) << pair.second << "\n";
		}
		out << "\n";
	}*/
}

void RoutePlanner::initLocations()
{
	// Initialize all locations from data.txt
	sats.clear();
	std::string loc;
	std::string name;
	
	// Read from sats.bin
	std::ifstream in("assets/sats.bin", std::ios::binary);
	if (!in) { throw std::runtime_error("Failed to open sats.bin!"); }

	uint32_t count;
	in.read(reinterpret_cast<char*>(&count), sizeof(count));

	for (uint32_t i = 0; i < count; i++)
	{
		Sat sat;

		// Read enum as string
		uint32_t locLen;
		std::string curLoc;
		in.read(reinterpret_cast<char*>(&locLen), sizeof(locLen));
		curLoc.resize(locLen);
		in.read(&curLoc[0], locLen);
		sat.loc = stringToLocation.at(curLoc);

		// Read name as string also
		uint32_t strLen;
		in.read(reinterpret_cast<char*>(&strLen), sizeof(strLen));
		sat.name.resize(strLen);
		in.read(&sat.name[0], strLen);

		// Read floats
		in.read(reinterpret_cast<char*>(&sat.x), sizeof(sat.x));
		in.read(reinterpret_cast<char*>(&sat.y), sizeof(sat.y));

		sats.push_back(sat);
	}
	
	initDistances();

	// Read from .txt (OLD)
	/*
	std::ifstream data("assets/data.txt");

	while (data >> loc >> name >> x >> y)
	{
		//std::cout << loc << ", " << name << std::endl;
		sats.push_back(RoutePlanner::Sat(stringToLocation.at(loc), name, x, y));
	}

	data.close();
	*/	

	// Write to binary
	/*
	std::ofstream out("assets/data.bin", std::ios::binary);
	if (!out) { throw std::runtime_error("Failed to open data.bin"); }

	uint32_t count = sats.size();
	out.write(reinterpret_cast<const char*>(&count), sizeof(count));

	for (const auto& sat : sats)
	{
		// Write enum as string
		uint32_t locLen = locationToString.at(sat.loc).size();
		out.write(reinterpret_cast<const char*>(&locLen), sizeof(locLen));
		out.write(locationToString.at(sat.loc).c_str(), locLen);

		// Write name also as string
		uint32_t strLen = sat.name.size();
		out.write(reinterpret_cast<const char*>(&strLen), sizeof(strLen));
		out.write(sat.name.c_str(), strLen);

		// Write floats
		out.write(reinterpret_cast<const char*>(&sat.x), sizeof(sat.x));
		out.write(reinterpret_cast<const char*>(&sat.y), sizeof(sat.y));
	}*/
}

RoutePlanner::RoutePlanner()
{
	srand((unsigned)time(nullptr)); // For simulated annealing
	toVisit.clear();
	initLocations();
	calcMethod = AUTO;
}

RoutePlanner::~RoutePlanner()
{
}

std::vector<RoutePlanner::location> RoutePlanner::getToVisit()
{
	return toVisit;
}

bool RoutePlanner::contains(location loc)
{
	for (location& visitLoc : toVisit)
	{
		if (visitLoc == loc) { return true; }
	}

	return false;
}

std::string RoutePlanner::toString()
{
	std::string ret = "toVisit: ";
	for (auto& loc : toVisit)
	{
		ret += locationToString.at(loc) + " ";
	}
	return ret;
}

bool RoutePlanner::empty()
{
	return toVisit.empty();
}

void RoutePlanner::calcBruteForce()
{
	// Based on Traveling Salesman Problem
	bestDist = std::numeric_limits<float>::max();

	// Make a copy of toVisit for permutations
	std::vector<RoutePlanner::location> route = toVisit;

	do
	{
		float totalDist = satMap.at(location::A)->distances.at(route.front());

		for (size_t i = 0; i < route.size() - 1; i++)
		{
			Sat* from = satMap.at(route[i]);
			RoutePlanner::location to = route[i + 1];
			totalDist += from->distances.at(to);
		}
		totalDist += satMap.at(route.back())->distances.at(location::A);

		if (totalDist < bestDist)
		{
			bestDist = totalDist;
			bestRoute = route;
		}

	} while (std::next_permutation(route.begin(), route.end()));
}

void RoutePlanner::calcNearestNeighbor()
{
	bestRoute.clear();
	std::vector<bool> visited(toVisit.size(), false);
	float totalDist = 0.f;
	RoutePlanner::location currentLoc = A;

	for (int step = 0; step < toVisit.size(); step++)
	{
		double bestDist = std::numeric_limits<double>::max();
		int bestInd = -1;

		for (int i = 0; i < toVisit.size(); i++)
		{
			if (!visited[i])
			{
				float dist = satMap.at(currentLoc)->distances.at(toVisit.at(i));
				if (dist < bestDist)
				{
					bestDist = dist;
					bestInd = i;
				}
			}
		}

		visited[bestInd] = true;
		bestRoute.push_back(toVisit.at(bestInd));
		totalDist += bestDist;
		currentLoc = toVisit.at(bestInd);
	}

	// Return to start
	totalDist += satMap.at(currentLoc)->distances.at(A);

	bestDist = totalDist;
}

void RoutePlanner::calcSimulatedAnnealing()
{
	auto getTotalDist = [&](const std::vector<location>& route)
		{
			float total = satMap.at(A)->distances.at(route[0]);
			for (size_t i = 0; i < route.size() - 1; i++)
			{
				total += satMap.at(route[i])->distances.at(route[i + 1]);
			}
			total += satMap.at(route[route.size() - 1])->distances.at(A);
			return total;
		};

	float T = 1000.f;
	float minT = 0.001f;
	float cooling = 0.995f;
	bestRoute = toVisit;
	bestDist = getTotalDist(toVisit);

	while (T > minT)
	{
		std::vector<location> newRoute = bestRoute;
		int i = rand() % toVisit.size();
		int j = rand() % toVisit.size();
		std::swap(newRoute[i], newRoute[j]);

		float newBestDist = getTotalDist(newRoute);
		float delta = newBestDist - bestDist;

		if (delta < 0 || (rand() / double(RAND_MAX)) < exp(-delta / T))
		{
			bestRoute = newRoute;
			bestDist = newBestDist;
		}

		T *= cooling;
	}
}

void RoutePlanner::calculateBest(const calculationMethod& method)
{
	calcMethod = method;

	switch (calcMethod)
	{
	case AUTO:
		if (toVisit.size() < 10) 
		{ 
			calcBruteForce(); 
		}
		else
		{
			calcSimulatedAnnealing();
		}
		break;

	case BRUTE_FORCE:
		calcBruteForce();
		break;

	case NEAREST_NEIGHBOR:
		calcNearestNeighbor();
		break;
	
	case SIMULATED_ANNEALING:
		calcSimulatedAnnealing();
		break;
	}
}

void RoutePlanner::add(location loc)
{
	toVisit.emplace_back(loc);
}

void RoutePlanner::remove(location loc)
{
	for (int ind = 0; ind < toVisit.size(); ind++)
	{
		if (toVisit.at(ind) == loc)
		{
			toVisit.erase(toVisit.begin() + ind);
			break;
		}
	}
}

void RoutePlanner::clear()
{
	toVisit.clear();
}

std::string RoutePlanner::getBestString()
{
	std::string ret;
	for (size_t i = 0; i < bestRoute.size(); i++)
	{
		ret += satMap.at(bestRoute[i])->name;
		if (i < bestRoute.size() - 1)
		{
			ret += ">";
		}
	}
	return ret;
}

size_t RoutePlanner::getSize() const
{
	return bestRoute.size();
}

float RoutePlanner::getBestDistance()
{
	return bestDist;
}

std::vector<RoutePlanner::location> RoutePlanner::getBestOrder()
{
	return bestRoute;
}
