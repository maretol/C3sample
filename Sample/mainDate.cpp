#include <stdio.h>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <GL/glut.h>

//-----------------------------------------------------------------------------------------------
//���̃f�[�^�́A�Ƃ���H���usample�v�ƌĂ΂����̂ł�
//����sample�����H���邱�Ƃɂ���āA���ȒP�ɃQ�[������邱�Ƃ��ł��邱�Ƃ�ڎw���č���Ă��܂�
//�������g��Ȃ��Ă��\��Ȃ����A�g���Ă��\���܂���
//����ҁFmaretol�A���� ���t(maretol@club.kyutech.ac.jp)
//�����֌W�F��{�I�ɏ����͂���܂���B�������A���H�E�����H�ɂ�����炸�񎟔z�z�͂����k��������
//���l�FC++,C,OpenGL,OpenCV��p���Đ��삳��Ă��܂�
//OpenGL�iGLUT�j�AOpenCV�̓�����NuGet��O��Ƃ��Ă��܂����A
//�p�X��ʂ�include���𐮗����Ă�����Α��̎�i�ł�������͂���܂���
//-----------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------
//���ӁF�v���g�^�C�v�錾�����Ă��Ȃ��̂ŕ��R�[�h�ɂȂ��Ă���܂�
//-----------------------------------------------------------------------------------------------

//�f�B�X�v���C�̏c���𑜓x
int displayWidth = 800;
int displayHeight = 600;



//���̐�́udisplay~�v�̂��̂͑S�ĕ`��̊֐�
//�����Ȃ���ʂ𐶐�
void display1() {
}




//�l�p�`��\������
void display2() {
	//�w�i�F����
	//�����̏���RGB�ƃA���t�@�l�B0�`255�ŕ\������邪�A������0.0�`1.0��float�^
	//256�i�K�Ō��߂Ă���̂Ȃ�� �o���������l/255 �������ɂ��ēn���Ƃ悢
	glClearColor(1.0, 1.0, 1.0, 0.0);

	//�w�i�`��
	glClear(GL_COLOR_BUFFER_BIT);

	//�`�悷��}�`�̌���BGL_LINE_LOOP�͕`��̎��
	//��ނ͎O�p�`�A�l�p�`�A�����A�|���S���Ȃǂ���������
	glBegin(GL_LINE_LOOP);

	//�`�悷��}�`�̐F
	//�F�̐��l�ɂ��Ă͔w�i�Ɠ�����RGB�̏���0.0�`1.0
	//�������AglColor��glColor3ub()�֐�������B����́iByte�^�Łj0�`255��n�����Ƃ��ł���
	glColor3f(0.0, 0.0, 0.0);

	//���W�̌���
	//Vertex�͍��W�A2�͈�����2�Ai��int�^�������Ƃ���A�Ƃ����Ӗ�
	//���W��
	glVertex2i(300, 200);
	glVertex2i(300, 400);
	glVertex2i(500, 400);
	glVertex2i(500, 200);
	//�w��`��̏I��
	glEnd();

	//���ׂĂ̏������I���Ă���`�悷��
	glFinish();
}




//�l�p�`��h��Ԃ�
void display3() {

	//�w�i�F����
	glClearColor(1.0, 1.0, 1.0, 0.0);

	//�w�i�`��
	glClear(GL_COLOR_BUFFER_BIT);

	//�`�悷��}�`�̌���
	glBegin(GL_QUADS);

	//�`�悷��}�`�̐F
	glColor3f(0.0, 0.0, 0.0);

	//���W�̌���
	glVertex2i(300, 200);
	glVertex2i(300, 400);
	glVertex2i(500, 400);
	glVertex2i(500, 200);
	//�w��`��̏I��
	glEnd();

	//���ׂĂ̏������I���Ă���`�悷��
	glFinish();
}




//���W���A�r���[�|�[�g�̐ݒ�
//�E�B���h�E�̃T�C�Y�ύX���̓�����o�^
void redisplay(int w, int h) {
	//�r���[�|�[�g�i������͈́j�̐ݒ�
	//����͌��_�������ɂȂ��Ă���AX�����E�������AY���W����������̍��W��
	glViewport(0, 0, w, h);

	glMatrixMode(GL_MODELVIEW);

	//�ϊ����W�̏�����
	glLoadIdentity();

	//�ǂ��܂ł�����ɓ���邩�̐ݒ�
	glOrtho(0.0, (double)w, (double)h, 0.0, -1.0, 1.0);
}




//���������e�N�X�`���֘A
//�e�N�X�`���ϐ��o�^
GLuint texture[1];

