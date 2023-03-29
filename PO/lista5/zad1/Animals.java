

public interface Animals extends Comparable<Animals>{
    int get_size();
    
    @Override
    default int compareTo(Animals o) {
        throw new UnsupportedOperationException("Unimplemented method 'compareTo'");
    }
}

class Ant implements Animals{
    @Override
    public int get_size(){
        return 0;
    }
    @Override
    public int compareTo(Animals o){
        return Integer.compare(this.get_size(), o.get_size());
    }
}

class Cat implements Animals{
    @Override
    public int get_size(){
        return 10;
    }
    @Override
    public int compareTo(Animals o){
        return Integer.compare(this.get_size(), o.get_size());
    }
}

class Wolf implements Animals{
    @Override
    public int get_size(){
        return 20;
    }
    @Override
    public int compareTo(Animals o){
        return Integer.compare(this.get_size(), o.get_size());
    }
}

class Elephant implements Animals{
    @Override
    public int get_size(){
        return 30;
    }
    @Override
    public int compareTo(Animals o){
        return Integer.compare(this.get_size(), o.get_size());
    }
}


