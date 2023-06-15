import javax.swing.JButton;


interface IButton{
    public JButton get_button();
    public void hide_button();
    public void show_button();
}


public class Button implements IButton{
    protected JButton b;
    // constructor with bounds
    public Button(int b1, int b2, int b3, int b4, String name){
        this.b = new JButton(name);
        b.setBounds(b1, b2, b3, b4);
    }    

    public JButton get_button(){
        return this.b;
    }
    
    public void hide_button(){
        this.b.setVisible(false);
    }

    public void show_button(){
        this.b.setVisible(true);
    }
    
}