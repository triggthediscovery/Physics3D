 /*
 * OpenGLSamples (openglsamples.sf.net) Examples
 * VC++ users should create a Win32 Console project and link 
 * the program with glut32.lib, glu32.lib, opengl32.lib
 *
 * GLUT can be downloaded from http://www.xmission.com/~nate/glut.html
 * OpenGL is by default installed on your system.
 * For an installation of glut on windows for MS Visual Studio 2010 see: http://nafsadh.wordpress.com/2010/08/20/glut-in-ms-visual-studio-2010-msvs10/
 *
 */
#define GLUT_DISABLE_ATEXIT_HACK 

#include <stdio.h>
#include <windows.h>	   // Standard header for MS Windows applications
#include <glew.h>
#include <glut.h>
#include <math.h>

#define KEY_ESCAPE 27

double yaw=0, pitch=0, char_x=0, char_y=0, char_z=-10;
int screen_pos_x, screen_pos_y, mouse_x_origin, mouse_y_origin, count;
int mouse_x, mouse_y, xloc, yloc, xloc2, yloc2;
int buttons[10];
bool Mouse_Press = false;

struct VERTEX {
	float x;
	float y;
	float z;
};

struct CONTXT {
	VERTEX mx;
	VERTEX my;
	VERTEX mz;
};

void                MOVEMENT();
void                PassiveMotion(int, int);
void                MousePressed(int, int, int, int);
void                MouseWheel(int, int, int, int);
void                CreateModel(LPCWSTR);
void                ReadModel(LPCWSTR);
void                ReadModel2();
void                WriteModel(LPCWSTR);
void                LoadTex(int, LPCTSTR);

typedef struct {
    int width;
	int height;
	char* title;

	float field_of_view_angle;
	float z_near;
	float z_far;
} glutWindow;

glutWindow win;

bool testAng(float x12, float x23, float x13, float y12, float y23, float y13) {
	if ((((x12/y12)-(x23/y23))<0.01) || (((x13/y13)-(x23/y23))<0.01) || (((x12/y12)-(x13/y13))<0.01)) {
		return true;
	} else {
		return false;
	}
}

VERTEX nVERTEX(float x, float y, float z) {
	VERTEX retVal;

	retVal.x=x;
	retVal.y=y;
	retVal.z=z;

	return retVal;
}

VERTEX addVERTEX(VERTEX v1, VERTEX v2) {
	VERTEX retVal;

	retVal.x=v1.x+(v2.x*5);
	retVal.y=v1.y+(v2.y*5);
	retVal.z=v1.z+(v2.z*5);

	return retVal;
}

VERTEX reorient(VERTEX in, CONTXT ctx) {
	return  nVERTEX(((in.x*ctx.mx.x)+(in.y*ctx.mx.y)+(in.z*ctx.mx.z)),
					((in.x*ctx.my.x)+(in.y*ctx.my.y)+(in.z*ctx.my.z)),
					((in.x*ctx.mz.x)+(in.y*ctx.mz.y)+(in.z*ctx.mz.z)));
}

public class Point {
	public:
		VERTEX loc;
		float size;

		void setPos (VERTEX mloc) {
			loc=mloc;
		}

		void setSize (float msize) {
			size=msize;
		}

		void draw() {
			VERTEX coords[5];
			
			coords[0].x = size;  coords[0].z = size;  coords[0].y = 2*size;
			coords[1].x = -size; coords[1].z = size;  coords[1].y = 2*size;
			coords[2].x = size;  coords[2].z = -size; coords[2].y = 2*size;
			coords[3].x = -size; coords[3].z = -size; coords[3].y = 2*size;
			coords[4].x = 0;  coords[4].z = 0;  coords[4].y = 0;
			
			VERTEX buf;

			for (int i=0; i<5; i++) {
				buf=coords[i];

				coords[i].x = buf.x + loc.x;
				coords[i].y = buf.y + loc.y;
				coords[i].z = buf.z + loc.z;
			}

			unsigned int tri[20] = {0, 2, 4, 1, 3, 4, 0, 1, 4,
									2, 3, 4, 0, 3, 1, 0, 3, 2};

			unsigned int lin[16] = {0, 1, 2, 3, 0, 2, 1, 3, 
									0, 4, 1, 4, 2, 4, 3, 4};

			glColor3f(0.8f,0.8f,0.8f);
			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3, GL_FLOAT, 0, &coords);
			glDrawElements(GL_TRIANGLES,20,GL_UNSIGNED_INT,&tri);
			glColor3f(0.0f,0.0f,0.0f);
			glDrawElements(GL_LINES,16,GL_UNSIGNED_INT,&lin);
		}
};

