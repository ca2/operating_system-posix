#include "../kwin_bridge.h"
#include <QJsonObject>
#include <cstdio>
#include <cstdlib>

static void require(bool condition, const char * message)
{
   if (!condition) { std::fprintf(stderr, "%s\n", message); std::exit(1); }
}
static QJsonObject window(const QString & id, qint64 pid, const QString & title)
{
   return {{"id", id}, {"pid", pid}, {"title", title},
      {"client", QJsonArray{-1280, 24, 800, 600}},
      {"frame", QJsonArray{-1284, 0, 808, 628}},
      {"output", QJsonArray{-1920, 0, 1920, 1080}}, {"scale", 1.5}};
}
int main()
{
   // Without a QCoreApplication the transport does not start; exercise cache rules.
   accessibility_kde6::kwin_bridge bridge;
   bridge.wait();
   accessibility_kde6::kwin_geometry result;
   result.id = "unchanged";
   require(!bridge.lookup(7, {}, {}, result), "empty cache must fail");
   require(result.id == "unchanged", "failure must preserve output");
   auto first = window("one", 7, "Hello");
   bridge.replace({first});
   require(bridge.lookup(7, {}, {}, result), "unique process lookup");
   require(result.client == QRect(-1280, 24, 800, 600) && result.scale == 1.5,
      "preserve negative coordinates and fractional output scale");
   bridge.replace({first, window("two", 7, "Other"), window("three", 8, "Hello")});
   require(!bridge.lookup(7, {}, {}, result), "ambiguous process must fail");
   require(bridge.lookup(7, "Hello", {}, result) && result.id == "one", "exact title and PID");
   require(!bridge.lookup(9, "Hello", {}, result), "wrong process must fail");
   require(bridge.lookup(7, "Renamed", "one", result), "stable ID survives title change");
   bridge.replace({first, window("two", 7, "Hello")});
   require(!bridge.lookup(7, "Hello", {}, result), "duplicate titles must fail");
   first["client"] = QJsonArray{0, 0, -1, 600};
   bridge.replace({first});
   require(!bridge.lookup(7, {}, {}, result), "invalid dimensions must fail");
   first["client"] = QJsonArray{-0.5, 1.5, 800, 600};
   bridge.replace({first});
   require(bridge.lookup(7, {}, {}, result) && result.client == QRect(-1, 1, 801, 601),
      "fractional logical coordinates round outwards");
   bridge.clear();
   require(!bridge.lookup(7, {}, "one", result), "cleared windows cannot be returned");
   std::puts("KWin geometry cache tests passed");
}
