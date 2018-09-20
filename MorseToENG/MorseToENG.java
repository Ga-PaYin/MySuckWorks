import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;

public class MorseToENG {
    HashMap<Character,String> etm = new HashMap<>();
    HashMap<String,Character> mte = new HashMap<>();

    public MorseToENG(){
        this.etm.put('A',".-");
        this.etm.put('B',"-...");
        this.etm.put('C',"-.-.");
        this.etm.put('D',"-..");
        this.etm.put('E',".");
        this.etm.put('F',"..-.");
        this.etm.put('G',"--.");
        this.etm.put('H',"....");
        this.etm.put('I',"..");
        this.etm.put('J',".---");
        this.etm.put('K',"-.-");
        this.etm.put('L',".-..");
        this.etm.put('M',"--");
        this.etm.put('N',"-.");
        this.etm.put('O',"---");
        this.etm.put('P',".--.");
        this.etm.put('Q',"--.-");
        this.etm.put('R',".-.");
        this.etm.put('S',"...");
        this.etm.put('T',"-");
        this.etm.put('U',"..-");
        this.etm.put('V',"...-");
        this.etm.put('W',".--");
        this.etm.put('X',"-..-");
        this.etm.put('Y',"-.--");
        this.etm.put('Z',"--..");

        this.etm.put('0',"-----");
        this.etm.put('1',".----");
        this.etm.put('2',"..---");
        this.etm.put('3',"...--");
        this.etm.put('4',"....-");
        this.etm.put('5',".....");
        this.etm.put('6',"-....");
        this.etm.put('7',"--...");
        this.etm.put('8',"---..");
        this.etm.put('9',"----.");

        this.etm.put('.',".-.-.-");
        this.etm.put(',',"--..--");
        this.etm.put('?',"..--..");
        this.etm.put('!',"..--.");
        this.etm.put(':',"---...");
        this.etm.put('"',".-..-.");
        this.etm.put('\'',".----.");
        this.etm.put(' ',"-....-");

        for (char i = 'A'; i <= 'Z'; i++) {
            this.mte.put(this.etm.get(i), i);
        }
        for (char i = '0'; i <= '9'; i++) {
            this.mte.put(this.etm.get(i), i);
        }
        this.mte.put(this.etm.get('.'), '.');
        this.mte.put(this.etm.get(','), ',');
        this.mte.put(this.etm.get('?'), '?');
        this.mte.put(this.etm.get('!'), '!');
        this.mte.put(this.etm.get(':'), ':');
        this.mte.put(this.etm.get('"'), '"');
        this.mte.put(this.etm.get('\''), '\'');
        this.mte.put(this.etm.get(' '),' ');

    }

    public static String EToM(String sentence,MorseToENG engtomorse) {
        String[] words = sentence.split(" ");
        String result = "";
        int i = 0;
        for (String word : words) {
            if (i < words.length) {
                word = word.toUpperCase();
                char[] alpha = word.toCharArray();
                for (Character Alpha : alpha) {
                    result += engtomorse.etm.get(Alpha) + "/";
                }
                result += engtomorse.etm.get(' ') + "/";
                i++;
            } else {
                word = word.toUpperCase();
                char[] alpha_ = word.toCharArray();
                for (Character Alpha : alpha_) {
                    result += engtomorse.etm.get(Alpha);
                }
            }
        }
        return result;
    }

    public static String MToE(String sentence, MorseToENG engtomorse){
        String []alpha = sentence.split("/");
        String result ="";
        for(String Alpha : alpha){
            result += engtomorse.mte.get(Alpha);
        }
        return result;
    }

    public static void main(String []args){
        GUI gui = new GUI();
        MorseToENG engtomorse = new MorseToENG();

        gui.etom.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String sentence = gui.ENG.getText();
                gui.Morse.setText(EToM(sentence,engtomorse));
            }
        });

        gui.mtoe.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String sentence = gui.Morse.getText();
                gui.ENG.setText(MToE(sentence,engtomorse));
            }
        });
    }
}
