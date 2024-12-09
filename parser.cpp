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

    #include "coreapi.h"
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
#define YYLAST   7214

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  260
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  58
/* YYNRULES -- Number of rules.  */
#define YYNRULES  498
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  971

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
     703,   704,   705,   709,   713,   717,   718,   719,   720,   721,
     722,   723,   724,   725,   726,   727,   728,   732,   736,   740,
     744,   745,   746,   747,   748,   749,   750,   751,   753,   754,
     755,   756,   758,   759,   760,   761,   763,   768,   772,   777,
     782,   787,   792,   796,   800,   805,   809,   813,   817,   821,
     825,   829,   833,   837,   841,   845,   849,   853,   854,   855,
     856,   857,   858,   859,   860,   861,   862,   863,   864,   865,
     866,   867,   868,   869,   870,   871,   872,   873,   874,   875,
     876,   877,   881,   885,   889,   890,   891,   892,   893,   894,
     895,   900,   904,   905,   906,   907,   908,   909,   910,   911,
     912,   913,   914,   915,   916,   917,   918,   919,   920,   921,
     922,   923,   924,   925,   926,   927,   928,   929,   930,   931,
     935,   936,   940,   941,   945,   946,   950,   951,   955,   956,
     957,   958,   962,   963,   967,   968,   972,   973,   974,   975,
     976,   980,   981,   985,   986,   987,   988,   989,   990,   991,
     992,   993,   994,   995,   996,   997,   998,   999,  1000,  1001,
    1002,  1003,  1004,  1005,  1006,  1007,  1008,  1009,  1010,  1011,
    1012,  1013,  1014,  1015,  1016,  1017,  1018,  1019,  1020,  1021,
    1022,  1023,  1024,  1025,  1026,  1027,  1028,  1029,  1030,  1031,
    1032,  1033,  1034,  1035,  1036,  1037,  1038,  1039,  1040,  1041,
    1042,  1043,  1044,  1045,  1046,  1047,  1048,  1049,  1050,  1054,
    1061,  1062,  1063,  1068,  1073,  1078,  1083,  1088,  1093,  1097,
    1101,  1105,  1109,  1113,  1117,  1121,  1125,  1129,  1135,  1139,
    1146,  1154,  1162,  1168,  1174,  1180,  1184,  1190,  1194,  1198,
    1205,  1211,  1217,  1221,  1225,  1231,  1235,  1239,  1248,  1252,
    1255,  1258,  1261,  1267,  1270,  1273,  1276,  1282,  1283,  1284,
    1288,  1289,  1293,  1297,  1302,  1311,  1312,  1316,  1317,  1318,
    1319,  1323,  1324,  1328,  1329,  1330,  1334,  1335,  1336,  1337,
    1338,  1342,  1348,  1354,  1358,  1364,  1365,  1366,  1367
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

