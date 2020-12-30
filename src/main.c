#include <system.h>
#include <log.h>
#include <mem.h>

void kmain()
{
    require_log(); /* logging capabilities */
    require_mem(); /* memory management */

    mem_logdump();

    log("\nhanging ...\n\n");
    hang();
}
