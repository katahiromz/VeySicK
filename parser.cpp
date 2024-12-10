/* A Bison parser, made by GNU Bison 3.5.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 5 "parser.yy"

    #include "ast.h" // AST (抽象構造木)
    typedef VskAstPtr YYSTYPE;
    #define YYSTYPE_IS_DECLARED
    int yylex(yyscan_t yyscanner);

#line 77 "C:/dev/VeySickProject/VeySicK/parser.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_C_DEV_VEYSICKPROJECT_VEYSICK_PARSER_H_INCLUDED
# define YY_YY_C_DEV_VEYSICKPROJECT_VEYSICK_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TK_ABS = 258,
    TK_AKCNV_dollar = 259,
    TK_ALLOC = 260,
    TK_AMPERSAND = 261,
    TK_AND = 262,
    TK_ASC = 263,
    TK_ASTERISK = 264,
    TK_ATN = 265,
    TK_ATTR_dollar = 266,
    TK_AUTO = 267,
    TK_BACKSLASH = 268,
    TK_BANG = 269,
    TK_BEEP = 270,
    TK_BLOAD = 271,
    TK_BSAVE = 272,
    TK_CALL = 273,
    TK_CDBL = 274,
    TK_CHAIN = 275,
    TK_CHDIR = 276,
    TK_CHILD = 277,
    TK_CHR_dollar = 278,
    TK_CINT = 279,
    TK_CIRCLE = 280,
    TK_CLEAR = 281,
    TK_CLOSE = 282,
    TK_CLOSE_SHARP = 283,
    TK_CLS = 284,
    TK_CMD = 285,
    TK_COLON = 286,
    TK_COLOR = 287,
    TK_COLOR_at = 288,
    TK_COM = 289,
    TK_COMMA = 290,
    TK_COMMENT = 291,
    TK_COMMON = 292,
    TK_CONSOLE = 293,
    TK_CONT = 294,
    TK_COPY = 295,
    TK_COS = 296,
    TK_CSNG = 297,
    TK_CSRLIN = 298,
    TK_CVD = 299,
    TK_CVI = 300,
    TK_CVS = 301,
    TK_DATA = 302,
    TK_DATE_dollar = 303,
    TK_DEF = 304,
    TK_DEFDBL = 305,
    TK_DEFINT = 306,
    TK_DEFSNG = 307,
    TK_DEFSTR = 308,
    TK_DELETE = 309,
    TK_DELIM = 310,
    TK_DIGITS = 311,
    TK_DIM = 312,
    TK_DIRTY_8BIT = 313,
    TK_DOLLAR = 314,
    TK_DRAW = 315,
    TK_DSKF = 316,
    TK_DSKI_dollar = 317,
    TK_DSKO_dollar = 318,
    TK_EDIT = 319,
    TK_ELSE = 320,
    TK_END = 321,
    TK_EOF = 322,
    TK_EQUAL = 323,
    TK_EQV = 324,
    TK_ERASE = 325,
    TK_ERL = 326,
    TK_ERR = 327,
    TK_ERROR = 328,
    TK_EVAL = 329,
    TK_EXP = 330,
    TK_FIELD = 331,
    TK_FIELD_sharp = 332,
    TK_FILES = 333,
    TK_FIX = 334,
    TK_FLOATING = 335,
    TK_FN = 336,
    TK_FOR = 337,
    TK_FPOS = 338,
    TK_FRE = 339,
    TK_GE = 340,
    TK_GET = 341,
    TK_GET_at = 342,
    TK_GET_sharp = 343,
    TK_GO = 344,
    TK_GOSUB = 345,
    TK_GOTO = 346,
    TK_GT = 347,
    TK_HAT = 348,
    TK_HELP = 349,
    TK_HEXADECIMAL = 350,
    TK_HEX_dollar = 351,
    TK_IDENTIFIER = 352,
    TK_IEEE = 353,
    TK_IF = 354,
    TK_IFC = 355,
    TK_IMP = 356,
    TK_INKEY_dollar = 357,
    TK_INP = 358,
    TK_INPUT = 359,
    TK_INPUT_dollar = 360,
    TK_INPUT_sharp = 361,
    TK_INSTR = 362,
    TK_INT = 363,
    TK_INVALID_CHARS = 364,
    TK_IRESET = 365,
    TK_ISET = 366,
    TK_JIS_dollar = 367,
    TK_KACNV_dollar = 368,
    TK_KANJI = 369,
    TK_KEXT_dollar = 370,
    TK_KEY = 371,
    TK_KILL = 372,
    TK_KINPUT = 373,
    TK_KINSTR = 374,
    TK_KLEN = 375,
    TK_KMID_dollar = 376,
    TK_KNJ_dollar = 377,
    TK_KPLOAD = 378,
    TK_KPOS = 379,
    TK_KTYPE = 380,
    TK_LE = 381,
    TK_LEFT_dollar = 382,
    TK_LEN = 383,
    TK_LET = 384,
    TK_LFILES = 385,
    TK_LINE = 386,
    TK_LIST = 387,
    TK_LLIST = 388,
    TK_LOAD = 389,
    TK_LOC = 390,
    TK_LOCATE = 391,
    TK_LOF = 392,
    TK_LOG = 393,
    TK_LPOS = 394,
    TK_LPRINT = 395,
    TK_LSET = 396,
    TK_LT = 397,
    TK_L_BRACE = 398,
    TK_L_BRACKET = 399,
    TK_L_PAREN = 400,
    TK_MAIL = 401,
    TK_MAP = 402,
    TK_MERGE = 403,
    TK_MID_dollar = 404,
    TK_MINUS = 405,
    TK_MKDIR = 406,
    TK_MKD_dollar = 407,
    TK_MKI_dollar = 408,
    TK_MKS_dollar = 409,
    TK_MOD = 410,
    TK_MON = 411,
    TK_MOTOR = 412,
    TK_MOUSE = 413,
    TK_NAME = 414,
    TK_NE = 415,
    TK_NEW = 416,
    TK_NEWLINE = 417,
    TK_NEXT = 418,
    TK_NOT = 419,
    TK_OCTAL = 420,
    TK_OCT_dollar = 421,
    TK_OFF = 422,
    TK_ON = 423,
    TK_OPEN = 424,
    TK_OPTION = 425,
    TK_OR = 426,
    TK_OUT = 427,
    TK_PAINT = 428,
    TK_PEEK = 429,
    TK_PEN = 430,
    TK_PERCENT = 431,
    TK_PERIOD = 432,
    TK_PLAY = 433,
    TK_PLUS = 434,
    TK_POINT = 435,
    TK_POKE = 436,
    TK_POLL = 437,
    TK_POS = 438,
    TK_PRESET = 439,
    TK_PRINT = 440,
    TK_PRINT_SHARP = 441,
    TK_PSET = 442,
    TK_PUT = 443,
    TK_PUT_at = 444,
    TK_PUT_sharp = 445,
    TK_QUESTION = 446,
    TK_RANDOMIZE = 447,
    TK_RBYTE = 448,
    TK_READ = 449,
    TK_REM = 450,
    TK_RENUM = 451,
    TK_RESTORE = 452,
    TK_RESUME = 453,
    TK_RETURN = 454,
    TK_RIGHT_dollar = 455,
    TK_RMDIR = 456,
    TK_RND = 457,
    TK_ROLL = 458,
    TK_RSET = 459,
    TK_RUN = 460,
    TK_R_BRACE = 461,
    TK_R_BRACKET = 462,
    TK_R_PAREN = 463,
    TK_SAVE = 464,
    TK_SCREEN = 465,
    TK_SEARCH = 466,
    TK_SEG = 467,
    TK_SEMICOLON = 468,
    TK_SET = 469,
    TK_SET_SHARP = 470,
    TK_SGN = 471,
    TK_SHARP = 472,
    TK_SIN = 473,
    TK_SLASH = 474,
    TK_SPACE_dollar = 475,
    TK_SPC = 476,
    TK_SQR = 477,
    TK_SRQ = 478,
    TK_STATUS = 479,
    TK_STEP = 480,
    TK_STOP = 481,
    TK_STRING = 482,
    TK_STRING_dollar = 483,
    TK_STR_dollar = 484,
    TK_SUB = 485,
    TK_SWAP = 486,
    TK_SYSTEM = 487,
    TK_TAB = 488,
    TK_TAN = 489,
    TK_TERM = 490,
    TK_THEN = 491,
    TK_TILDA = 492,
    TK_TIMEOUT = 493,
    TK_TIME_dollar = 494,
    TK_TO = 495,
    TK_TROFF = 496,
    TK_TRON = 497,
    TK_UNDERLINE = 498,
    TK_USING = 499,
    TK_USR = 500,
    TK_VAL = 501,
    TK_VARPTR = 502,
    TK_VBAR = 503,
    TK_VIEW = 504,
    TK_WAIT = 505,
    TK_WBYTE = 506,
    TK_WEND = 507,
    TK_WHILE = 508,
    TK_WIDTH = 509,
    TK_WIDTH_sharp = 510,
    TK_WINDOW = 511,
    TK_WRITE = 512,
    TK_WRITE_SHARP = 513,
    TK_XOR = 514
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (VskParseResult& result, yyscan_t yyscanner);

#endif /* !YY_YY_C_DEV_VEYSICKPROJECT_VEYSICK_PARSER_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  413
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   7588

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  260
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  58
/* YYNRULES -- Number of rules.  */
#define YYNRULES  499
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  978

#define YYUNDEFTOK  2
#define YYMAXUTOK   514


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int16 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   283,   283,   287,   288,   289,   290,   294,   295,   296,
     300,   301,   305,   306,   310,   311,   315,   316,   317,   318,
     322,   323,   324,   325,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   349,   353,   357,   358,   359,   360,   361,   362,   363,
     364,   365,   366,   370,   371,   375,   376,   381,   391,   392,
     393,   394,   395,   396,   397,   398,   399,   400,   401,   402,
     403,   404,   405,   406,   407,   408,   409,   410,   411,   412,
     413,   414,   415,   416,   417,   418,   419,   420,   421,   422,
     423,   424,   425,   426,   427,   428,   429,   430,   431,   432,
     433,   434,   435,   436,   437,   438,   439,   440,   441,   442,
     443,   444,   445,   446,   447,   448,   449,   450,   454,   455,
     458,   459,   460,   464,   465,   466,   470,   471,   475,   476,
     480,   481,   482,   486,   487,   488,   489,   490,   491,   492,
     496,   497,   501,   502,   506,   507,   511,   512,   516,   517,
     521,   522,   526,   530,   531,   532,   533,   534,   538,   539,
     543,   544,   548,   552,   553,   557,   558,   560,   561,   563,
     567,   571,   576,   580,   584,   588,   593,   597,   601,   605,
     610,   615,   619,   624,   628,   633,   638,   642,   646,   650,
     654,   658,   662,   666,   670,   674,   678,   682,   685,   689,
     693,   694,   695,   696,   697,   698,   699,   700,   701,   702,
     703,   704,   705,   709,   713,   717,   718,   719,   723,   724,
     725,   726,   727,   728,   729,   730,   731,   732,   733,   737,
     741,   745,   749,   750,   751,   752,   753,   754,   755,   756,
     758,   759,   760,   761,   763,   764,   765,   766,   768,   773,
     777,   782,   787,   792,   797,   801,   805,   810,   814,   818,
     822,   826,   830,   834,   838,   842,   846,   850,   854,   858,
     859,   860,   861,   862,   863,   864,   865,   866,   867,   868,
     869,   870,   871,   872,   873,   874,   875,   876,   877,   878,
     879,   880,   881,   882,   886,   890,   894,   895,   896,   897,
     898,   899,   900,   905,   909,   910,   911,   912,   913,   914,
     915,   916,   917,   918,   919,   920,   921,   922,   923,   924,
     925,   926,   927,   928,   929,   930,   931,   932,   933,   934,
     935,   936,   940,   941,   945,   946,   950,   951,   955,   956,
     960,   961,   962,   963,   967,   968,   972,   973,   977,   978,
     979,   980,   981,   985,   986,   990,   991,   992,   993,   994,
     995,   996,   997,   998,   999,  1000,  1001,  1002,  1003,  1004,
    1005,  1006,  1007,  1008,  1009,  1010,  1011,  1012,  1013,  1014,
    1015,  1016,  1017,  1018,  1019,  1020,  1021,  1022,  1023,  1024,
    1025,  1026,  1027,  1028,  1029,  1030,  1031,  1032,  1033,  1034,
    1035,  1036,  1037,  1038,  1039,  1040,  1041,  1042,  1043,  1044,
    1045,  1046,  1047,  1048,  1049,  1050,  1051,  1052,  1053,  1054,
    1055,  1059,  1066,  1067,  1068,  1073,  1078,  1083,  1088,  1093,
    1098,  1102,  1106,  1110,  1114,  1118,  1122,  1126,  1130,  1134,
    1140,  1144,  1151,  1159,  1167,  1173,  1179,  1185,  1189,  1195,
    1199,  1203,  1210,  1216,  1222,  1226,  1230,  1236,  1240,  1244,
    1253,  1257,  1260,  1263,  1266,  1272,  1275,  1278,  1281,  1287,
    1288,  1289,  1293,  1294,  1298,  1302,  1307,  1316,  1317,  1321,
    1322,  1323,  1324,  1328,  1329,  1333,  1334,  1335,  1339,  1340,
    1341,  1342,  1346,  1352,  1358,  1362,  1368,  1369,  1370,  1371
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TK_ABS", "TK_AKCNV_dollar", "TK_ALLOC",
  "TK_AMPERSAND", "TK_AND", "TK_ASC", "TK_ASTERISK", "TK_ATN",
  "TK_ATTR_dollar", "TK_AUTO", "TK_BACKSLASH", "TK_BANG", "TK_BEEP",
  "TK_BLOAD", "TK_BSAVE", "TK_CALL", "TK_CDBL", "TK_CHAIN", "TK_CHDIR",
  "TK_CHILD", "TK_CHR_dollar", "TK_CINT", "TK_CIRCLE", "TK_CLEAR",
  "TK_CLOSE", "TK_CLOSE_SHARP", "TK_CLS", "TK_CMD", "TK_COLON", "TK_COLOR",
  "TK_COLOR_at", "TK_COM", "TK_COMMA", "TK_COMMENT", "TK_COMMON",
  "TK_CONSOLE", "TK_CONT", "TK_COPY", "TK_COS", "TK_CSNG", "TK_CSRLIN",
  "TK_CVD", "TK_CVI", "TK_CVS", "TK_DATA", "TK_DATE_dollar", "TK_DEF",
  "TK_DEFDBL", "TK_DEFINT", "TK_DEFSNG", "TK_DEFSTR", "TK_DELETE",
  "TK_DELIM", "TK_DIGITS", "TK_DIM", "TK_DIRTY_8BIT", "TK_DOLLAR",
  "TK_DRAW", "TK_DSKF", "TK_DSKI_dollar", "TK_DSKO_dollar", "TK_EDIT",
  "TK_ELSE", "TK_END", "TK_EOF", "TK_EQUAL", "TK_EQV", "TK_ERASE",
  "TK_ERL", "TK_ERR", "TK_ERROR", "TK_EVAL", "TK_EXP", "TK_FIELD",
  "TK_FIELD_sharp", "TK_FILES", "TK_FIX", "TK_FLOATING", "TK_FN", "TK_FOR",
  "TK_FPOS", "TK_FRE", "TK_GE", "TK_GET", "TK_GET_at", "TK_GET_sharp",
  "TK_GO", "TK_GOSUB", "TK_GOTO", "TK_GT", "TK_HAT", "TK_HELP",
  "TK_HEXADECIMAL", "TK_HEX_dollar", "TK_IDENTIFIER", "TK_IEEE", "TK_IF",
  "TK_IFC", "TK_IMP", "TK_INKEY_dollar", "TK_INP", "TK_INPUT",
  "TK_INPUT_dollar", "TK_INPUT_sharp", "TK_INSTR", "TK_INT",
  "TK_INVALID_CHARS", "TK_IRESET", "TK_ISET", "TK_JIS_dollar",
  "TK_KACNV_dollar", "TK_KANJI", "TK_KEXT_dollar", "TK_KEY", "TK_KILL",
  "TK_KINPUT", "TK_KINSTR", "TK_KLEN", "TK_KMID_dollar", "TK_KNJ_dollar",
  "TK_KPLOAD", "TK_KPOS", "TK_KTYPE", "TK_LE", "TK_LEFT_dollar", "TK_LEN",
  "TK_LET", "TK_LFILES", "TK_LINE", "TK_LIST", "TK_LLIST", "TK_LOAD",
  "TK_LOC", "TK_LOCATE", "TK_LOF", "TK_LOG", "TK_LPOS", "TK_LPRINT",
  "TK_LSET", "TK_LT", "TK_L_BRACE", "TK_L_BRACKET", "TK_L_PAREN",
  "TK_MAIL", "TK_MAP", "TK_MERGE", "TK_MID_dollar", "TK_MINUS", "TK_MKDIR",
  "TK_MKD_dollar", "TK_MKI_dollar", "TK_MKS_dollar", "TK_MOD", "TK_MON",
  "TK_MOTOR", "TK_MOUSE", "TK_NAME", "TK_NE", "TK_NEW", "TK_NEWLINE",
  "TK_NEXT", "TK_NOT", "TK_OCTAL", "TK_OCT_dollar", "TK_OFF", "TK_ON",
  "TK_OPEN", "TK_OPTION", "TK_OR", "TK_OUT", "TK_PAINT", "TK_PEEK",
  "TK_PEN", "TK_PERCENT", "TK_PERIOD", "TK_PLAY", "TK_PLUS", "TK_POINT",
  "TK_POKE", "TK_POLL", "TK_POS", "TK_PRESET", "TK_PRINT",
  "TK_PRINT_SHARP", "TK_PSET", "TK_PUT", "TK_PUT_at", "TK_PUT_sharp",
  "TK_QUESTION", "TK_RANDOMIZE", "TK_RBYTE", "TK_READ", "TK_REM",
  "TK_RENUM", "TK_RESTORE", "TK_RESUME", "TK_RETURN", "TK_RIGHT_dollar",
  "TK_RMDIR", "TK_RND", "TK_ROLL", "TK_RSET", "TK_RUN", "TK_R_BRACE",
  "TK_R_BRACKET", "TK_R_PAREN", "TK_SAVE", "TK_SCREEN", "TK_SEARCH",
  "TK_SEG", "TK_SEMICOLON", "TK_SET", "TK_SET_SHARP", "TK_SGN", "TK_SHARP",
  "TK_SIN", "TK_SLASH", "TK_SPACE_dollar", "TK_SPC", "TK_SQR", "TK_SRQ",
  "TK_STATUS", "TK_STEP", "TK_STOP", "TK_STRING", "TK_STRING_dollar",
  "TK_STR_dollar", "TK_SUB", "TK_SWAP", "TK_SYSTEM", "TK_TAB", "TK_TAN",
  "TK_TERM", "TK_THEN", "TK_TILDA", "TK_TIMEOUT", "TK_TIME_dollar",
  "TK_TO", "TK_TROFF", "TK_TRON", "TK_UNDERLINE", "TK_USING", "TK_USR",
  "TK_VAL", "TK_VARPTR", "TK_VBAR", "TK_VIEW", "TK_WAIT", "TK_WBYTE",
  "TK_WEND", "TK_WHILE", "TK_WIDTH", "TK_WIDTH_sharp", "TK_WINDOW",
  "TK_WRITE", "TK_WRITE_SHARP", "TK_XOR", "$accept", "file_number",
  "file_numbers_or_expressions", "lvalue", "lvalue_list", "line_number",
  "casted_number", "number", "cast", "primary_expression",
  "parameter_list", "trailing_parameter_list", "function_name",
  "exponential_expression", "unary_expression",
  "multiplicative_expression", "backslash_expression", "mod_expression",
  "additive_expression", "relational_expression", "not_expression",
  "and_expression", "or_expression", "xor_expression", "imp_expression",
  "eqv_expression", "expression", "put_operation", "put_at", "get_at",
  "field_item", "field_items", "primary_statement", "dimension_list",
  "identifier_list", "print", "printing_list", "printing_list_2", "go_to",
  "go_sub", "printing_expression", "semicolon_or_comma",
  "lead_statement_0", "lead_statement_1", "matched_if_statement",
  "unmatched_if_statement", "matched_statement", "unmatched_statement",
  "statement", "line_number_or_dot", "line_numbers", "commas",
  "line_range", "dirty_8bit_sequence", "cmd_name", "cmd_parameter_list",
  "line", "translation_unit", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   436,   437,   438,   439,   440,   441,   442,   443,   444,
     445,   446,   447,   448,   449,   450,   451,   452,   453,   454,
     455,   456,   457,   458,   459,   460,   461,   462,   463,   464,
     465,   466,   467,   468,   469,   470,   471,   472,   473,   474,
     475,   476,   477,   478,   479,   480,   481,   482,   483,   484,
     485,   486,   487,   488,   489,   490,   491,   492,   493,   494,
     495,   496,   497,   498,   499,   500,   501,   502,   503,   504,
     505,   506,   507,   508,   509,   510,   511,   512,   513,   514
};
# endif

