public class IfAcmpExample {
    public static void main(String[] args) {
        String str1 = "Hello";
        String str2 = "World";
        String str3 = "Hello";

        if (str1 == str2) {
            System.out.println("str1 and str2 point to the same object.");
        } else {
            System.out.println("str1 and str2 do not point to the same object.");
        }

        if (str1 == str3) {
            System.out.println("str1 and str3 point to the same object.");
        } else {
            System.out.println("str1 and str3 do not point to the same object.");
        }
    }
}