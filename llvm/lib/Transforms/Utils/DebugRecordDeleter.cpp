#include "llvm/Transforms/Utils/DebugRecordDeleter.h"
#include "llvm/IR/DebugInfo.h"
#include "llvm/IR/DebugInfoMetadata.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"

using namespace llvm;

// build/bin/opt -S /home/ana-marija/Documents/foo_00.ll -passes=dbg-deleter
PreservedAnalyses DebugRecordDeleterPass::run(Module &M,
                                              ModuleAnalysisManager &AM) {

  for(Function &F : M) {
    for(BasicBlock &BB : F) {
      for(Instruction &I : BB) { 
        if(I.hasDbgRecords()) {
          I.dropDbgRecords();
        }
      }
    }
  }

  return PreservedAnalyses::all();
}
