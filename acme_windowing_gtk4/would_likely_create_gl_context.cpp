// Created by camilo on 8/11/25 (2025-08-11) 00:01 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>

/* X11 + GLX headers */
#include <X11/Xlib.h>
#include <GL/glx.h>

/* EGL headers */
#include <EGL/egl.h>
#include <EGL/eglext.h>

static bool file_exists(const char *path) {
    struct stat st;
    return stat(path, &st) == 0;
}

static bool probe_glx(void) {
    Display *dpy = XOpenDisplay(NULL);
    if (!dpy) return false;

    int fbcount;
    static int attribs[] = {
        GLX_X_RENDERABLE, True,
        GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
        GLX_RENDER_TYPE,   GLX_RGBA_BIT,
        GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
        GLX_RED_SIZE,      8,
        GLX_GREEN_SIZE,    8,
        GLX_BLUE_SIZE,     8,
        GLX_ALPHA_SIZE,    8,
        None
    };
    GLXFBConfig *fbc = glXChooseFBConfig(dpy, DefaultScreen(dpy), attribs, &fbcount);
    if (!fbc) { XCloseDisplay(dpy); return false; }

    XVisualInfo *vi = glXGetVisualFromFBConfig(dpy, fbc[0]);
    if (!vi) { XFree(fbc); XCloseDisplay(dpy); return false; }

    GLXContext ctx = glXCreateContext(dpy, vi, 0, GL_TRUE);
    XFree(vi);
    if (!ctx) { XFree(fbc); XCloseDisplay(dpy); return false; }

    glXDestroyContext(dpy, ctx);
    XFree(fbc);
    XCloseDisplay(dpy);
    return true;
}

static bool probe_egl(void) {
    EGLDisplay dpy = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (dpy == EGL_NO_DISPLAY) return false;

    if (!eglInitialize(dpy, NULL, NULL)) {
        eglTerminate(dpy);
        return false;
    }

    EGLint attribs[] = {
        EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
        EGL_NONE
    };
    EGLConfig cfg;
    EGLint n;
    if (!eglChooseConfig(dpy, attribs, &cfg, 1, &n) || n < 1) {
        eglTerminate(dpy);
        return false;
    }

    if (!eglBindAPI(EGL_OPENGL_API)) {
        eglTerminate(dpy);
        return false;
    }

    EGLContext ctx = eglCreateContext(dpy, cfg, EGL_NO_CONTEXT, NULL);
    if (ctx == EGL_NO_CONTEXT) {
        eglTerminate(dpy);
        return false;
    }

    eglDestroyContext(dpy, ctx);
    eglTerminate(dpy);
    return true;
}


static gboolean gdk_can_use_gl(void) {
    GError * pgerror = NULL;
    GdkDisplay *display = gdk_display_get_default();
    if (!display) return FALSE;

    GdkGLContext *ctx = gdk_display_create_gl_context(display, &pgerror);
    if (!ctx) {
        if (pgerror)
        {
            g_clear_error(&pgerror);
            pgerror = nullptr;
        }
        return FALSE;
    }
    if (pgerror)
    {
        g_clear_error(&pgerror);
        pgerror = nullptr;
    }


    if (!gdk_gl_context_realize(ctx, &pgerror)) {
        g_object_unref(ctx);
        if (pgerror)
        {
            g_clear_error(&pgerror);
            pgerror = nullptr;
        }
        return FALSE;
    }
    if (pgerror)
    {
        g_clear_error(&pgerror);
        pgerror = nullptr;
    }

    g_object_unref(ctx);
    return TRUE;
}

bool wouldnt_create_gl_context()
{
    /* No X11 or Wayland display at all */
    if (!getenv("DISPLAY") && !getenv("WAYLAND_DISPLAY"))
        return true;

    /* Detect SSH without X forwarding */
    if (getenv("SSH_CONNECTION") && !getenv("DISPLAY"))
        return true;

    /* No DRM/GPU device available (basic check) */
    if (!file_exists("/dev/dri") && !file_exists("/dev/nvidiactl"))
        return true;

    /* Probe for GL support */
    if (getenv("WAYLAND_DISPLAY") && !probe_egl()) return true; /* Wayland+EGL works */
    if (getenv("DISPLAY") && !probe_glx()) return true;   /* X11+GLX works */

    return !gdk_can_use_gl(); /* No working GL backend */
}