import javax.swing.*;
import java.awt.*;

public class GUI {
    JFrame window = new JFrame("English <-> MorseCode Transformer");
    JTextArea Morse = new JTextArea("input english sentence here,the morse code will show on the right");
    JTextArea ENG = new JTextArea("input the morse code here,the english sentence will show on the left");
    JButton etom = new JButton("ENG -> morse");
    JButton mtoe = new JButton("morse -> ENG");
    public GUI(){
        this.window.setSize(1300,650);
        this.window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.window.getContentPane().setBackground(Color.CYAN);
        this.window.setLayout(null);
        this.window.setResizable(true);
        this.window.setVisible(true);

        int tranwid = 200;
        int tranhei = 50;

        int engx = 5;
        int engwid = this.window.getWidth()/2 - engx * 2;
        int engy = 10;
        int enghei = this.window.getHeight() - engy * 3 - tranhei;
        this.ENG.setBounds(engx,engy,engwid,enghei);

        int morx = engx * 3 + engwid;
        int morwid = engwid;
        int mory = engy;
        int morhei = enghei;
        this.Morse.setBounds(morx,mory,morwid,morhei);

        int etomx = engx + engwid - tranwid;
        int etomy = engy * 2 + enghei;
        this.etom.setBounds(etomx,etomy,tranwid,tranhei);

        int mtoex = morx;
        int mtoey = etomy;
        this.mtoe.setBounds(mtoex,mtoey,tranwid,tranhei);

        this.ENG.setVisible(true);
        this.Morse.setVisible(true);
        this.ENG.setLineWrap(true);
        this.Morse.setLineWrap(true);

        this.window.getContentPane().add(this.ENG);
        this.window.getContentPane().add(this.Morse);
        this.window.getContentPane().add(this.mtoe);
        this.window.getContentPane().add(this.etom);

    }
}
