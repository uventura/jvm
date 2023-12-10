public class IreturnExample {
    public static void main(String[] args) {
        System.out.println(returnInteger(5));
    }

    public static int returnInteger(int a) {
        return a; // This triggers the ireturn opcode
    }
}