public class Cube {
	public:
		double x;
		double y;
		double z;
		double sizex;
		double sizey;
		double sizez;
		double pitch;
		double roll;
		double yaw;

		void setPos (double mx, double my, double mz) {
			x=mx;
			y=my;
			z=mz;
		}

		void setSize (double mysizex, double mysizey, double mysizez) {
			sizex=mysizex;
			sizey=mysizey;
			sizez=mysizez;
		}

		void setPitch (double pit) {
			pitch=pit;
		}

		void addPitch (double amt) {
			pitch+=amt;
		}

		void draw() {
			VERTEX xax, yax, zax;

			xax.x = sin((pitch)/57.29577);
			xax.y = 0;
			xax.z = cos((pitch)/57.29577);

			zax.x = cos((pitch)/57.29577);
			zax.y = 0;
			zax.z = -sin((pitch)/57.29577);

			yax.x = 0;
			yax.y = 1;
			yax.z = 0;

			VERTEX coords[8];
			
			coords[0].x = sizex;  coords[0].y = sizey;  coords[0].z = sizez;
			coords[1].x = -sizex; coords[1].y = sizey;  coords[1].z = sizez;
			coords[2].x = sizex;  coords[2].y = -sizey; coords[2].z = sizez;
			coords[3].x = -sizex; coords[3].y = -sizey; coords[3].z = sizez;
			coords[4].x = sizex;  coords[4].y = sizey;  coords[4].z = -sizez;
			coords[5].x = -sizex; coords[5].y = sizey;  coords[5].z = -sizez;
			coords[6].x = sizex;  coords[6].y = -sizey; coords[6].z = -sizez;
			coords[7].x = -sizex; coords[7].y = -sizey; coords[7].z = -sizez;

			VERTEX buf;

			for (int i=0; i<8; i++) {
				buf=coords[i];

				coords[i].x = (buf.x*xax.x) + (buf.y*xax.y) + (buf.z*xax.z) + x;
				coords[i].y = (buf.x*yax.x) + (buf.y*yax.y) + (buf.z*yax.z) + y;
				coords[i].z = (buf.x*zax.x) + (buf.y*zax.y) + (buf.z*zax.z) + z;
			}

			unsigned int tri[36] = {0, 3, 1, 0, 3, 2, 4, 7, 5, 4, 7, 6,
									0, 6, 2, 0, 6, 4, 1, 7, 3, 1, 7, 5,
									0, 5, 1, 0, 5, 4, 2, 7, 3, 2, 7, 6};

			unsigned int lin[36] = {0, 1, 2, 3, 4, 5, 6, 7,
									0, 2, 1, 3, 4, 6, 5, 7, 
									0, 4, 1, 5, 2, 6, 3, 7};

			glColor3f(0.8f,0.8f,0.8f);
			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3, GL_FLOAT, 0, &coords);
			glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,&tri);
			glColor3f(0.0f,0.0f,0.0f);
			glDrawElements(GL_LINES,36,GL_UNSIGNED_INT,&lin);

		}
};

public class Tri {
	public:
		VERTEX p1;
		VERTEX p2;
		VERTEX p3;
		VERTEX i1;
		VERTEX i2;

		CONTXT ctx;
		CONTXT atx;

		void setTri (VERTEX pp1, VERTEX pp2, VERTEX pp3) {
			p1=pp1;
			p2=pp2;
			p3=pp3;
		}

		void setInt (VERTEX ii1, VERTEX ii2) {
			i1=ii1;
			i2=ii2;
		}

