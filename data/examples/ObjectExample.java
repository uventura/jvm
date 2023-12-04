public class ObjectExample {
    int x;
    public ObjectExample(int val_x)
    {
        this.x = val_x;
    }

    public static void main(String[] args) {
    ObjectExample myObj = new ObjectExample(8);
    System.out.println(myObj.x);
    }
}
