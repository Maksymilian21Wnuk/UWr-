import javax.swing.*;
import java.awt.Component;

public class Frame{
    JFrame frame;

    public Frame(){
        frame = new JFrame(Constants.WINDOW_NAME);
        frame.setSize(Constants.win_size[0], Constants.win_size[1]);
        // make window appear in the center of screen
        frame.setLocationRelativeTo(null);
        frame.setLayout(null);
        frame.setVisible(true);
    }

    public void Add_button(Button b){
        frame.add(b.get_button());
    }

    public void Add_comp(Button b){
        frame.add(b.get_button());
    }

    public void Add_comp(Component c){
        frame.add(c);
    }

    // weird but this works,
    // prevents from not showing half
    // of screen bug
    public void Refresh_screen(){
        frame.setSize(701, 600);
        frame.setSize(700, 600);
    }
    
}