		void setCtx () {
			float db12 = sqrt(((p1.x-p2.x)*(p1.x-p2.x))+((p1.y-p2.y)*(p1.y-p2.y))+((p1.z-p2.z)*(p1.z-p2.z)));
			float db23 = sqrt(((p3.x-p2.x)*(p3.x-p2.x))+((p3.y-p2.y)*(p3.y-p2.y))+((p3.z-p2.z)*(p3.z-p2.z)));
			float db13 = sqrt(((p1.x-p3.x)*(p1.x-p3.x))+((p1.y-p3.y)*(p1.y-p3.y))+((p1.z-p3.z)*(p1.z-p3.z)));

			float d12, d23, d13;

				d12=db12;
				d23=db23;
				d13=db13;

			ctx.mx.x=(p1.x-p2.x)/d12;
			ctx.mx.y=(p1.y-p2.y)/d12;
			ctx.mx.z=(p1.z-p2.z)/d12;

			float d = ((d12*d12)-(d23*d23)+(d13*d13))/(2*(d12));

			VERTEX per = nVERTEX(p1.x-(ctx.mx.x*d),p1.y-(ctx.mx.y*d),p1.z-(ctx.mx.z*d));

			float dp = sqrt(((per.x-p3.x)*(per.x-p3.x))+((per.y-p3.y)*(per.y-p3.y))+((per.z-p3.z)*(per.z-p3.z)));

			ctx.my.x=(per.x-p3.x)/dp;
			ctx.my.y=(per.y-p3.y)/dp;
			ctx.my.z=(per.z-p3.z)/dp;

			ctx.mz.x = sqrt(abs((ctx.mx.x*ctx.mx.x)+(ctx.my.x*ctx.my.x)-1));
			ctx.mz.y = sqrt(abs((ctx.mx.y*ctx.mx.y)+(ctx.my.y*ctx.my.y)-1));
			ctx.mz.z = sqrt(abs((ctx.mx.z*ctx.mx.z)+(ctx.my.z*ctx.my.z)-1));

			if (abs(sqrt((ctx.mx.x*ctx.mx.x)+(ctx.my.x*ctx.my.x)+(ctx.mz.x*ctx.mz.x))-1)>.01) {ctx.mz.x=-ctx.mz.x;}
			if (abs(sqrt((ctx.mx.y*ctx.mx.y)+(ctx.my.y*ctx.my.y)+(ctx.mz.y*ctx.mz.y))-1)>.01) {ctx.mz.y=-ctx.mz.y;}
			if (abs(sqrt((ctx.mx.z*ctx.mx.z)+(ctx.my.z*ctx.my.z)+(ctx.mz.z*ctx.mz.z))-1)>.01) {ctx.mz.z=-ctx.mz.z;}

			atx.mx.x = ctx.mx.x; atx.mx.y=ctx.my.x; atx.mx.z=ctx.mz.x;
			atx.my.x = ctx.mx.y; atx.my.y=ctx.my.y; atx.my.z=ctx.mz.y;
			atx.mz.x = ctx.mx.z; atx.mz.y=ctx.my.z; atx.mz.z=ctx.mz.z;
		}

		bool intersection() {
			float nx =(p1.x*ctx.mz.x)+(p1.y*ctx.mz.y)+(p1.z*ctx.mz.z);
			VERTEX ix1, ix2, in, px1, px2, px3;

			ix1 = reorient(i1,ctx);
			ix2 = reorient(i2,ctx);

			px1 = reorient(p1,ctx);
			px2 = reorient(p2,ctx);
			px3 = reorient(p3,ctx);
			
			float mzx = ((ix1.x-ix2.x)/(ix1.z-ix2.z));
			float mzy = ((ix1.y-ix2.y)/(ix1.z-ix2.z));
			float bzx = ix1.x-(ix1.z*mzx);
			float bzy = ix1.y-(ix1.z*mzy);

			in.x=(nx*mzx)+bzx;
			in.y=(nx*mzy)+bzy;
			in.z=nx;

			float m1, m2; 

			VERTEX out;

			out = reorient(in,atx);

			Point outp;
			
			outp.setPos(out);
			outp.setSize(10);

			outp.draw();

			return true;
		}

