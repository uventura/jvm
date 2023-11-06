interface Soma{
    void getSoma(int a, int b);
}

class Matematico implements Soma{
    public void getSoma(int a, int b){
        System.out.println("Soma: " + (a+b));
    }
}

class Matematico_somando {
  public static void main(String[] args) {
    Matematico m1 = new Matematico();
    m1.getSoma(4,5);
  }
}