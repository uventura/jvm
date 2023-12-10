public class Store {
    public static void main(String[] args) {
        // Inicializando variáveis
        int num1 = 10;     // Pode gerar um opcode istore
        int num2 = 20;     // Pode gerar um opcode istore
        int index = 0;     // Pode gerar um opcode istore_0

        // Inicializando um array de short
        short[] shortArray = new short[5];

        // Executando uma operação e armazenando o resultado em uma variável
        int sum = num1 + num2; // Pode gerar um opcode istore

        // Armazenando um valor no array (conversão de int para short)
        shortArray[index] = (short)sum; // Pode gerar um opcode sastore
        int r = shortArray[index];

        // Exibindo o resultado
        System.out.println(r);
    }
}
