public class TableSwitch {
    public static void main(String args[]) {
      int a = 1;
      
      switch (a) {
        case 0:
            a = 1;
            break;
        case 1:
            a = 3;
            break;
        case 2:
            a = 5;
            break;
        default:
            a = 7;
      }
    }
}