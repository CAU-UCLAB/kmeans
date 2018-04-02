#include <iostream>
#include <fstream>
#include "kmeans.h"
#include "gnuplot-iostream.h"
#include <boost\tuple\tuple.hpp>

#define N_CLUSTERS 3
#define N_POINTS 18

int main(void) {
	kmeans km;
	std::vector<std::pair<float, float>> points = {
		{ -3.f, 2.f },{ -3.f, 3.f },{ -2.f, 2.f },
		{ 2.f, 2.f },{ 3.f, 2.f },{ 4.f, 2.f },
		{ 3.f, 3.5f },{ 3.f, 2.5f },{ 4.f, 2.5f },
		{ 2.f, -2.f },{ 3.f, -1.f },{ 3.f, -2.f },
		{ 2.f, -2.5f },{ 3.f, -1.5f },{ 3.5f, -2.f },
		{ 4.f, -1.f }, { 2.f, -4.f }, { 2.5f, 0.f }
	};
	km.setPoints(points);
	km.makeCluster(N_CLUSTERS);
	auto cls = km.getClusters();

	for (auto c : cls) {
		std::cout << "Cluster::" << std::endl;
		std::cout << "center : " << c.getCenter().first << ", " << c.getCenter().second << std::endl;
		for (auto p : c.getPoints()) {
			std::cout << "(" << p.first << ", " << p.second << ") ";
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}
	
	std::ofstream out("kmeans_result.txt");
	for (auto c : cls) {
		out << c.getPoints().size() << " ";
		for (auto v : c.getPoints()) {
			out << v.first << " " << v.second << " ";
		}
		out << std::endl;
	}
	out.close();


	Gnuplot gp("C:\\Program\" \"Files\\gnuplot\\bin\\gnuplot -persist");
	gp << "set style line 1 lc rgb 'black' pt 5" << std::endl;
	gp << "set style line 3 lc rgb 'red' pt 15 ps 1.5" << std::endl;
	
	gp << "set key outside" << std::endl;

	//gp << "set terminal eps" << std::endl;
	//gp << "set output \"output.eps\"" << std::endl;

	gp << "plot ";
	for (int i = 0; i < N_POINTS; i++) {
		gp << "'-' w p ls 1";
		gp << ", ";
	}
	for (int i = 0; i < N_CLUSTERS; i++) {
		gp << "'-' w p ls 3";
		if (i != N_CLUSTERS - 1)
			gp << ", ";
	}
	gp << std::endl;

	for (int i = 0; i < N_POINTS; i++) {
		gp << points[i].first << " " << points[i].second << std::endl;
		gp << "e" << std::endl;
	}
	for (int i = 0; i < N_CLUSTERS; i++) {
		gp << cls[i].getCenter().first << " " << cls[i].getCenter().second << std::endl;
		gp << "e" << std::endl;
	}


	gp.close();
	return 0;
}