#define YYPACT_NINF (-674)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-200)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    5956,    25,    86,  -674,  -674,  -674,  -674,  3794,  -674,  -674,
     -71,  -674,  4034,  5234,  -674,    54,  6706,    43,   -60,   -80,
    -674,  -674,  -674,  -674,  -674,  -674,    47,   -55,  -674,  -674,
    -674,  -674,    57,  6956,    37,  -674,  -674,  -674,    34,  -674,
      50,  -674,  5234,  4034,  5234,  -674,    37,   -38,  -674,   138,
     -99,  -674,  -674,   -41,   122,  5234,    20,   156,   101,  -674,
      37,  -674,    37,  -674,     3,    57,    57,  4274,  -674,  1844,
      37,  -674,    74,  -674,  -674,  -674,   -64,  5234,    27,    37,
    1110,  5234,   158,  -674,   -69,   -39,  1357,   -67,  -674,   -61,
    -674,   202,   -53,   -38,  -674,   205,  -674,  -674,  -674,  -674,
      89,    68,    89,  -674,  -674,    37,     8,  -674,  -674,  -674,
    -674,    75,    37,  -674,  -674,   -49,  -674,  -674,   130,  -674,
    -674,  -674,   -68,   224,   140,  2091,   231,   234,   154,   159,
    -674,  1597,    89,    89,  4514,   271,  -674,  -674,   283,   287,
     284,   261,   160,   321,  -674,   227,  5234,  -674,   290,  -674,
    -674,  -674,  -674,  -674,  -674,  -674,  -674,  -674,  -674,  -674,
    -674,  -674,  -674,  -674,  -674,  -674,  -674,   181,  -674,  -674,
    -674,  -674,  -674,  -674,   183,  -674,  -674,  -674,  -674,  -674,
     184,  -674,  -674,  -674,  -674,  -674,  -674,  -674,  -674,  -674,
    -674,  -674,  -674,  -674,   185,   188,  -674,  -674,  5234,  -674,
    5234,  -674,  5714,  -674,  -674,  -674,  -674,  5474,  -674,  -674,
    -674,  -674,  5714,  -674,  -674,  -674,   189,   190,  -674,  -674,
    -674,  -674,  -674,  -674,  -674,  -674,  -674,  -674,  -674,   191,
    -674,  -674,  -674,  -674,     6,  -674,   192,   239,  -674,     5,
     325,   186,   -40,   -10,  -674,   332,   169,    83,   242,   275,
     310,  5234,   201,  5714,  -674,   312,  -674,   313,  -674,  -674,
    -674,  2331,  6706,   283,   287,   204,  5234,  -674,  -674,  -674,
    5234,    21,   282,   285,    34,  -674,  -674,   206,  -674,   315,
    -674,   317,  -674,  -674,   319,  -674,   320,   322,   323,   291,
     326,   327,  -674,  -674,  -674,  -674,  -674,  5234,  5234,   -20,
     -12,  5234,  -674,  -674,   329,  -674,  -674,  5234,  -674,  -674,
    -674,  -674,   292,  3305,   311,  5234,   -52,   221,  -674,  -674,
    -674,   335,  -674,  -674,   228,   229,  5234,  -674,  3065,  -674,
     304,   280,  5234,  -674,  -674,  -674,   281,  -674,  -674,   329,
     182,   187,   182,   182,    48,   182,   182,   182,   314,   193,
     177,  -674,  5234,   235,  -674,  -674,  -674,  -674,  -674,  -674,
    -674,  -674,   344,   348,  -674,  4754,  5234,   240,  5234,   241,
     349,  5234,   243,   352,   354,  -674,  -674,  -674,  -674,   330,
     355,  -674,  -674,  -674,  -674,   356,  5234,  -674,  -674,  -674,
    5234,  -674,   359,   364,  5234,   365,  3065,   366,  5234,  5234,
    5234,  5234,   368,  3065,  -674,  -674,   348,  4514,  6706,  -674,
    -674,  -674,  -674,  -674,  -674,  -674,  5234,  4034,  4034,  5234,
    4034,  4034,   196,   370,   239,   -10,   239,  5234,   316,    37,
    -674,  -674,  -674,  -674,  -674,  4994,  5714,  5474,  5474,  5474,
    5474,  5474,  5474,  5474,  5474,  5474,  5474,  5474,  5474,  5234,
    5234,  5234,  5234,  5234,    58,   372,  5234,  -674,  4034,  4034,
    -674,  -674,  -674,   374,   348,  -674,  5234,   375,  -674,  5234,
     -43,  5234,  5234,  -674,    34,  -674,    37,   318,  5234,  5234,
    5234,  5234,  5234,  5234,   -11,  -674,   -22,   172,  6206,    89,
      37,    37,    -7,    37,   203,  5234,  5234,   379,    55,    -5,
     381,   385,  5234,   276,  5234,   328,  5234,  5234,   210,  -674,
    5234,    24,   389,   218,  5234,   197,    89,    89,    89,   230,
    5234,    89,    89,    89,    89,   207,   230,   230,    39,  4034,
     393,  5234,  4514,  4754,  -674,  -674,   396,  5234,   400,  5234,
    2571,   401,  5234,  5234,  5234,  5234,   341,    37,  -674,   404,
    5234,  5234,   407,  3065,  3065,  -674,   410,   411,   237,  2818,
     348,   283,   287,  -674,   245,   246,   247,   249,     1,   250,
     251,   253,   254,  -674,    89,   255,   412,    10,  -674,    12,
    -674,  -674,  -674,     5,   325,   186,   186,   -40,   -40,   -40,
     -40,   -40,   -40,  -674,   332,   169,    83,   242,  -674,   413,
    5234,   416,  -674,  -674,   312,  4514,   417,  5234,  -674,   397,
      13,  -674,  -674,  -674,  -674,  -674,   367,  -674,   431,   431,
     431,   233,  -674,  -674,  5234,  -674,  -674,   377,  6456,   402,
      94,  -674,   406,   329,   329,   -46,    37,  -674,    77,  -674,
     440,    37,  -674,  -674,    37,    37,  5234,   442,  5234,   445,
    -674,   273,   277,  5234,  -674,  5234,  5234,    82,  -674,  -674,
    -674,  -674,  -674,   348,   244,   279,  -674,  -674,  -674,  -674,
     182,   348,   348,   386,   392,  -674,  -674,  5234,   457,   348,
    -674,  5234,   459,  5234,   460,  5234,  3065,  5234,   461,  -674,
    -674,  -674,  -674,  -674,  5234,  -674,  -674,  5234,  3065,  3065,
    5234,  5234,  5234,  5234,  3065,  -674,  -674,  -674,  -674,   -38,
    -674,  -674,  -674,  -674,  -674,   463,  -674,  5234,  5234,  -674,
    -674,   403,   293,  5234,   348,  5234,   294,  5234,   437,    37,
    5234,  5234,  -674,  -674,  -674,   283,   287,  6456,  6456,  6456,
      -3,   329,   329,  -674,  -674,  -674,  5234,  -674,  -674,  -674,
     298,  5234,   464,  5234,  -674,  -674,  -674,  3554,   299,   473,
    -674,  -674,  -674,   244,  -674,   182,    89,  4034,  4034,   301,
    5234,   302,  5234,   303,  5234,   300,   306,  5234,   307,   308,
     309,   324,  3554,   305,   333,    79,    14,   336,  -674,   477,
     337,   338,   369,  -674,  5234,  -674,  -674,   295,  -674,   283,
     287,  -674,   283,   287,  -674,   283,   287,    37,    37,    65,
      -5,   371,   340,  5234,   342,  -674,  -674,  -674,   454,  5234,
    -674,    89,  -674,  -674,  -674,  -674,  -674,  -674,   345,  -674,
     346,  -674,   347,  5234,  -674,   350,   376,   378,   489,   380,
    5234,  -674,    57,   490,  5234,  -674,  -674,  5234,   492,  -674,
     384,  -674,  5234,   329,   329,    37,   -51,  -674,   351,   383,
    5234,   358,  -674,  -674,  -674,  -674,  3554,  -674,   390,   395,
      26,    16,  3554,  -674,   480,    17,  -674,  5234,  5234,  -674,
    -674,  5234,   398,  -674,    35,  -674,   470,  5234,  5234,   415,
     496,  5234,   419,    57,  5234,  -674,  -674,   514,   517,  5234,
    5234,   422,  5234,   521,   533,  5234,     4,   538,  5234,  -674,
     373,  5234,  5234,   539,   540,  5234,  -674,  5234,  5234,   387,
    -674,  -674,  -674,  -674,  -674,   541,  5234,   542,  -674,   388,
     391,  5234,  5234,   544,   394,   399,   545,  5234,   409,  5234,
    -674,  -674,   418,   423,  5234,  -674,  -674,    18,   547,   548,
     424,  -674,  -674,   425,  5234,   549,  5234,    37,   558,  -674,
     559,  5234,  -674,  -674,    37,  5234,   562,  -674,  -674,  5234,
    -674
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int16 yydefact[] =
{
     498,     0,   326,   353,   354,   355,   356,     0,   414,   357,
       0,   358,   303,     0,   359,     0,   469,   360,     0,     0,
     165,   361,   362,   363,   364,   365,     0,     0,   366,   367,
     368,   369,     0,     0,     0,   481,   370,   371,     0,   372,
       0,   373,     0,     0,     0,   374,     0,   161,   160,     0,
       0,   344,   342,     0,     9,     0,     0,     0,   375,   383,
       0,   384,     0,   385,     0,   297,   299,     0,   387,   182,
       0,   388,     0,   415,   389,   390,   391,     0,   392,   186,
       0,     0,     0,   396,     0,     0,   398,     0,   399,     0,
     334,     0,     0,   159,   158,     0,   335,   400,   401,   402,
     311,   237,   319,   416,   403,     0,   307,   404,   405,   406,
     407,   314,     0,   408,   409,     0,   294,   295,     0,   410,
     411,   412,   413,     0,     0,   179,     0,     0,     0,     0,
     461,   175,     0,     0,   222,   220,   460,   465,   467,   468,
     494,   329,   496,     0,   166,     0,     0,    12,   325,    58,
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
     263,     0,     0,     0,     3,   302,     4,   301,   483,   485,
     484,   218,     0,   459,   464,     0,     0,   267,   268,   269,
       0,     0,     0,     0,     0,   471,   470,   480,   234,   492,
     330,   200,   293,   332,   312,   497,     0,     0,     0,     0,
     239,   241,   345,   343,   282,   283,   284,     0,     0,     0,
       0,     0,   421,    10,   225,   420,   376,     0,   380,   381,
     382,   197,     0,     0,     0,     0,     0,     0,   296,   298,
     386,   309,   349,   350,     0,     0,     0,   346,   181,   336,
       0,     0,     0,   273,   274,   275,     0,   393,   394,   185,
       0,     0,     0,     0,   100,   103,     0,     0,    29,     0,
       0,   395,     0,     0,   276,   277,   278,   397,   475,   279,
     280,   281,     0,   322,    55,     0,     0,     0,     0,     0,
       0,     0,     0,   243,   245,   310,   235,   236,   318,     0,
     306,   304,   288,   289,   290,     0,     0,   285,   286,   287,
       0,   417,     0,     0,     0,     0,   178,     0,     0,     0,
       0,     0,     0,   174,   216,   215,   221,     0,   462,   466,
     493,   482,   495,     1,    13,   324,     0,     0,     0,     0,
       0,     0,     0,   259,   122,   141,   121,     0,     0,     0,
      23,    22,    20,    21,    14,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     2,     0,     0,
     488,   487,   486,     0,   489,   217,     0,     0,   233,     0,
       0,     0,     0,   479,   478,   491,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    53,     0,     0,   456,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    24,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   337,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   476,    57,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   232,     0,
       0,     0,     0,     0,     0,   168,     0,     0,     0,     0,
     219,   458,   463,   323,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    27,     0,     0,     0,     0,    33,     0,
     119,   124,   125,   127,   129,   132,   131,   138,   137,   136,
     135,   134,   139,   143,   145,   147,   149,   151,   260,   262,
       0,     0,     5,     6,   300,     0,     0,     0,   264,     0,
       0,   201,   202,   477,   331,   333,     0,   163,   316,   315,
     317,     0,   238,   240,     0,     8,     7,     0,   449,   454,
     467,   455,   457,   224,   223,     0,     0,    11,     0,   167,
       0,     0,   352,   351,     0,     0,     0,     0,     0,     0,
     308,     0,     0,     0,   230,     0,     0,     0,   320,   203,
     204,   207,   472,   208,     0,     0,   213,   209,   210,   211,
       0,   205,   206,     0,     0,   191,   192,     0,     0,   321,
      56,     0,     0,     0,     0,     0,   172,     0,     0,   242,
     244,   231,   305,   313,     0,   328,   327,     0,   177,   176,
       0,     0,     0,     0,   173,    45,    46,    49,    50,     0,
      52,    48,    47,    43,    44,   258,    36,     0,     0,    39,
      32,     0,     0,     0,   490,     0,     0,     0,     0,     0,
       0,     0,    54,    13,   444,   445,   453,     0,   448,     0,
       0,   229,   227,   377,   378,   379,     0,   195,   193,   196,
       0,     0,     0,     0,   347,   348,   338,   180,     0,     0,
     270,   271,   272,     0,   474,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   171,     0,     0,     0,     0,     0,   261,     0,
       0,     0,     0,   265,     0,   162,   164,   184,   440,   442,
     450,   443,   447,   452,   441,   446,   451,     0,     0,    24,
       0,     0,     0,     0,     0,   340,   341,   339,     0,     0,
     473,     0,   212,   187,   189,   188,   190,   435,     0,   292,
       0,   433,     0,     0,   430,     0,     0,     0,     0,     0,
       0,    51,     0,   256,     0,    40,    38,     0,     0,   436,
       0,   266,     0,   228,   226,     0,     0,   423,     0,     0,
       0,     0,   214,   434,   291,   432,   169,   431,     0,     0,
       0,     0,   170,   257,     0,     0,   428,     0,     0,   183,
     198,     0,     0,   422,     0,   419,     0,     0,     0,     0,
     254,     0,     0,     0,     0,    41,   429,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   255,
       0,     0,     0,     0,     0,     0,   418,     0,     0,     0,
     153,   154,   157,   156,   155,   253,     0,     0,    42,     0,
       0,     0,     0,     0,     0,     0,   251,     0,     0,     0,
     437,   427,     0,     0,     0,   438,   439,     0,     0,     0,
       0,   426,   425,     0,     0,   250,     0,     0,     0,   424,
       0,     0,   252,   247,     0,     0,     0,   246,   249,     0,
     248
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -674,   -25,   141,     0,   -73,    97,  -674,  -674,  -674,  -244,
    -235,  -126,  -674,    52,  -142,   162,   163,  -144,  -154,   405,
     155,   161,   157,   153,   194,  -674,   171,  -338,  -674,  -674,
    -120,  -170,  -674,  -674,  -674,  -674,  -110,  -673,  -197,  -305,
    -323,  -185,  -674,  -674,  -674,  -674,    -6,    11,   -32,   -34,
    -215,  -356,   -63,  -674,  -674,  -674,  -674,  -674
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   254,   255,   232,   304,   276,   233,   234,   434,   235,
     484,   363,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   327,   925,   128,   129,
     617,   618,   130,   281,   284,   131,   328,   757,   132,   133,
     329,   644,   134,   135,   136,   137,   138,   139,   140,   277,
     663,   365,   278,   141,   261,   465,   142,   143
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     127,   279,   318,   319,   282,   509,   339,   533,   406,   457,
     263,   920,   430,   624,   437,   396,   127,   145,   286,   386,
     431,   403,   290,   490,   624,   920,   271,   264,   635,   782,
     642,   302,   807,   127,   280,   516,   709,   518,   519,   521,
     522,   523,   524,   145,   527,   718,   289,   624,   493,   844,
     533,    54,   894,   954,    54,  -194,   303,   337,   443,   655,
     311,   362,   312,   486,   147,  -199,   145,   145,   373,   487,
     330,    52,   391,   509,   251,   444,   352,   145,   366,   303,
     509,   332,   445,   258,   368,   266,  -194,   267,   268,   469,
     147,  -194,   371,   502,   881,   145,  -199,   392,   145,   148,
     395,  -199,   489,   333,   334,   379,   402,   313,   533,   314,
     441,   265,   385,   147,   147,   270,   446,    54,   387,   388,
    -194,   146,   144,    54,   147,   408,   294,   295,   354,   355,
    -199,   292,   447,   842,    54,   464,   673,   515,    51,   442,
     889,   293,   147,   674,   517,   147,   269,   283,   315,   253,
     448,   259,   526,   316,   252,   598,   353,   272,   367,   738,
     866,   891,   335,   664,   369,   609,   470,   872,   297,   298,
     664,   664,   372,   503,   882,   921,   843,   389,   250,   253,
     900,   740,   432,   256,   257,   296,   626,   356,   922,   921,
     273,   923,   580,   520,   291,   338,   625,   375,   377,   378,
     579,   491,   922,   381,   533,   923,   636,   274,   643,   710,
     808,   275,   305,   285,   287,   288,   488,  -194,   719,   331,
     720,   728,   845,   433,   438,   895,   299,  -199,   317,   404,
     405,   376,   260,   306,   275,   380,   463,   253,   321,   145,
     473,   892,   382,   383,   743,   744,   307,   300,   336,   760,
     761,   349,   350,   145,   424,   351,   263,   364,   370,   528,
     901,   374,   127,   924,   426,   358,   297,   298,   308,   309,
     301,   515,    51,   264,   529,   390,   487,   924,    52,   534,
     393,   560,    50,    51,    52,   394,   147,   397,   497,   587,
     588,   589,   590,   591,   592,   581,   582,   585,   586,   399,
     147,   384,   398,   745,   400,   364,   407,   763,   762,   619,
     620,   671,   672,   498,   408,   763,   763,   415,   409,   411,
     410,   413,   412,   533,   414,   416,   417,   310,   418,   419,
     420,   512,   436,   421,   427,   428,   429,   435,   439,   449,
     450,   440,   451,   452,   453,   454,   456,   458,   459,   466,
     471,   475,   476,   472,   477,   478,   474,   479,   480,   481,
     495,   482,   483,   509,   493,   766,   504,   500,   533,   422,
     505,   423,   510,   506,   507,   509,   509,   511,   514,   532,
     531,   509,   525,   358,   540,   537,   539,   543,   542,   544,
     546,   547,   564,   566,   550,   569,   571,   610,   545,   551,
     553,   554,   561,   559,   573,   574,   679,   600,   127,   605,
     607,   638,   293,   576,   641,   615,   645,   633,   634,   562,
     646,   648,   455,   653,   656,   650,   657,   292,   677,   577,
     686,   681,   364,   602,   670,   683,   687,   467,   692,   694,
     613,   468,   697,   698,   699,   700,   701,   717,   721,   704,
     702,   723,   725,   705,   706,   707,   631,   708,   711,   712,
     821,   713,   714,   716,   729,   727,   730,   737,   485,   485,
     303,   739,   492,   731,   733,   746,   614,   751,   494,   724,
     753,   754,   630,   767,   499,   755,   501,   765,   127,   768,
     303,   303,   770,   637,   772,   774,   777,   508,   785,   813,
     788,   789,   792,   513,   675,   794,   811,   818,   819,   827,
     829,   831,   847,   833,   834,   836,   837,   838,   840,   850,
     852,   856,   860,   530,   870,   874,   868,   877,   869,   878,
     871,   906,   839,   884,   893,   887,   535,   536,   902,   538,
     888,   841,   541,   899,   846,   848,   849,   693,   857,   911,
     859,   599,   912,   863,   864,   865,   917,   548,   867,   883,
     905,   549,   741,   742,   908,   552,   886,   915,   918,   555,
     556,   557,   558,   926,   931,   932,   937,   939,   364,   944,
     947,   928,   956,   957,   961,   629,   632,   563,   565,   567,
     568,   570,   572,   964,   965,   936,   940,   969,   575,   941,
     604,   583,   945,   584,   593,   596,   485,   946,   595,   955,
     796,   594,   425,   659,   660,   661,   662,   949,   666,   667,
     668,   669,   735,   662,   662,   855,   951,   601,   127,   603,
     256,   952,   958,   959,     0,   303,   303,   606,     0,   736,
     608,   747,   611,   612,   748,   749,     0,   597,     0,   616,
     616,   616,   621,   622,   623,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   639,   640,     0,     0,
       0,   715,     0,   647,     0,   649,     0,   651,   652,     0,
       0,   654,     0,     0,   784,   658,     0,     0,     0,     0,
       0,   665,     0,     0,     0,     0,     0,     0,     0,     0,
     676,     0,   678,   364,   680,     0,     0,     0,   682,     0,
     684,     0,     0,   688,   689,   690,   691,     0,     0,     0,
       0,   695,   696,     0,     0,   734,     0,     0,     0,   795,
       0,   799,   802,   805,   853,   854,     0,   127,   127,   127,
       0,     0,   823,   825,     0,     0,   809,     0,   800,   803,
     806,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   764,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   722,     0,     0,     0,     0,   364,     0,   726,   873,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   732,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   303,   303,     0,
       0,     0,     0,     0,     0,     0,     0,   750,     0,   752,
       0,     0,     0,     0,   756,     0,   758,   759,     0,     0,
     909,     0,     0,     0,   798,   801,   804,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   769,     0,
       0,     0,   771,     0,   773,   880,   775,     0,   776,     0,
     820,     0,     0,   822,     0,   778,     0,     0,   779,     0,
     890,   780,   781,   756,   783,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   786,   787,
       0,     0,     0,     0,   790,     0,   791,     0,   793,     0,
       0,   616,   797,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   810,   862,     0,
       0,     0,   812,     0,   814,     0,     0,     0,   817,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   824,   826,
       0,   828,     0,   830,     0,   832,     0,     0,   835,     0,
       0,     0,     0,   817,     0,     0,     0,   963,     0,     0,
       0,     0,     0,     0,   967,   851,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   858,     0,     0,     0,     0,     0,
     861,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   756,     0,     0,     0,     0,     0,
       0,   756,     0,     0,     0,   875,     0,     0,   876,     0,
       0,     0,     0,   879,     0,     0,     0,     0,     0,     0,
       0,   885,     0,     0,     0,     0,     0,   817,     0,     0,
       0,     0,     0,   817,     0,     0,     0,     0,   896,   897,
       0,     0,   898,     0,     0,     0,     0,     0,   903,   904,
       0,     0,   907,     0,     0,   910,     0,     0,     0,     0,
     913,   914,     0,   916,     0,     0,   919,     0,     0,   927,
       0,     0,   929,   930,     0,     0,   933,     0,   934,   935,
       0,     0,     0,     0,     0,     0,     0,   938,     0,     0,
       0,     0,   942,   943,     0,     0,     0,     0,   948,     0,
     950,     0,     0,   149,   150,   953,     0,     0,   151,     0,
     152,   153,     0,     0,     0,   960,     0,   962,     0,   154,
       0,     0,   966,   155,   156,     0,   968,     0,     0,     0,
     970,     0,     0,     0,   340,     0,     0,     0,     0,     0,
       0,   157,   158,   159,   160,   161,   162,     0,   163,     0,
       0,     0,     0,     0,     0,     0,   164,     0,     0,     0,
       0,   165,   166,     0,     0,     0,     0,   167,     0,     0,
       0,   168,   169,   341,     0,   170,     0,     0,     0,   171,
     172,   173,     0,   174,   175,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   342,   176,   177,    54,     0,     0,
       0,     0,   178,   179,     0,   180,     0,   181,   182,     0,
       0,     0,   183,   184,     0,   185,   343,     0,     0,   186,
     187,   188,   189,     0,   190,   191,     0,   192,   193,     0,
       0,     0,     0,     0,     0,   194,     0,   195,   196,   197,
       0,     0,     0,     0,     0,   198,     0,   199,     0,   201,
     202,     0,   203,   204,   205,     0,     0,     0,   344,     0,
       0,     0,     0,     0,   207,   208,   209,     0,     0,     0,
       0,     0,     0,     0,   210,   345,     0,     0,   346,   212,
     213,     0,     0,   214,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     215,     0,   216,     0,     0,     0,     0,     0,     0,     0,
       0,   217,     0,     0,     0,     0,   218,     0,   219,     0,
     220,     0,   221,     0,     0,     0,   347,   222,   223,   224,
       0,     0,     0,     0,   225,     0,     0,     0,     0,   348,
       0,     0,     0,     0,     0,   227,   228,   229,     0,   230,
     149,   150,   357,     0,     0,   151,   231,   152,   153,     0,
       0,     0,     0,     0,     0,     0,   154,     0,     0,     0,
     155,   156,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   358,     0,     0,     0,     0,     0,   157,   158,
     159,   160,   161,   162,     0,   163,     0,     0,     0,     0,
       0,     0,     0,   164,     0,     0,     0,     0,   165,   166,
       0,     0,     0,     0,   167,     0,     0,     0,   168,   169,
       0,     0,   170,     0,     0,     0,   171,   172,   173,     0,
     174,   175,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   176,   177,    54,     0,     0,     0,     0,   178,
     179,     0,   180,     0,   181,   182,     0,     0,     0,   183,
     184,     0,   185,     0,     0,     0,   186,   187,   188,   189,
       0,   190,   191,     0,   192,   193,     0,     0,     0,     0,
       0,     0,   194,     0,   195,   196,   197,     0,     0,     0,
       0,     0,   198,     0,   199,     0,   201,   202,     0,   203,
     204,   205,     0,     0,     0,   206,     0,     0,     0,     0,
       0,   207,   208,   209,   359,   360,     0,     0,     0,     0,
       0,   210,   211,     0,     0,     0,   212,   213,     0,     0,
     214,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   215,     0,   216,
       0,     0,     0,     0,     0,     0,     0,     0,   217,     0,
       0,     0,     0,   218,   253,   219,     0,   220,     0,   221,
       0,     0,     0,   361,   222,   223,   224,     0,     0,     0,
       0,   225,     0,     0,     0,     0,   226,     0,     0,     0,
     149,   150,   227,   228,   229,   151,   230,   152,   153,     0,
       0,     0,     0,   231,     0,     0,   154,     0,     0,     0,
     155,   156,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   322,     0,     0,     0,     0,     0,   157,   158,
     159,   160,   161,   162,     0,   163,     0,     0,     0,     0,
       0,     0,     0,   164,     0,     0,     0,     0,   165,   166,
       0,     0,     0,     0,   167,     0,     0,     0,   168,   169,
       0,     0,   170,     0,     0,     0,   171,   172,   173,     0,
     174,   175,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   176,   177,    54,     0,     0,     0,     0,   178,
     179,     0,   180,     0,   181,   182,     0,     0,     0,   183,
     184,     0,   185,     0,     0,     0,   186,   187,   188,   189,
       0,   190,   191,     0,   192,   193,     0,     0,     0,     0,
       0,     0,   194,     0,   195,   196,   197,     0,     0,     0,
       0,     0,   198,     0,   199,     0,   201,   202,     0,   203,
     204,   205,     0,     0,     0,   206,     0,     0,     0,     0,
       0,   207,   208,   209,     0,     0,     0,     0,     0,     0,
       0,   210,   211,     0,     0,     0,   212,   213,     0,     0,
     214,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   215,     0,   216,
       0,     0,     0,     0,     0,     0,     0,     0,   217,     0,
     323,     0,     0,   218,   253,   219,     0,   220,   324,   221,
       0,     0,     0,     0,   222,   223,   224,     0,     0,     0,
     325,   225,     0,     0,     0,     0,   226,     0,     0,     0,
       0,   401,   227,   228,   229,     0,   230,   149,   150,     0,
       0,     0,   151,   231,   152,   153,     0,     0,     0,     0,
       0,     0,     0,   154,     0,     0,     0,   155,   156,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   322,
       0,     0,     0,     0,     0,   157,   158,   159,   160,   161,
     162,     0,   163,     0,     0,     0,     0,     0,     0,     0,
     164,     0,     0,     0,     0,   165,   166,     0,     0,     0,
       0,   167,     0,     0,     0,   168,   169,     0,     0,   170,
       0,     0,     0,   171,   172,   173,     0,   174,   175,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   176,
     177,    54,     0,     0,     0,     0,   178,   179,     0,   180,
       0,   181,   182,     0,     0,     0,   183,   184,     0,   185,
       0,     0,     0,   186,   187,   188,   189,     0,   190,   191,
       0,   192,   193,     0,     0,     0,     0,     0,     0,   194,
       0,   195,   196,   197,     0,     0,     0,     0,     0,   198,
       0,   199,     0,   201,   202,     0,   203,   204,   205,     0,
       0,     0,   206,     0,     0,     0,     0,     0,   207,   208,
     209,     0,     0,     0,     0,     0,     0,     0,   210,   211,
       0,     0,     0,   212,   213,     0,     0,   214,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   215,     0,   216,     0,     0,     0,
       0,     0,     0,     0,     0,   217,     0,   323,     0,     0,
     218,     0,   219,     0,   220,   324,   221,     0,     0,     0,
       0,   222,   223,   224,     0,     0,     0,   325,   225,     0,
       0,     0,     0,   226,     0,     0,     0,     0,   326,   227,
     228,   229,     0,   230,   149,   150,     0,     0,     0,   151,
     231,   152,   153,     0,     0,     0,     0,     0,     0,     0,
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
     226,     0,     0,     0,   149,   150,   227,   228,   229,   151,
     230,   152,   153,     0,     0,     0,     0,   231,     0,     0,
     154,     0,     0,     0,   155,   156,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   358,     0,     0,     0,
       0,   460,   157,   158,   159,   160,   161,   162,     0,   163,
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
       0,     0,     0,     0,     0,   207,   208,   209,   461,   462,
       0,     0,     0,     0,     0,   210,   211,     0,     0,     0,
     212,   213,     0,     0,   214,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   215,     0,   216,     0,     0,     0,     0,     0,     0,
       0,     0,   217,     0,     0,     0,     0,   218,   253,   219,
       0,   220,     0,   221,     0,     0,     0,     0,   222,   223,
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
       0,     0,   217,     0,   323,     0,     0,   218,     0,   219,
       0,   220,   324,   221,     0,     0,     0,     0,   222,   223,
     224,     0,     0,     0,   325,   225,     0,     0,     0,     0,
     226,     0,     0,     0,     0,   685,   227,   228,   229,     0,
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
       0,     0,   703,   227,   228,   229,     0,   230,   149,   150,
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
       0,   218,     0,   219,     0,   220,   324,   221,     0,     0,
       0,     0,   222,   223,   224,     0,     0,     0,   325,   225,
       0,     0,     0,     0,   226,     0,     0,     0,   149,   150,
     227,   228,   229,   151,   230,   152,   153,     0,     0,     0,
       0,   231,     0,     0,   154,     0,     0,     0,   155,   156,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   157,   158,   159,   160,
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
       0,     0,     0,     0,     0,     0,   217,     0,     0,     0,
       0,   218,   253,   219,     0,   220,     0,   221,     0,     0,
       0,     0,   222,   223,   224,     0,     0,     0,     0,   225,
       0,     0,     0,     0,   226,     0,     0,     0,     0,     0,
     227,   228,   229,     0,   230,   496,     0,   149,   150,     0,
       0,   231,   151,     0,   152,   153,     0,     0,     0,     0,
       0,     0,     0,   154,     0,     0,     0,   155,   156,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   815,
       0,     0,     0,     0,     0,   157,   158,   159,   160,   161,
     162,     0,   163,     0,     0,     0,     0,     0,     0,     0,
     164,     0,     0,     0,     0,   165,   166,     0,     0,     0,
       0,   167,     0,     0,     0,   168,   169,     0,     0,   170,
       0,     0,     0,   171,   172,   173,     0,   174,   175,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   176,
     177,    54,     0,     0,     0,     0,   178,   179,     0,   180,
       0,   181,   182,     0,     0,     0,   183,   184,     0,   185,
       0,     0,     0,   186,   187,   188,   189,     0,   190,   191,
       0,   192,   193,     0,     0,     0,     0,     0,     0,   194,
       0,   195,   196,   197,     0,     0,     0,     0,     0,   198,
       0,   199,     0,   201,   202,     0,   203,   204,   205,     0,
       0,     0,   206,     0,     0,     0,     0,     0,   207,   208,
     209,     0,     0,     0,     0,     0,     0,     0,   210,   211,
       0,     0,     0,   212,   213,     0,     0,   214,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   215,     0,   216,     0,     0,     0,
       0,     0,     0,     0,     0,   217,     0,   816,     0,     0,
     218,     0,   219,     0,   220,     0,   221,     0,     0,     0,
       0,   222,   223,   224,     0,     0,     0,     0,   225,     0,
       0,     0,     0,   226,     0,     0,     0,   149,   150,   227,
     228,   229,   151,   230,   152,   153,     0,     0,     0,     0,
     231,     0,     0,   154,     0,     0,     0,   155,   156,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   157,   158,   159,   160,   161,
     162,     0,   163,     0,     0,     0,     0,     0,     0,     0,
     164,     0,     0,     0,     0,   165,   166,     0,     0,     0,
       0,   167,     0,     0,     0,   168,   169,     0,     0,   170,
       0,     0,     0,   171,   172,   173,     0,   174,   175,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   176,
     177,    54,     0,     0,     0,     0,   178,   179,     0,   180,
       0,   181,   182,     0,     0,     0,   183,   184,     0,   185,
       0,     0,     0,   186,   187,   188,   189,     0,   190,   191,
       0,   192,   193,     0,     0,     0,     0,     0,     0,   194,
       0,   195,   196,   197,     0,     0,     0,     0,     0,   198,
       0,   199,   200,   201,   202,     0,   203,   204,   205,     0,
       0,     0,   206,     0,     0,     0,     0,     0,   207,   208,
     209,     0,     0,     0,     0,     0,     0,     0,   210,   211,
       0,     0,     0,   212,   213,     0,     0,   214,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   215,     0,   216,     0,     0,     0,
       0,     0,     0,     0,     0,   217,     0,     0,     0,     0,
     218,     0,   219,     0,   220,     0,   221,     0,     0,     0,
       0,   222,   223,   224,     0,     0,     0,     0,   225,     0,
       0,     0,     0,   226,     0,     0,     0,   149,   150,   227,
     228,   229,   151,   230,   152,   153,     0,     0,     0,     0,
     231,     0,     0,   154,     0,     0,     0,   155,   156,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   157,   158,   159,   160,   161,
     162,     0,   163,     0,     0,     0,     0,     0,     0,     0,
     164,     0,     0,     0,     0,   165,   166,     0,     0,     0,
       0,   167,     0,     0,     0,   168,   169,     0,     0,   170,
       0,     0,     0,   171,   172,   173,     0,   174,   175,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   176,
     177,    54,     0,     0,     0,     0,   178,   179,     0,   180,
       0,   181,   182,     0,     0,     0,   183,   184,     0,   185,
       0,     0,     0,   186,   187,   188,   189,     0,   190,   191,
       0,   192,   193,     0,     0,     0,     0,     0,     0,   194,
       0,   195,   196,   197,     0,     0,     0,     0,     0,   198,
       0,   199,     0,   201,   202,     0,   203,   204,   205,     0,
       0,     0,   206,     0,     0,     0,     0,     0,   207,   208,
     209,     0,     0,     0,     0,     0,     0,     0,   210,   211,
       0,     0,     0,   212,   213,     0,     0,   214,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   215,     0,   216,     0,     0,     0,
       0,     0,     0,     0,     0,   217,     0,     0,     0,     0,
     218,   253,   219,     0,   220,     0,   221,     0,     0,     0,
       0,   222,   223,   224,     0,     0,     0,     0,   225,     0,
       0,     0,     0,   226,     0,     0,     0,   149,   150,   227,
     228,   229,   151,   230,   152,   153,     0,     0,     0,     0,
     231,     0,     0,   154,     0,     0,     0,   155,   156,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   157,   158,   159,   160,   161,
     162,     0,   163,     0,     0,     0,     0,     0,     0,     0,
     164,     0,     0,     0,     0,   165,   166,     0,     0,     0,
       0,   167,     0,     0,     0,   168,   169,     0,     0,   170,
       0,     0,     0,   171,   172,   173,     0,   174,   175,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   176,
     177,    54,     0,     0,     0,     0,   178,   179,     0,   180,
       0,   181,   182,     0,     0,     0,   183,   184,     0,   185,
       0,     0,     0,   186,   187,   188,   189,     0,   190,   191,
       0,   192,   193,     0,     0,     0,     0,     0,     0,   194,
       0,   195,   196,   197,     0,     0,     0,     0,     0,   198,
       0,   199,     0,   201,   202,     0,   203,   204,   205,     0,
       0,     0,   206,     0,     0,     0,     0,     0,   207,   208,
     209,     0,     0,     0,     0,     0,     0,     0,   210,   211,
       0,     0,     0,   212,   213,     0,     0,   214,     0,     0,
       0,     0,     0,     0,     0,   320,     0,     0,     0,     0,
       0,     0,     0,     0,   215,     0,   216,     0,     0,     0,
       0,     0,     0,     0,     0,   217,     0,     0,     0,     0,
     218,     0,   219,     0,   220,     0,   221,     0,     0,     0,
       0,   222,   223,   224,     0,     0,     0,     0,   225,     0,
       0,     0,     0,   226,     0,     0,     0,   149,   150,   227,
     228,   229,   151,   230,   152,   153,     0,     0,     0,     0,
     231,     0,     0,   154,     0,     0,     0,   155,   156,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   358,
       0,     0,     0,     0,     0,   157,   158,   159,   160,   161,
     162,     0,   163,     0,     0,     0,     0,     0,     0,     0,
     164,     0,     0,     0,     0,   165,   166,     0,     0,     0,
       0,   167,     0,     0,     0,   168,   169,     0,     0,   170,
       0,     0,     0,   171,   172,   173,     0,   174,   175,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   176,
     177,    54,     0,     0,     0,     0,   178,   179,     0,   180,
       0,   181,   182,     0,     0,     0,   183,   184,     0,   185,
       0,     0,     0,   186,   187,   188,   189,     0,   190,   191,
       0,   192,   193,     0,     0,     0,     0,     0,     0,   194,
       0,   195,   196,   197,     0,     0,     0,     0,     0,   198,
       0,   199,     0,   201,   202,     0,   203,   204,   205,     0,
       0,     0,   206,     0,     0,     0,     0,     0,   207,   208,
     209,     0,     0,     0,     0,     0,     0,     0,   210,   211,
       0,     0,     0,   212,   213,     0,     0,   214,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   215,     0,   216,     0,     0,     0,
       0,     0,     0,     0,     0,   217,     0,     0,     0,     0,
     218,     0,   219,     0,   220,     0,   221,     0,     0,     0,
       0,   222,   223,   224,     0,     0,     0,     0,   225,     0,
       0,     0,     0,   226,     0,     0,     0,   149,   150,   227,
     228,   229,   151,   230,   152,   153,     0,     0,     0,     0,
     231,     0,     0,   154,     0,     0,     0,   155,   156,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   534,
       0,     0,     0,     0,     0,   157,   158,   159,   160,   161,
     162,     0,   163,     0,     0,     0,     0,     0,     0,     0,
     164,     0,     0,     0,     0,   165,   166,     0,     0,     0,
       0,   167,     0,     0,     0,   168,   169,     0,     0,   170,
       0,     0,     0,   171,   172,   173,     0,   174,   175,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   176,
     177,    54,     0,     0,     0,     0,   178,   179,     0,   180,
       0,   181,   182,     0,     0,     0,   183,   184,     0,   185,
       0,     0,     0,   186,   187,   188,   189,     0,   190,   191,
       0,   192,   193,     0,     0,     0,     0,     0,     0,   194,
       0,   195,   196,   197,     0,     0,     0,     0,     0,   198,
       0,   199,     0,   201,   202,     0,   203,   204,   205,     0,
       0,     0,   206,     0,     0,     0,     0,     0,   207,   208,
     209,     0,     0,     0,     0,     0,     0,     0,   210,   211,
       0,     0,     0,   212,   213,     0,     0,   214,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   215,     0,   216,     0,     0,     0,
       0,     0,     0,     0,     0,   217,     0,     0,     0,     0,
     218,     0,   219,     0,   220,     0,   221,     0,     0,     0,
       0,   222,   223,   224,     0,     0,     0,     0,   225,     0,
       0,     0,     0,   226,     0,     0,     0,   149,   150,   227,
     228,   229,   151,   230,   152,   153,     0,     0,     0,     0,
     231,     0,     0,   154,     0,     0,     0,   155,   156,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   157,   158,   159,   160,   161,
     162,     0,   163,     0,     0,     0,     0,     0,     0,     0,
     164,     0,     0,     0,     0,   165,   166,     0,     0,     0,
       0,   167,     0,     0,     0,   168,   169,     0,     0,   170,
       0,     0,     0,   171,   172,   173,     0,   174,   175,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   176,
     177,    54,     0,     0,     0,     0,   178,   179,     0,   180,
       0,   181,   182,     0,     0,     0,   183,   184,     0,   185,
       0,     0,     0,   186,   187,   188,   189,     0,   190,   191,
       0,   192,   193,     0,     0,     0,     0,     0,     0,   194,
       0,   195,   196,   197,     0,     0,     0,     0,     0,   198,
       0,   199,     0,   201,   202,     0,   203,   204,   205,     0,
       0,     0,   206,     0,     0,     0,     0,     0,   207,   208,
     209,     0,     0,     0,     0,     0,     0,     0,   210,   211,
       0,     0,     0,   212,   213,     0,     0,   214,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   215,     0,   216,     0,     0,     0,
       0,     0,   578,     0,     0,   217,     0,     0,     0,     0,
     218,     0,   219,     0,   220,     0,   221,     0,     0,     0,
       0,   222,   223,   224,     0,     0,     0,     0,   225,     0,
       0,     0,     0,   226,     0,     0,     0,   149,   150,   227,
     228,   229,   151,   230,   152,   153,     0,     0,     0,     0,
     231,     0,     0,   154,     0,     0,     0,   155,   156,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   157,   158,   159,   160,   161,
     162,     0,   163,     0,     0,     0,     0,     0,     0,     0,
     164,     0,     0,     0,     0,   165,   166,     0,     0,     0,
       0,   167,     0,     0,     0,   168,   169,     0,     0,   170,
       0,     0,     0,   171,   172,   173,     0,   174,   175,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   176,
     177,    54,     0,     0,     0,     0,   178,   179,     0,   180,
       0,   181,   182,     0,     0,     0,   183,   184,     0,   185,
       0,     0,     0,   186,   187,   188,   189,     0,   190,   191,
       0,   192,   193,     0,     0,     0,     0,     0,     0,   194,
       0,   195,   196,   197,     0,     0,     0,     0,     0,   198,
       0,   199,     0,   201,   202,     0,   203,   204,   205,     0,
       0,     0,   206,     0,     0,     0,     0,     0,   207,   208,
     209,     0,     0,     0,     0,     0,     0,     0,   210,   211,
       0,     0,     0,   212,   213,     0,     0,   214,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   215,     0,   216,     0,     0,     0,
       0,     0,     0,     0,     0,   217,     0,     0,     0,     0,
     218,     0,   219,     0,   220,     0,   221,     0,     0,     0,
       0,   222,   223,   224,     0,     0,     0,     0,   225,     0,
       0,     0,     0,   226,     0,     0,     0,   149,   150,   227,
     228,   229,   151,   230,   152,   153,     0,     0,     0,     0,
     231,     0,     0,   154,     0,     0,     0,   155,   156,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   157,   158,   159,   160,   161,
     162,     0,   163,     0,     0,     0,     0,     0,     0,     0,
     164,     0,     0,     0,     0,   165,   166,     0,     0,     0,
       0,   167,     0,     0,     0,   168,   169,     0,     0,   170,
       0,     0,     0,   171,   172,   173,     0,   174,   175,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   176,
     177,    54,     0,     0,     0,     0,   178,   179,     0,   180,
       0,   181,   182,     0,     0,     0,   183,   184,     0,   185,
       0,     0,     0,   186,   187,   188,   189,     0,   190,   191,
       0,   192,   193,     0,     0,     0,     0,     0,     0,   194,
       0,   195,   196,   197,     0,     0,     0,     0,     0,   198,
       0,   199,     0,   201,   202,     0,   203,   204,   205,     0,
       0,     0,   206,     0,     0,     0,     0,     0,     0,   208,
     209,     0,     0,     0,     0,     0,     0,     0,   210,   211,
       0,     0,     0,   212,   213,     0,     0,   214,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   215,     0,   216,     0,     0,     0,
       0,     0,     0,     0,     0,   217,     0,     0,     0,     0,
     218,     0,   219,     0,   220,     0,   221,     0,     0,     0,
       0,   222,   223,   224,     0,     0,     0,     0,   225,     0,
       0,     0,     0,   226,     0,     0,     0,   149,   150,   227,
     228,   229,   151,   230,   152,   153,     0,     0,     0,     0,
     231,     0,     0,   154,     0,     0,     0,   155,   156,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   157,   158,   159,   160,   161,
     162,     0,   163,     0,     0,     0,     0,     0,     0,     0,
     164,     0,     0,     0,     0,   165,   166,     0,     0,     0,
       0,   167,     0,     0,     0,   168,   169,     0,     0,   170,
       0,     0,     0,   171,   172,   173,     0,   174,   175,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   176,
     177,    54,     0,     0,     0,     0,   178,   179,     0,   180,
       0,   181,   182,     0,     0,     0,   183,   184,     0,   185,
       0,     0,     0,   186,   187,   188,   189,     0,   190,   191,
       0,   192,   193,     0,     0,     0,     0,     0,     0,   194,
       0,   195,   196,   197,     0,     0,     0,     0,     0,   198,
       0,   199,     0,   201,     0,     0,   203,   204,   205,     0,
       0,     0,   206,     0,     0,     0,     0,     0,     0,   208,
     209,     0,     0,     0,     0,     0,     0,     0,   210,   211,
       0,     0,     0,     0,   213,     0,     0,   214,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   215,     0,   216,     0,     0,     0,
       0,     0,     0,     0,     0,   217,     0,     0,     0,     0,
     218,     0,   219,     0,   220,     0,   221,     0,     0,     0,
       0,   222,   223,   224,     0,     0,     0,     0,   225,     0,
       0,     0,     0,   226,     0,     0,     0,     0,     0,   227,
     228,   229,     0,   230,     0,     1,     0,     0,     2,     0,
     231,     3,     4,     5,     6,     0,     7,     8,     9,     0,
       0,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,     0,    20,    21,    22,    23,    24,     0,     0,     0,
       0,     0,     0,    25,    26,    27,    28,    29,    30,    31,
      32,     0,    33,    34,    35,     0,    36,     0,     0,    37,
      38,     0,    39,     0,     0,     0,    40,     0,     0,    41,
      42,     0,    43,    44,    45,     0,     0,     0,    46,     0,
       0,     0,    47,    48,    49,    50,    51,    52,     0,     0,
      53,     0,     0,    54,     0,    55,     0,     0,     0,     0,
      56,     0,    57,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    58,    59,    60,     0,     0,     0,     0,    61,
       0,     0,     0,     0,     0,    62,    63,    64,    65,    66,
      67,     0,    68,     0,     0,     0,    69,    70,     0,     0,
       0,     0,     0,     0,    71,    72,     0,    73,     0,     0,
       0,     0,    74,    75,    76,    77,     0,    78,     0,    79,
       0,     0,     0,     0,    80,    81,    82,     0,    83,    84,
       0,    85,     0,     0,    86,     0,    87,    88,     0,     0,
      89,    90,    91,    92,    93,    94,    95,    96,    97,     0,
      98,     0,    99,   100,   101,   102,     0,   103,     0,   104,
     105,   106,     0,     0,     0,   107,   108,     0,     0,     0,
     109,   110,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   111,     0,     0,     0,     0,   112,   113,     0,
       0,   114,     0,     0,     0,   115,     0,   116,   117,     0,
       0,     0,     0,     0,     0,   118,   119,     0,   120,   121,
     122,   123,   124,   125,   126,   627,     0,     0,     2,     0,
       0,     3,     4,     5,     6,     0,     7,     8,     9,     0,
       0,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,     0,    20,    21,    22,    23,    24,     0,     0,     0,
       0,     0,     0,    25,    26,    27,    28,    29,    30,    31,
      32,     0,   147,    34,    35,     0,    36,     0,     0,    37,
      38,   628,    39,     0,     0,     0,    40,     0,     0,    41,
       0,     0,    43,    44,    45,     0,     0,     0,    46,     0,
       0,     0,    47,    48,    49,    50,    51,    52,     0,     0,
      53,     0,     0,    54,     0,    55,     0,     0,     0,     0,
      56,     0,    57,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    58,    59,    60,     0,     0,     0,     0,    61,
       0,     0,     0,     0,     0,    62,    63,    64,    65,    66,
      67,     0,    68,     0,     0,     0,    69,    70,     0,     0,
       0,     0,     0,     0,    71,    72,     0,    73,     0,     0,
       0,     0,    74,    75,    76,    77,     0,    78,     0,    79,
       0,     0,     0,     0,    80,    81,    82,     0,    83,    84,
       0,    85,     0,     0,    86,     0,    87,    88,     0,     0,
      89,    90,    91,    92,    93,    94,    95,    96,    97,     0,
      98,     0,    99,   100,   101,   102,     0,   103,     0,   104,
     105,   106,     0,     0,     0,   107,   108,     0,     0,     0,
     109,   110,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   111,     0,     0,     0,     0,   112,   113,     0,
       0,   114,     0,     0,     0,   115,     0,   116,   117,     0,
       0,     0,     0,     0,     0,   118,   119,     0,   120,   121,
     122,   123,   124,   125,   126,   627,     0,     0,     2,     0,
       0,     3,     4,     5,     6,     0,     7,     8,     9,     0,
       0,    10,    11,    12,    13,    14,    15,   262,    17,    18,
      19,     0,    20,    21,    22,    23,    24,     0,     0,     0,
       0,     0,     0,    25,    26,    27,    28,    29,    30,    31,
      32,     0,   147,    34,    35,     0,    36,     0,     0,    37,
      38,     0,    39,     0,     0,     0,    40,     0,     0,    41,
       0,     0,    43,    44,    45,     0,     0,     0,    46,     0,
       0,     0,    47,    48,    49,    50,    51,    52,     0,     0,
      53,     0,     0,    54,     0,    55,     0,     0,     0,     0,
      56,     0,    57,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    58,    59,    60,     0,     0,     0,     0,    61,
       0,     0,     0,     0,     0,    62,    63,    64,    65,    66,
      67,     0,    68,     0,     0,     0,    69,    70,     0,     0,
       0,     0,     0,     0,    71,    72,     0,    73,     0,     0,
       0,     0,    74,    75,    76,    77,     0,    78,     0,    79,
       0,     0,     0,     0,    80,    81,    82,     0,    83,    84,
       0,    85,     0,     0,    86,     0,    87,    88,     0,     0,
      89,    90,    91,    92,    93,    94,    95,    96,    97,     0,
      98,     0,    99,   100,   101,   102,     0,   103,     0,   104,
     105,   106,     0,     0,     0,   107,   108,     0,     0,     0,
     109,   110,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   111,     0,     0,     0,     0,   112,   113,     0,
       0,   114,     0,     0,     0,   115,     0,   116,   117,     0,
       0,     0,     0,     0,     0,   118,   119,     0,   120,   121,
     122,   123,   124,   125,   126,     1,     0,     0,     2,     0,
       0,     3,     4,     5,     6,     0,     7,     8,     9,     0,
       0,    10,    11,    12,    13,    14,    15,   262,    17,    18,
      19,     0,    20,    21,    22,    23,    24,     0,     0,     0,
       0,     0,     0,    25,    26,    27,    28,    29,    30,    31,
      32,     0,     0,    34,    35,     0,    36,     0,     0,    37,
      38,     0,    39,     0,     0,     0,    40,     0,     0,    41,
       0,     0,    43,    44,    45,     0,     0,     0,    46,     0,
       0,     0,    47,    48,    49,    50,    51,    52,     0,     0,
      53,     0,     0,    54,     0,    55,     0,     0,     0,     0,
      56,     0,    57,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    58,    59,    60,     0,     0,     0,     0,    61,
       0,     0,     0,     0,     0,    62,    63,    64,    65,    66,
      67,     0,    68,     0,     0,     0,    69,    70,     0,     0,
       0,     0,     0,     0,    71,    72,     0,    73,     0,     0,
       0,     0,    74,    75,    76,    77,     0,    78,     0,    79,
       0,     0,     0,     0,    80,    81,    82,     0,    83,    84,
       0,    85,     0,     0,    86,     0,    87,    88,     0,     0,
      89,    90,    91,    92,    93,    94,    95,    96,    97,     0,
      98,     0,    99,   100,   101,   102,     0,   103,     0,   104,
     105,   106,     0,     0,     0,   107,   108,     0,     0,     0,
     109,   110,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   111,     0,     0,     0,     0,   112,   113,     0,
       0,   114,     0,     0,     0,   115,     0,   116,   117,     0,
       0,     0,     0,     0,     0,   118,   119,     0,   120,   121,
     122,   123,   124,   125,   126,     1,     0,     0,     2,     0,
       0,     3,     4,     5,     6,     0,     7,     8,     9,     0,
       0,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,     0,    20,    21,    22,    23,    24,     0,     0,     0,
       0,     0,     0,    25,    26,    27,    28,    29,    30,    31,
      32,     0,     0,    34,    35,     0,    36,     0,     0,    37,
      38,     0,    39,     0,     0,     0,    40,     0,     0,    41,
       0,     0,    43,    44,    45,     0,     0,     0,    46,     0,
       0,     0,    47,    48,    49,    50,    51,    52,     0,     0,
      53,     0,     0,    54,     0,    55,     0,     0,     0,     0,
      56,     0,    57,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    58,    59,    60,     0,     0,     0,     0,    61,
       0,     0,     0,     0,     0,    62,    63,    64,    65,    66,
      67,     0,    68,     0,     0,     0,    69,    70,     0,     0,
       0,     0,     0,     0,    71,    72,     0,    73,     0,     0,
       0,     0,    74,    75,    76,    77,     0,    78,     0,    79,
       0,     0,     0,     0,    80,    81,    82,     0,    83,    84,
       0,    85,     0,     0,    86,     0,    87,    88,     0,     0,
      89,    90,    91,    92,    93,    94,    95,    96,    97,     0,
      98,     0,    99,   100,   101,   102,     0,   103,     0,   104,
     105,   106,     0,     0,     0,   107,   108,     0,     0,     0,
     109,   110,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   111,     0,     0,     0,     0,   112,   113,     0,
       0,   114,     0,     0,     0,   115,     0,   116,   117,     0,
       0,     0,     0,     0,     0,   118,   119,     0,   120,   121,
     122,   123,   124,   125,   126
};

