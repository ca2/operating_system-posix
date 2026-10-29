#include "platform.h"
#include "accessibility.h"
#include "kwin_bridge.h"

namespace accessibility_kde6
{
   accessibility::accessibility() : m_kwin(std::make_unique<kwin_bridge>()) {}
   accessibility::~accessibility() = default;

   bool accessibility::get_window_geometry(::process_identifier pid,
      const ::scoped_string & title, ::accessibility::window_geometry & geometry,
      const ::scoped_string & windowId)
   {
      kwin_geometry found;
      const ::string strTitle(title), strId(windowId);
      if (!m_kwin->lookup((qint64)pid, QString::fromUtf8(strTitle.c_str()),
         QString::fromUtf8(strId.c_str()), found)) return false;
      ::accessibility::window_geometry candidate;
      candidate.m_strWindowId = found.id.toUtf8().constData();
      auto rectangle = [](const QRect & r) {
         return ::i32_rectangle(r.x(), r.y(), r.x() + r.width(), r.y() + r.height());
      };
      candidate.m_rectangleClient = rectangle(found.client);
      candidate.m_rectangleFrame = rectangle(found.frame);
      candidate.m_rectangleOutput = rectangle(found.output);
      candidate.m_dOutputScale = found.scale;
      geometry = candidate;
      return true;
   }
}
