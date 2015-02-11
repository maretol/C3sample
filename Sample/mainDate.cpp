#include <stdio.h>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <GL/glut.h>

//-----------------------------------------------------------------------------------------------
//このデータは、ところ曰く「sample」と呼ばれるものです
//このsampleを加工することによって、より簡単にゲームを作ることができることを目指して作られています
//もちろん使わなくても構わないし、使っても構いません
//製作者：maretol、染矢 元春(maretol@club.kyutech.ac.jp)
//権利関係：基本的に条件はありません。ただし、加工・無加工にかかわらず二次配布はご相談ください
//備考：C++,C,OpenGL,OpenCVを用いて制作されています
//OpenGL（GLUT）、OpenCVの導入はNuGetを前提としていますが、
//パスを通しinclude文を整理してあげれば他の手段でも何ら問題はありません
//-----------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------
//注意：プロトタイプ宣言をしていないので糞コードになっております
//-----------------------------------------------------------------------------------------------

//ディスプレイの縦横解像度
int displayWidth = 800;
int displayHeight = 600;



//この先の「display~」のものは全て描画の関数
//何もない画面を生成
void display1() {
}




//四角形を表示する
void display2() {
	//背景色決定
	//引数の順はRGBとアルファ値。0～255で表現されるが、引数は0.0～1.0のfloat型
	//256段階で決めているのならば 出したい数値/255 を引数にして渡すとよい
	glClearColor(1.0, 1.0, 1.0, 0.0);

	//背景描画
	glClear(GL_COLOR_BUFFER_BIT);

	//描画する図形の決定。GL_LINE_LOOPは描画の種類
	//種類は三角形、四角形、直線、ポリゴンなどいくつかある
	glBegin(GL_LINE_LOOP);

	//描画する図形の色
	//色の数値については背景と同じでRGBの順に0.0～1.0
	//ただし、glColorはglColor3ub()関数がある。これは（Byte型で）0～255を渡すことができる
	glColor3f(0.0, 0.0, 0.0);

	//座標の決定
	//Vertexは座標、2は引数が2つ、iはint型を引数とする、という意味
	//座標は
	glVertex2i(300, 200);
	glVertex2i(300, 400);
	glVertex2i(500, 400);
	glVertex2i(500, 200);
	//指定描画の終了
	glEnd();

	//すべての処理を終えてから描画する
	glFinish();
}




//四角形を塗りつぶす
void display3() {

	//背景色決定
	glClearColor(1.0, 1.0, 1.0, 0.0);

	//背景描画
	glClear(GL_COLOR_BUFFER_BIT);

	//描画する図形の決定
	glBegin(GL_QUADS);

	//描画する図形の色
	glColor3f(0.0, 0.0, 0.0);

	//座標の決定
	glVertex2i(300, 200);
	glVertex2i(300, 400);
	glVertex2i(500, 400);
	glVertex2i(500, 200);
	//指定描画の終了
	glEnd();

	//すべての処理を終えてから描画する
	glFinish();
}




//座標軸、ビューポートの設定
//ウィンドウのサイズ変更時の動きを登録
void redisplay(int w, int h) {
	//ビューポート（見える範囲）の設定
	//これは原点が左下になっており、X軸が右方向正、Y座標が上方向正の座標軸
	glViewport(0, 0, w, h);

	glMatrixMode(GL_MODELVIEW);

	//変換座標の初期化
	glLoadIdentity();

	//どこまでを視野に入れるかの設定
	glOrtho(0.0, (double)w, (double)h, 0.0, -1.0, 1.0);
}




//ここから先テクスチャ関連
//テクスチャ変数登録
GLuint texture[1];

bool loadGLTextures() {
	IplImage *image1 = cvLoadImage("texture.jpg", CV_LOAD_IMAGE_ANYDEPTH|CV_LOAD_IMAGE_ANYCOLOR);
	if(image1==NULL) {
		return false;
	}
	
	cvCvtColor(image1, image1, CV_BGR2RGB);
	cvFlip(image1, NULL, 0);

	//ここからテクスチャ作成
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image1->width, image1->height,
		GL_RGB, GL_UNSIGNED_BYTE, image1->imageData);

	cvReleaseImage(&image1);

	return true;
}




//テクスチャの表示に関するdisplay関数
void display4() {
	glClear(GL_COLOR_BUFFER_BIT);

	//背景色決定
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

	//背景色決定
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
	//glutDisplayFunc内の関数を再呼び出しする
	//これによって再描画がされる
	glutPostRedisplay();

	//中で再び呼び出すことで再度動かす
	glutTimerFunc(17, timer, 0);
}



//ここからmain文
int main(int argc, char *argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(displayWidth, displayHeight);
	glutCreateWindow("ウィンドウタイトル");

	//ディスプレイの描写を行う
	glutDisplayFunc(display5);

	//ディスプレイが変化した場合の描画
	glutReshapeFunc(redisplay);
	
	//再描画処理を行うための関数
	glutTimerFunc(17, timer, 0);



	//マウス、キーボードの入力は以下の関数を利用。コメントアウトを解除すると使えます
	//付録がてらに入れました。詳しくは自分で調べよう
//	glutKeyboardFunc(keyboard);
//	glutMouseFunc(mouse);

	//メインループ
	glutMainLoop();
	return 0;
}


void keyboard(unsigned char key, int x, int y) {
	//key は押されたキーが文字型で渡される。直接int型に変換可能
	//x,y はキーが押された時のマウスの位置座標。ウィンドウの左上が原点
	//なお、この関数では特殊ボタン（←↓↑→やCtrlキー）は取れないので
	//別の関数(glutSpecialFunc)を使う
}

void mouse(int button, int state, int x, int y) {
	//button はどのボタンでアクションが起きたか。1で左ボタン、2で右ボタンなど
	//state は押されたか離れたか。x,y はkeyboardと同じ
	//なお、押したままの動作は別の関数(glutMotionFunc)を使う。詳しくは調べよう
}