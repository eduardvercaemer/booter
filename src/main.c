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
    log("uppmem:\n");
    log("  ------ base ------ "
        "----- length ----- "
        "------ type ------\n");
    log("  %0x%x %0x%x ",
        uppmem[0].base_high,
        uppmem[0].base_low,
        uppmem[0].size_high,
        uppmem[0].size_low);
    switch (uppmem[0].type) {
    case 1:
        log("Free Memory (1)");
    break;
    }
    log("\n");

    log("hanging ...\n\n");
    hang();
}
