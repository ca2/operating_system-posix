#include "automation.h"
#include <atspi/atspi.h>
#include "acme/parallelization/critical_section.h"
#include <unistd.h>

namespace accessibility_atspi
{
   namespace
   {
      using namespace accessibility::automation;
      struct error
      {
         GError *value = nullptr;
         ~error() { if (value) g_error_free(value); }
         void check() { if (value) throw ::exception(error_failed, value->message); }
      };
      template<class T> struct object
      {
         T *value;
         ~object() { if (value) g_object_unref(value); }
      };
      class accessible : public element
      {
         AtspiAccessible *m_object;
         bool state(AtspiStateType type)
         {
            object<AtspiStateSet> states{atspi_accessible_get_state_set(m_object)};
            return states.value && atspi_state_set_contains(states.value, type);
         }
      public:
         explicit accessible(AtspiAccessible *obj) : m_object(obj) {}
         ~accessible() override { g_object_unref(m_object); }
         ::string name() override
         {
            error e;
            char *text = atspi_accessible_get_name(m_object, &e.value);
            ::string result = text ? text : "";
            g_free(text); e.check(); return result;
         }
         role type() override
         {
            error e;
            auto type = atspi_accessible_get_role(m_object, &e.value);
            e.check();
            switch (type)
            {
            case ATSPI_ROLE_APPLICATION: return role::application;
            case ATSPI_ROLE_FRAME: case ATSPI_ROLE_WINDOW: return role::window;
            case ATSPI_ROLE_MENU_BAR: return role::menu_bar;
            case ATSPI_ROLE_MENU: return role::menu;
            case ATSPI_ROLE_MENU_ITEM: return role::menu_item;
            case ATSPI_ROLE_RADIO_MENU_ITEM: return role::radio_menu_item;
            case ATSPI_ROLE_PAGE_TAB_LIST: return role::tab_list;
            case ATSPI_ROLE_PAGE_TAB: return role::tab;
            case ATSPI_ROLE_TERMINAL: return role::terminal;
            default: return role::other;
            }
         }
         unsigned int process_id() override
         {
            error e;
            auto id = atspi_accessible_get_process_id(m_object, &e.value);
            e.check(); return id;
         }
         ::string executable_name() override
         {
            auto pid = process_id();
            char path[4096];
            for (auto suffix : {"/path/a.out", "/exe"})
            {
               auto proc = "/proc/" + ::as_string(pid) + suffix;
               auto length = readlink(proc.c_str(), path, sizeof(path) - 1);
               if (length <= 0) continue;
               path[length] = 0;
               ::string executable(path);
               ::string_array_base components;
               components.add_tokens(executable, "/", false);
               return components.is_empty() ? ::string() : components.last();
            }
            return {};
         }
         element_array children() override
         {
            // Fresh children are important after GTK opens a menu or changes tabs.
            atspi_accessible_clear_cache(m_object);
            error e;
            auto count = atspi_accessible_get_child_count(m_object, &e.value);
            e.check();
            if (count > 4096) throw ::exception(error_failed, "Too many accessible children");
            element_array result;
            for (int i = 0; i < count; ++i)
            {
               auto child = atspi_accessible_get_child_at_index(m_object, i, &e.value);
               if (e.value) { if (child) g_object_unref(child); e.check(); }
               if (child) result.add(allocateø accessible(child));
            }
            return result;
         }
         element_pointer parent() override
         {
            error e;
            auto item = atspi_accessible_get_parent(m_object, &e.value);
            if (e.value) { if (item) g_object_unref(item); e.check(); }
            if (!item) return nullptr;
            return allocateø accessible(item);
         }
         ::string_array_base actions() override
         {
            object<AtspiAction> action{atspi_accessible_get_action_iface(m_object)};
            if (!action.value) return {};
            error e;
            int count = atspi_action_get_n_actions(action.value, &e.value);
            e.check();
            ::string_array_base result;
            for (int i = 0; i < count; ++i)
            {
               char *text = atspi_action_get_action_name(action.value, i, &e.value);
               result.add(text ? text : "");
               g_free(text); e.check();
            }
            return result;
         }
         bool perform_action(int index) override
         {
            object<AtspiAction> action{atspi_accessible_get_action_iface(m_object)};
            if (!action.value) return false;
            error e;
            bool ok = atspi_action_do_action(action.value, index, &e.value);
            e.check(); return ok;
         }
         bool select_child(int index) override
         {
            object<AtspiSelection> selection{atspi_accessible_get_selection_iface(m_object)};
            if (!selection.value) return false;
            error e;
            bool ok = atspi_selection_select_child(selection.value, index, &e.value);
            e.check(); return ok;
         }
         bool selected() override { atspi_accessible_clear_cache(m_object); return state(ATSPI_STATE_SELECTED); }
         bool checked() override { atspi_accessible_clear_cache(m_object); return state(ATSPI_STATE_CHECKED); }
      };
   }
   accessibility::automation::element_pointer desktop()
   {
      static ::critical_section initialization;
      ::critical_section_lock lock(&initialization);
      static bool initialized = false;
      if (!initialized)
      {
         if (atspi_init() != 0)
            throw ::exception(error_failed, "Cannot initialize AT-SPI; enable desktop accessibility");
         atspi_set_timeout(1000, 1000);
         initialized = true;
      }
      auto root = atspi_get_desktop(0);
      if (!root) throw ::exception(error_failed, "No accessible desktop in this session");
      return allocateø accessible(root);
   }
}
