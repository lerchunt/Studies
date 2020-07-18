public enum Famille {

    Baton("Baton"), Or("Or"), Epee("Epee"), Coupe("Coupe");
    private String name ="";
    
    Famille(String name){
        this .name=name;
    }
    
    public String toString(){
        return name;
    }
    
}
