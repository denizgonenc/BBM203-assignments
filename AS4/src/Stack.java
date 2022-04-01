import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.Random;

public class Stack {
    private ArrayList<Integer> stack;
    FileWriter e;

    public Stack() throws IOException {
        stack = new ArrayList<>();
        String[] elements = ReadFromFile.readFile("stack.txt")[0].split(" ", 0);
        for (String element : elements) stack.add(Integer.parseInt(element));
        // Create output file
        File file = new File("stackOut.txt");
        file.createNewFile();
        e = new FileWriter("stackOut.txt");
    }

    public int top(){
        return stack.get(0);
    }

    public int pop(){
        int temp = stack.get(0);
        stack.remove(0);
        return temp;
    }

    public void push(int a){
        ArrayList<Integer> temp = new ArrayList<>();
        temp.add(a);
        temp.addAll(stack);
        stack = new ArrayList<>();
        stack.addAll(temp);
    }

    public void removeGreater(int k) throws IOException {
        ArrayList<Integer> temp = new ArrayList<>();
        while (!stack.isEmpty()){
            if (top() > k){
                pop();
            }
            else{
                temp.add(pop());
            }
        }
        stack = new ArrayList<>();
        stack.addAll(temp);
        updateFile(String.format("After removeGreater %d:\n%s", k, buildString()));
    }

    public int calculateDistance() throws IOException {
        ArrayList<Integer> temp = new ArrayList<>();
        int dist = 0;
        while (!stack.isEmpty()){
            for(int i = 1; i < stack.size(); i++){
                dist += Math.abs(stack.get(i) - top());
            }
            temp.add(pop());
        }
        stack = new ArrayList<>();
        stack.addAll(temp);
        updateFile(String.format("After calculateDistance:\nTotal distance=%d", dist));
        return dist;
    }

    public void addOrRemove(int k) throws IOException {
        int a = k;
        if (k < 0){
            while(k != 0){
                pop();
                k++;
            }
        }
        else if (k > 0){
            Random rand = new Random();
            while (k != 0){
                push(rand.nextInt(51));
                k--;
            }
        }
        updateFile(String.format("After addOrRemove %d:\n%s", a, buildString()));
    }

    public void reverse(int k) throws IOException {
        int a = k;
        ArrayList<Integer> temp = new ArrayList<>();
        while (k != 0){
            temp.add(pop());
            k--;
        }
        for(int i = 0; i < temp.size(); i++){
            push(temp.get(i));
        }
        updateFile(String.format("After reverse %d:\n%s", a, buildString()));
    }

    public void sortElements() throws IOException {
        stack.sort(Comparator.comparing(Integer::intValue));
        updateFile("After sortElements:\n" + buildString());
    }

    public int distinctElements() throws IOException {
        ArrayList<Integer> temp = new ArrayList<>();
        int count = 0;
        temp.addAll(stack);
        // Sort the list to compare easier
        stack.sort(Comparator.comparing(Integer::intValue));
        for (int i = 0; i < stack.size(); i++){
            if(i == 0 && stack.get(0) < stack.get(1)) count++;
            else if (i == stack.size()-1 && stack.get(i-1) < stack.get(i)) count++;
            else if (stack.get(i) < stack.get(i+1)) count++;
        }
        stack = new ArrayList<>();
        stack.addAll(temp);
        updateFile(String.format("After distinctElements:\nTotal distinct element=%d", count));
        return count;
    }

    public void updateFile(String line) throws IOException {
        e.write(line + "\n");
    }

    public void endFile() throws IOException {
        e.close();
    }

    public String buildString(){
        // Turn the arraylist into space separated integers
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < stack.size(); i++) {
            int num = stack.get(i);
            sb.append(num);
            if (i != stack.size()-1) sb.append(" ");
        }
        String result = sb.toString();
        return result;
    }
}
