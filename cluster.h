#pragma once
#include <vector>

class cluster {
	std::vector<std::pair<float, float>> points;
	std::pair<float, float> center;

public:
	cluster();
	cluster(std::vector<std::pair<float, float>>);
	virtual ~cluster();

	void addPoint(std::pair<float, float>);
	std::vector<std::pair<float, float>> getPoints();

	void calculateCenter();
	void setCenter(std::pair<float, float>);
	std::pair<float, float> getCenter();
};