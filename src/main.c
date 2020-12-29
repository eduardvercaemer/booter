#include <system.h>
#include <require.h>
#include <log.h>
#include <mem.h>

void kmain()
{
    // we want logging
    require_log();

    log("\n  ..:: b00ter - k:0.0.1 ::..\n\n");
    
    mem_logdump();

    log("\nhanging ...\n\n");
    hang();
}
