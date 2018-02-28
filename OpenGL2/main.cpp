//��������
#include "GLFW/glfw3.h"
#include "iostream"
#include "GLAD/glad.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

//������ɫ����
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";	//ǧ����������\0

		//ƬԪ��ɫ������
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\0";	//ǧ����������\0

float vertices[] = {			//��������
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f
};
int main() {
	// ��ʼ��glfw����
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);		//ָ��OpenGL�����汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);		//ָ��PoenGL���Ӱ汾��
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);		//ʹ��OpenGL�ĺ���ģʽ���ɱ����Ⱦ�ܵ���ģʽ��

	GLFWwindow* window = glfwCreateWindow(1280, 720, "LreanOpenGL", NULL, NULL);		//��������
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();		//�����������ֹ����
		return -1;
	}

	glfwMakeContextCurrent(window);		//�����ڵ������Ļ�������Ϊ��ǰ���̵߳������Ļ���

	//��ʼ��glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//ע�ᴰ�ڻص�����
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	//������ɫ������
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//Դ��ӵ���ɫ�����󲢱���
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//����ƬԪ��ɫ������
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//������ɫ��
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);


	//������ɫ��
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);			//����ΨһID
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	//ָ��Ϊ���㻺�����
										//���������ݸ��Ƶ�VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	////////////                   ���ݴ�С         ����		��ʽ
	
	//ָ�������ʽ
	glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, 3 * sizeof(float),(void*)0);
	///					loation Ver3 float  �淶��    3 * 4�ֽ�          ƫ����
	glEnableVertexAttribArray(0);	//location
	

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);



	//��Ⱦѭ��
	while (!glfwWindowShouldClose(window)) {  //����Ƿ�رմ���
		processInput(window);		//���������¼�

									//��Ⱦ
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);		//����������ɫ����ɫ��
		glClear(GL_COLOR_BUFFER_BIT);				//����


		//ʹ����ɫ������
		glUseProgram(shaderProgram);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);			//0��ʾ�����������ʼ������3��ʾ��2������

		glfwSwapBuffers(window);					//����ʾ������������潻������ʾ���������е����ݣ�
		glfwPollEvents();							//����Ƿ����¼������������������ͼ��������¼���

	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();								//��ֹ����
	return 0;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);				//����OpenGL���ӿ�����
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {//���Esc����û�а���
		glfwSetWindowShouldClose(window, true);				//���ô��ڹر�
	}

}