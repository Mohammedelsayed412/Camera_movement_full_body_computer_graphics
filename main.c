#include <GL/glut.h>
#include <math.h>

static int shoulder = 0, shoulder2 = 0, elbow = 0, finger1Base = 0, finger1Up = 0, finger2Base = 0, finger2Up = 0, 
         finger3Base = 0, finger3Up = 0, finger4Base = 0, finger4Up = 0, rhip = 0, rhip2 = 0, rknee = 0, lknee = 0,
			lhip = 0, lhip2 = 0 ,hand_up = 0,around=0 ;
double eye[] = { 0, 0, -20 };
double center[] = { 0, 0, -5 };
double up[] = { 0, 1, 0 };
double horizontal_dir[] = {0,0,0};
double look_dir[]= {0,0,};
double direction[]={0,0,0};
float speed = 0.05;

int moving, startx, starty;


GLfloat angle = 0.0;   /* in degrees */
GLfloat angle2 = 0.0;  

void init(void)
{
    glMatrixMode(GL_PROJECTION);
	gluPerspective(65.0, (GLfloat)1024 / (GLfloat)869, 1.0, 60.0);
}

void crossProduct(double a[], double b[], double c[])
{
	c[0] = a[1] * b[2] - a[2] * b[1];
	c[1] = a[2] * b[0] - a[0] * b[2];
	c[2] = a[0] * b[1] - a[1] * b[0];
}

void normalize(double a[])
{
	double norm;
	norm = a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
	norm = sqrt(norm);
	a[0] /= norm;
	a[1] /= norm;
	a[2] /= norm;
}

void rotatePoint(double a[], double theta, double p[])
{

	double temp[3];
	temp[0] = p[0];
	temp[1] = p[1];
	temp[2] = p[2];

	temp[0] = -a[2] * p[1] + a[1] * p[2];
	temp[1] = a[2] * p[0] - a[0] * p[2];
	temp[2] = -a[1] * p[0] + a[0] * p[1];

	temp[0] *= sin(theta);
	temp[1] *= sin(theta);
	temp[2] *= sin(theta);

	temp[0] += (1 - cos(theta))*(a[0] * a[0] * p[0] + a[0] * a[1] * p[1] + a[0] * a[2] * p[2]);
	temp[1] += (1 - cos(theta))*(a[0] * a[1] * p[0] + a[1] * a[1] * p[1] + a[1] * a[2] * p[2]);
	temp[2] += (1 - cos(theta))*(a[0] * a[2] * p[0] + a[1] * a[2] * p[1] + a[2] * a[2] * p[2]);

	temp[0] += cos(theta)*p[0];
	temp[1] += cos(theta)*p[1];
	temp[2] += cos(theta)*p[2];

	p[0] = temp[0];
	p[1] = temp[1];
	p[2] = temp[2];

}

void Left()
{
	// implement camera rotation arround vertical window screen axis to the left
	
	rotatePoint(up,0.1,eye);
	
	
	// used by mouse and left arrow
}

void Right()
{
	// implement camera rotation arround vertical window screen axis to the right
	rotatePoint(up,-0.1,eye);
	// used by mouse and right arrow
}

void Up()
{
	// implement camera rotation arround horizontal window screen axis +ve

	look_dir[0] = center[0] - eye[0];
	look_dir[1] = center[1] - eye[1];
	look_dir[2] = center[2] - eye[2];
	crossProduct(up,look_dir,horizontal_dir);
	normalize(horizontal_dir);
	rotatePoint(horizontal_dir,0.1,eye);
	rotatePoint(horizontal_dir,0.1,up);
	// used by up arrow
}

void Down()
{	
	// implement camera rotation arround horizontal window screen axis 
	look_dir[0] = center[0] - eye[0];
	look_dir[1] = center[1] - eye[1];
	look_dir[2] = center[2] - eye[2];
	crossProduct(up,look_dir,horizontal_dir);
	normalize(horizontal_dir);
	rotatePoint(horizontal_dir,-0.1,eye);
	rotatePoint(horizontal_dir,-0.1,up);
	// used by down arrow
}

void moveForward()
{
	direction[0] = center[0] - eye[0];
	direction[1] = center[1] - eye[1];
	direction[2] = center[2] - eye[2];

	eye[0]    += direction[0] * speed;
	eye[1]    += direction[1] * speed;
	eye[2]    += direction[2] * speed;

	center[0] += direction[0] * speed;
	center[1] += direction[1] * speed;
	center[2] += direction[2] * speed;


}

