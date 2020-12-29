#include <system.h>
#include <require.h>
#include <log.h>
#include <mem.h>

void kmain()
{
    // we want logging
    require_log();

    log("\n  ..:: b00ter - k:0.0.1 ::..\n\n");

    if (!klowmem) {
        log("lowmem: failed\n");
    } else {
        log("lowmem: %x Kb\n", klowmem);
    }
    log("kstart: %x\n", kstart);
    log("kend:   %x\n", kend);

    log("hanging ...\n\n");
    hang();
}