#define YYPACT_NINF (-633)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-200)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    6330,   -20,    92,  -633,  -633,  -633,  -633,  4168,  -633,  -633,
     -84,  -633,  4408,  5608,  -633,     7,  7080,    56,    -6,    38,
    -633,  -633,  -633,  -633,  -633,  -633,    74,   -50,  -633,  -633,
    -633,  -633,    42,  7330,    48,  -633,  -633,  -633,    50,  -633,
      60,  -633,  5608,  4408,  5608,  -633,    48,  -135,  -633,   107,
    -123,  -633,  -633,    62,   115,  5608,   -68,   127,   -59,  -633,
      48,  -633,    48,  -633,   -15,    42,    42,  4648,  -633,  1978,
      48,  -633,    99,  -633,  -633,  -633,   -65,  5608,    -2,    48,
    1244,  5608,   171,  -633,   -70,    68,  1491,   -67,  -633,   -61,
    -633,   190,   -60,  -135,  -633,   207,  -633,  -633,  -633,  -633,
      78,    41,    78,  -633,  -633,    48,    -3,  -633,  -633,  -633,
    -633,    70,    48,  -633,  -633,   -36,  -633,  -633,   125,  -633,
    -633,  -633,   -30,   218,   131,  2225,   227,   216,   140,   144,
    -633,  1731,    78,    78,  4888,   255,  -633,  -633,   262,   264,
     261,   241,   138,   302,  -633,   206,  5608,  -633,   269,  -633,
    -633,  -633,  -633,  -633,  -633,  -633,  -633,  -633,  -633,  -633,
    -633,  -633,  -633,  -633,  -633,  -633,  -633,   161,  -633,  -633,
    -633,  -633,  -633,  -633,   162,  -633,  -633,  -633,  -633,  -633,
     163,  -633,  -633,  -633,  -633,  -633,  -633,  -633,  -633,  -633,
    -633,  -633,  -633,  -633,   167,   169,  -633,  -633,  5608,  -633,
    5608,  -633,  6088,  -633,  -633,  -633,  -633,  5848,  -633,  -633,
    -633,  -633,  6088,  -633,  -633,  -633,   170,   172,  -633,  -633,
    -633,  -633,  -633,  -633,  -633,  -633,  -633,  -633,  -633,   174,
    -633,  -633,  -633,  -633,     1,  -633,   175,   223,  -633,     4,
     308,   168,   -35,   149,  -633,   315,   153,    69,   228,   263,
     295,  5608,   188,  6088,  -633,   300,  -633,   301,  -633,  -633,
    -633,  2465,  7080,   262,   264,   192,  5608,  -633,  -633,  -633,
    5608,    46,   271,   275,    50,  -633,  -633,   194,  -633,   309,
    -633,   311,  -633,  -633,   312,  -633,   313,   314,   316,   282,
     317,   319,  -633,  -633,  -633,  -633,  -633,  5608,  5608,   -22,
     -17,  5608,  -633,  -633,   320,  -633,  -633,  5608,  -633,  -633,
    -633,  -633,   288,  3679,   303,  5608,   -57,   212,  -633,  -633,
    -633,   323,  -633,  -633,   215,   217,  5608,  -633,  3439,  -633,
     293,   266,  5608,  -633,  -633,  -633,   267,  -633,  -633,   320,
     177,   122,   177,   177,   142,   177,   177,   177,   299,   166,
      40,  -633,  5608,   221,  -633,  -633,  -633,  -633,  -633,  -633,
    -633,  -633,   333,   336,  -633,  5128,  5608,   229,  5608,   231,
     337,  5608,   232,   338,   345,  -633,  -633,  -633,  -633,   318,
     350,  -633,  -633,  -633,  -633,   352,  5608,  -633,  -633,  -633,
    5608,  -633,   354,   355,  5608,   356,  3439,   357,  5608,  5608,
    5608,  5608,   359,  3439,  -633,  -633,   336,  4888,  7080,  -633,
    -633,  -633,  -633,  -633,  -633,  -633,  5608,  4408,  4408,  5608,
    4408,  4408,   187,   361,   223,   149,   223,  5608,   304,    48,
    -633,  -633,  -633,  -633,  -633,  5368,  6088,  5848,  5848,  5848,
    5848,  5848,  5848,  5848,  5848,  5848,  5848,  5848,  5848,  5608,
    5608,  5608,  5608,  5608,    57,   362,  5608,  -633,  4408,  4408,
    5608,  2705,  -633,  -633,   363,   336,  -633,  5608,   364,  -633,
    5608,   -39,  5608,  5608,  -633,    50,  -633,    48,   305,  5608,
    5608,  5608,  5608,  5608,  5608,    -8,  -633,   -10,   160,  6580,
      78,    48,    48,   -13,    48,   195,  5608,  5608,   370,    63,
     -12,   371,   372,  5608,   265,  5608,   321,  5608,  5608,   196,
    -633,  5608,    30,   377,   208,  5608,   185,    78,    78,    78,
     198,  5608,    78,    78,    78,    78,   193,   198,   198,    49,
    4408,   382,  5608,  4888,  5128,  -633,  -633,   384,  5608,   386,
    5608,  2945,   387,  5608,  5608,  5608,  5608,   326,    48,  -633,
     389,  5608,  5608,   390,  3439,  3439,  -633,   391,   392,   220,
    3192,   336,   262,   264,  -633,   222,   226,   230,   233,    -5,
     239,   244,   245,   246,  -633,    78,   248,   393,     8,  -633,
      12,  -633,  -633,  -633,     4,   308,   168,   168,   -35,   -35,
     -35,   -35,   -35,   -35,  -633,   315,   153,    69,   228,  -633,
     396,  5608,   400,  -633,  -633,   300,   402,  5608,  -633,  4888,
     404,  5608,  -633,   394,    13,  -633,  -633,  -633,  -633,  -633,
     343,  -633,   422,   422,   422,   219,  -633,  -633,  5608,  -633,
    -633,   366,  6830,   395,    95,  -633,   399,   320,   320,   -43,
      48,  -633,    72,  -633,   423,    48,  -633,  -633,    48,    48,
    5608,   430,  5608,   432,  -633,   260,   268,  5608,  -633,  5608,
    5608,    75,  -633,  -633,  -633,  -633,  -633,   336,   236,   270,
    -633,  -633,  -633,  -633,   177,   336,   336,   373,   375,  -633,
    -633,  5608,   434,   336,  -633,  5608,   439,  5608,   440,  5608,
    3439,  5608,   444,  -633,  -633,  -633,  -633,  -633,  5608,  -633,
    -633,  5608,  3439,  3439,  5608,  5608,  5608,  5608,  3439,  -633,
    -633,  -633,  -633,  -135,  -633,  -633,  -633,  -633,  -633,   445,
    -633,  5608,  5608,  -633,  -633,   385,   273,  5608,    48,   187,
     336,  5608,   276,  5608,   419,    48,  5608,  5608,  -633,  -633,
    -633,   262,   264,  6830,  6830,  6830,   -11,   320,   320,  -633,
    -633,  -633,  5608,  -633,  -633,  -633,   280,  5608,   455,  5608,
    -633,  -633,  -633,  3928,   285,   460,  -633,  -633,  -633,   236,
    -633,   177,    78,  4408,  4408,   289,  5608,   291,  5608,   292,
    5608,   290,   294,  5608,   296,   297,   306,   307,  3928,   310,
     322,    39,    14,   324,  -633,   466,   325,  -633,   327,   360,
    -633,  5608,  -633,  -633,   281,  -633,   262,   264,  -633,   262,
     264,  -633,   262,   264,    48,    48,    64,   -12,   367,   332,
    5608,   342,  -633,  -633,  -633,   443,  5608,  -633,    78,  -633,
    -633,  -633,  -633,  -633,  -633,   344,  -633,   346,  -633,   348,
    5608,  -633,   349,   368,   369,   472,   374,  5608,  -633,    42,
     477,  5608,  -633,  -633,  5608,   478,  -633,   376,  -633,  5608,
     320,   320,    48,   -55,  -633,   358,   378,  5608,   365,  -633,
    -633,  -633,  -633,  3928,  -633,   380,   381,    26,   -53,  3928,
    -633,   462,    20,  -633,  5608,  5608,  -633,  -633,  5608,   406,
    -633,   -49,  -633,   452,  5608,  5608,   408,   487,  5608,   413,
      42,  5608,  -633,  -633,   494,   496,  5608,  5608,   415,  5608,
     499,   510,  5608,     2,   528,  5608,  -633,   379,  5608,  5608,
     530,   532,  5608,  -633,  5608,  5608,   383,  -633,  -633,  -633,
    -633,  -633,   534,  5608,   535,  -633,   398,   401,  5608,  5608,
     536,   407,   409,   537,  5608,   410,  5608,  -633,  -633,   411,
     412,  5608,  -633,  -633,    10,   539,   540,   414,  -633,  -633,
     417,  5608,   541,  5608,    48,   542,  -633,   543,  5608,  -633,
    -633,    48,  5608,   544,  -633,  -633,  5608,  -633
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int16 yydefact[] =
{
     499,     0,   328,   355,   356,   357,   358,     0,   416,   359,
       0,   360,   305,     0,   361,     0,   471,   362,     0,     0,
     165,   363,   364,   365,   366,   367,     0,     0,   368,   369,
     370,   371,     0,     0,     0,   483,   372,   373,     0,   374,
       0,   375,     0,     0,     0,   376,     0,   161,   160,     0,
       0,   346,   344,     0,     9,     0,     0,     0,   377,   385,
       0,   386,     0,   387,     0,   299,   301,     0,   389,   182,
       0,   390,     0,   417,   391,   392,   393,     0,   394,   186,
       0,     0,     0,   398,     0,     0,   400,     0,   401,     0,
     336,     0,     0,   159,   158,     0,   337,   402,   403,   404,
     313,   239,   321,   418,   405,     0,   309,   406,   407,   408,
     409,   316,     0,   410,   411,     0,   296,   297,     0,   412,
     413,   414,   415,     0,     0,   179,     0,     0,     0,     0,
     463,   175,     0,     0,   224,   222,   462,   467,   469,   470,
     495,   331,   497,     0,   166,     0,     0,    12,   327,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    28,    16,    72,    73,     0,    34,    35,
      74,    75,    19,    76,     0,    77,    18,    78,    30,    79,
       0,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,     0,     0,    93,    94,     0,    95,
       0,    96,     0,    97,    98,    99,   100,     0,    17,   101,
     102,   103,     0,   104,   105,   106,    37,     0,   107,   108,
     109,   110,    26,   111,   112,   113,    29,   114,   115,     0,
     116,   117,    24,    25,    15,   118,    31,   120,   123,   126,
     128,   130,   133,   140,   142,   144,   146,   148,   150,   152,
     265,     0,     0,     0,     3,   304,     4,   303,   485,   487,
     486,   220,     0,   461,   466,     0,     0,   269,   270,   271,
       0,     0,     0,     0,     0,   473,   472,   482,   236,   493,
     332,   200,   295,   334,   314,   498,     0,     0,     0,     0,
     241,   243,   347,   345,   284,   285,   286,     0,     0,     0,
       0,     0,   423,    10,   227,   422,   378,     0,   382,   383,
     384,   197,     0,     0,     0,     0,     0,     0,   298,   300,
     388,   311,   351,   352,     0,     0,     0,   348,   181,   338,
       0,     0,     0,   275,   276,   277,     0,   395,   396,   185,
       0,     0,     0,     0,   100,   103,     0,     0,    29,     0,
       0,   397,     0,     0,   278,   279,   280,   399,   477,   281,
     282,   283,     0,   324,    55,     0,     0,     0,     0,     0,
       0,     0,     0,   245,   247,   312,   237,   238,   320,     0,
     308,   306,   290,   291,   292,     0,     0,   287,   288,   289,
       0,   419,     0,     0,     0,     0,   178,     0,     0,     0,
       0,     0,     0,   174,   216,   215,   223,     0,   464,   468,
     494,   484,   496,     1,    13,   326,     0,     0,     0,     0,
       0,     0,     0,   261,   122,   141,   121,     0,     0,     0,
      23,    22,    20,    21,    14,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     2,     0,     0,
       0,     9,   489,   488,     0,   490,   219,     0,     0,   235,
       0,     0,     0,     0,   481,   480,   492,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    53,     0,     0,   458,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    24,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     339,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   478,    57,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   234,
       0,     0,     0,     0,     0,     0,   168,     0,     0,     0,
       0,   221,   460,   465,   325,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    27,     0,     0,     0,     0,    33,
       0,   119,   124,   125,   127,   129,   132,   131,   138,   137,
     136,   135,   134,   139,   143,   145,   147,   149,   151,   262,
     264,     0,     0,     5,     6,   302,     0,     0,   218,     0,
       0,     0,   266,     0,     0,   201,   202,   479,   333,   335,
       0,   163,   318,   317,   319,     0,   240,   242,     0,     8,
       7,     0,   451,   456,   469,   457,   459,   226,   225,     0,
       0,    11,     0,   167,     0,     0,   354,   353,     0,     0,
       0,     0,     0,     0,   310,     0,     0,     0,   232,     0,
       0,     0,   322,   203,   204,   207,   474,   208,     0,     0,
     213,   209,   210,   211,     0,   205,   206,     0,     0,   191,
     192,     0,     0,   323,    56,     0,     0,     0,     0,     0,
     172,     0,     0,   244,   246,   233,   307,   315,     0,   330,
     329,     0,   177,   176,     0,     0,     0,     0,   173,    45,
      46,    49,    50,     0,    52,    48,    47,    43,    44,   260,
      36,     0,     0,    39,    32,     0,     0,     0,     0,    53,
     491,     0,     0,     0,     0,     0,     0,     0,    54,    13,
     446,   447,   455,     0,   450,     0,     0,   231,   229,   379,
     380,   381,     0,   195,   193,   196,     0,     0,     0,     0,
     349,   350,   340,   180,     0,     0,   272,   273,   274,     0,
     476,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   171,     0,
       0,     0,     0,     0,   263,     0,     0,   217,     0,     0,
     267,     0,   162,   164,   184,   442,   444,   452,   445,   449,
     454,   443,   448,   453,     0,     0,    24,     0,     0,     0,
       0,     0,   342,   343,   341,     0,     0,   475,     0,   212,
     187,   189,   188,   190,   437,     0,   294,     0,   435,     0,
       0,   432,     0,     0,     0,     0,     0,     0,    51,     0,
     258,     0,    40,    38,     0,     0,   438,     0,   268,     0,
     230,   228,     0,     0,   425,     0,     0,     0,     0,   214,
     436,   293,   434,   169,   433,     0,     0,     0,     0,   170,
     259,     0,     0,   430,     0,     0,   183,   198,     0,     0,
     424,     0,   421,     0,     0,     0,     0,   256,     0,     0,
       0,     0,    41,   431,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   257,     0,     0,     0,
       0,     0,     0,   420,     0,     0,     0,   153,   154,   157,
     156,   155,   255,     0,     0,    42,     0,     0,     0,     0,
       0,     0,     0,   253,     0,     0,     0,   439,   429,     0,
       0,     0,   440,   441,     0,     0,     0,     0,   428,   427,
       0,     0,   252,     0,     0,     0,   426,     0,     0,   254,
     249,     0,     0,     0,   248,   251,     0,   250
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -633,    25,   121,     0,   -78,    19,  -633,  -633,  -633,  -243,
    -226,   -82,  -633,   -69,  -165,   143,   141,  -164,  -195,   397,
     134,   135,   133,   136,   137,  -633,   298,  -368,  -633,  -633,
    -147,  -201,  -633,  -633,  -633,  -633,  -105,  -632,  -161,  -305,
    -320,  -225,  -633,  -633,  -633,  -633,    -4,     3,   -28,   -27,
    -246,  -349,   -63,  -633,  -633,   132,  -633,  -633
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   254,   255,   232,   304,   276,   233,   234,   434,   235,
     487,   465,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   327,   932,   128,   129,
     621,   622,   130,   281,   284,   131,   328,   763,   132,   133,
     329,   648,   134,   135,   136,   137,   138,   139,   140,   277,
     667,   365,   278,   141,   261,   466,   142,   143
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     127,   339,   318,   319,   363,   279,   145,   430,   510,   927,
     457,   282,   263,   437,   534,   431,   127,   927,   491,   264,
     396,   148,   639,   646,   814,   628,   403,   628,   337,    54,
     713,   271,   386,   127,   280,   517,   258,   519,   520,   522,
     523,   524,   525,   722,   528,   961,   289,   628,   494,   851,
     145,   145,   406,   147,    54,   901,   303,   534,    54,   145,
     311,   251,   312,  -194,  -199,   659,   145,   488,   286,    52,
     330,   485,   290,   306,   788,   352,   510,   144,   366,   303,
     332,   302,   253,   510,   368,   371,   307,   145,   503,   313,
     888,   314,   898,   849,  -194,  -199,   907,   147,   147,  -194,
    -199,   145,   333,   334,   259,   379,   147,   292,   308,   309,
     391,   362,   385,   147,   470,   441,   534,   293,   373,   375,
     377,   378,   529,    54,   265,   381,   408,   146,  -194,  -199,
     315,   387,   388,   424,   147,   316,   850,   530,   490,   266,
     896,   252,   270,   426,   442,    54,   677,   392,   147,   253,
     395,   404,   405,   678,   599,   353,   402,   283,   367,   300,
     744,   335,   272,   291,   369,   372,   338,   310,   504,   613,
     889,   668,   899,   928,   297,   298,   908,   432,   668,   668,
     518,   928,   301,   305,   746,   260,   929,   253,   527,   930,
     389,   471,   274,   581,   929,   273,   492,   930,   630,   629,
     640,   647,   815,   714,   376,   267,   268,   145,   873,   580,
     317,   488,   534,    52,   489,   879,   723,   443,   433,   275,
     724,   734,   852,   438,   380,  -194,  -199,   275,   902,   294,
     295,   516,    51,   358,   444,   354,   355,   382,   383,   749,
     750,   445,   766,   767,   331,   145,   370,   474,   588,   589,
     590,   591,   592,   593,   147,    50,    51,    52,   263,   297,
     298,   931,   127,   374,   269,   264,   516,    51,   351,   931,
     390,   535,   582,   583,   393,   446,   394,   586,   587,   623,
     624,   675,   676,   397,   398,   399,   464,   521,   296,   400,
     407,   447,   147,   408,   356,   409,   384,   410,   751,   411,
     412,   768,   413,   414,   416,   250,   417,   418,   419,   448,
     256,   257,   420,   499,   421,   427,   436,   428,   769,   429,
     435,   439,   449,   440,   450,   561,   769,   769,   451,   452,
     454,   513,   453,   456,   534,   458,   459,   467,   498,   472,
     285,   287,   288,   473,   475,   476,   477,   478,   479,   480,
     482,   481,   483,   299,   484,   494,   496,   505,   506,   501,
     507,   511,   508,   512,   515,   321,   532,   526,   533,   772,
     510,   358,   541,   544,   538,   336,   540,   543,   349,   350,
     545,   534,   510,   510,   364,   547,   546,   548,   510,   551,
     552,   554,   555,   614,   560,   574,   575,   601,   609,   611,
     293,   577,   619,   642,   562,   645,   649,   650,   127,   657,
     652,   563,   660,   637,   638,   292,   661,   681,   654,   685,
     674,   687,   691,   696,   698,   701,   704,   705,   721,   578,
     709,   725,   364,   706,   710,   727,   690,   728,   711,   731,
     735,   712,   565,   567,   415,   570,   572,   715,   617,   702,
     703,   683,   716,   717,   718,   708,   720,   736,   752,   737,
     743,   635,   733,   739,   745,   757,   828,   759,   760,   776,
     773,   303,   774,   600,   778,   780,   761,   618,   771,   783,
     791,   795,   794,   603,   799,   634,   464,   801,   818,   127,
     820,   303,   303,   825,   641,   826,   422,   834,   423,   836,
     838,   854,   841,   840,   843,   844,   859,   877,   633,   636,
     857,   867,   881,   884,   845,   846,   900,   863,   875,   876,
     909,   885,   913,   847,   878,   894,   895,   730,   891,   918,
     848,   919,   853,   855,   924,   856,   663,   664,   665,   666,
     864,   670,   671,   672,   673,   925,   666,   666,   697,   455,
     866,   906,   870,   912,   871,   679,   872,   874,   915,   364,
     922,   747,   748,   933,   468,   938,   890,   939,   469,   944,
     946,   951,   954,   893,   963,   964,   968,   971,   972,   976,
     605,   585,   584,   594,   596,   595,   962,   935,   597,   803,
     598,   943,   862,   608,   719,   486,   486,     0,     0,   493,
       0,     0,     0,     0,   425,   495,   947,     0,     0,   948,
       0,   500,     0,   502,     0,   952,     0,   953,   956,   958,
     959,     0,   965,     0,   509,   966,     0,     0,   741,     0,
     514,     0,   127,     0,     0,   742,     0,     0,     0,   303,
     303,     0,     0,     0,     0,   753,     0,     0,   754,   755,
     531,   740,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   536,   537,     0,   539,     0,     0,   542,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   549,     0,     0,   770,   550,     0,
       0,     0,   553,     0,     0,     0,   556,   557,   558,   559,
       0,     0,     0,     0,     0,   364,     0,     0,     0,     0,
       0,     0,     0,     0,   564,   566,   568,   569,   571,   573,
       0,     0,     0,     0,     0,   576,     0,     0,   797,     0,
       0,     0,     0,   486,     0,   802,   860,   861,   790,   806,
     809,   812,     0,   127,   127,   127,   807,   810,   813,     0,
       0,     0,   816,     0,   602,     0,   604,   256,   606,   364,
       0,     0,   805,   808,   811,   610,     0,     0,   612,     0,
     615,   616,     0,     0,     0,     0,     0,   620,   620,   620,
     625,   626,   627,     0,     0,     0,   880,     0,   827,     0,
       0,   829,     0,     0,   643,   644,     0,     0,   830,   832,
       0,   651,     0,   653,     0,   655,   656,     0,     0,   658,
       0,     0,     0,   662,   303,   303,     0,     0,     0,   669,
       0,     0,     0,     0,     0,     0,     0,     0,   680,     0,
     682,   364,   684,     0,     0,     0,   686,   916,   688,     0,
       0,   692,   693,   694,   695,     0,     0,   869,     0,   699,
     700,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   887,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   897,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   726,
       0,     0,     0,     0,     0,   729,     0,   364,     0,   732,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   738,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   756,     0,
     758,     0,     0,     0,     0,   762,     0,   764,   765,     0,
       0,     0,     0,     0,   970,     0,     0,     0,     0,     0,
       0,   974,     0,     0,     0,     0,     0,     0,     0,   775,
       0,     0,     0,   777,     0,   779,     0,   781,     0,   782,
       0,     0,     0,     0,     0,     0,   784,     0,     0,   785,
       0,     0,   786,   787,   762,   789,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   792,
     793,     0,     0,     0,     0,   796,     0,     0,     0,   798,
       0,   800,     0,     0,   620,   804,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     817,     0,     0,     0,     0,   819,     0,   821,     0,     0,
       0,   824,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   831,   833,     0,   835,     0,   837,     0,   839,     0,
       0,   842,     0,     0,     0,     0,   824,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   858,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   865,     0,
       0,     0,     0,     0,   868,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   762,     0,
       0,     0,     0,     0,     0,   762,     0,     0,     0,   882,
       0,     0,   883,     0,     0,     0,     0,   886,     0,     0,
       0,     0,     0,     0,     0,   892,     0,     0,     0,     0,
       0,   824,     0,     0,     0,     0,     0,   824,     0,     0,
       0,     0,   903,   904,     0,     0,   905,     0,     0,     0,
       0,     0,   910,   911,     0,     0,   914,     0,     0,   917,
       0,     0,     0,     0,   920,   921,     0,   923,     0,     0,
     926,     0,     0,   934,     0,     0,   936,   937,     0,     0,
     940,     0,   941,   942,     0,     0,     0,     0,     0,     0,
       0,   945,     0,     0,     0,     0,   949,   950,     0,     0,
       0,     0,   955,     0,   957,     0,     0,   149,   150,   960,
       0,     0,   151,     0,   152,   153,     0,     0,     0,   967,
       0,   969,     0,   154,     0,     0,   973,   155,   156,     0,
     975,     0,     0,     0,   977,     0,     0,     0,   340,     0,
       0,     0,     0,     0,     0,   157,   158,   159,   160,   161,
     162,     0,   163,     0,     0,     0,     0,     0,     0,     0,
     164,     0,     0,     0,     0,   165,   166,     0,     0,     0,
       0,   167,     0,     0,     0,   168,   169,   341,     0,   170,
       0,     0,     0,   171,   172,   173,     0,   174,   175,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   342,   176,
     177,    54,     0,     0,     0,     0,   178,   179,     0,   180,
       0,   181,   182,     0,     0,     0,   183,   184,     0,   185,
     343,     0,     0,   186,   187,   188,   189,     0,   190,   191,
       0,   192,   193,     0,     0,     0,     0,     0,     0,   194,
       0,   195,   196,   197,     0,     0,     0,     0,     0,   198,
       0,   199,     0,   201,   202,     0,   203,   204,   205,     0,
       0,     0,   344,     0,     0,     0,     0,     0,   207,   208,
     209,     0,     0,     0,     0,     0,     0,     0,   210,   345,
       0,     0,   346,   212,   213,     0,     0,   214,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   215,     0,   216,     0,     0,     0,
       0,     0,     0,     0,     0,   217,     0,     0,     0,     0,
     218,     0,   219,     0,   220,     0,   221,     0,     0,     0,
     347,   222,   223,   224,     0,     0,     0,     0,   225,     0,
       0,     0,     0,   348,     0,     0,     0,     0,     0,   227,
     228,   229,     0,   230,   149,   150,   357,     0,     0,   151,
     231,   152,   153,     0,     0,     0,     0,     0,     0,     0,
     154,     0,     0,     0,   155,   156,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   358,     0,     0,     0,
       0,     0,   157,   158,   159,   160,   161,   162,     0,   163,
       0,     0,     0,     0,     0,     0,     0,   164,     0,     0,
       0,     0,   165,   166,     0,     0,     0,     0,   167,     0,
       0,     0,   168,   169,     0,     0,   170,     0,     0,     0,
     171,   172,   173,     0,   174,   175,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   176,   177,    54,     0,
       0,     0,     0,   178,   179,     0,   180,     0,   181,   182,
       0,     0,     0,   183,   184,     0,   185,     0,     0,     0,
     186,   187,   188,   189,     0,   190,   191,     0,   192,   193,
       0,     0,     0,     0,     0,     0,   194,     0,   195,   196,
     197,     0,     0,     0,     0,     0,   198,     0,   199,     0,
     201,   202,     0,   203,   204,   205,     0,     0,     0,   206,
       0,     0,     0,     0,     0,   207,   208,   209,   359,   360,
       0,     0,     0,     0,     0,   210,   211,     0,     0,     0,
     212,   213,     0,     0,   214,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   215,     0,   216,     0,     0,     0,     0,     0,     0,
       0,     0,   217,     0,     0,     0,     0,   218,   253,   219,
       0,   220,     0,   221,     0,     0,     0,   361,   222,   223,
     224,     0,     0,     0,     0,   225,     0,     0,     0,     0,
     226,     0,     0,     0,   149,   150,   227,   228,   229,   151,
     230,   152,   153,     0,     0,     0,     0,   231,     0,     0,
     154,     0,     0,     0,   155,   156,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   322,     0,     0,     0,
       0,     0,   157,   158,   159,   160,   161,   162,     0,   163,
       0,     0,     0,     0,     0,     0,     0,   164,     0,     0,
       0,     0,   165,   166,     0,     0,     0,     0,   167,     0,
       0,     0,   168,   169,     0,     0,   170,     0,     0,     0,
     171,   172,   173,     0,   174,   175,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   176,   177,    54,     0,
       0,     0,     0,   178,   179,     0,   180,     0,   181,   182,
       0,     0,     0,   183,   184,     0,   185,     0,     0,     0,
     186,   187,   188,   189,     0,   190,   191,     0,   192,   193,
       0,     0,     0,     0,     0,     0,   194,     0,   195,   196,
     197,     0,     0,     0,     0,     0,   198,     0,   199,     0,
     201,   202,     0,   203,   204,   205,     0,     0,     0,   206,
       0,     0,     0,     0,     0,   207,   208,   209,     0,     0,
       0,     0,     0,     0,     0,   210,   211,     0,     0,     0,
     212,   213,     0,     0,   214,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   215,     0,   216,     0,     0,     0,     0,     0,     0,
       0,     0,   217,     0,   323,     0,     0,   218,   253,   219,
       0,   220,   324,   221,     0,     0,     0,     0,   222,   223,
     224,     0,     0,     0,   325,   225,     0,     0,     0,     0,
     226,     0,     0,     0,     0,   401,   227,   228,   229,     0,
     230,   149,   150,     0,     0,     0,   151,   231,   152,   153,
       0,     0,     0,     0,     0,     0,     0,   154,     0,     0,
       0,   155,   156,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   322,     0,     0,     0,     0,     0,   157,
     158,   159,   160,   161,   162,     0,   163,     0,     0,     0,
       0,     0,     0,     0,   164,     0,     0,     0,     0,   165,
     166,     0,     0,     0,     0,   167,     0,     0,     0,   168,
     169,     0,     0,   170,     0,     0,     0,   171,   172,   173,
       0,   174,   175,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   176,   177,    54,     0,     0,     0,     0,
     178,   179,     0,   180,     0,   181,   182,     0,     0,     0,
     183,   184,     0,   185,     0,     0,     0,   186,   187,   188,
     189,     0,   190,   191,     0,   192,   193,     0,     0,     0,
       0,     0,     0,   194,     0,   195,   196,   197,     0,     0,
       0,     0,     0,   198,     0,   199,     0,   201,   202,     0,
     203,   204,   205,     0,     0,     0,   206,     0,     0,     0,
       0,     0,   207,   208,   209,     0,     0,     0,     0,     0,
       0,     0,   210,   211,     0,     0,     0,   212,   213,     0,
       0,   214,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   215,     0,
     216,     0,     0,     0,     0,     0,     0,     0,     0,   217,
       0,   323,     0,     0,   218,     0,   219,     0,   220,   324,
     221,     0,     0,     0,     0,   222,   223,   224,     0,     0,
       0,   325,   225,     0,     0,     0,     0,   226,     0,     0,
       0,     0,   326,   227,   228,   229,     0,   230,   149,   150,
       0,     0,     0,   151,   231,   152,   153,     0,     0,     0,
       0,     0,     0,     0,   154,     0,     0,     0,   155,   156,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     322,     0,     0,     0,     0,     0,   157,   158,   159,   160,
     161,   162,     0,   163,     0,     0,     0,     0,     0,     0,
       0,   164,     0,     0,     0,     0,   165,   166,     0,     0,
       0,     0,   167,     0,     0,     0,   168,   169,     0,     0,
     170,     0,     0,     0,   171,   172,   173,     0,   174,   175,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     176,   177,    54,     0,     0,     0,     0,   178,   179,     0,
     180,     0,   181,   182,     0,     0,     0,   183,   184,     0,
     185,     0,     0,     0,   186,   187,   188,   189,     0,   190,
     191,     0,   192,   193,     0,     0,     0,     0,     0,     0,
     194,     0,   195,   196,   197,     0,     0,     0,     0,     0,
     198,     0,   199,     0,   201,   202,     0,   203,   204,   205,
       0,     0,     0,   206,     0,     0,     0,     0,     0,   207,
     208,   209,     0,     0,     0,     0,     0,     0,     0,   210,
     211,     0,     0,     0,   212,   213,     0,     0,   214,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   215,     0,   216,     0,     0,
       0,     0,     0,     0,     0,     0,   217,     0,   323,     0,
       0,   218,   253,   219,     0,   220,   324,   221,     0,     0,
       0,     0,   222,   223,   224,     0,     0,     0,   325,   225,
       0,     0,     0,     0,   226,     0,     0,     0,   149,   150,
     227,   228,   229,   151,   230,   152,   153,     0,     0,     0,
       0,   231,     0,     0,   154,     0,     0,     0,   155,   156,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     358,     0,     0,     0,     0,   460,   157,   158,   159,   160,
     161,   162,     0,   163,     0,     0,     0,     0,     0,     0,
       0,   164,     0,     0,     0,     0,   165,   166,     0,     0,
       0,     0,   167,     0,     0,     0,   168,   169,     0,     0,
     170,     0,     0,     0,   171,   172,   173,     0,   174,   175,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     176,   177,   461,     0,     0,     0,     0,   178,   179,     0,
     180,     0,   181,   182,     0,     0,     0,   183,   184,     0,
     185,     0,     0,     0,   186,   187,   188,   189,     0,   190,
     191,     0,   192,   193,     0,     0,     0,     0,     0,     0,
     194,     0,   195,   196,   197,     0,     0,     0,     0,     0,
     198,     0,   199,     0,   201,   202,     0,   203,   204,   205,
       0,     0,     0,   206,     0,     0,     0,     0,     0,   207,
     208,   209,   462,   463,     0,     0,     0,     0,     0,   210,
     211,     0,     0,     0,   212,   213,     0,     0,   214,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   215,     0,   216,     0,     0,
       0,     0,     0,     0,     0,     0,   217,     0,     0,     0,
       0,   218,   253,   219,     0,   220,     0,   221,     0,     0,
       0,     0,   222,   223,   224,     0,     0,     0,     0,   225,
       0,     0,     0,     0,   226,     0,     0,     0,   149,   150,
     227,   228,   229,   151,   230,   152,   153,     0,     0,     0,
       0,   231,     0,     0,   154,     0,     0,     0,   155,   156,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     358,     0,     0,     0,     0,     0,   157,   158,   159,   160,
     161,   162,     0,   163,     0,     0,     0,     0,     0,     0,
       0,   164,     0,     0,     0,     0,   165,   166,     0,     0,
       0,     0,   167,     0,     0,     0,   168,   169,     0,     0,
     170,     0,     0,     0,   171,   172,   173,     0,   174,   175,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     176,   177,    54,     0,     0,     0,     0,   178,   179,     0,
     180,     0,   181,   182,     0,     0,     0,   183,   184,     0,
     185,     0,     0,     0,   186,   187,   188,   189,     0,   190,
     191,     0,   192,   193,     0,     0,     0,     0,     0,     0,
     194,     0,   195,   196,   197,     0,     0,     0,     0,   297,
     607,     0,   199,     0,   201,   202,     0,   203,   204,   205,
       0,     0,     0,   206,     0,     0,     0,     0,     0,   207,
     208,   209,   462,   463,     0,     0,     0,     0,     0,   210,
     211,     0,     0,     0,   212,   213,     0,     0,   214,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   215,     0,   216,     0,     0,
       0,     0,     0,     0,     0,     0,   217,     0,     0,     0,
       0,   218,   253,   219,     0,   220,     0,   221,     0,     0,
       0,     0,   222,   223,   224,     0,     0,     0,     0,   225,
       0,     0,     0,     0,   226,     0,     0,     0,   149,   150,
     227,   228,   229,   151,   230,   152,   153,     0,     0,     0,
       0,   231,     0,     0,   154,     0,     0,     0,   155,   156,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     322,     0,     0,     0,     0,     0,   157,   158,   159,   160,
     161,   162,     0,   163,     0,     0,     0,     0,     0,     0,
       0,   164,     0,     0,     0,     0,   165,   166,     0,     0,
       0,     0,   167,     0,     0,     0,   168,   169,     0,     0,
     170,     0,     0,     0,   171,   172,   173,     0,   174,   175,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     176,   177,    54,     0,     0,     0,     0,   178,   179,     0,
     180,     0,   181,   182,     0,     0,     0,   183,   184,     0,
     185,     0,     0,     0,   186,   187,   188,   189,     0,   190,
     191,     0,   192,   193,     0,     0,     0,     0,     0,     0,
     194,     0,   195,   196,   197,     0,     0,     0,     0,     0,
     198,     0,   199,     0,   201,   202,     0,   203,   204,   205,
       0,     0,     0,   206,     0,     0,     0,     0,     0,   207,
     208,   209,     0,     0,     0,     0,     0,     0,     0,   210,
     211,     0,     0,     0,   212,   213,     0,     0,   214,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   215,     0,   216,     0,     0,
       0,     0,     0,     0,     0,     0,   217,     0,   323,     0,
       0,   218,     0,   219,     0,   220,   324,   221,     0,     0,
       0,     0,   222,   223,   224,     0,     0,     0,   325,   225,
       0,     0,     0,     0,   226,     0,     0,     0,     0,   689,
     227,   228,   229,     0,   230,   149,   150,     0,     0,     0,
     151,   231,   152,   153,     0,     0,     0,     0,     0,     0,
       0,   154,     0,     0,     0,   155,   156,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   322,     0,     0,
       0,     0,     0,   157,   158,   159,   160,   161,   162,     0,
     163,     0,     0,     0,     0,     0,     0,     0,   164,     0,
       0,     0,     0,   165,   166,     0,     0,     0,     0,   167,
       0,     0,     0,   168,   169,     0,     0,   170,     0,     0,
       0,   171,   172,   173,     0,   174,   175,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   176,   177,    54,
       0,     0,     0,     0,   178,   179,     0,   180,     0,   181,
     182,     0,     0,     0,   183,   184,     0,   185,     0,     0,
       0,   186,   187,   188,   189,     0,   190,   191,     0,   192,
     193,     0,     0,     0,     0,     0,     0,   194,     0,   195,
     196,   197,     0,     0,     0,     0,     0,   198,     0,   199,
       0,   201,   202,     0,   203,   204,   205,     0,     0,     0,
     206,     0,     0,     0,     0,     0,   207,   208,   209,     0,
       0,     0,     0,     0,     0,     0,   210,   211,     0,     0,
       0,   212,   213,     0,     0,   214,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   215,     0,   216,     0,     0,     0,     0,     0,
       0,     0,     0,   217,     0,   323,     0,     0,   218,     0,
     219,     0,   220,   324,   221,     0,     0,     0,     0,   222,
     223,   224,     0,     0,     0,   325,   225,     0,     0,     0,
       0,   226,     0,     0,     0,     0,   707,   227,   228,   229,
       0,   230,   149,   150,     0,     0,     0,   151,   231,   152,
     153,     0,     0,     0,     0,     0,     0,     0,   154,     0,
       0,     0,   155,   156,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   322,     0,     0,     0,     0,     0,
     157,   158,   159,   160,   161,   162,     0,   163,     0,     0,
       0,     0,     0,     0,     0,   164,     0,     0,     0,     0,
     165,   166,     0,     0,     0,     0,   167,     0,     0,     0,
     168,   169,     0,     0,   170,     0,     0,     0,   171,   172,
     173,     0,   174,   175,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   176,   177,    54,     0,     0,     0,
       0,   178,   179,     0,   180,     0,   181,   182,     0,     0,
       0,   183,   184,     0,   185,     0,     0,     0,   186,   187,
     188,   189,     0,   190,   191,     0,   192,   193,     0,     0,
       0,     0,     0,     0,   194,     0,   195,   196,   197,     0,
       0,     0,     0,     0,   198,     0,   199,     0,   201,   202,
       0,   203,   204,   205,     0,     0,     0,   206,     0,     0,
       0,     0,     0,   207,   208,   209,     0,     0,     0,     0,
       0,     0,     0,   210,   211,     0,     0,     0,   212,   213,
       0,     0,   214,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   215,
       0,   216,     0,     0,     0,     0,     0,     0,     0,     0,
     217,     0,   323,     0,     0,   218,     0,   219,     0,   220,
     324,   221,     0,     0,     0,     0,   222,   223,   224,     0,
       0,     0,   325,   225,     0,     0,     0,     0,   226,     0,
       0,     0,   149,   150,   227,   228,   229,   151,   230,   152,
     153,     0,     0,     0,     0,   231,     0,     0,   154,     0,
       0,     0,   155,   156,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     157,   158,   159,   160,   161,   162,     0,   163,     0,     0,
       0,     0,     0,     0,     0,   164,     0,     0,     0,     0,
     165,   166,     0,     0,     0,     0,   167,     0,     0,     0,
     168,   169,     0,     0,   170,     0,     0,     0,   171,   172,
     173,     0,   174,   175,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   176,   177,    54,     0,     0,     0,
       0,   178,   179,     0,   180,     0,   181,   182,     0,     0,
       0,   183,   184,     0,   185,     0,     0,     0,   186,   187,
     188,   189,     0,   190,   191,     0,   192,   193,     0,     0,
       0,     0,     0,     0,   194,     0,   195,   196,   197,     0,
       0,     0,     0,     0,   198,     0,   199,     0,   201,   202,
       0,   203,   204,   205,     0,     0,     0,   206,     0,     0,
       0,     0,     0,   207,   208,   209,     0,     0,     0,     0,
       0,     0,     0,   210,   211,     0,     0,     0,   212,   213,
       0,     0,   214,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   215,
       0,   216,     0,     0,     0,     0,     0,     0,     0,     0,
     217,     0,     0,     0,     0,   218,   253,   219,     0,   220,
       0,   221,     0,     0,     0,     0,   222,   223,   224,     0,
       0,     0,     0,   225,     0,     0,     0,     0,   226,     0,
       0,     0,     0,     0,   227,   228,   229,     0,   230,   497,
       0,   149,   150,     0,     0,   231,   151,     0,   152,   153,
       0,     0,     0,     0,     0,     0,     0,   154,     0,     0,
       0,   155,   156,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   822,     0,     0,     0,     0,     0,   157,
     158,   159,   160,   161,   162,     0,   163,     0,     0,     0,
       0,     0,     0,     0,   164,     0,     0,     0,     0,   165,
     166,     0,     0,     0,     0,   167,     0,     0,     0,   168,
     169,     0,     0,   170,     0,     0,     0,   171,   172,   173,
       0,   174,   175,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   176,   177,    54,     0,     0,     0,     0,
     178,   179,     0,   180,     0,   181,   182,     0,     0,     0,
     183,   184,     0,   185,     0,     0,     0,   186,   187,   188,
     189,     0,   190,   191,     0,   192,   193,     0,     0,     0,
       0,     0,     0,   194,     0,   195,   196,   197,     0,     0,
       0,     0,     0,   198,     0,   199,     0,   201,   202,     0,
     203,   204,   205,     0,     0,     0,   206,     0,     0,     0,
       0,     0,   207,   208,   209,     0,     0,     0,     0,     0,
       0,     0,   210,   211,     0,     0,     0,   212,   213,     0,
       0,   214,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   215,     0,
     216,     0,     0,     0,     0,     0,     0,     0,     0,   217,
       0,   823,     0,     0,   218,     0,   219,     0,   220,     0,
     221,     0,     0,     0,     0,   222,   223,   224,     0,     0,
       0,     0,   225,     0,     0,     0,     0,   226,     0,     0,
       0,   149,   150,   227,   228,   229,   151,   230,   152,   153,
       0,     0,     0,     0,   231,     0,     0,   154,     0,     0,
       0,   155,   156,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   157,
     158,   159,   160,   161,   162,     0,   163,     0,     0,     0,
       0,     0,     0,     0,   164,     0,     0,     0,     0,   165,
     166,     0,     0,     0,     0,   167,     0,     0,     0,   168,
     169,     0,     0,   170,     0,     0,     0,   171,   172,   173,
       0,   174,   175,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   176,   177,    54,     0,     0,     0,     0,
     178,   179,     0,   180,     0,   181,   182,     0,     0,     0,
     183,   184,     0,   185,     0,     0,     0,   186,   187,   188,
     189,     0,   190,   191,     0,   192,   193,     0,     0,     0,
       0,     0,     0,   194,     0,   195,   196,   197,     0,     0,
       0,     0,     0,   198,     0,   199,   200,   201,   202,     0,
     203,   204,   205,     0,     0,     0,   206,     0,     0,     0,
       0,     0,   207,   208,   209,     0,     0,     0,     0,     0,
       0,     0,   210,   211,     0,     0,     0,   212,   213,     0,
       0,   214,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   215,     0,
     216,     0,     0,     0,     0,     0,     0,     0,     0,   217,
       0,     0,     0,     0,   218,     0,   219,     0,   220,     0,
     221,     0,     0,     0,     0,   222,   223,   224,     0,     0,
       0,     0,   225,     0,     0,     0,     0,   226,     0,     0,
       0,   149,   150,   227,   228,   229,   151,   230,   152,   153,
       0,     0,     0,     0,   231,     0,     0,   154,     0,     0,
       0,   155,   156,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   157,
     158,   159,   160,   161,   162,     0,   163,     0,     0,     0,
       0,     0,     0,     0,   164,     0,     0,     0,     0,   165,
     166,     0,     0,     0,     0,   167,     0,     0,     0,   168,
     169,     0,     0,   170,     0,     0,     0,   171,   172,   173,
       0,   174,   175,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   176,   177,    54,     0,     0,     0,     0,
     178,   179,     0,   180,     0,   181,   182,     0,     0,     0,
     183,   184,     0,   185,     0,     0,     0,   186,   187,   188,
     189,     0,   190,   191,     0,   192,   193,     0,     0,     0,
       0,     0,     0,   194,     0,   195,   196,   197,     0,     0,
       0,     0,     0,   198,     0,   199,     0,   201,   202,     0,
     203,   204,   205,     0,     0,     0,   206,     0,     0,     0,
       0,     0,   207,   208,   209,     0,     0,     0,     0,     0,
       0,     0,   210,   211,     0,     0,     0,   212,   213,     0,
       0,   214,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   215,     0,
     216,     0,     0,     0,     0,     0,     0,     0,     0,   217,
       0,     0,     0,     0,   218,   253,   219,     0,   220,     0,
     221,     0,     0,     0,     0,   222,   223,   224,     0,     0,
       0,     0,   225,     0,     0,     0,     0,   226,     0,     0,
       0,   149,   150,   227,   228,   229,   151,   230,   152,   153,
       0,     0,     0,     0,   231,     0,     0,   154,     0,     0,
       0,   155,   156,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   157,
     158,   159,   160,   161,   162,     0,   163,     0,     0,     0,
       0,     0,     0,     0,   164,     0,     0,     0,     0,   165,
     166,     0,     0,     0,     0,   167,     0,     0,     0,   168,
     169,     0,     0,   170,     0,     0,     0,   171,   172,   173,
       0,   174,   175,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   176,   177,    54,     0,     0,     0,     0,
     178,   179,     0,   180,     0,   181,   182,     0,     0,     0,
     183,   184,     0,   185,     0,     0,     0,   186,   187,   188,
     189,     0,   190,   191,     0,   192,   193,     0,     0,     0,
       0,     0,     0,   194,     0,   195,   196,   197,     0,     0,
       0,     0,     0,   198,     0,   199,     0,   201,   202,     0,
     203,   204,   205,     0,     0,     0,   206,     0,     0,     0,
       0,     0,   207,   208,   209,     0,     0,     0,     0,     0,
       0,     0,   210,   211,     0,     0,     0,   212,   213,     0,
       0,   214,     0,     0,     0,     0,     0,     0,     0,   320,
       0,     0,     0,     0,     0,     0,     0,     0,   215,     0,
     216,     0,     0,     0,     0,     0,     0,     0,     0,   217,
       0,     0,     0,     0,   218,     0,   219,     0,   220,     0,
     221,     0,     0,     0,     0,   222,   223,   224,     0,     0,
       0,     0,   225,     0,     0,     0,     0,   226,     0,     0,
       0,   149,   150,   227,   228,   229,   151,   230,   152,   153,
       0,     0,     0,     0,   231,     0,     0,   154,     0,     0,
       0,   155,   156,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   358,     0,     0,     0,     0,     0,   157,
     158,   159,   160,   161,   162,     0,   163,     0,     0,     0,
       0,     0,     0,     0,   164,     0,     0,     0,     0,   165,
     166,     0,     0,     0,     0,   167,     0,     0,     0,   168,
     169,     0,     0,   170,     0,     0,     0,   171,   172,   173,
       0,   174,   175,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   176,   177,    54,     0,     0,     0,     0,
     178,   179,     0,   180,     0,   181,   182,     0,     0,     0,
     183,   184,     0,   185,     0,     0,     0,   186,   187,   188,
     189,     0,   190,   191,     0,   192,   193,     0,     0,     0,
       0,     0,     0,   194,     0,   195,   196,   197,     0,     0,
       0,     0,     0,   198,     0,   199,     0,   201,   202,     0,
     203,   204,   205,     0,     0,     0,   206,     0,     0,     0,
       0,     0,   207,   208,   209,     0,     0,     0,     0,     0,
       0,     0,   210,   211,     0,     0,     0,   212,   213,     0,
       0,   214,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   215,     0,
     216,     0,     0,     0,     0,     0,     0,     0,     0,   217,
       0,     0,     0,     0,   218,     0,   219,     0,   220,     0,
     221,     0,     0,     0,     0,   222,   223,   224,     0,     0,
       0,     0,   225,     0,     0,     0,     0,   226,     0,     0,
       0,   149,   150,   227,   228,   229,   151,   230,   152,   153,
       0,     0,     0,     0,   231,     0,     0,   154,     0,     0,
       0,   155,   156,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   535,     0,     0,     0,     0,     0,   157,
     158,   159,   160,   161,   162,     0,   163,     0,     0,     0,
       0,     0,     0,     0,   164,     0,     0,     0,     0,   165,
     166,     0,     0,     0,     0,   167,     0,     0,     0,   168,
     169,     0,     0,   170,     0,     0,     0,   171,   172,   173,
       0,   174,   175,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   176,   177,    54,     0,     0,     0,     0,
     178,   179,     0,   180,     0,   181,   182,     0,     0,     0,
     183,   184,     0,   185,     0,     0,     0,   186,   187,   188,
     189,     0,   190,   191,     0,   192,   193,     0,     0,     0,
       0,     0,     0,   194,     0,   195,   196,   197,     0,     0,
       0,     0,     0,   198,     0,   199,     0,   201,   202,     0,
     203,   204,   205,     0,     0,     0,   206,     0,     0,     0,
       0,     0,   207,   208,   209,     0,     0,     0,     0,     0,
       0,     0,   210,   211,     0,     0,     0,   212,   213,     0,
       0,   214,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   215,     0,
     216,     0,     0,     0,     0,     0,     0,     0,     0,   217,
       0,     0,     0,     0,   218,     0,   219,     0,   220,     0,
     221,     0,     0,     0,     0,   222,   223,   224,     0,     0,
       0,     0,   225,     0,     0,     0,     0,   226,     0,     0,
       0,   149,   150,   227,   228,   229,   151,   230,   152,   153,
       0,     0,     0,     0,   231,     0,     0,   154,     0,     0,
       0,   155,   156,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   157,
     158,   159,   160,   161,   162,     0,   163,     0,     0,     0,
       0,     0,     0,     0,   164,     0,     0,     0,     0,   165,
     166,     0,     0,     0,     0,   167,     0,     0,     0,   168,
     169,     0,     0,   170,     0,     0,     0,   171,   172,   173,
       0,   174,   175,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   176,   177,    54,     0,     0,     0,     0,
     178,   179,     0,   180,     0,   181,   182,     0,     0,     0,
     183,   184,     0,   185,     0,     0,     0,   186,   187,   188,
     189,     0,   190,   191,     0,   192,   193,     0,     0,     0,
       0,     0,     0,   194,     0,   195,   196,   197,     0,     0,
       0,     0,     0,   198,     0,   199,     0,   201,   202,     0,
     203,   204,   205,     0,     0,     0,   206,     0,     0,     0,
       0,     0,   207,   208,   209,     0,     0,     0,     0,     0,
       0,     0,   210,   211,     0,     0,     0,   212,   213,     0,
       0,   214,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   215,     0,
     216,     0,     0,     0,     0,     0,   579,     0,     0,   217,
       0,     0,     0,     0,   218,     0,   219,     0,   220,     0,
     221,     0,     0,     0,     0,   222,   223,   224,     0,     0,
       0,     0,   225,     0,     0,     0,     0,   226,     0,     0,
       0,   149,   150,   227,   228,   229,   151,   230,   152,   153,
       0,     0,     0,     0,   231,     0,     0,   154,     0,     0,
       0,   155,   156,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   157,
     158,   159,   160,   161,   162,     0,   163,     0,     0,     0,
       0,     0,     0,     0,   164,     0,     0,     0,     0,   165,
     166,     0,     0,     0,     0,   167,     0,     0,     0,   168,
     169,     0,     0,   170,     0,     0,     0,   171,   172,   173,
       0,   174,   175,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   176,   177,    54,     0,     0,     0,     0,
     178,   179,     0,   180,     0,   181,   182,     0,     0,     0,
     183,   184,     0,   185,     0,     0,     0,   186,   187,   188,
     189,     0,   190,   191,     0,   192,   193,     0,     0,     0,
       0,     0,     0,   194,     0,   195,   196,   197,     0,     0,
       0,     0,     0,   198,     0,   199,     0,   201,   202,     0,
     203,   204,   205,     0,     0,     0,   206,     0,     0,     0,
       0,     0,   207,   208,   209,     0,     0,     0,     0,     0,
       0,     0,   210,   211,     0,     0,     0,   212,   213,     0,
       0,   214,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   215,     0,
     216,     0,     0,     0,     0,     0,     0,     0,     0,   217,
       0,     0,     0,     0,   218,     0,   219,     0,   220,     0,
     221,     0,     0,     0,     0,   222,   223,   224,     0,     0,
       0,     0,   225,     0,     0,     0,     0,   226,     0,     0,
       0,   149,   150,   227,   228,   229,   151,   230,   152,   153,
       0,     0,     0,     0,   231,     0,     0,   154,     0,     0,
       0,   155,   156,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   157,
     158,   159,   160,   161,   162,     0,   163,     0,     0,     0,
       0,     0,     0,     0,   164,     0,     0,     0,     0,   165,
     166,     0,     0,     0,     0,   167,     0,     0,     0,   168,
     169,     0,     0,   170,     0,     0,     0,   171,   172,   173,
       0,   174,   175,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   176,   177,    54,     0,     0,     0,     0,
     178,   179,     0,   180,     0,   181,   182,     0,     0,     0,
     183,   184,     0,   185,     0,     0,     0,   186,   187,   188,
     189,     0,   190,   191,     0,   192,   193,     0,     0,     0,
       0,     0,     0,   194,     0,   195,   196,   197,     0,     0,
       0,     0,     0,   198,     0,   199,     0,   201,   202,     0,
     203,   204,   205,     0,     0,     0,   206,     0,     0,     0,
       0,     0,     0,   208,   209,     0,     0,     0,     0,     0,
       0,     0,   210,   211,     0,     0,     0,   212,   213,     0,
       0,   214,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   215,     0,
     216,     0,     0,     0,     0,     0,     0,     0,     0,   217,
       0,     0,     0,     0,   218,     0,   219,     0,   220,     0,
     221,     0,     0,     0,     0,   222,   223,   224,     0,     0,
       0,     0,   225,     0,     0,     0,     0,   226,     0,     0,
       0,   149,   150,   227,   228,   229,   151,   230,   152,   153,
       0,     0,     0,     0,   231,     0,     0,   154,     0,     0,
       0,   155,   156,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   157,
     158,   159,   160,   161,   162,     0,   163,     0,     0,     0,
       0,     0,     0,     0,   164,     0,     0,     0,     0,   165,
     166,     0,     0,     0,     0,   167,     0,     0,     0,   168,
     169,     0,     0,   170,     0,     0,     0,   171,   172,   173,
       0,   174,   175,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   176,   177,    54,     0,     0,     0,     0,
     178,   179,     0,   180,     0,   181,   182,     0,     0,     0,
     183,   184,     0,   185,     0,     0,     0,   186,   187,   188,
     189,     0,   190,   191,     0,   192,   193,     0,     0,     0,
       0,     0,     0,   194,     0,   195,   196,   197,     0,     0,
       0,     0,     0,   198,     0,   199,     0,   201,     0,     0,
     203,   204,   205,     0,     0,     0,   206,     0,     0,     0,
       0,     0,     0,   208,   209,     0,     0,     0,     0,     0,
       0,     0,   210,   211,     0,     0,     0,     0,   213,     0,
       0,   214,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   215,     0,
     216,     0,     0,     0,     0,     0,     0,     0,     0,   217,
       0,     0,     0,     0,   218,     0,   219,     0,   220,     0,
     221,     0,     0,     0,     0,   222,   223,   224,     0,     0,
       0,     0,   225,     0,     0,     0,     0,   226,     0,     0,
       0,     0,     0,   227,   228,   229,     0,   230,     0,     1,
       0,     0,     2,     0,   231,     3,     4,     5,     6,     0,
       7,     8,     9,     0,     0,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,     0,    20,    21,    22,    23,
      24,     0,     0,     0,     0,     0,     0,    25,    26,    27,
      28,    29,    30,    31,    32,     0,    33,    34,    35,     0,
      36,     0,     0,    37,    38,     0,    39,     0,     0,     0,
      40,     0,     0,    41,    42,     0,    43,    44,    45,     0,
       0,     0,    46,     0,     0,     0,    47,    48,    49,    50,
      51,    52,     0,     0,    53,     0,     0,    54,     0,    55,
       0,     0,     0,     0,    56,     0,    57,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    58,    59,    60,     0,
       0,     0,     0,    61,     0,     0,     0,     0,     0,    62,
      63,    64,    65,    66,    67,     0,    68,     0,     0,     0,
      69,    70,     0,     0,     0,     0,     0,     0,    71,    72,
       0,    73,     0,     0,     0,     0,    74,    75,    76,    77,
       0,    78,     0,    79,     0,     0,     0,     0,    80,    81,
      82,     0,    83,    84,     0,    85,     0,     0,    86,     0,
      87,    88,     0,     0,    89,    90,    91,    92,    93,    94,
      95,    96,    97,     0,    98,     0,    99,   100,   101,   102,
       0,   103,     0,   104,   105,   106,     0,     0,     0,   107,
     108,     0,     0,     0,   109,   110,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   111,     0,     0,     0,
       0,   112,   113,     0,     0,   114,     0,     0,     0,   115,
       0,   116,   117,     0,     0,     0,     0,     0,     0,   118,
     119,     0,   120,   121,   122,   123,   124,   125,   126,   631,
       0,     0,     2,     0,     0,     3,     4,     5,     6,     0,
       7,     8,     9,     0,     0,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,     0,    20,    21,    22,    23,
      24,     0,     0,     0,     0,     0,     0,    25,    26,    27,
      28,    29,    30,    31,    32,     0,   147,    34,    35,     0,
      36,     0,     0,    37,    38,   632,    39,     0,     0,     0,
      40,     0,     0,    41,     0,     0,    43,    44,    45,     0,
       0,     0,    46,     0,     0,     0,    47,    48,    49,    50,
      51,    52,     0,     0,    53,     0,     0,    54,     0,    55,
       0,     0,     0,     0,    56,     0,    57,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    58,    59,    60,     0,
       0,     0,     0,    61,     0,     0,     0,     0,     0,    62,
      63,    64,    65,    66,    67,     0,    68,     0,     0,     0,
      69,    70,     0,     0,     0,     0,     0,     0,    71,    72,
       0,    73,     0,     0,     0,     0,    74,    75,    76,    77,
       0,    78,     0,    79,     0,     0,     0,     0,    80,    81,
      82,     0,    83,    84,     0,    85,     0,     0,    86,     0,
      87,    88,     0,     0,    89,    90,    91,    92,    93,    94,
      95,    96,    97,     0,    98,     0,    99,   100,   101,   102,
       0,   103,     0,   104,   105,   106,     0,     0,     0,   107,
     108,     0,     0,     0,   109,   110,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   111,     0,     0,     0,
       0,   112,   113,     0,     0,   114,     0,     0,     0,   115,
       0,   116,   117,     0,     0,     0,     0,     0,     0,   118,
     119,     0,   120,   121,   122,   123,   124,   125,   126,   631,
       0,     0,     2,     0,     0,     3,     4,     5,     6,     0,
       7,     8,     9,     0,     0,    10,    11,    12,    13,    14,
      15,   262,    17,    18,    19,     0,    20,    21,    22,    23,
      24,     0,     0,     0,     0,     0,     0,    25,    26,    27,
      28,    29,    30,    31,    32,     0,   147,    34,    35,     0,
      36,     0,     0,    37,    38,     0,    39,     0,     0,     0,
      40,     0,     0,    41,     0,     0,    43,    44,    45,     0,
       0,     0,    46,     0,     0,     0,    47,    48,    49,    50,
      51,    52,     0,     0,    53,     0,     0,    54,     0,    55,
       0,     0,     0,     0,    56,     0,    57,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    58,    59,    60,     0,
       0,     0,     0,    61,     0,     0,     0,     0,     0,    62,
      63,    64,    65,    66,    67,     0,    68,     0,     0,     0,
      69,    70,     0,     0,     0,     0,     0,     0,    71,    72,
       0,    73,     0,     0,     0,     0,    74,    75,    76,    77,
       0,    78,     0,    79,     0,     0,     0,     0,    80,    81,
      82,     0,    83,    84,     0,    85,     0,     0,    86,     0,
      87,    88,     0,     0,    89,    90,    91,    92,    93,    94,
      95,    96,    97,     0,    98,     0,    99,   100,   101,   102,
       0,   103,     0,   104,   105,   106,     0,     0,     0,   107,
     108,     0,     0,     0,   109,   110,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   111,     0,     0,     0,
       0,   112,   113,     0,     0,   114,     0,     0,     0,   115,
       0,   116,   117,     0,     0,     0,     0,     0,     0,   118,
     119,     0,   120,   121,   122,   123,   124,   125,   126,     1,
       0,     0,     2,     0,     0,     3,     4,     5,     6,     0,
       7,     8,     9,     0,     0,    10,    11,    12,    13,    14,
      15,   262,    17,    18,    19,     0,    20,    21,    22,    23,
      24,     0,     0,     0,     0,     0,     0,    25,    26,    27,
      28,    29,    30,    31,    32,     0,     0,    34,    35,     0,
      36,     0,     0,    37,    38,     0,    39,     0,     0,     0,
      40,     0,     0,    41,     0,     0,    43,    44,    45,     0,
       0,     0,    46,     0,     0,     0,    47,    48,    49,    50,
      51,    52,     0,     0,    53,     0,     0,    54,     0,    55,
       0,     0,     0,     0,    56,     0,    57,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    58,    59,    60,     0,
       0,     0,     0,    61,     0,     0,     0,     0,     0,    62,
      63,    64,    65,    66,    67,     0,    68,     0,     0,     0,
      69,    70,     0,     0,     0,     0,     0,     0,    71,    72,
       0,    73,     0,     0,     0,     0,    74,    75,    76,    77,
       0,    78,     0,    79,     0,     0,     0,     0,    80,    81,
      82,     0,    83,    84,     0,    85,     0,     0,    86,     0,
      87,    88,     0,     0,    89,    90,    91,    92,    93,    94,
      95,    96,    97,     0,    98,     0,    99,   100,   101,   102,
       0,   103,     0,   104,   105,   106,     0,     0,     0,   107,
     108,     0,     0,     0,   109,   110,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   111,     0,     0,     0,
       0,   112,   113,     0,     0,   114,     0,     0,     0,   115,
       0,   116,   117,     0,     0,     0,     0,     0,     0,   118,
     119,     0,   120,   121,   122,   123,   124,   125,   126,     1,
       0,     0,     2,     0,     0,     3,     4,     5,     6,     0,
       7,     8,     9,     0,     0,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,     0,    20,    21,    22,    23,
      24,     0,     0,     0,     0,     0,     0,    25,    26,    27,
      28,    29,    30,    31,    32,     0,     0,    34,    35,     0,
      36,     0,     0,    37,    38,     0,    39,     0,     0,     0,
      40,     0,     0,    41,     0,     0,    43,    44,    45,     0,
       0,     0,    46,     0,     0,     0,    47,    48,    49,    50,
      51,    52,     0,     0,    53,     0,     0,    54,     0,    55,
       0,     0,     0,     0,    56,     0,    57,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    58,    59,    60,     0,
       0,     0,     0,    61,     0,     0,     0,     0,     0,    62,
      63,    64,    65,    66,    67,     0,    68,     0,     0,     0,
      69,    70,     0,     0,     0,     0,     0,     0,    71,    72,
       0,    73,     0,     0,     0,     0,    74,    75,    76,    77,
       0,    78,     0,    79,     0,     0,     0,     0,    80,    81,
      82,     0,    83,    84,     0,    85,     0,     0,    86,     0,
      87,    88,     0,     0,    89,    90,    91,    92,    93,    94,
      95,    96,    97,     0,    98,     0,    99,   100,   101,   102,
       0,   103,     0,   104,   105,   106,     0,     0,     0,   107,
     108,     0,     0,     0,   109,   110,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   111,     0,     0,     0,
       0,   112,   113,     0,     0,   114,     0,     0,     0,   115,
       0,   116,   117,     0,     0,     0,     0,     0,     0,   118,
     119,     0,   120,   121,   122,   123,   124,   125,   126
};

