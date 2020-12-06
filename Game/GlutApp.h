#ifndef GlutApp_h
#define GlutApp_h
#include <string>
#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
#include <string>
class GlutApp
{
    int width;
    int height;

    const char *title;

    bool fullscreen;

    // Prevent derived classes from defining these constructors
    GlutApp() {}
    GlutApp(const GlutApp &) {}

    static void glutDisplayCB();

    static void glutKeyDownCB(unsigned char, int, int);
    static void glutKeyUpCB(unsigned char, int, int);
    static void glutSpecialKeyDownCB(int, int, int);
    static void glutSpecialKeyUpCB(int, int, int);

    static void glutMouseCB(int, int, int, int);
    static void glutMotionCB(int, int);

    static void glutResizeCB(int, int);

    static void glutIdleCB();

    friend void windowToScene(float &, float &);
    friend void renderText(
        std::string text,
        float x,
        float y,
        void *font = GLUT_BITMAP_HELVETICA_18,
        float r = 1,
        float g = 1,
        float b = 1)
    {
        glColor3f(r, g, b);
        float offset = 0;
        for (int i = 0; i < text.length(); i++)
        {
            glRasterPos2f(x + offset, y);
            glutBitmapCharacter(font, text[i]);
            int w = glutBitmapWidth(font, text[i]);
            offset += ((float)w / 1366) * 2;
        }
    }

protected:
    GlutApp(int, char **, int = 600, int = 600, const char *title = "GLUT Application");

public:
    void run();
    void redraw();
    void toggleFullScreen();

    virtual void draw() const = 0;

    virtual void keyDown(unsigned char, float, float) {}
    virtual void keyUp(unsigned char, float, float) {}

    virtual void specialKeyDown(int, float, float) {}
    virtual void specialKeyUp(int, float, float) {}

    virtual void leftMouseDown(float, float) {}
    virtual void rightMouseDown(float, float) {}
    virtual void leftMouseUp(float, float) {}
    virtual void rightMouseUp(float, float) {}

    virtual void drag(float, float) {}

    virtual void idle() {}

    virtual ~GlutApp() {}
};

#endif
