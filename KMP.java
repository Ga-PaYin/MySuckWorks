import java.awt.*;
import java.util.Scanner;

public class KMP {
    public static int[] makeNext(char[] parttern, int size) {
        int[] next = new int[size];
        next[0] = 0;
        int i = 1, j = 0;
        while (i < size && j < size) {
            if (parttern[j] == parttern[i]) {
                next[i] = j + 1;
                j++;
                i++;
            } else {
                if (j > 0) {
                    j = next[j - 1];
                } else {
                    next[i] = 0;
                    i++;
                }
            }
        }
        for (int t = 0; t < size; t++) {
            System.out.print(next[t]);
        }
        System.out.println("");
        return next;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("请输入主串");
        String TEXT = scanner.nextLine();
        System.out.print("请输入子串");
        String PARTTERN = scanner.nextLine();
        char[] text = TEXT.toCharArray();
        char[] parttern = PARTTERN.toCharArray();
        int[] next = makeNext(parttern, PARTTERN.length());
        int complited = 0;
        int i = 0, j = 0;
        boolean succeed = false;
        if (TEXT.length() >= PARTTERN.length()) {
            while (i < TEXT.length() && j < PARTTERN.length()) {
                if (text[i] == parttern[j]) {
                    i++;
                    j++;
                    complited++;
                } else {
                    if (j > 0) {
                        complited = next[j - 1];
                        j = next[j - 1];
                    } else {
                        complited = 0;
                        i++;
                    }
                }
                if (complited == PARTTERN.length()-1) {
                    if(succeed == false) {
                        System.out.println("匹配成功");
                        System.out.println("初始位置在第"+(i-j+1)+"位");
                    }else{
                        System.out.print("还有"+(i-j+1)+" ");
                    }
                    succeed = true;
                    System.out.println();
                    System.out.println(TEXT);
                    for(int t = 0; t < i-j; t++){
                        System.out.print(" ");
                    }
                    System.out.println(PARTTERN);
                    complited = 0;
                    j = 0;
                }
            }
            if (succeed == false) {
                System.out.println("匹配失败");
            }
        } else {
            System.out.println("子串长于主串，找不到");
        }
    }
}
