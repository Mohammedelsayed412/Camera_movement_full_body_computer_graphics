# Assignment 2 report.

### Name: Mohammed Elsayed Sayed &emsp;&emsp;Sec: 2&emsp;&emsp; BN: 17
## <br /> ***Implementaion***
### **I follow up my body implementaion and apply the camera movement on it and connect the vertica rotaion with mouse clicks and move.**



## **Code:-**

### **Right_Function :**
```cpp

void Right()
{
		rotatePoint(up,-0.1,eye);
}
```
### **Left_Function :**
```cpp
void Left()
{
	rotatePoint(up,0.1,eye);
}
```
### **moveForward_Function :**
```cpp

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
```
### **moveBckward_Function :**
```cpp

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

```
### **Up_Function :**
```cpp
void Up()
{
	look_dir[0] = center[0] - eye[0];
	look_dir[1] = center[1] - eye[1];
	look_dir[2] = center[2] - eye[2];
	crossProduct(up,look_dir,horizontal_dir);
	normalize(horizontal_dir);
	rotatePoint(horizontal_dir,0.1,eye);
	rotatePoint(horizontal_dir,0.1,up);
}
```
### **Down_Function :**
```cpp
void Down()
{	
	look_dir[0] = center[0] - eye[0];
	look_dir[1] = center[1] - eye[1];
	look_dir[2] = center[2] - eye[2];
	crossProduct(up,look_dir,horizontal_dir);
	normalize(horizontal_dir);
	rotatePoint(horizontal_dir,-0.1,eye);
	rotatePoint(horizontal_dir,-0.1,up);
}
```
### **mouse_Function :**
```cpp
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
```
### **motion_Function :**
```cpp
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
```
## <br /> ***Ressults***
### **This the output of camera move :**
![picture](imgs/11.png)
![picture](imgs/12.png)
![picture](imgs/13.png)
![picture](imgs/14.png)
![picture](imgs/15.png)
![picture](imgs/16.png)
![picture](imgs/17.png)
![picture](imgs/18.png)
![picture](imgs/19.png)