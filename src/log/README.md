# Log

This is the logging module.

```
#include <log.h>
require_log();
```
to utilize the module.

`export.h` defines the exported symbols for this module.

# Exports

Macros:
- `log_f`: append __FILE__ to log.

Functions:
- `require_log`: import this module.
- `log`: print formatted string to log.

# Internals

For now, we use serial for all logging.
