//
// ref: https://www.leadroyal.cn/p/2210/
//

#include <llvm/Transforms/IPO/PassManagerBuilder.h>
#include <llvm/Passes/PassBuilder.h>

#include "Obfuscation/BogusControlFlow.h"
#include "Obfuscation/Flattening.h"
#include "Obfuscation/FlatteningEnhanced.h"
#include "Obfuscation/GlobalsEncryption.h"
#include "Obfuscation/HelloWorld.h"
#include "Obfuscation/MBAObfuscation.h"
#include "Obfuscation/RandomControlFlow.h"
#include "Obfuscation/SplitBasicBlock.h"
#include "Obfuscation/Substitution.h"
#include "Obfuscation/TrapAngr.h"
#include "Obfuscation/VariableSubstitution.h"

using namespace llvm;

struct PassPluginInfo {
  uint32_t APIVersion;
  const char *PluginName;
  const char *PluginVersion;
  void (*RegisterPassBuilderCallbacks)(PassBuilder &);
};

extern "C" PassPluginInfo __declspec(dllexport)
    llvmGetPassPluginInfo() {
  return {1, "PlutoObfuscator", LLVM_VERSION_STRING, [](PassBuilder &PB) {

            PB.registerPipelineStartEPCallback(
                [](ModulePassManager &MPM, OptimizationLevel) {
                    MPM.addPass(MyFlattenPass());
            });
  
            PB.registerVectorizerStartEPCallback(
                [](FunctionPassManager &FM, OptimizationLevel) {
            //        FM.addPass(BogusControlFlowPass());
                    FM.addPass(FlatteningPass());
                    FM.addPass(SplitBasicBlockPass());
                    FM.addPass(MBAObfuscationPass());
                    FM.addPass(VariableSubstitutionPass());
                    FM.addPass(RandomControlFlowPass());
                    FM.addPass(SubstitutionPass());
           //         FM.addPass(TrapAngrPass());
                }
            );

            PB.registerOptimizerLastEPCallback(
               [](llvm::ModulePassManager &MPM, llvm::OptimizationLevel) {
                    MPM.addPass(GlobalsEncryptionPass());
                });
          }};
}