public class Foo extends Goo {
    static { System.out.println("1"); }
    {
        System.out.println("2");
    }

    public Foo() { System.out.println("3"); }
    public static void main(String[] args)
    {
        System.out.println("4");
        Foo f = new Foo();
    }
}
