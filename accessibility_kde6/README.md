# accessibility_kde6 for FreeBSD

This directory is a FreeBSD/KDE6 replacement for the copied
`accessibility_windows` skeleton.

## What changed

- Renamed the CMake project, factory and C++ namespace to `accessibility_kde6`.
- Removed dependencies on `acme_windows`, Win32 resources, Shell API, GDI+,
  SetupAPI and CredUI.
- Uses `pkg-config`'s `kde6` target, which supplies GTK, GDK, GLib, GObject,
  Pango and Cairo compile/link flags on FreeBSD.
- Preserves the three factory mappings:
  `accessibility`, `application`, and `main_window`.
- Adds KDE6-native helpers for accessible labels, descriptions, ranges,
  states and screen-reader announcements.
- Guards `gtk_accessible_announce()` so the library still compiles with GTK
  versions older than 4.14.

## Integration

Copy this directory over:

```text
/home/camilo/code/main/operating_system/operating_system-freebsd/accessibility_kde6
```

Then add the directory from the same parent CMake file that currently adds the
Windows accessibility library.

The default ca2 link targets are `axis;acme`. If your FreeBSD build uses
another target list, configure it before adding this subdirectory:

```cmake
set(ACCESSIBILITY_KDE6_CA2_LIBRARIES axis acme acme_posix)
add_subdirectory(accessibility_kde6)
```

## GTK widget use

```cpp
#include "accessibility_kde6/gtk_accessible.h"

accessibility_kde6::set_accessible_label(pwidget, "Open document");
accessibility_kde6::set_accessible_description(
   pwidget,
   "Opens an existing document from disk");

accessibility_kde6::set_accessible_disabled(pwidget, false);
accessibility_kde6::set_accessible_busy(pwidget, true);

accessibility_kde6::announce_accessible_message(
   pwidget,
   "Document saved");
```

GTK widget roles are determined by the GTK widget class. For a custom widget,
set the role from its class initialization with
`gtk_widget_class_set_accessible_role()` instead of trying to mutate the role
per instance.

## Important limitation

The uploaded Windows folder did not contain the bodies of its original
`accessibility.cpp`, `application.cpp`, `main_window.cpp`, or their headers.
The replacement classes therefore preserve the factory and inheritance shape
but cannot carry over any private Windows-specific behavior that may exist in
those missing files. The KDE6 helper implementation itself is complete.
