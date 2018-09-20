import javax.swing.*;
import java.awt.*;
import java.util.Random;


public class Huaji {
    public JLabel label;
    public int x,y,size,dx,dy,times,g;
    public Huaji(int size,int x,int y,int dx,int dy,int times){
        ImageIcon funny = new ImageIcon("C:\\Users\\10990\\Desktop\\coding\\Java编程\\ACloudArrow\\images\\Left.jpg");
        this.label = new JLabel();
        label.setSize(size,size);
        this.size = size;
        label.setVisible(true);
        this.g = 7;
        this.x = x;
        this.dx = dx;
        this.y = y;
        this.dy = dy;
        this.times = times;
        label.setLocation(this.x,this.y);

        Image temp = funny.getImage().getScaledInstance(label.getWidth(),label.getHeight(),funny.getImage().SCALE_DEFAULT);
        funny = new ImageIcon(temp);
        label.setIcon(funny);
    }
    public void move(JFrame window,int dy){

        this.dy += this.g;
        this.x += this.dx;
        this.y += this.dy;
        this.label.setLocation(this.x,this.y);
        if(this.x + this.size >= window.getWidth() || this.x <= 0){
            this.changeDirection();
            this.times++;
            this.dx = -(this.dx);
            if(this.x + this.size > window.getWidth()){
                this.x = window.getWidth() - size;
            }else if(this.x < 0){
                this.x = 0;
            }
        }
        if(this.y + this.size >= window.getHeight() || this.y <= 0){
            this.changeDirection();
            this.times++;
            this.dy = -(this.dy);
            if(this.y + this.size > window.getHeight()){
                this.y = window.getHeight() - size;
            }else if(this.y < 0){
                this.y = 0;
            }
        }
    }

    public void changeDirection(){
        ImageIcon funny;
        if(times % 2 == 0){
            funny = new ImageIcon("C:\\Users\\10990\\Desktop\\coding\\Java编程\\ACloudArrow\\images\\Right.jpg");
        }else{
            funny = new ImageIcon("C:\\Users\\10990\\Desktop\\coding\\Java编程\\ACloudArrow\\images\\Left.jpg");
        }
        Image temp = funny.getImage().getScaledInstance(label.getWidth(),label.getHeight(),funny.getImage().SCALE_DEFAULT);
        funny = new ImageIcon(temp);
        label.setIcon(funny);
    }

    public static void main(String args[]){
        JFrame window = new frame().window;
        int size = 200;
        int x = 0, y = 0;
        int times1 = 0, times2 = 0, times3 = 0;
//        Random random = new Random();
        int dx1 = 1, dy1 = 5;
        int dx2 = 2, dy2 = 10;
        int dx3 = 3, dy3 = 20;
        Huaji funny1 = new Huaji(size,x,y,dx1,dy1,times1);
        Huaji funny2 = new Huaji(size,x,y,dx2,dy2,times2);
        Huaji funny3 = new Huaji(size,x,y,dx3,dy3,times3);
        window.getContentPane().add(funny1.label);
        window.getContentPane().add(funny2.label);
        window.getContentPane().add(funny3.label);
        while(true){
            try {
                Thread.sleep(25);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            funny1.move(window,dy1);
            funny2.move(window,dy2);
            funny3.move(window,dy3);
        }
    }
}