static const yytype_int16 yycheck[] =
{
       0,    79,    65,    66,    86,    33,     9,     6,   328,     7,
     253,    38,    16,     9,   363,    14,    16,     7,    35,    16,
     125,     2,    35,    35,    35,    35,   131,    35,    30,    97,
      35,    81,    68,    33,    34,   340,    29,   342,   343,   344,
     345,   346,   347,    35,   349,    35,    46,    35,    35,    35,
       9,     9,   134,    56,    97,    35,    56,   406,    97,     9,
      60,   145,    62,     0,     0,    35,     9,    89,    43,    91,
      70,   297,    47,   132,   706,   145,   396,    97,   145,    79,
     145,    56,   217,   403,   145,   145,   145,     9,   145,   104,
     145,   106,   145,    54,    31,    31,   145,    56,    56,    36,
      36,     9,   167,   168,    97,   105,    56,   230,   167,   168,
     140,    86,   112,    56,    68,   150,   465,   240,    93,   100,
     101,   102,    82,    97,    68,   106,    31,    35,    65,    65,
     145,   167,   168,   202,    56,   150,    97,    97,   299,   145,
     114,   225,    68,   212,   179,    97,    97,   122,    56,   217,
     125,   132,   133,   104,    97,   225,   131,    97,   225,   227,
      65,   226,   212,    56,   225,   225,   168,   226,   225,   208,
     225,   520,   225,   171,   144,   145,   225,   176,   527,   528,
     341,   171,   250,    56,   227,   178,   184,   217,   349,   187,
     226,   145,   150,   436,   184,   245,   213,   187,   208,   207,
     213,   213,   213,   208,   163,   167,   168,     9,   840,   435,
     225,    89,   561,    91,   236,   847,   208,    68,   217,   177,
     208,   208,   208,   219,   227,   162,   162,   177,   208,   167,
     168,    89,    90,    35,    85,   167,   168,   167,   168,   167,
     168,    92,   167,   168,   145,     9,    56,   274,   443,   444,
     445,   446,   447,   448,    56,    89,    90,    91,   262,   144,
     145,   259,   262,    56,   226,   262,    89,    90,    97,   259,
     145,    35,   437,   438,    56,   126,   145,   441,   442,   480,
     481,   527,   528,    56,    68,   145,   261,   145,   226,   145,
      35,   142,    56,    31,   226,    31,   226,    36,   226,    58,
     162,   226,     0,    97,    35,     7,   145,   145,   145,   160,
      12,    13,   145,   313,   145,   145,    93,   145,   667,   145,
     145,    13,     7,   155,   171,   407,   675,   676,   259,   101,
      35,   331,    69,   145,   683,    35,    35,   145,   313,    68,
      42,    43,    44,    68,   150,    36,    35,    35,    35,    35,
      68,    35,    35,    55,    35,    35,    68,   145,    35,    56,
     145,    68,   145,    97,    97,    67,   145,    68,    35,   674,
     690,    35,    35,    35,   145,    77,   145,   145,    80,    81,
      35,   730,   702,   703,    86,    35,    68,    35,   708,    35,
      35,    35,    35,   471,    35,   208,    35,    35,    35,    35,
     240,    97,    97,   208,   408,    35,    35,    35,   408,   213,
     145,   408,    35,   491,   492,   230,   208,    35,    97,    35,
     227,    35,    35,    97,    35,    35,    35,    35,    35,   429,
     208,    35,   134,   213,   208,    35,   541,    35,   208,    35,
      97,   208,   417,   418,   146,   420,   421,   208,   475,   554,
     555,   533,   208,   208,   208,   560,   208,    35,    35,   240,
      65,   489,    68,    97,    65,    35,   771,    35,   208,    35,
      97,   471,    97,   454,    35,    35,   208,   477,   208,    35,
      35,   208,    97,   458,   208,   489,   461,    68,   208,   489,
      35,   491,   492,   208,   494,    35,   198,   208,   200,   208,
     208,    35,   208,   213,   208,   208,   225,    35,   489,   490,
     150,    68,    35,    35,   208,   208,    54,   150,   150,   150,
      68,   145,    35,   213,   150,   145,   145,   609,   150,    35,
     208,    35,   208,   208,    35,   208,   517,   518,   519,   520,
     208,   522,   523,   524,   525,    35,   527,   528,   548,   251,
     208,   145,   208,   145,   208,   530,   208,   208,   145,   261,
     145,   639,   640,    35,   266,    35,   208,    35,   270,    35,
      35,    35,    35,   208,    35,    35,    35,    35,    35,    35,
     459,   440,   439,   449,   451,   450,   954,   208,   452,   736,
     453,   208,   817,   461,   575,   297,   298,    -1,    -1,   301,
      -1,    -1,    -1,    -1,   207,   307,   208,    -1,    -1,   208,
      -1,   313,    -1,   315,    -1,   208,    -1,   208,   208,   208,
     208,    -1,   208,    -1,   326,   208,    -1,    -1,   632,    -1,
     332,    -1,   632,    -1,    -1,   632,    -1,    -1,    -1,   639,
     640,    -1,    -1,    -1,    -1,   645,    -1,    -1,   648,   649,
     352,   632,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   365,   366,    -1,   368,    -1,    -1,   371,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   386,    -1,    -1,   668,   390,    -1,
      -1,    -1,   394,    -1,    -1,    -1,   398,   399,   400,   401,
      -1,    -1,    -1,    -1,    -1,   407,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   416,   417,   418,   419,   420,   421,
      -1,    -1,    -1,    -1,    -1,   427,    -1,    -1,   728,    -1,
      -1,    -1,    -1,   435,    -1,   735,   814,   815,   713,   743,
     744,   745,    -1,   743,   744,   745,   743,   744,   745,    -1,
      -1,    -1,   752,    -1,   456,    -1,   458,   459,   460,   461,
      -1,    -1,   743,   744,   745,   467,    -1,    -1,   470,    -1,
     472,   473,    -1,    -1,    -1,    -1,    -1,   479,   480,   481,
     482,   483,   484,    -1,    -1,    -1,   849,    -1,   769,    -1,
      -1,   772,    -1,    -1,   496,   497,    -1,    -1,   773,   774,
      -1,   503,    -1,   505,    -1,   507,   508,    -1,    -1,   511,
      -1,    -1,    -1,   515,   814,   815,    -1,    -1,    -1,   521,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   530,    -1,
     532,   533,   534,    -1,    -1,    -1,   538,   900,   540,    -1,
      -1,   543,   544,   545,   546,    -1,    -1,   828,    -1,   551,
     552,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   862,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   877,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   601,
      -1,    -1,    -1,    -1,    -1,   607,    -1,   609,    -1,   611,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   628,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   650,    -1,
     652,    -1,    -1,    -1,    -1,   657,    -1,   659,   660,    -1,
      -1,    -1,    -1,    -1,   964,    -1,    -1,    -1,    -1,    -1,
      -1,   971,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   681,
      -1,    -1,    -1,   685,    -1,   687,    -1,   689,    -1,   691,
      -1,    -1,    -1,    -1,    -1,    -1,   698,    -1,    -1,   701,
      -1,    -1,   704,   705,   706,   707,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   721,
     722,    -1,    -1,    -1,    -1,   727,    -1,    -1,    -1,   731,
      -1,   733,    -1,    -1,   736,   737,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     752,    -1,    -1,    -1,    -1,   757,    -1,   759,    -1,    -1,
      -1,   763,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   773,   774,    -1,   776,    -1,   778,    -1,   780,    -1,
      -1,   783,    -1,    -1,    -1,    -1,   788,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   801,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   820,    -1,
      -1,    -1,    -1,    -1,   826,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   840,    -1,
      -1,    -1,    -1,    -1,    -1,   847,    -1,    -1,    -1,   851,
      -1,    -1,   854,    -1,    -1,    -1,    -1,   859,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   867,    -1,    -1,    -1,    -1,
      -1,   873,    -1,    -1,    -1,    -1,    -1,   879,    -1,    -1,
      -1,    -1,   884,   885,    -1,    -1,   888,    -1,    -1,    -1,
      -1,    -1,   894,   895,    -1,    -1,   898,    -1,    -1,   901,
      -1,    -1,    -1,    -1,   906,   907,    -1,   909,    -1,    -1,
     912,    -1,    -1,   915,    -1,    -1,   918,   919,    -1,    -1,
     922,    -1,   924,   925,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   933,    -1,    -1,    -1,    -1,   938,   939,    -1,    -1,
      -1,    -1,   944,    -1,   946,    -1,    -1,     3,     4,   951,
      -1,    -1,     8,    -1,    10,    11,    -1,    -1,    -1,   961,
      -1,   963,    -1,    19,    -1,    -1,   968,    23,    24,    -1,
     972,    -1,    -1,    -1,   976,    -1,    -1,    -1,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    41,    42,    43,    44,    45,
      46,    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      56,    -1,    -1,    -1,    -1,    61,    62,    -1,    -1,    -1,
      -1,    67,    -1,    -1,    -1,    71,    72,    73,    -1,    75,
      -1,    -1,    -1,    79,    80,    81,    -1,    83,    84,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    94,    95,
      96,    97,    -1,    -1,    -1,    -1,   102,   103,    -1,   105,
      -1,   107,   108,    -1,    -1,    -1,   112,   113,    -1,   115,
     116,    -1,    -1,   119,   120,   121,   122,    -1,   124,   125,
      -1,   127,   128,    -1,    -1,    -1,    -1,    -1,    -1,   135,
      -1,   137,   138,   139,    -1,    -1,    -1,    -1,    -1,   145,
      -1,   147,    -1,   149,   150,    -1,   152,   153,   154,    -1,
      -1,    -1,   158,    -1,    -1,    -1,    -1,    -1,   164,   165,
     166,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   174,   175,
      -1,    -1,   178,   179,   180,    -1,    -1,   183,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   200,    -1,   202,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   211,    -1,    -1,    -1,    -1,
     216,    -1,   218,    -1,   220,    -1,   222,    -1,    -1,    -1,
     226,   227,   228,   229,    -1,    -1,    -1,    -1,   234,    -1,
      -1,    -1,    -1,   239,    -1,    -1,    -1,    -1,    -1,   245,
     246,   247,    -1,   249,     3,     4,     5,    -1,    -1,     8,
     256,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      19,    -1,    -1,    -1,    23,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,    -1,    -1,
      -1,    -1,    41,    42,    43,    44,    45,    46,    -1,    48,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,
      -1,    -1,    61,    62,    -1,    -1,    -1,    -1,    67,    -1,
      -1,    -1,    71,    72,    -1,    -1,    75,    -1,    -1,    -1,
      79,    80,    81,    -1,    83,    84,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    95,    96,    97,    -1,
      -1,    -1,    -1,   102,   103,    -1,   105,    -1,   107,   108,
      -1,    -1,    -1,   112,   113,    -1,   115,    -1,    -1,    -1,
     119,   120,   121,   122,    -1,   124,   125,    -1,   127,   128,
      -1,    -1,    -1,    -1,    -1,    -1,   135,    -1,   137,   138,
     139,    -1,    -1,    -1,    -1,    -1,   145,    -1,   147,    -1,
     149,   150,    -1,   152,   153,   154,    -1,    -1,    -1,   158,
      -1,    -1,    -1,    -1,    -1,   164,   165,   166,   167,   168,
      -1,    -1,    -1,    -1,    -1,   174,   175,    -1,    -1,    -1,
     179,   180,    -1,    -1,   183,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   200,    -1,   202,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   211,    -1,    -1,    -1,    -1,   216,   217,   218,
      -1,   220,    -1,   222,    -1,    -1,    -1,   226,   227,   228,
     229,    -1,    -1,    -1,    -1,   234,    -1,    -1,    -1,    -1,
     239,    -1,    -1,    -1,     3,     4,   245,   246,   247,     8,
     249,    10,    11,    -1,    -1,    -1,    -1,   256,    -1,    -1,
      19,    -1,    -1,    -1,    23,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,    -1,    -1,
      -1,    -1,    41,    42,    43,    44,    45,    46,    -1,    48,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,
      -1,    -1,    61,    62,    -1,    -1,    -1,    -1,    67,    -1,
      -1,    -1,    71,    72,    -1,    -1,    75,    -1,    -1,    -1,
      79,    80,    81,    -1,    83,    84,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    95,    96,    97,    -1,
      -1,    -1,    -1,   102,   103,    -1,   105,    -1,   107,   108,
      -1,    -1,    -1,   112,   113,    -1,   115,    -1,    -1,    -1,
     119,   120,   121,   122,    -1,   124,   125,    -1,   127,   128,
      -1,    -1,    -1,    -1,    -1,    -1,   135,    -1,   137,   138,
     139,    -1,    -1,    -1,    -1,    -1,   145,    -1,   147,    -1,
     149,   150,    -1,   152,   153,   154,    -1,    -1,    -1,   158,
      -1,    -1,    -1,    -1,    -1,   164,   165,   166,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   174,   175,    -1,    -1,    -1,
     179,   180,    -1,    -1,   183,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   200,    -1,   202,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   211,    -1,   213,    -1,    -1,   216,   217,   218,
      -1,   220,   221,   222,    -1,    -1,    -1,    -1,   227,   228,
     229,    -1,    -1,    -1,   233,   234,    -1,    -1,    -1,    -1,
     239,    -1,    -1,    -1,    -1,   244,   245,   246,   247,    -1,
     249,     3,     4,    -1,    -1,    -1,     8,   256,    10,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    19,    -1,    -1,
      -1,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    -1,    -1,    -1,    -1,    -1,    41,
      42,    43,    44,    45,    46,    -1,    48,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,    61,
      62,    -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,    71,
      72,    -1,    -1,    75,    -1,    -1,    -1,    79,    80,    81,
      -1,    83,    84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    95,    96,    97,    -1,    -1,    -1,    -1,
     102,   103,    -1,   105,    -1,   107,   108,    -1,    -1,    -1,
     112,   113,    -1,   115,    -1,    -1,    -1,   119,   120,   121,
     122,    -1,   124,   125,    -1,   127,   128,    -1,    -1,    -1,
      -1,    -1,    -1,   135,    -1,   137,   138,   139,    -1,    -1,
      -1,    -1,    -1,   145,    -1,   147,    -1,   149,   150,    -1,
     152,   153,   154,    -1,    -1,    -1,   158,    -1,    -1,    -1,
      -1,    -1,   164,   165,   166,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   174,   175,    -1,    -1,    -1,   179,   180,    -1,
      -1,   183,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   200,    -1,
     202,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   211,
      -1,   213,    -1,    -1,   216,    -1,   218,    -1,   220,   221,
     222,    -1,    -1,    -1,    -1,   227,   228,   229,    -1,    -1,
      -1,   233,   234,    -1,    -1,    -1,    -1,   239,    -1,    -1,
      -1,    -1,   244,   245,   246,   247,    -1,   249,     3,     4,
      -1,    -1,    -1,     8,   256,    10,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    19,    -1,    -1,    -1,    23,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    -1,    -1,    -1,    -1,    -1,    41,    42,    43,    44,
      45,    46,    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    56,    -1,    -1,    -1,    -1,    61,    62,    -1,    -1,
      -1,    -1,    67,    -1,    -1,    -1,    71,    72,    -1,    -1,
      75,    -1,    -1,    -1,    79,    80,    81,    -1,    83,    84,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      95,    96,    97,    -1,    -1,    -1,    -1,   102,   103,    -1,
     105,    -1,   107,   108,    -1,    -1,    -1,   112,   113,    -1,
     115,    -1,    -1,    -1,   119,   120,   121,   122,    -1,   124,
     125,    -1,   127,   128,    -1,    -1,    -1,    -1,    -1,    -1,
     135,    -1,   137,   138,   139,    -1,    -1,    -1,    -1,    -1,
     145,    -1,   147,    -1,   149,   150,    -1,   152,   153,   154,
      -1,    -1,    -1,   158,    -1,    -1,    -1,    -1,    -1,   164,
     165,   166,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   174,
     175,    -1,    -1,    -1,   179,   180,    -1,    -1,   183,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   200,    -1,   202,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   211,    -1,   213,    -1,
      -1,   216,   217,   218,    -1,   220,   221,   222,    -1,    -1,
      -1,    -1,   227,   228,   229,    -1,    -1,    -1,   233,   234,
      -1,    -1,    -1,    -1,   239,    -1,    -1,    -1,     3,     4,
     245,   246,   247,     8,   249,    10,    11,    -1,    -1,    -1,
      -1,   256,    -1,    -1,    19,    -1,    -1,    -1,    23,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    44,
      45,    46,    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    56,    -1,    -1,    -1,    -1,    61,    62,    -1,    -1,
      -1,    -1,    67,    -1,    -1,    -1,    71,    72,    -1,    -1,
      75,    -1,    -1,    -1,    79,    80,    81,    -1,    83,    84,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      95,    96,    97,    -1,    -1,    -1,    -1,   102,   103,    -1,
     105,    -1,   107,   108,    -1,    -1,    -1,   112,   113,    -1,
     115,    -1,    -1,    -1,   119,   120,   121,   122,    -1,   124,
     125,    -1,   127,   128,    -1,    -1,    -1,    -1,    -1,    -1,
     135,    -1,   137,   138,   139,    -1,    -1,    -1,    -1,    -1,
     145,    -1,   147,    -1,   149,   150,    -1,   152,   153,   154,
      -1,    -1,    -1,   158,    -1,    -1,    -1,    -1,    -1,   164,
     165,   166,   167,   168,    -1,    -1,    -1,    -1,    -1,   174,
     175,    -1,    -1,    -1,   179,   180,    -1,    -1,   183,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   200,    -1,   202,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   211,    -1,    -1,    -1,
      -1,   216,   217,   218,    -1,   220,    -1,   222,    -1,    -1,
      -1,    -1,   227,   228,   229,    -1,    -1,    -1,    -1,   234,
      -1,    -1,    -1,    -1,   239,    -1,    -1,    -1,     3,     4,
     245,   246,   247,     8,   249,    10,    11,    -1,    -1,    -1,
      -1,   256,    -1,    -1,    19,    -1,    -1,    -1,    23,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    -1,    -1,    -1,    -1,    -1,    41,    42,    43,    44,
      45,    46,    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    56,    -1,    -1,    -1,    -1,    61,    62,    -1,    -1,
      -1,    -1,    67,    -1,    -1,    -1,    71,    72,    -1,    -1,
      75,    -1,    -1,    -1,    79,    80,    81,    -1,    83,    84,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      95,    96,    97,    -1,    -1,    -1,    -1,   102,   103,    -1,
     105,    -1,   107,   108,    -1,    -1,    -1,   112,   113,    -1,
     115,    -1,    -1,    -1,   119,   120,   121,   122,    -1,   124,
     125,    -1,   127,   128,    -1,    -1,    -1,    -1,    -1,    -1,
     135,    -1,   137,   138,   139,    -1,    -1,    -1,    -1,   144,
     145,    -1,   147,    -1,   149,   150,    -1,   152,   153,   154,
      -1,    -1,    -1,   158,    -1,    -1,    -1,    -1,    -1,   164,
     165,   166,   167,   168,    -1,    -1,    -1,    -1,    -1,   174,
     175,    -1,    -1,    -1,   179,   180,    -1,    -1,   183,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   200,    -1,   202,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   211,    -1,    -1,    -1,
      -1,   216,   217,   218,    -1,   220,    -1,   222,    -1,    -1,
      -1,    -1,   227,   228,   229,    -1,    -1,    -1,    -1,   234,
      -1,    -1,    -1,    -1,   239,    -1,    -1,    -1,     3,     4,
     245,   246,   247,     8,   249,    10,    11,    -1,    -1,    -1,
      -1,   256,    -1,    -1,    19,    -1,    -1,    -1,    23,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    -1,    -1,    -1,    -1,    -1,    41,    42,    43,    44,
      45,    46,    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    56,    -1,    -1,    -1,    -1,    61,    62,    -1,    -1,
      -1,    -1,    67,    -1,    -1,    -1,    71,    72,    -1,    -1,
      75,    -1,    -1,    -1,    79,    80,    81,    -1,    83,    84,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      95,    96,    97,    -1,    -1,    -1,    -1,   102,   103,    -1,
     105,    -1,   107,   108,    -1,    -1,    -1,   112,   113,    -1,
     115,    -1,    -1,    -1,   119,   120,   121,   122,    -1,   124,
     125,    -1,   127,   128,    -1,    -1,    -1,    -1,    -1,    -1,
     135,    -1,   137,   138,   139,    -1,    -1,    -1,    -1,    -1,
     145,    -1,   147,    -1,   149,   150,    -1,   152,   153,   154,
      -1,    -1,    -1,   158,    -1,    -1,    -1,    -1,    -1,   164,
     165,   166,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   174,
     175,    -1,    -1,    -1,   179,   180,    -1,    -1,   183,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   200,    -1,   202,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   211,    -1,   213,    -1,
      -1,   216,    -1,   218,    -1,   220,   221,   222,    -1,    -1,
      -1,    -1,   227,   228,   229,    -1,    -1,    -1,   233,   234,
      -1,    -1,    -1,    -1,   239,    -1,    -1,    -1,    -1,   244,
     245,   246,   247,    -1,   249,     3,     4,    -1,    -1,    -1,
       8,   256,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    19,    -1,    -1,    -1,    23,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,    -1,
      -1,    -1,    -1,    41,    42,    43,    44,    45,    46,    -1,
      48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    -1,
      -1,    -1,    -1,    61,    62,    -1,    -1,    -1,    -1,    67,
      -1,    -1,    -1,    71,    72,    -1,    -1,    75,    -1,    -1,
      -1,    79,    80,    81,    -1,    83,    84,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    95,    96,    97,
      -1,    -1,    -1,    -1,   102,   103,    -1,   105,    -1,   107,
     108,    -1,    -1,    -1,   112,   113,    -1,   115,    -1,    -1,
      -1,   119,   120,   121,   122,    -1,   124,   125,    -1,   127,
     128,    -1,    -1,    -1,    -1,    -1,    -1,   135,    -1,   137,
     138,   139,    -1,    -1,    -1,    -1,    -1,   145,    -1,   147,
      -1,   149,   150,    -1,   152,   153,   154,    -1,    -1,    -1,
     158,    -1,    -1,    -1,    -1,    -1,   164,   165,   166,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   174,   175,    -1,    -1,
      -1,   179,   180,    -1,    -1,   183,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   200,    -1,   202,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   211,    -1,   213,    -1,    -1,   216,    -1,
     218,    -1,   220,   221,   222,    -1,    -1,    -1,    -1,   227,
     228,   229,    -1,    -1,    -1,   233,   234,    -1,    -1,    -1,
      -1,   239,    -1,    -1,    -1,    -1,   244,   245,   246,   247,
      -1,   249,     3,     4,    -1,    -1,    -1,     8,   256,    10,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    19,    -1,
      -1,    -1,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    -1,    -1,    -1,    -1,    -1,
      41,    42,    43,    44,    45,    46,    -1,    48,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,
      61,    62,    -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,
      71,    72,    -1,    -1,    75,    -1,    -1,    -1,    79,    80,
      81,    -1,    83,    84,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    95,    96,    97,    -1,    -1,    -1,
      -1,   102,   103,    -1,   105,    -1,   107,   108,    -1,    -1,
      -1,   112,   113,    -1,   115,    -1,    -1,    -1,   119,   120,
     121,   122,    -1,   124,   125,    -1,   127,   128,    -1,    -1,
      -1,    -1,    -1,    -1,   135,    -1,   137,   138,   139,    -1,
      -1,    -1,    -1,    -1,   145,    -1,   147,    -1,   149,   150,
      -1,   152,   153,   154,    -1,    -1,    -1,   158,    -1,    -1,
      -1,    -1,    -1,   164,   165,   166,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   174,   175,    -1,    -1,    -1,   179,   180,
      -1,    -1,   183,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   200,
      -1,   202,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     211,    -1,   213,    -1,    -1,   216,    -1,   218,    -1,   220,
     221,   222,    -1,    -1,    -1,    -1,   227,   228,   229,    -1,
      -1,    -1,   233,   234,    -1,    -1,    -1,    -1,   239,    -1,
      -1,    -1,     3,     4,   245,   246,   247,     8,   249,    10,
      11,    -1,    -1,    -1,    -1,   256,    -1,    -1,    19,    -1,
      -1,    -1,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      41,    42,    43,    44,    45,    46,    -1,    48,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,
      61,    62,    -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,
      71,    72,    -1,    -1,    75,    -1,    -1,    -1,    79,    80,
      81,    -1,    83,    84,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    95,    96,    97,    -1,    -1,    -1,
      -1,   102,   103,    -1,   105,    -1,   107,   108,    -1,    -1,
      -1,   112,   113,    -1,   115,    -1,    -1,    -1,   119,   120,
     121,   122,    -1,   124,   125,    -1,   127,   128,    -1,    -1,
      -1,    -1,    -1,    -1,   135,    -1,   137,   138,   139,    -1,
      -1,    -1,    -1,    -1,   145,    -1,   147,    -1,   149,   150,
      -1,   152,   153,   154,    -1,    -1,    -1,   158,    -1,    -1,
      -1,    -1,    -1,   164,   165,   166,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   174,   175,    -1,    -1,    -1,   179,   180,
      -1,    -1,   183,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   200,
      -1,   202,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     211,    -1,    -1,    -1,    -1,   216,   217,   218,    -1,   220,
      -1,   222,    -1,    -1,    -1,    -1,   227,   228,   229,    -1,
      -1,    -1,    -1,   234,    -1,    -1,    -1,    -1,   239,    -1,
      -1,    -1,    -1,    -1,   245,   246,   247,    -1,   249,   250,
      -1,     3,     4,    -1,    -1,   256,     8,    -1,    10,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    19,    -1,    -1,
      -1,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    -1,    -1,    -1,    -1,    -1,    41,
      42,    43,    44,    45,    46,    -1,    48,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,    61,
      62,    -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,    71,
      72,    -1,    -1,    75,    -1,    -1,    -1,    79,    80,    81,
      -1,    83,    84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    95,    96,    97,    -1,    -1,    -1,    -1,
     102,   103,    -1,   105,    -1,   107,   108,    -1,    -1,    -1,
     112,   113,    -1,   115,    -1,    -1,    -1,   119,   120,   121,
     122,    -1,   124,   125,    -1,   127,   128,    -1,    -1,    -1,
      -1,    -1,    -1,   135,    -1,   137,   138,   139,    -1,    -1,
      -1,    -1,    -1,   145,    -1,   147,    -1,   149,   150,    -1,
     152,   153,   154,    -1,    -1,    -1,   158,    -1,    -1,    -1,
      -1,    -1,   164,   165,   166,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   174,   175,    -1,    -1,    -1,   179,   180,    -1,
      -1,   183,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   200,    -1,
     202,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   211,
      -1,   213,    -1,    -1,   216,    -1,   218,    -1,   220,    -1,
     222,    -1,    -1,    -1,    -1,   227,   228,   229,    -1,    -1,
      -1,    -1,   234,    -1,    -1,    -1,    -1,   239,    -1,    -1,
      -1,     3,     4,   245,   246,   247,     8,   249,    10,    11,
      -1,    -1,    -1,    -1,   256,    -1,    -1,    19,    -1,    -1,
      -1,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,
      42,    43,    44,    45,    46,    -1,    48,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,    61,
      62,    -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,    71,
      72,    -1,    -1,    75,    -1,    -1,    -1,    79,    80,    81,
      -1,    83,    84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    95,    96,    97,    -1,    -1,    -1,    -1,
     102,   103,    -1,   105,    -1,   107,   108,    -1,    -1,    -1,
     112,   113,    -1,   115,    -1,    -1,    -1,   119,   120,   121,
     122,    -1,   124,   125,    -1,   127,   128,    -1,    -1,    -1,
      -1,    -1,    -1,   135,    -1,   137,   138,   139,    -1,    -1,
      -1,    -1,    -1,   145,    -1,   147,   148,   149,   150,    -1,
     152,   153,   154,    -1,    -1,    -1,   158,    -1,    -1,    -1,
      -1,    -1,   164,   165,   166,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   174,   175,    -1,    -1,    -1,   179,   180,    -1,
      -1,   183,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   200,    -1,
     202,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   211,
      -1,    -1,    -1,    -1,   216,    -1,   218,    -1,   220,    -1,
     222,    -1,    -1,    -1,    -1,   227,   228,   229,    -1,    -1,
      -1,    -1,   234,    -1,    -1,    -1,    -1,   239,    -1,    -1,
      -1,     3,     4,   245,   246,   247,     8,   249,    10,    11,
      -1,    -1,    -1,    -1,   256,    -1,    -1,    19,    -1,    -1,
      -1,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,
      42,    43,    44,    45,    46,    -1,    48,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,    61,
      62,    -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,    71,
      72,    -1,    -1,    75,    -1,    -1,    -1,    79,    80,    81,
      -1,    83,    84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    95,    96,    97,    -1,    -1,    -1,    -1,
     102,   103,    -1,   105,    -1,   107,   108,    -1,    -1,    -1,
     112,   113,    -1,   115,    -1,    -1,    -1,   119,   120,   121,
     122,    -1,   124,   125,    -1,   127,   128,    -1,    -1,    -1,
      -1,    -1,    -1,   135,    -1,   137,   138,   139,    -1,    -1,
      -1,    -1,    -1,   145,    -1,   147,    -1,   149,   150,    -1,
     152,   153,   154,    -1,    -1,    -1,   158,    -1,    -1,    -1,
      -1,    -1,   164,   165,   166,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   174,   175,    -1,    -1,    -1,   179,   180,    -1,
      -1,   183,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   200,    -1,
     202,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   211,
      -1,    -1,    -1,    -1,   216,   217,   218,    -1,   220,    -1,
     222,    -1,    -1,    -1,    -1,   227,   228,   229,    -1,    -1,
      -1,    -1,   234,    -1,    -1,    -1,    -1,   239,    -1,    -1,
      -1,     3,     4,   245,   246,   247,     8,   249,    10,    11,
      -1,    -1,    -1,    -1,   256,    -1,    -1,    19,    -1,    -1,
      -1,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,
      42,    43,    44,    45,    46,    -1,    48,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,    61,
      62,    -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,    71,
      72,    -1,    -1,    75,    -1,    -1,    -1,    79,    80,    81,
      -1,    83,    84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    95,    96,    97,    -1,    -1,    -1,    -1,
     102,   103,    -1,   105,    -1,   107,   108,    -1,    -1,    -1,
     112,   113,    -1,   115,    -1,    -1,    -1,   119,   120,   121,
     122,    -1,   124,   125,    -1,   127,   128,    -1,    -1,    -1,
      -1,    -1,    -1,   135,    -1,   137,   138,   139,    -1,    -1,
      -1,    -1,    -1,   145,    -1,   147,    -1,   149,   150,    -1,
     152,   153,   154,    -1,    -1,    -1,   158,    -1,    -1,    -1,
      -1,    -1,   164,   165,   166,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   174,   175,    -1,    -1,    -1,   179,   180,    -1,
      -1,   183,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   191,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   200,    -1,
     202,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   211,
      -1,    -1,    -1,    -1,   216,    -1,   218,    -1,   220,    -1,
     222,    -1,    -1,    -1,    -1,   227,   228,   229,    -1,    -1,
      -1,    -1,   234,    -1,    -1,    -1,    -1,   239,    -1,    -1,
      -1,     3,     4,   245,   246,   247,     8,   249,    10,    11,
      -1,    -1,    -1,    -1,   256,    -1,    -1,    19,    -1,    -1,
      -1,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    -1,    -1,    -1,    -1,    -1,    41,
      42,    43,    44,    45,    46,    -1,    48,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,    61,
      62,    -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,    71,
      72,    -1,    -1,    75,    -1,    -1,    -1,    79,    80,    81,
      -1,    83,    84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    95,    96,    97,    -1,    -1,    -1,    -1,
     102,   103,    -1,   105,    -1,   107,   108,    -1,    -1,    -1,
     112,   113,    -1,   115,    -1,    -1,    -1,   119,   120,   121,
     122,    -1,   124,   125,    -1,   127,   128,    -1,    -1,    -1,
      -1,    -1,    -1,   135,    -1,   137,   138,   139,    -1,    -1,
      -1,    -1,    -1,   145,    -1,   147,    -1,   149,   150,    -1,
     152,   153,   154,    -1,    -1,    -1,   158,    -1,    -1,    -1,
      -1,    -1,   164,   165,   166,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   174,   175,    -1,    -1,    -1,   179,   180,    -1,
      -1,   183,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   200,    -1,
     202,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   211,
      -1,    -1,    -1,    -1,   216,    -1,   218,    -1,   220,    -1,
     222,    -1,    -1,    -1,    -1,   227,   228,   229,    -1,    -1,
      -1,    -1,   234,    -1,    -1,    -1,    -1,   239,    -1,    -1,
      -1,     3,     4,   245,   246,   247,     8,   249,    10,    11,
      -1,    -1,    -1,    -1,   256,    -1,    -1,    19,    -1,    -1,
      -1,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    -1,    -1,    -1,    -1,    -1,    41,
      42,    43,    44,    45,    46,    -1,    48,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,    61,
      62,    -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,    71,
      72,    -1,    -1,    75,    -1,    -1,    -1,    79,    80,    81,
      -1,    83,    84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    95,    96,    97,    -1,    -1,    -1,    -1,
     102,   103,    -1,   105,    -1,   107,   108,    -1,    -1,    -1,
     112,   113,    -1,   115,    -1,    -1,    -1,   119,   120,   121,
     122,    -1,   124,   125,    -1,   127,   128,    -1,    -1,    -1,
      -1,    -1,    -1,   135,    -1,   137,   138,   139,    -1,    -1,
      -1,    -1,    -1,   145,    -1,   147,    -1,   149,   150,    -1,
     152,   153,   154,    -1,    -1,    -1,   158,    -1,    -1,    -1,
      -1,    -1,   164,   165,   166,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   174,   175,    -1,    -1,    -1,   179,   180,    -1,
      -1,   183,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   200,    -1,
     202,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   211,
      -1,    -1,    -1,    -1,   216,    -1,   218,    -1,   220,    -1,
     222,    -1,    -1,    -1,    -1,   227,   228,   229,    -1,    -1,
      -1,    -1,   234,    -1,    -1,    -1,    -1,   239,    -1,    -1,
      -1,     3,     4,   245,   246,   247,     8,   249,    10,    11,
      -1,    -1,    -1,    -1,   256,    -1,    -1,    19,    -1,    -1,
      -1,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,
      42,    43,    44,    45,    46,    -1,    48,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,    61,
      62,    -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,    71,
      72,    -1,    -1,    75,    -1,    -1,    -1,    79,    80,    81,
      -1,    83,    84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    95,    96,    97,    -1,    -1,    -1,    -1,
     102,   103,    -1,   105,    -1,   107,   108,    -1,    -1,    -1,
     112,   113,    -1,   115,    -1,    -1,    -1,   119,   120,   121,
     122,    -1,   124,   125,    -1,   127,   128,    -1,    -1,    -1,
      -1,    -1,    -1,   135,    -1,   137,   138,   139,    -1,    -1,
      -1,    -1,    -1,   145,    -1,   147,    -1,   149,   150,    -1,
     152,   153,   154,    -1,    -1,    -1,   158,    -1,    -1,    -1,
      -1,    -1,   164,   165,   166,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   174,   175,    -1,    -1,    -1,   179,   180,    -1,
      -1,   183,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   200,    -1,
     202,    -1,    -1,    -1,    -1,    -1,   208,    -1,    -1,   211,
      -1,    -1,    -1,    -1,   216,    -1,   218,    -1,   220,    -1,
     222,    -1,    -1,    -1,    -1,   227,   228,   229,    -1,    -1,
      -1,    -1,   234,    -1,    -1,    -1,    -1,   239,    -1,    -1,
      -1,     3,     4,   245,   246,   247,     8,   249,    10,    11,
      -1,    -1,    -1,    -1,   256,    -1,    -1,    19,    -1,    -1,
      -1,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,
      42,    43,    44,    45,    46,    -1,    48,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,    61,
      62,    -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,    71,
      72,    -1,    -1,    75,    -1,    -1,    -1,    79,    80,    81,
      -1,    83,    84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    95,    96,    97,    -1,    -1,    -1,    -1,
     102,   103,    -1,   105,    -1,   107,   108,    -1,    -1,    -1,
     112,   113,    -1,   115,    -1,    -1,    -1,   119,   120,   121,
     122,    -1,   124,   125,    -1,   127,   128,    -1,    -1,    -1,
      -1,    -1,    -1,   135,    -1,   137,   138,   139,    -1,    -1,
      -1,    -1,    -1,   145,    -1,   147,    -1,   149,   150,    -1,
     152,   153,   154,    -1,    -1,    -1,   158,    -1,    -1,    -1,
      -1,    -1,   164,   165,   166,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   174,   175,    -1,    -1,    -1,   179,   180,    -1,
      -1,   183,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   200,    -1,
     202,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   211,
      -1,    -1,    -1,    -1,   216,    -1,   218,    -1,   220,    -1,
     222,    -1,    -1,    -1,    -1,   227,   228,   229,    -1,    -1,
      -1,    -1,   234,    -1,    -1,    -1,    -1,   239,    -1,    -1,
      -1,     3,     4,   245,   246,   247,     8,   249,    10,    11,
      -1,    -1,    -1,    -1,   256,    -1,    -1,    19,    -1,    -1,
      -1,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,
      42,    43,    44,    45,    46,    -1,    48,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,    61,
      62,    -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,    71,
      72,    -1,    -1,    75,    -1,    -1,    -1,    79,    80,    81,
      -1,    83,    84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    95,    96,    97,    -1,    -1,    -1,    -1,
     102,   103,    -1,   105,    -1,   107,   108,    -1,    -1,    -1,
     112,   113,    -1,   115,    -1,    -1,    -1,   119,   120,   121,
     122,    -1,   124,   125,    -1,   127,   128,    -1,    -1,    -1,
      -1,    -1,    -1,   135,    -1,   137,   138,   139,    -1,    -1,
      -1,    -1,    -1,   145,    -1,   147,    -1,   149,   150,    -1,
     152,   153,   154,    -1,    -1,    -1,   158,    -1,    -1,    -1,
      -1,    -1,    -1,   165,   166,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   174,   175,    -1,    -1,    -1,   179,   180,    -1,
      -1,   183,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   200,    -1,
     202,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   211,
      -1,    -1,    -1,    -1,   216,    -1,   218,    -1,   220,    -1,
     222,    -1,    -1,    -1,    -1,   227,   228,   229,    -1,    -1,
      -1,    -1,   234,    -1,    -1,    -1,    -1,   239,    -1,    -1,
      -1,     3,     4,   245,   246,   247,     8,   249,    10,    11,
      -1,    -1,    -1,    -1,   256,    -1,    -1,    19,    -1,    -1,
      -1,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,
      42,    43,    44,    45,    46,    -1,    48,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,    61,
      62,    -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,    71,
      72,    -1,    -1,    75,    -1,    -1,    -1,    79,    80,    81,
      -1,    83,    84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    95,    96,    97,    -1,    -1,    -1,    -1,
     102,   103,    -1,   105,    -1,   107,   108,    -1,    -1,    -1,
     112,   113,    -1,   115,    -1,    -1,    -1,   119,   120,   121,
     122,    -1,   124,   125,    -1,   127,   128,    -1,    -1,    -1,
      -1,    -1,    -1,   135,    -1,   137,   138,   139,    -1,    -1,
      -1,    -1,    -1,   145,    -1,   147,    -1,   149,    -1,    -1,
     152,   153,   154,    -1,    -1,    -1,   158,    -1,    -1,    -1,
      -1,    -1,    -1,   165,   166,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   174,   175,    -1,    -1,    -1,    -1,   180,    -1,
      -1,   183,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   200,    -1,
     202,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   211,
      -1,    -1,    -1,    -1,   216,    -1,   218,    -1,   220,    -1,
     222,    -1,    -1,    -1,    -1,   227,   228,   229,    -1,    -1,
      -1,    -1,   234,    -1,    -1,    -1,    -1,   239,    -1,    -1,
      -1,    -1,    -1,   245,   246,   247,    -1,   249,    -1,     9,
      -1,    -1,    12,    -1,   256,    15,    16,    17,    18,    -1,
      20,    21,    22,    -1,    -1,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    -1,    36,    37,    38,    39,
      40,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    49,
      50,    51,    52,    53,    54,    -1,    56,    57,    58,    -1,
      60,    -1,    -1,    63,    64,    -1,    66,    -1,    -1,    -1,
      70,    -1,    -1,    73,    74,    -1,    76,    77,    78,    -1,
      -1,    -1,    82,    -1,    -1,    -1,    86,    87,    88,    89,
      90,    91,    -1,    -1,    94,    -1,    -1,    97,    -1,    99,
      -1,    -1,    -1,    -1,   104,    -1,   106,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   116,   117,   118,    -1,
      -1,    -1,    -1,   123,    -1,    -1,    -1,    -1,    -1,   129,
     130,   131,   132,   133,   134,    -1,   136,    -1,    -1,    -1,
     140,   141,    -1,    -1,    -1,    -1,    -1,    -1,   148,   149,
      -1,   151,    -1,    -1,    -1,    -1,   156,   157,   158,   159,
      -1,   161,    -1,   163,    -1,    -1,    -1,    -1,   168,   169,
     170,    -1,   172,   173,    -1,   175,    -1,    -1,   178,    -1,
     180,   181,    -1,    -1,   184,   185,   186,   187,   188,   189,
     190,   191,   192,    -1,   194,    -1,   196,   197,   198,   199,
      -1,   201,    -1,   203,   204,   205,    -1,    -1,    -1,   209,
     210,    -1,    -1,    -1,   214,   215,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   226,    -1,    -1,    -1,
      -1,   231,   232,    -1,    -1,   235,    -1,    -1,    -1,   239,
      -1,   241,   242,    -1,    -1,    -1,    -1,    -1,    -1,   249,
     250,    -1,   252,   253,   254,   255,   256,   257,   258,     9,
      -1,    -1,    12,    -1,    -1,    15,    16,    17,    18,    -1,
      20,    21,    22,    -1,    -1,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    -1,    36,    37,    38,    39,
      40,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    49,
      50,    51,    52,    53,    54,    -1,    56,    57,    58,    -1,
      60,    -1,    -1,    63,    64,    65,    66,    -1,    -1,    -1,
      70,    -1,    -1,    73,    -1,    -1,    76,    77,    78,    -1,
      -1,    -1,    82,    -1,    -1,    -1,    86,    87,    88,    89,
      90,    91,    -1,    -1,    94,    -1,    -1,    97,    -1,    99,
      -1,    -1,    -1,    -1,   104,    -1,   106,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   116,   117,   118,    -1,
      -1,    -1,    -1,   123,    -1,    -1,    -1,    -1,    -1,   129,
     130,   131,   132,   133,   134,    -1,   136,    -1,    -1,    -1,
     140,   141,    -1,    -1,    -1,    -1,    -1,    -1,   148,   149,
      -1,   151,    -1,    -1,    -1,    -1,   156,   157,   158,   159,
      -1,   161,    -1,   163,    -1,    -1,    -1,    -1,   168,   169,
     170,    -1,   172,   173,    -1,   175,    -1,    -1,   178,    -1,
     180,   181,    -1,    -1,   184,   185,   186,   187,   188,   189,
     190,   191,   192,    -1,   194,    -1,   196,   197,   198,   199,
      -1,   201,    -1,   203,   204,   205,    -1,    -1,    -1,   209,
     210,    -1,    -1,    -1,   214,   215,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   226,    -1,    -1,    -1,
      -1,   231,   232,    -1,    -1,   235,    -1,    -1,    -1,   239,
      -1,   241,   242,    -1,    -1,    -1,    -1,    -1,    -1,   249,
     250,    -1,   252,   253,   254,   255,   256,   257,   258,     9,
      -1,    -1,    12,    -1,    -1,    15,    16,    17,    18,    -1,
      20,    21,    22,    -1,    -1,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    -1,    36,    37,    38,    39,
      40,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    49,
      50,    51,    52,    53,    54,    -1,    56,    57,    58,    -1,
      60,    -1,    -1,    63,    64,    -1,    66,    -1,    -1,    -1,
      70,    -1,    -1,    73,    -1,    -1,    76,    77,    78,    -1,
      -1,    -1,    82,    -1,    -1,    -1,    86,    87,    88,    89,
      90,    91,    -1,    -1,    94,    -1,    -1,    97,    -1,    99,
      -1,    -1,    -1,    -1,   104,    -1,   106,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   116,   117,   118,    -1,
      -1,    -1,    -1,   123,    -1,    -1,    -1,    -1,    -1,   129,
     130,   131,   132,   133,   134,    -1,   136,    -1,    -1,    -1,
     140,   141,    -1,    -1,    -1,    -1,    -1,    -1,   148,   149,
      -1,   151,    -1,    -1,    -1,    -1,   156,   157,   158,   159,
      -1,   161,    -1,   163,    -1,    -1,    -1,    -1,   168,   169,
     170,    -1,   172,   173,    -1,   175,    -1,    -1,   178,    -1,
     180,   181,    -1,    -1,   184,   185,   186,   187,   188,   189,
     190,   191,   192,    -1,   194,    -1,   196,   197,   198,   199,
      -1,   201,    -1,   203,   204,   205,    -1,    -1,    -1,   209,
     210,    -1,    -1,    -1,   214,   215,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   226,    -1,    -1,    -1,
      -1,   231,   232,    -1,    -1,   235,    -1,    -1,    -1,   239,
      -1,   241,   242,    -1,    -1,    -1,    -1,    -1,    -1,   249,
     250,    -1,   252,   253,   254,   255,   256,   257,   258,     9,
      -1,    -1,    12,    -1,    -1,    15,    16,    17,    18,    -1,
      20,    21,    22,    -1,    -1,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    -1,    36,    37,    38,    39,
      40,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    49,
      50,    51,    52,    53,    54,    -1,    -1,    57,    58,    -1,
      60,    -1,    -1,    63,    64,    -1,    66,    -1,    -1,    -1,
      70,    -1,    -1,    73,    -1,    -1,    76,    77,    78,    -1,
      -1,    -1,    82,    -1,    -1,    -1,    86,    87,    88,    89,
      90,    91,    -1,    -1,    94,    -1,    -1,    97,    -1,    99,
      -1,    -1,    -1,    -1,   104,    -1,   106,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   116,   117,   118,    -1,
      -1,    -1,    -1,   123,    -1,    -1,    -1,    -1,    -1,   129,
     130,   131,   132,   133,   134,    -1,   136,    -1,    -1,    -1,
     140,   141,    -1,    -1,    -1,    -1,    -1,    -1,   148,   149,
      -1,   151,    -1,    -1,    -1,    -1,   156,   157,   158,   159,
      -1,   161,    -1,   163,    -1,    -1,    -1,    -1,   168,   169,
     170,    -1,   172,   173,    -1,   175,    -1,    -1,   178,    -1,
     180,   181,    -1,    -1,   184,   185,   186,   187,   188,   189,
     190,   191,   192,    -1,   194,    -1,   196,   197,   198,   199,
      -1,   201,    -1,   203,   204,   205,    -1,    -1,    -1,   209,
     210,    -1,    -1,    -1,   214,   215,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   226,    -1,    -1,    -1,
      -1,   231,   232,    -1,    -1,   235,    -1,    -1,    -1,   239,
      -1,   241,   242,    -1,    -1,    -1,    -1,    -1,    -1,   249,
     250,    -1,   252,   253,   254,   255,   256,   257,   258,     9,
      -1,    -1,    12,    -1,    -1,    15,    16,    17,    18,    -1,
      20,    21,    22,    -1,    -1,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    -1,    36,    37,    38,    39,
      40,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    49,
      50,    51,    52,    53,    54,    -1,    -1,    57,    58,    -1,
      60,    -1,    -1,    63,    64,    -1,    66,    -1,    -1,    -1,
      70,    -1,    -1,    73,    -1,    -1,    76,    77,    78,    -1,
      -1,    -1,    82,    -1,    -1,    -1,    86,    87,    88,    89,
      90,    91,    -1,    -1,    94,    -1,    -1,    97,    -1,    99,
      -1,    -1,    -1,    -1,   104,    -1,   106,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   116,   117,   118,    -1,
      -1,    -1,    -1,   123,    -1,    -1,    -1,    -1,    -1,   129,
     130,   131,   132,   133,   134,    -1,   136,    -1,    -1,    -1,
     140,   141,    -1,    -1,    -1,    -1,    -1,    -1,   148,   149,
      -1,   151,    -1,    -1,    -1,    -1,   156,   157,   158,   159,
      -1,   161,    -1,   163,    -1,    -1,    -1,    -1,   168,   169,
     170,    -1,   172,   173,    -1,   175,    -1,    -1,   178,    -1,
     180,   181,    -1,    -1,   184,   185,   186,   187,   188,   189,
     190,   191,   192,    -1,   194,    -1,   196,   197,   198,   199,
      -1,   201,    -1,   203,   204,   205,    -1,    -1,    -1,   209,
     210,    -1,    -1,    -1,   214,   215,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   226,    -1,    -1,    -1,
      -1,   231,   232,    -1,    -1,   235,    -1,    -1,    -1,   239,
      -1,   241,   242,    -1,    -1,    -1,    -1,    -1,    -1,   249,
     250,    -1,   252,   253,   254,   255,   256,   257,   258
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int16 yystos[] =
{
       0,     9,    12,    15,    16,    17,    18,    20,    21,    22,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      36,    37,    38,    39,    40,    47,    48,    49,    50,    51,
      52,    53,    54,    56,    57,    58,    60,    63,    64,    66,
      70,    73,    74,    76,    77,    78,    82,    86,    87,    88,
      89,    90,    91,    94,    97,    99,   104,   106,   116,   117,
     118,   123,   129,   130,   131,   132,   133,   134,   136,   140,
     141,   148,   149,   151,   156,   157,   158,   159,   161,   163,
     168,   169,   170,   172,   173,   175,   178,   180,   181,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   194,   196,
     197,   198,   199,   201,   203,   204,   205,   209,   210,   214,
     215,   226,   231,   232,   235,   239,   241,   242,   249,   250,
     252,   253,   254,   255,   256,   257,   258,   263,   288,   289,
     292,   295,   298,   299,   302,   303,   304,   305,   306,   307,
     308,   313,   316,   317,    97,     9,    35,    56,   265,     3,
       4,     8,    10,    11,    19,    23,    24,    41,    42,    43,
      44,    45,    46,    48,    56,    61,    62,    67,    71,    72,
      75,    79,    80,    81,    83,    84,    95,    96,   102,   103,
     105,   107,   108,   112,   113,   115,   119,   120,   121,   122,
     124,   125,   127,   128,   135,   137,   138,   139,   145,   147,
     148,   149,   150,   152,   153,   154,   158,   164,   165,   166,
     174,   175,   179,   180,   183,   200,   202,   211,   216,   218,
     220,   222,   227,   228,   229,   234,   239,   245,   246,   247,
     249,   256,   263,   266,   267,   269,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   145,   225,   217,   261,   262,   286,   286,    29,    97,
     178,   314,    31,   306,   307,    68,   145,   167,   168,   226,
      68,    81,   212,   245,   150,   177,   265,   309,   312,   308,
     263,   293,   309,    97,   294,   286,   261,   286,   286,   263,
     261,    56,   230,   240,   167,   168,   226,   144,   145,   286,
     227,   250,   261,   263,   264,    56,   132,   145,   167,   168,
     226,   263,   263,   104,   106,   145,   150,   225,   312,   312,
     191,   286,    35,   213,   221,   233,   244,   286,   296,   300,
     263,   145,   145,   167,   168,   226,   286,    30,   168,   264,
      34,    73,    94,   116,   158,   175,   178,   226,   239,   286,
     286,    97,   145,   225,   167,   168,   226,     5,    35,   167,
     168,   226,   261,   271,   286,   311,   145,   225,   145,   225,
      56,   145,   225,   261,    56,   265,   163,   265,   265,   263,
     227,   265,   167,   168,   226,   263,    68,   167,   168,   226,
     145,   140,   261,    56,   145,   261,   296,    56,    68,   145,
     145,   244,   261,   296,   265,   265,   271,    35,    31,    31,
      36,    58,   162,     0,    97,   286,    35,   145,   145,   145,
     145,   145,   286,   286,   273,   279,   273,   145,   145,   145,
       6,    14,   176,   217,   268,   145,    93,     9,   219,    13,
     155,   150,   179,    68,    85,    92,   126,   142,   160,     7,
     171,   259,   101,    69,    35,   286,   145,   269,    35,    35,
      40,    97,   167,   168,   261,   271,   315,   145,   286,   286,
      68,   145,    68,    68,   309,   150,    36,    35,    35,    35,
      35,    35,    68,    35,    35,   270,   286,   270,    89,   236,
     298,    35,   213,   286,    35,   286,    68,   250,   261,   263,
     286,    56,   286,   145,   225,   145,    35,   145,   145,   286,
     300,    68,    97,   263,   286,    97,    89,   299,   298,   299,
     299,   145,   299,   299,   299,   299,    68,   298,   299,    82,
      97,   286,   145,    35,   311,    35,   286,   286,   145,   286,
     145,    35,   286,   145,    35,    35,    68,    35,    35,   286,
     286,    35,    35,   286,    35,    35,   286,   286,   286,   286,
      35,   271,   306,   307,   286,   261,   286,   261,   286,   286,
     261,   286,   261,   286,   208,    35,   286,    97,   263,   208,
     270,   269,   274,   274,   275,   276,   277,   277,   278,   278,
     278,   278,   278,   278,   280,   281,   282,   283,   284,    97,
     265,    35,   286,   261,   286,   262,   286,   145,   315,    35,
     286,    35,   286,   208,   264,   286,   286,   309,   263,    97,
     286,   290,   291,   291,   291,   286,   286,   286,    35,   207,
     208,     9,    65,   265,   306,   308,   265,   264,   264,    35,
     213,   263,   208,   286,   286,    35,    35,   213,   301,    35,
      35,   286,   145,   286,    97,   286,   286,   213,   286,    35,
      35,   208,   286,   265,   265,   265,   265,   310,   311,   286,
     265,   265,   265,   265,   227,   310,   310,    97,   104,   261,
     286,    35,   286,   271,   286,    35,   286,    35,   286,   244,
     296,    35,   286,   286,   286,   286,    97,   263,    35,   286,
     286,    35,   296,   296,    35,    35,   213,   244,   296,   208,
     208,   208,   208,    35,   208,   208,   208,   208,   208,   265,
     208,    35,    35,   208,   208,    35,   286,    35,    35,   286,
     271,    35,   286,    68,   208,    97,    35,   240,   286,    97,
     265,   306,   307,    65,    65,    65,   227,   264,   264,   167,
     168,   226,    35,   263,   263,   263,   286,    35,   286,    35,
     208,   208,   286,   297,   286,   286,   167,   168,   226,   311,
     265,   208,   299,    97,    97,   286,    35,   286,    35,   286,
      35,   286,   286,    35,   286,   286,   286,   286,   297,   286,
     261,    35,   286,   286,    97,   208,   286,   263,   286,   208,
     286,    68,   263,   290,   286,   265,   306,   307,   265,   306,
     307,   265,   306,   307,    35,   213,   263,   286,   208,   286,
      35,   286,    35,   213,   286,   208,    35,   265,   299,   265,
     261,   286,   261,   286,   208,   286,   208,   286,   208,   286,
     213,   208,   286,   208,   208,   208,   208,   213,   208,    54,
      97,    35,   208,   208,    35,   208,   208,   150,   286,   225,
     264,   264,   301,   150,   208,   286,   208,    68,   286,   265,
     208,   208,   208,   297,   208,   150,   150,    35,   150,   297,
     312,    35,   286,   286,    35,   145,   286,   263,   145,   225,
     208,   150,   286,   208,   145,   145,   114,   263,   145,   225,
      54,    35,   208,   286,   286,   286,   145,   145,   225,    68,
     286,   286,   145,    35,   286,   145,   312,   286,    35,    35,
     286,   286,   145,   286,    35,    35,   286,     7,   171,   184,
     187,   259,   287,    35,   286,   208,   286,   286,    35,    35,
     286,   286,   286,   208,    35,   286,    35,   208,   208,   286,
     286,    35,   208,   208,    35,   286,   208,   286,   208,   208,
     286,    35,   287,    35,    35,   208,   208,   286,    35,   286,
     263,    35,    35,   286,   263,   286,    35,   286
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int16 yyr1[] =
{
       0,   260,   261,   262,   262,   262,   262,   263,   263,   263,
     264,   264,   265,   265,   266,   266,   267,   267,   267,   267,
     268,   268,   268,   268,   269,   269,   269,   269,   269,   269,
     269,   269,   269,   269,   269,   269,   269,   269,   269,   269,
     269,   269,   269,   269,   269,   269,   269,   269,   269,   269,
     269,   269,   269,   270,   270,   271,   271,   271,   272,   272,
     272,   272,   272,   272,   272,   272,   272,   272,   272,   272,
     272,   272,   272,   272,   272,   272,   272,   272,   272,   272,
     272,   272,   272,   272,   272,   272,   272,   272,   272,   272,
     272,   272,   272,   272,   272,   272,   272,   272,   272,   272,
     272,   272,   272,   272,   272,   272,   272,   272,   272,   272,
     272,   272,   272,   272,   272,   272,   272,   272,   273,   273,
     274,   274,   274,   275,   275,   275,   276,   276,   277,   277,
     278,   278,   278,   279,   279,   279,   279,   279,   279,   279,
     280,   280,   281,   281,   282,   282,   283,   283,   284,   284,
     285,   285,   286,   287,   287,   287,   287,   287,   288,   288,
     289,   289,   290,   291,   291,   292,   292,   292,   292,   292,
     292,   292,   292,   292,   292,   292,   292,   292,   292,   292,
     292,   292,   292,   292,   292,   292,   292,   292,   292,   292,
     292,   292,   292,   292,   292,   292,   292,   292,   292,   292,
     292,   292,   292,   292,   292,   292,   292,   292,   292,   292,
     292,   292,   292,   292,   292,   292,   292,   292,   292,   292,
     292,   292,   292,   292,   292,   292,   292,   292,   292,   292,
     292,   292,   292,   292,   292,   292,   292,   292,   292,   292,
     292,   292,   292,   292,   292,   292,   292,   292,   292,   292,
     292,   292,   292,   292,   292,   292,   292,   292,   292,   292,
     292,   292,   292,   292,   292,   292,   292,   292,   292,   292,
     292,   292,   292,   292,   292,   292,   292,   292,   292,   292,
     292,   292,   292,   292,   292,   292,   292,   292,   292,   292,
     292,   292,   292,   292,   292,   292,   292,   292,   292,   292,
     292,   292,   292,   292,   292,   292,   292,   292,   292,   292,
     292,   292,   292,   292,   292,   292,   292,   292,   292,   292,
     292,   292,   292,   292,   292,   292,   292,   292,   292,   292,
     292,   292,   293,   293,   294,   294,   295,   295,   296,   296,
     297,   297,   297,   297,   298,   298,   299,   299,   300,   300,
     300,   300,   300,   301,   301,   302,   302,   302,   302,   302,
     302,   302,   302,   302,   302,   302,   302,   302,   302,   302,
     302,   302,   302,   302,   302,   302,   302,   302,   302,   302,
     302,   302,   302,   302,   302,   302,   302,   302,   302,   302,
     302,   302,   302,   302,   302,   302,   302,   302,   302,   302,
     302,   302,   302,   302,   302,   302,   302,   302,   302,   302,
     302,   302,   302,   302,   302,   302,   302,   302,   302,   302,
     302,   302,   303,   303,   303,   303,   303,   303,   303,   303,
     303,   303,   303,   303,   303,   303,   303,   303,   303,   303,
     303,   303,   304,   304,   304,   304,   304,   304,   304,   304,
     304,   304,   305,   305,   305,   305,   305,   305,   305,   305,
     306,   306,   306,   306,   306,   307,   307,   307,   307,   308,
     308,   308,   309,   309,   310,   310,   310,   311,   311,   312,
     312,   312,   312,   313,   313,   314,   314,   314,   315,   315,
     315,   315,   316,   316,   316,   316,   317,   317,   317,   317
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     3,     3,     4,     4,     1,
       1,     3,     1,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     1,     4,     3,     1,     1,     4,     1,     6,     4,
       6,     8,    10,     4,     4,     4,     4,     4,     4,     4,
       4,     6,     4,     1,     3,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     2,     2,     1,     3,     3,     1,     3,     1,     3,
       1,     3,     3,     1,     3,     3,     3,     3,     3,     3,
       1,     2,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     3,     1,     2,     4,     3,     7,
       7,     5,     4,     4,     2,     1,     4,     4,     2,     1,
       5,     2,     1,     8,     6,     2,     1,     6,     6,     6,
       6,     4,     4,     5,     3,     5,     5,     2,     8,     6,
       2,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     6,     4,     7,     2,     2,     6,     4,     3,
       2,     3,     1,     2,     1,     4,     4,     2,     7,     5,
       7,     5,     4,     4,     3,     3,     2,     2,     2,     1,
       4,     2,     4,     2,     4,     2,     4,     2,    15,    14,
      17,    16,    13,    11,    14,    10,     8,    10,     7,     8,
       5,     3,     4,     6,     4,     2,     4,     6,     7,     2,
       2,     2,     5,     5,     5,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     7,     6,     2,     1,     1,     2,     1,
       2,     1,     4,     2,     2,     1,     2,     4,     2,     1,
       4,     2,     2,     1,     2,     4,     1,     4,     4,     4,
       2,     1,     4,     4,     2,     4,     3,     2,     1,     4,
       4,     1,     1,     3,     1,     3,     1,     1,     1,     2,
       1,     2,     2,     2,     1,     2,     1,     2,     1,     4,
       4,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     5,
       5,     5,     2,     2,     2,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     2,     2,     2,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
      10,     8,     2,     2,     8,     7,    14,    13,    13,    12,
       8,     9,     6,     7,     7,     6,     7,     6,     7,    12,
      12,    12,     6,     6,     6,     6,     5,     5,     6,     6,
       5,     4,     6,     6,     6,     5,     4,     4,     3,     4,
       3,     2,     1,     1,     2,     3,     2,     1,     2,     1,
       1,     1,     1,     1,     1,     3,     2,     1,     2,     3,
       2,     2,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     3,     3,     2,     2,     1,     2,     1,     2,     0
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (result, yyscanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, result, yyscanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, VskParseResult& result, yyscan_t yyscanner)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (result);
  YYUSE (yyscanner);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, VskParseResult& result, yyscan_t yyscanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep, result, yyscanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule, VskParseResult& result, yyscan_t yyscanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              , result, yyscanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, result, yyscanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, VskParseResult& result, yyscan_t yyscanner)
{
  YYUSE (yyvaluep);
  YYUSE (result);
  YYUSE (yyscanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (VskParseResult& result, yyscan_t yyscanner)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (yyscanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 283 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_FILE_NUMBER, { yyvsp[0] }); }
#line 3627 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 3:
#line 287 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_FILE_NUMBERS, { yyvsp[0] }); }
#line 3633 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 4:
#line 288 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_FILE_NUMBERS, { yyvsp[0] }); }
#line 3639 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 5:
#line 289 "parser.yy"
                                                        { yyval = yyvsp[-2]; yyval->push_back(yyvsp[0]); }
#line 3645 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 6:
#line 290 "parser.yy"
                                                        { yyval = yyvsp[-2]; yyval->push_back(yyvsp[0]); }
#line 3651 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 7:
#line 294 "parser.yy"
                                                                { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_LVALUE, { yyvsp[-3], yyvsp[-1] }); }
#line 3657 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 8:
#line 295 "parser.yy"
                                                                { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_LVALUE, { yyvsp[-3], yyvsp[-1] }); }
#line 3663 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 9:
#line 296 "parser.yy"
                                                                { yyval = yyvsp[0]; }
#line 3669 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 10:
#line 300 "parser.yy"
                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_LVALUE_LIST, { yyvsp[0] }); }
