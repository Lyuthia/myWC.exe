<!--# myWC.exe
源程序特征统计程序-->

# WC个人项目博客 #
 
#### [github项目传送门：https://github.com/Lyuthia/myWC.exe.git](https://github.com/Lyuthia/myWC.exe.git "https://github.com/Lyuthia/myWC.exe.git") ####

## 一、项目相关要求 ##
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
wc.exe 是一个常见的工具，它能统计文本文件的字符数、单词数和行数。这个项目要求写一个命令行程序，模仿已有wc.exe 的功能，并加以扩充，给出某程序设计语言源文件的字符数、单词数和行数。

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
实现一个统计程序，它能正确统计程序文件中的字符数、单词数、行数，以及还具备其他扩展功能，并能够快速地处理多个文件。

#### 具体功能要求： ####

程序处理用户需求的模式为：

wc.exe [parameter] [file_name]

#### 基本功能列表： ####
- wc.exe -c file.c     //返回文件 file.c 的字符数
- wc.exe -w file.c    //返回文件 file.c 的词的数目  
- wc.exe -l file.c      //返回文件 file.c 的行数

#### 扩展功能： ####
- -s   递归处理目录下符合条件的文件。
- -a   返回更复杂的数据（代码行 / 空行 / 注释行）。

#### 高级功能： ####
- -x 这个参数单独使用。如果命令行有这个参数，则程序会显示图形界面，用户可以通过界面选取单个文件，程序就会显示文件的字符数、行数等全部统计信息。

 
## 二、遇到的困难及解决方法 ##
- 困难描述：没用Java做过文件输入、命令行带参数的程序
- 做过哪些尝试：网上搜索相关资源进行学习
- 是否解决：是
- 有何收获：了解并实现了相关功能

## 三、设计程序流程 ##

## 四、关键代码 ##
项目目录：

![项目目录](https://i.imgur.com/VCw5zjO.png)

主函数代码：

    public static void main(String[] args) throws IOException
    {
    	while (true) {
    		// 输出面板
    		System.out.println("\n----------------------3216005168 WC程序----------------------");
    		System.out.println("|   |");
    		System.out.println("|-c [文件路径]  返回文件字符数  |");
    		System.out.println("|-w [文件路径]  返回文件词的数目|");
    		System.out.println("|-l [文件路径]  返回文件行数|");
    		System.out.println("|-s [文件夹路径]  搜索文件名(须为第1位) |");
    		System.out.println("|-a [文件路径]  统计代码行/空行/注释行  |");
    		System.out.println("|   |");
    		System.out.println("-------------------------------------------------------------");
    
    		// 获取输入指令
    		System.out.println("Please enter the command：");
    		Scanner command = new Scanner(System.in);
    		String arr[]= command.nextLine().split("\\s");
    
    		/* * 根据命令 执行操作 * */
    		int len = arr.length;
    		if(arr[0].equals("-s"))
				searchFile(arr);
    		else
				operation(len,0,arr,arr[arr.length-1]);
    	}
    }

操作函数代码：

	private static void operation(int len,int start,String[] arr,String fileName) throws IOException
    {
        for(int i=start;i<len-1;i++) {
            switch (arr[i]) {
                //指定文件下字符数、单词数、行数、特殊行数
                case "-c":
				case "-w":
				case "-l":
				case "-a":
                    searchByFileName(fileName,arr[i]);break;
                default:
                    System.out.println("指令输入错误!");
                    break;
            }
        }
    }

逻辑函数代码：

- 基本功能整合

		/* * 计算字符数的函数 * */
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

		/* * 计算词的数目的函数 * */
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

- 拓展功能

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
        	        System.out.println(f.getName());
        	    } else if (f.isDirectory()) {
        	        System.out.println(f.getAbsolutePath());
        	        searchFile(arr);
        	    }
        	}
        	for (File f1 : fileList) {
        	    //operation(arr.length,1,arr,f1.getAbsolutePath());
        	    operation(arr.length-1,1,arr,f1.getAbsolutePath());
        	    //System.out.println(f1.getAbsolutePath());
        	}
    	}

## 五、测试运行 ##

1. 测试目录/测试文件

	![测试目录/测试文件](https://i.imgur.com/2ZLFBLN.png)

2. 程序启动：
 
	 ![程序启动](https://i.imgur.com/K7lU5Qo.png)

3. 基本功能：

	![基本功能](https://i.imgur.com/lUJWtKS.png)

4. 递归查询文件

	![递归查询文件](https://i.imgur.com/o3qJCJ1.png)

	![递归查询2](https://i.imgur.com/QvGyjCD.png)

5. 统计代码行、注释行、空行

	![特殊行数](https://i.imgur.com/iNGzdJh.png)

6. 代码覆盖率

	![覆盖率](https://i.imgur.com/2rJNBKI.png)

 
## 六、PSP ##

| PSP2.1| Personal Software Process Stages| 预估耗时（分钟） | 实际耗时（分钟） |
|-----------------|----------------------|-----------------|----------------|
| Planning        | 计划                     |30              |45            |
| · Estimate        | · 估计这个任务需要多少时间    |· 30        |· 45          |
| Development     | 开发                      |780             |645          |
| · Analysis        | · 需求分析 (包括学习新技术)   |· 120       |· 150        |
| · Design Spec     | · 生成设计文档               |· 30        |· 40         |
| · Design Review   | · 设计复审 (和同事审核设计文档)|· 30        |· 30         |
| · Coding Standard | · 代码规范 (为目前的开发制定合适的规范)|· 60 |· 45         |
| · Design          | · 具体设计              |· 120            |· 90         |
| · Coding          | · 具体编码              |· 240            |· 200        |
| · Code Review     | · 代码复审              |· 60             |· 30         |
| · Test            | · 测试（自我测试，修改代码，提交修改）|· 120  |· 60         |
| Reporting         | 报告                   |120               |105          |
| · Test Report     | · 测试报告              |· 60             |· 45         |
| · Size Measurement| · 计算工作量            |· 30              |· 30        |
| · Postmortem & Process Improvement Plan|· 事后总结, 并提出过程改进计划|· 30|· 30|
| 合计              |                        |930               |795         |

## 七、项目小结 ##
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
首先，因为自己是前端方向的，对于Java的学习也只是停留在学校教学阶段，所以在开发这个个人项目之前，重新回顾了一下Java的知识，也充分意识到自己对于Java语言的事件流的不了解，同时也学会了从0到1实现一个程序，从预估、设计、编码、开发、测试、文档等流程中锻炼自己。

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
其次，在作业中使用了博客的方法来提交作业，对于一直想要搭建博客写博文却一直没有实现的自己无疑是极好的，既能培养自己写博客的习惯，又能提升自己的实践能力。