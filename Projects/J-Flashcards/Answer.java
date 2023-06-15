


public class Answer{
    private int correct_num;
    private String question;
    private String[] answers = {"", "", ""};

    // split answer and parse it 
    public Answer(String a){
        String[] splitted = a.split(" ");
        
        this.correct_num = Integer.parseInt(splitted[1]);
        this.question = splitted[2];
        for (int i = 0; i < 3; i++){
            answers[i] = splitted[i + 3];
        }
    }
    // get question
    public String get_question(){
        return question;
    }

    public String get_answer(int which){
        return answers[which];
    }
    // return correct answer
    public String get_correct(){
        return answers[correct_num - 1];
    }


}