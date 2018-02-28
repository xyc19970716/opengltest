#include "GLFW/glfw3.h"
#include "iostream"
#include "GLAD/glad.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

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

	//��Ⱦѭ��
	while (!glfwWindowShouldClose(window)) {  //����Ƿ�رմ���
		processInput(window);		//���������¼�

									//��Ⱦ
		glClearColor(1.0f, 1.0f, 0.0f, 1.0f);		//����������ɫ����ɫ��
		glClear(GL_COLOR_BUFFER_BIT);				//����

		glfwSwapBuffers(window);					//����ʾ������������潻������ʾ���������е����ݣ�
		glfwPollEvents();							//����Ƿ����¼������������������ͼ��������¼���

	}
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