#include <system.h>
#include <require.h>
#include <log.h>
#include <mem.h>

void kmain()
{
    require(log); /* logging capabilities */
    log("\n  ..:: b00ter - k:0.0.1 ::..\n\n");
    require(mem); /* memory management */

    log("\nhanging ...\n\n");
    hang();
}
