import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.Random;

public class Queue {
    private ArrayList<Integer> queue;
    FileWriter f;

    public Queue() throws IOException {
        queue = new ArrayList<>();
        String[] elements = ReadFromFile.readFile("queue.txt")[0].split(" ", 0);
        for (String element : elements) queue.add(Integer.parseInt(element));
        // Create output file
        File file = new File("queueOut.txt");
        file.createNewFile();
        f = new FileWriter("queueOut.txt");
    }

    public void enqueue(int a){
        queue.add(a);
    }

    public int dequeue(){
        int temp = front();
        queue.remove(0);
        return temp;
    }

    public int front(){
        return queue.get(0);
    }

    public int rear(){
        return queue.get(queue.size()-1);
    }

    public void removeGreater(int k) throws IOException {
        ArrayList<Integer> temp = new ArrayList<>();
        while (!queue.isEmpty()){
            if (front() > k){
                dequeue();
            }
            else{
                temp.add(dequeue());
            }
        }
        queue = new ArrayList<>();
        queue.addAll(temp);
        updateFile(String.format("After removeGreater %d:\n%s", k, buildString()));
    }

    public int calculateDistance() throws IOException {
        ArrayList<Integer> temp = new ArrayList<>();
        int dist = 0;
        while (!queue.isEmpty()){
            for(int i = 1; i < queue.size(); i++){
                dist += Math.abs(queue.get(i) - front());
            }
            temp.add(dequeue());
        }
        queue = new ArrayList<>();
        queue.addAll(temp);
        updateFile(String.format("After calculateDistance:\nTotal distance=%d", dist));
        return dist;
    }

    public void addOrRemove(int k) throws IOException {
        int a = k;
        if (k < 0){
            while(k != 0){
                dequeue();
                k++;
            }
        }
        else if (k > 0){
            Random rand = new Random();
            while (k != 0){
                enqueue(rand.nextInt(51));
                k--;
            }
        }
        updateFile(String.format("After addOrRemove %d:\n%s", a, buildString()));
    }

    public void reverse(int k) throws IOException {
        ArrayList<Integer> temp = new ArrayList<>();
        int a = k;
        int b = k;
        while (k != 0){
            temp.add(queue.get(k-1));
            k--;
        }
        while (a != 0){
            dequeue();
            a--;
        }
        temp.addAll(queue);
        queue = new ArrayList<>();
        queue.addAll(temp);
        updateFile(String.format("After reverse %d:\n%s", b, buildString()));
    }

    public void sortElements() throws IOException {
        queue.sort(Comparator.comparing(Integer::intValue));
        updateFile("After sortElements:\n" + buildString());
    }

    public int distinctElements() throws IOException {
        ArrayList<Integer> temp = new ArrayList<>();
        int count = 0;
        temp.addAll(queue);
        // Sort the list to compare easier
        queue.sort(Comparator.comparing(Integer::intValue));
        for (int i = 0; i < queue.size(); i++){
            if(i == 0 && queue.get(0) < queue.get(1)) count++;
            else if (i == queue.size()-1 && queue.get(i-1) < queue.get(i)) count++;
            else if (queue.get(i) < queue.get(i+1)) count++;
        }
        queue = new ArrayList<>();
        queue.addAll(temp);
        updateFile(String.format("After distinctElements:\nTotal distinct element=%d", count));
        return count;
    }

    public void updateFile(String line) throws IOException {
        f.write(line + "\n");
    }

    public void endFile() throws IOException {
        f.close();
    }

    public String buildString(){
        // Turn the arraylist into space separated integers
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < queue.size(); i++) {
            int num = queue.get(i);
            sb.append(num);
            if (i != queue.size()-1) sb.append(" ");
        }
        String result = sb.toString();
        return result;
    }
}