#line 3675 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 11:
#line 301 "parser.yy"
                                        { yyval = yyvsp[-2]; yyval->push_back(yyvsp[0]); }
#line 3681 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 12:
#line 305 "parser.yy"
                                { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_LABEL, { yyvsp[0] }); }
#line 3687 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 13:
#line 306 "parser.yy"
                                { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_LABEL, { yyvsp[0] }); }
#line 3693 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 14:
#line 310 "parser.yy"
                        { yyval = yyvsp[0]; yyvsp[0]->push_back(yyvsp[-1]); }
#line 3699 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 15:
#line 311 "parser.yy"
                        { yyval = yyvsp[0]; }
#line 3705 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 16:
#line 315 "parser.yy"
                        { yyval = yyvsp[0]; }
#line 3711 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 17:
#line 316 "parser.yy"
                        { yyval = yyvsp[0]; }
#line 3717 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 18:
#line 317 "parser.yy"
                        { yyval = yyvsp[0]; }
#line 3723 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 19:
#line 318 "parser.yy"
                        { yyval = yyvsp[0]; }
#line 3729 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 20:
#line 322 "parser.yy"
                        { yyval = yyvsp[0]; }
#line 3735 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 21:
#line 323 "parser.yy"
                        { yyval = yyvsp[0]; }
