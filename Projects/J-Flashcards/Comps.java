import java.util.List;

import java.awt.Component;
import java.util.ArrayList;
import java.util.Arrays;
import javax.swing.JLabel;


// class containing static variables of components
public class Comps{
   // startup buttons, exit and menu:
   public static Button b_exit;
   public static Button b_menu;

   public static List<Button> s_buttons = new ArrayList<Button>();

   public static List<Component> admin_login = new ArrayList<Component>();
   public static List<Component> admin_panel = new ArrayList<Component>();

   public static List<Button_set.Game_button> game_panel = new ArrayList<Button_set.Game_button>();
   public static JLabel question_label;
   // boolean telling if already rendered admin, if admin is rendered,
   // then we have to only make components visible
   public static boolean admin_login_rendered = false;
   public static boolean admin_panel_rendered = false;
   public static boolean game_rendered = false; 

   public static Answers_set ans_set;

   public static List<Button_set.Choice_button> choice_buttons = new ArrayList<Button_set.Choice_button>();
   public static int which_correct;

   public static JLabel is_correct;
   public static Button next;
}