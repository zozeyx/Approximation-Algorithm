#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <limits>
#include <set>

using namespace std;

// 점(Point)을 나타내는 구조체
struct Point {
    int x, y;

    Point(int x = 0, int y = 0) : x(x), y(y) {}

    // 두 점 간의 거리 계산 (유클리드 거리)
    double distance(const Point& p) const {
        return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
    }

    // 중복 확인을 위한 비교 연산자 오버로딩
    bool operator<(const Point& p) const {
        return x < p.x || (x == p.x && y < p.y);  // x, y 순으로 비교
    }
};

// 각 클러스터의 중심을 계산하는 함수
Point calculateCenter(const vector<Point>& cluster) {
    int sum_x = 0, sum_y = 0;
    for (const auto& p : cluster) {
        sum_x += p.x;
        sum_y += p.y;
    }
    int center_x = sum_x / cluster.size();
    int center_y = sum_y / cluster.size();
    return Point(center_x, center_y);
}

// K-means 알고리즘
void Approx_k_Clusters(const vector<Point>& points, int k) {
    int n = points.size();
    vector<Point> centers(k);  // 각 클러스터의 중심점
    vector<vector<Point>> clusters(k);  // 각 클러스터에 속한 점들
    vector<int> assignments(n, -1);  // 각 점이 속하는 클러스터 번호

    // 1. 첫 번째 좌표를 첫 번째 중심점으로 설정
    centers[0] = points[0];
    
    bool changed;
    do {
        changed = false;

        // 2. 각 클러스터 초기화
        for (int i = 0; i < k; i++) {
            clusters[i].clear();  // 클러스터 초기화
        }

        // 3. 각 점에 대해 가장 가까운 중심점 찾기
        for (int i = 0; i < n; i++) {
            double minDist = numeric_limits<double>::max();
            int closestCluster = -1;
            for (int j = 0; j < k; j++) {
                double dist = points[i].distance(centers[j]);
                if (dist < minDist) {
                    minDist = dist;
                    closestCluster = j;
                }
            }

            // 4. 점이 속할 클러스터 변경되면 할당
            if (assignments[i] != closestCluster) {
                assignments[i] = closestCluster;
                changed = true;
            }
            clusters[closestCluster].push_back(points[i]);
        }

        // 5. 각 클러스터의 중심점 재계산
        for (int i = 0; i < k; i++) {
            if (!clusters[i].empty()) {
                centers[i] = calculateCenter(clusters[i]);
            }
        }

    } while (changed);  // 중심점이 더 이상 변하지 않을 때까지 반복

    // 결과 출력
    cout << "클러스터의 중심점과 해당 클러스터의 점들:" << endl;
    for (int i = 0; i < k; i++) {
        cout << "클러스터 " << i + 1 << " 중심점: (" << centers[i].x << ", " << centers[i].y << ")" << endl;
        cout << "점들: ";
        for (const auto& p : clusters[i]) {
            cout << "(" << p.x << ", " << p.y << ") ";
        }
        cout << endl << endl;
    }
}

int main() {
    // 파일에서 입력 좌표 읽기
    ifstream inputFile("clustering_input.txt");
    set<Point> uniquePoints;  // 중복된 좌표를 자동으로 처리하는 set

    int x, y;
    while (inputFile >> x >> y) {
        uniquePoints.insert(Point(x, y));  // set에 삽입 (중복 제거)
    }

    inputFile.close();

    // 중복을 제거한 좌표들을 vector로 변환
    vector<Point> points(uniquePoints.begin(), uniquePoints.end());

    int k = 8;  // 8개의 클러스터
    Approx_k_Clusters(points, k);  // K-means 클러스터링 수행

    return 0;
}
