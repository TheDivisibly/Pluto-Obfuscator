#include "Obfuscation/HelloWorld.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "Obfuscation/Utils.h"
#include <iostream>
using namespace llvm;

bool HelloWorld::runOnFunction(Function &F) {
    if (enable) {
        SKIP_IF_SHOULD(F);
        outs() << "Hello, " << F.getName() << ", " << readAnnotation(&F) << "\n";
    }
    return false;
}

FunctionPass *llvm::createHelloWorldPass(bool enable) {
    return new HelloWorld(enable);
}

char HelloWorld::ID = 0;

#if LLVM_VERSION_MAJOR >= 13
PreservedAnalyses HelloWorldPass::run(Function &F,
                                             FunctionAnalysisManager &AM) {
  HelloWorld hw(1);
  hw.runOnFunction(F);

  return PreservedAnalyses::all();
}
#endif