#include "../native/runtime.h"
#include <atomic>
#include <chrono>
#include <cstdio>
#include <thread>
#include <vector>
int main()
{
 ca2_wayland::runtime display;
 std::atomic<int> configured{0};
 ca2_wayland::callbacks callbacks;
 callbacks.configure=[&](int w,int h) { if(w>0 && h>0) ++configured; };
 auto window=display.create_window(360,240,"ca2 standalone Wayland test","ca2.native.wayland.test",callbacks);
 for(int i=0;i<100 && !window->configured();++i) std::this_thread::sleep_for(std::chrono::milliseconds(20));
 if(!window->configured()) return 1;
 std::vector<uint32_t> pixels(360*240);
 for(int frame=0;frame<5;++frame) {
  for(int y=0;y<240;++y) for(int x=0;x<360;++x) pixels[y*360+x]=0xff000000u|uint32_t((x+frame*30)%256)<<16|uint32_t(y)<<8|0x80;
  window->present(pixels.data(),360,240,360*4);
  std::this_thread::sleep_for(std::chrono::milliseconds(150));
 }
 window->acquire_external_presentation();
 window->acquire_external_presentation();
 if(window->present(pixels.data(),360,240,360*4)) return 3;
 window->release_external_presentation();
 if(window->present(pixels.data(),360,240,360*4)) return 4;
 window->release_external_presentation();
 std::this_thread::sleep_for(std::chrono::milliseconds(200));
 if(!window->present(pixels.data(),360,240,360*4)) return 5;
 for (int cycle=0;cycle<3;++cycle) {
  window->hide();
  if(window->configured()) return 6;
  window->show();
  if(!window->configured()) return 7;
  if(!window->present(pixels.data(),360,240,360*4)) return 8;
  std::this_thread::sleep_for(std::chrono::milliseconds(150));
 }
 bool invalid=false;
 try {window->present(pixels.data(),360,240,1);}catch(const std::invalid_argument &){invalid=true;}
 const auto outputs=display.outputs();
 std::printf("Native Wayland smoke passed: %d configure events, %zu outputs, image presentation, exclusive presentation ownership, three hide/show cycles, invalid stride rejected=%d\n",configured.load(),outputs.size(),invalid);
 window.reset();
 return invalid && !outputs.empty() ? 0 : 2;
}
