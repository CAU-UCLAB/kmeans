#pragma once
#include "cluster.h"

class kmeans {
	std::vector<std::pair<float, float>> points;
	std::vector<cluster> clusters;

	float distance(std::pair<float, float>, std::pair<float, float>);

public:
	kmeans();
	
	void setPoints(std::vector<std::pair<float, float>>);
	void makeCluster(int n);
	std::vector<cluster> getClusters();
};