static const yytype_int16 yycheck[] =
{
       0,    33,    65,    66,    38,   328,    79,   363,   134,   253,
      16,     7,     6,    35,     9,   125,    16,     9,    43,    68,
      14,   131,    47,    35,    35,     7,    81,    16,    35,   702,
      35,    56,    35,    33,    34,   340,    35,   342,   343,   344,
     345,   346,   347,     9,   349,    35,    46,    35,    35,    35,
     406,    97,    35,    35,    97,     0,    56,    30,    68,    35,
      60,    86,    62,   298,    56,     0,     9,     9,    93,    89,
      70,    91,   140,   396,   145,    85,   145,     9,   145,    79,
     403,   145,    92,    29,   145,   145,    31,   167,   168,    68,
      56,    36,   145,   145,   145,     9,    31,   122,     9,     2,
     125,    36,   299,   167,   168,   105,   131,   104,   464,   106,
     150,    68,   112,    56,    56,    68,   126,    97,   167,   168,
      65,    35,    97,    97,    56,    31,   167,   168,   167,   168,
      65,   230,   142,    54,    97,   261,    97,    89,    90,   179,
     114,   240,    56,   104,   341,    56,   226,    97,   145,   217,
     160,    97,   349,   150,   225,    97,   225,   212,   225,    65,
     833,   145,   226,   519,   225,   208,   145,   840,   144,   145,
     526,   527,   225,   225,   225,   171,    97,   226,     7,   217,
     145,   227,   176,    12,    13,   226,   208,   226,   184,   171,
     245,   187,   436,   145,    56,   168,   207,   100,   101,   102,
     435,   213,   184,   106,   560,   187,   213,   150,   213,   208,
     213,   177,    56,    42,    43,    44,   236,   162,   208,   145,
     208,   208,   208,   217,   219,   208,    55,   162,   225,   132,
     133,   163,   178,   132,   177,   227,   261,   217,    67,     9,
     274,   225,   167,   168,   167,   168,   145,   227,    77,   167,
     168,    80,    81,     9,   202,    97,   262,    86,    56,    82,
     225,    56,   262,   259,   212,    35,   144,   145,   167,   168,
     250,    89,    90,   262,    97,   145,    89,   259,    91,    35,
      56,   407,    89,    90,    91,   145,    56,    56,   313,   443,
     444,   445,   446,   447,   448,   437,   438,   441,   442,   145,
      56,   226,    68,   226,   145,   134,    35,   663,   226,   479,
     480,   526,   527,   313,    31,   671,   672,   146,    31,    58,
      36,     0,   162,   679,    97,    35,   145,   226,   145,   145,
     145,   331,    93,   145,   145,   145,   145,   145,    13,     7,
     171,   155,   259,   101,    69,    35,   145,    35,    35,   145,
      68,    36,    35,    68,    35,    35,   150,    35,    35,    68,
      68,    35,    35,   686,    35,   670,   145,    56,   724,   198,
      35,   200,    68,   145,   145,   698,   699,    97,    97,    35,
     145,   704,    68,    35,    35,   145,   145,    35,   145,    35,
      35,    35,   417,   418,    35,   420,   421,   470,    68,    35,
      35,    35,   408,    35,   208,    35,   532,    35,   408,    35,
      35,   208,   240,    97,    35,    97,    35,   490,   491,   408,
      35,   145,   251,   213,    35,    97,   208,   230,    35,   429,
     540,    35,   261,   458,   227,    35,    35,   266,    97,    35,
     474,   270,    35,   553,   554,    35,    35,    35,    35,   559,
     213,    35,    35,   208,   208,   208,   488,   208,   208,   208,
     765,   208,   208,   208,    97,    68,    35,    65,   297,   298,
     470,    65,   301,   240,    97,    35,   476,    35,   307,   605,
      35,   208,   488,    97,   313,   208,   315,   208,   488,    97,
     490,   491,    35,   493,    35,    35,    35,   326,    35,    35,
      97,   208,   208,   332,   529,    68,   208,   208,    35,   208,
     208,   208,    35,   213,   208,   208,   208,   208,   213,   150,
     225,   150,    68,   352,    35,    35,   150,    35,   150,   145,
     150,    35,   208,   150,    54,   145,   365,   366,    68,   368,
     145,   208,   371,   145,   208,   208,   208,   547,   208,    35,
     208,   454,    35,   208,   208,   208,    35,   386,   208,   208,
     145,   390,   635,   636,   145,   394,   208,   145,    35,   398,
     399,   400,   401,    35,    35,    35,    35,    35,   407,    35,
      35,   208,    35,    35,    35,   488,   489,   416,   417,   418,
     419,   420,   421,    35,    35,   208,   208,    35,   427,   208,
     459,   439,   208,   440,   449,   452,   435,   208,   451,   947,
     730,   450,   207,   516,   517,   518,   519,   208,   521,   522,
     523,   524,   628,   526,   527,   810,   208,   456,   628,   458,
     459,   208,   208,   208,    -1,   635,   636,   466,    -1,   628,
     469,   641,   471,   472,   644,   645,    -1,   453,    -1,   478,
     479,   480,   481,   482,   483,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   495,   496,    -1,    -1,
      -1,   574,    -1,   502,    -1,   504,    -1,   506,   507,    -1,
      -1,   510,    -1,    -1,   709,   514,    -1,    -1,    -1,    -1,
      -1,   520,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     529,    -1,   531,   532,   533,    -1,    -1,    -1,   537,    -1,
     539,    -1,    -1,   542,   543,   544,   545,    -1,    -1,    -1,
      -1,   550,   551,    -1,    -1,   628,    -1,    -1,    -1,   729,
      -1,   737,   738,   739,   807,   808,    -1,   737,   738,   739,
      -1,    -1,   767,   768,    -1,    -1,   746,    -1,   737,   738,
     739,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   664,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   600,    -1,    -1,    -1,    -1,   605,    -1,   607,   842,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   624,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   807,   808,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   646,    -1,   648,
      -1,    -1,    -1,    -1,   653,    -1,   655,   656,    -1,    -1,
     893,    -1,    -1,    -1,   737,   738,   739,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   677,    -1,
      -1,    -1,   681,    -1,   683,   855,   685,    -1,   687,    -1,
     763,    -1,    -1,   766,    -1,   694,    -1,    -1,   697,    -1,
     870,   700,   701,   702,   703,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   717,   718,
      -1,    -1,    -1,    -1,   723,    -1,   725,    -1,   727,    -1,
      -1,   730,   731,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   746,   821,    -1,
      -1,    -1,   751,    -1,   753,    -1,    -1,    -1,   757,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   767,   768,
      -1,   770,    -1,   772,    -1,   774,    -1,    -1,   777,    -1,
      -1,    -1,    -1,   782,    -1,    -1,    -1,   957,    -1,    -1,
      -1,    -1,    -1,    -1,   964,   794,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   813,    -1,    -1,    -1,    -1,    -1,
     819,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   833,    -1,    -1,    -1,    -1,    -1,
      -1,   840,    -1,    -1,    -1,   844,    -1,    -1,   847,    -1,
      -1,    -1,    -1,   852,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   860,    -1,    -1,    -1,    -1,    -1,   866,    -1,    -1,
      -1,    -1,    -1,   872,    -1,    -1,    -1,    -1,   877,   878,
      -1,    -1,   881,    -1,    -1,    -1,    -1,    -1,   887,   888,
      -1,    -1,   891,    -1,    -1,   894,    -1,    -1,    -1,    -1,
     899,   900,    -1,   902,    -1,    -1,   905,    -1,    -1,   908,
      -1,    -1,   911,   912,    -1,    -1,   915,    -1,   917,   918,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   926,    -1,    -1,
      -1,    -1,   931,   932,    -1,    -1,    -1,    -1,   937,    -1,
     939,    -1,    -1,     3,     4,   944,    -1,    -1,     8,    -1,
      10,    11,    -1,    -1,    -1,   954,    -1,   956,    -1,    19,
      -1,    -1,   961,    23,    24,    -1,   965,    -1,    -1,    -1,
     969,    -1,    -1,    -1,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    41,    42,    43,    44,    45,    46,    -1,    48,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,
      -1,    61,    62,    -1,    -1,    -1,    -1,    67,    -1,    -1,
      -1,    71,    72,    73,    -1,    75,    -1,    -1,    -1,    79,
      80,    81,    -1,    83,    84,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    94,    95,    96,    97,    -1,    -1,
      -1,    -1,   102,   103,    -1,   105,    -1,   107,   108,    -1,
      -1,    -1,   112,   113,    -1,   115,   116,    -1,    -1,   119,
     120,   121,   122,    -1,   124,   125,    -1,   127,   128,    -1,
      -1,    -1,    -1,    -1,    -1,   135,    -1,   137,   138,   139,
      -1,    -1,    -1,    -1,    -1,   145,    -1,   147,    -1,   149,
     150,    -1,   152,   153,   154,    -1,    -1,    -1,   158,    -1,
      -1,    -1,    -1,    -1,   164,   165,   166,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   174,   175,    -1,    -1,   178,   179,
     180,    -1,    -1,   183,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     200,    -1,   202,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   211,    -1,    -1,    -1,    -1,   216,    -1,   218,    -1,
     220,    -1,   222,    -1,    -1,    -1,   226,   227,   228,   229,
      -1,    -1,    -1,    -1,   234,    -1,    -1,    -1,    -1,   239,
      -1,    -1,    -1,    -1,    -1,   245,   246,   247,    -1,   249,
       3,     4,     5,    -1,    -1,     8,   256,    10,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    19,    -1,    -1,    -1,
      23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    -1,    -1,    -1,    -1,    -1,    41,    42,
      43,    44,    45,    46,    -1,    48,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,    61,    62,
      -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,    71,    72,
      -1,    -1,    75,    -1,    -1,    -1,    79,    80,    81,    -1,
      83,    84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    95,    96,    97,    -1,    -1,    -1,    -1,   102,
     103,    -1,   105,    -1,   107,   108,    -1,    -1,    -1,   112,
     113,    -1,   115,    -1,    -1,    -1,   119,   120,   121,   122,
      -1,   124,   125,    -1,   127,   128,    -1,    -1,    -1,    -1,
      -1,    -1,   135,    -1,   137,   138,   139,    -1,    -1,    -1,
      -1,    -1,   145,    -1,   147,    -1,   149,   150,    -1,   152,
     153,   154,    -1,    -1,    -1,   158,    -1,    -1,    -1,    -1,
      -1,   164,   165,   166,   167,   168,    -1,    -1,    -1,    -1,
      -1,   174,   175,    -1,    -1,    -1,   179,   180,    -1,    -1,
     183,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   200,    -1,   202,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   211,    -1,
      -1,    -1,    -1,   216,   217,   218,    -1,   220,    -1,   222,
      -1,    -1,    -1,   226,   227,   228,   229,    -1,    -1,    -1,
      -1,   234,    -1,    -1,    -1,    -1,   239,    -1,    -1,    -1,
       3,     4,   245,   246,   247,     8,   249,    10,    11,    -1,
      -1,    -1,    -1,   256,    -1,    -1,    19,    -1,    -1,    -1,
      23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    -1,    -1,    -1,    -1,    -1,    41,    42,
      43,    44,    45,    46,    -1,    48,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,    61,    62,
      -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,    71,    72,
      -1,    -1,    75,    -1,    -1,    -1,    79,    80,    81,    -1,
      83,    84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    95,    96,    97,    -1,    -1,    -1,    -1,   102,
     103,    -1,   105,    -1,   107,   108,    -1,    -1,    -1,   112,
     113,    -1,   115,    -1,    -1,    -1,   119,   120,   121,   122,
      -1,   124,   125,    -1,   127,   128,    -1,    -1,    -1,    -1,
      -1,    -1,   135,    -1,   137,   138,   139,    -1,    -1,    -1,
      -1,    -1,   145,    -1,   147,    -1,   149,   150,    -1,   152,
     153,   154,    -1,    -1,    -1,   158,    -1,    -1,    -1,    -1,
      -1,   164,   165,   166,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   174,   175,    -1,    -1,    -1,   179,   180,    -1,    -1,
     183,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   200,    -1,   202,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   211,    -1,
     213,    -1,    -1,   216,   217,   218,    -1,   220,   221,   222,
      -1,    -1,    -1,    -1,   227,   228,   229,    -1,    -1,    -1,
     233,   234,    -1,    -1,    -1,    -1,   239,    -1,    -1,    -1,
      -1,   244,   245,   246,   247,    -1,   249,     3,     4,    -1,
      -1,    -1,     8,   256,    10,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    19,    -1,    -1,    -1,    23,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      -1,    -1,    -1,    -1,    -1,    41,    42,    43,    44,    45,
      46,    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      56,    -1,    -1,    -1,    -1,    61,    62,    -1,    -1,    -1,
      -1,    67,    -1,    -1,    -1,    71,    72,    -1,    -1,    75,
      -1,    -1,    -1,    79,    80,    81,    -1,    83,    84,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    95,
      96,    97,    -1,    -1,    -1,    -1,   102,   103,    -1,   105,
      -1,   107,   108,    -1,    -1,    -1,   112,   113,    -1,   115,
      -1,    -1,    -1,   119,   120,   121,   122,    -1,   124,   125,
      -1,   127,   128,    -1,    -1,    -1,    -1,    -1,    -1,   135,
      -1,   137,   138,   139,    -1,    -1,    -1,    -1,    -1,   145,
      -1,   147,    -1,   149,   150,    -1,   152,   153,   154,    -1,
      -1,    -1,   158,    -1,    -1,    -1,    -1,    -1,   164,   165,
     166,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   174,   175,
      -1,    -1,    -1,   179,   180,    -1,    -1,   183,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   200,    -1,   202,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   211,    -1,   213,    -1,    -1,
     216,    -1,   218,    -1,   220,   221,   222,    -1,    -1,    -1,
      -1,   227,   228,   229,    -1,    -1,    -1,   233,   234,    -1,
      -1,    -1,    -1,   239,    -1,    -1,    -1,    -1,   244,   245,
     246,   247,    -1,   249,     3,     4,    -1,    -1,    -1,     8,
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
      -1,    -1,    -1,    -1,    -1,   164,   165,   166,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   174,   175,    -1,    -1,    -1,
     179,   180,    -1,    -1,   183,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   200,    -1,   202,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   211,    -1,   213,    -1,    -1,   216,   217,   218,
      -1,   220,   221,   222,    -1,    -1,    -1,    -1,   227,   228,
     229,    -1,    -1,    -1,   233,   234,    -1,    -1,    -1,    -1,
     239,    -1,    -1,    -1,     3,     4,   245,   246,   247,     8,
     249,    10,    11,    -1,    -1,    -1,    -1,   256,    -1,    -1,
      19,    -1,    -1,    -1,    23,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,    -1,    -1,
      -1,    40,    41,    42,    43,    44,    45,    46,    -1,    48,
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
      -1,   220,    -1,   222,    -1,    -1,    -1,    -1,   227,   228,
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
      -1,    -1,   211,    -1,   213,    -1,    -1,   216,    -1,   218,
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
      -1,   216,    -1,   218,    -1,   220,   221,   222,    -1,    -1,
      -1,    -1,   227,   228,   229,    -1,    -1,    -1,   233,   234,
      -1,    -1,    -1,    -1,   239,    -1,    -1,    -1,     3,     4,
     245,   246,   247,     8,   249,    10,    11,    -1,    -1,    -1,
      -1,   256,    -1,    -1,    19,    -1,    -1,    -1,    23,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    41,    42,    43,    44,
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
      -1,    -1,    -1,    -1,    -1,    -1,   211,    -1,    -1,    -1,
      -1,   216,   217,   218,    -1,   220,    -1,   222,    -1,    -1,
      -1,    -1,   227,   228,   229,    -1,    -1,    -1,    -1,   234,
      -1,    -1,    -1,    -1,   239,    -1,    -1,    -1,    -1,    -1,
     245,   246,   247,    -1,   249,   250,    -1,     3,     4,    -1,
      -1,   256,     8,    -1,    10,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    19,    -1,    -1,    -1,    23,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      -1,    -1,    -1,    -1,    -1,    41,    42,    43,    44,    45,
      46,    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      56,    -1,    -1,    -1,    -1,    61,    62,    -1,    -1,    -1,
      -1,    67,    -1,    -1,    -1,    71,    72,    -1,    -1,    75,
      -1,    -1,    -1,    79,    80,    81,    -1,    83,    84,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    95,
      96,    97,    -1,    -1,    -1,    -1,   102,   103,    -1,   105,
      -1,   107,   108,    -1,    -1,    -1,   112,   113,    -1,   115,
      -1,    -1,    -1,   119,   120,   121,   122,    -1,   124,   125,
      -1,   127,   128,    -1,    -1,    -1,    -1,    -1,    -1,   135,
      -1,   137,   138,   139,    -1,    -1,    -1,    -1,    -1,   145,
      -1,   147,    -1,   149,   150,    -1,   152,   153,   154,    -1,
      -1,    -1,   158,    -1,    -1,    -1,    -1,    -1,   164,   165,
     166,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   174,   175,
      -1,    -1,    -1,   179,   180,    -1,    -1,   183,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   200,    -1,   202,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   211,    -1,   213,    -1,    -1,
     216,    -1,   218,    -1,   220,    -1,   222,    -1,    -1,    -1,
      -1,   227,   228,   229,    -1,    -1,    -1,    -1,   234,    -1,
      -1,    -1,    -1,   239,    -1,    -1,    -1,     3,     4,   245,
     246,   247,     8,   249,    10,    11,    -1,    -1,    -1,    -1,
     256,    -1,    -1,    19,    -1,    -1,    -1,    23,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    41,    42,    43,    44,    45,
      46,    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      56,    -1,    -1,    -1,    -1,    61,    62,    -1,    -1,    -1,
      -1,    67,    -1,    -1,    -1,    71,    72,    -1,    -1,    75,
      -1,    -1,    -1,    79,    80,    81,    -1,    83,    84,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    95,
      96,    97,    -1,    -1,    -1,    -1,   102,   103,    -1,   105,
      -1,   107,   108,    -1,    -1,    -1,   112,   113,    -1,   115,
      -1,    -1,    -1,   119,   120,   121,   122,    -1,   124,   125,
      -1,   127,   128,    -1,    -1,    -1,    -1,    -1,    -1,   135,
      -1,   137,   138,   139,    -1,    -1,    -1,    -1,    -1,   145,
      -1,   147,   148,   149,   150,    -1,   152,   153,   154,    -1,
      -1,    -1,   158,    -1,    -1,    -1,    -1,    -1,   164,   165,
     166,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   174,   175,
      -1,    -1,    -1,   179,   180,    -1,    -1,   183,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   200,    -1,   202,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   211,    -1,    -1,    -1,    -1,
     216,    -1,   218,    -1,   220,    -1,   222,    -1,    -1,    -1,
      -1,   227,   228,   229,    -1,    -1,    -1,    -1,   234,    -1,
      -1,    -1,    -1,   239,    -1,    -1,    -1,     3,     4,   245,
     246,   247,     8,   249,    10,    11,    -1,    -1,    -1,    -1,
     256,    -1,    -1,    19,    -1,    -1,    -1,    23,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    41,    42,    43,    44,    45,
      46,    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      56,    -1,    -1,    -1,    -1,    61,    62,    -1,    -1,    -1,
      -1,    67,    -1,    -1,    -1,    71,    72,    -1,    -1,    75,
      -1,    -1,    -1,    79,    80,    81,    -1,    83,    84,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    95,
      96,    97,    -1,    -1,    -1,    -1,   102,   103,    -1,   105,
      -1,   107,   108,    -1,    -1,    -1,   112,   113,    -1,   115,
      -1,    -1,    -1,   119,   120,   121,   122,    -1,   124,   125,
      -1,   127,   128,    -1,    -1,    -1,    -1,    -1,    -1,   135,
      -1,   137,   138,   139,    -1,    -1,    -1,    -1,    -1,   145,
      -1,   147,    -1,   149,   150,    -1,   152,   153,   154,    -1,
      -1,    -1,   158,    -1,    -1,    -1,    -1,    -1,   164,   165,
     166,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   174,   175,
      -1,    -1,    -1,   179,   180,    -1,    -1,   183,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   200,    -1,   202,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   211,    -1,    -1,    -1,    -1,
     216,   217,   218,    -1,   220,    -1,   222,    -1,    -1,    -1,
      -1,   227,   228,   229,    -1,    -1,    -1,    -1,   234,    -1,
      -1,    -1,    -1,   239,    -1,    -1,    -1,     3,     4,   245,
     246,   247,     8,   249,    10,    11,    -1,    -1,    -1,    -1,
     256,    -1,    -1,    19,    -1,    -1,    -1,    23,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    41,    42,    43,    44,    45,
      46,    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      56,    -1,    -1,    -1,    -1,    61,    62,    -1,    -1,    -1,
      -1,    67,    -1,    -1,    -1,    71,    72,    -1,    -1,    75,
      -1,    -1,    -1,    79,    80,    81,    -1,    83,    84,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    95,
      96,    97,    -1,    -1,    -1,    -1,   102,   103,    -1,   105,
      -1,   107,   108,    -1,    -1,    -1,   112,   113,    -1,   115,
      -1,    -1,    -1,   119,   120,   121,   122,    -1,   124,   125,
      -1,   127,   128,    -1,    -1,    -1,    -1,    -1,    -1,   135,
      -1,   137,   138,   139,    -1,    -1,    -1,    -1,    -1,   145,
      -1,   147,    -1,   149,   150,    -1,   152,   153,   154,    -1,
      -1,    -1,   158,    -1,    -1,    -1,    -1,    -1,   164,   165,
     166,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   174,   175,
      -1,    -1,    -1,   179,   180,    -1,    -1,   183,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   191,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   200,    -1,   202,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   211,    -1,    -1,    -1,    -1,
     216,    -1,   218,    -1,   220,    -1,   222,    -1,    -1,    -1,
      -1,   227,   228,   229,    -1,    -1,    -1,    -1,   234,    -1,
      -1,    -1,    -1,   239,    -1,    -1,    -1,     3,     4,   245,
     246,   247,     8,   249,    10,    11,    -1,    -1,    -1,    -1,
     256,    -1,    -1,    19,    -1,    -1,    -1,    23,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      -1,    -1,    -1,    -1,    -1,    41,    42,    43,    44,    45,
      46,    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      56,    -1,    -1,    -1,    -1,    61,    62,    -1,    -1,    -1,
      -1,    67,    -1,    -1,    -1,    71,    72,    -1,    -1,    75,
      -1,    -1,    -1,    79,    80,    81,    -1,    83,    84,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    95,
      96,    97,    -1,    -1,    -1,    -1,   102,   103,    -1,   105,
      -1,   107,   108,    -1,    -1,    -1,   112,   113,    -1,   115,
      -1,    -1,    -1,   119,   120,   121,   122,    -1,   124,   125,
      -1,   127,   128,    -1,    -1,    -1,    -1,    -1,    -1,   135,
      -1,   137,   138,   139,    -1,    -1,    -1,    -1,    -1,   145,
      -1,   147,    -1,   149,   150,    -1,   152,   153,   154,    -1,
      -1,    -1,   158,    -1,    -1,    -1,    -1,    -1,   164,   165,
     166,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   174,   175,
      -1,    -1,    -1,   179,   180,    -1,    -1,   183,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   200,    -1,   202,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   211,    -1,    -1,    -1,    -1,
     216,    -1,   218,    -1,   220,    -1,   222,    -1,    -1,    -1,
      -1,   227,   228,   229,    -1,    -1,    -1,    -1,   234,    -1,
      -1,    -1,    -1,   239,    -1,    -1,    -1,     3,     4,   245,
     246,   247,     8,   249,    10,    11,    -1,    -1,    -1,    -1,
     256,    -1,    -1,    19,    -1,    -1,    -1,    23,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      -1,    -1,    -1,    -1,    -1,    41,    42,    43,    44,    45,
      46,    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      56,    -1,    -1,    -1,    -1,    61,    62,    -1,    -1,    -1,
      -1,    67,    -1,    -1,    -1,    71,    72,    -1,    -1,    75,
      -1,    -1,    -1,    79,    80,    81,    -1,    83,    84,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    95,
      96,    97,    -1,    -1,    -1,    -1,   102,   103,    -1,   105,
      -1,   107,   108,    -1,    -1,    -1,   112,   113,    -1,   115,
      -1,    -1,    -1,   119,   120,   121,   122,    -1,   124,   125,
      -1,   127,   128,    -1,    -1,    -1,    -1,    -1,    -1,   135,
      -1,   137,   138,   139,    -1,    -1,    -1,    -1,    -1,   145,
      -1,   147,    -1,   149,   150,    -1,   152,   153,   154,    -1,
      -1,    -1,   158,    -1,    -1,    -1,    -1,    -1,   164,   165,
     166,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   174,   175,
      -1,    -1,    -1,   179,   180,    -1,    -1,   183,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   200,    -1,   202,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   211,    -1,    -1,    -1,    -1,
     216,    -1,   218,    -1,   220,    -1,   222,    -1,    -1,    -1,
      -1,   227,   228,   229,    -1,    -1,    -1,    -1,   234,    -1,
      -1,    -1,    -1,   239,    -1,    -1,    -1,     3,     4,   245,
     246,   247,     8,   249,    10,    11,    -1,    -1,    -1,    -1,
     256,    -1,    -1,    19,    -1,    -1,    -1,    23,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    41,    42,    43,    44,    45,
      46,    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      56,    -1,    -1,    -1,    -1,    61,    62,    -1,    -1,    -1,
      -1,    67,    -1,    -1,    -1,    71,    72,    -1,    -1,    75,
      -1,    -1,    -1,    79,    80,    81,    -1,    83,    84,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    95,
      96,    97,    -1,    -1,    -1,    -1,   102,   103,    -1,   105,
      -1,   107,   108,    -1,    -1,    -1,   112,   113,    -1,   115,
      -1,    -1,    -1,   119,   120,   121,   122,    -1,   124,   125,
      -1,   127,   128,    -1,    -1,    -1,    -1,    -1,    -1,   135,
      -1,   137,   138,   139,    -1,    -1,    -1,    -1,    -1,   145,
      -1,   147,    -1,   149,   150,    -1,   152,   153,   154,    -1,
      -1,    -1,   158,    -1,    -1,    -1,    -1,    -1,   164,   165,
     166,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   174,   175,
      -1,    -1,    -1,   179,   180,    -1,    -1,   183,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   200,    -1,   202,    -1,    -1,    -1,
      -1,    -1,   208,    -1,    -1,   211,    -1,    -1,    -1,    -1,
     216,    -1,   218,    -1,   220,    -1,   222,    -1,    -1,    -1,
      -1,   227,   228,   229,    -1,    -1,    -1,    -1,   234,    -1,
      -1,    -1,    -1,   239,    -1,    -1,    -1,     3,     4,   245,
     246,   247,     8,   249,    10,    11,    -1,    -1,    -1,    -1,
     256,    -1,    -1,    19,    -1,    -1,    -1,    23,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    41,    42,    43,    44,    45,
      46,    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      56,    -1,    -1,    -1,    -1,    61,    62,    -1,    -1,    -1,
      -1,    67,    -1,    -1,    -1,    71,    72,    -1,    -1,    75,
      -1,    -1,    -1,    79,    80,    81,    -1,    83,    84,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    95,
      96,    97,    -1,    -1,    -1,    -1,   102,   103,    -1,   105,
      -1,   107,   108,    -1,    -1,    -1,   112,   113,    -1,   115,
      -1,    -1,    -1,   119,   120,   121,   122,    -1,   124,   125,
      -1,   127,   128,    -1,    -1,    -1,    -1,    -1,    -1,   135,
      -1,   137,   138,   139,    -1,    -1,    -1,    -1,    -1,   145,
      -1,   147,    -1,   149,   150,    -1,   152,   153,   154,    -1,
      -1,    -1,   158,    -1,    -1,    -1,    -1,    -1,   164,   165,
     166,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   174,   175,
      -1,    -1,    -1,   179,   180,    -1,    -1,   183,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   200,    -1,   202,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   211,    -1,    -1,    -1,    -1,
     216,    -1,   218,    -1,   220,    -1,   222,    -1,    -1,    -1,
      -1,   227,   228,   229,    -1,    -1,    -1,    -1,   234,    -1,
      -1,    -1,    -1,   239,    -1,    -1,    -1,     3,     4,   245,
     246,   247,     8,   249,    10,    11,    -1,    -1,    -1,    -1,
     256,    -1,    -1,    19,    -1,    -1,    -1,    23,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    41,    42,    43,    44,    45,
      46,    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      56,    -1,    -1,    -1,    -1,    61,    62,    -1,    -1,    -1,
      -1,    67,    -1,    -1,    -1,    71,    72,    -1,    -1,    75,
      -1,    -1,    -1,    79,    80,    81,    -1,    83,    84,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    95,
      96,    97,    -1,    -1,    -1,    -1,   102,   103,    -1,   105,
      -1,   107,   108,    -1,    -1,    -1,   112,   113,    -1,   115,
      -1,    -1,    -1,   119,   120,   121,   122,    -1,   124,   125,
      -1,   127,   128,    -1,    -1,    -1,    -1,    -1,    -1,   135,
      -1,   137,   138,   139,    -1,    -1,    -1,    -1,    -1,   145,
      -1,   147,    -1,   149,   150,    -1,   152,   153,   154,    -1,
      -1,    -1,   158,    -1,    -1,    -1,    -1,    -1,    -1,   165,
     166,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   174,   175,
      -1,    -1,    -1,   179,   180,    -1,    -1,   183,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   200,    -1,   202,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   211,    -1,    -1,    -1,    -1,
     216,    -1,   218,    -1,   220,    -1,   222,    -1,    -1,    -1,
      -1,   227,   228,   229,    -1,    -1,    -1,    -1,   234,    -1,
      -1,    -1,    -1,   239,    -1,    -1,    -1,     3,     4,   245,
     246,   247,     8,   249,    10,    11,    -1,    -1,    -1,    -1,
     256,    -1,    -1,    19,    -1,    -1,    -1,    23,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    41,    42,    43,    44,    45,
      46,    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      56,    -1,    -1,    -1,    -1,    61,    62,    -1,    -1,    -1,
      -1,    67,    -1,    -1,    -1,    71,    72,    -1,    -1,    75,
      -1,    -1,    -1,    79,    80,    81,    -1,    83,    84,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    95,
      96,    97,    -1,    -1,    -1,    -1,   102,   103,    -1,   105,
      -1,   107,   108,    -1,    -1,    -1,   112,   113,    -1,   115,
      -1,    -1,    -1,   119,   120,   121,   122,    -1,   124,   125,
      -1,   127,   128,    -1,    -1,    -1,    -1,    -1,    -1,   135,
      -1,   137,   138,   139,    -1,    -1,    -1,    -1,    -1,   145,
      -1,   147,    -1,   149,    -1,    -1,   152,   153,   154,    -1,
      -1,    -1,   158,    -1,    -1,    -1,    -1,    -1,    -1,   165,
     166,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   174,   175,
      -1,    -1,    -1,    -1,   180,    -1,    -1,   183,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   200,    -1,   202,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   211,    -1,    -1,    -1,    -1,
     216,    -1,   218,    -1,   220,    -1,   222,    -1,    -1,    -1,
      -1,   227,   228,   229,    -1,    -1,    -1,    -1,   234,    -1,
      -1,    -1,    -1,   239,    -1,    -1,    -1,    -1,    -1,   245,
     246,   247,    -1,   249,    -1,     9,    -1,    -1,    12,    -1,
     256,    15,    16,    17,    18,    -1,    20,    21,    22,    -1,
      -1,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    -1,    36,    37,    38,    39,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    48,    49,    50,    51,    52,    53,
      54,    -1,    56,    57,    58,    -1,    60,    -1,    -1,    63,
      64,    -1,    66,    -1,    -1,    -1,    70,    -1,    -1,    73,
      74,    -1,    76,    77,    78,    -1,    -1,    -1,    82,    -1,
      -1,    -1,    86,    87,    88,    89,    90,    91,    -1,    -1,
      94,    -1,    -1,    97,    -1,    99,    -1,    -1,    -1,    -1,
     104,    -1,   106,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   116,   117,   118,    -1,    -1,    -1,    -1,   123,
      -1,    -1,    -1,    -1,    -1,   129,   130,   131,   132,   133,
     134,    -1,   136,    -1,    -1,    -1,   140,   141,    -1,    -1,
      -1,    -1,    -1,    -1,   148,   149,    -1,   151,    -1,    -1,
      -1,    -1,   156,   157,   158,   159,    -1,   161,    -1,   163,
      -1,    -1,    -1,    -1,   168,   169,   170,    -1,   172,   173,
      -1,   175,    -1,    -1,   178,    -1,   180,   181,    -1,    -1,
     184,   185,   186,   187,   188,   189,   190,   191,   192,    -1,
     194,    -1,   196,   197,   198,   199,    -1,   201,    -1,   203,
     204,   205,    -1,    -1,    -1,   209,   210,    -1,    -1,    -1,
     214,   215,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   226,    -1,    -1,    -1,    -1,   231,   232,    -1,
      -1,   235,    -1,    -1,    -1,   239,    -1,   241,   242,    -1,
      -1,    -1,    -1,    -1,    -1,   249,   250,    -1,   252,   253,
     254,   255,   256,   257,   258,     9,    -1,    -1,    12,    -1,
      -1,    15,    16,    17,    18,    -1,    20,    21,    22,    -1,
      -1,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    -1,    36,    37,    38,    39,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    48,    49,    50,    51,    52,    53,
      54,    -1,    56,    57,    58,    -1,    60,    -1,    -1,    63,
      64,    65,    66,    -1,    -1,    -1,    70,    -1,    -1,    73,
      -1,    -1,    76,    77,    78,    -1,    -1,    -1,    82,    -1,
      -1,    -1,    86,    87,    88,    89,    90,    91,    -1,    -1,
      94,    -1,    -1,    97,    -1,    99,    -1,    -1,    -1,    -1,
     104,    -1,   106,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   116,   117,   118,    -1,    -1,    -1,    -1,   123,
      -1,    -1,    -1,    -1,    -1,   129,   130,   131,   132,   133,
     134,    -1,   136,    -1,    -1,    -1,   140,   141,    -1,    -1,
      -1,    -1,    -1,    -1,   148,   149,    -1,   151,    -1,    -1,
      -1,    -1,   156,   157,   158,   159,    -1,   161,    -1,   163,
      -1,    -1,    -1,    -1,   168,   169,   170,    -1,   172,   173,
      -1,   175,    -1,    -1,   178,    -1,   180,   181,    -1,    -1,
     184,   185,   186,   187,   188,   189,   190,   191,   192,    -1,
     194,    -1,   196,   197,   198,   199,    -1,   201,    -1,   203,
     204,   205,    -1,    -1,    -1,   209,   210,    -1,    -1,    -1,
     214,   215,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   226,    -1,    -1,    -1,    -1,   231,   232,    -1,
      -1,   235,    -1,    -1,    -1,   239,    -1,   241,   242,    -1,
      -1,    -1,    -1,    -1,    -1,   249,   250,    -1,   252,   253,
     254,   255,   256,   257,   258,     9,    -1,    -1,    12,    -1,
      -1,    15,    16,    17,    18,    -1,    20,    21,    22,    -1,
      -1,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    -1,    36,    37,    38,    39,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    48,    49,    50,    51,    52,    53,
      54,    -1,    56,    57,    58,    -1,    60,    -1,    -1,    63,
      64,    -1,    66,    -1,    -1,    -1,    70,    -1,    -1,    73,
      -1,    -1,    76,    77,    78,    -1,    -1,    -1,    82,    -1,
      -1,    -1,    86,    87,    88,    89,    90,    91,    -1,    -1,
      94,    -1,    -1,    97,    -1,    99,    -1,    -1,    -1,    -1,
     104,    -1,   106,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   116,   117,   118,    -1,    -1,    -1,    -1,   123,
      -1,    -1,    -1,    -1,    -1,   129,   130,   131,   132,   133,
     134,    -1,   136,    -1,    -1,    -1,   140,   141,    -1,    -1,
      -1,    -1,    -1,    -1,   148,   149,    -1,   151,    -1,    -1,
      -1,    -1,   156,   157,   158,   159,    -1,   161,    -1,   163,
      -1,    -1,    -1,    -1,   168,   169,   170,    -1,   172,   173,
      -1,   175,    -1,    -1,   178,    -1,   180,   181,    -1,    -1,
     184,   185,   186,   187,   188,   189,   190,   191,   192,    -1,
     194,    -1,   196,   197,   198,   199,    -1,   201,    -1,   203,
     204,   205,    -1,    -1,    -1,   209,   210,    -1,    -1,    -1,
     214,   215,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   226,    -1,    -1,    -1,    -1,   231,   232,    -1,
      -1,   235,    -1,    -1,    -1,   239,    -1,   241,   242,    -1,
      -1,    -1,    -1,    -1,    -1,   249,   250,    -1,   252,   253,
     254,   255,   256,   257,   258,     9,    -1,    -1,    12,    -1,
      -1,    15,    16,    17,    18,    -1,    20,    21,    22,    -1,
      -1,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    -1,    36,    37,    38,    39,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    48,    49,    50,    51,    52,    53,
      54,    -1,    -1,    57,    58,    -1,    60,    -1,    -1,    63,
      64,    -1,    66,    -1,    -1,    -1,    70,    -1,    -1,    73,
      -1,    -1,    76,    77,    78,    -1,    -1,    -1,    82,    -1,
      -1,    -1,    86,    87,    88,    89,    90,    91,    -1,    -1,
      94,    -1,    -1,    97,    -1,    99,    -1,    -1,    -1,    -1,
     104,    -1,   106,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   116,   117,   118,    -1,    -1,    -1,    -1,   123,
      -1,    -1,    -1,    -1,    -1,   129,   130,   131,   132,   133,
     134,    -1,   136,    -1,    -1,    -1,   140,   141,    -1,    -1,
      -1,    -1,    -1,    -1,   148,   149,    -1,   151,    -1,    -1,
      -1,    -1,   156,   157,   158,   159,    -1,   161,    -1,   163,
      -1,    -1,    -1,    -1,   168,   169,   170,    -1,   172,   173,
      -1,   175,    -1,    -1,   178,    -1,   180,   181,    -1,    -1,
     184,   185,   186,   187,   188,   189,   190,   191,   192,    -1,
     194,    -1,   196,   197,   198,   199,    -1,   201,    -1,   203,
     204,   205,    -1,    -1,    -1,   209,   210,    -1,    -1,    -1,
     214,   215,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   226,    -1,    -1,    -1,    -1,   231,   232,    -1,
      -1,   235,    -1,    -1,    -1,   239,    -1,   241,   242,    -1,
      -1,    -1,    -1,    -1,    -1,   249,   250,    -1,   252,   253,
     254,   255,   256,   257,   258,     9,    -1,    -1,    12,    -1,
      -1,    15,    16,    17,    18,    -1,    20,    21,    22,    -1,
      -1,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    -1,    36,    37,    38,    39,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    48,    49,    50,    51,    52,    53,
      54,    -1,    -1,    57,    58,    -1,    60,    -1,    -1,    63,
      64,    -1,    66,    -1,    -1,    -1,    70,    -1,    -1,    73,
      -1,    -1,    76,    77,    78,    -1,    -1,    -1,    82,    -1,
      -1,    -1,    86,    87,    88,    89,    90,    91,    -1,    -1,
      94,    -1,    -1,    97,    -1,    99,    -1,    -1,    -1,    -1,
     104,    -1,   106,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   116,   117,   118,    -1,    -1,    -1,    -1,   123,
      -1,    -1,    -1,    -1,    -1,   129,   130,   131,   132,   133,
     134,    -1,   136,    -1,    -1,    -1,   140,   141,    -1,    -1,
      -1,    -1,    -1,    -1,   148,   149,    -1,   151,    -1,    -1,
      -1,    -1,   156,   157,   158,   159,    -1,   161,    -1,   163,
      -1,    -1,    -1,    -1,   168,   169,   170,    -1,   172,   173,
      -1,   175,    -1,    -1,   178,    -1,   180,   181,    -1,    -1,
     184,   185,   186,   187,   188,   189,   190,   191,   192,    -1,
     194,    -1,   196,   197,   198,   199,    -1,   201,    -1,   203,
     204,   205,    -1,    -1,    -1,   209,   210,    -1,    -1,    -1,
     214,   215,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   226,    -1,    -1,    -1,    -1,   231,   232,    -1,
      -1,   235,    -1,    -1,    -1,   239,    -1,   241,   242,    -1,
      -1,    -1,    -1,    -1,    -1,   249,   250,    -1,   252,   253,
     254,   255,   256,   257,   258
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
      40,   167,   168,   261,   271,   315,   145,   286,   286,    68,
     145,    68,    68,   309,   150,    36,    35,    35,    35,    35,
      35,    68,    35,    35,   270,   286,   270,    89,   236,   298,
      35,   213,   286,    35,   286,    68,   250,   261,   263,   286,
      56,   286,   145,   225,   145,    35,   145,   145,   286,   300,
      68,    97,   263,   286,    97,    89,   299,   298,   299,   299,
     145,   299,   299,   299,   299,    68,   298,   299,    82,    97,
     286,   145,    35,   311,    35,   286,   286,   145,   286,   145,
      35,   286,   145,    35,    35,    68,    35,    35,   286,   286,
      35,    35,   286,    35,    35,   286,   286,   286,   286,    35,
     271,   306,   307,   286,   261,   286,   261,   286,   286,   261,
     286,   261,   286,   208,    35,   286,    97,   263,   208,   270,
     269,   274,   274,   275,   276,   277,   277,   278,   278,   278,
     278,   278,   278,   280,   281,   282,   283,   284,    97,   265,
      35,   286,   261,   286,   262,    35,   286,    35,   286,   208,
     264,   286,   286,   309,   263,    97,   286,   290,   291,   291,
     291,   286,   286,   286,    35,   207,   208,     9,    65,   265,
     306,   308,   265,   264,   264,    35,   213,   263,   208,   286,
     286,    35,    35,   213,   301,    35,    35,   286,   145,   286,
      97,   286,   286,   213,   286,    35,    35,   208,   286,   265,
     265,   265,   265,   310,   311,   286,   265,   265,   265,   265,
     227,   310,   310,    97,   104,   261,   286,    35,   286,   271,
     286,    35,   286,    35,   286,   244,   296,    35,   286,   286,
     286,   286,    97,   263,    35,   286,   286,    35,   296,   296,
      35,    35,   213,   244,   296,   208,   208,   208,   208,    35,
     208,   208,   208,   208,   208,   265,   208,    35,    35,   208,
     208,    35,   286,    35,   271,    35,   286,    68,   208,    97,
      35,   240,   286,    97,   265,   306,   307,    65,    65,    65,
     227,   264,   264,   167,   168,   226,    35,   263,   263,   263,
     286,    35,   286,    35,   208,   208,   286,   297,   286,   286,
     167,   168,   226,   311,   265,   208,   299,    97,    97,   286,
      35,   286,    35,   286,    35,   286,   286,    35,   286,   286,
     286,   286,   297,   286,   261,    35,   286,   286,    97,   208,
     286,   286,   208,   286,    68,   263,   290,   286,   265,   306,
     307,   265,   306,   307,   265,   306,   307,    35,   213,   263,
     286,   208,   286,    35,   286,    35,   213,   286,   208,    35,
     265,   299,   265,   261,   286,   261,   286,   208,   286,   208,
     286,   208,   286,   213,   208,   286,   208,   208,   208,   208,
     213,   208,    54,    97,    35,   208,   208,    35,   208,   208,
     150,   286,   225,   264,   264,   301,   150,   208,   286,   208,
      68,   286,   265,   208,   208,   208,   297,   208,   150,   150,
      35,   150,   297,   312,    35,   286,   286,    35,   145,   286,
     263,   145,   225,   208,   150,   286,   208,   145,   145,   114,
     263,   145,   225,    54,    35,   208,   286,   286,   286,   145,
     145,   225,    68,   286,   286,   145,    35,   286,   145,   312,
     286,    35,    35,   286,   286,   145,   286,    35,    35,   286,
       7,   171,   184,   187,   259,   287,    35,   286,   208,   286,
     286,    35,    35,   286,   286,   286,   208,    35,   286,    35,
     208,   208,   286,   286,    35,   208,   208,    35,   286,   208,
     286,   208,   208,   286,    35,   287,    35,    35,   208,   208,
     286,    35,   286,   263,    35,    35,   286,   263,   286,    35,
     286
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
     293,   293,   294,   294,   295,   295,   296,   296,   297,   297,
     297,   297,   298,   298,   299,   299,   300,   300,   300,   300,
     300,   301,   301,   302,   302,   302,   302,   302,   302,   302,
     302,   302,   302,   302,   302,   302,   302,   302,   302,   302,
     302,   302,   302,   302,   302,   302,   302,   302,   302,   302,
     302,   302,   302,   302,   302,   302,   302,   302,   302,   302,
     302,   302,   302,   302,   302,   302,   302,   302,   302,   302,
     302,   302,   302,   302,   302,   302,   302,   302,   302,   302,
     302,   302,   302,   302,   302,   302,   302,   302,   302,   302,
     303,   303,   303,   303,   303,   303,   303,   303,   303,   303,
     303,   303,   303,   303,   303,   303,   303,   303,   303,   303,
     304,   304,   304,   304,   304,   304,   304,   304,   304,   304,
     305,   305,   305,   305,   305,   305,   305,   305,   306,   306,
     306,   306,   306,   307,   307,   307,   307,   308,   308,   308,
     309,   309,   310,   310,   310,   311,   311,   312,   312,   312,
     312,   313,   313,   314,   314,   314,   315,   315,   315,   315,
     315,   316,   316,   316,   316,   317,   317,   317,   317
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
       4,     4,     6,     4,     7,     2,     2,     3,     2,     3,
       1,     2,     1,     4,     4,     2,     7,     5,     7,     5,
       4,     4,     3,     3,     2,     2,     2,     1,     4,     2,
       4,     2,     4,     2,     4,     2,    15,    14,    17,    16,
      13,    11,    14,    10,     8,    10,     7,     8,     5,     3,
       4,     6,     4,     2,     4,     6,     7,     2,     2,     2,
       5,     5,     5,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     7,     6,     2,     1,     1,     2,     1,     2,     1,
       4,     2,     2,     1,     2,     4,     2,     1,     4,     2,
       2,     1,     2,     4,     1,     4,     4,     4,     2,     1,
       4,     4,     2,     4,     3,     2,     1,     4,     4,     1,
       1,     3,     1,     3,     1,     1,     1,     2,     1,     2,
       2,     2,     1,     2,     1,     2,     1,     4,     4,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     5,     5,     5,
       2,     2,     2,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     2,     2,     2,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,    10,     8,
       2,     2,     8,     7,    14,    13,    13,    12,     8,     9,
       6,     7,     7,     6,     7,     6,     7,    12,    12,    12,
       6,     6,     6,     6,     5,     5,     6,     6,     5,     4,
       6,     6,     6,     5,     4,     4,     3,     4,     3,     2,
       1,     1,     2,     3,     2,     1,     2,     1,     1,     1,
       1,     1,     1,     3,     2,     1,     2,     3,     2,     2,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     2,     2,     1,     2,     1,     2,     0
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
#line 3553 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 3:
#line 287 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_FILE_NUMBERS, { yyvsp[0] }); }
#line 3559 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 4:
#line 288 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_FILE_NUMBERS, { yyvsp[0] }); }
#line 3565 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 5:
#line 289 "parser.yy"
                                                        { yyval = yyvsp[-2]; yyval->push_back(yyvsp[0]); }
#line 3571 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 6:
#line 290 "parser.yy"
                                                        { yyval = yyvsp[-2]; yyval->push_back(yyvsp[0]); }
#line 3577 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 7:
#line 294 "parser.yy"
                                                                { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_LVALUE, { yyvsp[-3], yyvsp[-1] }); }
