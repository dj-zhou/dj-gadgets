/***********************************************************
    >   File Name     : time-fetch.c
    >   Author        : Dingjiang Zhou
                        Tieling 110, Shanghai, China.
    >   Create Time   : Tue 12 Feb 2013 10:36:24 PM CST
    >   Last Modified :
    >   Purpose       :
***********************************************************/
#include "file-create.h"

void create_main_cpp(void) {
    int   i;
    char  time_to_print[] = "WWW, MMM. DDth, YYYY. HH:MM:SS AM";
    FILE* F;
    int   run_shell;

    current_time_date(time_to_print);
    if ((F = fopen("src/main.cpp", "r")) == NULL) {
        printf("No \"src/main.cpp\" exists, create one.\n");
        run_shell = system("mkdir src");
        F         = fopen("src/main.cpp", "a");
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
    else /* files exists, only modify src/main.cpp */
    {
        int   run_shell = 0;
        FILE* F2;
        char  line_buf[LINE_MAX_LEN];
        char  last_modified[17];
        printf("\"src/main.cpp\" exists, modify the \"Last Modified\" item:\n");
        F2 = fopen("src/main.ctemp", "w"); /* read from F then write to F2 */
        /* read out "Last Modified", then modify the time behind */
        while (fgets(line_buf, LINE_MAX_LEN, F) != NULL) {
            /* modify */
            /* locate "Last Modified " */
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
        run_shell = system("mv src/main.ctemp src/main.cpp");

        /* create the Makefile */
        /* if exist the Makefile, don't have to generate again */
        if ((F2 = fopen("Makefile", "r")) != NULL) /* file exists */
        {
            printf("<Makefile> exists, exit.\n");
            fclose(F2);
            exit;
        }
        else {
            create_Makefile();
        }
    }
}

static FILE* create_file(const char filename[]) {
    FILE* F;
    if ((F = fopen(filename, "r")) != NULL) {
        printf("\"%s\" exists, no need to create.\n", filename);
        exit(-1);
    }
    else {
        printf("\"%s\" does not exist, create one.\n", filename);
        F = fopen(filename, "w");
    }
    return F;
}
void create_Makefile(void) {

    FILE* F = create_file("Makefile");
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

void create_CMakeLists_txt(void) {
    FILE* F = create_file("CMakeLists.txt");
    fprintf(F, "cmake_minimum_required(VERSION 3.5)\n");
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
    fclose(F);
}

void create_editor_config(void) {
    FILE* F = create_file(".editorconfig");
    fprintf(F, "root = true\n\n");

    fprintf(F, "[*]\n");
    fprintf(F, "end_of_line = lf\n");
    fprintf(F, "insert_final_newline = true\n");
    fprintf(F, "trim_trailing_whitespace = true\n");
    fprintf(F, "charset = utf-8\n\n");

    fprintf(F, "[*.diff]\n");
    fprintf(F, "insert_final_newline = false\n");
    fprintf(F, "trim_trailing_whitespace = false\n\n");

    fprintf(F, "[*.{c,h}]\n");
    fprintf(F, "indent_style = tab\n");
    fprintf(F, "indent_size = 8\n\n");

    fprintf(F, "[*.{cc,hh,cpp,cxx,hpp}]\n");
    fprintf(F, "indent_style = space\n");
    fprintf(F, "indent_size = 4\n\n");

    fprintf(F, "[*.x]\n");
    fprintf(F, "indent_style = space\n");
    fprintf(F, "indent_size = 2\n\n");

    fprintf(F, "[.uncrustify.cfg]\n");
    fprintf(F, "indent_style = space\n\n");

    fprintf(F, "[Dockerfile*]\n");
    fprintf(F, "indent_size = 4\n");
    fprintf(F, "indent_style = space\n\n");

    fprintf(F, "[{BUILD.bazel,*.bzl,WORKSPACE}]\n");
    fprintf(F, "indent_size = 4\n");
    fprintf(F, "indent_style = space\n\n");

    fprintf(F, "[*.{yml,yaml}]\n");
    fprintf(F, "indent_size = 2\n");
    fprintf(F, "indent_style = space\n\n");

    fprintf(F, "[*.proto]\n");
    fprintf(F, "indent_size = 2\n");
    fprintf(F, "indent_style = space\n\n");

    fclose(F);
}

void create_clang_format(void) {
    FILE* F = create_file(".clang-format");
    fprintf(F, "Language: Cpp\n");
    fprintf(F, "AccessModifierOffset: -4\n");
    fprintf(F, "AlignAfterOpenBracket: Align\n");
    fprintf(F, "AlignConsecutiveAssignments: true\n");
    fprintf(F, "AlignConsecutiveDeclarations: true\n");
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
    fprintf(F, "AlwaysBreakTemplateDeclarations: true\n");
    fprintf(F, "BinPackArguments: true\n");
    fprintf(F, "BinPackParameters: true\n");
    fprintf(F, "BraceWrapping:\n");
    fprintf(F, "    AfterClass: false\n");
    fprintf(F, "    AfterControlStatement: false\n");
    fprintf(F, "    AfterEnum: false\n");
    fprintf(F, "    AfterFunction: false\n");
    fprintf(F, "    AfterNamespace: false\n");
    fprintf(F, "    AfterObjCDeclaration: false\n");
    fprintf(F, "    AfterStruct: false\n");
    fprintf(F, "    AfterUnion: false\n");
    fprintf(F, "    BeforeCatch: true\n");
    fprintf(F, "    BeforeElse: true\n");
    fprintf(F, "    IndentBraces: false\n");
    fprintf(F, "BreakBeforeBinaryOperators: NonAssignment\n");
    fprintf(F, "BreakBeforeBraces: Custom\n");
    fprintf(F, "BreakBeforeTernaryOperators: true\n");
    fprintf(F, "BreakConstructorInitializersBeforeComma: false\n");
    fprintf(F, "ColumnLimit: 80\n");
    fprintf(F, "CommentPragmas: '^ IWYU pragma:'\n");
    fprintf(F, "ConstructorInitializerAllOnOneLineOrOnePerLine: false\n");
    fprintf(F, "ConstructorInitializerIndentWidth: 4\n");
    fprintf(F, "ContinuationIndentWidth: 4\n");
    fprintf(F, "Cpp11BracedListStyle: false\n");
    fprintf(F, "DerivePointerAlignment: false\n");
    fprintf(F, "DisableFormat: false\n");
    fprintf(F, "ExperimentalAutoDetectBinPacking: false\n");
    fprintf(F, "ForEachMacros: [ foreach, Q_FOREACH, BOOST_FOREACH ]\n");
    fprintf(F, "IncludeCategories:\n");
    fprintf(F, "  - Regex: '^\"(llvm|llvm-c|clang|clang-c)/'\n");
    fprintf(F, "    Priority: 2\n");
    fprintf(F, "  - Regex: '^(<|\"(gtest|isl|json)/)'\n");
    fprintf(F, "    Priority: 3\n");
    fprintf(F, "  - Regex: '.*'\n");
    fprintf(F, "    Priority: 1\n");
    fprintf(F, "IndentCaseLabels: false\n");
    fprintf(F, "IndentWidth: 4\n");
    fprintf(F, "IndentWrappedFunctionNames: false\n");
    fprintf(F, "KeepEmptyLinesAtTheStartOfBlocks: true\n");
    fprintf(F, "MacroBlockBegin: ''\n");
    fprintf(F, "MacroBlockEnd: ''\n");
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
    fprintf(F, "SpacesInCStyleCastParentheses: true\n");
    fprintf(F, "SpacesInParentheses: false\n");
    fprintf(F, "SpacesInSquareBrackets: false\n");
    fprintf(F, "Standard: Cpp11\n");
    fprintf(F, "TabWidth: 4\n");
    fprintf(F, "UseTab: Never\n");
    fclose(F);
}

void create_gitignore(void) {
    FILE* F = create_file(".clang-format");
    fprintf(F, "*.csv\n");
    fprintf(F, "*.diff\n");
    fprintf(F, "*.log\n");
    fprintf(F, "*.stacks\n");
    fprintf(F, "*.svg\n");
    fprintf(F, ".cache\n");
    fprintf(F, ".clangd\n");
    fprintf(F, ".dorkspacerc.cache.yaml\n");
    fprintf(F, ".gdb_history\n");
    fprintf(F, ".ipynb_checkpoints\n");
    fprintf(F, ".vscode\n");
    fprintf(F, "target\n");
    fprintf(F, "_*\n");
    fprintf(F, "bazel-*\n");
    fprintf(F, "build\n");
    fprintf(F, "compile_commands.json\n");
    fprintf(F, "node_modules\n");
    fprintf(F, "perf.*\n");
    fprintf(F, "tags\n");
    fprintf(F, "user.bazelrc\n");
    fprintf(F, "gmn*\n");
    fclose(F);
}

void create_cpp_file(char* fileName) {
    int  i;
    char time_to_print[] = "WWW, MMM. DDth, YYYY. HH:MM:SS AM";
    int  lenName;
    lenName          = strlen(fileName);
    char* headerName = ( char* )malloc((lenName + 1) * sizeof(char));
    for (i = 0; i < lenName - 1; i++)
        headerName[i] = fileName[i];
    headerName[lenName - 1] = 'h';
    headerName[lenName]     = '\0';
    FILE* F;
    current_time_date(time_to_print);
    if ((F = fopen(fileName, "r")) == NULL) /* does not exist */
    {
        printf("No <%s> exists, create one.\n", fileName);
        F = fopen(fileName, "a");
        fprintf(F, "/*********************************************************"
                   "*********************\n");
        fprintf(F, "File Name     : %s\n", fileName);
        fprintf(F, "Author        : Dingjiang Zhou\n");
        fprintf(F, "Email         : zhoudingjiang@gmail.com\n");
        fprintf(F, "Create Time   : %s\n", time_to_print);
        fprintf(F, "Last Modified : \n");
        fprintf(F, "Purpose       : \n");
        fprintf(F, "----------------------------------------------------------"
                   "---------------------\n");
        fprintf(F, "INPUTS\n\nOUTPUTS\n\n");
        fprintf(F, "**********************************************************"
                   "********************/\n");
        fprintf(F, "#include \"%s\"\n\n", headerName);
        fprintf(F, "int fncs(void)\n");
        fprintf(F, "{\n");
        /* fprintf(F,"    printf(\"Hello, Dingjiang!\\n\");\n"); */
        fprintf(F, "    return 0;\n");
        fprintf(F, "}\n");
        /* the above cannot be generated twice */
        fclose(F);
    }
    else /* files exists */
    {
        int run_shell = 0;

        int   i;
        FILE* F2;
        char  line_buf[LINE_MAX_LEN];
        char  last_modified[17];

        char tempFileName[lenName + 5];
        strcpy(tempFileName, fileName);
        tempFileName[lenName]     = 't';
        tempFileName[lenName + 1] = 'e';
        tempFileName[lenName + 2] = 'm';
        tempFileName[lenName + 3] = 'p';
        tempFileName[lenName + 4] = '\0';
        printf("<%s> exists, modify the \"Last Modified\" item:\n", fileName);
        F2 = fopen(tempFileName, "w"); /* read from F then write to F2 */
        /* read out "Last Modified", then modify the time behind */
        while (fgets(line_buf, LINE_MAX_LEN, F) != NULL) {
            /* modify */
            /* locate "Last Modified " */
            for (i = 0; i < 16; i++) {
                last_modified[i] = line_buf[i];
            }
            last_modified[16] = '\0';
            if (strcmp(last_modified, "Last Modified :") == 0) {
                fprintf(F2, "Last Modified : %s\n", time_to_print);
            }
            else {
                fprintf(F2, "%s", line_buf);
            }
        }
        fclose(F);
        fclose(F2);

        /* to form the mv command */
        int sysCmdLen;
        sysCmdLen = 9 + 2 * lenName;
        char sysCmdVim[sysCmdLen];

        strcpy(sysCmdVim, "mv ");

        for (i = 3; i < 3 + lenName; i++) {
            sysCmdVim[i] = fileName[i - 3];
        }

        sysCmdVim[lenName + 3] = 't';
        sysCmdVim[lenName + 4] = 'e';
        sysCmdVim[lenName + 5] = 'm';
        sysCmdVim[lenName + 6] = 'p';
        sysCmdVim[lenName + 7] = ' ';

        for (i = lenName + 8; i < 2 * lenName + 8; i++)
            sysCmdVim[i] = fileName[i - lenName - 8];
        sysCmdVim[sysCmdLen] = '\0';

        /* run the cmd: mv hello.ctemp hello.c */
        run_shell = system(sysCmdVim);
    }
}

/* --------------------------------- */
void create_header_file(char* fileName) {
    int  i;
    char time_to_print[] = "WWW, MMM. DDth, YYYY. HH:MM:SS AM";
    int  lenName;
    lenName = strlen(fileName);
    /* convert the low case name to captical name */
    char* headerNameCap = ( char* )malloc((lenName + 1) * sizeof(char));
    for (i = 0; i < lenName; i++) {
        if (fileName[i] >= 'a' && fileName[i] <= 'z')
            headerNameCap[i] = fileName[i] - 32;
        else if (fileName[i] >= 'A' && fileName[i] <= 'Z')
            headerNameCap[i] = fileName[i];
        else if (fileName[i] == '.')
            headerNameCap[i] = '_';
    }
    headerNameCap[lenName + 1] = '\0'; /* the end of a string */
    /* creat the file */
    FILE* F;
    current_time_date(time_to_print);
    if ((F = fopen(fileName, "r")) == NULL) /* does not exist */
    {
        printf("No <%s> exists, create one.\n", fileName);
        F = fopen(fileName, "a");
        fprintf(F, "/*********************************************************"
                   "*********************\n");
        fprintf(F, "File Name     : %s\n", fileName);
        fprintf(F, "Author        : Dingjiang Zhou\n");
        fprintf(F, "Email         : zhoudingjiang@gmail.com\n");
        fprintf(F, "Create Time   : %s\n", time_to_print);
        fprintf(F, "Last Modified : \n");
        fprintf(F, "Purpose       : \n");
        fprintf(F, "----------------------------------------------------------"
                   "---------------------\n");
        fprintf(F, "INPUTS\n\nOUTPUTS\n\n");
        fprintf(F, "**********************************************************"
                   "********************/\n");
        fprintf(F, "#ifndef __%s__\n", headerNameCap);
        fprintf(F, "#define __%s__\n\n", headerNameCap);
        fprintf(F, "#include <stdio.h>\n");
        fprintf(F, "#include <stdlib.h>\n");
        fprintf(F, "#include <unistd.h>\n");
        fprintf(F, "#include <stdint.h>\n\n");
        fprintf(F, "/* typedef struct{\n\n}; */\n\n\n");
        fprintf(F, "/* variables declaration */\n\n\n");
        fprintf(F, "/* functions declaration */\n\n\n");
        fprintf(F, "#endif\n");
        /* the above cannot be generated twice */
        fclose(F);
    }
    else /* files exists */
    {
        int run_shell = 0;

        int   i;
        FILE* F2;
        char  line_buf[LINE_MAX_LEN];
        char  last_modified[14];

        char tempFileName[lenName + 5];
        strcpy(tempFileName, fileName);
        tempFileName[lenName]     = 't';
        tempFileName[lenName + 1] = 'e';
        tempFileName[lenName + 2] = 'm';
        tempFileName[lenName + 3] = 'p';
        tempFileName[lenName + 4] = '\0';
        printf("<%s> exists, modify the \"Last Modified\" item:\n", fileName);
        F2 = fopen(tempFileName, "w"); /* read from F then write to F2 */
        /* read out "Last Modified", then modify the time behind */
        while (fgets(line_buf, LINE_MAX_LEN, F) != NULL) {
            /* modify */
            /* locate "Last Modified " */
            for (i = 0; i < 13; i++)
                last_modified[i] = line_buf[i + 3];
            last_modified[13] = '\0';
            if (strcmp(last_modified, "Last Modified") == 0) {
                fprintf(F2, "   Last Modified  : %s\n", time_to_print);
            }
            else
                fprintf(F2, "%s", line_buf);
        }
        fclose(F);
        fclose(F2);

        /* to form the mv command */
        int sysCmdLen;
        sysCmdLen = 9 + 2 * lenName;
        char sysCmdVim[sysCmdLen];

        strcpy(sysCmdVim, "mv ");

        for (i = 3; i < 3 + lenName; i++) {
            sysCmdVim[i] = fileName[i - 3];
        }

        sysCmdVim[lenName + 3] = 't';
        sysCmdVim[lenName + 4] = 'e';
        sysCmdVim[lenName + 5] = 'm';
        sysCmdVim[lenName + 6] = 'p';
        sysCmdVim[lenName + 7] = ' ';

        for (i = lenName + 8; i < 2 * lenName + 8; i++)
            sysCmdVim[i] = fileName[i - lenName - 8];
        sysCmdVim[sysCmdLen] = '\0';

        /* run the cmd: mv hello.ctemp hello.c */
        run_shell = system(sysCmdVim);
    }
}