void moveBack()
{
	direction[0] = center[0] - eye[0];
	direction[1] = center[1] - eye[1];
	direction[2] = center[2] - eye[2];

	eye[0]    -= direction[0] * speed;
	eye[1]    -= direction[1] * speed;
	eye[2]    -= direction[2] * speed;

	center[0] -= direction[0] * speed;
	center[1] -= direction[1] * speed;
	center[2] -= direction[2] * speed;
}


void finger (float x , float y , int base , int up)
{  glPushMatrix();
   glTranslatef(1.0, x, y);
   glRotatef((GLfloat)base, 0.0, 0.0, 1.0);
   glTranslatef(0.2, 0.0, 0.0);
   glPushMatrix();
   glScalef(0.4, 0.2, 0.1);
   glutSolidCube(1);
   glPopMatrix();

   glTranslatef(0.2, 0.0, 0.0);
   glRotatef((GLfloat)up, 0.0, 0.0, 1.0);
   glTranslatef(0.2, 0.0, 0.0);
   glPushMatrix();
   glScalef(0.4, 0.2, 0.1);
   glutSolidCube(1);
   glPopMatrix();
   glPopMatrix();
}
void hand(int x , int y,int z)
{  
   
   glColor3f(0.5, 0.5, 0.2); 
   glTranslatef(1.5,1.275,0);
   glScalef(0.5,0.5,0.4);
   glTranslatef (-1.0, 0.0, 0.0);
   glRotatef ((GLfloat) shoulder2, x, 0.0, 0);
   glRotatef ((GLfloat) shoulder, 0.0, z, 0.0);
   glRotatef(hand_up,0,0,1);
   glRotatef(-90,0,0,1);
   glTranslatef (1.0, 0.0, 0.0);
   glPushMatrix();
   glScalef (2.0, 0.9, 1.0);
   glutWireCube (1.0);
   glPopMatrix();
   glTranslatef (1.0, 0.0, 0.0);
   glRotatef ((GLfloat) elbow, 0.0, y, 0);
   glTranslatef (1.0, 0.0, 0.0);
   glPushMatrix();
   glScalef (2.0, 0.9, 1.0);
   glutWireCube (1.0);
   glPopMatrix();
   
}

void Leg(int leg , int knee,int out )
{
   glPushMatrix();
   glTranslatef (-0.5, -1.5, 0.0);
   glRotatef(out,0,0,1);
   glRotatef (leg, 1.0, 0.0, 0);
   glTranslatef (0, -0.5, 0.0);
   glPushMatrix();
   glScalef (0.5, 1,0.6);
   glutWireCube (1.0);
   glPopMatrix();
   glTranslatef (0, -0.5, 0.0);
   glRotatef (knee, 1.0, 0.0, 0);
   glTranslatef (0, -0.5, 0.0);
   glPushMatrix();
   glScalef (0.5, 1,0.6);
   glutWireCube (1.0);
   glPopMatrix();
   glTranslatef (0, -0.65, 0.0);
   glPushMatrix();
   glScalef (0.5, 0.3,0.8);
   glutSolidCube (1.0);
   glPopMatrix();
   glPopMatrix();
} 

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT );
   	glClearColor(0.0, 0.0, 0.0, 0.0);
	glRotatef(angle2, 1.0, 0.0, 0.0);
	glRotatef(angle, 0.0, 1.0, 0.0);
	glShadeModel(GL_FLAT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);

	//////.....body....../////
	glPushMatrix();
	glRotatef(angle2, 1.0, 0.0, 0.0);
	glRotatef(angle, 0.0, 1.0, 0.0);
	glTranslatef(0,0,1);
	glRotatef(around,0,1,0);
	glTranslatef(0,0,-1);
	//////.....hand....../////
	glTranslatef(0,0.5,0);
	glPushMatrix();
	hand(1,1,1);
	finger(-0.35,0,finger1Base,finger1Up);
	finger(0.35,0,finger2Base,finger2Up);
	finger(0.35,-0.45,finger3Base,finger3Up);
	finger(0.35,0.45,finger4Base,finger4Up);
	glPopMatrix();
	glPushMatrix();
	glRotatef(-180,0,-1,0);
	hand(-1,-1,-1);
	finger(-0.35,0,finger1Base,finger1Up);
	finger(0.35,0,finger2Base,finger2Up);
	finger(0.35,-0.45,finger3Base,finger3Up);
	finger(0.35,0.45,finger4Base,finger4Up);
	glPopMatrix();
	//////.....head....../////
	glPushMatrix();
	glTranslatef(0,2.25,0);
	glutSolidSphere(0.5, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glScalef (1.5,3, 0.6);
	glutWireCube (1.0);
	glPopMatrix();
	/////........leg.......////
	glPushMatrix();
	Leg(rhip,rknee,rhip2);
	glPopMatrix();
	glPushMatrix();
	glRotatef(180,0,1,0);   
	Leg(lhip,lknee,lhip2);
	glPopMatrix();
	glPopMatrix();
	//////.....body_end....../////
	glutSwapBuffers();
}

void specialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT: Left(); break;
	case GLUT_KEY_RIGHT: Right(); break;
	case GLUT_KEY_UP:    Up(); break;
	case GLUT_KEY_DOWN:  Down(); break;
	}

	glutPostRedisplay();
}



void keyboard(unsigned char key, int x, int y)
{
   switch (key)
   {

	case 'f':
		moveForward();
		glutPostRedisplay();
		break;
	case 'b':
		moveBack();
		glutPostRedisplay();
		break;
	/////.....Assignment2 buttons..../////
   case 's':
      if(shoulder < 90){
      shoulder = (shoulder + 5) % 360;
      glutPostRedisplay();}
      
      break;
   case 'S':
      if(shoulder>-90){
      shoulder = (shoulder - 5) % 360;
      glutPostRedisplay();}
      break;

   case 'w':
      if(hand_up < 90){
      hand_up = (hand_up + 5) % 360;
      glutPostRedisplay();}
      
      break;
   case 'W':
      if(hand_up>-90){
      hand_up = (hand_up - 5) % 360;
      glutPostRedisplay();}
      break;


   case 'i':
      if(shoulder2 >-90){
      shoulder2 = (shoulder2 - 5) % 360;
      glutPostRedisplay();}
      
      break;
   case 'I':
      if(shoulder2<0){
      shoulder2 = (shoulder2 + 5) % 360;
      glutPostRedisplay();}
      break;

   case 'E':
   if(elbow <  160){
      elbow = (elbow + 5) % 360;
      glutPostRedisplay();
      break;
   }
   case 'e':
   if(elbow>-120){
      elbow = (elbow - 5) % 360;
      glutPostRedisplay();
   }
      break;
   
   
   case 't':
   if(finger1Base<90){
      finger1Base = (finger1Base + 5) % 360;
      glutPostRedisplay();
   }
      break;
   case 'T':
   if(finger1Base<=90&&finger1Base>0){
      finger1Base = (finger1Base - 5) % 360;
      glutPostRedisplay();}
      break;
   
   
   case 'g':
   if(finger1Up<90){
      finger1Up = (finger1Up + 5) % 360;
      glutPostRedisplay();
   }
      break;
   case 'G':
   if(finger1Up<=90&&finger1Up>0){
      finger1Up = (finger1Up - 5) % 360;
      glutPostRedisplay();}
      break;
   
   //*******************************
   case 'z':
      if(finger2Base<90){

      finger2Base = (finger2Base + 5) % 360;
      glutPostRedisplay();}
      break;
   case 'Z':
      if(finger2Base<=90&&finger2Base>0){

      finger2Base = (finger2Base - 5) % 360;
      glutPostRedisplay();}
      break;
   
   case 'x':
      if(finger2Up<90){

      finger2Up = (finger2Up + 5) % 360;
      glutPostRedisplay();}
      break;
   case 'X':
      if(finger2Up<=90&&finger2Up>0){

      finger2Up = (finger2Up - 5) % 360;
      glutPostRedisplay();}
      break;
   
   //*******************************
   case 'c':
      if(finger3Base<90){

      finger3Base = (finger3Base + 5) % 360;
      glutPostRedisplay();}
      break;
   case 'C':
      if(finger3Base<=90&&finger3Base>0){

      finger2Base = (finger3Base - 5) % 360;
      glutPostRedisplay();}
      break;
   case 'v':
      if(finger3Up<90){

      finger3Up = (finger3Up + 5) % 360;
      glutPostRedisplay();}
      break;
   case 'V':
      if(finger3Up<=90&&finger3Up>0){

      finger3Up = (finger3Up - 5) % 360;
      glutPostRedisplay();}
      break;
   
   //*******************************
   case 'a':
      if(finger4Base<90){

      finger4Base = (finger4Base + 5) % 360;
      glutPostRedisplay();}
      break;
   case 'A':
      if(finger4Base<=90&&finger4Base>0){

      finger4Base = (finger4Base - 5) % 360;
      glutPostRedisplay();}
      break;
   
   case 'n':
      if(finger4Up<90){

      finger4Up = (finger4Up + 5) % 360;
      glutPostRedisplay();}
      break;
   case 'N':
      if(finger4Up<=90&&finger4Up>0){

      finger4Up = (finger4Up - 5) % 360;
      glutPostRedisplay();}
      break;
   //*******************************
   case 'l':
      if(rhip<90&&lhip==0&&lknee==0&&lhip2==0){
      rhip = (rhip + 5) % 360;
      glutPostRedisplay();}
      break;
   case 'L':
      if(rhip<=90&&rhip>=-90&&lhip==0&&lknee==0&&lhip2==0){

         rhip = (rhip - 5) % 360;
         glutPostRedisplay();}
      
      break;
   case 'P':
      if(lhip<90&&rhip==0&&rknee==0&&rhip2==0){
      lhip = (lhip + 5) % 360;
      glutPostRedisplay();}
      break;
   case 'p':
      if(lhip<=90&&lhip>=-90&&rhip==0&&rknee==0&&rhip2==0){

         lhip = (lhip - 5) % 360;
         glutPostRedisplay();}
      
      break;
   case 'o':
      if(rknee<90&&lhip==0&&lknee==0&&lhip2==0){
      rknee = (rknee + 5) % 360;
      glutPostRedisplay();}
      break;
   case 'O':
      if(rknee<=90&&rknee>=0&&lhip==0&&lknee==0&&lhip2==0){

         rknee = (rknee - 5) % 360;
         glutPostRedisplay();}
      
      break;
   case 'u':
      if(lknee>-90&&rhip==0&&rknee==0&&rhip2==0){
      lknee = (lknee - 5) % 360;
      glutPostRedisplay();}
      break;
   case 'U':
      if(lknee>=-90&&lknee<=0&&rhip==0&&rknee==0&&rhip2==0){

         lknee = (lknee + 5) % 360;
         glutPostRedisplay();}
      break;

   case 'q':
      if(rhip2>-90&&lhip==0&&lknee==0&&lhip2==0){
      rhip2 = (rhip2 - 5) % 360;
      glutPostRedisplay();}
      break;
   case 'Q':
      if(rhip2>=-90&&rhip2<=0&&lhip==0&&lknee==0&&lhip2==0){

         rhip2 = (rhip2 + 5) % 360;
         glutPostRedisplay();}
      break;

   case 'm':
      if(lhip2>-90&&rhip==0&&rknee==0&&rhip2==0){
      lhip2 = (lhip2 - 5) % 360;
      glutPostRedisplay();}
      break;
   case 'M':
      if(lhip2>=-90&&lhip2<=0&&rhip==0&&rknee==0&&rhip2==0){

         lhip2 = (lhip2 + 5) % 360;
         glutPostRedisplay();}
      break;

   case '0':
      
      around = (around - 5) % 360;
      glutPostRedisplay();
      break;
   case '1':
      

         around = (around + 5) % 360;
         glutPostRedisplay();
      break;



   case 27:
      exit(0);
      break;
   default:
      break;
   }
}

static void mouse(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON) {
	  
    if (state == GLUT_DOWN) {	
      Right();
      moving = 1;
	  glutPostRedisplay();
    }
    if (state == GLUT_UP) {
      moving = 0;
	  
    }
  }
  if (button == GLUT_RIGHT_BUTTON) {
	  
    if (state == GLUT_DOWN) {	
      Left();
      moving = 2;
	  glutPostRedisplay();
    }
    if (state == GLUT_UP) {
      moving = 0;
	  
    }
  }
}


static void motion(int x, int y)
{
  if (moving==1) {
     Right();
    glutPostRedisplay();}
   if (moving==2) {
     Left();
    glutPostRedisplay();
   
  }
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("body");
	init();
	glutMouseFunc(mouse);
    glutMotionFunc(motion);
	glutDisplayFunc(display);
    	glutSpecialFunc(specialKeys);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
	return 0;
}
