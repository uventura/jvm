import java.util.Scanner;

/**
 * Classe utilizada para demonstrar o uso da palavra chave throws,
 * deixando para quem chamar o método tratar alguma possivel exceção.
 */
public class ExemploThrows {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    try {
      ExemploThrows et = new ExemploThrows();

      System.out.print("Digite o valor do dividendo: ");
      double dividendo = s.nextDouble();

      System.out.print("Digite o valor do divisor: ");
      double divisor = s.nextDouble();

      double resultado = et.dividir(dividendo, divisor);

      System.out.println("O resultado da divisao eh: " + resultado);
    } catch (Exception ex) {
      System.out.println(ex.getMessage());
    }
  }

  public double dividir(double dividendo, double divisor) throws Exception {
    if(divisor == 0) {
      throw new Exception("Nao e permitido fazer uma divisao por zero!");
    }

    return dividendo / divisor;
  }
}