#line 3741 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 22:
#line 324 "parser.yy"
                        { yyval = yyvsp[0]; }
#line 3747 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 23:
#line 325 "parser.yy"
                        { yyval = yyvsp[0]; }
#line 3753 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 24:
#line 329 "parser.yy"
                                        { yyval = yyvsp[0]; }
#line 3759 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 25:
#line 330 "parser.yy"
                                        { yyval = yyvsp[0]; }
#line 3765 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 26:
#line 331 "parser.yy"
                                        { yyval = yyvsp[0]; }
#line 3771 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 27:
#line 332 "parser.yy"
                                        { yyval = yyvsp[-1]; }
#line 3777 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 28:
#line 333 "parser.yy"
                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_DATE_dollar_var); }
#line 3783 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 29:
#line 334 "parser.yy"
                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_TIME_dollar_var); }
#line 3789 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 30:
#line 335 "parser.yy"
                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_INKEY_dollar); }
#line 3795 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 31:
#line 336 "parser.yy"
                                                             { vsk_targeting(yyvsp[0]); yyval = yyvsp[0]; }
#line 3801 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 32:
#line 337 "parser.yy"
                                                             { vsk_targeting(yyvsp[-3]); yyval = yyvsp[-3]; yyval->children() = std::move(yyvsp[-1]->children()); }
