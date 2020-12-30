#include <system.h>
#include <log.h>
#include <mem.h>

void kmain()
{
    require_log(); /* logging capabilities */
    require_mem(); /* memory management */

    mem_logdump();

    /* request some pages */
    void *page0 = mem_palloc();
    void *page1 = mem_palloc();
    void *page2 = mem_palloc();
    void *page3 = mem_palloc();

    mem_pfree(page2);
    mem_pfree(page0);
    mem_pfree(page3);
    mem_pfree(page1);

    log("\nhanging ...\n\n");
    hang();
}
