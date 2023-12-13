 public class Fields2 {

      private static String str = "Default";

      public String getString() {
          return str;
      }

      public void setString(String s) {
          str = s;
      }

      public static void main(String[] args) {
            Fields2 obj = new Fields2();
            obj.setString("New Value");
            System.out.println(obj.getString());
      }
  }