#line 3807 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 33:
#line 338 "parser.yy"
                                                             { vsk_targeting(yyvsp[-2]); yyval = yyvsp[-2]; }
#line 3813 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 34:
#line 339 "parser.yy"
                                                             { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_ERL); }
#line 3819 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 35:
#line 340 "parser.yy"
                                                             { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_ERR); }
#line 3825 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 36:
#line 341 "parser.yy"
                                                             { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_RND, { yyvsp[-1] }); }
#line 3831 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 37:
#line 342 "parser.yy"
                                                             { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_RND); }
#line 3837 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 38:
#line 343 "parser.yy"
                                                                 { vsk_targeting(yyvsp[-5]); yyval = vsk_ast(INSN_VARPTR, { yyvsp[-3], yyvsp[-1] }); }
#line 3843 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 39:
#line 344 "parser.yy"
                                                                 { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_VARPTR, { yyvsp[-1] }); }
#line 3849 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 40:
#line 345 "parser.yy"
                                                                        {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_SEARCH, { yyvsp[-3], yyvsp[-1] });
    }
#line 3858 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 41:
#line 349 "parser.yy"
                                                                                            {
        vsk_targeting(yyvsp[-7]);
        yyval = vsk_ast(INSN_SEARCH, { yyvsp[-5], yyvsp[-3], yyvsp[-1] });
    }
#line 3867 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 42:
#line 353 "parser.yy"
                                                                                                                {
        vsk_targeting(yyvsp[-9]);
        yyval = vsk_ast(INSN_SEARCH, { yyvsp[-7], yyvsp[-5], yyvsp[-3], yyvsp[-1] });
    }
#line 3876 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 43:
#line 357 "parser.yy"
                                               { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_LOF, { yyvsp[-1] }); }
#line 3882 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 44:
#line 358 "parser.yy"
                                               { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_LOF, { yyvsp[-1] }); }
#line 3888 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 45:
#line 359 "parser.yy"
                                               { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_EOF, { yyvsp[-1] }); }
#line 3894 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 46:
#line 360 "parser.yy"
                                               { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_EOF, { yyvsp[-1] }); }
#line 3900 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 47:
#line 361 "parser.yy"
                                               { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_LOC, { yyvsp[-1] }); }
#line 3906 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 48:
#line 362 "parser.yy"
                                               { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_LOC, { yyvsp[-1] }); }
#line 3912 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 49:
#line 363 "parser.yy"
                                                { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_FPOS, { yyvsp[-1] }); }
#line 3918 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 50:
#line 364 "parser.yy"
                                                { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_FPOS, { yyvsp[-1] }); }
#line 3924 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 51:
#line 365 "parser.yy"
                                                                            { vsk_targeting(yyvsp[-5]); yyval = vsk_ast(INSN_INPUT_dollar, { yyvsp[-3], yyvsp[-1] }); }
#line 3930 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 52:
#line 366 "parser.yy"
                                                       { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_INPUT_dollar, { yyvsp[-1] }); }
#line 3936 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 53:
#line 370 "parser.yy"
                                         { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_PARAM_LIST, { yyvsp[0] }); }
#line 3942 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 54:
#line 371 "parser.yy"
                                         { yyval = yyvsp[-2]; yyval->push_back(yyvsp[0]); }
#line 3948 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 55:
#line 375 "parser.yy"
                                                                { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_PARAM_LIST, { yyvsp[0] }); }
#line 3954 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 56:
#line 376 "parser.yy"
                                                {
        yyval = yyvsp[-2];
        yyval->insert(yyval->end(), yyvsp[-1]->begin(), yyvsp[-1]->end());
        yyval->push_back(yyvsp[0]);
    }
#line 3964 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 57:
#line 381 "parser.yy"
                        {
        vsk_targeting(yyvsp[-1]);
        yyval = vsk_ast(INSN_PARAM_LIST);
        yyval->push_back(nullptr);
        yyval->insert(yyval->end(), yyvsp[-1]->begin(), yyvsp[-1]->end());
        yyval->push_back(yyvsp[0]);
    }
#line 3976 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 58:
#line 391 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_ABS); }
#line 3982 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 59:
#line 392 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_AKCNV_dollar); }
#line 3988 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 60:
#line 393 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_ASC); }
#line 3994 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 61:
#line 394 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_ATN); }
#line 4000 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 62:
#line 395 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_ATTR_dollar); }
#line 4006 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 63:
#line 396 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CDBL); }
#line 4012 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 64:
#line 397 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CHR_dollar); }
#line 4018 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 65:
#line 398 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CINT); }
#line 4024 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 66:
#line 399 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_COS); }
#line 4030 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 67:
#line 400 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CSNG); }
#line 4036 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 68:
#line 401 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CSRLIN); }
#line 4042 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 69:
#line 402 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CVD); }
#line 4048 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 70:
#line 403 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CVI); }
#line 4054 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 71:
#line 404 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CVS); }
#line 4060 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 72:
#line 405 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_DSKF); }
#line 4066 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 73:
#line 406 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_DSKI_dollar); }
#line 4072 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 74:
#line 407 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_EXP); }
#line 4078 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 75:
#line 408 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_FIX); }
#line 4084 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 76:
#line 409 "parser.yy"
                          { yyval = yyvsp[0]; }
#line 4090 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 77:
#line 410 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_FRE); }
#line 4096 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 78:
#line 411 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_HEX_dollar); }
#line 4102 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 79:
#line 412 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_INP); }
#line 4108 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 80:
#line 413 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_INSTR); }
#line 4114 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 81:
#line 414 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_INT); }
#line 4120 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 82:
#line 415 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_JIS_dollar); }
#line 4126 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 83:
#line 416 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_KACNV_dollar); }
#line 4132 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 84:
#line 417 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_KEXT_dollar); }
#line 4138 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 85:
#line 418 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_KINSTR); }
#line 4144 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 86:
#line 419 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_KLEN); }
#line 4150 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 87:
#line 420 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_KMID_dollar); }
#line 4156 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 88:
#line 421 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_KNJ_dollar); }
#line 4162 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 89:
#line 422 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_KPOS); }
#line 4168 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 90:
#line 423 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_KTYPE); }
#line 4174 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 91:
#line 424 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_LEFT_dollar); }
#line 4180 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 92:
#line 425 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_LEN); }
#line 4186 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 93:
#line 426 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_LOG); }
#line 4192 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 94:
#line 427 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_LPOS); }
#line 4198 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 95:
#line 428 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_MAP); }
#line 4204 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 96:
#line 429 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_MID_dollar_func); }
#line 4210 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 97:
#line 430 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_MKD_dollar); }
#line 4216 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 98:
#line 431 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_MKI_dollar); }
#line 4222 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 99:
#line 432 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_MKS_dollar); }
#line 4228 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 100:
#line 433 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_MOUSE_func); }
#line 4234 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 101:
#line 434 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_OCT_dollar); }
#line 4240 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 102:
#line 435 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_PEEK); }
#line 4246 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 103:
#line 436 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_PEN); }
#line 4252 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 104:
#line 437 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_POINT_func); }
#line 4258 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 105:
#line 438 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_POS); }
#line 4264 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 106:
#line 439 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_RIGHT_dollar); }
#line 4270 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 107:
#line 440 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_SGN); }
#line 4276 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 108:
#line 441 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_SIN); }
#line 4282 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 109:
#line 442 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_SPACE_dollar); }
#line 4288 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 110:
#line 443 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_SQR); }
#line 4294 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 111:
#line 444 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_STRING_dollar); }
#line 4300 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 112:
#line 445 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_STR_dollar); }
#line 4306 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 113:
#line 446 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_TAN); }
#line 4312 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 114:
#line 447 "parser.yy"
                          { yyval = yyvsp[0]; }
#line 4318 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 115:
#line 448 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_VAL); }
#line 4324 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 116:
#line 449 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_VIEW_func); }
#line 4330 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 117:
#line 450 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_WINDOW_func); }
#line 4336 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 118:
#line 454 "parser.yy"
                                                         { yyval = yyvsp[0]; }
#line 4342 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 119:
#line 455 "parser.yy"
                                                         { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_HAT, { yyvsp[-2], yyvsp[0] }); }
#line 4348 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 120:
#line 458 "parser.yy"
                                       { yyval = yyvsp[0]; }
#line 4354 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 121:
#line 459 "parser.yy"
                                       { yyval = yyvsp[0]; }
#line 4360 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 122:
#line 460 "parser.yy"
                                       { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_UMINUS, { yyvsp[0] }); }
#line 4366 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 123:
#line 464 "parser.yy"
                                                             { yyval = yyvsp[0]; }
#line 4372 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 124:
#line 465 "parser.yy"
                                                             { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_MUL, { yyvsp[-2], yyvsp[0] }); }
#line 4378 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 125:
#line 466 "parser.yy"
                                                             { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_DIV, { yyvsp[-2], yyvsp[0] }); }
#line 4384 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 126:
#line 470 "parser.yy"
                                                                    { yyval = yyvsp[0]; }
