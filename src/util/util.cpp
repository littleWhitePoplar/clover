#include "util.h"
namespace kernel {
Uint32 getReg32Value(Uint32 &reg32) { return *((Uint32 *)(&reg32)); }
void setReg32Value(Uint32 &reg32, Uint32 value) {
  *((Uint32 *)(&reg32)) = value;
}
}  // namespace kernel