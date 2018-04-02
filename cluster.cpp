#include <cmath>
#include "cluster.h"

cluster::cluster() {

}

cluster::cluster(std::vector<std::pair<float, float>> init) {
	points = init;
}

cluster::~cluster() {

}

void cluster::addPoint(std::pair<float, float> pt) {
	points.push_back(pt);
}

std::vector<std::pair<float, float>> cluster::getPoints() {
	return points;
}

void cluster::calculateCenter() {
	float xsum = 0, ysum = 0;
	for (auto p : points) {
		xsum += p.first;
		ysum += p.second;
	}

	xsum /= points.size();
	ysum /= points.size();

	center = { xsum,ysum };
}

void cluster::setCenter(std::pair<float, float> ct) {
	center = ct;
}

std::pair<float, float> cluster::getCenter() {
	return center;
}