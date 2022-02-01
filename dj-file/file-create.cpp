#include "file-create.h"
#include "time-fetch.h"
#include <string.h>

void create_main_cpp(void) {
    int i;
    char time_to_print[] = "WWW, MMM. DDth, YYYY. HH:MM:SS AM";
    FILE* F;

    current_time_date(time_to_print);
    if ((F = fopen("src/main.cpp", "r")) == NULL) {
        printf("\"src/main.cpp\" does not exist, create one.\n");
        int run_shell = system("mkdir src");
        (void)run_shell;
        F = fopen("src/main.cpp", "a");
        fprintf(F, "/*********************************************************"
                   "*********************\n");
        fprintf(F, "File Name     : main.cpp\n");
        fprintf(F, "Author        : Dingjiang Zhou\n");
        fprintf(F, "Email         : zhoudingjiang@gmail.com\n");
        fprintf(F, "Create Time   : %s\n", time_to_print);
        fprintf(F, "Last Modified : \n");
        fprintf(F, "Purpose       : \n");
        fprintf(F, "----------------------------------------------------------"
                   "---------------------\n");
        fprintf(F, "INPUTS\n\nOUTPUTS\n\n");
        fprintf(F, "*********************************************************"
                   "*********************/\n");
        fprintf(F, "#include <iostream>\n");
        fprintf(F, "#include <math.h>\n");
        fprintf(F, "#include <stdint.h>\n");
        fprintf(F, "#include <stdio.h>\n");
        fprintf(F, "#include <stdlib.h>\n");
        fprintf(F, "#include <unistd.h>\n\n");
        fprintf(F, "using namespace std;\n\n");
        fprintf(F, "int main(int argc, char* argv[]) {\n");
        fprintf(F, "    ( void )argc;\n");
        fprintf(F, "    ( void )argv;\n");
        fprintf(F, "    return 0;\n");
        fprintf(F, "}\n");
        fclose(F);
    }
    // files exists, only modify src/main.cpp
    else {
        FILE* F2;
        char line_buf[LINE_MAX_LEN];
        char last_modified[17];
        printf("\"src/main.cpp\" exists, modify the \"Last Modified\" item:\n");
        F2 = fopen("src/main.ctemp", "w");  // read from F then write to F2
        // read out "Last Modified", then modify the time behind
        while (fgets(line_buf, LINE_MAX_LEN, F) != NULL) {
            // modify
            // locate "Last Modified "
            for (i = 0; i < 16; i++) {
                last_modified[i] = line_buf[i];
            }
            last_modified[16] = '\0';
            if (strcmp(last_modified, "Last Modified : ") == 0) {
                fprintf(F2, "Last Modified : %s\n", time_to_print);
            }
            else {
                fprintf(F2, "%s", line_buf);
            }
        }
        fclose(F);
        fclose(F2);
        int run_shell = system("mv src/main.ctemp src/main.cpp");
        (void)run_shell;
    }
}

static FILE* create_file(const char filename[]) {
    FILE* F;
    if ((F = fopen(filename, "r")) != NULL) {
        printf("\"%s\" exists, no need to create.\n", filename);
        return NULL;
    }
    else {
        printf("\"%s\" does not exist, create one.\n", filename);
        F = fopen(filename, "w");
    }
    return F;
}

