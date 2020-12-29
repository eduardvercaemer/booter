#include <system.h>
#include <require.h>
#include <log.h>

void kmain()
{
    // we want logging
    require_log();

    log("\n  ..:: b00ter - k:0.0.1 ::..\n\n");
    log("hanging ...\n\n");
    hang();
}
