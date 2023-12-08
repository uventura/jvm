public class StaticUsage {
    public static int square(int number) {
        return number * number;
    }

    public static void main(String[] args) {
        int result = StaticUsage.square(5);
        System.out.println(result);
    }
}
