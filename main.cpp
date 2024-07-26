#include <GL/glut.h>
#include <complex>
#include <vector>
#include <thread>
#include <mutex>
#include <iostream>

const int WIDTH = 800;
const int HEIGHT = 600;
const int MAX_ITER = 1000;
const double ZOOM_IN_FACTOR = 1.2;
const double ZOOM_OUT_FACTOR = 1.0 / ZOOM_IN_FACTOR;

std::vector<std::vector<int>> mandelbrotSet(HEIGHT, std::vector<int>(WIDTH));
std::mutex mtx;
int colorScheme = 0;
double zoomLevel = 1.0;
double offsetX = 0.0, offsetY = 0.0;

int currentRow = 0; 

int mandelbrot(std::complex<double> c) {
    std::complex<double> z = 0;
    int n = 0;
    while (abs(z) <= 2.0 && n < MAX_ITER) {
        z = z * z + c;
        n++;
    }
    return n;
}

void computeMandelbrotRow(int y) {
    for (int x = 0; x < WIDTH; ++x) {
        double scaledX = (x - WIDTH / 2.0 + offsetX * WIDTH) * 4.0 / (WIDTH * zoomLevel);
        double scaledY = (y - HEIGHT / 2.0 + offsetY * HEIGHT) * 4.0 / (HEIGHT * zoomLevel);
        std::complex<double> c(scaledX, scaledY);
        int value = mandelbrot(c);
        {
            std::lock_guard<std::mutex> lock(mtx);
            mandelbrotSet[y][x] = value;
        }
    }
}


void idle();

void computeMandelbrotSet() {
    currentRow = 0; 
    glutIdleFunc(idle); 
}

void idle() {
    if (currentRow < HEIGHT) {
        computeMandelbrotRow(currentRow);
        currentRow++;
        glutPostRedisplay();
    } else {
        glutIdleFunc(NULL); 
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            int value = mandelbrotSet[y][x];
            double t = (double)value / MAX_ITER;
            if (colorScheme == 0) {
                glColor3f(t, t, t);
            } else {
                if (value == MAX_ITER) {
                    bool isEdge = false;
                    for (int dy = -1; dy <= 1; ++dy) {
                        for (int dx = -1; dx <= 1; ++dx) {
                            if (y + dy >= 0 && y + dy < HEIGHT && x + dx >= 0 && x + dx < WIDTH) {
                                if (mandelbrotSet[y + dy][x + dx] < MAX_ITER) {
                                    isEdge = true;
                                    break;
                                }
                            }
                        }
                        if (isEdge) break;
                    }
                    if (isEdge) {
                        glColor3f(1.0, 1.0, 1.0);
                    } else {
                        glColor3f(0.0, 0.0, 0.0);
                    }
                } else {
                    glColor3f(0.0, 0.0, 0.502);
                }
            }
            glVertex2i(x, y);
        }
    }
    glEnd();
    glFlush();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        colorScheme = 1 - colorScheme;
        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y) {
    if (key == '+') {
        zoomLevel *= ZOOM_IN_FACTOR;
        computeMandelbrotSet();
    } else if (key == '-') {
        zoomLevel *= ZOOM_OUT_FACTOR;
        computeMandelbrotSet();
    }
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Multithreaded Mandelbrot Set");
    gluOrtho2D(0, WIDTH, 0, HEIGHT);

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);

    computeMandelbrotSet();

    glutMainLoop();

    return 0;
}
