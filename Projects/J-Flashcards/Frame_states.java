import java.awt.Color;
import java.awt.Component;
import java.awt.Font;
import java.nio.file.Files;

import javax.swing.*;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

// states are methods that are called
// only to initialize the components of application
public class Frame_states {
    public static Frame main_frame;

    private void Show_exit(){
        Comps.b_exit.show_button();
    }
    
    private void Show_menu(){
        Comps.b_menu.show_button();
    }

    void Startup(Frame m_frame){
        main_frame = m_frame;
        
        Button exit = new Button_set().new Exit_button(520, 490, 150, 60);
        Comps.b_exit = exit;

        Button menu = new Button_set().new Menu_button();
        Comps.b_menu = menu;

        Button start = new Button_set().new Start_button(270, 200, 150, 50);
        Button admin = new Button_set().new Admin_button(270, 270, 150, 50);

        Button[] buttons = {exit, start, admin, menu};

        for (Button b : buttons){
            main_frame.Add_button(b);
            Comps.s_buttons.add(b);
        }

        menu.hide_button();
    }

    void Admin_password(){
        // pswd initialization with label
        JPasswordField p_field = new JPasswordField();
        JLabel l1 = new JLabel("Password: ");
        
        Button proceed = new Button_set().new Proceed_button(p_field);

        // some coords
        l1.setBounds(100, 100, 130, 100); 
        p_field.setBounds(300, 130, 150, 40);

        l1.setFont(new Font("Serif", Font.PLAIN, 20));

        // adding to main_frame
        main_frame.Add_comp(l1);
        main_frame.Add_comp(p_field);
        main_frame.Add_comp(Comps.b_menu);
        main_frame.Add_comp(proceed);

        // also add exit button

        // show and refresh        
        Show_exit();
        Show_menu();
        main_frame.Refresh_screen();

        // może niech Button implementuje add?? dobre 
        Comps.admin_login.add(proceed.get_button());
        Comps.admin_login.add(l1);
        Comps.admin_login.add(p_field);
        Comps.admin_login.add(Comps.b_menu.get_button());
        Comps.admin_login.add(Comps.b_exit.get_button());
        
        main_frame.Refresh_screen();
    }

    void Admin_panel(){
        Show_exit();
        Show_menu();

        // show labels 
        String[] texts = {
            "Question: ", "Answer 1: ", "Answer 2: ", "Answer 3: "
        };

        List<JTextField> t_fields = new ArrayList<JTextField>();

        // adding fields for writing text:
        for (int i = 0; i < 4; i++){
            JTextField t_field = new JTextField();
            JLabel l1 = new JLabel(texts[i]);

            l1.setBounds(100, 100 + (i * 50), 100, 30);
            t_field.setBounds(300,100 + (i * 50), 200,30);  
            main_frame.Add_comp(t_field);
            main_frame.Add_comp(l1);

            main_frame.Refresh_screen();

            Comps.admin_panel.add(t_field);
            Comps.admin_panel.add(l1);
            t_fields.add(t_field);
        }

        // adding buttons which indicate which answer is correct

        int y_cords[] = {110, 170, 230};
        for (int i = 0; i < 3; i++){
            Button bc = new Button_set().new Choice_button(550, y_cords[i]);
            Comps.admin_panel.add(bc.get_button());
            main_frame.Add_comp(bc);
            main_frame.Refresh_screen();
        }


        // adding done appending button
        Button done = new Button_set().new Done_button(t_fields);
        Comps.admin_panel.add(done.get_button());
        main_frame.Add_comp(done);
        main_frame.Refresh_screen();

    }

    // helpful function for rendering is_correct popup
    void Render_is_correct(){
        JLabel is_correct = new JLabel("Correct!");

        is_correct.setFont(new Font("Verdana", Font.PLAIN, 34));
        is_correct.setBounds(300, 150, 200, 200);
        main_frame.Refresh_screen();
        Comps.is_correct = is_correct;
        main_frame.Add_comp(is_correct);     
        is_correct.setVisible(false);

    }

    void Game(){

        // as usual, show exit menu and create new answer set
        Show_exit();
        Show_menu();
        Answers_set set = new Answers_set();
        Answer random_ans = set.Get_random_answer();
        
        // if rendered, do not make new buttons,
        // just change names of previous buttons
        if (Comps.game_rendered){
            Comps.next.show_button();
            int ans_idx = 0;
            // set texts of answer buttons
            for (Button_set.Game_button gb : Comps.game_panel){
                    gb.get_button().setText(random_ans.get_answer(ans_idx++));
                    gb.show_button();
                }
                // set text of question label
            Comps.question_label.setText(random_ans.get_question());
            Comps.question_label.setVisible(true);
            main_frame.Refresh_screen();
            }
                
        
        // case when not rendered
        else{
            Render_is_correct();

            Button next = new Button_set().new Next(400,400, set, main_frame);
            Comps.next = next;
            main_frame.Add_comp(next);

            JLabel question = new JLabel();
            Comps.question_label = question;

            question.setBounds(300, 50, 200, 200);
            question.setFont(new Font("Verdana", Font.PLAIN, 34));
            main_frame.Add_comp(question);
            question.setText(random_ans.get_question());

            Comps.game_rendered = true;

            for (int i = 0; i < 3; i++){
                Button_set.Game_button button_game = new Button_set().new Game_button(150 + 150 * i, 300, 
                                    random_ans.get_answer(i),
                                    random_ans.get_correct());
                Comps.game_panel.add(button_game);
                main_frame.Add_comp(button_game.get_button());
                main_frame.Refresh_screen();
            }

        }
    }   

}