void create_stm32_main_cpp(Stm32Target target) {
    int run_shell = system("mkdir -p src");
    run_shell = system("rm -f src/main.c");
    (void)run_shell;
    FILE* F = create_file("src/main.c");
    if (F == NULL) {
        printf("failed to create \"src/main.c\" file");
        return;
    }

    fprintf(F, "#include \"config.h\"\n\n");
    fprintf(F, "// "
               "==============================================================="
               "==============\n");
    fprintf(F, "static void taskPrint(void) {\n");
    fprintf(F, "    console.printf(\"hello world\\r\\n\");\n");
    fprintf(F, "}\n\n");

    fprintf(F, "// "
               "==============================================================="
               "==============\n");
    fprintf(F, "int main(void) {\n");
    switch (target) {
    case Stm32Target::f030r8:
        fprintf(F, "    utils.system.initClock(48, 48);\n");
        break;
    case Stm32Target::f107xc:
    case Stm32Target::f103rb:
    case Stm32Target::f303re:
        fprintf(F, "    utils.system.initClock(72, 36, 72);\n");
        break;
    case Stm32Target::f407vg:
    case Stm32Target::f407zg:
        fprintf(F, "    utils.system.initClock(168, 42, 84);\n");
        break;
    case Stm32Target::f427vi:
        fprintf(F, "    utils.system.initClock(176, 44, 88);\n");
        break;
    case Stm32Target::f746zg:
    case Stm32Target::f767zi:
        fprintf(F, "    utils.system.initClock(216, 54, 108);\n");
        break;
    case Stm32Target::h750vb:
        fprintf(F, "    utils.system.initClock(480, 120, 120);\n");
        break;
    default:
        break;
    }

    fprintf(F, "    utils.system.initNvic(4);\n");
    fprintf(F, "    stime.config();\n");
    fprintf(F, "    stime.scheduler.config();\n");
    fprintf(F, "    console.config(2000000);\n");
    fprintf(F, "    console.printf(\"\\r\\n\\r\\n\");\n");
    fprintf(F, "    led.config(LED_DOUBLE_BLINK);\n\n");
    fprintf(F, "    // tasks -----------\n");
    fprintf(F,
            "    stime.scheduler.attach(500, 2, taskPrint, \"taskPrint\");\n");
    fprintf(F, "    stime.scheduler.show();\n\n");

    fprintf(F, "    // system starts to run -----------\n");
    fprintf(F, "    stime.scheduler.run();\n");

    fprintf(F, "    console.printf(\"main ends.\\r\\n\");\n");
    fprintf(F, "    return 0;\n");
    fprintf(F, "}\n\n");
}

void create_Makefile(void) {
    FILE* F = create_file("Makefile");
    if (F == NULL) {
        return;
    }
    fprintf(F, "\n# "
               "=============================================================="
               "===============\n");
    fprintf(F, "EXEC      = main\n");
    fprintf(F, "CODE_PATH = .\n");
    fprintf(F, "LIBS      = -lm\n");
    fprintf(F, "LIBS     += -I/usr/local/lib/\n");
    fprintf(F, "OUTPATH   = bin\n");
    fprintf(F, "OPT       = -Og -O0\n");
    fprintf(F, "CC        = g++\n");
    fprintf(F, "CPPSTD    = -std=c++11\n");
    fprintf(F, "MTYPE_ALL = RELEASE\n");
    fprintf(F, "$(info )\n");
    fprintf(F, "$(info ------------------------------------)\n");
    fprintf(F, "$(info LIBS:)\n");
    fprintf(F, "$(info  $(LIBS))\n");
    fprintf(F, "\n# "
               "=============================================================="
               "===============\n");
    fprintf(F, "AS = $(CC) -x assembler-with-cpp\n");
    fprintf(F, "CP = objcopy\n");
    fprintf(F, "SZ = size\n");
    fprintf(F, "\n# "
               "=============================================================="
               "===============\n");
    fprintf(F, "# C_DEFS += -D BIN_NAME=\\\"$(EXEC)\\\"\n");
    fprintf(F, "# C_DEFS += -D PRJ_GIT_CMT=\\\"$(shell git rev-parse --short "
               "HEAD)\\\"\n");
    fprintf(F,
            "# C_DEFS += -D PRJ_GIT_BRH=\\\"$(shell git rev-parse --abbrev-ref "
            "HEAD)\\\"\n");
    fprintf(F, "# C_DEFS += -D PRJ_GIT_VER=\\\"$(shell git describe --abbrev=7 "
               "--dirty --always --tags)\\\"\n");
    fprintf(F, "\n# "
               "=============================================================="
               "===============\n");
    fprintf(F, "# collect '.cpp' file to SRCS\n");
    fprintf(F, "DIRS := $(shell find $(CODE_PATH) -maxdepth 10 -type d)\n");
    fprintf(F, "SRCS  = $(foreach dir,$(DIRS),$(wildcard $(dir)/*.cpp))\n");
    fprintf(F, "$(info )\n");
    fprintf(F, "$(info ------------------------------------)\n");
    fprintf(F, "$(info source files:)\n");
    fprintf(F, "$(info  $(SRCS))\n");
    fprintf(F, "\nOBJS     = $(addprefix $(OUTPATH)/,$(notdir "
               "$(SRCS:.cpp=.o)))\n");
    fprintf(F, "vpath %%.cpp $(sort $(dir $(SRCS)))\n");
    fprintf(F, "$(info )\n");
    fprintf(F, "$(info ------------------------------------)\n");
    fprintf(F, "$(info object files:)\n");
    fprintf(F, "$(info  $(OBJS))\n");
    fprintf(F, "\n# collect '.h' files in INC\n");
    fprintf(F, "INCH = $(foreach dir,$(DIRS),$(wildcard $(dir)/*.h))\n");
    fprintf(F, "INC  = $(shell find -L $(INCH) -name '*.h' -exec dirname {} "
               "\\; | uniq)\n");
    fprintf(F, "$(info )\n");
    fprintf(F, "$(info ------------------------------------)\n");
    fprintf(F, "$(info headers to include:)\n");
    fprintf(F, "$(info  $(INC:%%=-I%%))\n");
    fprintf(F, "\n$(info )\n");
    fprintf(F, "$(info ====================================)\n");
    fprintf(F, "$(info )\n");

    fprintf(F, "\n# "
               "=============================================================="
               "===============\n");
    fprintf(F, "CFLAGS    = $(C_DEFS) $(INC:%%=-I%%) $(OPT)\n");
    fprintf(F, "# treat all warnings as errors\n");
    fprintf(F, "CFLAGS  += -Werror=unused-parameter -Werror=unused-variable\n");
    fprintf(F, "HOSTFLAGS = $(CPPSTD) $(LIBS)\n");
    fprintf(F, "\n# "
               "=============================================================="
               "===============\n");
    fprintf(F, ".PHONY: all\n");
    fprintf(F, "all: CFLAGS+= -D MAKE_TYPE=\\\"$(MTYPE_ALL)\\\"\n");
    fprintf(F, "all: CFLAGS+= $(HOSTFLAGS)\n");
    fprintf(F, "all: $(OBJS)\n");
    fprintf(F, "\t$(CC) -o $(OUTPATH)/$(EXEC) $(OBJS) $(CFLAGS)\n");
    fprintf(F, "\t$(SZ) $(OUTPATH)/$(EXEC)\n");
    fprintf(F, "\n$(OUTPATH)/%%.o: %%.cpp | $(OUTPATH)\n");
    fprintf(F, "\t$(CC) -c $(CFLAGS) $< -o $@\n");
    fprintf(F, "\n$(OUTPATH):\n");
    fprintf(F, "\tmkdir -p $@\n");
    fprintf(F, "\n# ------------------------------------------------\n");
    fprintf(F, "clean:\n");
    fprintf(F, "\trm -f $(OUTPATH)/*\n");
    fclose(F);
}

