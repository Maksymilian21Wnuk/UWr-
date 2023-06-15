import javax.swing.*;


// just initialize answer set and startup frame state
public class Program {
    public static void main(String[] s){
        // initialize answers
        new Answers_set();
        Frame m_frame = new Frame();
        // on start, the state is only startup
        new Frame_states().Startup(m_frame);


    }
}
