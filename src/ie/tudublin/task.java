package ie.tudublin;


import processing.data.TableRow;

public class task 
{
    private String task_name;
    private int start_day;
    private int end_day;

    public task(String name, int start, int end)
    {
        this.task_name = name;
        this.start_day = start;
        this.end_day = end;
    }

    public task (TableRow row)
    {
        this.task_name = row.getString("task_name");
        this.start_day = row.getInt("start_day");
        this.end_day = row.getInt("end_day");
    }

    public String get_name()
    {
        return this.task_name;
    }
    public void set_name(String name)
    {
        this.task_name = name;
    }

    public int get_start_day()
    {
        return this.start_day;
    }
    public void set_start_day(int start)
    {
        this.start_day = start;
    }

    public int get_end_day()
    {
        return this.end_day;
    }
    public void set_end_day(int end)
    {
        this.end_day = end;
    }
}
