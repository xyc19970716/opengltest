//画三角形
#include "GLFW/glfw3.h"
#include "iostream"
#include "GLAD/glad.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

//顶点着色代码
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";	//千万别忘记这个\0

		//片元着色器代码
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\0";	//千万别忘记这个\0

float vertices[] = {			//顶点数组
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f
};
int main() {
	// 初始化glfw窗口
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);		//指定OpenGL的主版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);		//指定PoenGL的子版本号
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);		//使用OpenGL的核心模式（可编程渲染管道的模式）

	GLFWwindow* window = glfwCreateWindow(1280, 720, "LreanOpenGL", NULL, NULL);		//创建窗口
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();		//如果出错，则终止进程
		return -1;
	}

	glfwMakeContextCurrent(window);		//将窗口的上下文环境设置为当前主线程的上下文环境

	//初始化glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//注册窗口回调函数
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	//创建着色器对象
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//源码加到着色器对象并编译
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//创建片元着色器对象
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//链接着色器
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);


	//清理着色器
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);			//生成唯一ID
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	//指定为顶点缓存对象
										//将顶点数据复制到VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	////////////                   数据大小         数据		方式
	
	//指定顶点格式
	glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, 3 * sizeof(float),(void*)0);
	///					loation Ver3 float  规范化    3 * 4字节          偏移量
	glEnableVertexAttribArray(0);	//location
	

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);



	//渲染循环
	while (!glfwWindowShouldClose(window)) {  //检测是否关闭窗口
		processInput(window);		//处理输入事件

									//渲染
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);		//设置清屏颜色（黄色）
		glClear(GL_COLOR_BUFFER_BIT);				//清屏


		//使用着色器对象
		glUseProgram(shaderProgram);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);			//0表示顶点数组的起始索引，3表示右2个顶点

		glfwSwapBuffers(window);					//将显示缓存和离屏缓存交换（显示离屏缓存中的内容）
		glfwPollEvents();							//检查是否有事件触发（例如鼠标输入和键盘输入事件）

	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();								//终止进程
	return 0;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);				//调整OpenGL的视口区域
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {//检查Esc键有没有按下
		glfwSetWindowShouldClose(window, true);				//设置窗口关闭
	}

}