#line 3583 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 8:
#line 295 "parser.yy"
                                                                { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_LVALUE, { yyvsp[-3], yyvsp[-1] }); }
#line 3589 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 9:
#line 296 "parser.yy"
                                                                { yyval = yyvsp[0]; }
#line 3595 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 10:
#line 300 "parser.yy"
                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_LVALUE_LIST, { yyvsp[0] }); }
#line 3601 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 11:
#line 301 "parser.yy"
                                        { yyval = yyvsp[-2]; yyval->push_back(yyvsp[0]); }
#line 3607 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 12:
#line 305 "parser.yy"
                                { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_LABEL, { yyvsp[0] }); }
#line 3613 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 13:
#line 306 "parser.yy"
                                { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_LABEL, { yyvsp[0] }); }
#line 3619 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 14:
#line 310 "parser.yy"
                        { yyval = yyvsp[0]; yyvsp[0]->push_back(yyvsp[-1]); }
#line 3625 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 15:
#line 311 "parser.yy"
                        { yyval = yyvsp[0]; }
#line 3631 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 16:
#line 315 "parser.yy"
                        { yyval = yyvsp[0]; }
#line 3637 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 17:
#line 316 "parser.yy"
                        { yyval = yyvsp[0]; }
#line 3643 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 18:
#line 317 "parser.yy"
                        { yyval = yyvsp[0]; }
