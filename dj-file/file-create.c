/***********************************************************
    >   File Name     : time-fetch.c
    >   Author        : Dingjiang Zhou
                        Tieling 110, Shanghai, China.
    >   Create Time   : Tue 12 Feb 2013 10:36:24 PM CST
    >   Last Modified :
    >   Purpose       :
***********************************************************/
#include "file-create.h"

void create_main_cpp( void ) {
    int   i;
    char  time_to_print[] = "WWW, MMM. DDth, YYYY. HH:MM:SS AM";
    FILE* F;
    int   run_shell;
    /* need to judge if the file already exist */
    current_time_date( time_to_print );
    if ( ( F = fopen( "src/main.cpp", "r" ) ) == NULL ) /* does not exist */
    {
        printf( "No \"src/main.cpp\" exists, create one.\n" );
        run_shell = system( "mkdir src" );
        F         = fopen( "src/main.cpp", "a" );
        fprintf( F, "/*********************************************************"
                    "*********************\n" );
        fprintf( F, "File Name     : main.cpp\n" );
        fprintf( F, "Author        : Dingjiang Zhou\n" );
        fprintf( F, "Email         : zhoudingjiang@gmail.com\n" );
        fprintf( F, "Create Time   : %s\n", time_to_print );
        fprintf( F, "Last Modified : \n" );
        fprintf( F, "Purpose       : \n" );
        fprintf( F, "----------------------------------------------------------"
                    "---------------------\n" );
        fprintf( F, "INPUTS\n\nOUTPUTS\n\n" );
        fprintf( F, "*********************************************************"
                    "*********************/\n" );
        fprintf( F, "#include <iostream>\n" );
        fprintf( F, "#include <math.h>\n" );
        fprintf( F, "#include <stdint.h>\n" );
        fprintf( F, "#include <stdio.h>\n" );
        fprintf( F, "#include <stdlib.h>\n" );
        fprintf( F, "#include <unistd.h>\n\n" );
        fprintf( F, "using namespace std;\n\n" );
        fprintf( F, "int main(int argc, char* argv[]) {\n" );
        fprintf( F, "    ( void )argc;\n" );
        fprintf( F, "    ( void )argv;\n" );
        fprintf( F, "    return 0;\n" );
        fprintf( F, "}\n" );
        fclose( F );
    }
    else /* files exists, only modify src/main.cpp */
    {
        int   run_shell = 0;
        FILE* F2;
        char  line_buf[LINE_MAX_LEN];
        char  last_modified[17];
        printf(
            "\"src/main.cpp\" exists, modify the \"Last Modified\" item:\n" );
        F2 = fopen( "src/main.ctemp", "w" ); /* read from F then write to F2 */
        /* read out "Last Modified", then modify the time behind */
        while ( fgets( line_buf, LINE_MAX_LEN, F ) != NULL ) {
            /* modify */
            /* locate "Last Modified " */
            for ( i = 0; i < 16; i++ ) {
                last_modified[i] = line_buf[i];
            }
            last_modified[16] = '\0';
            if ( strcmp( last_modified, "Last Modified : " ) == 0 ) {
                fprintf( F2, "Last Modified : %s\n", time_to_print );
            }
            else {
                fprintf( F2, "%s", line_buf );
            }
        }
        fclose( F );
        fclose( F2 );
        run_shell = system( "mv src/main.ctemp src/main.cpp" );

        /* create the Makefile */
        /* if exist the Makefile, don't have to generate again */
        if ( ( F2 = fopen( "Makefile", "r" ) ) != NULL ) /* file exists */
        {
            printf( "<Makefile> exists, exit.\n" );
            fclose( F2 );
            exit;
        }
        else {
            create_Makefile();
        }
    }
}

