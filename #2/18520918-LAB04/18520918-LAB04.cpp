// 18520918-LAB03.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <windows.h>
#include <iostream>
#include "include/GL/GL.H"
#include "include/GL/glut.h"
#include "include/GL/GLU.H"
#define K_MAT_RED 0
#define K_MAT_GREEN 1
#define K_MAT_BLUE 2
#define K_MAT_YELLOW 3
#define K_MAT_PINK 4

GLfloat g_box;
GLfloat g_sphere;
GLfloat g_cylinder;
GLfloat g_pyramid;

void DrawCoordinate()
{
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(10.0, 0.0, 0.0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 10.0, 0.0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 10.0);
    glEnd();

    glEnable(GL_LIGHTING);
}

GLuint MakeCube(const float& size)
{
    GLuint dp_list;
    dp_list = glGenLists(1);
    glNewList(dp_list, GL_COMPILE);
    glBegin(GL_QUADS);
    // Front Face
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(-size, -size, size);
    glVertex3f(size, -size, size);
    glVertex3f(size, size, size);
    glVertex3f(-size, size, size);
    // Back Face
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(-size, -size, -size);
    glVertex3f(-size, size, -size);
    glVertex3f(size, size, -size);
    glVertex3f(size, -size, -size);
    // Top Face
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(-size, size, -size);
    glVertex3f(-size, size, size);
    glVertex3f(size, size, size);
    glVertex3f(size, size, -size);
    // Bottom Face
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(-size, -size, -size);
    glVertex3f(size, -size, -size);
    glVertex3f(size, -size, size);
    glVertex3f(-size, -size, size);
    // Right face
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(size, -size, -size);
    glVertex3f(size, size, -size);
    glVertex3f(size, size, size);
    glVertex3f(size, -size, size);
    // Left Face
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(-size, -size, -size);
    glVertex3f(-size, -size, size);
    glVertex3f(-size, size, size);
    glVertex3f(-size, size, -size);

    glEnd();
    glEndList();
    return dp_list;
}

GLuint MakeSphere(const float& radius)
{
    GLuint dp_list;
    dp_list = glGenLists(1);
    glNewList(dp_list, GL_COMPILE);
    glutSolidSphere(radius, 64, 64);
    glEndList();

    return dp_list;
}

GLuint MakeCylinder(const float& radius, const float& length)
{
    GLuint dp_list;
    dp_list = glGenLists(1);
    glNewList(dp_list, GL_COMPILE);
    GLUquadricObj* quadratic_obj;
    quadratic_obj = gluNewQuadric();
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(quadratic_obj, radius, radius, length, 32, 32);
    glEndList();
    return dp_list;
}

GLuint MakePyramid(const float& size, const float& height)
{
    GLuint dp_list;
    dp_list = glGenLists(1);
    glNewList(dp_list, GL_COMPILE);
    double half_size = size * 0.5;
    glBegin(GL_TRIANGLES);
    //Front face
    glNormal3f(0.0, 0.0, 1.0f);
    glVertex3f(0.0f, height, 0.0f);
    glVertex3f(-half_size, 0, half_size);
    glVertex3f(half_size, 0, half_size);

    //left face
    glNormal3f(-1.0, 0.0, 0.0f);
    glVertex3f(0.0, height, 0.0);
    glVertex3f(-half_size, 0.0, -half_size);
    glVertex3f(-half_size, 0.0, half_size);

    //back face
    glNormal3f(0.0, 0.0, -1.0f);
    glVertex3f(0.0f, height, 0.0f);
    glVertex3f(-half_size, 0, -half_size);
    glVertex3f(half_size, 0, -half_size);

    //Right face
    glNormal3f(1.0, 0.0, 0.0f);
    glVertex3f(0.0, height, 0.0);
    glVertex3f(half_size, 0.0, -half_size);
    glVertex3f(half_size, 0.0, half_size);
    glEnd();

    //Bottom face
    glBegin(GL_QUADS);
    glNormal3f(0.0, -1.0, 0.0f);
    glVertex3f(half_size, 0.0, half_size);
    glVertex3f(half_size, 0.0, -half_size);
    glVertex3f(-half_size, 0.0, -half_size);
    glVertex3f(-half_size, 0.0, half_size);
    glEnd();
    glEndList();

    return dp_list;
}




void SetMaterialColor(GLfloat ambient[4], GLfloat diff_use[4])
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff_use);
}

void SetMaterialColor(const int& type)
{
    GLfloat ambien[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat diff_use[] = { 0.0, 0.0, 0.0, 1.0 };
    switch (type)
    {
    case K_MAT_RED:
    {
        ambien[0] = 1.0f;
        diff_use[0] = 1.0f;
    }
    break;
    case K_MAT_GREEN:
    {
        ambien[1] = 1.0f;
        diff_use[1] = 1.0f;
    }
    break;
    case K_MAT_BLUE:
    {
        ambien[2] = 1.0f;
        diff_use[2] = 1.0f;
    }
    break;
    case K_MAT_YELLOW:
    {
        ambien[0] = 1.0f;
        ambien[1] = 1.0f;
        diff_use[0] = 1.0f;
        diff_use[1] = 1.0f;
    }
    break;
    case K_MAT_PINK:
    {
        ambien[0] = 1.0f;
        ambien[2] = 1.0f;
        diff_use[0] = 1.0f;
        diff_use[1] = 1.0f;
    }
    break;
    default:
    {
        ambien[0] = 1.0f;
        ambien[1] = 1.0f;
        ambien[2] = 1.0f;
        diff_use[0] = 1.0f;
        diff_use[1] = 1.0f;
        diff_use[2] = 1.0f;
    }
    break;
    }

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambien);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff_use);
}

void ReShape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float ratio = (float)width / (float)height;
    gluPerspective(45.0, ratio, 1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void RendenScene()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(5.0, 5.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glPushMatrix();
    DrawCoordinate();
    SetMaterialColor(K_MAT_RED);
    glCallList(g_box);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.0, 0.0, 0.0);
    SetMaterialColor(K_MAT_YELLOW);
    glCallList(g_sphere);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.0, 0.0, 0.0);
    SetMaterialColor(K_MAT_BLUE);
    glCallList(g_cylinder);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.0, -3.0);
    GLfloat ambien[] = { 0.5, 0.3, 0.7, 1.0 };
    GLfloat diff_use[] = { 0.5, 0.2, 0.4, 1.0 };
    SetMaterialColor(ambien, diff_use);
    glCallList(g_pyramid);
    glPopMatrix();

    glFlush();
}

void Init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat light_pos[] = { 0.0, 0.0, 1.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

    GLfloat ambient[] = { 1.0, 1.0, 0.0, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);

    GLfloat diff_use[] = { 0.5, 0.5, 0.0, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff_use);

    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);

    GLfloat shininess = 50.0f;
    glMateriali(GL_FRONT, GL_SHININESS, shininess);

    g_box = MakeCube(1);
    g_sphere = MakeSphere(1);
    g_cylinder = MakeCylinder(1.0,3.0);
    g_pyramid = MakePyramid(2.0,4.0);
    
}

int main()
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("18520918-LAB-04");

    Init();
    glutReshapeFunc(ReShape);
    glutDisplayFunc(RendenScene);

    glutMainLoop();

}

