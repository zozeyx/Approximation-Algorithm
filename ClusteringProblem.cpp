#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <set>
#include <map>
#include <fstream>
#include <sstream>

using namespace std;

// 구조체로 좌표를 나타냄
struct Point {
    int x, y;
    
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    
    // 두 점 사이의 유클리드 거리 계산
    double distance(const Point& other) const {
        return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
    }
};

void printCluster(const vector<vector<Point>>& clusters) {
    for (int i = 0; i < clusters.size(); ++i) {
        cout << "Cluster " << i + 1 << " center: (" << clusters[i][0].x << ", " << clusters[i][0].y << ")\n";
        cout << "Points: ";
        for (const auto& p : clusters[i]) {
            cout << "(" << p.x << ", " << p.y << ") ";
        }
        cout << endl;
    }
}

// k개의 클러스터를 구하는 함수
void Approx_k_Clusters(const vector<Point>& points, int k) {
    int n = points.size();
    vector<Point> centers;  // 클러스터 센터들
    vector<vector<Point>> clusters(k);  // 각 클러스터에 포함될 점들

    // 첫 번째 클러스터 센터는 첫 번째 점으로 설정
    centers.push_back(points[0]);

    // 나머지 k-1개의 센터를 설정 (가장 멀리 있는 점들 선택)
    for (int j = 1; j < k; ++j) {
        vector<double> dist(n, numeric_limits<double>::max());

        // 각 점이 기존 센터들과 얼마나 멀리 떨어져 있는지 계산
        for (int i = 0; i < n; ++i) {
            for (int m = 0; m < j; ++m) {
                dist[i] = min(dist[i], points[i].distance(centers[m]));
            }
        }

        // 가장 멀리 있는 점을 새로운 센터로 선택
        double maxDist = -1;
        int maxIndex = -1;
        for (int i = 0; i < n; ++i) {
            if (dist[i] > maxDist) {
                maxDist = dist[i];
                maxIndex = i;
            }
        }

        centers.push_back(points[maxIndex]);
    }

    // 중심점을 기준으로 점들을 할당
    bool changed = true;
    while (changed) {
        changed = false;
        // 클러스터를 초기화
        for (int i = 0; i < k; ++i) {
            clusters[i].clear();
        }

        // 각 점을 가장 가까운 중심점에 할당
        for (int i = 0; i < n; ++i) {
            double minDist = numeric_limits<double>::max();
            int clusterIndex = -1;
            for (int j = 0; j < k; ++j) {
                double dist = points[i].distance(centers[j]);
                if (dist < minDist) {
                    minDist = dist;
                    clusterIndex = j;
                }
            }
            clusters[clusterIndex].push_back(points[i]);
        }

        // 각 클러스터의 새로운 중심점 계산
        vector<Point> newCenters;
        for (int i = 0; i < k; ++i) {
            int sumX = 0, sumY = 0;
            for (const auto& p : clusters[i]) {
                sumX += p.x;
                sumY += p.y;
            }
            Point newCenter(sumX / clusters[i].size(), sumY / clusters[i].size());
            newCenters.push_back(newCenter);

            // 중심점이 변화하면 changed = true
            if (newCenter.x != centers[i].x || newCenter.y != centers[i].y) {
                changed = true;
            }
        }
        centers = newCenters;  // 새로운 중심점을 반영
    }

    // 결과 출력
    printCluster(clusters);
}

// 파일에서 (x, y) 좌표 읽기
vector<Point> readPointsFromFile(const string& filename) {
    vector<Point> points;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        int x, y;
        ss >> x >> y;
        points.push_back(Point(x, y));
    }
    return points;
}

int main() {
    // 파일에서 좌표 읽기
    string filename = "clustering_input.txt";
    vector<Point> points = readPointsFromFile(filename);

    // 중복 제거
    set<Point> uniquePoints(points.begin(), points.end());
    points.assign(uniquePoints.begin(), uniquePoints.end());

    // k개의 클러스터로 나누기
    int k = 8;
    Approx_k_Clusters(points, k);

    return 0;
}