		void draw() {
			VERTEX coords[8];
			
			coords[0]=p1;
			coords[1]=p2;
			coords[2]=p3;
			coords[3]=i1;
			coords[4]=i2;
			coords[5]=addVERTEX(p1,ctx.mx);
			coords[6]=addVERTEX(p1,ctx.my);
			coords[7]=addVERTEX(p1,ctx.mz);

			unsigned int tri[6] = {0,1,2};

			unsigned int lin[8] = {0,1,1,2,2,0,3,4};

			unsigned int ln1[2] = {0,5};
			unsigned int ln2[2] = {0,6};
			unsigned int ln3[2] = {0,7};

			glColor3f(0.8f,0.8f,0.8f);
			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3, GL_FLOAT, 0, &coords);
			glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,&tri);
			glColor3f(0.0f,0.0f,0.0f);
			glDrawElements(GL_LINES,8,GL_UNSIGNED_INT,&lin);

			glColor3f(1.0f,0.0f,0.0f);
			glDrawElements(GL_LINES,2,GL_UNSIGNED_INT,&ln1);
			glColor3f(0.0f,1.0f,0.0f);
			glDrawElements(GL_LINES,2,GL_UNSIGNED_INT,&ln2);
			glColor3f(0.0f,0.0f,1.0f);
			glDrawElements(GL_LINES,2,GL_UNSIGNED_INT,&ln3);

			Point ipt1, ipt2;
			
			ipt1.setPos(i1);
			ipt1.setSize(10);

			ipt2.setPos(i2);
			ipt2.setSize(10);

			//ipt1.draw();
			//ipt2.draw();

			intersection();
		}
};

Cube testCube;
Tri testTri;
Point testPoint;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		     // Clear Screen and Depth Buffer
	glLoadIdentity();

	glBegin(GL_TRIANGLES);
		glColor3f(0.5f,0.5f,0.5f);
		glVertex3f(2000,2000,-500);
		glVertex3f(2000,-2000,-500);
		glVertex3f(-2000,-2000,-500);
		glVertex3f(2000,2000,-500);
		glVertex3f(-2000,2000,-500);
		glVertex3f(-2000,-2000,-500);
	glEnd();

	glRotatef(pitch,1,0,0);
	glRotatef(yaw,0,1,0);
	glTranslatef(char_x,char_y,char_z);

	if (yaw>180)
	{
		yaw=yaw-360;
	}

	if (yaw<-180)
	{
		yaw=yaw+360;
	}

	if (pitch>180)
	{
		pitch=pitch-360;
	}

	if (pitch<-180)
	{
		pitch=pitch+360;
	}

	if (GetAsyncKeyState(0x57))
	{
		char_x = ((sin(yaw/-57.29577)*sin((pitch/57.29577)+1.57079633))*.1)+char_x;
		char_z = ((cos(yaw/-57.29577)*sin((pitch/57.29577)+1.57079633))*.1)+char_z;
		char_y = (cos((pitch/57.29577)+1.57079633)*-.1)+char_y;
	}

	if (GetAsyncKeyState(0x53))
	{
		char_x = ((sin(yaw/-57.29577)*sin((pitch/57.29577)+1.57079633))*-.1)+char_x;
		char_z = ((cos(yaw/-57.29577)*sin((pitch/57.29577)+1.57079633))*-.1)+char_z;
		char_y = (cos((pitch/57.29577)+1.57079633)*.1)+char_y;
	}

	if (GetAsyncKeyState(0x41))
	{
		char_x = (sin((yaw-90)/-57.29577)*.1)+char_x;
		char_z = (cos((yaw-90)/-57.29577)*.1)+char_z;
	}

	if (GetAsyncKeyState(0x44))
	{
		char_x = (sin((yaw-90)/-57.29577)*-.1)+char_x;
		char_z = (cos((yaw-90)/-57.29577)*-.1)+char_z;
	}

	if (GetAsyncKeyState(0x49)) {testTri.p1.y+=.1;}
	if (GetAsyncKeyState(0x4A)) {testTri.p1.x-=.1;}
	if (GetAsyncKeyState(0x4B)) {testTri.p1.y-=.1;}
	if (GetAsyncKeyState(0x4C)) {testTri.p1.x+=.1;}

	glutPassiveMotionFunc(PassiveMotion);
	glutMotionFunc(PassiveMotion);
	glutMouseFunc(MousePressed);

	if (buttons[GLUT_LEFT_BUTTON] == GLUT_DOWN)
	{
		if (Mouse_Press==false)
		{
			mouse_x_origin=mouse_x;
			mouse_y_origin=mouse_y;
		}

		yaw=yaw+((mouse_x-mouse_x_origin)/2.0);
		pitch=pitch-((mouse_y-mouse_y_origin+1)/2.0);

		screen_pos_x = glutGet((GLenum)GLUT_WINDOW_X);
		screen_pos_y = glutGet((GLenum)GLUT_WINDOW_Y);

		glutWarpPointer((screen_pos_x+mouse_x_origin)-8,(screen_pos_y-mouse_y_origin)-30);

		Mouse_Press=true;
	}
	else
	{
		Mouse_Press=false;
	}

	testTri.setCtx();
	
	//testCube.set_values(0,0,-200,10);

	testCube.draw();

	testCube.addPitch(0.01);

	testTri.draw();

	glutSwapBuffers();

	
}

