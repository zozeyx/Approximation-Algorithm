import java.util.*;

public class VertexCoverProblem {

    public static void main(String[] args) {
        // 입력 데이터
        String[] vertices = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P"};
        String[] edges = {
            "A-B", "A-E", "B-C", "B-E", "B-F", "B-G", "C-D", "C-G", "D-G", "D-H", "E-F", "E-I", "E-J",
            "F-G", "F-J", "G-H", "G-J", "G-K", "G-L", "H-L", "I-J", "I-M", "J-K", "J-M", "J-N", "J-O",
            "K-L", "K-O", "L-O", "L-P", "M-N", "N-O", "O-P"
        };

        // 극대 매칭 계산
        Set<String> maximalMatching = findMaximalMatching(vertices, edges);

        // 결과 출력
        System.out.println(maximalMatching);
    }

    // 극대 매칭 계산
    private static Set<String> findMaximalMatching(String[] vertices, String[] edges) {
        Set<String> maximalMatching = new HashSet<>();
        Set<String> matchedVertices = new HashSet<>();

        for (String edge : edges) {
            String[] nodes = edge.split("-");
            String u = nodes[0];
            String v = nodes[1];

            // 두 정점 모두 매칭되지 않은 경우에만 매칭 추가
            if (!matchedVertices.contains(u) && !matchedVertices.contains(v)) {
                maximalMatching.add(edge);
                matchedVertices.add(u);
                matchedVertices.add(v);
            }
        }

        return maximalMatching;
    }
}
