package ie.tudublin;

import java.util.Scanner;
import java.io.File;
import java.util.ArrayList;
import processing.core.*;

public class Main {

    public void gant() {
    }
    
    public static void main(String[] arg) throws Exception{
        String[] a = { "MAIN" };
        processing.core.PApplet.runSketch(a, new Gantt());
        
        ArrayList<String> rows = new ArrayList<String>();
        
        Scanner sc = new Scanner(new File("test.csv"));
        sc.useDelimiter(",");

        while(sc.hasNext())
        {
            rows.add(sc.nextLine());
        }

        for (String string : rows) {
            System.out.println(string);
        }

        sc.close();
    }
}