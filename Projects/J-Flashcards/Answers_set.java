import java.io.Console;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Random;
import java.nio.file.StandardOpenOption;

public class Answers_set{
    /* contains of strings of file which has questions and answers
     * 
     */
    private static List<String> ans_list;

    public Answers_set(){
        try{
            ans_list = Files.readAllLines(Paths.get(Constants.TXT_PATH));
            Comps.ans_set = this;
        }
        catch (IOException e){
            e.printStackTrace();
        }
    }

    // get random answer, we dont want them to repeat
    // to user!!
    public Answer Get_random_answer(){
        Random rand = new Random();
        // get random index
        int idx = rand.nextInt(this.Answer_count());
        // get string make answer and then remove, so we wont have repeating answer
        String s = ans_list.get(idx);

        ans_list.remove(idx);
        
        return new Answer(s);

    }

    public void Append_answer(String ans){
        ans_list.add(ans);
        try {
            Files.write(Paths.get(Constants.TXT_PATH), ans.getBytes(), StandardOpenOption.APPEND);
        }
        catch (IOException e){
            e.printStackTrace();
        }
    }

    public int Answer_count(){
        return ans_list.size();
    }

}