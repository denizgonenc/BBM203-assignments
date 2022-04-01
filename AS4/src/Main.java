import java.io.IOException;

public class Main {
    public static void main(String[] args) throws IOException {
        String[] lines = ReadFromFile.readFile(args[0]);
        // Create the objects
        Stack stack = new Stack();
        Queue queue = new Queue();
        for (String line : lines){
            String[] split = line.split(" ", 0);
            String type = split[0];
            // Choose which functions to use
            switch (split[1]){
                case "removeGreater":
                    if (type.equals("Q")) queue.removeGreater(Integer.parseInt(split[2]));
                    else if(type.equals("S")) stack.removeGreater(Integer.parseInt(split[2]));
                    break;
                case "calculateDistance":
                    if (type.equals("Q")) queue.calculateDistance();
                    else if(type.equals("S")) stack.calculateDistance();
                    break;
                case "addOrRemove":
                    if (type.equals("Q")) queue.addOrRemove(Integer.parseInt(split[2]));
                    else if (type.equals("S")) stack.addOrRemove(Integer.parseInt(split[2]));
                    break;
                case "reverse":
                    if(type.equals("Q")) queue.reverse(Integer.parseInt(split[2]));
                    else if (type.equals("S")) stack.reverse(Integer.parseInt(split[2]));
                    break;
                case "sortElements":
                    if (type.equals("Q")) queue.sortElements();
                    else if(type.equals("S")) stack.sortElements();
                    break;
                case "distinctElements":
                    if (type.equals("Q")) queue.distinctElements();
                    else if(type.equals("S")) stack.distinctElements();
                    break;
            }
        }
        // Close the output files
        stack.endFile();
        queue.endFile();
    }
}
