import java.util.ArrayList;
import java.util.Collections;
import java.util.List;


class OrderedList{
    
    List<Animals> animal_list;

    OrderedList(){
        animal_list = new ArrayList<Animals>();
    }

    void add_element(Animals a){
        animal_list.add(a);
        Collections.sort(animal_list);
    }

    Animals get_first(){
        if (animal_list.size() == 0){
            throw new Error("List empty\n");
        }
        return animal_list.get(0);
    }

}