#line 3649 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 19:
#line 318 "parser.yy"
                        { yyval = yyvsp[0]; }
#line 3655 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 20:
#line 322 "parser.yy"
                        { yyval = yyvsp[0]; }
#line 3661 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 21:
#line 323 "parser.yy"
                        { yyval = yyvsp[0]; }
#line 3667 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 22:
#line 324 "parser.yy"
                        { yyval = yyvsp[0]; }
#line 3673 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 23:
#line 325 "parser.yy"
                        { yyval = yyvsp[0]; }
#line 3679 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 24:
#line 329 "parser.yy"
                                        { yyval = yyvsp[0]; }
#line 3685 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 25:
#line 330 "parser.yy"
                                        { yyval = yyvsp[0]; }
#line 3691 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 26:
#line 331 "parser.yy"
                                        { yyval = yyvsp[0]; }
#line 3697 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 27:
#line 332 "parser.yy"
                                        { yyval = yyvsp[-1]; }
#line 3703 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 28:
#line 333 "parser.yy"
                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_DATE_dollar_var); }
#line 3709 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 29:
#line 334 "parser.yy"
                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_TIME_dollar_var); }
#line 3715 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 30:
#line 335 "parser.yy"
                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_INKEY_dollar); }
#line 3721 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 31:
#line 336 "parser.yy"
                                                             { vsk_targeting(yyvsp[0]); yyval = yyvsp[0]; }