void create_Makefile( void ) {

    /* create the Makefile */
    FILE* F;
    if ( ( F = fopen( "Makefile", "r" ) ) == NULL ) {
        printf( "No \"Makefile\" exists, create one.\n" );
        F = fopen( "Makefile", "w" );
        fprintf(
            F, "\n# "
               "=============================================================="
               "===============\n" );
        fprintf( F, "EXEC      = main\n" );
        fprintf( F, "CODE_PATH = .\n" );
        fprintf( F, "LIBS      = -lm\n" );
        fprintf( F, "LIBS     += -I/usr/local/lib/\n" );
        fprintf( F, "OUTPATH   = bin\n" );
        fprintf( F, "OPT       = -Og -O0\n" );
        fprintf( F, "CC        = g++\n" );
        fprintf( F, "CPPSTD    = -std=c++11\n" );
        fprintf( F, "MTYPE_ALL = RELEASE\n" );
        fprintf( F, "$(info )\n" );
        fprintf( F, "$(info ------------------------------------)\n" );
        fprintf( F, "$(info LIBS:)\n" );
        fprintf( F, "$(info  $(LIBS))\n" );
        fprintf(
            F, "\n# "
               "=============================================================="
               "===============\n" );
        fprintf( F, "AS = $(CC) -x assembler-with-cpp\n" );
        fprintf( F, "CP = objcopy\n" );
        fprintf( F, "SZ = size\n" );
        fprintf(
            F, "\n# "
               "=============================================================="
               "===============\n" );
        fprintf( F, "# C_DEFS += -D BIN_NAME=\\\"$(EXEC)\\\"\n" );
        fprintf( F,
                 "# C_DEFS += -D PRJ_GIT_CMT=\\\"$(shell git rev-parse --short "
                 "HEAD)\\\"\n" );
        fprintf(
            F,
            "# C_DEFS += -D PRJ_GIT_BRH=\\\"$(shell git rev-parse --abbrev-ref "
            "HEAD)\\\"\n" );
        fprintf(
            F, "# C_DEFS += -D PRJ_GIT_VER=\\\"$(shell git describe --abbrev=7 "
               "--dirty --always --tags)\\\"\n" );
        fprintf(
            F, "\n# "
               "=============================================================="
               "===============\n" );
        fprintf( F, "# collect '.cpp' file to SRCS\n" );
        fprintf( F,
                 "DIRS := $(shell find $(CODE_PATH) -maxdepth 10 -type d)\n" );
        fprintf( F,
                 "SRCS  = $(foreach dir,$(DIRS),$(wildcard $(dir)/*.cpp))\n" );
        fprintf( F, "$(info )\n" );
        fprintf( F, "$(info ------------------------------------)\n" );
        fprintf( F, "$(info source files:)\n" );
        fprintf( F, "$(info  $(SRCS))\n" );
        fprintf( F, "\nOBJS     = $(addprefix $(OUTPATH)/,$(notdir "
                    "$(SRCS:.cpp=.o)))\n" );
        fprintf( F, "vpath %%.cpp $(sort $(dir $(SRCS)))\n" );
        fprintf( F, "$(info )\n" );
        fprintf( F, "$(info ------------------------------------)\n" );
        fprintf( F, "$(info object files:)\n" );
        fprintf( F, "$(info  $(OBJS))\n" );
        fprintf( F, "\n# collect '.h' files in INC\n" );
        fprintf( F, "INCH = $(foreach dir,$(DIRS),$(wildcard $(dir)/*.h))\n" );
        fprintf( F,
                 "INC  = $(shell find -L $(INCH) -name '*.h' -exec dirname {} "
                 "\\; | uniq)\n" );
        fprintf( F, "$(info )\n" );
        fprintf( F, "$(info ------------------------------------)\n" );
        fprintf( F, "$(info headers to include:)\n" );
        fprintf( F, "$(info  $(INC:%%=-I%%))\n" );
        fprintf( F, "\n$(info )\n" );
        fprintf( F, "$(info ====================================)\n" );
        fprintf( F, "$(info )\n" );

        fprintf(
            F, "\n# "
               "=============================================================="
               "===============\n" );
        fprintf( F, "CFLAGS    = $(C_DEFS) $(INC:%%=-I%%) $(OPT)\n" );
        fprintf( F, "# treat all warnings as errors\n" );
        fprintf(
            F,
            "CFLAGS  += -Werror=unused-parameter -Werror=unused-variable\n" );
        fprintf( F, "HOSTFLAGS = $(CPPSTD) $(LIBS)\n" );
        fprintf(
            F, "\n# "
               "=============================================================="
               "===============\n" );
        fprintf( F, ".PHONY: all\n" );
        fprintf( F, "all: CFLAGS+= -D MAKE_TYPE=\\\"$(MTYPE_ALL)\\\"\n" );
        fprintf( F, "all: CFLAGS+= $(HOSTFLAGS)\n" );
        fprintf( F, "all: $(OBJS)\n" );
        fprintf( F, "\t$(CC) -o $(OUTPATH)/$(EXEC) $(OBJS) $(CFLAGS)\n" );
        fprintf( F, "\t$(SZ) $(OUTPATH)/$(EXEC)\n" );
        fprintf( F, "\n$(OUTPATH)/%%.o: %%.cpp | $(OUTPATH)\n" );
        fprintf( F, "\t$(CC) -c $(CFLAGS) $< -o $@\n" );
        fprintf( F, "\n$(OUTPATH):\n" );
        fprintf( F, "\tmkdir -p $@\n" );
        fprintf( F, "\n# ------------------------------------------------\n" );
        fprintf( F, "clean:\n" );
        fprintf( F, "\trm -f $(OUTPATH)/*\n" );
        fclose( F );
    }
}

