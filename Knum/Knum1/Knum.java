import java.util.Arrays;

class Solution {
    public int[] solution(int[] array, int[][] commands) {
        
        int[] answer = new int[commands.length];

        for(int a = 0; a<commands.length;a++){
            
            int cnt = 0;

            int[] arr = new int[commands[a][1]-commands[a][0]+1];

			for (int b = commands[a][0] - 1; b < commands[a][1]; b++) {
				arr[cnt++] = array[b];
			}
			Arrays.sort(arr);

			answer[a] = arr[commands[a][2] - 1];
        }
        
        return answer;
    }
}

public class Knum {

	public static void main(String[] args) {
		int[] array = {1, 5, 2, 6, 3, 7, 4};
		int[][] commands = {{2, 5, 3}, {4, 4, 1}, {1, 7, 3}};
		Solution s = new Solution();
		int[] array1 = s.solution(array, commands);
		for(int sum : array1) {
			System.out.println(sum);
		}
	}

}
