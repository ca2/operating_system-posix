# GTK3 accessibility component

`accessibility_gtk3` registers `accessibility::accessibility` in the ca2
factory system. On SunOS, `system()->accessibility()` selects this component.
Its `automation_desktop()` method returns the same backend-neutral element
tree used by the standalone automation helper.

The application-independent operations live in Acme:

- `accessibility::automation::applications(desktop, predicate)` selects
  application roots, including by the backend's verified executable identity.
- `windows(application, predicate)` selects windows by caller-defined criteria.
- `find_all(root, predicate)` performs bounded role/name/tree searches.
- `invoke(element)` activates an accessible action.
- `menu_item(window, predicate)` finds an unambiguous matching menu item.
- `select_menu_item(window, predicate, settle, verify_checked)` opens its
  menu ancestors, invokes the item, and optionally verifies radio selection.
- `for_each_tab(window, operation, settle)` selects each tab and restores
  the original selection on success or failure.

These functions contain no GTK, AT-SPI, MATE, or Ambient-specific calls.
They operate on the abstract `element` interface. The `settle` callback lets
each caller provide its own waiting/deadline policy.

GTK3 exposes other processes' accessible controls through AT-SPI. The
`accessibility_atspi` library owns native objects and performs the IPC;
`accessibility_gtk3` provides the ca2 component entry point. This split lets
other desktop backends reuse the AT-SPI transport without duplicating it.

Call automation from a dedicated worker/helper outside the GTK GUI thread.
The existing `accessibility_atspi_mate_terminal` executable now consumes
this GTK3 component. Ambient supplies only the target executable/profile
policy. Its existing executable name and command-line options are preserved.

See `../accessibility_atspi/README.md` for OpenIndiana build prerequisites,
desktop accessibility setup and diagnostics. Native compilation and a live
MATE session test are still required. Tests now link Acme through the
`accessibility_selection_tests` target and have not been rerun since the
ca2 conversion.

Elements, traversal helpers, sessions and backend implementations inherit
from `particle` and use `::pointer`. Strings, arrays, callbacks, timing,
locking and exceptions use ca2 types. Native GLib handle guards remain
scoped stack objects at the API boundary. No STL containers are used.
