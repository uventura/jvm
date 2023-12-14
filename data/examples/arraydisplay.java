public class arraydisplay {
    public static void main(String args[]) {
        int[] vetor = { 5, 9, 7, 4, 6, 1, 2, 3, 10, -1, };
        print_array(vetor);
    }

    private static void print_array(int[] vetor)
	{
		int i = 0;
		int fim = 10;
		while(i < fim)
		{
			System.out.println(vetor[i]);
            i+=1;
		}
	}
}
