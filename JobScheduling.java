import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class JobScheduling {

    // Approx_JobScheduling 알고리즘 구현
    public static int approximateJobScheduling(int m, int[] operation_time) {
        int n = operation_time.length;  // 작업의 개수
        int[] L = new int[m];  // 각 기계에 배정된 마지막 작업 종료 시간을 나타내는 배열
        List<List<Integer>> machines = new ArrayList<>();  // 각 기계에서 실행된 작업들을 추적하는 리스트 배열
        
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
            machines.get(minMachine).add(startTime);  // 작업의 시작 시간을 해당 기계의 작업 리스트에 추가
        }

        // 전체 시간표를 보여주는 출력 (시간 0부터 12까지)
        System.out.println("전체 시간표:");
        for (int i = 0; i < m; i++) {
            System.out.print("기계 M" + (i + 1) + ": ");
            int[] timeSlot = new int[13]; // 0부터 12까지 시간 슬롯 (13개)
            Arrays.fill(timeSlot, -1); // 초기값 -1로 설정 (작업이 없음을 표시)

            // 기계에서 실행된 각 작업의 시작 시간을 시간 슬롯에 배치
            for (int j = 0; j < machines.get(i).size(); j++) {
                int startTime = machines.get(i).get(j);
                int taskId = j + 1;  // 작업 번호 (t1, t2, ...)
                timeSlot[startTime] = taskId;  // 작업 번호를 해당 시작 시간에 배치
            }

            // 시간 슬롯을 출력
            for (int time = 0; time < 13; time++) {
                if (timeSlot[time] != -1) {
                    System.out.print("t" + timeSlot[time] + " (" + time + "시) ");
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