void create_clang_format( void ) {
    FILE* F;
    if ( ( F = fopen( ".clang-format", "r" ) ) == NULL ) {

        printf( "No \".clang-format\" exists, create one.\n" );
        F = fopen( ".clang-format", "w" );
        fprintf( F, "---\n" );
        fprintf( F, "# 语言: None, Cpp, Java, JavaScript, ObjC, Proto, "
                    "TableGen, TextProto\n" );
        fprintf( F, "Language:	Cpp\n" );
        fprintf( F, "# BasedOnStyle:	LLVM\n" );
        fprintf( F, "# 访问说明符（public、private等）的偏移\n" );
        fprintf( F, "AccessModifierOffset:	-4\n" );
        fprintf( F, "# 开括号（开圆括号、开尖括号、开方括号）后的对齐: Align, "
                    "DontAlign, AlwaysBreak（总是在开括号后换行）\n" );
        fprintf( F, "AlignAfterOpenBracket:	Align\n" );
        fprintf( F, "# 连续赋值时，对齐所有等号\n" );
        fprintf( F, "AlignConsecutiveAssignments:	true\n" );
        fprintf( F, "# 连续声明时，对齐所有声明的变量名\n" );
        fprintf( F, "AlignConsecutiveDeclarations:	true\n" );
        fprintf( F, "# 左对齐逃脱换行（使用反斜杠换行）的反斜杠\n" );
        fprintf( F, "AlignEscapedNewlinesLeft:	true\n" );
        fprintf( F, "# 水平对齐二元和三元表达式的操作数\n" );
        fprintf( F, "AlignOperands:	true\n" );
        fprintf( F, "# 对齐连续的尾随的注释\n" );
        fprintf( F, "AlignTrailingComments:	true\n" );
        fprintf( F, "# 允许函数声明的所有参数在放在下一行\n" );
        fprintf( F, "AllowAllParametersOfDeclarationOnNextLine:	true\n" );
        fprintf( F, "# 允许短的块放在同一行\n" );
        fprintf( F, "AllowShortBlocksOnASingleLine:	false\n" );
        fprintf( F, "# 允许短的case标签放在同一行\n" );
        fprintf( F, "AllowShortCaseLabelsOnASingleLine:	false\n" );
        fprintf( F, "# 允许短的函数放在同一行: None, InlineOnly（定义在类中）, "
                    "Empty（空函数）, Inline（定义在类中，空函数）, All\n" );
        fprintf( F, "AllowShortFunctionsOnASingleLine:	Empty\n" );
        fprintf( F, "# 允许短的if语句保持在同一行\n" );
        fprintf( F, "AllowShortIfStatementsOnASingleLine:	false\n" );

        fprintf( F, "# 允许短的循环保持在同一行\n" );
        fprintf( F, "AllowShortLoopsOnASingleLine:	false\n" );
        fprintf( F, "# 总是在定义返回类型后换行（deprecated）\n" );
        fprintf( F, "AlwaysBreakAfterDefinitionReturnType:	None\n" );
        fprintf( F, "# 总是在返回类型后换行: None, All, "
                    "TopLevel（顶级函数，不包括在类中的函数）, \n" );
        fprintf( F, "#   AllDefinitions（所有的定义，不包括声明）, "
                    "TopLevelDefinitions（所有的顶级函数的定义）\n" );
        fprintf( F, "AlwaysBreakAfterReturnType:	None\n" );
        fprintf( F, "# 总是在多行string字面量前换行\n" );
        fprintf( F, "AlwaysBreakBeforeMultilineStrings:	false\n" );
        fprintf( F, "# 总是在template声明后换行\n" );
        fprintf( F, "AlwaysBreakTemplateDeclarations:	true\n" );
        fprintf( F, "# false表示函数实参要么都在同一行，要么都各自一行\n" );
        fprintf( F, "BinPackArguments:	true\n" );
        fprintf( F, "# false表示所有形参要么都在同一行，要么都各自一行\n" );
        fprintf( F, "BinPackParameters:	true\n" );
        fprintf(
            F, "# 大括号换行，只有当BreakBeforeBraces设置为Custom时才有效\n" );
        fprintf( F, "BraceWrapping:   \n" );
        fprintf( F, "  # class定义后面\n" );
        fprintf( F, "  AfterClass:	false\n" );
        fprintf( F, "  # 控制语句后面\n" );
        fprintf( F, "  AfterControlStatement:	false\n" );
        fprintf( F, "  # enum定义后面\n" );
        fprintf( F, "  AfterEnum:	false\n" );
        fprintf( F, "  # 函数定义后面\n" );
        fprintf( F, "  AfterFunction:	false\n" );
        fprintf( F, "  # 命名空间定义后面\n" );
        fprintf( F, "  AfterNamespace:	false\n" );
        fprintf( F, "  # ObjC定义后面\n" );
        fprintf( F, "  AfterObjCDeclaration:	false\n" );
        fprintf( F, "  # struct定义后面\n" );
        fprintf( F, "  AfterStruct:	false\n" );
        fprintf( F, "  # union定义后面\n" );
        fprintf( F, "  AfterUnion:	false\n" );
        fprintf( F, "  # catch之前\n" );
        fprintf( F, "  BeforeCatch:	true\n" );
        fprintf( F, "  # else之前\n" );
        fprintf( F, "  BeforeElse:	true\n" );
        fprintf( F, "  # 缩进大括号\n" );
        fprintf( F, "  IndentBraces:	false\n" );
        fprintf( F, "# 在二元运算符前换行: None（在操作符后换行）, "
                    "NonAssignment（在非赋值的操作符前换行）, "
                    "All（在操作符前换行）\n" );
        fprintf( F, "BreakBeforeBinaryOperators:	NonAssignment\n" );
        fprintf( F,
                 "# 在大括号前换行: Attach（始终将大括号附加到周围的上下文）, "
                 "Linux（除函数、命名空间和类定义，与Attach类似）, \n" );
        fprintf( F, "#   Mozilla（除枚举、函数、记录定义，与Attach类似）, "
                    "Stroustrup（除函数定义、catch、else，与Attach类似）, \n" );
        fprintf(
            F, "#   Allman（总是在大括号前换行）, "
               "GNU（总是在大括号前换行，并对于控制语句的大括号增加额外的缩进）"
               ", WebKit（在函数前换行）, Custom\n" );
        fprintf( F, "#   注：这里认为语句块也属于函数\n" );
        fprintf( F, "BreakBeforeBraces:	Custom\n" );
        fprintf( F, "# 在三元运算符前换行\n" );
        fprintf( F, "BreakBeforeTernaryOperators:	true\n" );
        fprintf( F, "# 在构造函数的初始化列表的逗号前换行\n" );
        fprintf( F, "BreakConstructorInitializersBeforeComma:	false\n" );
        fprintf( F, "# 每行字符的限制，0表示没有限制\n" );
        fprintf( F, "ColumnLimit:	80\n" );
        fprintf( F, "# "
                    "描述具有特殊意义的注释的正则表达式，它不应该被分割为多行或"
                    "以其它方式改变\n" );
        fprintf( F, "CommentPragmas:	'^ IWYU pragma:'\n" );
        fprintf( F, "# 构造函数的初始化列表要么都在同一行，要么都各自一行\n" );
        fprintf( F,
                 "ConstructorInitializerAllOnOneLineOrOnePerLine:	false\n" );
        fprintf( F, "# 构造函数的初始化列表的缩进宽度\n" );
        fprintf( F, "ConstructorInitializerIndentWidth:	4\n" );
        fprintf( F, "# 延续的行的缩进宽度\n" );
        fprintf( F, "ContinuationIndentWidth:	4\n" );
        fprintf( F, "# 去除C++11的列表初始化的大括号{后和}前的空格\n" );
        fprintf( F, "Cpp11BracedListStyle:	false\n" );
        fprintf( F, "# 继承最常用的指针和引用的对齐方式\n" );
        fprintf( F, "DerivePointerAlignment:	false\n" );
        fprintf( F, "# 关闭格式化\n" );
        fprintf( F, "DisableFormat:	false\n" );
        fprintf( F, "# "
                    "自动检测函数的调用和定义是否被格式为每行一个参数（"
                    "Experimental）\n" );
        fprintf( F, "ExperimentalAutoDetectBinPacking:	false\n" );
        fprintf( F, "# 需要被解读为foreach循环而不是函数调用的宏\n" );
        fprintf( F, "ForEachMacros:	[ foreach, Q_FOREACH, BOOST_FOREACH ]\n" );
        fprintf( F, "# "
                    "对#include进行排序，匹配了某正则表达式的#"
                    "include拥有对应的优先级，匹配不到的则默认优先级为INT_MAX（"
                    "优先级越小排序越靠前），\n" );
        fprintf( F,
                 "#   可以定义负数优先级从而保证某些#include永远在最前面\n" );
        fprintf( F, "IncludeCategories: \n" );
        fprintf( F, "  - Regex:	'^\"(llvm|llvm-c|clang|clang-c)/'\n" );
        fprintf( F, "    Priority:	2\n" );
        fprintf( F, "  - Regex:	'^(<|\"(gtest|isl|json)/)'\n" );
        fprintf( F, "    Priority:	3\n" );
        fprintf( F, "  - Regex:	'.*'\n" );
        fprintf( F, "    Priority:	1\n" );
        fprintf( F, "# 缩进case标签\n" );
        fprintf( F, "IndentCaseLabels:	false\n" );
        fprintf( F, "# 缩进宽度\n" );
        fprintf( F, "IndentWidth:	4\n" );
        fprintf( F, "# 函数返回类型换行时，缩进函数声明或函数定义的函数名\n" );
        fprintf( F, "IndentWrappedFunctionNames:	false\n" );
        fprintf( F, "# 保留在块开始处的空行\n" );
        fprintf( F, "KeepEmptyLinesAtTheStartOfBlocks:	true\n" );
        fprintf( F, "# 开始一个块的宏的正则表达式\n" );
        fprintf( F, "MacroBlockBegin:	''\n" );
        fprintf( F, "# 结束一个块的宏的正则表达式\n" );
        fprintf( F, "MacroBlockEnd:	''\n" );
        fprintf( F, "# 连续空行的最大数量\n" );
        fprintf( F, "MaxEmptyLinesToKeep:	1\n" );
        fprintf( F, "# 命名空间的缩进: None, "
                    "Inner（缩进嵌套的命名空间中的内容）, All\n" );
        fprintf( F, "NamespaceIndentation:	Inner\n" );
        fprintf( F, "# 使用ObjC块时缩进宽度\n" );
        fprintf( F, "ObjCBlockIndentWidth:	4\n" );
        fprintf( F, "# 在ObjC的@property后添加一个空格\n" );
        fprintf( F, "ObjCSpaceAfterProperty:	false\n" );
        fprintf( F, "# 在ObjC的protocol列表前添加一个空格\n" );
        fprintf( F, "ObjCSpaceBeforeProtocolList:	true\n" );
        fprintf( F, "# 在call(后对函数调用换行的penalty\n" );
        fprintf( F, "PenaltyBreakBeforeFirstCallParameter:	19\n" );
        fprintf( F, "# 在一个注释中引入换行的penalty\n" );
        fprintf( F, "PenaltyBreakComment:	300\n" );
        fprintf( F, "# 第一次在<<前换行的penalty\n" );
        fprintf( F, "PenaltyBreakFirstLessLess:	120\n" );
        fprintf( F, "# 在一个字符串字面量中引入换行的penalty\n" );
        fprintf( F, "PenaltyBreakString:	1000\n" );
        fprintf( F, "# 对于每个在行字符数限制之外的字符的penalty\n" );
        fprintf( F, "PenaltyExcessCharacter:	1000000\n" );
        fprintf( F, "# 将函数的返回类型放到它自己的行的penalty\n" );
        fprintf( F, "PenaltyReturnTypeOnItsOwnLine:	60\n" );
        fprintf( F, "# 指针和引用的对齐: Left, Right, Middle\n" );
        fprintf( F, "PointerAlignment:	Left\n" );
        fprintf( F, "# 允许重新排版注释\n" );
        fprintf( F, "ReflowComments:	true\n" );
        fprintf( F, "# 允许排序#include\n" );
        fprintf( F, "SortIncludes:	true\n" );
        fprintf( F, "# 在C风格类型转换后添加空格\n" );
        fprintf( F, "SpaceAfterCStyleCast:	false\n" );
        fprintf( F, "# 在赋值运算符之前添加空格\n" );
        fprintf( F, "SpaceBeforeAssignmentOperators:	true\n" );
        fprintf(
            F,
            "# 开圆括号之前添加一个空格: Never, ControlStatements, Always\n" );
        fprintf( F, "SpaceBeforeParens:	ControlStatements\n" );
        fprintf( F, "# 在空的圆括号中添加空格\n" );
        fprintf( F, "SpaceInEmptyParentheses:	false\n" );
        fprintf( F, "# 在尾随的评论前添加的空格数（只适用于//）\n" );
        fprintf( F, "SpacesBeforeTrailingComments:	2\n" );
        fprintf( F, "# 在尖括号的<后和>前添加空格\n" );
        fprintf( F, "SpacesInAngles:	false\n" );
        fprintf( F,
                 "# 在容器(ObjC和JavaScript的数组和字典等)字面量中添加空格\n" );
        fprintf( F, "SpacesInContainerLiterals:	true\n" );
        fprintf( F, "# 在C风格类型转换的括号中添加空格\n" );
        fprintf( F, "SpacesInCStyleCastParentheses:	true\n" );
        fprintf( F, "# 在圆括号的(后和)前添加空格\n" );
        fprintf( F, "SpacesInParentheses:	false\n" );
        fprintf( F,
                 "# "
                 "在方括号的[后和]"
                 "前添加空格，lamda表达式和未指明大小的数组的声明不受影响\n" );
        fprintf( F, "SpacesInSquareBrackets:	false\n" );
        fprintf( F, "# 标准: Cpp03, Cpp11, Auto\n" );
        fprintf( F, "Standard:	Cpp11\n" );
        fprintf( F, "# tab宽度\n" );
        fprintf( F, "TabWidth:	4\n" );
        fprintf( F, "# 使用tab字符: Never, ForIndentation, "
                    "ForContinuationAndIndentation, Always\n" );
        fprintf( F, "UseTab:	Never\n" );
        fclose( F );
    }
}
void create_cpp_file( char* fileName ) {
    int  i;
    char time_to_print[] = "WWW, MMM. DDth, YYYY. HH:MM:SS AM";
    int  lenName;
    lenName          = strlen( fileName );
    char* headerName = ( char* )malloc( ( lenName + 1 ) * sizeof( char ) );
    for ( i = 0; i < lenName - 1; i++ )
        headerName[i] = fileName[i];
    headerName[lenName - 1] = 'h';
    headerName[lenName]     = '\0';
    FILE* F;
    current_time_date( time_to_print );
    if ( ( F = fopen( fileName, "r" ) ) == NULL ) /* does not exist */
    {
        printf( "No <%s> exists, create one.\n", fileName );
        F = fopen( fileName, "a" );
        fprintf( F, "/*********************************************************"
                    "*********************\n" );
        fprintf( F, "File Name     : %s\n", fileName );
        fprintf( F, "Author        : Dingjiang Zhou\n" );
        fprintf( F, "Email         : zhoudingjiang@gmail.com\n" );
        fprintf( F, "Create Time   : %s\n", time_to_print );
        fprintf( F, "Last Modified : \n" );
        fprintf( F, "Purpose       : \n" );
        fprintf( F, "----------------------------------------------------------"
                    "---------------------\n" );
        fprintf( F, "INPUTS\n\nOUTPUTS\n\n" );
        fprintf( F, "**********************************************************"
                    "********************/\n" );
        fprintf( F, "#include \"%s\"\n\n", headerName );
        fprintf( F, "int fncs(void)\n" );
        fprintf( F, "{\n" );
        /* fprintf(F,"    printf(\"Hello, Dingjiang!\\n\");\n"); */
        fprintf( F, "    return 0;\n" );
        fprintf( F, "}\n" );
        /* the above cannot be generated twice */
        fclose( F );
    }
    else /* files exists */
    {
        int run_shell = 0;

        int   i;
        FILE* F2;
        char  line_buf[LINE_MAX_LEN];
        char  last_modified[17];

        char tempFileName[lenName + 5];
        strcpy( tempFileName, fileName );
        tempFileName[lenName]     = 't';
        tempFileName[lenName + 1] = 'e';
        tempFileName[lenName + 2] = 'm';
        tempFileName[lenName + 3] = 'p';
        tempFileName[lenName + 4] = '\0';
        printf( "<%s> exists, modify the \"Last Modified\" item:\n", fileName );
        F2 = fopen( tempFileName, "w" ); /* read from F then write to F2 */
        /* read out "Last Modified", then modify the time behind */
        while ( fgets( line_buf, LINE_MAX_LEN, F ) != NULL ) {
            /* modify */
            /* locate "Last Modified " */
            for ( i = 0; i < 16; i++ ) {
                last_modified[i] = line_buf[i];
            }
            last_modified[16] = '\0';
            if ( strcmp( last_modified, "Last Modified :" ) == 0 ) {
                fprintf( F2, "Last Modified : %s\n", time_to_print );
            }
            else {
                fprintf( F2, "%s", line_buf );
            }
        }
        fclose( F );
        fclose( F2 );

        /* to form the mv command */
        int sysCmdLen;
        sysCmdLen = 9 + 2 * lenName;
        char sysCmdVim[sysCmdLen];

        strcpy( sysCmdVim, "mv " );

        for ( i = 3; i < 3 + lenName; i++ ) {
            sysCmdVim[i] = fileName[i - 3];
        }

        sysCmdVim[lenName + 3] = 't';
        sysCmdVim[lenName + 4] = 'e';
        sysCmdVim[lenName + 5] = 'm';
        sysCmdVim[lenName + 6] = 'p';
        sysCmdVim[lenName + 7] = ' ';

        for ( i = lenName + 8; i < 2 * lenName + 8; i++ )
            sysCmdVim[i] = fileName[i - lenName - 8];
        sysCmdVim[sysCmdLen] = '\0';

        /* run the cmd: mv hello.ctemp hello.c */
        run_shell = system( sysCmdVim );
    }
}