#line 3727 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 32:
#line 337 "parser.yy"
                                                             { vsk_targeting(yyvsp[-3]); yyval = yyvsp[-3]; yyval->children() = std::move(yyvsp[-1]->children()); }
#line 3733 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 33:
#line 338 "parser.yy"
                                                             { vsk_targeting(yyvsp[-2]); yyval = yyvsp[-2]; }
#line 3739 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 34:
#line 339 "parser.yy"
                                                             { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_ERL); }
#line 3745 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 35:
#line 340 "parser.yy"
                                                             { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_ERR); }
#line 3751 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 36:
#line 341 "parser.yy"
                                                             { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_RND, { yyvsp[-1] }); }
#line 3757 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 37:
#line 342 "parser.yy"
                                                             { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_RND); }
#line 3763 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 38:
#line 343 "parser.yy"
                                                                 { vsk_targeting(yyvsp[-5]); yyval = vsk_ast(INSN_VARPTR, { yyvsp[-3], yyvsp[-1] }); }
#line 3769 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 39:
#line 344 "parser.yy"
                                                                 { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_VARPTR, { yyvsp[-1] }); }
#line 3775 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 40:
#line 345 "parser.yy"
                                                                        {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_SEARCH, { yyvsp[-3], yyvsp[-1] });
    }
#line 3784 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 41:
#line 349 "parser.yy"
                                                                                            {
        vsk_targeting(yyvsp[-7]);
        yyval = vsk_ast(INSN_SEARCH, { yyvsp[-5], yyvsp[-3], yyvsp[-1] });
    }
#line 3793 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 42:
#line 353 "parser.yy"
                                                                                                                {
        vsk_targeting(yyvsp[-9]);
        yyval = vsk_ast(INSN_SEARCH, { yyvsp[-7], yyvsp[-5], yyvsp[-3], yyvsp[-1] });
    }
#line 3802 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 43:
#line 357 "parser.yy"
                                               { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_LOF, { yyvsp[-1] }); }
#line 3808 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 44:
#line 358 "parser.yy"
                                               { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_LOF, { yyvsp[-1] }); }
#line 3814 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 45:
#line 359 "parser.yy"
                                               { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_EOF, { yyvsp[-1] }); }
#line 3820 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 46:
#line 360 "parser.yy"
                                               { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_EOF, { yyvsp[-1] }); }
#line 3826 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 47:
#line 361 "parser.yy"
                                               { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_LOC, { yyvsp[-1] }); }
#line 3832 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 48:
#line 362 "parser.yy"
                                               { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_LOC, { yyvsp[-1] }); }
#line 3838 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 49:
#line 363 "parser.yy"
                                                { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_FPOS, { yyvsp[-1] }); }
#line 3844 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 50:
#line 364 "parser.yy"
                                                { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_FPOS, { yyvsp[-1] }); }
#line 3850 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 51:
#line 365 "parser.yy"
                                                                            { vsk_targeting(yyvsp[-5]); yyval = vsk_ast(INSN_INPUT_dollar, { yyvsp[-3], yyvsp[-1] }); }
#line 3856 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 52:
#line 366 "parser.yy"
                                                       { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_INPUT_dollar, { yyvsp[-1] }); }
#line 3862 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 53:
#line 370 "parser.yy"
                                         { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_PARAM_LIST, { yyvsp[0] }); }
#line 3868 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 54:
#line 371 "parser.yy"
                                         { yyval = yyvsp[-2]; yyval->push_back(yyvsp[0]); }
#line 3874 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 55:
#line 375 "parser.yy"
                                                                { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_PARAM_LIST, { yyvsp[0] }); }
#line 3880 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 56:
#line 376 "parser.yy"
                                                {
        yyval = yyvsp[-2];
        yyval->insert(yyval->end(), yyvsp[-1]->begin(), yyvsp[-1]->end());
        yyval->push_back(yyvsp[0]);
    }
#line 3890 "C:/dev/VeySickProject/VeySicK/parser.cpp"
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
#line 3902 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 58:
#line 391 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_ABS); }
#line 3908 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 59:
#line 392 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_AKCNV_dollar); }
#line 3914 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 60:
#line 393 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_ASC); }
#line 3920 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 61:
#line 394 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_ATN); }
#line 3926 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 62:
#line 395 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_ATTR_dollar); }
#line 3932 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 63:
#line 396 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CDBL); }
#line 3938 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 64:
#line 397 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CHR_dollar); }
#line 3944 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 65:
#line 398 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CINT); }
#line 3950 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 66:
#line 399 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_COS); }
#line 3956 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 67:
#line 400 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CSNG); }
#line 3962 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 68:
#line 401 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CSRLIN); }
#line 3968 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 69:
#line 402 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CVD); }
#line 3974 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 70:
#line 403 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CVI); }
#line 3980 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 71:
#line 404 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CVS); }
#line 3986 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 72:
#line 405 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_DSKF); }
#line 3992 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 73:
#line 406 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_DSKI_dollar); }
#line 3998 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 74:
#line 407 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_EXP); }
#line 4004 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 75:
#line 408 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_FIX); }
#line 4010 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 76:
#line 409 "parser.yy"
                          { yyval = yyvsp[0]; }
#line 4016 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 77:
#line 410 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_FRE); }
#line 4022 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 78:
#line 411 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_HEX_dollar); }
#line 4028 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 79:
#line 412 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_INP); }
#line 4034 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 80:
#line 413 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_INSTR); }
#line 4040 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 81:
#line 414 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_INT); }
#line 4046 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 82:
#line 415 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_JIS_dollar); }
#line 4052 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 83:
#line 416 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_KACNV_dollar); }
#line 4058 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 84:
#line 417 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_KEXT_dollar); }
#line 4064 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 85:
#line 418 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_KINSTR); }
#line 4070 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 86:
#line 419 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_KLEN); }
#line 4076 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 87:
#line 420 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_KMID_dollar); }
#line 4082 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 88:
#line 421 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_KNJ_dollar); }
#line 4088 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 89:
#line 422 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_KPOS); }
#line 4094 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 90:
#line 423 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_KTYPE); }
#line 4100 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 91:
#line 424 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_LEFT_dollar); }
#line 4106 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 92:
#line 425 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_LEN); }
#line 4112 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 93:
#line 426 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_LOG); }
#line 4118 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 94:
#line 427 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_LPOS); }
#line 4124 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 95:
#line 428 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_MAP); }
#line 4130 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 96:
#line 429 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_MID_dollar_func); }
#line 4136 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 97:
#line 430 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_MKD_dollar); }
#line 4142 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 98:
#line 431 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_MKI_dollar); }
#line 4148 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 99:
#line 432 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_MKS_dollar); }
#line 4154 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 100:
#line 433 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_MOUSE_func); }
#line 4160 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 101:
#line 434 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_OCT_dollar); }
#line 4166 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 102:
#line 435 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_PEEK); }
#line 4172 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 103:
#line 436 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_PEN); }
#line 4178 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 104:
#line 437 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_POINT_func); }
#line 4184 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 105:
#line 438 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_POS); }
#line 4190 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 106:
#line 439 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_RIGHT_dollar); }
#line 4196 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 107:
#line 440 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_SGN); }
#line 4202 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 108:
#line 441 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_SIN); }
#line 4208 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 109:
#line 442 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_SPACE_dollar); }
#line 4214 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 110:
#line 443 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_SQR); }
#line 4220 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 111:
#line 444 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_STRING_dollar); }
#line 4226 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 112:
#line 445 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_STR_dollar); }
#line 4232 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 113:
#line 446 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_TAN); }
#line 4238 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 114:
#line 447 "parser.yy"
                          { yyval = yyvsp[0]; }
#line 4244 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 115:
#line 448 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_VAL); }
#line 4250 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 116:
#line 449 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_VIEW_func); }
#line 4256 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 117:
#line 450 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_WINDOW_func); }
#line 4262 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 118:
#line 454 "parser.yy"
                                                         { yyval = yyvsp[0]; }
#line 4268 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 119:
#line 455 "parser.yy"
                                                         { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_HAT, { yyvsp[-2], yyvsp[0] }); }
#line 4274 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 120:
#line 458 "parser.yy"
                                       { yyval = yyvsp[0]; }
#line 4280 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 121:
#line 459 "parser.yy"
                                       { yyval = yyvsp[0]; }
#line 4286 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 122:
#line 460 "parser.yy"
                                       { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_UMINUS, { yyvsp[0] }); }
#line 4292 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 123:
#line 464 "parser.yy"
                                                             { yyval = yyvsp[0]; }
#line 4298 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 124:
#line 465 "parser.yy"
                                                             { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_MUL, { yyvsp[-2], yyvsp[0] }); }
#line 4304 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 125:
#line 466 "parser.yy"
                                                             { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_DIV, { yyvsp[-2], yyvsp[0] }); }
#line 4310 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 126:
#line 470 "parser.yy"
                                                                    { yyval = yyvsp[0]; }
#line 4316 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 127:
#line 471 "parser.yy"
                                                                    { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_IDIV, { yyvsp[-2], yyvsp[0] }); }
#line 4322 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 128:
#line 475 "parser.yy"
                                                       { yyval = yyvsp[0]; }
#line 4328 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 129:
#line 476 "parser.yy"
                                                       { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_MOD, { yyvsp[-2], yyvsp[0] }); }
#line 4334 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 130:
#line 480 "parser.yy"
                                                     { yyval = yyvsp[0]; }
#line 4340 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 131:
#line 481 "parser.yy"
                                                     { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_ADD, { yyvsp[-2], yyvsp[0] }); }
#line 4346 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 132:
#line 482 "parser.yy"
                                                     { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_SUB, { yyvsp[-2], yyvsp[0] }); }
#line 4352 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 133:
#line 486 "parser.yy"
                                                            { yyval = yyvsp[0]; }
#line 4358 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 134:
#line 487 "parser.yy"
                                                            { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_LT, { yyvsp[-2], yyvsp[0] }); }
#line 4364 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 135:
#line 488 "parser.yy"
                                                            { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_LE, { yyvsp[-2], yyvsp[0] }); }
#line 4370 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 136:
#line 489 "parser.yy"
                                                            { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_GT, { yyvsp[-2], yyvsp[0] }); }
#line 4376 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 137:
#line 490 "parser.yy"
                                                            { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_GE, { yyvsp[-2], yyvsp[0] }); }
#line 4382 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 138:
#line 491 "parser.yy"
                                                            { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_EQUAL, { yyvsp[-2], yyvsp[0] }); }
#line 4388 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 139:
#line 492 "parser.yy"
                                                            { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_NE, { yyvsp[-2], yyvsp[0] }); }
#line 4394 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 140:
#line 496 "parser.yy"
                                                        { yyval = yyvsp[0]; }
#line 4400 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 141:
#line 497 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_NOT, { yyvsp[0] });}
#line 4406 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 142:
#line 501 "parser.yy"
                                                        { yyval = yyvsp[0]; }
#line 4412 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 143:
#line 502 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_AND, { yyvsp[-2], yyvsp[0] }); }
#line 4418 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 144:
#line 506 "parser.yy"
                                                        { yyval = yyvsp[0]; }
#line 4424 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 145:
#line 507 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_OR, { yyvsp[-2], yyvsp[0] }); }
#line 4430 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 146:
#line 511 "parser.yy"
                                                        { yyval = yyvsp[0]; }
#line 4436 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 147:
#line 512 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_XOR, { yyvsp[-2], yyvsp[0] }); }
#line 4442 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 148:
#line 516 "parser.yy"
                                                        { yyval = yyvsp[0]; }
#line 4448 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 149:
#line 517 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_IMP, { yyvsp[-2], yyvsp[0] }); }
#line 4454 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 150:
#line 521 "parser.yy"
                                                        { yyval = yyvsp[0]; }
#line 4460 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 151:
#line 522 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_EQV, { yyvsp[-2], yyvsp[0] }); }
#line 4466 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 152:
#line 526 "parser.yy"
                                                        { yyval = yyvsp[0]; }
#line 4472 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 153:
#line 530 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast_str("AND"); }
#line 4478 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 154:
#line 531 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast_str("OR"); }
#line 4484 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 155:
#line 532 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast_str("XOR"); }
#line 4490 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 156:
#line 533 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast_str("PSET"); }
#line 4496 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 157:
#line 534 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast_str("PRESET"); }
#line 4502 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 158:
#line 538 "parser.yy"
                                                        { yyval = yyvsp[0]; }
#line 4508 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 159:
#line 539 "parser.yy"
                                                        { yyval = yyvsp[0]; }
#line 4514 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 160:
#line 543 "parser.yy"
                                                        { yyval = yyvsp[0]; }
#line 4520 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 161:
#line 544 "parser.yy"
                                                        { yyval = yyvsp[0]; }
#line 4526 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 162:
#line 548 "parser.yy"
                                                        { vsk_targeting(yyvsp[-2]); yyval = vsk_ast(INSN_FIELD_ITEM, { yyvsp[-2], yyvsp[-1], yyvsp[0] }); }
#line 4532 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 163:
#line 552 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_FIELD_ITEMS, { yyvsp[0] }); }
#line 4538 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 164:
#line 553 "parser.yy"
                                                        { yyval = yyvsp[-2]; yyval->push_back(yyvsp[0]); }
#line 4544 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 165:
#line 557 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_REM, yyvsp[0]->m_str); }
#line 4550 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 166:
#line 558 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_LABEL_DEF, yyvsp[0]->m_str); }
#line 4556 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 167:
#line 560 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_LET, { yyvsp[-2], yyvsp[0] }); }
#line 4562 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 168:
#line 561 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_LET, { yyvsp[-2], yyvsp[0] }); }
#line 4568 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 169:
#line 563 "parser.yy"
                                                                                         {
        vsk_targeting(yyvsp[-6]);
        yyval = vsk_ast(INSN_PRINT_USING, { yyvsp[-5], yyvsp[-2], yyvsp[0] });
    }
#line 4577 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 170:
#line 567 "parser.yy"
                                                                                      {
        vsk_targeting(yyvsp[-6]);
        yyval = vsk_ast(INSN_PRINT_USING, { yyvsp[-5], yyvsp[-2], yyvsp[0] });
    }
#line 4586 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 171:
#line 571 "parser.yy"
                                                             {
        vsk_targeting(yyvsp[-4]);
        yyval = vsk_ast(INSN_PRINT_USING, { nullptr, yyvsp[-2], yyvsp[0] });
    }
#line 4595 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 172:
#line 576 "parser.yy"
                                                      {
        vsk_targeting(yyvsp[-3]);
        yyval = vsk_ast(INSN_PRINT, { yyvsp[-2], yyvsp[0] });
    }
#line 4604 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 173:
#line 580 "parser.yy"
                                               {
        vsk_targeting(yyvsp[-3]);
        yyval = vsk_ast(INSN_PRINT, { yyvsp[-2], yyvsp[0] });
    }
#line 4613 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 174:
#line 584 "parser.yy"
                          {
        vsk_targeting(yyvsp[-1]);
        yyval = vsk_ast(INSN_PRINT, { nullptr, yyvsp[0] });
    }
#line 4622 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 175:
#line 588 "parser.yy"
            {
        vsk_targeting(yyvsp[0]);
        yyval = vsk_ast(INSN_PRINT, { nullptr, nullptr });
    }
#line 4631 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 176:
#line 593 "parser.yy"
                                                      {
        vsk_targeting(yyvsp[-3]);
        yyval = vsk_ast(INSN_WRITE, { yyvsp[-2], yyvsp[0] });
    }
#line 4640 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 177:
#line 597 "parser.yy"
                                                   {
        vsk_targeting(yyvsp[-3]);
        yyval = vsk_ast(INSN_WRITE, { yyvsp[-2], yyvsp[0] });
    }
#line 4649 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 178:
#line 601 "parser.yy"
                             {
        vsk_targeting(yyvsp[-1]);
        yyval = vsk_ast(INSN_WRITE, { nullptr, yyvsp[0] });
    }
#line 4658 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 179:
#line 605 "parser.yy"
               {
        vsk_targeting(yyvsp[0]);
        yyval = vsk_ast(INSN_WRITE, { nullptr, nullptr });
    }
#line 4667 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 180:
#line 610 "parser.yy"
                                                                 {
        vsk_targeting(yyvsp[-4]);
        yyval = vsk_ast(INSN_LPRINT_USING, { yyvsp[-2], yyvsp[0] });
    }
#line 4676 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 181:
#line 615 "parser.yy"
                              {
        vsk_targeting(yyvsp[-1]);
        yyval = vsk_ast(INSN_LPRINT, { yyvsp[0] });
    }
#line 4685 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 182:
#line 619 "parser.yy"
                {
        vsk_targeting(yyvsp[0]);
        yyval = vsk_ast(INSN_LPRINT, { nullptr });
    }
#line 4694 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 183:
#line 624 "parser.yy"
                                                                            {
        vsk_targeting(yyvsp[-7]);
        yyval = vsk_ast(INSN_FOR, { yyvsp[-6], yyvsp[-4], yyvsp[-2], yyvsp[0] });
    }
#line 4703 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 184:
#line 628 "parser.yy"
                                                         {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_FOR, { yyvsp[-4], yyvsp[-2], yyvsp[0], nullptr });
    }
#line 4712 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 185:
#line 633 "parser.yy"
                          {
        vsk_targeting(yyvsp[-1]);
        yyval = vsk_ast(INSN_NEXT);
        yyval->insert(yyval->end(), yyvsp[0]->begin(), yyvsp[0]->end());
    }
#line 4722 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 186:
#line 638 "parser.yy"
              {
        vsk_targeting(yyvsp[0]);
        yyval = vsk_ast(INSN_NEXT);
    }
#line 4731 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 187:
#line 642 "parser.yy"
                                                                        {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_OPEN, { yyvsp[-4], yyvsp[-2], yyvsp[-1], yyvsp[0] });
    }
#line 4740 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 188:
#line 646 "parser.yy"
                                                                   {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_OPEN, { yyvsp[-4], yyvsp[-2], yyvsp[-1], yyvsp[0] });
    }
#line 4749 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 189:
#line 650 "parser.yy"
                                                                       {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_OPEN, { yyvsp[-4], yyvsp[-2], yyvsp[-1], yyvsp[0] });
    }
#line 4758 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 190:
#line 654 "parser.yy"
                                                                  {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_OPEN, { yyvsp[-4], yyvsp[-2], yyvsp[-1], yyvsp[0] });
    }
#line 4767 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 191:
#line 658 "parser.yy"
                                                   {
        vsk_targeting(yyvsp[-3]);
        yyval = vsk_ast(INSN_OPEN, { yyvsp[-2], nullptr, yyvsp[-1], yyvsp[0] });
    }
#line 4776 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 192:
#line 662 "parser.yy"
                                                  {
        vsk_targeting(yyvsp[-3]);
        yyval = vsk_ast(INSN_OPEN, { yyvsp[-2], nullptr, yyvsp[-1], yyvsp[0] });
    }
#line 4785 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 193:
#line 666 "parser.yy"
                                                            {
        vsk_targeting(yyvsp[-4]);
        yyval = vsk_ast(INSN_LINE_INPUT, { yyvsp[-2], yyvsp[0] });
    }
#line 4794 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 194:
#line 670 "parser.yy"
                              {
        vsk_targeting(yyvsp[-2]);
        yyval = vsk_ast(INSN_LINE_INPUT, { nullptr, yyvsp[0] });
    }
#line 4803 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 195:
#line 674 "parser.yy"
                                                   {
        vsk_targeting(yyvsp[-4]);
        yyval = vsk_ast(INSN_LINE_INPUT_sharp, { yyvsp[-2], yyvsp[0] });
    }
#line 4812 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 196:
#line 678 "parser.yy"
                                                       {
        vsk_targeting(yyvsp[-4]);
        yyval = vsk_ast(INSN_LINE_INPUT_sharp, { yyvsp[-2], yyvsp[0] });
    }