void create_stm32_Makefile(Stm32Target stm32_target) {
    (void)stm32_target;
}

void create_CMakeLists_txt(void) {
    FILE* F = create_file("CMakeLists.txt");
    if (F == NULL) {
        return;
    }
    fprintf(F, "cmake_minimum_required(VERSION 3.10)\n");
    fprintf(F, "project(cmake-project)\n");
    fprintf(F, "set(CMAKE_CXX_STANDARD 17)\n");
    fprintf(F, "add_compile_options(\n");
    fprintf(F, "  -Wall\n");
    fprintf(F, "  -Wextra\n");
    fprintf(F, "  -pedantic\n");
    fprintf(F, "  -Werror\n");
    fprintf(F, "  -Wformat=2\n");
    fprintf(F, "  -Wduplicated-cond\n");
    fprintf(F, "  -Wfloat-equal\n");
    fprintf(F, "  -Wshadow\n");
    fprintf(F, "  -Wconversion\n");
    fprintf(F, "  -Wlogical-not-parentheses\n");
    fprintf(F, ")\n\n");

    fprintf(F, "# ------------------------------\n");
    fprintf(F, "add_executable(\n");
    fprintf(F, "  main\n");
    fprintf(F, "  src/main.cpp\n");
    fprintf(F, ")\n");
    fprintf(F, "# target_link_libraries(\n");
    fprintf(F, "#   main\n");
    fprintf(F, "# )\n");
    fprintf(F, "# install(TARGETS main RUNTIME DESTINATION bin)\n\n");

    // static library
    fprintf(F, "# ------------------------------\n");
    fprintf(F, "# set(SRC_FILES\n");
    fprintf(F, "#     src/xxx.c\n");
    fprintf(F, "# )\n");
    fprintf(F, "# set(HEADER_FILES\n");
    fprintf(F, "#     inc/xxx.h\n");
    fprintf(F, "# )\n\n");

    fprintf(F, "# add_library(yyy STATIC \"${SRC_FILES}\")\n");
    fprintf(F, "# set_target_properties(yyy PROPERTIES PUBLIC_HEADER "
               "\"${HEADER_FILES}\")\n");
    fprintf(F, "# INSTALL(TARGETS yyy\n");
    fprintf(F, "#     ARCHIVE DESTINATION /usr/local/lib\n");
    fprintf(F, "#     LIBRARY DESTINATION /usr/local/lib\n");
    fprintf(F, "#     PUBLIC_HEADER DESTINATION /usr/local/include/yyy/\n");
    fprintf(F, "# )\n");

    fclose(F);
}