#line 4390 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 127:
#line 471 "parser.yy"
                                                                    { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_IDIV, { yyvsp[-2], yyvsp[0] }); }
#line 4396 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 128:
#line 475 "parser.yy"
                                                       { yyval = yyvsp[0]; }
#line 4402 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 129:
#line 476 "parser.yy"
                                                       { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_MOD, { yyvsp[-2], yyvsp[0] }); }
#line 4408 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 130:
#line 480 "parser.yy"
                                                     { yyval = yyvsp[0]; }
#line 4414 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 131:
#line 481 "parser.yy"
                                                     { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_ADD, { yyvsp[-2], yyvsp[0] }); }
#line 4420 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 132:
#line 482 "parser.yy"
                                                     { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_SUB, { yyvsp[-2], yyvsp[0] }); }
#line 4426 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 133:
#line 486 "parser.yy"
                                                            { yyval = yyvsp[0]; }
#line 4432 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 134:
#line 487 "parser.yy"
                                                            { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_LT, { yyvsp[-2], yyvsp[0] }); }
#line 4438 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 135:
#line 488 "parser.yy"
                                                            { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_LE, { yyvsp[-2], yyvsp[0] }); }
#line 4444 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 136:
#line 489 "parser.yy"
                                                            { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_GT, { yyvsp[-2], yyvsp[0] }); }
#line 4450 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 137:
#line 490 "parser.yy"
                                                            { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_GE, { yyvsp[-2], yyvsp[0] }); }
#line 4456 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 138:
#line 491 "parser.yy"
                                                            { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_EQUAL, { yyvsp[-2], yyvsp[0] }); }
#line 4462 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 139:
#line 492 "parser.yy"
                                                            { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_NE, { yyvsp[-2], yyvsp[0] }); }
#line 4468 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 140:
#line 496 "parser.yy"
                                                        { yyval = yyvsp[0]; }
#line 4474 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 141:
#line 497 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_NOT, { yyvsp[0] });}
#line 4480 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 142:
#line 501 "parser.yy"
                                                        { yyval = yyvsp[0]; }
#line 4486 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 143:
#line 502 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_AND, { yyvsp[-2], yyvsp[0] }); }
#line 4492 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 144:
#line 506 "parser.yy"
                                                        { yyval = yyvsp[0]; }
#line 4498 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 145:
#line 507 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_OR, { yyvsp[-2], yyvsp[0] }); }
#line 4504 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 146:
#line 511 "parser.yy"
                                                        { yyval = yyvsp[0]; }
#line 4510 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 147:
#line 512 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_XOR, { yyvsp[-2], yyvsp[0] }); }
#line 4516 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 148:
#line 516 "parser.yy"
                                                        { yyval = yyvsp[0]; }
#line 4522 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 149:
#line 517 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_IMP, { yyvsp[-2], yyvsp[0] }); }
#line 4528 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 150:
#line 521 "parser.yy"
                                                        { yyval = yyvsp[0]; }
#line 4534 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 151:
#line 522 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_EQV, { yyvsp[-2], yyvsp[0] }); }
#line 4540 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 152:
#line 526 "parser.yy"
                                                        { yyval = yyvsp[0]; }
#line 4546 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 153:
#line 530 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast_str("AND"); }
#line 4552 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 154:
#line 531 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast_str("OR"); }
#line 4558 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 155:
#line 532 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast_str("XOR"); }
#line 4564 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 156:
#line 533 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast_str("PSET"); }
#line 4570 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 157:
#line 534 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast_str("PRESET"); }
#line 4576 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 158:
#line 538 "parser.yy"
                                                        { yyval = yyvsp[0]; }
#line 4582 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 159:
#line 539 "parser.yy"
                                                        { yyval = yyvsp[0]; }
#line 4588 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 160:
#line 543 "parser.yy"
                                                        { yyval = yyvsp[0]; }
#line 4594 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 161:
#line 544 "parser.yy"
                                                        { yyval = yyvsp[0]; }
#line 4600 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 162:
#line 548 "parser.yy"
                                                        { vsk_targeting(yyvsp[-2]); yyval = vsk_ast(INSN_FIELD_ITEM, { yyvsp[-2], yyvsp[-1], yyvsp[0] }); }
#line 4606 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 163:
#line 552 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_FIELD_ITEMS, { yyvsp[0] }); }
#line 4612 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 164:
#line 553 "parser.yy"
                                                        { yyval = yyvsp[-2]; yyval->push_back(yyvsp[0]); }
#line 4618 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 165:
#line 557 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_REM, yyvsp[0]->m_str); }
#line 4624 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 166:
#line 558 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_LABEL_DEF, yyvsp[0]->m_str); }
#line 4630 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 167:
#line 560 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_LET, { yyvsp[-2], yyvsp[0] }); }
#line 4636 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 168:
#line 561 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_LET, { yyvsp[-2], yyvsp[0] }); }
#line 4642 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 169:
#line 563 "parser.yy"
                                                                                         {
        vsk_targeting(yyvsp[-6]);
        yyval = vsk_ast(INSN_PRINT_USING, { yyvsp[-5], yyvsp[-2], yyvsp[0] });
    }
#line 4651 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 170:
#line 567 "parser.yy"
                                                                                      {
        vsk_targeting(yyvsp[-6]);
        yyval = vsk_ast(INSN_PRINT_USING, { yyvsp[-5], yyvsp[-2], yyvsp[0] });
    }
#line 4660 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 171:
#line 571 "parser.yy"
                                                             {
        vsk_targeting(yyvsp[-4]);
        yyval = vsk_ast(INSN_PRINT_USING, { nullptr, yyvsp[-2], yyvsp[0] });
    }
#line 4669 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 172:
#line 576 "parser.yy"
                                                      {
        vsk_targeting(yyvsp[-3]);
        yyval = vsk_ast(INSN_PRINT, { yyvsp[-2], yyvsp[0] });
    }
#line 4678 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 173:
#line 580 "parser.yy"
                                               {
        vsk_targeting(yyvsp[-3]);
        yyval = vsk_ast(INSN_PRINT, { yyvsp[-2], yyvsp[0] });
    }
#line 4687 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 174:
#line 584 "parser.yy"
                          {
        vsk_targeting(yyvsp[-1]);
        yyval = vsk_ast(INSN_PRINT, { nullptr, yyvsp[0] });
    }
#line 4696 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 175:
#line 588 "parser.yy"
            {
        vsk_targeting(yyvsp[0]);
        yyval = vsk_ast(INSN_PRINT, { nullptr, nullptr });
    }
#line 4705 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 176:
#line 593 "parser.yy"
                                                      {
        vsk_targeting(yyvsp[-3]);
        yyval = vsk_ast(INSN_WRITE, { yyvsp[-2], yyvsp[0] });
    }
#line 4714 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 177:
#line 597 "parser.yy"
                                                   {
        vsk_targeting(yyvsp[-3]);
        yyval = vsk_ast(INSN_WRITE, { yyvsp[-2], yyvsp[0] });
    }
#line 4723 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 178:
#line 601 "parser.yy"
                             {
        vsk_targeting(yyvsp[-1]);
        yyval = vsk_ast(INSN_WRITE, { nullptr, yyvsp[0] });
    }
#line 4732 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 179:
#line 605 "parser.yy"
               {
        vsk_targeting(yyvsp[0]);
        yyval = vsk_ast(INSN_WRITE, { nullptr, nullptr });
    }
#line 4741 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 180:
#line 610 "parser.yy"
                                                                 {
        vsk_targeting(yyvsp[-4]);
        yyval = vsk_ast(INSN_LPRINT_USING, { yyvsp[-2], yyvsp[0] });
    }
#line 4750 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 181:
#line 615 "parser.yy"
                              {
        vsk_targeting(yyvsp[-1]);
        yyval = vsk_ast(INSN_LPRINT, { yyvsp[0] });
    }
#line 4759 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 182:
#line 619 "parser.yy"
                {
        vsk_targeting(yyvsp[0]);
        yyval = vsk_ast(INSN_LPRINT, { nullptr });
    }
#line 4768 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 183:
#line 624 "parser.yy"
                                                                            {
        vsk_targeting(yyvsp[-7]);
        yyval = vsk_ast(INSN_FOR, { yyvsp[-6], yyvsp[-4], yyvsp[-2], yyvsp[0] });
    }
#line 4777 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 184:
#line 628 "parser.yy"
                                                         {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_FOR, { yyvsp[-4], yyvsp[-2], yyvsp[0], nullptr });
    }
#line 4786 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 185:
#line 633 "parser.yy"
                          {
        vsk_targeting(yyvsp[-1]);
        yyval = vsk_ast(INSN_NEXT);
        yyval->insert(yyval->end(), yyvsp[0]->begin(), yyvsp[0]->end());
    }
#line 4796 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 186:
#line 638 "parser.yy"
              {
        vsk_targeting(yyvsp[0]);
        yyval = vsk_ast(INSN_NEXT);
    }
#line 4805 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 187:
#line 642 "parser.yy"
                                                                        {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_OPEN, { yyvsp[-4], yyvsp[-2], yyvsp[-1], yyvsp[0] });
    }
#line 4814 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 188:
#line 646 "parser.yy"
                                                                   {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_OPEN, { yyvsp[-4], yyvsp[-2], yyvsp[-1], yyvsp[0] });
    }
#line 4823 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 189:
#line 650 "parser.yy"
                                                                       {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_OPEN, { yyvsp[-4], yyvsp[-2], yyvsp[-1], yyvsp[0] });
    }
#line 4832 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 190:
#line 654 "parser.yy"
                                                                  {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_OPEN, { yyvsp[-4], yyvsp[-2], yyvsp[-1], yyvsp[0] });
    }
#line 4841 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 191:
#line 658 "parser.yy"
                                                   {
        vsk_targeting(yyvsp[-3]);
        yyval = vsk_ast(INSN_OPEN, { yyvsp[-2], nullptr, yyvsp[-1], yyvsp[0] });
    }
#line 4850 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 192:
#line 662 "parser.yy"
                                                  {
        vsk_targeting(yyvsp[-3]);
        yyval = vsk_ast(INSN_OPEN, { yyvsp[-2], nullptr, yyvsp[-1], yyvsp[0] });
    }
#line 4859 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 193:
#line 666 "parser.yy"
                                                            {
        vsk_targeting(yyvsp[-4]);
        yyval = vsk_ast(INSN_LINE_INPUT, { yyvsp[-2], yyvsp[0] });
    }
#line 4868 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 194:
#line 670 "parser.yy"
                              {
        vsk_targeting(yyvsp[-2]);
        yyval = vsk_ast(INSN_LINE_INPUT, { nullptr, yyvsp[0] });
    }
#line 4877 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 195:
#line 674 "parser.yy"
                                                   {
        vsk_targeting(yyvsp[-4]);
        yyval = vsk_ast(INSN_LINE_INPUT_sharp, { yyvsp[-2], yyvsp[0] });
    }
#line 4886 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 196:
#line 678 "parser.yy"
                                                       {
        vsk_targeting(yyvsp[-4]);
        yyval = vsk_ast(INSN_LINE_INPUT_sharp, { yyvsp[-2], yyvsp[0] });
    }
#line 4895 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 197:
#line 682 "parser.yy"
                       {
        vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_KINPUT, { yyvsp[0] });
    }
#line 4903 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 198:
#line 685 "parser.yy"
                                                                                        {
        vsk_targeting(yyvsp[-7]);
        yyval = vsk_ast(INSN_LINE_INPUT_WAIT, { yyvsp[-4], yyvsp[-2], yyvsp[0] });
    }
#line 4912 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 199:
#line 689 "parser.yy"
                                                          {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_LINE_INPUT_WAIT, { yyvsp[-2], nullptr, yyvsp[0] });
    }
#line 4921 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 200:
#line 693 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_DIM, { yyvsp[0] }); }
#line 4927 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 201:
#line 694 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_DEF_SEG, { yyvsp[0] }); }
#line 4933 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 202:
#line 695 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_DEF_USR, { yyvsp[-2], yyvsp[0] }); }
#line 4939 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 203:
#line 696 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_ON_COM_GOSUB, { yyvsp[0] }); }
#line 4945 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 204:
#line 697 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_ON_ERROR_GOTO, { yyvsp[0] }); }
#line 4951 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 205:
#line 698 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_ON_EXPR_GOTO, { yyvsp[-2], yyvsp[0] }); }
#line 4957 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 206:
#line 699 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_ON_EXPR_GOSUB, { yyvsp[-2], yyvsp[0] }); }
#line 4963 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 207:
#line 700 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_ON_HELP_GOSUB, { yyvsp[0] }); }
#line 4969 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 208:
#line 701 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_ON_KEY_GOSUB, { yyvsp[0] }); }
#line 4975 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 209:
#line 702 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_ON_PEN_GOSUB, { yyvsp[0] }); }
#line 4981 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 210:
#line 703 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_ON_PLAY_GOSUB, { yyvsp[0] }); }
#line 4987 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 211:
#line 704 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_ON_STOP_GOSUB, { yyvsp[0] }); }
#line 4993 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 212:
#line 705 "parser.yy"
                                                                 {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_ON_TIME_dollar_GOSUB, { yyvsp[-2], yyvsp[0] });
    }
#line 5002 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 213:
#line 709 "parser.yy"
                                                                         {
        vsk_targeting(yyvsp[-3]);
        yyval = vsk_ast(INSN_ON_MOUSE_GOSUB, { nullptr, yyvsp[0] });
    }
#line 5011 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 214:
#line 713 "parser.yy"
                                                                         {
        vsk_targeting(yyvsp[-6]);
        yyval = vsk_ast(INSN_ON_MOUSE_GOSUB, { yyvsp[-3], yyvsp[0] });
    }
#line 5020 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 215:
#line 717 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_GOSUB, { yyvsp[0] }); }
#line 5026 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 216:
#line 718 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast_goto(yyvsp[0]); }
#line 5032 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 217:
#line 719 "parser.yy"
                                                         {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_CMD, { yyvsp[-4], yyvsp[-3], yyvsp[-2], yyvsp[0] });
    }
#line 5041 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 218:
#line 723 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_CMD, { yyvsp[-2], yyvsp[-1] }); yyval->insert(yyval->end(), yyvsp[0]->begin(), yyvsp[0]->end()); }
#line 5047 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 219:
#line 724 "parser.yy"
                                                        { vsk_targeting(yyvsp[-2]); yyval = vsk_ast(INSN_CMD, { yyvsp[-1] }); yyval->insert(yyval->end(), yyvsp[0]->begin(), yyvsp[0]->end()); }
#line 5053 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 220:
#line 725 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_CMD, { yyvsp[0] }); }
#line 5059 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 221:
#line 726 "parser.yy"
                                                        { yyval = yyvsp[-2]; yyval->insert(yyval->end(), yyvsp[0]->begin(), yyvsp[0]->end()); }
#line 5065 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 222:
#line 727 "parser.yy"
                                                        { yyval = yyvsp[0]; }
#line 5071 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 223:
#line 728 "parser.yy"
                                                        { yyval = yyvsp[-1]; yyval->insert(yyval->end(), yyvsp[0]->begin(), yyvsp[0]->end()); }
#line 5077 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 224:
#line 729 "parser.yy"
                                                        { yyval = yyvsp[0]; }
#line 5083 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 225:
#line 730 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_INPUT_semicolon, { yyvsp[-2], yyvsp[0] }); }
#line 5089 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 226:
#line 731 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_INPUT, { yyvsp[-2], yyvsp[0] }); }
#line 5095 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 227:
#line 732 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_INPUT, { nullptr, yyvsp[0] }); }
#line 5101 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 228:
#line 733 "parser.yy"
                                                                              {
        vsk_targeting(yyvsp[-6]);
        yyval = vsk_ast(INSN_INPUT_WAIT_semicolon, { yyvsp[-4], yyvsp[-2], yyvsp[0] });
    }
#line 5110 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 229:
#line 737 "parser.yy"
                                                                              {
        vsk_targeting(yyvsp[-4]);
        yyval = vsk_ast(INSN_INPUT_WAIT_semicolon, { yyvsp[-2], nullptr, yyvsp[0] });
    }
#line 5119 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 230:
#line 741 "parser.yy"
                                                                          {
        vsk_targeting(yyvsp[-6]);
        yyval = vsk_ast(INSN_INPUT_WAIT, { yyvsp[-4], yyvsp[-2], yyvsp[0] });
    }
#line 5128 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 231:
#line 745 "parser.yy"
                                                                          {
        vsk_targeting(yyvsp[-4]);
        yyval = vsk_ast(INSN_INPUT_WAIT, { yyvsp[-2], nullptr, yyvsp[0] });
    }
#line 5137 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 232:
#line 749 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_LSET, { yyvsp[-2], yyvsp[0] }); }
#line 5143 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 233:
#line 750 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_RSET, { yyvsp[-2], yyvsp[0] }); }
#line 5149 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 234:
#line 751 "parser.yy"
                                                        { vsk_targeting(yyvsp[-2]); yyval = vsk_ast(INSN_TIME_dollar, { yyvsp[0] }); }
#line 5155 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 235:
#line 752 "parser.yy"
                                                        { vsk_targeting(yyvsp[-2]); yyval = vsk_ast(INSN_DATE_dollar, { yyvsp[0] }); }
#line 5161 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 236:
#line 753 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_DELETE, { yyvsp[0] }); }
#line 5167 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 237:
#line 754 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_RESUME, { yyvsp[0] }); }
#line 5173 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 238:
#line 755 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_RESUME, { yyvsp[0] }); }
#line 5179 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 239:
#line 756 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_RESUME);}
#line 5185 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 240:
#line 758 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_GET_sharp, { yyvsp[-2], yyvsp[0] }); }
#line 5191 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 241:
#line 759 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_GET_sharp, { yyvsp[0], nullptr }); }
#line 5197 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 242:
#line 760 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_GET_sharp, { yyvsp[-2], yyvsp[0] }); }
#line 5203 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 243:
#line 761 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_GET_sharp, { yyvsp[0], nullptr }); }
#line 5209 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 244:
#line 763 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_PUT_sharp, { yyvsp[-2], yyvsp[0] });}
#line 5215 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 245:
#line 764 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_PUT_sharp, { yyvsp[0], nullptr });}
#line 5221 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 246:
#line 765 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_PUT_sharp, { yyvsp[-2], yyvsp[0] });}
#line 5227 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 247:
#line 766 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_PUT_sharp, { yyvsp[0], nullptr });}
#line 5233 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 248:
#line 768 "parser.yy"
                                                                                                                                                        {
        vsk_targeting(yyvsp[-14]);
        yyval = vsk_ast(INSN_GET_at_STEP, { yyvsp[-12], yyvsp[-10], yyvsp[-5], yyvsp[-3], yyvsp[0] });
    }
#line 5242 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 249:
#line 773 "parser.yy"
                                                                                                                                                        {
        vsk_targeting(yyvsp[-13]);
        yyval = vsk_ast(INSN_GET_at, { yyvsp[-11], yyvsp[-9], yyvsp[-5], yyvsp[-3], yyvsp[0] });
    }
#line 5251 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 250:
#line 777 "parser.yy"
                                                                                                                                                                                    {
        // PUT@(50,50),KANJI(...),OP,color1,color2
        vsk_targeting(yyvsp[-16]);
        yyval = vsk_ast(INSN_PUT_at_KANJI, { yyvsp[-14], yyvsp[-12], yyvsp[-7], yyvsp[-4], yyvsp[-2], yyvsp[0] });
    }
#line 5261 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 251:
#line 782 "parser.yy"
                                                                                                                                                                      {
        // PUT@(50,50),KANJI(...),,color1,color2
        vsk_targeting(yyvsp[-15]);
        yyval = vsk_ast(INSN_PUT_at_KANJI, { yyvsp[-13], yyvsp[-11], yyvsp[-6], yyvsp[-3], yyvsp[-2], yyvsp[0] });
    }
#line 5271 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 252:
#line 787 "parser.yy"
                                                                                                                                            {
        // PUT@(50,50),KANJI(...),OP
        vsk_targeting(yyvsp[-12]);
        yyval = vsk_ast(INSN_PUT_at_KANJI, { yyvsp[-10], yyvsp[-8], yyvsp[-3], yyvsp[0] });
    }
#line 5281 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 253:
#line 792 "parser.yy"
                                                                                                                     {
        // PUT@(50,50),KANJI(...)
        vsk_targeting(yyvsp[-10]);
        yyval = vsk_ast(INSN_PUT_at_KANJI, { yyvsp[-8], yyvsp[-6], yyvsp[-1] });
    }
#line 5291 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 254:
#line 797 "parser.yy"
                                                                                                                                                 {
        vsk_targeting(yyvsp[-13]);
        yyval = vsk_ast(INSN_PUT_at, { yyvsp[-11], yyvsp[-9], yyvsp[-6], yyvsp[-4], yyvsp[-2], yyvsp[0] });
    }
#line 5300 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 255:
#line 801 "parser.yy"
                                                                                                         {
        vsk_targeting(yyvsp[-9]);
        yyval = vsk_ast(INSN_PUT_at, { yyvsp[-7], yyvsp[-5], yyvsp[-2], yyvsp[0] });
    }
#line 5309 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 256:
#line 805 "parser.yy"
                                                                                  {
        vsk_targeting(yyvsp[-7]);
        yyval = vsk_ast(INSN_PUT_at, { yyvsp[-5], yyvsp[-3], yyvsp[0] });
    }
#line 5318 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 257:
#line 810 "parser.yy"
                                                                                                             {
        vsk_targeting(yyvsp[-9]);
        yyval = vsk_ast(INSN_CHAIN_MERGE_ALL_DELETE, { yyvsp[-7], yyvsp[-5], yyvsp[0] });
    }
#line 5327 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 258:
#line 814 "parser.yy"
                                                                               {
        vsk_targeting(yyvsp[-6]);
        yyval = vsk_ast(INSN_CHAIN_MERGE_ALL, { yyvsp[-4], yyvsp[-2] });
    }
#line 5336 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 259:
#line 818 "parser.yy"
                                                                                      {
        vsk_targeting(yyvsp[-7]);
        yyval = vsk_ast(INSN_CHAIN_MERGE_DELETE, { yyvsp[-5], yyvsp[-3] });
    }
#line 5345 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 260:
#line 822 "parser.yy"
                                                        {
        vsk_targeting(yyvsp[-4]);
        yyval = vsk_ast(INSN_CHAIN_MERGE, { yyvsp[-2], yyvsp[0] });
    }
#line 5354 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 261:
#line 826 "parser.yy"
                                   {
        vsk_targeting(yyvsp[-2]);
        yyval = vsk_ast(INSN_CHAIN_MERGE, { yyvsp[0] });
    }
#line 5363 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 262:
#line 830 "parser.yy"
                                                 {
        vsk_targeting(yyvsp[-3]);
        yyval = vsk_ast(INSN_CHAIN, { yyvsp[-2], nullptr, yyvsp[0] });
    }
#line 5372 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 263:
#line 834 "parser.yy"
                                                                      {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_CHAIN, { yyvsp[-4], yyvsp[-2], yyvsp[0] });
    }
#line 5381 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 264:
#line 838 "parser.yy"
                                               {
        vsk_targeting(yyvsp[-3]);
        yyval = vsk_ast(INSN_CHAIN, { yyvsp[-2], yyvsp[0] });
    }
#line 5390 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 265:
#line 842 "parser.yy"
                          {
        vsk_targeting(yyvsp[-1]);
        yyval = vsk_ast(INSN_CHAIN, { yyvsp[0] });
    }
#line 5399 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 266:
#line 846 "parser.yy"
                                       {
        vsk_targeting(yyvsp[-3]);
        yyval = vsk_ast(INSN_DEF_FN, { yyvsp[-2], nullptr, yyvsp[0] });
    }
#line 5408 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 267:
#line 850 "parser.yy"
                                                             {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_DEF_FN, { yyvsp[-4], nullptr, yyvsp[0] });
    }
#line 5417 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 268:
#line 854 "parser.yy"
                                                                         {
        vsk_targeting(yyvsp[-6]);
        yyval = vsk_ast(INSN_DEF_FN, { yyvsp[-5], yyvsp[-3], yyvsp[0] });
    }
#line 5426 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 269:
#line 858 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_COM_OFF); }
#line 5432 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 270:
#line 859 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_COM_ON); }
#line 5438 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 271:
#line 860 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_COM_STOP); }
#line 5444 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 272:
#line 861 "parser.yy"
                                                        { vsk_targeting(yyvsp[-4]); yyval = vsk_ast(INSN_MOUSE_OFF, { yyvsp[-2] }); }
#line 5450 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 273:
#line 862 "parser.yy"
                                                        { vsk_targeting(yyvsp[-4]); yyval = vsk_ast(INSN_MOUSE_ON, { yyvsp[-2] }); }
#line 5456 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 274:
#line 863 "parser.yy"
                                                        { vsk_targeting(yyvsp[-4]); yyval = vsk_ast(INSN_MOUSE_STOP, { yyvsp[-2] }); }
#line 5462 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 275:
#line 864 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_MOUSE_OFF, { nullptr }); }
#line 5468 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 276:
#line 865 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_MOUSE_ON, { nullptr }); }
#line 5474 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 277:
#line 866 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_MOUSE_STOP, { nullptr }); }
#line 5480 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 278:
#line 867 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_PEN_OFF); }
#line 5486 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 279:
#line 868 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_PEN_ON); }
#line 5492 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 280:
#line 869 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_PEN_STOP); }
#line 5498 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 281:
#line 870 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_PLAY_OFF); }
#line 5504 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 282:
#line 871 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_PLAY_ON); }
#line 5510 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 283:
#line 872 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_PLAY_STOP); }
#line 5516 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 284:
#line 873 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_HELP_OFF); }
#line 5522 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 285:
#line 874 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_HELP_ON); }
#line 5528 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 286:
#line 875 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_HELP_STOP); }
#line 5534 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 287:
#line 876 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_TIME_dollar_OFF); }
#line 5540 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 288:
#line 877 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_TIME_dollar_ON); }
#line 5546 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 289:
#line 878 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_TIME_dollar_STOP); }
#line 5552 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 290:
#line 879 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_STOP_OFF); }
#line 5558 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 291:
#line 880 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_STOP_ON); }
#line 5564 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 292:
#line 881 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_STOP_STOP); }
#line 5570 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 293:
#line 882 "parser.yy"
                                                                            {
        vsk_targeting(yyvsp[-6]);
        yyval = vsk_ast(INSN_POINT_STEP, { yyvsp[-3], yyvsp[-1] });
    }
#line 5579 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 294:
#line 886 "parser.yy"
                                                                            {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_POINT, { yyvsp[-3], yyvsp[-1] });
    }
#line 5588 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 295:
#line 890 "parser.yy"
                                 {
        vsk_targeting(yyvsp[-1]);
        yyval = vsk_ast(INSN_EDIT, { yyvsp[0] });
    }
