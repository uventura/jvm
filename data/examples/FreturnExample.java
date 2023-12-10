public class FreturnExample {
    public static void main(String[] args) {
        System.out.println(returnFloat(5));
    }

    public static float returnFloat(float a) {
        return a; // This triggers the freturn opcode
    }
}