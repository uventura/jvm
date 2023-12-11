public class IntConversionExample {
    public static void main(String[] args) {
        int intValue = 'a';

        short shortValue = (short) intValue;
        char charValue = (char) intValue;
        byte byteValue = (byte) intValue;

        System.out.println(shortValue);
        System.out.println(charValue);
        System.out.println(byteValue);
        return;
    }
}
