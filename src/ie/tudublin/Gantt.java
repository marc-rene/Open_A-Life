package ie.tudublin;

import processing.core.PApplet;
import processing.core.PFont;
import processing.data.*;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

import ie.tudublin.task;

public class Gantt extends PApplet
{	
	Table task_table = new Table();
	
	ArrayList<task> tasks = new ArrayList<task>();
	PFont font;

	


	/*class slider
	{
		static int row;
		private int start_x;
		private int start_y;
		
		public String name;
		public int start;
		public int end;

		slider()
		{
			row++;
		}


	}*/
	
	public void settings()
	{
		size(1000, 600);
	}

	public void loadTasks() throws FileNotFoundException
	{
		Scanner sc = new Scanner(new File("test.csv"));
        //sc.useDelimiter(",");


        while(sc.hasNextLine())
        {
			TableRow row = task_table.addRow();
			String this_row = sc.nextLine();
			String[] this_row_array = this_row.split(",");


			row.setString("task_name", this_row_array[0]);
			row.setInt("start_day", parseInt(this_row_array[1]));
			row.setInt("end_day", parseInt(this_row_array[2]));
			
			tasks.add(new task(row));
        }

        sc.close();
	}

	public void printTasks()
	{
		for (task t : tasks) {
			println(t.get_name() +" and starts "+ t.get_start_day() +" and ends "+ t.get_end_day());
			println("---------------------");
		}
	}
	
	public void mousePressed()
	{
		println("Mouse pressed");	
	}

	public void mouseDragged()
	{
		println("Mouse dragged");
	}

	
	
	public void setup() 
	{
		font = createFont("Arial", 10);
		textFont(font);

		task_table.addColumn("task_name", Table.STRING);
		task_table.addColumn("start_day", Table.INT);
		task_table.addColumn("end_day", Table.INT);
	}
	
	public void draw()
	{			
		background(0);

		int initial_offset_x = 100;
		
		//Draw our lines
		for(int i = 0; i < 30; i++)
		{
			int start_x = initial_offset_x + (30*i);
			int offset_y = 10;

			//Change line colour;
			if (i % 2 == 0)
			{ stroke(250); }
			else { 
				stroke(150); 
				offset_y = 25;
			}
			textAlign(CENTER, CENTER);
			text("Day " + (i+1), start_x, offset_y);

			line(start_x, 40, start_x, 500);
		}

		try {
			loadTasks();
		} 
		catch (FileNotFoundException e) {
			e.printStackTrace();
		}

		printTasks();
		

	}
}
