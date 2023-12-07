public class ObjectExample {
    int x;
    float y;
    public ObjectExample(int val_x, float val_y)
    {
        this.x = val_x;
        this.y = val_y;
    }

    public static void main(String[] args) {
    ObjectExample myObj = new ObjectExample(8, 2.4f);
    System.out.println(myObj.x);
    System.out.println(myObj.y);
    }
}
