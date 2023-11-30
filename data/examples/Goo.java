class Goo {
    static
    {
        System.out.println("5");
    }

    { System.out.println("6"); }
    Goo()
    {
        System.out.println("7");
    }
}
