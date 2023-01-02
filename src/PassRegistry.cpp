#include "Obfuscation/PassRegistry.h"
#include "llvm/Support/CommandLine.h"
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
#include "llvm/Transforms/Utils.h"

using namespace llvm;

static cl::opt<bool>
    RunHelloWorld("hlw", cl::init(false),
                  cl::desc("PlutoObfuscator - HelloWorld Pass"));

static cl::opt<bool>
    RunFlattening("fla", cl::init(false),
                  cl::desc("PlutoObfuscator - Flattening Pass"));

static cl::opt<bool>
    RunFlatteningEnhanced("fla-ex", cl::init(false),
                          cl::desc("PlutoObfuscator - FlatteningEnhanced"));

static cl::opt<bool>
    RunBogusControlFlow("bcf", cl::init(false),
                        cl::desc("PlutoObfuscator -  BogusControlFlow Pass"));

static cl::opt<bool>
    RunSubstitution("sub", cl::init(false),
                    cl::desc("PlutoObfuscator - Substitution Pass"));

static cl::opt<bool>
    RunGlobalsEncryption("gle", cl::init(false),
                         cl::desc("PlutoObfuscator - GlobalsEncryption Pass"));

static cl::opt<bool> RunVariableSubstitution(
    "vsb", cl::init(false),
    cl::desc("PlutoObfuscator - VariableSubstitution Pass"));

static cl::opt<bool>
    RunRandomControlFlow("rcf", cl::init(false),
                         cl::desc("PlutoObfuscator - RandomControlFlow Pass"));

static cl::opt<bool> RunTrapAngr("trap-angr", cl::init(false),
                                 cl::desc("PlutoObfuscator - TrapAngr Pass"));

static cl::opt<bool>
    RunMBAObfuscation("mba", cl::init(false), 
                      cl::desc("PlutoObfuscator -  MBAObfuscation Pass"));

void llvm::registerModulePasses(legacy::PassManagerBase &MPM) {
    MPM.add(createGlobalsEncryptionPass(RunGlobalsEncryption));
    MPM.add(createFlatteningEnhancedPass(RunFlatteningEnhanced));
}

void llvm::registerFunctionPasses(legacy::PassManagerBase &FPM) {
    FPM.add(createHelloWorldPass(RunHelloWorld));
    FPM.add(createSplitBasicBlockPass());
    FPM.add(createLowerSwitchPass());
    FPM.add(createFlatteningPass(RunFlattening));
    FPM.add(craeteBogusControlFlow(RunBogusControlFlow));
    FPM.add(createSubstitutionPass(RunSubstitution));
    FPM.add(createVariableSubstitutionPass(RunVariableSubstitution));
    FPM.add(createRandomControlFlow(RunRandomControlFlow));
    FPM.add(createTrapAngrPass(RunTrapAngr));
    FPM.add(createMBAObfuscationPass(RunMBAObfuscation));
}
