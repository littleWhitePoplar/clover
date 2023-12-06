#include "format.h"
namespace kernel {
static Format format;
Format& getFormat() { return format; }
}  // namespace kernel