import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class a {
    public static void main(String[] args) {
        File file = new File("a.txt");
        try {
            file.createNewFile();
        } catch (IOException e) {
            System.out.println("An error ocurred.");
            e.printStackTrace();
        }
        for (int i = 0; i < 1000000; i++) {
            try {
                FileWriter file_writer = new FileWriter(file, true);
                file_writer.write("a");
                file_writer.close();
            } catch (IOException e) {
                System.out.println("An error occurred.");
                e.printStackTrace();
            }
        }
    }
}