# AT-SPI accessibility automation

The backend implements the platform-independent element interface in
`acme/accessibility/automation.h`: names, roles, process IDs, children,
parents, named actions, child selection, and selected/checked states.
It uses libatspi's accessibility bus, not simulated keyboard input.

`accessibility_gtk3` exposes this transport through ca2's accessibility
factory. Shared application/window selection, menu navigation and tab
iteration live in `acme/accessibility/selection.h`; Ambient retains only
the MATE Terminal profile policy.

The initial consumer is Ambient's MATE Terminal profile association.
Ambient invokes the accessibility component directly in its existing worker
task. GTK3 serializes in-process automation transactions. Traversals and
individual IPC calls are bounded; terminal scrollback is excluded.
`accessibility_atspi_mate_terminal` is an optional diagnostic executable
that uses the same component operation.

## OpenIndiana

CMake enables `INCLUDE_ACCESSIBILITY_ATSPI` by default on SunOS. Building
`_app_core_ambient` also builds the AT-SPI and GTK3 shared components in `output`.
The diagnostic executable is no longer an Ambient dependency.
The development headers and pkgconf metadata for `atspi-2` and `gio-2.0`
are required. Check before configuring:

```sh
pkgconf --cflags --libs atspi-2 gio-2.0
```

If development files are absent, find their IPS package with
`pkg search -r 'path:*atspi/atspi.h'`. The feature may be disabled with
`-DINCLUDE_ACCESSIBILITY_ATSPI=OFF`; default-profile selection still works.

Enable MATE accessibility in the desktop session:

```sh
gsettings set org.mate.interface accessibility true
```

Existing terminal processes may need to be restarted once so GTK registers
their accessibility trees. Preserve ongoing shell work before closing them.
Keep the terminal menubar visible for this initial implementation.

```sh
cd ~/code/main/cmake-build-debug
cmake ..
build1 _app_core_ambient
cmake --build . --target accessibility_atspi_mate_terminal
./output/accessibility_atspi_mate_terminal --dump
```

The diagnostic dump is read-only and contains menu and tab labels, not
terminal scrollback. Roles are the indices in the generic `role` enum.

Ambient reads its associated profile name and sends a menu-selection request
to `system()->accessibility()` in-process. For a
manual test, `./output/accessibility_atspi_mate_terminal 'Dark'` selects
that named profile in every accessible MATE Terminal window and tab.

Profile menus are located by roles and the exact user-defined profile
name, avoiding translated menu titles. Missing or duplicate profile names,
hidden/unexposed menus, stale objects and failed actions produce diagnostics.
The original selected tab is restored, including after a failed action.
Only processes identified as the `mate-terminal` executable through `/proc`
are acted on. A complete application failure or unavailable accessibility
does not prevent Ambient from changing the default for new terminals.

## Validation

The backend-neutral automation tests cover multiple tabs, translated parent
labels, idempotent selection, duplicate/missing profiles, failure restoration,
and exclusion of terminal scrollback:

```sh
cmake --build cmake-build-debug --target accessibility_selection_tests
./cmake-build-debug/output/accessibility_selection_tests
```

Tests now link Acme and have not been rerun after converting from STL.
These tests do not substitute for testing GTK's live accessible menu tree.
The AT-SPI backend and Ambient integration still require an OpenIndiana build
and desktop test. No MATE Terminal patch is required.

API references:
- https://gnome.pages.gitlab.gnome.org/at-spi2-core/libatspi/class.Accessible.html
- https://gnome.pages.gitlab.gnome.org/at-spi2-core/libatspi/method.Selection.select_child.html
