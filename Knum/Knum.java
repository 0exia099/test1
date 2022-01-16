import java.util.Arrays;

class Solution {
    public int[] solution(int[] array, int[][] commands) {
        
        int[] answer = new int[commands.length];
        int i = 0;
        int j = 0;
        int k = 0;
        for(int a = 0; a<commands.length;a++){
            
            int cnt = 0;
            i = commands[a][0];
            j = commands[a][1];
            k = commands[a][2];
            int[] arr = new int[j-i+1];
			if (j-1 < array.length) {
				for (int b = i - 1; b < j; b++) {
					arr[cnt++] = array[b];
				}
				Arrays.sort(arr);
				
				answer[a] = arr[k - 1];
			}
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
