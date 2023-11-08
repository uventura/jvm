import java.util.Arrays;
/*
 *  author/twitter: @Lucaaslb
 */

/* 
  procedimento QuickSort(X[], IniVet, FimVet)
  var
     i, j, pivo, aux
  início
     i <- IniVet
     j <- FimVet
     pivo <- X[(IniVet + FimVet) div 2]
        enquanto(i < j)
         |      enquanto (X[i] < pivo) faça
         |        |   i <- i + 1
         |      fimEnquanto
         |      enquanto (X[j] > pivo) faça
         |        |   j <- j - 1
         |      fimEnquanto
         |      se (i <= j) então
         |        |  aux  <- X[i]
         |        |   X[i] <- X[j]
         |        |   X[j] <- aux
         |        |   i <- i + 1
         |        |   j <- j - 1
         |      fimSe
         fimEnquanto
         se (j > IniVet) então
            |   QuickSort(X, IniVet, j)
         fimSe
         se (i < FimVet) então
         |  QuickSort(X, i, FimVet)
         fimse
  fimprocedimento
 */

public class QuickSort {

	public static void main(String[] args) {
		// TODO Auto-generated method stub

		int[] vetor = { 5, 9, 7, 4, 6, 1, 2, 3, 10, -1, };

		System.out.println(Arrays.toString(vetor));
		quickSort(vetor, 0, vetor.length - 1);
		System.out.println(Arrays.toString(vetor));

	}

	private static void quickSort(int[] vetor, int inicio, int fim) {
		if (inicio < fim) {
			int posicaoPivo = separar(vetor, inicio, fim);
			quickSort(vetor, inicio, posicaoPivo - 1);
			quickSort(vetor, posicaoPivo + 1, fim);

		}
	}

	private static int separar(int[] vetor, int inicio, int fim) {
		int pivo = vetor[inicio];
		int i = inicio + 1;
		while (i <= fim) {
			if (vetor[i] <= pivo)
				i++;
			else if (pivo < vetor[fim])
				fim--;
			else {
				int troca = vetor[i];
				vetor[i] = vetor[fim];
				vetor[fim] = troca;
				i++;
				fim--;
			}
		}
		vetor[inicio] = vetor[fim];
		vetor[fim] = pivo;
		return fim;
	}
	

}
