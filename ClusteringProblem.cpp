#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <cmath>
#include <limits>
#include <iomanip>
#include <algorithm>

using namespace std;

// 구조체: 2D 좌표를 표현
struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}

    // 두 점이 같은지 비교하는 연산자
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

// 두 점 사이의 유클리드 거리 계산
double calculateDistance(const Point& p1, const Point& p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

// 클러스터의 중심점 계산 (x, y 좌표 평균값)
Point calculateCenter(const vector<Point>& cluster) {
    int sumX = 0, sumY = 0;
    for (const auto& point : cluster) {
        sumX += point.x;
        sumY += point.y;
    }
    return Point(sumX / cluster.size(), sumY / cluster.size());
}

// K-means++ 초기화 알고리즘
void initializeCenters(const vector<Point>& points, vector<Point>& centers, int k) {
    centers.push_back(points[0]); // 첫 번째 중심점은 파일의 첫 번째 점으로 설정

    // 나머지 k-1개의 중심점 선택
    for (int i = 1; i < k; ++i) {
        vector<double> distances(points.size(), numeric_limits<double>::max());

        // 각 점에 대해 가장 가까운 중심점과의 거리를 계산
        for (int j = 0; j < points.size(); ++j) {
            double minDist = numeric_limits<double>::max();
            for (int c = 0; c < centers.size(); ++c) {
                double dist = calculateDistance(points[j], centers[c]);
                minDist = min(minDist, dist);
            }
            distances[j] = minDist * minDist; // 거리의 제곱값을 사용
        }

        // 가장 큰 거리를 가진 점을 새로운 중심점으로 추가
        double maxDist = -1;
        int maxIndex = -1;
        for (int j = 0; j < points.size(); ++j) {
            if (distances[j] > maxDist) {
                maxDist = distances[j];
                maxIndex = j;
            }
        }

        centers.push_back(points[maxIndex]);
    }
}

// K-means 알고리즘
void kMeansClustering(vector<Point>& points, int k) {
    vector<Point> centers(k);          // 중심점 저장
    vector<vector<Point>> clusters(k); // 각 클러스터에 포함된 점

    // 첫 번째 중심점은 입력 파일의 첫 번째 좌표로 고정
    initializeCenters(points, centers, k);

    bool changed;
    do {
        // 클러스터 초기화
        for (auto& cluster : clusters) {
            cluster.clear();
        }

        // 각 점을 가장 가까운 중심점의 클러스터에 추가
        for (const auto& point : points) {
            int closestCenter = 0;
            double minDistance = calculateDistance(point, centers[0]);
            for (int i = 1; i < k; ++i) {
                double distance = calculateDistance(point, centers[i]);
                if (distance < minDistance) {
                    minDistance = distance;
                    closestCenter = i;
                }
            }
            clusters[closestCenter].push_back(point);
        }

        // 중심점 업데이트
        changed = false;
        for (int i = 0; i < k; ++i) {
            if (!clusters[i].empty()) {
                // 클러스터의 새로운 중심점을 계산
                Point newCenter = calculateCenter(clusters[i]);

                // 중심점이 변경되었으면, 해당 중심점을 업데이트하고 flag를 true로 설정
                if (newCenter.x != centers[i].x || newCenter.y != centers[i].y) {
                    centers[i] = newCenter;
                    changed = true;
                }
            }
        }
    } while (changed); // 중심점이 변경되지 않을 때까지 반복

    // 결과 출력
    cout << "Clusters and Centers:\n";
    for (int i = 0; i < k; ++i) {
        cout << "Cluster " << i + 1 << ":\n";
        cout << "Center: (" << centers[i].x << ", " << centers[i].y << ")\n"; // 중심점 출력

        // 클러스터 점 출력
        for (const auto& point : clusters[i]) {
            cout << "(" << point.x << ", " << point.y << ")\n";
        }
        cout << endl;
    }
}

int main() {
    ifstream inputFile("clustering_input.txt");
    if (!inputFile) {
        cerr << "Error: Unable to open input file.\n";
        return 1;
    }

    set<pair<int, int>> uniquePoints; // 중복 제거를 위한 집합
    vector<Point> points;

    // 입력 파일 읽기
    int x, y;
    while (inputFile >> x >> y) {
        if (uniquePoints.insert({x, y}).second) { // 중복되지 않은 좌표만 추가
            points.emplace_back(x, y);
        }
    }
    inputFile.close();

    if (points.size() < 8) {
        cerr << "Error: Not enough unique points for 8 clusters.\n";
        return 1;
    }

    // 클러스터링 수행 (k = 8)
    kMeansClustering(points, 8);

    return 0;
}