#line 4821 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 197:
#line 682 "parser.yy"
                       {
        vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_KINPUT, { yyvsp[0] });
    }
#line 4829 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 198:
#line 685 "parser.yy"
                                                                                        {
        vsk_targeting(yyvsp[-7]);
        yyval = vsk_ast(INSN_LINE_INPUT_WAIT, { yyvsp[-4], yyvsp[-2], yyvsp[0] });
    }
#line 4838 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 199:
#line 689 "parser.yy"
                                                          {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_LINE_INPUT_WAIT, { yyvsp[-2], nullptr, yyvsp[0] });
    }
#line 4847 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 200:
#line 693 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_DIM, { yyvsp[0] }); }
#line 4853 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 201:
#line 694 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_DEF_SEG, { yyvsp[0] }); }
#line 4859 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 202:
#line 695 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_DEF_USR, { yyvsp[-2], yyvsp[0] }); }
#line 4865 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 203:
#line 696 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_ON_COM_GOSUB, { yyvsp[0] }); }
#line 4871 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 204:
#line 697 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_ON_ERROR_GOTO, { yyvsp[0] }); }
#line 4877 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 205:
#line 698 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_ON_EXPR_GOTO, { yyvsp[-2], yyvsp[0] }); }
#line 4883 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 206:
#line 699 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_ON_EXPR_GOSUB, { yyvsp[-2], yyvsp[0] }); }
#line 4889 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 207:
#line 700 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_ON_HELP_GOSUB, { yyvsp[0] }); }
#line 4895 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 208:
#line 701 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_ON_KEY_GOSUB, { yyvsp[0] }); }
#line 4901 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 209:
#line 702 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_ON_PEN_GOSUB, { yyvsp[0] }); }
#line 4907 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 210:
#line 703 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_ON_PLAY_GOSUB, { yyvsp[0] }); }
#line 4913 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 211:
#line 704 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_ON_STOP_GOSUB, { yyvsp[0] }); }
#line 4919 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 212:
#line 705 "parser.yy"
                                                                 {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_ON_TIME_dollar_GOSUB, { yyvsp[-2], yyvsp[0] });
    }
#line 4928 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 213:
#line 709 "parser.yy"
                                                                         {
        vsk_targeting(yyvsp[-3]);
        yyval = vsk_ast(INSN_ON_MOUSE_GOSUB, { nullptr, yyvsp[0] });
    }
#line 4937 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 214:
#line 713 "parser.yy"
                                                                         {
        vsk_targeting(yyvsp[-6]);
        yyval = vsk_ast(INSN_ON_MOUSE_GOSUB, { yyvsp[-3], yyvsp[0] });
    }
#line 4946 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 215:
#line 717 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_GOSUB, { yyvsp[0] }); }
#line 4952 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 216:
#line 718 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast_goto(yyvsp[0]); }
#line 4958 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 217:
#line 719 "parser.yy"
                                                        { vsk_targeting(yyvsp[-2]); yyval = vsk_ast(INSN_CMD, { yyvsp[-1] }); yyval->insert(yyval->end(), yyvsp[0]->begin(), yyvsp[0]->end()); }
#line 4964 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 218:
#line 720 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_CMD, { yyvsp[0] }); }
#line 4970 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 219:
#line 721 "parser.yy"
                                                        { yyval = yyvsp[-2]; yyval->insert(yyval->end(), yyvsp[0]->begin(), yyvsp[0]->end()); }
#line 4976 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 220:
#line 722 "parser.yy"
                                                        { yyval = yyvsp[0]; }
#line 4982 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 221:
#line 723 "parser.yy"
                                                        { yyval = yyvsp[-1]; yyval->insert(yyval->end(), yyvsp[0]->begin(), yyvsp[0]->end()); }
#line 4988 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 222:
#line 724 "parser.yy"
                                                        { yyval = yyvsp[0]; }
#line 4994 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 223:
#line 725 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_INPUT_semicolon, { yyvsp[-2], yyvsp[0] }); }
#line 5000 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 224:
#line 726 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_INPUT, { yyvsp[-2], yyvsp[0] }); }
#line 5006 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 225:
#line 727 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_INPUT, { nullptr, yyvsp[0] }); }
#line 5012 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 226:
#line 728 "parser.yy"
                                                                              {
        vsk_targeting(yyvsp[-6]);
        yyval = vsk_ast(INSN_INPUT_WAIT_semicolon, { yyvsp[-4], yyvsp[-2], yyvsp[0] });
    }
#line 5021 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 227:
#line 732 "parser.yy"
                                                                              {
        vsk_targeting(yyvsp[-4]);
        yyval = vsk_ast(INSN_INPUT_WAIT_semicolon, { yyvsp[-2], nullptr, yyvsp[0] });
    }
#line 5030 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 228:
#line 736 "parser.yy"
                                                                          {
        vsk_targeting(yyvsp[-6]);
        yyval = vsk_ast(INSN_INPUT_WAIT, { yyvsp[-4], yyvsp[-2], yyvsp[0] });
    }
#line 5039 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 229:
#line 740 "parser.yy"
                                                                          {
        vsk_targeting(yyvsp[-4]);
        yyval = vsk_ast(INSN_INPUT_WAIT, { yyvsp[-2], nullptr, yyvsp[0] });
    }
#line 5048 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 230:
#line 744 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_LSET, { yyvsp[-2], yyvsp[0] }); }
#line 5054 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 231:
#line 745 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_RSET, { yyvsp[-2], yyvsp[0] }); }
#line 5060 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 232:
#line 746 "parser.yy"
                                                        { vsk_targeting(yyvsp[-2]); yyval = vsk_ast(INSN_TIME_dollar, { yyvsp[0] }); }
#line 5066 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 233:
#line 747 "parser.yy"
                                                        { vsk_targeting(yyvsp[-2]); yyval = vsk_ast(INSN_DATE_dollar, { yyvsp[0] }); }
#line 5072 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 234:
#line 748 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_DELETE, { yyvsp[0] }); }
#line 5078 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 235:
#line 749 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_RESUME, { yyvsp[0] }); }
#line 5084 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 236:
#line 750 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_RESUME, { yyvsp[0] }); }
#line 5090 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 237:
#line 751 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_RESUME);}
#line 5096 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 238:
#line 753 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_GET_sharp, { yyvsp[-2], yyvsp[0] }); }
#line 5102 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 239:
#line 754 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_GET_sharp, { yyvsp[0], nullptr }); }
#line 5108 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 240:
#line 755 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_GET_sharp, { yyvsp[-2], yyvsp[0] }); }
#line 5114 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 241:
#line 756 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_GET_sharp, { yyvsp[0], nullptr }); }
#line 5120 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 242:
#line 758 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_PUT_sharp, { yyvsp[-2], yyvsp[0] });}
#line 5126 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 243:
#line 759 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_PUT_sharp, { yyvsp[0], nullptr });}
#line 5132 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 244:
#line 760 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_PUT_sharp, { yyvsp[-2], yyvsp[0] });}
#line 5138 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 245:
#line 761 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_PUT_sharp, { yyvsp[0], nullptr });}
#line 5144 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 246:
#line 763 "parser.yy"
                                                                                                                                                        {
        vsk_targeting(yyvsp[-14]);
        yyval = vsk_ast(INSN_GET_at_STEP, { yyvsp[-12], yyvsp[-10], yyvsp[-5], yyvsp[-3], yyvsp[0] });
    }
#line 5153 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 247:
#line 768 "parser.yy"
                                                                                                                                                        {
        vsk_targeting(yyvsp[-13]);
        yyval = vsk_ast(INSN_GET_at, { yyvsp[-11], yyvsp[-9], yyvsp[-5], yyvsp[-3], yyvsp[0] });
    }
#line 5162 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 248:
#line 772 "parser.yy"
                                                                                                                                                                                    {
        // PUT@(50,50),KANJI(...),OP,color1,color2
        vsk_targeting(yyvsp[-16]);
        yyval = vsk_ast(INSN_PUT_at_KANJI, { yyvsp[-14], yyvsp[-12], yyvsp[-7], yyvsp[-4], yyvsp[-2], yyvsp[0] });
    }
#line 5172 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 249:
#line 777 "parser.yy"
                                                                                                                                                                      {
        // PUT@(50,50),KANJI(...),,color1,color2
        vsk_targeting(yyvsp[-15]);
        yyval = vsk_ast(INSN_PUT_at_KANJI, { yyvsp[-13], yyvsp[-11], yyvsp[-6], yyvsp[-3], yyvsp[-2], yyvsp[0] });
    }
#line 5182 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 250:
#line 782 "parser.yy"
                                                                                                                                            {
        // PUT@(50,50),KANJI(...),OP
        vsk_targeting(yyvsp[-12]);
        yyval = vsk_ast(INSN_PUT_at_KANJI, { yyvsp[-10], yyvsp[-8], yyvsp[-3], yyvsp[0] });
    }
#line 5192 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 251:
#line 787 "parser.yy"
                                                                                                                     {
        // PUT@(50,50),KANJI(...)
        vsk_targeting(yyvsp[-10]);
        yyval = vsk_ast(INSN_PUT_at_KANJI, { yyvsp[-8], yyvsp[-6], yyvsp[-1] });
    }
#line 5202 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 252:
#line 792 "parser.yy"
                                                                                                                                                 {
        vsk_targeting(yyvsp[-13]);
        yyval = vsk_ast(INSN_PUT_at, { yyvsp[-11], yyvsp[-9], yyvsp[-6], yyvsp[-4], yyvsp[-2], yyvsp[0] });
    }
#line 5211 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 253:
#line 796 "parser.yy"
                                                                                                         {
        vsk_targeting(yyvsp[-9]);
        yyval = vsk_ast(INSN_PUT_at, { yyvsp[-7], yyvsp[-5], yyvsp[-2], yyvsp[0] });
    }
#line 5220 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 254:
#line 800 "parser.yy"
                                                                                  {
        vsk_targeting(yyvsp[-7]);
        yyval = vsk_ast(INSN_PUT_at, { yyvsp[-5], yyvsp[-3], yyvsp[0] });
    }
#line 5229 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 255:
#line 805 "parser.yy"
                                                                                                             {
        vsk_targeting(yyvsp[-9]);
        yyval = vsk_ast(INSN_CHAIN_MERGE_ALL_DELETE, { yyvsp[-7], yyvsp[-5], yyvsp[0] });
    }
#line 5238 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 256:
#line 809 "parser.yy"
                                                                               {
        vsk_targeting(yyvsp[-6]);
        yyval = vsk_ast(INSN_CHAIN_MERGE_ALL, { yyvsp[-4], yyvsp[-2] });
    }
#line 5247 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 257:
#line 813 "parser.yy"
                                                                                      {
        vsk_targeting(yyvsp[-7]);
        yyval = vsk_ast(INSN_CHAIN_MERGE_DELETE, { yyvsp[-5], yyvsp[-3] });
    }
#line 5256 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 258:
#line 817 "parser.yy"
                                                        {
        vsk_targeting(yyvsp[-4]);
        yyval = vsk_ast(INSN_CHAIN_MERGE, { yyvsp[-2], yyvsp[0] });
    }
#line 5265 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 259:
#line 821 "parser.yy"
                                   {
        vsk_targeting(yyvsp[-2]);
        yyval = vsk_ast(INSN_CHAIN_MERGE, { yyvsp[0] });
    }
#line 5274 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 260:
#line 825 "parser.yy"
                                                 {
        vsk_targeting(yyvsp[-3]);
        yyval = vsk_ast(INSN_CHAIN, { yyvsp[-2], nullptr, yyvsp[0] });
    }
#line 5283 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 261:
#line 829 "parser.yy"
                                                                      {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_CHAIN, { yyvsp[-4], yyvsp[-2], yyvsp[0] });
    }
#line 5292 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 262:
#line 833 "parser.yy"
                                               {
        vsk_targeting(yyvsp[-3]);
        yyval = vsk_ast(INSN_CHAIN, { yyvsp[-2], yyvsp[0] });
    }
#line 5301 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 263:
#line 837 "parser.yy"
                          {
        vsk_targeting(yyvsp[-1]);
        yyval = vsk_ast(INSN_CHAIN, { yyvsp[0] });
    }
#line 5310 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 264:
#line 841 "parser.yy"
                                       {
        vsk_targeting(yyvsp[-3]);
        yyval = vsk_ast(INSN_DEF_FN, { yyvsp[-2], nullptr, yyvsp[0] });
    }
#line 5319 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 265:
#line 845 "parser.yy"
                                                             {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_DEF_FN, { yyvsp[-4], nullptr, yyvsp[0] });
    }
#line 5328 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 266:
#line 849 "parser.yy"
                                                                         {
        vsk_targeting(yyvsp[-6]);
        yyval = vsk_ast(INSN_DEF_FN, { yyvsp[-5], yyvsp[-3], yyvsp[0] });
    }
#line 5337 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 267:
#line 853 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_COM_OFF); }
#line 5343 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 268:
#line 854 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_COM_ON); }
#line 5349 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 269:
#line 855 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_COM_STOP); }
#line 5355 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 270:
#line 856 "parser.yy"
                                                        { vsk_targeting(yyvsp[-4]); yyval = vsk_ast(INSN_MOUSE_OFF, { yyvsp[-2] }); }
#line 5361 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 271:
#line 857 "parser.yy"
                                                        { vsk_targeting(yyvsp[-4]); yyval = vsk_ast(INSN_MOUSE_ON, { yyvsp[-2] }); }
#line 5367 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 272:
#line 858 "parser.yy"
                                                        { vsk_targeting(yyvsp[-4]); yyval = vsk_ast(INSN_MOUSE_STOP, { yyvsp[-2] }); }
#line 5373 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 273:
#line 859 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_MOUSE_OFF, { nullptr }); }
#line 5379 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 274:
#line 860 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_MOUSE_ON, { nullptr }); }
#line 5385 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 275:
#line 861 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_MOUSE_STOP, { nullptr }); }
#line 5391 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 276:
#line 862 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_PEN_OFF); }
#line 5397 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 277:
#line 863 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_PEN_ON); }
#line 5403 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 278:
#line 864 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_PEN_STOP); }
#line 5409 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 279:
#line 865 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_PLAY_OFF); }
#line 5415 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 280:
#line 866 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_PLAY_ON); }
#line 5421 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 281:
#line 867 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_PLAY_STOP); }
#line 5427 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 282:
#line 868 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_HELP_OFF); }
#line 5433 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 283:
#line 869 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_HELP_ON); }
#line 5439 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 284:
#line 870 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_HELP_STOP); }
#line 5445 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 285:
#line 871 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_TIME_dollar_OFF); }
#line 5451 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 286:
#line 872 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_TIME_dollar_ON); }
#line 5457 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 287:
#line 873 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_TIME_dollar_STOP); }
#line 5463 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 288:
#line 874 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_STOP_OFF); }
#line 5469 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 289:
#line 875 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_STOP_ON); }
#line 5475 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 290:
#line 876 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_STOP_STOP); }
#line 5481 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 291:
#line 877 "parser.yy"
                                                                            {
        vsk_targeting(yyvsp[-6]);
        yyval = vsk_ast(INSN_POINT_STEP, { yyvsp[-3], yyvsp[-1] });
    }
#line 5490 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 292:
#line 881 "parser.yy"
                                                                            {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_POINT, { yyvsp[-3], yyvsp[-1] });
    }
#line 5499 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 293:
#line 885 "parser.yy"
                                 {
        vsk_targeting(yyvsp[-1]);
        yyval = vsk_ast(INSN_EDIT, { yyvsp[0] });
    }
#line 5508 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 294:
#line 889 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_TROFF); }
#line 5514 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 295:
#line 890 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_TRON); }
#line 5520 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 296:
#line 891 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_LIST, { yyvsp[0] }); }
#line 5526 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 297:
#line 892 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_LIST); }
#line 5532 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 298:
#line 893 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_LLIST, { yyvsp[0] }); }
#line 5538 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 299:
#line 894 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_LLIST); }
#line 5544 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 300:
#line 895 "parser.yy"
                                                                     {
        vsk_targeting(yyvsp[-3]);
        yyvsp[0]->insert(yyvsp[0]->begin(), yyvsp[-2]);
        yyval = vsk_ast(INSN_CLOSE, { yyvsp[0] });
    }
#line 5554 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 301:
#line 900 "parser.yy"
                                {
        vsk_targeting(yyvsp[-1]);
        yyval = vsk_ast(INSN_CLOSE, { vsk_ast(INSN_FILE_NUMBERS, { yyvsp[0] }) });
    }
#line 5563 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 302:
#line 904 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_CLOSE, { yyvsp[0] }); }
#line 5569 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 303:
#line 905 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CLOSE, { nullptr }); }
#line 5575 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 304:
#line 906 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_RUN, { yyvsp[0], nullptr, nullptr }); }
#line 5581 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 305:
#line 907 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_RUN, { nullptr, yyvsp[-2], yyvsp[0] }); }
#line 5587 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 306:
#line 908 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_RUN, { nullptr, yyvsp[0], nullptr }); }
#line 5593 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 307:
#line 909 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_RUN, { nullptr, nullptr, nullptr }); }
#line 5599 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 308:
#line 910 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_LOAD, { yyvsp[-2], yyvsp[0] }); }
#line 5605 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 309:
#line 911 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_LOAD, { yyvsp[0], nullptr }); }
#line 5611 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 310:
#line 912 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_RESTORE, { yyvsp[0] }); }
#line 5617 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 311:
#line 913 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_RESTORE); }
#line 5623 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 312:
#line 914 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_ERASE, { yyvsp[0] }); }
#line 5629 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 313:
#line 915 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_SWAP, { yyvsp[-2], yyvsp[0] }); }
#line 5635 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 314:
#line 916 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_STOP); }
#line 5641 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 315:
#line 917 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_FIELD, { yyvsp[-2], yyvsp[0] }); }
#line 5647 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 316:
#line 918 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_FIELD, { yyvsp[-2], yyvsp[0] }); }
#line 5653 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 317:
#line 919 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_FIELD, { yyvsp[-2], yyvsp[0] }); }
#line 5659 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 318:
#line 920 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_RETURN, { yyvsp[0] }); }
#line 5665 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 319:
#line 921 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_RETURN); }
#line 5671 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 320:
#line 922 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_NAME, { yyvsp[-2], yyvsp[-1], yyvsp[0] }); }
#line 5677 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 321:
#line 923 "parser.yy"
                                                                   { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_PLAY, { yyvsp[-2], yyvsp[0] }); }
#line 5683 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 322:
#line 924 "parser.yy"
                                                                   { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_PLAY, { nullptr, yyvsp[0] }); }
#line 5689 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 323:
#line 925 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_AUTO, { yyvsp[-2], yyvsp[0] }); }
#line 5695 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 324:
#line 926 "parser.yy"
                                                        { vsk_targeting(yyvsp[-2]); yyval = vsk_ast(INSN_AUTO, { nullptr, yyvsp[0] }); }
#line 5701 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 325:
#line 927 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_AUTO, { yyvsp[0], nullptr }); }
#line 5707 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 326:
#line 928 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_AUTO, { nullptr, nullptr }); }
#line 5713 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 327:
#line 929 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_WIDTH_sharp, { yyvsp[-2], yyvsp[0] }); }
#line 5719 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 328:
#line 930 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_WIDTH_sharp, { yyvsp[-2], yyvsp[0] }); }
#line 5725 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 329:
#line 931 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = yyvsp[0]; }
#line 5731 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 330:
#line 935 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_DIM_LIST, { yyvsp[0] }); }
#line 5737 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 331:
#line 936 "parser.yy"
                                                        { yyval = yyvsp[-2]; yyval->push_back(yyvsp[0]); }
#line 5743 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 332:
#line 940 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_IDENT_LIST, { yyvsp[0] }); }
#line 5749 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 333:
#line 941 "parser.yy"
                                                        { yyval = yyvsp[-2]; yyval->push_back(yyvsp[0]); }
#line 5755 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 334:
#line 945 "parser.yy"
                            { yyval = yyvsp[0]; }
#line 5761 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 335:
#line 946 "parser.yy"
                            { yyval = yyvsp[0]; }
#line 5767 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 336:
#line 950 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_PRINTING, { yyvsp[0] }); }
#line 5773 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 337:
#line 951 "parser.yy"
                                                        { yyval = yyvsp[-1]; yyval->push_back(yyvsp[0]); }
#line 5779 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 338:
#line 955 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_PRINTING, { yyvsp[0] }); }
#line 5785 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 339:
#line 956 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = yyvsp[-1]; yyval->push_back(yyvsp[0]); }
#line 5791 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 340:
#line 957 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = yyvsp[-1]; yyval->push_back(vsk_ast(INSN_COMMA)); }
#line 5797 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 341:
#line 958 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = yyvsp[-1]; yyval->push_back(vsk_ast(INSN_SEMICOLON)); }
#line 5803 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 342:
#line 962 "parser.yy"
                            { yyval = yyvsp[0]; }
#line 5809 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 343:
#line 963 "parser.yy"
                            { yyval = yyvsp[0]; }
#line 5815 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 344:
#line 967 "parser.yy"
                            { yyval = yyvsp[0]; }
#line 5821 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 345:
#line 968 "parser.yy"
                            { yyval = yyvsp[0]; }
#line 5827 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 346:
#line 972 "parser.yy"
                                                { yyval = yyvsp[0]; }
