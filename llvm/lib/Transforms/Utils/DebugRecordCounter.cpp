#include "llvm/Transforms/Utils/DebugRecordCounter.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/Debug.h"

#define DEBUG_TYPE "counter"

using namespace llvm;

// build/bin/opt -disable-output /home/ana-marija/Documents/foo_00.ll
// -passes=dbg-counter
PreservedAnalyses DebugRecordCounterPass::run(Module &M,
                                              ModuleAnalysisManager &AM) {

  unsigned dbg_values, dbg_declares, dbg_assigns;

  for (Function &F : M) {
    LLVM_DEBUG(dbgs() << "Function: " << F.getName() << "\n";);

    dbg_assigns = dbg_declares = dbg_values = 0;

    for (BasicBlock &BB : F) {
      for (Instruction &I : BB) {
        for (DbgVariableRecord &DVR : filterDbgVars(I.getDbgRecordRange())) {
          if (DVR.isDbgDeclare())
            dbg_declares++;
          if (DVR.isDbgValue())
            dbg_values++;
          if (DVR.isDbgAssign())
            dbg_assigns++;
        }
      }
    }
    LLVM_DEBUG(dbgs() << "\t#dbg_value: " << dbg_values << "\n";
               dbgs() << "\t#dbg_declare: " << dbg_declares << "\n";
               dbgs() << "\t#dbg_assign: " << dbg_assigns << "\n";);
  }
  return PreservedAnalyses::all();
}
