// Exercise the real protocol callbacks without requiring desktop input injection.
#include "../native/runtime.cpp"
#include <xkbcommon/xkbcommon-keysyms.h>
#include <cstdlib>
#include <vector>
#define CHECK(x) do { if (!(x)) { std::fprintf(stderr,"Keyboard test failed at line %d: %s\n",__LINE__,#x); return 1; } } while (0)
struct event { uint32_t code, symbol; bool down; };
int main()
{
 using namespace ca2_wayland;
 std::vector<event> events;
 window::impl window{};
 runtime::impl state{};
 state.xkb=xkb_context_new(XKB_CONTEXT_NO_FLAGS);
 xkb_rule_names names{};names.layout="us";
 state.keymap=xkb_keymap_new_from_names(state.xkb,&names,XKB_KEYMAP_COMPILE_NO_FLAGS);
 CHECK(state.keymap);
 state.keyboard_state=xkb_state_new(state.keymap);CHECK(state.keyboard_state);
 window.events.key=[&](uint32_t code,uint32_t symbol,bool down,const std::string&){events.push_back({code,symbol,down});};
 auto surface=reinterpret_cast<wl_surface*>(uintptr_t(1));
 state.windows[surface]=&window;
 wl_array empty{};
 keyboard_enter(&state,nullptr,0,surface,&empty);
 const std::pair<uint32_t,uint32_t> keys[]={
  {KEY_W,XKB_KEY_w},{KEY_A,XKB_KEY_a},{KEY_S,XKB_KEY_s},{KEY_D,XKB_KEY_d},
  {KEY_Q,XKB_KEY_q},{KEY_E,XKB_KEY_e},{KEY_LEFT,XKB_KEY_Left},{KEY_RIGHT,XKB_KEY_Right},
  {KEY_UP,XKB_KEY_Up},{KEY_DOWN,XKB_KEY_Down}};
 for(auto [code,symbol]:keys) {
  events.clear();keyboard_key(&state,nullptr,0,0,code,WL_KEYBOARD_KEY_STATE_PRESSED);
  keyboard_key(&state,nullptr,0,0,code,WL_KEYBOARD_KEY_STATE_RELEASED);
  CHECK(events.size()==2 && events[0].down && !events[1].down);
  CHECK(events[0].symbol==symbol && events[1].symbol==symbol && state.pressed_keys.empty());
 }
 // Focus entry supplies keys already held, including simultaneous movement keys.
 uint32_t held[]={KEY_W,KEY_A,KEY_LEFT};wl_array snapshot{sizeof held,sizeof held,held};
 events.clear();keyboard_enter(&state,nullptr,0,surface,&snapshot);
 CHECK(events.size()==3 && state.pressed_keys.size()==3);
 keyboard_leave(&state,nullptr,0,surface);
 CHECK(events.size()==6 && state.pressed_keys.empty() && !state.keyboard_window);
 for(size_t i=3;i<6;++i)CHECK(!events[i].down);
 // A shifted press must release the same symbol after Shift is released first.
 keyboard_enter(&state,nullptr,0,surface,&empty);events.clear();
 keyboard_key(&state,nullptr,0,0,KEY_LEFTSHIFT,WL_KEYBOARD_KEY_STATE_PRESSED);
 const auto shift=xkb_keymap_mod_get_index(state.keymap,XKB_MOD_NAME_SHIFT);
 keyboard_modifiers(&state,nullptr,0,1u<<shift,0,0,0);
 keyboard_key(&state,nullptr,0,0,KEY_W,WL_KEYBOARD_KEY_STATE_PRESSED);
 keyboard_key(&state,nullptr,0,0,KEY_LEFTSHIFT,WL_KEYBOARD_KEY_STATE_RELEASED);
 keyboard_modifiers(&state,nullptr,0,0,0,0,0);
 keyboard_key(&state,nullptr,0,0,KEY_W,WL_KEYBOARD_KEY_STATE_RELEASED);
 CHECK(events.size()==4 && events[1].symbol==XKB_KEY_W && events[3].symbol==XKB_KEY_W && !events[3].down);
 // Replacing the layout cannot strand keys from the old XKB state.
 events.clear();keyboard_key(&state,nullptr,0,0,KEY_W,WL_KEYBOARD_KEY_STATE_PRESSED);
 char* map=xkb_keymap_get_as_string(state.keymap,XKB_KEYMAP_FORMAT_TEXT_V1);
 int fd=memfd_create("ca2-keymap-test",MFD_CLOEXEC);CHECK(fd>=0);
 const auto bytes=std::strlen(map)+1;CHECK(write(fd,map,bytes)==ssize_t(bytes));std::free(map);
 keyboard_keymap(&state,nullptr,WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1,fd,bytes);
 CHECK(events.size()==2 && !events.back().down && state.pressed_keys.empty());
 std::puts("Wayland keyboard callbacks passed: WASDQE/arrows, simultaneous held keys on focus entry, focus-loss releases, modifier-stable keyup, layout replacement");
}