void create_editor_config(void) {
    FILE* F = create_file(".editorconfig");
    if (F == NULL) {
        return;
    }
    fprintf(F, "root = true\n\n");

    fprintf(F, "[*]\n");
    fprintf(F, "end_of_line = lf\n");
    fprintf(F, "insert_final_newline = true\n");
    fprintf(F, "trim_trailing_whitespace = true\n");
    fprintf(F, "charset = utf-8\n\n");

    fprintf(F, "[*.{c,h,cc,hh,cpp,cxx,hpp}]\n");
    fprintf(F, "indent_size = 4\n");
    fprintf(F, "indent_style = space\n\n");

    fprintf(F, "[{CMakeLists.txt,meson.build}]\n");
    fprintf(F, "indent_size = 2\n");
    fprintf(F, "indent_style = space\n\n");

    fprintf(F, "[*.{yml,yaml}]\n");
    fprintf(F, "indent_size = 2\n");
    fprintf(F, "indent_style = space\n\n");

    fprintf(F, "[*.diff]\n");
    fprintf(F, "insert_final_newline = false\n");
    fprintf(F, "trim_trailing_whitespace = false\n\n");

    fprintf(F, "[*.proto]\n");
    fprintf(F, "indent_size = 2\n");
    fprintf(F, "indent_style = space\n\n");

    fprintf(F, "[Dockerfile*]\n");
    fprintf(F, "indent_size = 4\n");
    fprintf(F, "indent_style = space\n");

    fclose(F);
}