void initialize () 
{
    glMatrixMode(GL_PROJECTION);												// select projection matrix
    glViewport(0, 0, win.width, win.height);									// set the viewport
    glMatrixMode(GL_PROJECTION);												// set matrix mode
    glLoadIdentity();															// reset projection matrix
    GLfloat aspect = (GLfloat) win.width / win.height;
	gluPerspective(win.field_of_view_angle, aspect, win.z_near, win.z_far);		// set up a perspective projection matrix
    glMatrixMode(GL_MODELVIEW);													// specify which matrix is the current matrix
    glShadeModel( GL_SMOOTH );
    glClearDepth( 1.0f );														// specify the clear value for the depth buffer
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );						// specify implementation-specific hints
	glClearColor(1.0, 1.0, 1.0, 1.0);	                                        // specify clear values for the color buffers	

}

void keyboard ( unsigned char key, int mousePositionX, int mousePositionY )		
{ 
  switch ( key ) 
  {
    case KEY_ESCAPE:        
      exit ( 0 );   
      break;      

    default:      
      break;
  }
}



int main(int argc, char **argv) 
{
	// set window values
	win.width = 640;
	win.height = 480;
	win.title = "3d_test";
	win.field_of_view_angle = 90;
	win.z_near = 1.0f;
	win.z_far = 10000.0f;

	// initialize and run program
	glutInit(&argc, argv);                                      // GLUT initialization
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );  // Display Mode
	glutInitWindowSize(win.width,win.height);					// set window sizes
	glutCreateWindow(win.title);								// create Window
	glutDisplayFunc(display);									// register Display Function
	glutIdleFunc( display );									// register Idle Function
    glutKeyboardFunc( keyboard );								// register Keyboard Handler

	testCube.setPos(0,0,100);
	testCube.setSize(40,20,20);
	testCube.setPitch(0);

	testTri.setTri(nVERTEX(0,0,0), nVERTEX(100,0,-100), nVERTEX(0,100,-100));
	testTri.setInt(nVERTEX(40,40,-50), nVERTEX(40,40,-150));
	testTri.setCtx();

	testPoint.setPos(nVERTEX(0,100,0));
	testPoint.setSize(20);

	//glutSetCursor(GLUT_CURSOR_NONE);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	initialize();
	glutMainLoop();												// run GLUT mainloop
	return 0;
}

void PassiveMotion(int x,int y)
{
	mouse_x=x;
	mouse_y=y*-1;	
}

void MousePressed(int button, int state, int x, int y) 
{
	buttons[button] = state; 
}


