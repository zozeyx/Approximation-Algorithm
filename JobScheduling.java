import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class JobScheduling {

    // Approx_JobScheduling 알고리즘 구현
    public static int approximateJobScheduling(int m, int[] operation_time) {
        int n = operation_time.length;  // 작업의 개수
        int[] L = new int[m];  // 각 기계에 배정된 마지막 작업 종료 시간을 나타내는 배열
        List<List<String>> machines = new ArrayList<>();  // 각 기계에서 실행된 작업들을 추적하는 리스트 배열
        
        // 각 기계에 대해 작업 리스트 초기화
        for (int i = 0; i < m; i++) {
            machines.add(new ArrayList<>());  // 각 기계마다 새로운 리스트를 추가
        }

        // 각 작업에 대해 처리
        for (int i = 0; i < n; i++) {
            int minMachine = 0;  // 가장 빨리 종료되는 기계를 찾기 위한 변수

            // 가장 일찍 끝나는 기계 찾기
            for (int j = 1; j < m; j++) {
                if (L[j] < L[minMachine]) {
                    minMachine = j;
                }
            }

            // 작업 i를 가장 빨리 끝나는 기계에 할당
            int startTime = L[minMachine];  // 해당 기계의 작업 시작 시간
            L[minMachine] += operation_time[i]; // 해당 기계의 종료 시간 갱신
            machines.get(minMachine).add("t" + (i + 1) + "(" + startTime + "시)");  // 작업 이름(t1, t2, ...)과 시작 시간을 추가
        }

        // 시간대 0부터 12까지 표시
        System.out.println("시간대 0  1  2  3  4  5  6  7  8  9  10  11  12");

        // 각 기계별 작업 배치 결과 출력
        for (int i = m - 1; i >= 0; i--) {  // m4, m3, m2, m1 순으로 출력
            System.out.print("m" + (i + 1) + " ");
            int[] timeSlot = new int[13]; // 0부터 12까지 시간 슬롯 (13개)
            Arrays.fill(timeSlot, -1); // 초기값 -1로 설정 (작업이 없음을 표시)

            // 기계에서 실행된 각 작업의 시작 시간을 시간 슬롯에 배치
            for (String task : machines.get(i)) {
                int startTime = Integer.parseInt(task.substring(task.indexOf('(') + 1, task.indexOf('시')));
                int taskId = Integer.parseInt(task.substring(1, task.indexOf('('))) - 1;  // 작업 번호(t1, t2, t3 ...) 추출
                timeSlot[startTime] = taskId + 1;  // 작업 번호를 해당 시작 시간에 배치
            }

            // 시간 슬롯을 출력
            for (int time = 0; time < 13; time++) {
                if (timeSlot[time] != -1) {
                    System.out.print("t" + timeSlot[time] + " ");
                } else {
                    System.out.print("    ");  // 해당 시간대에 작업이 없으면 공백 출력
                }
            }
            System.out.println();
        }

        // 가장 늦은 종료 시간 반환
        int maxEndTime = 0;
        for (int time : L) {
            maxEndTime = Math.max(maxEndTime, time);
        }

        return maxEndTime;
    }

    public static void main(String[] args) {
        // 주어진 입력 값
        int m = 4;  // 기계의 수
        int[] operation_time = {5, 2, 4, 3, 4, 7, 9, 2, 4, 1};  // 각 작업의 수행 시간

        // Job Scheduling 실행
        int result = approximateJobScheduling(m, operation_time);

        // 결과 출력
        System.out.println("모든 작업이 종료된 시간: " + result);
    }
}
