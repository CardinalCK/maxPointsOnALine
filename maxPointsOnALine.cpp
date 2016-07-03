#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <sstream>

using namespace std;

class Point {
public:
	const int x;
	const int y;
	const int index;
	Point();
	Point(int x, int y, int index) : x(x), y(y), index(index) {}
	string printPoint() {
		ostringstream oss;
		oss << '(' << x << ',' << y << ')';
		return oss.str();
	}

	bool operator== (const Point& rhs) const {
		return (this->x == rhs.x && this->y == rhs.y && this->index == rhs.index);
	}
};

class Line {
public:
	const double slope;
	const double yint;
	const int xint;
	Line();
	Line(Point p1, Point p2) : slope(((double)(p1.x-p2.x) == 0 ? INFINITY : ((double)(p1.y-p2.y) /  double(p1.x-p2.x)))), yint((double)(p1.y)-slope *(p1.x)), xint((slope == INFINITY) ? p1.x : ((double)p1.y - yint)/slope) {
		
		//cout << "Created new line from " << p1.printPoint() << " and " << p2.printPoint() << " Slope: " << slope << " yint: " << yint << " xint: " << xint << endl;
	} 
	bool operator==(const Line& rhs) const {
		//cout << this->slope << " " << rhs.slope << " " << (this->slope == rhs.slope && this->yint == rhs.yint) << "" endl;
		return (this->slope == rhs.slope && this->yint == rhs.yint && this->xint == rhs.xint);
	}
	// bool operator< (const Line& rhs) const {
	// 	return this->slope < rhs.slope;
	// }
};

namespace std {

    template<>
	struct hash<Line> {
		size_t operator() (const Line& l) const {
			return l.slope + l.yint;
		}
	};

    template<>
	struct hash<Point> {
		size_t operator() (const Point& p) const {
			return p.x * 3 + p.y * 5;
		}
	};

}

vector<Point> processVectors(vector<int> &X, vector<int> &Y) {
	vector<Point> vec;
	for (int i = 0; i < X.size(); i++) {
		Point p = Point(X[i], Y[i], i);
		vec.push_back(p);
	}
	return vec;
}

int maxPoints(vector<int> &X, vector<int> &Y) {
	if (X.size() == 0) return 0;
	vector<Point> points = processVectors(X,Y);
	unordered_map<Line, unordered_set<Point>> m;
	int maxPoints = 1;
	for (int i = 0; i < points.size(); i++) {
		for (int j = i + 1; j < points.size(); j++) {
			Point p1 = points[i];
			Point p2 = points[j];
			Line l = Line(p1, p2);
			m[l].insert(p1);
			m[l].insert(p2);
			//cout << m[l].size() << endl;
		}   
	}
	for (auto& p : m) {
		unordered_set<Point> s = p.second;
		//cout << "Slope " << p.first.slope << " YInt " << p.first.yint << " NumPoints " << (int)s.size() << endl;
		maxPoints = max(maxPoints, (int)s.size());
	}

	return maxPoints;
}

int main(int argc, char** argv) {
	vector<int> X;
	vector<int> Y;
	int numPoints = atoi(argv[1]);
	for (int i = 2; i < numPoints * 2 + 2; i++) {
		int xVal = atoi(argv[i]);
		int yVal = atoi(argv[++i]);
		X.push_back(xVal);
		Y.push_back(yVal);
	}
	cout << maxPoints(X, Y) << endl; 
}