void create_clang_format(void) {
    FILE* F = create_file(".clang-format");
    if (F == NULL) {
        return;
    }
    fprintf(F, "Language: Cpp\n");
    fprintf(F, "AccessModifierOffset: -4\n");
    fprintf(F, "AlignAfterOpenBracket: Align\n");
    fprintf(F, "AlignConsecutiveAssignments: false\n");
    fprintf(F, "AlignConsecutiveDeclarations: false\n");
    fprintf(F, "AlignEscapedNewlinesLeft: true\n");
    fprintf(F, "AlignOperands: true\n");
    fprintf(F, "AlignTrailingComments: true\n");
    fprintf(F, "AllowAllParametersOfDeclarationOnNextLine: true\n");
    fprintf(F, "AllowShortBlocksOnASingleLine: false\n");
    fprintf(F, "AllowShortCaseLabelsOnASingleLine: false\n");
    fprintf(F, "AllowShortFunctionsOnASingleLine: Empty\n");
    fprintf(F, "AllowShortIfStatementsOnASingleLine: false\n");
    fprintf(F, "AllowShortLoopsOnASingleLine: false\n");
    fprintf(F, "AlwaysBreakAfterDefinitionReturnType: None\n");
    fprintf(F, "AlwaysBreakAfterReturnType: None\n");
    fprintf(F, "AlwaysBreakBeforeMultilineStrings: false\n");
    fprintf(F, "AlwaysBreakTemplateDeclarations: false\n");
    fprintf(F, "BinPackArguments: true\n");
    fprintf(F, "BinPackParameters: true\n");
    fprintf(F, "BraceWrapping:\n");
    fprintf(F, "  AfterClass: false\n");
    fprintf(F, "  AfterControlStatement: false\n");
    fprintf(F, "  AfterEnum: false\n");
    fprintf(F, "  AfterFunction: false\n");
    fprintf(F, "  AfterNamespace: false\n");
    fprintf(F, "  AfterObjCDeclaration: false\n");
    fprintf(F, "  AfterStruct: false\n");
    fprintf(F, "  AfterUnion: false\n");
    fprintf(F, "  BeforeCatch: true\n");
    fprintf(F, "  BeforeElse: true\n");
    fprintf(F, "  IndentBraces: false\n");
    fprintf(F, "BreakBeforeBinaryOperators: NonAssignment\n");
    fprintf(F, "BreakBeforeBraces: Custom\n");
    fprintf(F, "BreakBeforeTernaryOperators: true\n");
    fprintf(F, "BreakConstructorInitializersBeforeComma: false\n");
    fprintf(F, "ColumnLimit: 80\n");
    fprintf(F, "CommentPragmas: \"^ IWYU pragma:\"\n");
    fprintf(F, "ConstructorInitializerAllOnOneLineOrOnePerLine: false\n");
    fprintf(F, "ConstructorInitializerIndentWidth: 4\n");
    fprintf(F, "ContinuationIndentWidth: 4\n");
    fprintf(F, "Cpp11BracedListStyle: false\n");
    fprintf(F, "DerivePointerAlignment: false\n");
    fprintf(F, "DisableFormat: false\n");
    fprintf(F, "ExperimentalAutoDetectBinPacking: false\n");
    fprintf(F, "ForEachMacros: [foreach, Q_FOREACH, BOOST_FOREACH]\n");
    fprintf(F, "IncludeCategories:\n");
    fprintf(F, "  - Regex: '^\"(llvm|llvm-c|clang|clang-c)/'\n");
    fprintf(F, "    Priority: 2\n");
    fprintf(F, "  - Regex: '^(<|\"(gtest|isl|json)/)'\n");
    fprintf(F, "    Priority: 3\n");
    fprintf(F, "  - Regex: \".*\"\n");
    fprintf(F, "    Priority: 1\n");
    fprintf(F, "IndentCaseLabels: false\n");
    fprintf(F, "IndentWidth: 4\n");
    fprintf(F, "IndentWrappedFunctionNames: false\n");
    fprintf(F, "KeepEmptyLinesAtTheStartOfBlocks: true\n");
    fprintf(F, "MacroBlockBegin: \"\"\n");
    fprintf(F, "MacroBlockEnd: \"\"\n");
    fprintf(F, "MaxEmptyLinesToKeep: 1\n");
    fprintf(F, "NamespaceIndentation: Inner\n");
    fprintf(F, "ObjCBlockIndentWidth: 4\n");
    fprintf(F, "ObjCSpaceAfterProperty: false\n");
    fprintf(F, "ObjCSpaceBeforeProtocolList: true\n");
    fprintf(F, "PenaltyBreakBeforeFirstCallParameter: 19\n");
    fprintf(F, "PenaltyBreakComment: 300\n");
    fprintf(F, "PenaltyBreakFirstLessLess: 120\n");
    fprintf(F, "PenaltyBreakString: 1000\n");
    fprintf(F, "PenaltyExcessCharacter: 1000000\n");
    fprintf(F, "PenaltyReturnTypeOnItsOwnLine: 60\n");
    fprintf(F, "PointerAlignment: Left\n");
    fprintf(F, "ReflowComments: true\n");
    fprintf(F, "SortIncludes: true\n");
    fprintf(F, "SpaceAfterCStyleCast: false\n");
    fprintf(F, "SpaceBeforeAssignmentOperators: true\n");
    fprintf(F, "SpaceBeforeParens: ControlStatements\n");
    fprintf(F, "SpaceInEmptyParentheses: false\n");
    fprintf(F, "SpacesBeforeTrailingComments: 2\n");
    fprintf(F, "SpacesInAngles: false\n");
    fprintf(F, "SpacesInContainerLiterals: true\n");
    fprintf(F, "SpacesInCStyleCastParentheses: false\n");
    fprintf(F, "SpacesInParentheses: false\n");
    fprintf(F, "SpacesInSquareBrackets: false\n");
    fprintf(F, "Standard: Cpp11\n");
    fprintf(F, "TabWidth: 4\n");
    fprintf(F, "UseTab: Never\n");
    fclose(F);
}

void create_gitignore(void) {
    FILE* F = create_file(".gitignore");
    if (F == NULL) {
        return;
    }
    fprintf(F, "*.csv\n");
    fprintf(F, "*.diff\n");
    fprintf(F, "*.log\n");
    fprintf(F, "*.stacks\n");
    fprintf(F, "*.svg\n");
    fprintf(F, ".cache\n");
    fprintf(F, ".gdb_history\n");
    fprintf(F, ".vscode\n");
    fprintf(F, "target\n");
    fprintf(F, "_*\n");
    fprintf(F, "build\n");
    fprintf(F, "node_modules\n");
    fprintf(F, "perf.*\n");
    fprintf(F, "tags\n");
    fprintf(F, "gmn*\n");
    fclose(F);
}
