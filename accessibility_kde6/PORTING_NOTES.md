# Porting notes

The original CMake file named the project `accessibility_windows`, linked
Windows-only libraries, and had a Linux branch that still requested GTK 3.
The active factory registered three Windows namespace classes.

The original `_.cpp`, `_file.cpp`, and `_graphics2d.h` were copied from other
Windows modules. `_file.cpp` and `_graphics2d.h` were not active CMake sources;
they are deliberately omitted from this port.

The KDE6 bridge uses the public `GtkAccessible` interface:

- `gtk_accessible_update_property()` for label, description and numeric range.
- `gtk_accessible_update_state()` for busy, disabled, hidden, expanded,
  selected, checked and pressed.
- `gtk_accessible_announce()` when built with GTK 4.14 or newer.

Do not perform these calls from an arbitrary worker thread. Dispatch them to
the same GTK main context used by the windowing backend.
