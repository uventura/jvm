public class ConditionalExample {
    public static void main(String[] args)
    {
        int y = 5;

        if(3 > y){
            System.out.println("Not ok (3 is not greater than 8...)");
        }
        //System.out.println("passou do if_cmple...");

        if(3 < y){
            System.out.println("Ok (3<8)");
        }
        //System.out.println("passou do if_icmpge..."); // experimenta tirar isso aqui.

        if(3 == y){
            System.out.println("Not ok 3 is not equal to 8...");
        }
        //System.out.println("passou do if_icmpne...");

        if(3 >= y){
            System.out.println("Not ok 3 is not greater than or equal to 8...");
        }
        //System.out.println("passou do if_icmplt...");

        if(3 <= y){
            System.out.println("Ok (3<=8)");
        }
        //System.out.println("passou do if_icmpgt...");

        if(3 != y){
            System.out.println("Ok (3 != 8)");
        }
        //System.out.println("passou do if_icmpeq...");

    }
}
