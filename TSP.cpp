#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>

using namespace std;

struct Point {
    char name;
    double x, y;
};

// 두 점 사이의 거리 계산
double calculateDistance(const Point& p1, const Point& p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

// MST 생성
vector<vector<int>> createMST(const vector<Point>& points) {
    int n = points.size();
    vector<vector<int>> mst(n); // MST를 인접 리스트로 표현
    vector<bool> visited(n, false);
    vector<double> minDistance(n, numeric_limits<double>::infinity());
    vector<int> parent(n, -1);

    minDistance[0] = 0; // 시작점(A)

    for (int i = 0; i < n; ++i) {
        // 방문하지 않은 점 중 최소 비용으로 연결 가능한 점 선택
        int u = -1;
        for (int j = 0; j < n; ++j) {
            if (!visited[j] && (u == -1 || minDistance[j] < minDistance[u])) {
                u = j;
            }
        }

        visited[u] = true;

        // 선택된 점과 연결된 다른 점들 갱신
        for (int v = 0; v < n; ++v) {
            double dist = calculateDistance(points[u], points[v]);
            if (!visited[v] && dist < minDistance[v]) {
                minDistance[v] = dist;
                parent[v] = u;
            }
        }
    }

    // MST 생성 (인접 리스트)
    for (int i = 1; i < n; ++i) {
        mst[parent[i]].push_back(i);
        mst[i].push_back(parent[i]);
    }

    return mst;
}

// MST의 Pre-order Traversal
void preOrderTraversal(int node, const vector<vector<int>>& mst, vector<bool>& visited, vector<int>& path) {
    visited[node] = true;
    path.push_back(node);

    for (int neighbor : mst[node]) {
        if (!visited[neighbor]) {
            preOrderTraversal(neighbor, mst, visited, path);
        }
    }
}

// TSP
void TSP(const vector<Point>& points) {
    // 1. MST 생성
    vector<vector<int>> mst = createMST(points);

    // 2. Pre-order Traversal로 경로 생성
    vector<bool> visited(points.size(), false);
    vector<int> path;
    preOrderTraversal(0, mst, visited, path);

    // 3. 중복 방문 제거 및 거리 계산
    vector<char> finalPath;
    double totalDistance = 0.0;

    for (size_t i = 0; i < path.size(); ++i) {
        finalPath.push_back(points[path[i]].name);
        if (i > 0) {
            totalDistance += calculateDistance(points[path[i - 1]], points[path[i]]);
        }
    }

    // 시작점으로 돌아가는 거리 추가
    totalDistance += calculateDistance(points[path.back()], points[path[0]]);
    finalPath.push_back(points[path[0]].name);

    // 결과 출력
    cout << "이동 순서: ";
    for (char p : finalPath) {
        cout << p << " ";
    }
    cout << endl;
    cout << "총 이동 거리: " << totalDistance << endl;
}

int main() {
    // 점들 정의
    vector<Point> points = {
        {'A', 0, 3},
        {'B', 7, 5},
        {'C', 6, 0},
        {'D', 4, 3},
        {'E', 1, 0},
        {'F', 5, 3},
        {'G', 2, 2},
        {'H', 4, 1}
    };

    // TSP
    TSP(points);

    return 0;
}
