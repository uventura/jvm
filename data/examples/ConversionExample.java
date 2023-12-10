
public class ConversionExample {
    public static int main(String[] args) {
        int intValue = 42;
        
        long longValue = (long) intValue;
        float floatValue = (float) longValue;
        double doubleValue = (double) floatValue;
        intValue = (int) doubleValue;
        
        return intValue;
    }
}