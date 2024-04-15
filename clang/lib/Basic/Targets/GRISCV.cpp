#include "GRISCV.h"
#include "clang/Basic/Builtins.h"
#include "clang/Basic/MacroBuilder.h"

namespace clang::targets {
void GRISCVTargetInfo::getTargetDefines(const LangOptions &Opts,
                                        MacroBuilder &Builder) const {
  Builder.defineMacro("__griscv__");
}
} // namespace clang::targets
