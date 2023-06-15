import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPasswordField;
import javax.swing.JTextField;

import java.awt.event.ActionListener;
import java.io.Console;
import java.sql.Time;
import java.awt.Choice;
import java.awt.Color;
import java.awt.Component;
import java.awt.event.ActionEvent;
import java.util.Arrays;
import java.util.List;
import java.util.concurrent.TimeUnit;


public class Button_set{

    class Exit_button extends Button implements ActionListener{
        public Exit_button(int b1, int b2, int b3, int b4){
            super(b1, b2, b3, b4, "Exit");
            this.get_button().addActionListener(this);

        }
        public void actionPerformed(ActionEvent e){
            System.exit(0);
        }
    }

    class Start_button extends Button implements ActionListener{
        public Start_button(int b1, int b2, int b3, int b4){
            super(b1, b2, b3, b4, "Start");
            this.get_button().addActionListener(this);

        }
        public void actionPerformed(ActionEvent e){
            for(Button b : Comps.s_buttons){
                b.hide_button();
            }
            

            new Frame_states().Game();
        }

    }

    class Admin_button extends Button implements ActionListener{
        public Admin_button(int b1, int b2, int b3, int b4){
            super(b1, b2, b3, b4, "Admin");
            this.get_button().addActionListener(this);

        }
        public void actionPerformed(ActionEvent e){
            for(Button b : Comps.s_buttons){
                b.hide_button();
            }
            // if admin rendered, just show buttons
            if (Comps.admin_login_rendered){
                for (Component c : Comps.admin_login){
                    c.setVisible(true);
                }
            }
            // else make new instances of buttons and make them visible
            else{
                Comps.admin_login_rendered = true;
                new Frame_states().Admin_password();
            }
        }

    }

    class Menu_button extends Button implements ActionListener{
        public Menu_button(){
            super(80, 480, 150, 50, "Menu");
            this.get_button().addActionListener(this);
        }

        public void actionPerformed(ActionEvent e){
            for (Component c : Comps.admin_login){
                c.setVisible(false);
            }

            for (Component c : Comps.admin_panel){
                c.setVisible(false);
            }

            for (Game_button c : Comps.game_panel){
                c.hide_button();
            }

            for (Button b : Comps.s_buttons){
                b.show_button();
            }
            Comps.is_correct.setVisible(false);
            Comps.next.hide_button();
            Comps.question_label.setVisible(false);

        }

    }

    class Proceed_button extends Button implements ActionListener{
        JPasswordField p_field;
        public Proceed_button(JPasswordField p_field){
            super(300, 500, 150, 50,"Proceed");
            this.get_button().addActionListener(this);
            this.p_field = p_field;
        }

        public void actionPerformed(ActionEvent e){
            if (Constants.paswd.equals(new String(p_field.getPassword()))){
                // set field to null, so that next login wont be having password
                p_field.setText(null);
                for (Component c : Comps.admin_login){
                    c.setVisible(false);
                }
                // go into new state, admin panel
                if (Comps.admin_panel_rendered){
                    for (Component c : Comps.admin_panel){
                        c.setVisible(true);
                    }
                }
                // render new state of frame, admin panel:
                else{
                    new Frame_states().Admin_panel();
                }
            }

            else{
                Frame_states.main_frame.Refresh_screen();

                JLabel error = new JLabel("Wrong password");
                error.setBounds(300, 50, 150, 50);
                error.setForeground(Color.RED);
                Frame_states.main_frame.Add_comp(error);

                Frame_states.main_frame.Refresh_screen();

                Comps.admin_login.add(error);
                
            }
        }
    }

    class Done_button extends Button implements ActionListener{
        List<JTextField> t_fields;

        public Done_button(List<JTextField> t_fields){
            super(400, 300, 100, 50,"Done");
            this.get_button().addActionListener(this);
            this.t_fields = t_fields;

        }

        public void actionPerformed(ActionEvent e){
            // get count of answers, create string 
            String ans = Integer.toString(Comps.ans_set.Answer_count() + 1) + " " + Comps.which_correct;
            String tmp;
            for (int i = 0; i < 4; i++){
                tmp = " " + this.t_fields.get(i).getText();
                ans += tmp;
            }
            // remove text from fields:
            for (int i = 0; i < 4; i++){
                this.t_fields.get(i).setText("");
            }

            for (Choice_button cb : Comps.choice_buttons){
                cb.get_button().setBackground(Color.red);
            }

            Comps.ans_set.Append_answer(ans + "\n");

        }

    }    

    // choice button, which answer is correct
    class Choice_button extends Button implements ActionListener{
        
        public Choice_button(int x, int y){
            super(x, y, 50, 50, "");
            this.get_button().addActionListener(this);
            this.get_button().setBackground(Color.red);
            Comps.choice_buttons.add(this);
        }


        public void actionPerformed(ActionEvent e){
            // b_num shows which one is green,
            // its used in order to parse to string to show
            // which action is correct
            int b_num = 1;
            for (Choice_button cb : Comps.choice_buttons){
                if (cb == this){
                    this.get_button().setBackground(Color.GREEN);
                    // make b_num's correct option as it is clicked button
                    Comps.which_correct = b_num;
                }
                else{
                    cb.get_button().setBackground(Color.red);
                }
                b_num += 1;
            }

            System.out.println(Comps.which_correct);

        }
    }

    // game button, its button with answer which player clicks
    class Game_button extends Button implements ActionListener{
        private String ans_correct;
        private String name;

        public Game_button(int x, int y, String name, String ans_correct){
            super(x, y, 130, 50, name);
            this.ans_correct = ans_correct;
            this.name = name;
            this.get_button().addActionListener(this);


        }

        public void set_new_ans(String ans){
            this.ans_correct = ans;
        }

        public void set_new_name(String name){
            this.name = name;
        }

        public void actionPerformed(ActionEvent e){
            // good answer
            if (this.name == this.ans_correct){
                Comps.is_correct.setText("Correct!");
                Comps.is_correct.setForeground(Color.green);
            }
            // bad answer
            else{
                Comps.is_correct.setText("Incorrect...");
                Comps.is_correct.setForeground(Color.red);
            }
            
            Comps.is_correct.setVisible(true);

        }
    }

    // next board
    class Next extends Button implements ActionListener{
        private Frame main_frame;
        public Answers_set set;

        public Next(int x, int y, Answers_set set, Frame main_frame){
            super(x, y, 130, 50, "Next");
            this.get_button().addActionListener(this);
            this.set = set;
            this.main_frame = main_frame;
        }

        public void actionPerformed(ActionEvent e){
            Comps.is_correct.setVisible(false);
            Answer random_ans = this.set.Get_random_answer();
            int ans_idx = 0;
            for (Game_button gb : Comps.game_panel){
                    gb.get_button().setText(random_ans.get_answer(ans_idx));
                    gb.set_new_ans(random_ans.get_correct());
                    gb.set_new_name(random_ans.get_answer(ans_idx++));
            }
            // set text of question label
            Comps.question_label.setText(random_ans.get_question());
            main_frame.Refresh_screen();    
        }        
    }
}