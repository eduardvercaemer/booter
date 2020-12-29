#include <system.h>
#include <require.h>
#include <log.h>
#include <mem.h>

void kmain()
{
    require(log); /* logging capabilities */
    require(mem); /* memory management */

    mem_logdump();

    log("\nhanging ...\n\n");
    hang();
}
