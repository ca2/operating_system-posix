#define GL_GLEXT_PROTOTYPES
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>
static Atom
get_atom(Display* dpy, const char* name)
{
    return XInternAtom(dpy, name, False);
}

int main(void)
{
    /* ---------------- X11 ---------------- */

    Display* dpy = XOpenDisplay(NULL);
    if (!dpy)
    {
        fprintf(stderr, "XOpenDisplay failed\n");
        return 1;
    }

    int screen = DefaultScreen(dpy);

   /* ---------------- EGL ---------------- */

   EGLDisplay egl_dpy = eglGetDisplay((EGLNativeDisplayType)dpy);
   if (egl_dpy == EGL_NO_DISPLAY)
   {
      fprintf(stderr, "eglGetDisplay failed\n");
      return 1;
   }

   if (!eglInitialize(egl_dpy, NULL, NULL))
   {
      fprintf(stderr, "eglInitialize failed\n");
      return 1;
   }

    /* Pick a 32-bit ARGB visual */
    XVisualInfo vinfo;
    if (!XMatchVisualInfo(dpy, screen, 32, TrueColor, &vinfo))
    {
        fprintf(stderr, "No 32-bit visual found\n");
        return 1;
    }

    Colormap cmap = XCreateColormap(
        dpy,
        RootWindow(dpy, screen),
        vinfo.visual,
        AllocNone
    );

    XSetWindowAttributes swa = {0};
    swa.colormap = cmap;
    swa.border_pixel = 0;
    swa.event_mask = ExposureMask | StructureNotifyMask | KeyPressMask;

    Window win = XCreateWindow(
        dpy,
        RootWindow(dpy, screen),
        100, 100,
        640, 480,
        0,
        vinfo.depth,
        InputOutput,
        vinfo.visual,
        CWColormap | CWBorderPixel | CWEventMask,
        &swa
    );

    /* Remove window decorations */
    Atom mwm_hints = get_atom(dpy, "_MOTIF_WM_HINTS");
    struct {
        unsigned long flags;
        unsigned long functions;
        unsigned long decorations;
        long input_mode;
        unsigned long status;
    } hints = {
        .flags = 1L << 1, /* MWM_HINTS_DECORATIONS */
        .decorations = 0
    };

    XChangeProperty(
        dpy,
        win,
        mwm_hints,
        mwm_hints,
        32,
        PropModeReplace,
        (unsigned char*)&hints,
        5
    );




    EGLint cfg_attribs[] = {
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,

        EGL_RED_SIZE,   8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE,  8,
        EGL_ALPHA_SIZE, 8,

        EGL_NATIVE_VISUAL_ID, vinfo.visualid,
        EGL_NONE
    };

    EGLConfig cfg;
    EGLint num;
    if (!eglChooseConfig(egl_dpy, cfg_attribs, &cfg, 1, &num) || num != 1)
    {
        fprintf(stderr, "eglChooseConfig failed\n");
        return 1;
    }

   // Get the visual ID from the EGL config
   EGLint visualId2;
   eglGetConfigAttrib(egl_dpy, cfg, EGL_NATIVE_VISUAL_ID, &visualId2);
   printf("EGL config visual ID: {}", visualId2);

   // Get the X11 window's visual
   //auto display = (Display*)pacmewindowingwindow->__x11_Display();
   XWindowAttributes attrs;
   XGetWindowAttributes(dpy, win, &attrs);
   printf("X11 window visual ID: {}", attrs.visual->visualid);

   // They should match!
   if (visualId2 != (EGLint)attrs.visual->visualid) {
      printf("Visual ID mismatch! EGL={} X11={}", visualId2, attrs.visual->visualid);
   }


    if (!eglBindAPI(EGL_OPENGL_API))
    {
        fprintf(stderr, "eglBindAPI failed\n");
        return 1;
    }

    EGLContext ctx = eglCreateContext(
        egl_dpy,
        cfg,
        EGL_NO_CONTEXT,
        NULL
    );

    if (ctx == EGL_NO_CONTEXT)
    {
        fprintf(stderr, "eglCreateContext failed\n");
        return 1;
    }

    EGLSurface surf = eglCreateWindowSurface(
        egl_dpy,
        cfg,
        (EGLNativeWindowType)win,
        NULL
    );

    if (surf == EGL_NO_SURFACE)
    {
        fprintf(stderr, "eglCreateWindowSurface failed\n");
        return 1;
    }


    /* ---------------- OpenGL ---------------- */

    printf("GL_VENDOR   = %s\n", glGetString(GL_VENDOR));
    printf("GL_RENDERER = %s\n", glGetString(GL_RENDERER));
    printf("GL_VERSION  = %s\n", glGetString(GL_VERSION));

    bool running = true;
   float f = 0.f;

   bool bMapped = false;

    while (running)
    {
        while (XPending(dpy))
        {
            XEvent e;
            XNextEvent(dpy, &e);

            if (e.type == KeyPress)
                running = false;
        }


       if (!bMapped)
       {
          bMapped = true;

          XMapWindow(dpy, win);
          XFlush(dpy);


       }


       eglMakeCurrent(egl_dpy, surf, surf, ctx);


       glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

        /* Light blue, translucent */
        glViewport(0, 0, 640, 480);
        glClearColor((sin(f * 2.0f* 3.1415* 0.5) * 0.5 + 0.5) * 0.6 * 0.6f, 0.8f* 0.6f, 1.0f * 0.6f, 0.6f);
        glClear(GL_COLOR_BUFFER_BIT);

        eglSwapBuffers(egl_dpy, surf);
       eglMakeCurrent(egl_dpy, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

        usleep(16667);

       f += 0.016666666;
    }

    /* ---------------- Cleanup ---------------- */

    eglDestroySurface(egl_dpy, surf);
    eglDestroyContext(egl_dpy, ctx);
    eglTerminate(egl_dpy);

    XDestroyWindow(dpy, win);
    XCloseDisplay(dpy);

    return 0;
}