#line 5597 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 296:
#line 894 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_TROFF); }
#line 5603 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 297:
#line 895 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_TRON); }
#line 5609 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 298:
#line 896 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_LIST, { yyvsp[0] }); }
#line 5615 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 299:
#line 897 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_LIST); }
#line 5621 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 300:
#line 898 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_LLIST, { yyvsp[0] }); }
#line 5627 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 301:
#line 899 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_LLIST); }
#line 5633 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 302:
#line 900 "parser.yy"
                                                                     {
        vsk_targeting(yyvsp[-3]);
        yyvsp[0]->insert(yyvsp[0]->begin(), yyvsp[-2]);
        yyval = vsk_ast(INSN_CLOSE, { yyvsp[0] });
    }
#line 5643 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 303:
#line 905 "parser.yy"
                                {
        vsk_targeting(yyvsp[-1]);
        yyval = vsk_ast(INSN_CLOSE, { vsk_ast(INSN_FILE_NUMBERS, { yyvsp[0] }) });
    }
#line 5652 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 304:
#line 909 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_CLOSE, { yyvsp[0] }); }
#line 5658 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 305:
#line 910 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CLOSE, { nullptr }); }
#line 5664 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 306:
#line 911 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_RUN, { yyvsp[0], nullptr, nullptr }); }
#line 5670 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 307:
#line 912 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_RUN, { nullptr, yyvsp[-2], yyvsp[0] }); }
#line 5676 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 308:
#line 913 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_RUN, { nullptr, yyvsp[0], nullptr }); }
#line 5682 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 309:
#line 914 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_RUN, { nullptr, nullptr, nullptr }); }
#line 5688 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 310:
#line 915 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_LOAD, { yyvsp[-2], yyvsp[0] }); }
#line 5694 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 311:
#line 916 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_LOAD, { yyvsp[0], nullptr }); }
#line 5700 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 312:
#line 917 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_RESTORE, { yyvsp[0] }); }
#line 5706 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 313:
#line 918 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_RESTORE); }
#line 5712 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 314:
#line 919 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_ERASE, { yyvsp[0] }); }
#line 5718 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 315:
#line 920 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_SWAP, { yyvsp[-2], yyvsp[0] }); }
#line 5724 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 316:
#line 921 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_STOP); }
#line 5730 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 317:
#line 922 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_FIELD, { yyvsp[-2], yyvsp[0] }); }
#line 5736 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 318:
#line 923 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_FIELD, { yyvsp[-2], yyvsp[0] }); }
#line 5742 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 319:
#line 924 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_FIELD, { yyvsp[-2], yyvsp[0] }); }
#line 5748 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 320:
#line 925 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_RETURN, { yyvsp[0] }); }
#line 5754 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 321:
#line 926 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_RETURN); }
#line 5760 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 322:
#line 927 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_NAME, { yyvsp[-2], yyvsp[-1], yyvsp[0] }); }
#line 5766 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 323:
#line 928 "parser.yy"
                                                                   { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_PLAY, { yyvsp[-2], yyvsp[0] }); }
#line 5772 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 324:
#line 929 "parser.yy"
                                                                   { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_PLAY, { nullptr, yyvsp[0] }); }
#line 5778 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 325:
#line 930 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_AUTO, { yyvsp[-2], yyvsp[0] }); }
#line 5784 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 326:
#line 931 "parser.yy"
                                                        { vsk_targeting(yyvsp[-2]); yyval = vsk_ast(INSN_AUTO, { nullptr, yyvsp[0] }); }
#line 5790 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 327:
#line 932 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_AUTO, { yyvsp[0], nullptr }); }
#line 5796 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 328:
#line 933 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_AUTO, { nullptr, nullptr }); }
#line 5802 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 329:
#line 934 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_WIDTH_sharp, { yyvsp[-2], yyvsp[0] }); }
#line 5808 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 330:
#line 935 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_WIDTH_sharp, { yyvsp[-2], yyvsp[0] }); }
#line 5814 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 331:
#line 936 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = yyvsp[0]; }
#line 5820 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 332:
#line 940 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_DIM_LIST, { yyvsp[0] }); }
#line 5826 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 333:
#line 941 "parser.yy"
                                                        { yyval = yyvsp[-2]; yyval->push_back(yyvsp[0]); }
#line 5832 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 334:
#line 945 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_IDENT_LIST, { yyvsp[0] }); }
#line 5838 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 335:
#line 946 "parser.yy"
                                                        { yyval = yyvsp[-2]; yyval->push_back(yyvsp[0]); }
#line 5844 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 336:
#line 950 "parser.yy"
                            { yyval = yyvsp[0]; }
#line 5850 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 337:
#line 951 "parser.yy"
                            { yyval = yyvsp[0]; }
#line 5856 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 338:
#line 955 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_PRINTING, { yyvsp[0] }); }
#line 5862 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 339:
#line 956 "parser.yy"
                                                        { yyval = yyvsp[-1]; yyval->push_back(yyvsp[0]); }
#line 5868 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 340:
#line 960 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_PRINTING, { yyvsp[0] }); }
#line 5874 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 341:
#line 961 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = yyvsp[-1]; yyval->push_back(yyvsp[0]); }
#line 5880 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 342:
#line 962 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = yyvsp[-1]; yyval->push_back(vsk_ast(INSN_COMMA)); }
#line 5886 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 343:
#line 963 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = yyvsp[-1]; yyval->push_back(vsk_ast(INSN_SEMICOLON)); }
#line 5892 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 344:
#line 967 "parser.yy"
                            { yyval = yyvsp[0]; }
#line 5898 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 345:
#line 968 "parser.yy"
                            { yyval = yyvsp[0]; }
#line 5904 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 346:
#line 972 "parser.yy"
                            { yyval = yyvsp[0]; }
#line 5910 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 347:
#line 973 "parser.yy"
                            { yyval = yyvsp[0]; }
#line 5916 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 348:
#line 977 "parser.yy"
                                                { yyval = yyvsp[0]; }
#line 5922 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 349:
#line 978 "parser.yy"
                                                { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_SPC, { yyvsp[-1] });}
#line 5928 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 350:
#line 979 "parser.yy"
                                                { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_TAB, { yyvsp[-1] });}
#line 5934 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 351:
#line 980 "parser.yy"
                                                { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_COMMA); }
#line 5940 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 352:
#line 981 "parser.yy"
                                                { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_SEMICOLON); }
#line 5946 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 353:
#line 985 "parser.yy"
                                                { yyval = yyvsp[0]; }
#line 5952 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 354:
#line 986 "parser.yy"
                                                { yyval = yyvsp[0]; }
#line 5958 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 355:
#line 990 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_BEEP); }
#line 5964 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 356:
#line 991 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_BLOAD); }
#line 5970 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 357:
#line 992 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_BSAVE); }
#line 5976 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 358:
#line 993 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CALL); }
#line 5982 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 359:
#line 994 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CHILD); }
#line 5988 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 360:
#line 995 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CLEAR); }
#line 5994 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 361:
#line 996 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CLS); }
#line 6000 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 362:
#line 997 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_COLOR); }
#line 6006 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 363:
#line 998 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_COMMON); }
#line 6012 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 364:
#line 999 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CONSOLE); }
#line 6018 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 365:
#line 1000 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CONT); }
#line 6024 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 366:
#line 1001 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_COPY); }
#line 6030 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 367:
#line 1002 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_DATA); }
#line 6036 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 368:
#line 1003 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_DEFDBL); }
#line 6042 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 369:
#line 1004 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_DEFINT); }
#line 6048 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 370:
#line 1005 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_DEFSNG); }
#line 6054 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 371:
#line 1006 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_DEFSTR); }
#line 6060 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 372:
#line 1007 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_DRAW); }
#line 6066 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 373:
#line 1008 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_DSKO_dollar); }
#line 6072 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 374:
#line 1009 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_END); }
#line 6078 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 375:
#line 1010 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_ERROR); }
#line 6084 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 376:
#line 1011 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_FILES); }
#line 6090 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 377:
#line 1012 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_KEY); }
#line 6096 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 378:
#line 1013 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_KEY_LIST); }
#line 6102 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 379:
#line 1014 "parser.yy"
                                                        { vsk_targeting(yyvsp[-4]); yyval = vsk_ast(INSN_KEY_OFF, { yyvsp[-2] }); }
#line 6108 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 380:
#line 1015 "parser.yy"
                                                        { vsk_targeting(yyvsp[-4]); yyval = vsk_ast(INSN_KEY_ON, { yyvsp[-2] }); }
#line 6114 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 381:
#line 1016 "parser.yy"
                                                        { vsk_targeting(yyvsp[-4]); yyval = vsk_ast(INSN_KEY_STOP, { yyvsp[-2] }); }
#line 6120 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 382:
#line 1017 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_KEY_OFF); }
#line 6126 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 383:
#line 1018 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_KEY_ON); }
#line 6132 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 384:
#line 1019 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_KEY_STOP); }
#line 6138 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 385:
#line 1020 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_KILL); }
#line 6144 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 386:
#line 1021 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_KPLOAD); }
#line 6150 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 387:
#line 1022 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_LFILES); }
#line 6156 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 388:
#line 1023 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_LOAD_question); }
#line 6162 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 389:
#line 1024 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_LOCATE); }
#line 6168 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 390:
#line 1025 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_MERGE); }
#line 6174 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 391:
#line 1026 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_MON); }
#line 6180 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 392:
#line 1027 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_MOTOR); }
#line 6186 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 393:
#line 1028 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_MOUSE_stmt); }
#line 6192 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 394:
#line 1029 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_NEW); }
#line 6198 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 395:
#line 1030 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_NEW_CMD); }
#line 6204 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 396:
#line 1031 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_NEW_ON); }
#line 6210 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 397:
#line 1032 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_OPTION_IDENT, { yyvsp[0] }); }
#line 6216 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 398:
#line 1033 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_OUT); }
#line 6222 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 399:
#line 1034 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_PLAY_ALLOC); }
#line 6228 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 400:
#line 1035 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_PLAY); }
#line 6234 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 401:
#line 1036 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_POKE); }
#line 6240 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 402:
#line 1037 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_RANDOMIZE); }
#line 6246 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 403:
#line 1038 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_READ); }
#line 6252 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 404:
#line 1039 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_RENUM); }
#line 6258 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 405:
#line 1040 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_ROLL); }
#line 6264 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 406:
#line 1041 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_SAVE); }
#line 6270 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 407:
#line 1042 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_SCREEN); }
#line 6276 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 408:
#line 1043 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_SET); }
#line 6282 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 409:
#line 1044 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_SET); }
#line 6288 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 410:
#line 1045 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_SYSTEM); }
#line 6294 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 411:
#line 1046 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_TERM); }
#line 6300 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 412:
#line 1047 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_WAIT); }
#line 6306 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 413:
#line 1048 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_WEND); }
#line 6312 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 414:
#line 1049 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_WHILE); }
#line 6318 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 415:
#line 1050 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_WIDTH); }
#line 6324 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 416:
#line 1051 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CHDIR); }
#line 6330 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 417:
#line 1052 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_MKDIR); }
#line 6336 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 418:
#line 1053 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_RMDIR); }
#line 6342 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 419:
#line 1054 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_WIDTH_LPRINT); }
#line 6348 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 420:
#line 1055 "parser.yy"
                                                                                                             {
        vsk_targeting(yyvsp[-9]);
        yyval = vsk_ast(INSN_MID_dollar_stmt, { yyvsp[-7], yyvsp[-5], yyvsp[-3], yyvsp[0] });
    }
#line 6357 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 421:
#line 1059 "parser.yy"
                                                                                                {
        vsk_targeting(yyvsp[-7]);
        yyval = vsk_ast(INSN_MID_dollar_stmt, { yyvsp[-5], yyvsp[-3], nullptr, yyvsp[0] });
    }
#line 6366 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 422:
#line 1066 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_INPUT_sharp, { yyvsp[0] });}
#line 6372 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 423:
#line 1067 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_INPUT_sharp, { yyvsp[0] });}
#line 6378 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 424:
#line 1068 "parser.yy"
                                                                                    {
        // LINE -STEP(100,100) likely
        vsk_targeting(yyvsp[-7]);
        yyval = vsk_ast(INSN_LINE1, { nullptr, nullptr, yyvsp[-3], yyvsp[-1] });
    }
#line 6388 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 425:
#line 1073 "parser.yy"
                                                                            {
        // LINE -(100,100) likely
        vsk_targeting(yyvsp[-6]);
        yyval = vsk_ast(INSN_LINE0, { nullptr, nullptr, yyvsp[-3], yyvsp[-1] });
    }
#line 6398 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 426:
#line 1078 "parser.yy"
                                                                                                                                                 {
        // LINE STEP(0,0)-STEP(100,100) likely
        vsk_targeting(yyvsp[-13]);
        yyval = vsk_ast(INSN_LINE3, { yyvsp[-10], yyvsp[-8], yyvsp[-3], yyvsp[-1] });
    }
#line 6408 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 427:
#line 1083 "parser.yy"
                                                                                                                                         {
        // LINE STEP(0,0)-(100,100) likely
        vsk_targeting(yyvsp[-12]);
        yyval = vsk_ast(INSN_LINE2, { yyvsp[-9], yyvsp[-7], yyvsp[-3], yyvsp[-1] });
    }
#line 6418 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 428:
#line 1088 "parser.yy"
                                                                                                                                         {
        // LINE(0,0)-STEP(100,100) likely
        vsk_targeting(yyvsp[-12]);
        yyval = vsk_ast(INSN_LINE1, { yyvsp[-10], yyvsp[-8], yyvsp[-3], yyvsp[-1] });
    }
#line 6428 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 429:
#line 1093 "parser.yy"
                                                                                                                                 {
        // LINE(0,0)-(100,100) likely
        vsk_targeting(yyvsp[-11]);
        yyval = vsk_ast(INSN_LINE0, { yyvsp[-9], yyvsp[-7], yyvsp[-3], yyvsp[-1] });
    }
#line 6438 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 430:
#line 1098 "parser.yy"
                                                                                         {
        vsk_targeting(yyvsp[-7]);
        yyval = vsk_ast(INSN_CIRCLE, { yyvsp[-5], yyvsp[-3], yyvsp[0] });
    }
#line 6447 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 431:
#line 1102 "parser.yy"
                                                                                                 {
        vsk_targeting(yyvsp[-8]);
        yyval = vsk_ast(INSN_CIRCLE_STEP, { yyvsp[-5], yyvsp[-3], yyvsp[0] });
    }
#line 6456 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 432:
#line 1106 "parser.yy"
                                                                           {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_PSET, { yyvsp[-3], yyvsp[-1] });
    }
#line 6465 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 433:
#line 1110 "parser.yy"
                                                                           {
        vsk_targeting(yyvsp[-6]);
        yyval = vsk_ast(INSN_PSET_STEP, { yyvsp[-3], yyvsp[-1] });
    }
#line 6474 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 434:
#line 1114 "parser.yy"
                                                                             {
        vsk_targeting(yyvsp[-6]);
        yyval = vsk_ast(INSN_PRESET_STEP, { yyvsp[-3], yyvsp[-1] });
    }
#line 6483 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 435:
#line 1118 "parser.yy"
                                                                             {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_PRESET, { yyvsp[-3], yyvsp[-1] });
    }
#line 6492 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 436:
#line 1122 "parser.yy"
                                                                            {
        vsk_targeting(yyvsp[-6]);
        yyval = vsk_ast(INSN_PAINT_STEP, { yyvsp[-3], yyvsp[-1] });
    }
#line 6501 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 437:
#line 1126 "parser.yy"
                                                                            {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_PAINT, { yyvsp[-3], yyvsp[-1] });
    }
#line 6510 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 438:
#line 1130 "parser.yy"
                                                                             {
        vsk_targeting(yyvsp[-6]);
        yyval = vsk_ast(INSN_COLOR_equal, { yyvsp[-3], yyvsp[-1] });
    }
#line 6519 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 439:
#line 1136 "parser.yy"
    {
        vsk_targeting(yyvsp[-11]);
        yyval = vsk_ast(INSN_COLOR_at, { yyvsp[-9], yyvsp[-7], yyvsp[-3], yyvsp[-1] });
    }
#line 6528 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 440:
#line 1140 "parser.yy"
                                                                                                                                 {
        vsk_targeting(yyvsp[-11]);
        yyval = vsk_ast(INSN_VIEW_stmt, { yyvsp[-9], yyvsp[-7], yyvsp[-3], yyvsp[-1] });
    }
#line 6537 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 441:
#line 1144 "parser.yy"
                                                                                                                                   {
        vsk_targeting(yyvsp[-11]);
        yyval = vsk_ast(INSN_WINDOW_stmt, { yyvsp[-9], yyvsp[-7], yyvsp[-3], yyvsp[-1] });
    }
#line 6546 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 442:
#line 1151 "parser.yy"
                                                                           {
        vsk_targeting(yyvsp[-2]);
        auto go_to_0 = vsk_ast_goto(yyvsp[-2]);
        vsk_targeting(yyvsp[0]);
        auto go_to_1 = vsk_ast_goto(yyvsp[0]);
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-4], go_to_0, go_to_1 });
    }
#line 6559 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 443:
#line 1159 "parser.yy"
                                                                           {
        vsk_targeting(yyvsp[-2]);
        auto go_to_0 = vsk_ast_goto(yyvsp[-2]);
        vsk_targeting(yyvsp[0]);
        auto go_to_1 = vsk_ast_goto(yyvsp[0]);
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-4], go_to_0, go_to_1 });
    }
#line 6572 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 444:
#line 1167 "parser.yy"
                                                                           {
        vsk_targeting(yyvsp[-2]);
        auto go_to = vsk_ast_goto(yyvsp[-2]);
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-4], go_to, yyvsp[0] });
    }
#line 6583 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 445:
#line 1173 "parser.yy"
                                                                           {
        vsk_targeting(yyvsp[0]);
        auto go_to = vsk_ast_goto(yyvsp[0]);
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-4], yyvsp[-2], go_to });
    }
#line 6594 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 446:
#line 1179 "parser.yy"
                                                                           {
        vsk_targeting(yyvsp[0]);
        auto go_to = vsk_ast_goto(yyvsp[0]);
        vsk_targeting(yyvsp[-4]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-3], vsk_ast(INSN_MULTI), go_to });
    }
#line 6605 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 447:
#line 1185 "parser.yy"
                                                                           {
        vsk_targeting(yyvsp[-4]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-3], vsk_ast(INSN_MULTI), yyvsp[0] });
    }
#line 6614 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 448:
#line 1189 "parser.yy"
                                                                           {
        vsk_targeting(yyvsp[-2]);
        auto go_to = vsk_ast_goto(yyvsp[-2]);
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-4], go_to, yyvsp[0] });
    }
#line 6625 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 449:
#line 1195 "parser.yy"
                                                                           {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-4], yyvsp[-2], yyvsp[0] });
    }
#line 6634 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 450:
#line 1199 "parser.yy"
                                                                           {
        vsk_targeting(yyvsp[-4]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-3], yyvsp[-1], vsk_ast(INSN_MULTI) });
    }
#line 6643 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 451:
#line 1203 "parser.yy"
                                                                           {
        vsk_targeting(yyvsp[-3]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-2], vsk_ast(INSN_MULTI), vsk_ast(INSN_MULTI) });
    }
#line 6652 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 452:
#line 1210 "parser.yy"
                                                                             {
        vsk_targeting(yyvsp[-2]);
        auto go_to = vsk_ast_goto(yyvsp[-2]);
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-4], go_to, yyvsp[0] });
    }
#line 6663 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 453:
#line 1216 "parser.yy"
                                                                             {
        vsk_targeting(yyvsp[-2]);
        auto go_to = vsk_ast_goto(yyvsp[-2]);
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-4], go_to, yyvsp[0] });
    }
#line 6674 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 454:
#line 1222 "parser.yy"
                                                                             {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-4], yyvsp[-2], yyvsp[0] });
    }
#line 6683 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 455:
#line 1226 "parser.yy"
                                                                             {
        vsk_targeting(yyvsp[-4]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-3], vsk_ast(INSN_MULTI), yyvsp[0] });
    }
#line 6692 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 456:
#line 1230 "parser.yy"
                                                                             {
        vsk_targeting(yyvsp[0]);
        auto go_to = vsk_ast_goto(yyvsp[0]);
        vsk_targeting(yyvsp[-3]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-2], go_to, nullptr });
    }
#line 6703 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 457:
#line 1236 "parser.yy"
                                                                             {
        vsk_targeting(yyvsp[-3]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-2], yyvsp[0], nullptr });
    }
#line 6712 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 458:
#line 1240 "parser.yy"
                                                                             {
        vsk_targeting(yyvsp[-2]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-1], vsk_ast(INSN_MULTI), nullptr });
    }
#line 6721 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 459:
#line 1244 "parser.yy"
                                                                             {
        vsk_targeting(yyvsp[0]);
        auto go_to = vsk_ast_goto(yyvsp[0]);
        vsk_targeting(yyvsp[-3]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-2], go_to, nullptr });
    }
#line 6732 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 460:
#line 1253 "parser.yy"
                                                   {
        vsk_targeting(yyvsp[-2]);
        yyval = vsk_ast_multi(yyvsp[-2], yyvsp[0]);
    }
#line 6741 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 461:
#line 1257 "parser.yy"
                                 {
        yyval = yyvsp[0];
    }
#line 6749 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 462:
#line 1260 "parser.yy"
                           {
        yyval = yyvsp[0];
    }
#line 6757 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 463:
#line 1263 "parser.yy"
                        {
        yyval = yyvsp[0];
    }
#line 6765 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 464:
#line 1266 "parser.yy"
                                 {
        yyval = yyvsp[-1];
    }
#line 6773 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 465:
#line 1272 "parser.yy"
                                                     {
        yyval = vsk_ast_multi(yyvsp[-2], yyvsp[0]);
    }
#line 6781 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 466:
#line 1275 "parser.yy"
                                   {
        vsk_targeting(yyvsp[-1]); yyval = yyvsp[0];
    }
#line 6789 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 467:
#line 1278 "parser.yy"
                             {
        yyval = yyvsp[0];
    }
#line 6797 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 468:
#line 1281 "parser.yy"
                                   {
        yyval = yyvsp[-1];
    }
#line 6805 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 469:
#line 1287 "parser.yy"
                           { yyval = yyvsp[0]; }
#line 6811 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 470:
#line 1288 "parser.yy"
                           { yyval = yyvsp[0]; }
#line 6817 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 471:
#line 1289 "parser.yy"
                           { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_MULTI); }
#line 6823 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 472:
#line 1293 "parser.yy"
                                { yyval = yyvsp[0]; }
#line 6829 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 473:
#line 1294 "parser.yy"
                                { vsk_targeting(yyvsp[0]); yyval = yyval = vsk_ast(INSN_LABEL, { vsk_ast(INSN_PERIOD) }); }
#line 6835 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 474:
#line 1298 "parser.yy"
                  {
        vsk_targeting(yyvsp[0]);
        yyval = vsk_ast(INSN_LINE_NUMBERS, { yyvsp[0] });
    }
#line 6844 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 475:
#line 1302 "parser.yy"
                                      {
        yyval = yyvsp[-2];
        yyval->insert(yyvsp[-2]->end(), yyvsp[-1]->begin(), yyvsp[-1]->end());
        yyval->push_back(yyvsp[0]);
    }
#line 6854 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 476:
#line 1307 "parser.yy"
                         {
        vsk_targeting(yyvsp[-1]);
        yyval = vsk_ast(INSN_LINE_NUMBERS, { nullptr });
        yyval->insert(yyval->end(), yyvsp[-1]->begin(), yyvsp[-1]->end());
        yyval->push_back(yyvsp[0]);
    }
#line 6865 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 477:
#line 1316 "parser.yy"
                                         { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_COMMAS); }
#line 6871 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 478:
#line 1317 "parser.yy"
                                         { yyval = yyvsp[-1]; yyval->push_back(nullptr); }
#line 6877 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 479:
#line 1321 "parser.yy"
                                                     { vsk_targeting(yyvsp[-2]); yyval = vsk_ast(INSN_LINE_RANGE, { yyvsp[-2], yyvsp[0] }); }
#line 6883 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 480:
#line 1322 "parser.yy"
                                                     { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_LINE_RANGE, { yyvsp[-1], nullptr }); }
#line 6889 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 481:
#line 1323 "parser.yy"
                                                     { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_LINE_RANGE, { nullptr, yyvsp[0] }); }
#line 6895 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 482:
#line 1324 "parser.yy"
                                                     { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_LINE_RANGE, { yyvsp[0], yyvsp[0] }); }
#line 6901 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 483:
#line 1328 "parser.yy"
                                         { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_DIRTY_8BIT); }
#line 6907 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 484:
#line 1329 "parser.yy"
                                         { yyval = yyvsp[-1]; }
#line 6913 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 485:
#line 1333 "parser.yy"
                            { yyval = yyvsp[0]; }
#line 6919 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 486:
#line 1334 "parser.yy"
                            { yyval = yyvsp[0]; }
#line 6925 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 487:
#line 1335 "parser.yy"
                            { yyval = yyvsp[0]; }
#line 6931 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 488:
#line 1339 "parser.yy"
                                                   { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_PARAM_LIST, { yyvsp[0] }); }
#line 6937 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 489:
#line 1340 "parser.yy"
                                                   { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_PARAM_LIST, { yyvsp[0] }); }
#line 6943 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 490:
#line 1341 "parser.yy"
                                                   { yyval = yyvsp[0]; }
#line 6949 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 491:
#line 1342 "parser.yy"
                                                   { yyval = yyvsp[0]; yyval->insert(yyval->begin(), yyvsp[-2]); }
#line 6955 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 492:
#line 1346 "parser.yy"
                                     {
        vsk_targeting(yyvsp[-2]);
        vsk_target_line = yyvsp[-2]->to_int();
        yyval = vsk_ast_multi(yyvsp[-1], yyvsp[0]);
        yyval->m_program_line = vsk_target_line;
    }
#line 6966 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 493:
#line 1352 "parser.yy"
                          {
        vsk_targeting(yyvsp[-1]);
        vsk_target_line = yyvsp[-1]->to_int();
        yyval = yyvsp[0];
        yyval->m_program_line = vsk_target_line;
    }
#line 6977 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 494:
#line 1358 "parser.yy"
                           {
        vsk_targeting(yyvsp[-1]);
        yyval = vsk_ast_multi(yyvsp[-1], yyvsp[0]);
    }
#line 6986 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 495:
#line 1362 "parser.yy"
                {
        yyval = yyvsp[0];
    }
#line 6994 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 496:
#line 1368 "parser.yy"
                                { yyval = yyvsp[-1]; result = yyval; }
#line 7000 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 497:
#line 1369 "parser.yy"
                                { yyval = yyvsp[0]; result = yyval; }
#line 7006 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 498:
#line 1370 "parser.yy"
                                { yyval = yyvsp[0]; result = yyval; }
#line 7012 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 499:
#line 1371 "parser.yy"
                                { yyval = vsk_ast(INSN_MULTI); }
#line 7018 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;


#line 7022 "C:/dev/VeySickProject/VeySicK/parser.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (result, yyscanner, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (result, yyscanner, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, result, yyscanner);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, result, yyscanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (result, yyscanner, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, result, yyscanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp, result, yyscanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
