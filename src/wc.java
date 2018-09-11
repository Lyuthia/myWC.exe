import java.io.*;
import java.util.*;

public class wc {

    /* * 根据命令 执行操作 * */
    private static void operation(int len,int start,String[] arr,String fileName) throws IOException
    {
        for(int i=start;i<len-1;i++) {
            switch (arr[i]) {
                //指定文件下字符数、单词数、行数、特殊行数：-c -w -l -a F:\wc1c.cpp
                case "-c":case "-w":case "-l":case "-a":
                    //System.out.println(fileName);
                    //System.out.println(arr[i]);
                    searchByFileName(fileName,arr[i]);break;
                default:
                    System.out.println("指令输入错误!");
                    break;
            }
        }
    }

    /* * 字符数 * */
    private static void countChar(BufferedReader fileContent) throws IOException
    {
        int c = 0;//字符数
        String lineContent = null;
        while ((lineContent = fileContent.readLine()) != null)
        {
            lineContent=lineContent.trim();
            //System.out.println(lineContent);
            for(int i=0;i<lineContent.length();i++) {
                char a = lineContent.charAt(i);
                if(a!=' '&&a!='\n'&&a!='\t'&&a!=','&&a!='.'&&a!='!'&&a!=';'&&a!='=')
                    c++;
            }
        }
        System.out.println("字符数：" + c);
    }

    /* * 词的数目 * */
    private static void countWords(BufferedReader fileContent) throws IOException
    {
        int w = 0;//词数
        String lineContent = null;
        while ((lineContent = fileContent.readLine()) != null)
        {
            lineContent=lineContent.trim();
            //System.out.println(lineContent);
            if(!lineContent.matches("^ *$"))
                w+=lineContent.replaceAll(" +"," ").split(" ").length;
        }
        System.out.println("词数：" + w);
    }

    /* * 行的数目 * */
    private static void countLines(BufferedReader fileContent) throws IOException
    {
        int l = 0;//行数
        String lineContent = null;
        while ((lineContent = fileContent.readLine()) != null)
        {
            lineContent=lineContent.trim();
            //System.out.println(lineContent);
            l++;
        }
        System.out.println("行数：" + l);
    }

    /* * 特殊行的数目：代码行数、空行数、注释行数 * */
    private static void countSpecialRows(BufferedReader fileContent) throws IOException
    {
        int blankLine = 0;//空行数
        int codeLine = 0;//代码行数
        int annotatedLine = 0;//注释行数
        Boolean comment = false;

        String lineContent = null;

        while ((lineContent = fileContent.readLine()) != null)
        {
            lineContent=lineContent.trim();
            //System.out.println(lineContent);

            if (lineContent.matches("^[\\s&&[^\\n]]*$")||lineContent.length()==1) {
                blankLine++;
            } else if (lineContent.startsWith("/*") && !lineContent.endsWith("*/")) {
                annotatedLine++;
                comment = true;
            } else if (comment.equals(true)) {
                annotatedLine++;
                if (lineContent.endsWith("*/")) {
                    comment = false;
                }
            } else if (lineContent.startsWith("//")) {
                annotatedLine++;
            } else {
                codeLine++;
            }
        }
        //System.out.println("代码行数：" + codeLine + " 空行数：" + blankLine + " 注释行数：" + annotatedLine);
        System.out.println( codeLine + " / " + blankLine + " / " + annotatedLine);
    }

    /* * 查找指定文件 * */
    private static void searchByFileName(String fileName,String command) throws IOException
    {
        try {
            File file = new File(fileName);
            if (file.isFile() && file.exists()) {
                //从文件地址中读取内容到程序中
                String encoding = "GBK";
                InputStreamReader read = new InputStreamReader(new FileInputStream(file), encoding);
                BufferedReader fileContent = new BufferedReader(read);

                switch (command) {
                    case "-c"://字符数
                        countChar(fileContent);break;
                    case "-w"://单词数
                        countWords(fileContent);break;
                    case "-l"://行数
                        countLines(fileContent);break;
                    case "-a"://特殊行数
                        countSpecialRows(fileContent);break;
                    default:
                        System.out.println("\n********  指令输入错误  **********");break;
                }

                read.close();
            } else {
                System.out.println("找不到指定的文件！");
            }
        } catch (Exception e) {
            System.out.println("读取文件内容操作出错");
            e.printStackTrace();
        }
    }

    /* * 递归 获取 指定目录下 指定后缀 的 文件 * */
    private static void searchFile(String[] arr) throws IOException
    {
        //String fileDir = arr[arr.length-1];
        //String fileFilter = ".cpp";
        String fileDir = arr[arr.length-2];
        String fileFilter = arr[arr.length-1];

        List<File> fileList = new ArrayList<File>();
        File file = new File(fileDir);// 指定查找目录
        File[] files = file.listFiles();// 获取目录下的所有文件或文件夹
        if (files == null) {// 如果目录为空，直接退出
            return;
        }
        // 遍历files中的所有文件
        for (File f : files) {
            if (f.isFile()&&f.getName().endsWith(fileFilter)) {
                fileList.add(f);
                //System.out.println(f.getName());
            } else if (f.isDirectory()) {
                //System.out.println(f.getAbsolutePath());
                searchFile(arr);
            }
        }
        //-s -c -w -l -a F:\\test .cpp
        for (File f1 : fileList) {
            //operation(arr.length,1,arr,f1.getAbsolutePath());
            operation(arr.length-1,1,arr,f1.getAbsolutePath());
            //System.out.println(f1.getAbsolutePath());
        }
    }

    public static void main(String[] args) throws IOException
    {
        //System.out.println("操作：" + args[0] + " " + args[1]);
        //searchFile("F:\\test",".cpp");

        // 获取输入指令
        System.out.print("Please enter the command：");
        Scanner command = new Scanner(System.in);
        String arr[]= command.nextLine().split("\\s");

        /* * 根据命令 执行操作 * */
        int len = arr.length;
        //-s -c -w -l -a F:\\test .cpp
        if(arr[0].equals("-s")) searchFile(arr);
        //-c -w -l -a F:\wc1c.cpp
        else operation(len,0,arr,arr[arr.length-1]);
    }
}
