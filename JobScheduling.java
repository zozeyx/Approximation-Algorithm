public class JobScheduling {

    // 작업 시간 배열
    public static int[] operationTime = {5, 2, 4, 3, 4, 7, 9, 2, 4, 1};
    
    // m은 기계의 수
    public static int m = 4;
    
    public static void main(String[] args) {
        int n = operationTime.length;  // 작업의 개수
        int[] L = new int[m];  // 각 기계의 마지막 작업 종료 시간을 저장하는 배열
        int[][] machineSchedules = new int[m][n];  // 각 기계의 작업 시간을 기록하기 위한 2D 배열

        // 기계에 작업 배정 초기화 (기계들은 처음에 모두 0 시간부터 시작)
        for (int j = 0; j < m; j++) {
            L[j] = 0;
        }

        // 각 작업을 기계에 배정
        for (int i = 0; i < n; i++) {
            int minMachine = 0; // 가장 일찍 끝나는 기계의 인덱스
            // 가장 일찍 끝나는 기계 찾기
            for (int j = 1; j < m; j++) {
                if (L[j] < L[minMachine]) {
                    minMachine = j;
                }
            }

            // 선택된 기계에 작업을 배정
            L[minMachine] += operationTime[i];
            machineSchedules[minMachine][i] = L[minMachine];  // 작업이 끝난 시간 기록
        }

        // 최대 시간 구하기 (기계마다 작업이 끝나는 최대 시간)
        int maxTime = 0;
        for (int j = 0; j < m; j++) {
            if (L[j] > maxTime) {
                maxTime = L[j];
            }
        }

        // 시간대별로 각 기계에서 수행된 작업을 출력
        System.out.print("시간대   ");
        for (int time = 0; time <= maxTime; time++) {
            System.out.print(time + "   ");
        }
        System.out.println();

        // 각 기계의 작업 출력
        for (int j = 0; j < m; j++) {
            System.out.print("m" + (j + 1) + "      ");
            for (int time = 0; time <= maxTime; time++) {
                boolean printed = false;
                for (int i = 0; i < n; i++) {
                    if (machineSchedules[j][i] == time) {
                        System.out.print("t" + (i + 1) + " ");
                        printed = true;
                        break;  // 한 기계에 한 번만 출력하도록 처리
                    }
                }
                if (!printed) {
                    System.out.print("    ");  // 해당 시간에 작업이 없으면 공백
                }
            }
            System.out.println();
        }
    }
}