#line 5833 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 347:
#line 973 "parser.yy"
                                                { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_SPC, { yyvsp[-1] });}
#line 5839 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 348:
#line 974 "parser.yy"
                                                { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_TAB, { yyvsp[-1] });}
#line 5845 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 349:
#line 975 "parser.yy"
                                                { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_COMMA); }
#line 5851 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 350:
#line 976 "parser.yy"
                                                { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_SEMICOLON); }
#line 5857 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 351:
#line 980 "parser.yy"
                                                { yyval = yyvsp[0]; }
#line 5863 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 352:
#line 981 "parser.yy"
                                                { yyval = yyvsp[0]; }
#line 5869 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 353:
#line 985 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_BEEP); }
#line 5875 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 354:
#line 986 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_BLOAD); }
#line 5881 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 355:
#line 987 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_BSAVE); }
#line 5887 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 356:
#line 988 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CALL); }
#line 5893 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 357:
#line 989 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CHILD); }
#line 5899 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 358:
#line 990 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CLEAR); }
#line 5905 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 359:
#line 991 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CLS); }
#line 5911 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 360:
#line 992 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_COLOR); }
#line 5917 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 361:
#line 993 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_COMMON); }
#line 5923 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 362:
#line 994 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CONSOLE); }
#line 5929 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 363:
#line 995 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CONT); }
#line 5935 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 364:
#line 996 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_COPY); }
#line 5941 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 365:
#line 997 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_DATA); }
#line 5947 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 366:
#line 998 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_DEFDBL); }
#line 5953 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 367:
#line 999 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_DEFINT); }
#line 5959 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 368:
#line 1000 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_DEFSNG); }
#line 5965 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 369:
#line 1001 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_DEFSTR); }
#line 5971 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 370:
#line 1002 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_DRAW); }
#line 5977 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 371:
#line 1003 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_DSKO_dollar); }
#line 5983 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 372:
#line 1004 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_END); }
#line 5989 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 373:
#line 1005 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_ERROR); }
#line 5995 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 374:
#line 1006 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_FILES); }
#line 6001 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 375:
#line 1007 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_KEY); }
#line 6007 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 376:
#line 1008 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_KEY_LIST); }
#line 6013 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 377:
#line 1009 "parser.yy"
                                                        { vsk_targeting(yyvsp[-4]); yyval = vsk_ast(INSN_KEY_OFF, { yyvsp[-2] }); }
#line 6019 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 378:
#line 1010 "parser.yy"
                                                        { vsk_targeting(yyvsp[-4]); yyval = vsk_ast(INSN_KEY_ON, { yyvsp[-2] }); }
#line 6025 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 379:
#line 1011 "parser.yy"
                                                        { vsk_targeting(yyvsp[-4]); yyval = vsk_ast(INSN_KEY_STOP, { yyvsp[-2] }); }
#line 6031 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 380:
#line 1012 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_KEY_OFF); }
#line 6037 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 381:
#line 1013 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_KEY_ON); }
#line 6043 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 382:
#line 1014 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_KEY_STOP); }
#line 6049 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 383:
#line 1015 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_KILL); }
#line 6055 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 384:
#line 1016 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_KPLOAD); }
#line 6061 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 385:
#line 1017 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_LFILES); }
#line 6067 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 386:
#line 1018 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_LOAD_question); }
#line 6073 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 387:
#line 1019 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_LOCATE); }
#line 6079 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 388:
#line 1020 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_MERGE); }
#line 6085 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 389:
#line 1021 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_MON); }
#line 6091 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 390:
#line 1022 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_MOTOR); }
#line 6097 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 391:
#line 1023 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_MOUSE_stmt); }
#line 6103 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 392:
#line 1024 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_NEW); }
#line 6109 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 393:
#line 1025 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_NEW_CMD); }
#line 6115 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 394:
#line 1026 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_NEW_ON); }
#line 6121 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 395:
#line 1027 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_OPTION_IDENT, { yyvsp[0] }); }
#line 6127 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 396:
#line 1028 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_OUT); }
#line 6133 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 397:
#line 1029 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_PLAY_ALLOC); }
#line 6139 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 398:
#line 1030 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_PLAY); }
#line 6145 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 399:
#line 1031 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_POKE); }
#line 6151 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 400:
#line 1032 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_RANDOMIZE); }
#line 6157 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 401:
#line 1033 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_READ); }
#line 6163 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 402:
#line 1034 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_RENUM); }
#line 6169 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 403:
#line 1035 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_ROLL); }
#line 6175 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 404:
#line 1036 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_SAVE); }
#line 6181 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 405:
#line 1037 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_SCREEN); }
#line 6187 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 406:
#line 1038 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_SET); }
#line 6193 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 407:
#line 1039 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_SET); }
#line 6199 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 408:
#line 1040 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_SYSTEM); }
#line 6205 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 409:
#line 1041 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_TERM); }
#line 6211 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 410:
#line 1042 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_WAIT); }
#line 6217 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 411:
#line 1043 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_WEND); }
#line 6223 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 412:
#line 1044 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_WHILE); }
#line 6229 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 413:
#line 1045 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_WIDTH); }
#line 6235 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 414:
#line 1046 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CHDIR); }
#line 6241 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 415:
#line 1047 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_MKDIR); }
#line 6247 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 416:
#line 1048 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_RMDIR); }
#line 6253 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 417:
#line 1049 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_WIDTH_LPRINT); }
#line 6259 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 418:
#line 1050 "parser.yy"
                                                                                                             {
        vsk_targeting(yyvsp[-9]);
        yyval = vsk_ast(INSN_MID_dollar_stmt, { yyvsp[-7], yyvsp[-5], yyvsp[-3], yyvsp[0] });
    }
#line 6268 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 419:
#line 1054 "parser.yy"
                                                                                                {
        vsk_targeting(yyvsp[-7]);
        yyval = vsk_ast(INSN_MID_dollar_stmt, { yyvsp[-5], yyvsp[-3], nullptr, yyvsp[0] });
    }
#line 6277 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 420:
#line 1061 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_INPUT_sharp, { yyvsp[0] });}
#line 6283 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 421:
#line 1062 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_INPUT_sharp, { yyvsp[0] });}
#line 6289 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 422:
#line 1063 "parser.yy"
                                                                                    {
        // LINE -STEP(100,100) likely
        vsk_targeting(yyvsp[-7]);
        yyval = vsk_ast(INSN_LINE1, { nullptr, nullptr, yyvsp[-3], yyvsp[-1] });
    }
#line 6299 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 423:
#line 1068 "parser.yy"
                                                                            {
        // LINE -(100,100) likely
        vsk_targeting(yyvsp[-6]);
        yyval = vsk_ast(INSN_LINE0, { nullptr, nullptr, yyvsp[-3], yyvsp[-1] });
    }
#line 6309 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 424:
#line 1073 "parser.yy"
                                                                                                                                                 {
        // LINE STEP(0,0)-STEP(100,100) likely
        vsk_targeting(yyvsp[-13]);
        yyval = vsk_ast(INSN_LINE3, { yyvsp[-10], yyvsp[-8], yyvsp[-3], yyvsp[-1] });
    }
#line 6319 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 425:
#line 1078 "parser.yy"
                                                                                                                                         {
        // LINE STEP(0,0)-(100,100) likely
        vsk_targeting(yyvsp[-12]);
        yyval = vsk_ast(INSN_LINE2, { yyvsp[-9], yyvsp[-7], yyvsp[-3], yyvsp[-1] });
    }
#line 6329 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 426:
#line 1083 "parser.yy"
                                                                                                                                         {
        // LINE(0,0)-STEP(100,100) likely
        vsk_targeting(yyvsp[-12]);
        yyval = vsk_ast(INSN_LINE1, { yyvsp[-10], yyvsp[-8], yyvsp[-3], yyvsp[-1] });
    }
#line 6339 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 427:
#line 1088 "parser.yy"
                                                                                                                                 {
        // LINE(0,0)-(100,100) likely
        vsk_targeting(yyvsp[-11]);
        yyval = vsk_ast(INSN_LINE0, { yyvsp[-9], yyvsp[-7], yyvsp[-3], yyvsp[-1] });
    }
#line 6349 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 428:
#line 1093 "parser.yy"
                                                                                         {
        vsk_targeting(yyvsp[-7]);
        yyval = vsk_ast(INSN_CIRCLE, { yyvsp[-5], yyvsp[-3], yyvsp[0] });
    }
#line 6358 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 429:
#line 1097 "parser.yy"
                                                                                                 {
        vsk_targeting(yyvsp[-8]);
        yyval = vsk_ast(INSN_CIRCLE_STEP, { yyvsp[-5], yyvsp[-3], yyvsp[0] });
    }
#line 6367 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 430:
#line 1101 "parser.yy"
                                                                           {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_PSET, { yyvsp[-3], yyvsp[-1] });
    }
#line 6376 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 431:
#line 1105 "parser.yy"
                                                                           {
        vsk_targeting(yyvsp[-6]);
        yyval = vsk_ast(INSN_PSET_STEP, { yyvsp[-3], yyvsp[-1] });
    }
#line 6385 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 432:
#line 1109 "parser.yy"
                                                                             {
        vsk_targeting(yyvsp[-6]);
        yyval = vsk_ast(INSN_PRESET_STEP, { yyvsp[-3], yyvsp[-1] });
    }
#line 6394 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 433:
#line 1113 "parser.yy"
                                                                             {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_PRESET, { yyvsp[-3], yyvsp[-1] });
    }
#line 6403 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 434:
#line 1117 "parser.yy"
                                                                            {
        vsk_targeting(yyvsp[-6]);
        yyval = vsk_ast(INSN_PAINT_STEP, { yyvsp[-3], yyvsp[-1] });
    }
#line 6412 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 435:
#line 1121 "parser.yy"
                                                                            {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_PAINT, { yyvsp[-3], yyvsp[-1] });
    }
#line 6421 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 436:
#line 1125 "parser.yy"
                                                                             {
        vsk_targeting(yyvsp[-6]);
        yyval = vsk_ast(INSN_COLOR_equal, { yyvsp[-3], yyvsp[-1] });
    }
#line 6430 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 437:
#line 1131 "parser.yy"
    {
        vsk_targeting(yyvsp[-11]);
        yyval = vsk_ast(INSN_COLOR_at, { yyvsp[-9], yyvsp[-7], yyvsp[-3], yyvsp[-1] });
    }
#line 6439 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 438:
#line 1135 "parser.yy"
                                                                                                                                 {
        vsk_targeting(yyvsp[-11]);
        yyval = vsk_ast(INSN_VIEW_stmt, { yyvsp[-9], yyvsp[-7], yyvsp[-3], yyvsp[-1] });
    }
#line 6448 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 439:
#line 1139 "parser.yy"
                                                                                                                                   {
        vsk_targeting(yyvsp[-11]);
        yyval = vsk_ast(INSN_WINDOW_stmt, { yyvsp[-9], yyvsp[-7], yyvsp[-3], yyvsp[-1] });
    }
#line 6457 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 440:
#line 1146 "parser.yy"
                                                                           {
        vsk_targeting(yyvsp[-2]);
        auto go_to_0 = vsk_ast_goto(yyvsp[-2]);
        vsk_targeting(yyvsp[0]);
        auto go_to_1 = vsk_ast_goto(yyvsp[0]);
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-4], go_to_0, go_to_1 });
    }
#line 6470 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 441:
#line 1154 "parser.yy"
                                                                           {
        vsk_targeting(yyvsp[-2]);
        auto go_to_0 = vsk_ast_goto(yyvsp[-2]);
        vsk_targeting(yyvsp[0]);
        auto go_to_1 = vsk_ast_goto(yyvsp[0]);
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-4], go_to_0, go_to_1 });
    }
#line 6483 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 442:
#line 1162 "parser.yy"
                                                                           {
        vsk_targeting(yyvsp[-2]);
        auto go_to = vsk_ast_goto(yyvsp[-2]);
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-4], go_to, yyvsp[0] });
    }
#line 6494 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 443:
#line 1168 "parser.yy"
                                                                           {
        vsk_targeting(yyvsp[0]);
        auto go_to = vsk_ast_goto(yyvsp[0]);
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-4], yyvsp[-2], go_to });
    }
#line 6505 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 444:
#line 1174 "parser.yy"
                                                                           {
        vsk_targeting(yyvsp[0]);
        auto go_to = vsk_ast_goto(yyvsp[0]);
        vsk_targeting(yyvsp[-4]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-3], vsk_ast(INSN_MULTI), go_to });
    }
#line 6516 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 445:
#line 1180 "parser.yy"
                                                                           {
        vsk_targeting(yyvsp[-4]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-3], vsk_ast(INSN_MULTI), yyvsp[0] });
    }
#line 6525 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 446:
#line 1184 "parser.yy"
                                                                           {
        vsk_targeting(yyvsp[-2]);
        auto go_to = vsk_ast_goto(yyvsp[-2]);
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-4], go_to, yyvsp[0] });
    }
#line 6536 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 447:
#line 1190 "parser.yy"
                                                                           {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-4], yyvsp[-2], yyvsp[0] });
    }
#line 6545 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 448:
#line 1194 "parser.yy"
                                                                           {
        vsk_targeting(yyvsp[-4]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-3], yyvsp[-1], vsk_ast(INSN_MULTI) });
    }
#line 6554 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 449:
#line 1198 "parser.yy"
                                                                           {
        vsk_targeting(yyvsp[-3]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-2], vsk_ast(INSN_MULTI), vsk_ast(INSN_MULTI) });
    }
#line 6563 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 450:
#line 1205 "parser.yy"
                                                                             {
        vsk_targeting(yyvsp[-2]);
        auto go_to = vsk_ast_goto(yyvsp[-2]);
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-4], go_to, yyvsp[0] });
    }
#line 6574 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 451:
#line 1211 "parser.yy"
                                                                             {
        vsk_targeting(yyvsp[-2]);
        auto go_to = vsk_ast_goto(yyvsp[-2]);
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-4], go_to, yyvsp[0] });
    }
#line 6585 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 452:
#line 1217 "parser.yy"
                                                                             {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-4], yyvsp[-2], yyvsp[0] });
    }
#line 6594 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 453:
#line 1221 "parser.yy"
                                                                             {
        vsk_targeting(yyvsp[-4]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-3], vsk_ast(INSN_MULTI), yyvsp[0] });
    }
#line 6603 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 454:
#line 1225 "parser.yy"
                                                                             {
        vsk_targeting(yyvsp[0]);
        auto go_to = vsk_ast_goto(yyvsp[0]);
        vsk_targeting(yyvsp[-3]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-2], go_to, nullptr });
    }
#line 6614 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 455:
#line 1231 "parser.yy"
                                                                             {
        vsk_targeting(yyvsp[-3]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-2], yyvsp[0], nullptr });
    }
#line 6623 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 456:
#line 1235 "parser.yy"
                                                                             {
        vsk_targeting(yyvsp[-2]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-1], vsk_ast(INSN_MULTI), nullptr });
    }
#line 6632 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 457:
#line 1239 "parser.yy"
                                                                             {
        vsk_targeting(yyvsp[0]);
        auto go_to = vsk_ast_goto(yyvsp[0]);
        vsk_targeting(yyvsp[-3]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-2], go_to, nullptr });
    }
#line 6643 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 458:
#line 1248 "parser.yy"
                                                   {
        vsk_targeting(yyvsp[-2]);
        yyval = vsk_ast_multi(yyvsp[-2], yyvsp[0]);
    }
#line 6652 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 459:
#line 1252 "parser.yy"
                                 {
        yyval = yyvsp[0];
    }
#line 6660 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 460:
#line 1255 "parser.yy"
                           {
        yyval = yyvsp[0];
    }
#line 6668 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 461:
#line 1258 "parser.yy"
                        {
        yyval = yyvsp[0];
    }
#line 6676 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 462:
#line 1261 "parser.yy"
                                 {
        yyval = yyvsp[-1];
    }
#line 6684 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 463:
#line 1267 "parser.yy"
                                                     {
        yyval = vsk_ast_multi(yyvsp[-2], yyvsp[0]);
    }
#line 6692 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 464:
#line 1270 "parser.yy"
                                   {
        vsk_targeting(yyvsp[-1]); yyval = yyvsp[0];
    }
#line 6700 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 465:
#line 1273 "parser.yy"
                             {
        yyval = yyvsp[0];
    }
#line 6708 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 466:
#line 1276 "parser.yy"
                                   {
        yyval = yyvsp[-1];
    }
#line 6716 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 467:
#line 1282 "parser.yy"
                           { yyval = yyvsp[0]; }
#line 6722 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 468:
#line 1283 "parser.yy"
                           { yyval = yyvsp[0]; }
#line 6728 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 469:
#line 1284 "parser.yy"
                           { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_MULTI); }
#line 6734 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 470:
#line 1288 "parser.yy"
                                { yyval = yyvsp[0]; }
#line 6740 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 471:
#line 1289 "parser.yy"
                                { vsk_targeting(yyvsp[0]); yyval = yyval = vsk_ast(INSN_LABEL, { vsk_ast(INSN_PERIOD) }); }
#line 6746 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 472:
#line 1293 "parser.yy"
                  {
        vsk_targeting(yyvsp[0]);
        yyval = vsk_ast(INSN_LINE_NUMBERS, { yyvsp[0] });
    }
#line 6755 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 473:
#line 1297 "parser.yy"
                                      {
        yyval = yyvsp[-2];
        yyval->insert(yyvsp[-2]->end(), yyvsp[-1]->begin(), yyvsp[-1]->end());
        yyval->push_back(yyvsp[0]);
    }
#line 6765 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 474:
#line 1302 "parser.yy"
                         {
        vsk_targeting(yyvsp[-1]);
        yyval = vsk_ast(INSN_LINE_NUMBERS, { nullptr });
        yyval->insert(yyval->end(), yyvsp[-1]->begin(), yyvsp[-1]->end());
        yyval->push_back(yyvsp[0]);
    }
#line 6776 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 475:
#line 1311 "parser.yy"
                                         { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_COMMAS); }
#line 6782 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 476:
#line 1312 "parser.yy"
                                         { yyval = yyvsp[-1]; yyval->push_back(nullptr); }
#line 6788 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 477:
#line 1316 "parser.yy"
                                                     { vsk_targeting(yyvsp[-2]); yyval = vsk_ast(INSN_LINE_RANGE, { yyvsp[-2], yyvsp[0] }); }
#line 6794 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 478:
#line 1317 "parser.yy"
                                                     { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_LINE_RANGE, { yyvsp[-1], nullptr }); }
#line 6800 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 479:
#line 1318 "parser.yy"
                                                     { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_LINE_RANGE, { nullptr, yyvsp[0] }); }
#line 6806 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 480:
#line 1319 "parser.yy"
                                                     { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_LINE_RANGE, { yyvsp[0], yyvsp[0] }); }
#line 6812 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 481:
#line 1323 "parser.yy"
                                         { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_DIRTY_8BIT); }
#line 6818 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 482:
#line 1324 "parser.yy"
                                         { yyval = yyvsp[-1]; }
#line 6824 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 483:
#line 1328 "parser.yy"
                            { yyval = yyvsp[0]; }
#line 6830 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 484:
#line 1329 "parser.yy"
                            { yyval = yyvsp[0]; }
#line 6836 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 485:
#line 1330 "parser.yy"
                            { yyval = yyvsp[0]; }
#line 6842 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 486:
#line 1334 "parser.yy"
                                                   { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_PARAM_LIST, { yyvsp[0] }); }
#line 6848 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 487:
#line 1335 "parser.yy"
                                                   { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_PARAM_LIST, { yyvsp[0] }); }
#line 6854 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 488:
#line 1336 "parser.yy"
                                                   { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_PARAM_LIST, { yyvsp[0] }); }
#line 6860 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 489:
#line 1337 "parser.yy"
                                                   { yyval = yyvsp[0]; }
#line 6866 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 490:
#line 1338 "parser.yy"
                                                   { yyval = yyvsp[0]; yyval->insert(yyval->begin(), yyvsp[-2]); }
#line 6872 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 491:
#line 1342 "parser.yy"
                                     {
        vsk_targeting(yyvsp[-2]);
        vsk_target_line = yyvsp[-2]->to_int();
        yyval = vsk_ast_multi(yyvsp[-1], yyvsp[0]);
        yyval->m_program_line = vsk_target_line;
    }
#line 6883 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 492:
#line 1348 "parser.yy"
                          {
        vsk_targeting(yyvsp[-1]);
        vsk_target_line = yyvsp[-1]->to_int();
        yyval = yyvsp[0];
        yyval->m_program_line = vsk_target_line;
    }
#line 6894 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 493:
#line 1354 "parser.yy"
                           {
        vsk_targeting(yyvsp[-1]);
        yyval = vsk_ast_multi(yyvsp[-1], yyvsp[0]);
    }
#line 6903 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 494:
#line 1358 "parser.yy"
                {
        yyval = yyvsp[0];
    }
#line 6911 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 495:
#line 1364 "parser.yy"
                                { yyval = yyvsp[-1]; result = yyval; }
#line 6917 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 496:
#line 1365 "parser.yy"
                                { yyval = yyvsp[0]; result = yyval; }
#line 6923 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 497:
#line 1366 "parser.yy"
                                { yyval = yyvsp[0]; result = yyval; }
#line 6929 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 498:
#line 1367 "parser.yy"
                                { yyval = vsk_ast(INSN_MULTI); }
#line 6935 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;


#line 6939 "C:/dev/VeySickProject/VeySicK/parser.cpp"

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
