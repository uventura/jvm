public class ConditionalZeroExample {
    public static void main(String[] args) {
        int intValue = 42;

        if (intValue == 0) {
            System.out.println("not ok");
        }
        System.out.println("ok");

        if (intValue != 0){
            System.out.println("not equal 0. ok");
        }
        System.out.println("ok");

        if(intValue > 0){
            System.out.println("greater than zero. ok");
        }

        if(intValue >= 0){
            System.out.println("greater of equal. ok");
        }

        if(intValue < 0){
            System.out.println("not ok");
        }

        if(intValue <= 0){
            System.out.println("not ok");
        }

        System.out.println("end of test!");
    }
}