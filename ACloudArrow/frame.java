import javax.swing.*;
import java.awt.*;

public class frame {
    JFrame window;
    private int width;

    public frame(){

        this.window = new JFrame("一支穿云箭,万千滑稽来相见");
        this.window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.window.setResizable(true);
//        this.window.setUndecorated(true);
//        this.window.setBackground(new Color(0,0,0,0));
//        Toolkit kit = Toolkit.getDefaultToolkit();
//        Dimension screenSize = kit.getScreenSize();
//        this.window.setSize(screenSize);hua

        this.window.getContentPane().setBackground(Color.white);


        this.window.setExtendedState(JFrame.MAXIMIZED_BOTH);
        this.window.setLayout(null);
        this.window.setVisible(true);

    }

}