bool loadGLTextures() {
	IplImage *image1 = cvLoadImage("texture.jpg", CV_LOAD_IMAGE_ANYDEPTH|CV_LOAD_IMAGE_ANYCOLOR);
	if(image1==NULL) {
		return false;
	}
	
	cvCvtColor(image1, image1, CV_BGR2RGB);
	cvFlip(image1, NULL, 0);

	//��������e�N�X�`���쐬
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image1->width, image1->height,
		GL_RGB, GL_UNSIGNED_BYTE, image1->imageData);

	cvReleaseImage(&image1);

	return true;
}




//�e�N�X�`���̕\���Ɋւ���display�֐�
void display4() {
	glClear(GL_COLOR_BUFFER_BIT);

	//�w�i�F����
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);

	glTexCoord2d(0.0, 1.0);
	glVertex2i(300, 200);

	glTexCoord2d(0.0, 0.0);
	glVertex2i(300, 400);

	glTexCoord2d(1.0, 0.0);
	glVertex2i(500, 400);

	glTexCoord2d(1.0, 1.0);
	glVertex2i(500, 200);

	glEnd();

	glDisable(GL_TEXTURE_2D);

	glClearColor(1.0, 1.0, 1.0, 1.0);
	if(loadGLTextures()==false) {
		std::cerr<<"Can't Load Image\n";
	}

	glFinish();
}




double xMove = 1.00;
double yMove = 0.00;
int xFlag = 300;
int yFlag = 400;
const GLint vertex[] = {xFlag, 200, 300, 400, 500, 400, 500, 200};
const GLfloat texVer[] = {0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0};

void display5() {
	glClear(GL_COLOR_BUFFER_BIT);

	//�w�i�F����
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glEnable(GL_TEXTURE_2D);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glTranslatef(xMove, yMove, 0.0);
	glVertexPointer(2, GL_INT, 0, vertex);
	glTexCoordPointer(2, GL_FLOAT, 0, texVer);

	glBegin(GL_QUADS);{
		for(int i = 0; i<4; i++) {
			glArrayElement(i);
		}
	}
	glEnd();


	xFlag = xFlag+xMove;
	if(xFlag+200>displayWidth||xFlag<0) {
		xMove = xMove * (-1);
	}

	glDisable(GL_TEXTURE_2D);

	glClearColor(1.0, 1.0, 1.0, 1.0);
	if(loadGLTextures()==false) {
		std::cerr<<"Can't Load Image\n";
	}

	glFinish();
}

void timer(int t) {
	//glutDisplayFunc���̊֐����ČĂяo������
	//����ɂ���čĕ`�悪�����
	glutPostRedisplay();

	//���ōĂьĂяo�����Ƃōēx������
	glutTimerFunc(17, timer, 0);
}



//��������main��
int main(int argc, char *argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(displayWidth, displayHeight);
	glutCreateWindow("�E�B���h�E�^�C�g��");

	//�f�B�X�v���C�̕`�ʂ��s��
	glutDisplayFunc(display5);

	//�f�B�X�v���C���ω������ꍇ�̕`��
	glutReshapeFunc(redisplay);
	
	//�ĕ`�揈�����s�����߂̊֐�
	glutTimerFunc(17, timer, 0);



	//�}�E�X�A�L�[�{�[�h�̓��͈͂ȉ��̊֐��𗘗p�B�R�����g�A�E�g����������Ǝg���܂�
	//�t�^���Ă�ɓ���܂����B�ڂ����͎����Œ��ׂ悤
//	glutKeyboardFunc(keyboard);
//	glutMouseFunc(mouse);

	//���C�����[�v
	glutMainLoop();
	return 0;
}


void keyboard(unsigned char key, int x, int y) {
	//key �͉����ꂽ�L�[�������^�œn�����B����int�^�ɕϊ��\
	//x,y �̓L�[�������ꂽ���̃}�E�X�̈ʒu���W�B�E�B���h�E�̍��オ���_
	//�Ȃ��A���̊֐��ł͓���{�^���i����������Ctrl�L�[�j�͎��Ȃ��̂�
	//�ʂ̊֐�(glutSpecialFunc)���g��
}

void mouse(int button, int state, int x, int y) {
	//button �͂ǂ̃{�^���ŃA�N�V�������N�������B1�ō��{�^���A2�ŉE�{�^���Ȃ�
	//state �͉����ꂽ�����ꂽ���Bx,y ��keyboard�Ɠ���
	//�Ȃ��A�������܂܂̓���͕ʂ̊֐�(glutMotionFunc)���g���B�ڂ����͒��ׂ悤
}