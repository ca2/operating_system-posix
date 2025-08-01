//
// Created by camilo on 9/10/23.
//
/* Generated by wayland-scanner 1.21.0 */

#ifndef XDG_ACTIVATION_V1_CLIENT_PROTOCOL_H
#define XDG_ACTIVATION_V1_CLIENT_PROTOCOL_H

#include <stdint.h>
#include <stddef.h>
#include "wayland-client.h"

#ifdef  __cplusplus
extern "C" {
#endif

/**
 * @page page_xdg_activation_v1 The xdg_activation_v1 protocol
 * Protocol for requesting activation of surfaces
 *
 * @section page_desc_xdg_activation_v1 Description
 *
 * The way for a client to pass focus to another toplevel is as follows.
 *
 * The client that intends to activate another toplevel uses the
 * xdg_activation_v1.get_activation_token request to get an activation token.
 * This token is then forwarded to the client, which is supposed to activate
 * one of its surfaces, through a separate band of communication.
 *
 * One established way of doing this is through the XDG_ACTIVATION_TOKEN
 * environment variable of a newly launched child process. The child process
 * should unset the environment variable again right after reading it out in
 * order to avoid propagating it to other child processes.
 *
 * Another established way exists for Applications implementing the D-Bus
 * interface org.freedesktop.Application, which should get their token under
 * XDG_ACTIVATION_TOKEN on their platform_data.
 *
 * In general activation tokens may be transferred across clients through
 * means not described in this protocol.
 *
 * The client to be activated will then pass the token
 * it received to the xdg_activation_v1.activate request. The compositor can
 * then use this token to decide how to react to the activation request.
 *
 * The token the activating client gets may be ineffective either already at
 * the time it receives it, for example if it was not focused, for focus
 * stealing prevention. The activating client will have no way to discover
 * the validity of the token, and may still forward it to the to be activated
 * client.
 *
 * The created activation token may optionally get information attached to it
 * that can be used by the compositor to identify the application that we
 * intend to activate. This can for example be used to display a visual hint
 * about what application is being started.
 *
 * Warning! The protocol described in this file is currently in the testing
 * phase. Backward compatible changes may be added together with the
 * corresponding interface version bump. Backward incompatible changes can
 * only be done by creating a ___new major version of the extension.
 *
 * @section page_ifaces_xdg_activation_v1 Interfaces
 * - @subpage page_iface_xdg_activation_v1 - interface for activating surfaces
 * - @subpage page_iface_xdg_activation_token_v1 - an exported activation handle
 * @section page_copyright_xdg_activation_v1 Copyright
 * <pre>
 *
 * Copyright © 2020 Aleix Pol Gonzalez <aleixpol@kde.org>
 * Copyright © 2020 Carlos Garnacho <carlosg@gnome.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 * </pre>
 */
struct wl_seat;
struct wl_surface;
struct xdg_activation_token_v1;
struct xdg_activation_v1;

#ifndef XDG_ACTIVATION_V1_INTERFACE
#define XDG_ACTIVATION_V1_INTERFACE
/**
 * @page page_iface_xdg_activation_v1 xdg_activation_v1
 * @section page_iface_xdg_activation_v1_desc Description
 *
 * A global interface used for informing the compositor about applications
 * being activated or started, or for applications to request to be
 * activated.
 * @section page_iface_xdg_activation_v1_api API
 * See @ref iface_xdg_activation_v1.
 */
/**
 * @defgroup iface_xdg_activation_v1 The xdg_activation_v1 interface
 *
 * A global interface used for informing the compositor about applications
 * being activated or started, or for applications to request to be
 * activated.
 */
extern const struct wl_interface xdg_activation_v1_interface;
#endif
#ifndef XDG_ACTIVATION_TOKEN_V1_INTERFACE
#define XDG_ACTIVATION_TOKEN_V1_INTERFACE
/**
 * @page page_iface_xdg_activation_token_v1 xdg_activation_token_v1
 * @section page_iface_xdg_activation_token_v1_desc Description
 *
 * An object for setting up a token and receiving a token handle that can
 * be passed as an activation token to another client.
 *
 * The object is created using the xdg_activation_v1.get_activation_token
 * request. This object should then be populated with the app_id, surface
 * and serial information and committed. The compositor shall then issue a
 * done happening with the token. In case the request's parameters are invalid,
 * the compositor will provide an invalid token.
 * @section page_iface_xdg_activation_token_v1_api API
 * See @ref iface_xdg_activation_token_v1.
 */
/**
 * @defgroup iface_xdg_activation_token_v1 The xdg_activation_token_v1 interface
 *
 * An object for setting up a token and receiving a token handle that can
 * be passed as an activation token to another client.
 *
 * The object is created using the xdg_activation_v1.get_activation_token
 * request. This object should then be populated with the app_id, surface
 * and serial information and committed. The compositor shall then issue a
 * done happening with the token. In case the request's parameters are invalid,
 * the compositor will provide an invalid token.
 */
extern const struct wl_interface xdg_activation_token_v1_interface;
#endif

#define XDG_ACTIVATION_V1_DESTROY 0
#define XDG_ACTIVATION_V1_GET_ACTIVATION_TOKEN 1
#define XDG_ACTIVATION_V1_ACTIVATE 2


/**
 * @ingroup iface_xdg_activation_v1
 */
#define XDG_ACTIVATION_V1_DESTROY_SINCE_VERSION 1
/**
 * @ingroup iface_xdg_activation_v1
 */
#define XDG_ACTIVATION_V1_GET_ACTIVATION_TOKEN_SINCE_VERSION 1
/**
 * @ingroup iface_xdg_activation_v1
 */
#define XDG_ACTIVATION_V1_ACTIVATE_SINCE_VERSION 1

/** @ingroup iface_xdg_activation_v1 */
static inline void
xdg_activation_v1_set_user_data(struct xdg_activation_v1 *xdg_activation_v1, void *user_data)
{
   wl_proxy_set_user_data((struct wl_proxy *) xdg_activation_v1, user_data);
}

/** @ingroup iface_xdg_activation_v1 */
static inline void *
xdg_activation_v1_get_user_data(struct xdg_activation_v1 *xdg_activation_v1)
{
   return wl_proxy_get_user_data((struct wl_proxy *) xdg_activation_v1);
}

static inline uint32_t
xdg_activation_v1_get_version(struct xdg_activation_v1 *xdg_activation_v1)
{
   return wl_proxy_get_version((struct wl_proxy *) xdg_activation_v1);
}

/**
 * @ingroup iface_xdg_activation_v1
 *
 * Notify the compositor that the xdg_activation object will no longer be
 * used.
 *
 * The child objects created via this interface are unaffected and should
 * be destroyed separately.
 */
static inline void
xdg_activation_v1_destroy(struct xdg_activation_v1 *xdg_activation_v1)
{
   wl_proxy_marshal_flags((struct wl_proxy *) xdg_activation_v1,
                          XDG_ACTIVATION_V1_DESTROY, NULL, wl_proxy_get_version((struct wl_proxy *) xdg_activation_v1), WL_MARSHAL_FLAG_DESTROY);
}

/**
 * @ingroup iface_xdg_activation_v1
 *
 * Creates an xdg_activation_token_v1 object that will provide
 * the initiating client with a unique token for this activation. This
 * token should be offered to the clients to be activated.
 */
static inline struct xdg_activation_token_v1 *
xdg_activation_v1_get_activation_token(struct xdg_activation_v1 *xdg_activation_v1)
{
   struct wl_proxy *id;

   id = wl_proxy_marshal_flags((struct wl_proxy *) xdg_activation_v1,
                               XDG_ACTIVATION_V1_GET_ACTIVATION_TOKEN, &xdg_activation_token_v1_interface, wl_proxy_get_version((struct wl_proxy *) xdg_activation_v1), 0, NULL);

   return (struct xdg_activation_token_v1 *) id;
}

/**
 * @ingroup iface_xdg_activation_v1
 *
 * Requests surface activation. It's up to the compositor to display
 * this information as desired, for example by placing the surface above
 * the rest.
 *
 * The compositor may know who requested this by checking the activation
 * token and might decide not to follow through with the activation if it's
 * considered unwanted.
 *
 * Compositors can ignore unknown activation tokens when an invalid
 * token is passed.
 */
static inline void
xdg_activation_v1_activate(struct xdg_activation_v1 *xdg_activation_v1, const_char_pointer token, struct wl_surface *surface)
{
   wl_proxy_marshal_flags((struct wl_proxy *) xdg_activation_v1,
                          XDG_ACTIVATION_V1_ACTIVATE, NULL, wl_proxy_get_version((struct wl_proxy *) xdg_activation_v1), 0, token, surface);
}

#ifndef XDG_ACTIVATION_TOKEN_V1_ERROR_ENUM
#define XDG_ACTIVATION_TOKEN_V1_ERROR_ENUM
enum xdg_activation_token_v1_error {
   /**
    * The token has already been used previously
    */
   XDG_ACTIVATION_TOKEN_V1_ERROR_ALREADY_USED = 0,
};
#endif /* XDG_ACTIVATION_TOKEN_V1_ERROR_ENUM */

/**
 * @ingroup iface_xdg_activation_token_v1
 * @struct xdg_activation_token_v1_listener
 */
struct xdg_activation_token_v1_listener {
   /**
    * the exported activation token
    *
    * The 'done' happening contains the unique token of this activation
    * request and notifies that the provider is done.
    * @param token the exported activation token
    */
   void (*done)(void *data,
                struct xdg_activation_token_v1 *xdg_activation_token_v1,
                const_char_pointer token);
};

/**
 * @ingroup iface_xdg_activation_token_v1
 */
static inline int
xdg_activation_token_v1_add_listener(struct xdg_activation_token_v1 *xdg_activation_token_v1,
                                     const struct xdg_activation_token_v1_listener *listener, void *data)
{
   return wl_proxy_add_listener((struct wl_proxy *) xdg_activation_token_v1,
                                (void (**)(void)) listener, data);
}

#define XDG_ACTIVATION_TOKEN_V1_SET_SERIAL 0
#define XDG_ACTIVATION_TOKEN_V1_SET_APP_ID 1
#define XDG_ACTIVATION_TOKEN_V1_SET_SURFACE 2
#define XDG_ACTIVATION_TOKEN_V1_COMMIT 3
#define XDG_ACTIVATION_TOKEN_V1_DESTROY 4

/**
 * @ingroup iface_xdg_activation_token_v1
 */
#define XDG_ACTIVATION_TOKEN_V1_DONE_SINCE_VERSION 1

/**
 * @ingroup iface_xdg_activation_token_v1
 */
#define XDG_ACTIVATION_TOKEN_V1_SET_SERIAL_SINCE_VERSION 1
/**
 * @ingroup iface_xdg_activation_token_v1
 */
#define XDG_ACTIVATION_TOKEN_V1_SET_APP_ID_SINCE_VERSION 1
/**
 * @ingroup iface_xdg_activation_token_v1
 */
#define XDG_ACTIVATION_TOKEN_V1_SET_SURFACE_SINCE_VERSION 1
/**
 * @ingroup iface_xdg_activation_token_v1
 */
#define XDG_ACTIVATION_TOKEN_V1_COMMIT_SINCE_VERSION 1
/**
 * @ingroup iface_xdg_activation_token_v1
 */
#define XDG_ACTIVATION_TOKEN_V1_DESTROY_SINCE_VERSION 1

/** @ingroup iface_xdg_activation_token_v1 */
static inline void
xdg_activation_token_v1_set_user_data(struct xdg_activation_token_v1 *xdg_activation_token_v1, void *user_data)
{
   wl_proxy_set_user_data((struct wl_proxy *) xdg_activation_token_v1, user_data);
}

/** @ingroup iface_xdg_activation_token_v1 */
static inline void *
xdg_activation_token_v1_get_user_data(struct xdg_activation_token_v1 *xdg_activation_token_v1)
{
   return wl_proxy_get_user_data((struct wl_proxy *) xdg_activation_token_v1);
}

static inline uint32_t
xdg_activation_token_v1_get_version(struct xdg_activation_token_v1 *xdg_activation_token_v1)
{
   return wl_proxy_get_version((struct wl_proxy *) xdg_activation_token_v1);
}

/**
 * @ingroup iface_xdg_activation_token_v1
 *
 * Provides information about the seat and serial happening that requested the
 * token.
 *
 * The serial can come from an input or focus happening. For instance, if a
 * click triggers the launch of a third-party client, the launcher client
 * should send a set_serial request with the serial and seat from the
 * wl_pointer.button happening.
 *
 * Some compositors might refuse to activate toplevels when the token
 * doesn't have a valid and recent enough happening serial.
 *
 * Must be sent before commit. This information is optional.
 */
static inline void
xdg_activation_token_v1_set_serial(struct xdg_activation_token_v1 *xdg_activation_token_v1, uint32_t serial, struct wl_seat *seat)
{
   wl_proxy_marshal_flags((struct wl_proxy *) xdg_activation_token_v1,
                          XDG_ACTIVATION_TOKEN_V1_SET_SERIAL, NULL, wl_proxy_get_version((struct wl_proxy *) xdg_activation_token_v1), 0, serial, seat);
}

/**
 * @ingroup iface_xdg_activation_token_v1
 *
 * The requesting client can specify an app_id to associate the token
 * being created with it.
 *
 * Must be sent before commit. This information is optional.
 */
static inline void
xdg_activation_token_v1_set_app_id(struct xdg_activation_token_v1 *xdg_activation_token_v1, const_char_pointer app_id)
{
   wl_proxy_marshal_flags((struct wl_proxy *) xdg_activation_token_v1,
                          XDG_ACTIVATION_TOKEN_V1_SET_APP_ID, NULL, wl_proxy_get_version((struct wl_proxy *) xdg_activation_token_v1), 0, app_id);
}

/**
 * @ingroup iface_xdg_activation_token_v1
 *
 * This request sets the surface requesting the activation. Note, this is
 * different from the surface that will be activated.
 *
 * Some compositors might refuse to activate toplevels when the token
 * doesn't have a requesting surface.
 *
 * Must be sent before commit. This information is optional.
 */
static inline void
xdg_activation_token_v1_set_surface(struct xdg_activation_token_v1 *xdg_activation_token_v1, struct wl_surface *surface)
{
   wl_proxy_marshal_flags((struct wl_proxy *) xdg_activation_token_v1,
                          XDG_ACTIVATION_TOKEN_V1_SET_SURFACE, NULL, wl_proxy_get_version((struct wl_proxy *) xdg_activation_token_v1), 0, surface);
}

/**
 * @ingroup iface_xdg_activation_token_v1
 *
 * Requests an activation token based on the different parameters that
 * have been offered through set_serial, set_surface and set_app_id.
 */
static inline void
xdg_activation_token_v1_commit(struct xdg_activation_token_v1 *xdg_activation_token_v1)
{
   wl_proxy_marshal_flags((struct wl_proxy *) xdg_activation_token_v1,
                          XDG_ACTIVATION_TOKEN_V1_COMMIT, NULL, wl_proxy_get_version((struct wl_proxy *) xdg_activation_token_v1), 0);
}

/**
 * @ingroup iface_xdg_activation_token_v1
 *
 * Notify the compositor that the xdg_activation_token_v1 object will no
 * longer be used.
 */
static inline void
xdg_activation_token_v1_destroy(struct xdg_activation_token_v1 *xdg_activation_token_v1)
{
   wl_proxy_marshal_flags((struct wl_proxy *) xdg_activation_token_v1,
                          XDG_ACTIVATION_TOKEN_V1_DESTROY, NULL, wl_proxy_get_version((struct wl_proxy *) xdg_activation_token_v1), WL_MARSHAL_FLAG_DESTROY);
}

#ifdef  __cplusplus
}
#endif

#endif