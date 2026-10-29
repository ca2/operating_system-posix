# Native Wayland backend

The active CMake target uses `native/`. The older sources remain as an archive;
they are not part of the target.

`acme_windowing_wayland` owns the Wayland connection, xdg-shell windows, seat,
XKB input, outputs and shared-memory presentation. `windowing_wayland` adapts
these events and buffers to Aura. Neither backend links Qt, EGL or OpenGL.
`gpu_opengl` borrows the display and surface, and owns its EGL objects and
`wl_egl_window`.

An external renderer must acquire the generic `native_surface_provider`
presentation claim before attaching buffers and release it after destroying its
native presentation objects. While claimed, CPU shared-memory presentation is
suppressed. Claims use a mutex directly rather than waiting on the event thread.

Wayland application IDs use the common freedesktop desktop application ID,
matching the desktop entry basename. The common ca2 icon/shortcut flow installs
the application matter icon; KDE resolves it from the desktop entry.

Key symbols are translated through XKB and delivered to the interaction thread.
Arrow keys and left/right modifiers are included. Focus loss and keymap replacement release held keys; focus entry restores the compositor-provided held-key snapshot. Key releases still clear session state after a surface is hidden.

Set the application's roaming `windowing.txt` to `wayland_windowing` and its
`graphics3d_output.txt` to `swap_chain` for native EGL presentation. Build the
application, `windowing_wayland`, and `operating_ambient_wayland` targets.
Optional `CA2_NATIVE_WAYLAND_TESTS` enables live runtime and EGL smoke tests.

This backend currently provides basic window/input/presentation support.
Clipboard, IME, key repeat and fractional output geometry still need further
work. Hidden surfaces remap through a fresh xdg-shell configure handshake. Global window placement is not provided by
Wayland; use an accessibility/compositor service when available.

`native_wayland_keyboard_test` exercises WASDQE/arrows, simultaneous held keys on focus entry, focus-loss release, modifier changes before keyup, and keymap replacement without sending input to the desktop.
