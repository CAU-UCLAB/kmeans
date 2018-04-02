#include "kmeans.h"
#include <random>
#include <ctime>
#include <functional>
#include <algorithm>

float kmeans::distance(std::pair<float, float> a, std::pair<float, float> b) {
	return sqrtf(powf(a.first - b.first, 2) + powf(a.second - b.second, 2));
}

kmeans::kmeans() {

}

void kmeans::setPoints(std::vector<std::pair<float, float>> pts) {
	points = pts;
}

void kmeans::makeCluster(int n) {
	std::mt19937 engine(time(NULL));
	std::uniform_int_distribution<int> dist(0, points.size());
	auto generator = std::bind(dist, engine);

	std::vector<std::pair<float,float>> centers;
	while (centers.size() < n) {
		int g = generator();
		if (std::find(centers.begin(), centers.end(), points[g]) == centers.end()) {
			centers.push_back(points[g]);
		}
	}

	while (true) {
		auto match = new std::vector<int>[n];

		for (int i = 0; i < points.size(); i++) {
			int closest = -1;
			float closestDistance = std::numeric_limits<float>::max();

			for (int j = 0; j < n; j++) {
				if (distance(points[i], centers[j]) < closestDistance) {
					closest = j;
					closestDistance = distance(points[i], centers[j]);
				}
			}

			match[closest].push_back(i);
		}

		std::vector<cluster> clsvec;
		for (int i = 0; i < n; i++) {
			cluster c;
			c.setCenter(centers[i]);
			for (auto v : match[i])
				c.addPoint(points[v]);
			clsvec.push_back(c);
		}

		delete[] match;
		
		for (auto& c : clsvec) {
			c.calculateCenter();
		}

		int same = 0;
		for (int i = 0; i < n; i++)
			if (centers[i] == clsvec[i].getCenter()) same++;

		if (same == n) {
			clusters = clsvec;
			break;
		}

		for (int i = 0; i < n; i++)
			centers[i] = clsvec[i].getCenter();
	}

}
std::vector<cluster> kmeans::getClusters() {
	return clusters;
}