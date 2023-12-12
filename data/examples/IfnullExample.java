class Person {
    private String name;

    public String getName() {
        return name;
    }
}


class IfnullExample {

    public static void main(String[] args) {
        Person person = new Person();
        if(person == null){
            System.out.println("not okay");
        }else{
            System.out.println("okay");
        }
        
        if(person != null){
            System.out.println("okay");
        }else{
            System.out.println("not okay");
        }
        
    }
}