/* --------------------------------- */
void create_header_file( char* fileName ) {
    int  i;
    char time_to_print[] = "WWW, MMM. DDth, YYYY. HH:MM:SS AM";
    int  lenName;
    lenName = strlen( fileName );
    /* convert the low case name to captical name */
    char* headerNameCap = ( char* )malloc( ( lenName + 1 ) * sizeof( char ) );
    for ( i = 0; i < lenName; i++ ) {
        if ( fileName[i] >= 'a' && fileName[i] <= 'z' )
            headerNameCap[i] = fileName[i] - 32;
        else if ( fileName[i] >= 'A' && fileName[i] <= 'Z' )
            headerNameCap[i] = fileName[i];
        else if ( fileName[i] == '.' )
            headerNameCap[i] = '_';
    }
    headerNameCap[lenName + 1] = '\0'; /* the end of a string */
    /* creat the file */
    FILE* F;
    current_time_date( time_to_print );
    if ( ( F = fopen( fileName, "r" ) ) == NULL ) /* does not exist */
    {
        printf( "No <%s> exists, create one.\n", fileName );
        F = fopen( fileName, "a" );
        fprintf( F, "/*********************************************************"
                    "*********************\n" );
        fprintf( F, "File Name     : %s\n", fileName );
        fprintf( F, "Author        : Dingjiang Zhou\n" );
        fprintf( F, "Email         : zhoudingjiang@gmail.com\n" );
        fprintf( F, "Create Time   : %s\n", time_to_print );
        fprintf( F, "Last Modified : \n" );
        fprintf( F, "Purpose       : \n" );
        fprintf( F, "----------------------------------------------------------"
                    "---------------------\n" );
        fprintf( F, "INPUTS\n\nOUTPUTS\n\n" );
        fprintf( F, "**********************************************************"
                    "********************/\n" );
        fprintf( F, "#ifndef __%s__\n", headerNameCap );
        fprintf( F, "#define __%s__\n\n", headerNameCap );
        fprintf( F, "#include <stdio.h>\n" );
        fprintf( F, "#include <stdlib.h>\n" );
        fprintf( F, "#include <unistd.h>\n" );
        fprintf( F, "#include <stdint.h>\n\n" );
        fprintf( F, "/* typedef struct{\n\n}; */\n\n\n" );
        fprintf( F, "/* variables declaration */\n\n\n" );
        fprintf( F, "/* functions declaration */\n\n\n" );
        fprintf( F, "#endif\n" );
        /* the above cannot be generated twice */
        fclose( F );
    }
    else /* files exists */
    {
        int run_shell = 0;

        int   i;
        FILE* F2;
        char  line_buf[LINE_MAX_LEN];
        char  last_modified[14];

        char tempFileName[lenName + 5];
        strcpy( tempFileName, fileName );
        tempFileName[lenName]     = 't';
        tempFileName[lenName + 1] = 'e';
        tempFileName[lenName + 2] = 'm';
        tempFileName[lenName + 3] = 'p';
        tempFileName[lenName + 4] = '\0';
        printf( "<%s> exists, modify the \"Last Modified\" item:\n", fileName );
        F2 = fopen( tempFileName, "w" ); /* read from F then write to F2 */
        /* read out "Last Modified", then modify the time behind */
        while ( fgets( line_buf, LINE_MAX_LEN, F ) != NULL ) {
            /* modify */
            /* locate "Last Modified " */
            for ( i = 0; i < 13; i++ )
                last_modified[i] = line_buf[i + 3];
            last_modified[13] = '\0';
            if ( strcmp( last_modified, "Last Modified" ) == 0 ) {
                fprintf( F2, "   Last Modified  : %s\n", time_to_print );
            }
            else
                fprintf( F2, "%s", line_buf );
        }
        fclose( F );
        fclose( F2 );

        /* to form the mv command */
        int sysCmdLen;
        sysCmdLen = 9 + 2 * lenName;
        char sysCmdVim[sysCmdLen];

        strcpy( sysCmdVim, "mv " );

        for ( i = 3; i < 3 + lenName; i++ ) {
            sysCmdVim[i] = fileName[i - 3];
        }

        sysCmdVim[lenName + 3] = 't';
        sysCmdVim[lenName + 4] = 'e';
        sysCmdVim[lenName + 5] = 'm';
        sysCmdVim[lenName + 6] = 'p';
        sysCmdVim[lenName + 7] = ' ';

        for ( i = lenName + 8; i < 2 * lenName + 8; i++ )
            sysCmdVim[i] = fileName[i - lenName - 8];
        sysCmdVim[sysCmdLen] = '\0';

        /* run the cmd: mv hello.ctemp hello.c */
        run_shell = system( sysCmdVim );
    }
}