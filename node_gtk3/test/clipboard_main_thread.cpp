#include "node_gtk3/platform.h"
#include "node_gtk3/copydesk.h"
#include "acme/platform/system.h"
#include "acme/platform/node.h"
#include "acme/platform/application.h"
#include "acme/parallelization/task.h"
#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include <dlfcn.h>
#include <unistd.h>

class test_node : public ::platform::node
{
public:
   ::string get_call_stack_trace(const ::scoped_string &, ::i32, void *, ::i32) override { return {}; }
};

// Give this process a private X11 selection. Never replace the user's clipboard.
extern "C" GtkClipboard * gtk_clipboard_get(GdkAtom selection)
{
   using function = GtkClipboard * (*)(GdkAtom);
   static auto real = reinterpret_cast<function>(dlsym(RTLD_NEXT, "gtk_clipboard_get"));
   if (selection == GDK_SELECTION_CLIPBOARD)
   {
      char name[100];
      snprintf(name, sizeof(name), "_CODEX_GTK3_CLIPBOARD_TEST_%ld", (long)getpid());
      selection = gdk_atom_intern(name, false);
   }
   return real(selection);
}

int main(int argc, char ** argv)
{
   if (!gtk_init_check(&argc, &argv) || !GDK_IS_X11_DISPLAY(gdk_display_get_default())) return 77;
   ::platform::system runtime;
   runtime.m_pnode = ::pointer<test_node>(allocate_t{});
   ::set_main_user_thread();
   if (!::is_main_thread()) return 2;
   ::pointer<::platform::application> app(allocate_t{});
   app->m_papplication = app;
   ::pointer<::node_gtk3::copydesk> clipboard(allocate_t{});
   clipboard->m_papplication = app;
   ::file::path_array_base files;
   files.add("/tmp/clipboard-test.png");
   files.add("google-drive://folder-id/file-id");
   for (auto op : {::user::copydesk::e_op_copy, ::user::copydesk::e_op_cut})
   {
      if (!clipboard->_set_filea(files, op)) return 3;
      if (!clipboard->_has_filea()) return 4;
      ::file::path_array_base copied;
      auto actual = ::user::copydesk::e_op_copy;
      if (!clipboard->_get_filea(copied, actual) || actual != op || copied.size() != 2
         || copied[0] != files[0] || copied[1] != files[1]) return 5;
   }
   auto native = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
   gtk_clipboard_set_text(native, "clipboard-test", -1);
   ::string text;
   if (!clipboard->_get_plain_text(text) || text != "clipboard-test" || clipboard->_has_filea()) return 6;
   gtk_clipboard_clear(native);
   clipboard->destroy();
   return 0;
}
