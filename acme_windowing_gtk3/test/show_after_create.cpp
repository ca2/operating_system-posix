#include "acme_windowing_gtk3/platform.h"
#include "acme_windowing_gtk3/window.h"
#include "acme/platform/system.h"
#include "acme/platform/node.h"
#include <vector>
class test_node : public ::platform::node
{
public:
   ::string get_call_stack_trace(const ::scoped_string &, ::i32, void *, ::i32) override { return {}; }
};
class test_window : public ::gtk3::acme::windowing::window
{
public:
   int immediate = 0;
   std::vector<::procedure> queued;
   void main_send(const ::procedure & p) override { ++immediate; p(); }
   void main_post(const ::procedure & p) override { queued.push_back(p); }
};
int main()
{
   ::platform::system runtime;
   runtime.m_pnode = ::pointer<test_node>(allocate_t{});
   ::pointer<test_window> window(allocate_t{});
   window->m_pgtkwidget = nullptr;
   bool created = false;
   window->main_post([&created]() { created = true; });
   window->show_window(::user_interface::e_show_window_show_normal);
   bool ordered = !window->immediate && !created && window->queued.size() == 2;
   window->queued[0]();
   ordered = ordered && created;
   // A pending show must safely tolerate a widget that was never created/destroyed.
   window->queued[1]();
   window->queued.clear();
   return ordered ? 0 : 1;
}
