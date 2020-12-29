#include <system.h>
#include <require.h>
#include <log.h>

void kmain()
{
    // we want logging
    require_log();

    log_info("hanging ...");
    hang();
}
