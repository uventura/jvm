public class StaticAttributeExample {
    public static int x = 2;

    public static void main(String[] args)
    {
        StaticAttributeExample.x = 2;
        System.out.println(StaticAttributeExample.x);

        StaticAttributeExample.x = StaticAttributeExample.x * 4;
        System.out.println(StaticAttributeExample.x);
    }
}
