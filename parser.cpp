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
#define YYFINAL  414
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   8012

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  260
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  58
/* YYNRULES -- Number of rules.  */
#define YYNRULES  502
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  982

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
     297,   298,   302,   303,   307,   308,   312,   313,   317,   318,
     319,   320,   324,   325,   326,   327,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   351,   355,   359,   360,   361,   362,   363,
     364,   365,   366,   367,   368,   372,   373,   377,   378,   383,
     393,   394,   395,   396,   397,   398,   399,   400,   401,   402,
     403,   404,   405,   406,   407,   408,   409,   410,   411,   412,
     413,   414,   415,   416,   417,   418,   419,   420,   421,   422,
     423,   424,   425,   426,   427,   428,   429,   430,   431,   432,
     433,   434,   435,   436,   437,   438,   439,   440,   441,   442,
     443,   444,   445,   446,   447,   448,   449,   450,   451,   452,
     456,   457,   460,   461,   462,   466,   467,   468,   472,   473,
     477,   478,   482,   483,   484,   488,   489,   490,   491,   492,
     493,   494,   498,   499,   503,   504,   508,   509,   513,   514,
     518,   519,   523,   524,   528,   532,   533,   534,   535,   536,
     540,   541,   545,   546,   550,   554,   555,   559,   560,   562,
     563,   565,   569,   573,   578,   582,   586,   590,   595,   599,
     603,   607,   612,   617,   621,   626,   630,   635,   640,   644,
     648,   652,   656,   660,   664,   668,   672,   676,   680,   684,
     687,   691,   695,   696,   697,   698,   699,   700,   701,   702,
     703,   704,   705,   706,   707,   711,   715,   719,   720,   721,
     725,   726,   727,   728,   729,   730,   731,   732,   733,   734,
     735,   739,   743,   747,   751,   752,   753,   754,   755,   756,
     757,   758,   760,   761,   762,   763,   765,   766,   767,   768,
     770,   775,   779,   784,   789,   794,   799,   803,   807,   812,
     816,   820,   824,   828,   832,   836,   840,   844,   848,   852,
     856,   860,   864,   865,   866,   867,   868,   869,   870,   871,
     872,   873,   874,   875,   876,   877,   878,   879,   880,   881,
     882,   883,   884,   885,   886,   887,   888,   892,   896,   900,
     901,   902,   903,   904,   905,   906,   911,   915,   916,   917,
     918,   919,   920,   921,   922,   923,   924,   925,   926,   927,
     928,   929,   930,   931,   932,   933,   934,   935,   936,   937,
     938,   939,   940,   941,   942,   943,   947,   948,   952,   953,
     957,   958,   962,   963,   967,   968,   969,   970,   974,   975,
     979,   980,   984,   985,   986,   987,   988,   992,   993,   997,
     998,   999,  1000,  1001,  1002,  1003,  1004,  1005,  1006,  1007,
    1008,  1009,  1010,  1011,  1012,  1013,  1014,  1015,  1016,  1017,
    1018,  1019,  1020,  1021,  1022,  1023,  1024,  1025,  1026,  1027,
    1028,  1029,  1030,  1031,  1032,  1033,  1034,  1035,  1036,  1037,
    1038,  1039,  1040,  1041,  1042,  1043,  1044,  1045,  1046,  1047,
    1048,  1049,  1050,  1051,  1052,  1053,  1054,  1055,  1056,  1057,
    1058,  1059,  1060,  1061,  1065,  1072,  1073,  1074,  1079,  1084,
    1089,  1094,  1099,  1104,  1108,  1112,  1116,  1120,  1124,  1128,
    1132,  1136,  1140,  1146,  1150,  1157,  1165,  1173,  1179,  1185,
    1191,  1195,  1201,  1205,  1209,  1216,  1222,  1228,  1232,  1236,
    1242,  1246,  1250,  1259,  1263,  1266,  1269,  1272,  1278,  1281,
    1284,  1287,  1293,  1294,  1295,  1299,  1300,  1304,  1308,  1313,
    1322,  1323,  1327,  1328,  1329,  1330,  1334,  1335,  1339,  1340,
    1341,  1345,  1346,  1347,  1348,  1352,  1358,  1364,  1368,  1374,
    1375,  1376,  1377
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

#define YYPACT_NINF (-681)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-202)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    6754,    -2,   259,  -681,  -681,  -681,  -681,  4112,  -681,  -681,
     -92,  -681,  4352,  6032,  -681,    35,  7504,    52,   -80,    78,
    -681,    29,  -681,  -681,  -681,  -681,    79,   -15,  -681,  -681,
    -681,  -681,    26,  7754,    29,  -681,  -681,  -681,    32,  -681,
      45,  -681,  6032,  4352,  6032,  -681,    29,   -47,  -681,   143,
    -109,  -681,  -681,    80,    11,  6032,   -50,   170,    90,  -681,
      29,  -681,    29,  -681,    18,    26,    26,  4592,  -681,  1922,
      29,  -681,   114,  -681,  -681,  -681,   -65,  6032,    25,    29,
    1188,  6032,   164,  -681,   -56,    82,  1435,   -44,  -681,   -27,
    -681,   207,    12,   -47,  -681,   213,  -681,  -681,  -681,  -681,
      87,    58,    87,  -681,  -681,    29,     2,  -681,  -681,  -681,
    -681,    84,    29,  -681,  -681,   -51,  -681,  -681,   135,  -681,
    -681,  -681,   -81,   229,   146,  2169,   232,   224,   150,   153,
    -681,  1675,    87,    87,  4832,   265,  -681,  -681,   270,   271,
     267,   247,   145,   309,  -681,   214,  6032,  -681,   284,  -681,
    -681,  -681,  -681,  -681,  -681,  -681,  -681,  -681,  -681,  -681,
    -681,  -681,  -681,  -681,  -681,  -681,  -681,   175,  -681,  -681,
    -681,  -681,  -681,  -681,   178,  -681,  -681,  -681,  -681,  -681,
     180,  -681,  -681,  -681,  -681,  -681,  -681,  -681,  -681,  -681,
    -681,  -681,  -681,  -681,   182,   183,  -681,  -681,  6032,  -681,
    6032,  -681,  6512,  -681,  -681,  -681,  -681,  6272,  -681,  -681,
    -681,  -681,  6512,  -681,  -681,  -681,   185,   186,  -681,  -681,
    -681,  -681,  -681,  -681,  -681,  -681,  -681,  -681,  -681,   188,
    -681,  -681,  -681,  -681,     6,  -681,   189,   242,  -681,    15,
     323,   184,   -39,    23,  -681,   330,   167,    81,   240,   273,
     308,  6032,   199,  6512,  -681,   311,  -681,   313,  -681,  -681,
    -681,  2409,  7504,   270,   271,   204,  6032,  -681,  -681,  -681,
    -681,   315,  6032,    13,   283,   285,    32,  -681,  -681,   202,
    -681,   318,  -681,   320,  -681,  -681,   321,  -681,   322,   324,
     325,   290,   326,   327,  -681,  -681,  -681,  -681,  -681,  5072,
    5312,   -40,   -12,  6032,  -681,   315,  -681,  -681,  6032,  -681,
    -681,  -681,  -681,   295,  3623,   310,  6032,    17,   219,  -681,
    -681,  -681,   332,  -681,  -681,   220,   223,  6032,  -681,  3383,
    -681,   301,   274,  6032,  -681,  -681,  -681,   275,  -681,  -681,
     315,   151,    34,   151,   151,   142,   151,   151,   151,   302,
      61,    16,  -681,  6032,   230,  -681,  -681,  -681,  -681,  -681,
    -681,  -681,  -681,   339,   341,  -681,  5552,  6032,   233,  6032,
     234,   345,  6032,   236,   347,   348,  -681,  -681,  -681,  -681,
     316,   352,  -681,  -681,  -681,  -681,   353,  6032,  -681,  -681,
    -681,  6032,  -681,   354,   355,  6032,   357,  3383,   360,  6032,
    6032,  6032,  6032,   364,  3383,  -681,  -681,   341,  4832,  7504,
    -681,  -681,  -681,  -681,  -681,  -681,  -681,  6032,  4352,  4352,
    6032,  4352,  4352,   192,   366,   242,    23,   242,  6032,   305,
      29,  -681,  -681,  -681,  -681,  -681,  5792,  6512,  6272,  6272,
    6272,  6272,  6272,  6272,  6272,  6272,  6272,  6272,  6272,  6272,
    6032,  6032,  6032,  6032,  6032,    48,   368,  6032,  -681,  4352,
    4352,  6032,  2649,  -681,  -681,   369,   341,  -681,  6032,   371,
      29,  -681,  6032,   -60,  6032,  6032,  -681,    32,  -681,    29,
     314,  6032,  6032,  6032,  6032,  6032,  6032,  -681,    -3,  -681,
    -681,   -22,   172,  7004,    87,    29,    29,    -8,   206,  6032,
    6032,   372,    54,    -7,   375,   380,  6032,   272,  6032,   319,
    6032,  6032,   205,  -681,  6032,    94,   386,   215,  6032,   194,
      87,    87,    87,   261,  6032,    87,    87,    87,    87,   195,
     261,   261,    49,  4352,   390,  6032,  4832,  5552,  -681,  -681,
     391,  6032,   392,  6032,  2889,   393,  6032,  6032,  6032,  6032,
     334,    29,  -681,   397,  6032,  6032,   400,  3383,  3383,  -681,
     401,   404,   227,  3136,   341,   270,   271,  -681,   241,   245,
     248,   250,   -21,   251,   252,   254,   256,  -681,    83,   258,
     406,     3,  -681,     4,  -681,  -681,  -681,    15,   323,   184,
     184,   -39,   -39,   -39,   -39,   -39,   -39,  -681,   330,   167,
      81,   240,  -681,   409,  6032,   413,  -681,  -681,   311,   432,
    5312,  -681,  4832,   433,  6032,  -681,  -681,   403,     7,  -681,
    -681,  -681,  -681,  -681,   378,  -681,   434,   434,   434,   237,
    -681,  -681,  6032,  -681,  -681,   379,  7254,   407,    76,  -681,
     416,   315,   315,   -49,    29,    86,  -681,   443,    29,  -681,
    -681,    29,    29,  6032,   447,  6032,   448,  -681,   276,   277,
    6032,  -681,  6032,  6032,    98,  -681,  -681,  -681,  -681,  -681,
     341,   262,   278,  -681,  -681,  -681,  -681,   151,   341,   341,
     394,   395,  -681,  -681,  6032,   452,   341,  -681,  6032,   453,
    6032,   454,  6032,  3383,  6032,   455,  -681,  -681,  -681,  -681,
    -681,  6032,  -681,  -681,  6032,  3383,  3383,  6032,  6032,  6032,
    6032,  3383,  -681,  -681,  -681,  -681,   -47,  -681,  -681,  -681,
    -681,  -681,  -681,   459,  -681,  6032,  6032,  -681,  -681,   402,
     289,  6032,    29,   192,   341,  6032,   293,  6032,   430,    29,
    6032,  6032,  -681,  -681,  -681,   270,   271,  7254,  7254,  7254,
      -5,   315,   315,  -681,  -681,  -681,  6032,  -681,  -681,  -681,
     294,  6032,   469,  6032,  -681,  -681,  -681,  3872,   297,   471,
    -681,  -681,  -681,   262,  -681,   151,    87,  4352,  4352,   299,
    6032,   303,  6032,   304,  6032,   296,   307,  6032,   312,   317,
     328,   329,  3872,   331,   333,    33,     9,   335,  -681,   475,
     337,  -681,   342,   373,  -681,  6032,  -681,  -681,   306,  -681,
     270,   271,  -681,   270,   271,  -681,   270,   271,    29,    29,
      63,    -7,   374,   344,  6032,   346,  -681,  -681,  -681,   450,
    6032,  -681,    87,  -681,  -681,  -681,  -681,  -681,  -681,   349,
    -681,   350,  -681,   351,  6032,  -681,   362,   376,   377,   486,
     382,  6032,  -681,    26,   487,  6032,  -681,  -681,  6032,   493,
    -681,   384,  -681,  6032,   315,   315,    29,    39,  -681,   363,
     383,  6032,   365,  -681,  -681,  -681,  -681,  3872,  -681,   408,
     411,    -4,    65,  3872,  -681,   481,    10,  -681,  6032,  6032,
    -681,  -681,  6032,   415,  -681,    74,  -681,   472,  6032,  6032,
     417,   504,  6032,   418,    26,  6032,  -681,  -681,   526,   537,
    6032,  6032,   429,  6032,   541,   542,  6032,     1,   543,  6032,
    -681,   381,  6032,  6032,   544,   545,  6032,  -681,  6032,  6032,
     385,  -681,  -681,  -681,  -681,  -681,   546,  6032,   547,  -681,
     387,   388,  6032,  6032,   549,   389,   405,   550,  6032,   410,
    6032,  -681,  -681,   412,   419,  6032,  -681,  -681,     8,   551,
     552,   426,  -681,  -681,   427,  6032,   553,  6032,    29,   557,
    -681,   559,  6032,  -681,  -681,    29,  6032,   563,  -681,  -681,
    6032,  -681
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int16 yydefact[] =
{
     502,     0,   331,   359,   360,   361,   362,     0,   419,   363,
       0,   364,   308,     0,   365,     0,   474,   366,     0,     0,
     167,     0,   367,   368,   369,   370,     0,     0,   371,   372,
     373,   374,     0,     0,     0,   486,   375,   376,     0,   377,
       0,   378,     0,     0,     0,   379,     0,   163,   162,     0,
       0,   350,   348,     0,    11,     0,     0,     0,   380,   388,
       0,   389,     0,   390,     0,   302,   304,     0,   392,   184,
       0,   393,     0,   420,   394,   395,   396,     0,   397,   188,
       0,     0,     0,   401,     0,     0,   403,     0,   404,     0,
     340,     0,     0,   161,   160,     0,   341,   405,   406,   407,
     316,   241,   324,   421,   408,     0,   312,   409,   410,   411,
     412,   319,     0,   413,   414,     0,   299,   300,     0,   415,
     416,   417,   418,     0,     0,   181,     0,     0,     0,     0,
     466,   177,     0,     0,   226,   224,   465,   470,   472,   473,
     498,   335,   500,     0,   168,     0,     0,    14,   330,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    30,    18,    74,    75,     0,    36,    37,
      76,    77,    21,    78,     0,    79,    20,    80,    32,    81,
       0,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,     0,     0,    95,    96,     0,    97,
       0,    98,     0,    99,   100,   101,   102,     0,    19,   103,
     104,   105,     0,   106,   107,   108,    39,     0,   109,   110,
     111,   112,    28,   113,   114,   115,    31,   116,   117,     0,
     118,   119,    26,    27,    17,   120,    33,   122,   125,   128,
     130,   132,   135,   142,   144,   146,   148,   150,   152,   154,
     268,     0,     0,     0,     3,   307,     4,   306,   488,   490,
     489,   222,     0,   464,   469,     0,     0,   272,   273,   274,
      12,   334,     0,     0,     0,     0,     0,   476,   475,   485,
     238,   496,   336,   202,   298,   338,   317,   501,     0,     0,
       0,     0,   243,   245,   351,   349,   287,   288,   289,     0,
       0,     0,     0,     0,   426,   229,   425,   381,     0,   385,
     386,   387,   199,     0,     0,     0,     0,     0,     0,   301,
     303,   391,   314,   355,   356,     0,     0,     0,   352,   183,
     342,     0,     0,     0,   278,   279,   280,     0,   398,   399,
     187,     0,     0,     0,     0,   102,   105,     0,     0,    31,
       0,     0,   400,     0,     0,   281,   282,   283,   402,   480,
     284,   285,   286,     0,   327,    57,     0,     0,     0,     0,
       0,     0,     0,     0,   247,   249,   315,   239,   240,   323,
       0,   311,   309,   293,   294,   295,     0,     0,   290,   291,
     292,     0,   422,     0,     0,     0,     0,   180,     0,     0,
       0,     0,     0,     0,   176,   218,   217,   225,     0,   467,
     471,   497,   487,   499,     1,    15,   329,     0,     0,     0,
       0,     0,     0,     0,   264,   124,   143,   123,     0,     0,
       0,    25,    24,    22,    23,    16,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     2,     0,
       0,     0,    11,   492,   491,     0,   493,   221,     0,     0,
       0,   237,     0,     0,     0,     0,   484,   483,   495,     0,
       0,     0,     0,     0,     0,     0,     0,    10,     0,    55,
       9,     0,     0,   461,     0,     0,     0,     0,     0,     0,
       0,     0,    26,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   343,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   481,    59,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   236,     0,     0,     0,     0,     0,     0,   170,
       0,     0,     0,     0,   223,   463,   468,   328,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    29,     0,     0,
       0,     0,    35,     0,   121,   126,   127,   129,   131,   134,
     133,   140,   139,   138,   137,   136,   141,   145,   147,   149,
     151,   153,   265,   267,     0,     0,     5,     6,   305,     0,
       0,   220,     0,     0,     0,    13,   269,     0,     0,   203,
     204,   482,   337,   339,     0,   165,   321,   320,   322,     0,
     242,   244,     0,     8,     7,     0,   454,   459,   472,   460,
     462,   228,   227,     0,     0,     0,   169,     0,     0,   358,
     357,     0,     0,     0,     0,     0,     0,   313,     0,     0,
       0,   234,     0,     0,     0,   325,   205,   206,   209,   477,
     210,     0,     0,   215,   211,   212,   213,     0,   207,   208,
       0,     0,   193,   194,     0,     0,   326,    58,     0,     0,
       0,     0,     0,   174,     0,     0,   246,   248,   235,   310,
     318,     0,   333,   332,     0,   179,   178,     0,     0,     0,
       0,   175,    47,    48,    51,    52,     0,    54,    50,    49,
      45,    46,   261,   263,    38,     0,     0,    41,    34,     0,
       0,     0,     0,    55,   494,     0,     0,     0,     0,     0,
       0,     0,    56,    15,   449,   450,   458,     0,   453,     0,
       0,   233,   231,   382,   383,   384,     0,   197,   195,   198,
       0,     0,     0,     0,   353,   354,   344,   182,     0,     0,
     275,   276,   277,     0,   479,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   173,     0,     0,     0,     0,     0,   266,     0,
       0,   219,     0,     0,   270,     0,   164,   166,   186,   445,
     447,   455,   448,   452,   457,   446,   451,   456,     0,     0,
      26,     0,     0,     0,     0,     0,   346,   347,   345,     0,
       0,   478,     0,   214,   189,   191,   190,   192,   440,     0,
     297,     0,   438,     0,     0,   435,     0,     0,     0,     0,
       0,     0,    53,     0,   262,     0,    42,    40,     0,     0,
     441,     0,   271,     0,   232,   230,     0,     0,   428,     0,
       0,     0,     0,   216,   439,   296,   437,   171,   436,     0,
       0,     0,     0,   172,   260,     0,     0,   433,     0,     0,
     185,   200,     0,     0,   427,     0,   424,     0,     0,     0,
       0,   258,     0,     0,     0,     0,    43,   434,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     259,     0,     0,     0,     0,     0,     0,   423,     0,     0,
       0,   155,   156,   159,   158,   157,   257,     0,     0,    44,
       0,     0,     0,     0,     0,     0,     0,   255,     0,     0,
       0,   442,   432,     0,     0,     0,   443,   444,     0,     0,
       0,     0,   431,   430,     0,     0,   254,     0,     0,     0,
     429,     0,     0,   256,   251,     0,     0,     0,   250,   253,
       0,   252
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -681,   -25,   139,     0,   -53,   610,  -681,  -681,  -681,  -243,
    -216,   -82,  -681,   -68,  -301,   160,   161,  -187,  -172,   396,
     155,   159,   149,   158,   162,  -681,   147,  -344,  -681,  -681,
    -123,  -204,  -681,  -681,  -681,  -681,  -106,  -680,  -215,  -272,
    -320,  -198,  -681,  -681,  -681,  -681,    24,    20,   -28,   -32,
    -247,  -357,   -64,  -681,  -681,   163,  -681,  -681
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   254,   255,   232,   271,   278,   233,   234,   435,   235,
     491,   466,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   328,   936,   128,   129,
     625,   626,   130,   283,   286,   131,   329,   767,   132,   133,
     330,   651,   134,   135,   136,   137,   138,   139,   140,   279,
     670,   366,   280,   141,   261,   467,   142,   143
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     127,   319,   320,   305,   364,   281,   284,   537,   931,   513,
     458,   145,   431,   632,   716,   931,   127,   387,   288,   397,
     432,   270,   292,   495,   438,   404,   340,   643,   649,   792,
     818,   304,   632,   127,   282,   145,   264,    54,   726,   632,
     263,   145,   470,   965,   855,   905,   291,    54,    54,   492,
     537,    52,   407,   251,  -196,   338,   270,   145,   147,   392,
     312,   363,   313,  -201,   258,   266,   273,   145,   374,   520,
     331,   522,   523,   525,   526,   527,   528,   513,   531,   270,
     333,   472,   147,   488,   513,  -196,   494,   853,   147,   353,
    -196,   444,   145,    54,  -201,   144,   145,   393,   532,  -201,
     396,   367,   334,   335,   147,   380,   403,   409,   445,   537,
     900,   442,   386,   533,   147,   446,   388,   389,   369,  -196,
     265,   294,   314,   492,   315,    52,    54,   521,  -201,   662,
     854,   295,   259,   252,   425,   530,   253,   585,   586,   147,
     443,   748,   285,   147,   427,   602,   680,   272,   617,   447,
      50,    51,    52,   681,   250,   299,   300,   372,   473,   256,
     257,   336,   506,   316,   877,   448,   671,   253,   317,   354,
     253,   883,   932,   671,   671,   390,   276,   302,   750,   932,
     722,   368,   433,   449,   892,   933,   634,   717,   934,   287,
     289,   290,   933,   339,   584,   934,   493,   274,   370,   293,
     303,   496,   301,   277,   633,   644,   650,   537,   819,   277,
     902,   727,   728,   260,   322,   738,  -196,   856,   906,   911,
     583,   377,   307,   434,   337,  -201,   306,   350,   351,   381,
     275,   519,    51,   365,   439,   308,   465,   373,   299,   300,
     519,    51,   507,   318,   476,   267,   268,   296,   297,   355,
     356,   383,   384,   753,   754,   589,   590,   309,   310,   332,
     935,   352,   127,   371,   893,   770,   771,   935,   145,   375,
     145,   145,   591,   592,   593,   594,   595,   596,   627,   628,
     391,   365,   264,   678,   679,   394,   263,   524,   398,   501,
     903,   395,   399,   416,   146,   400,   359,   538,   401,   912,
     408,   409,   410,   411,   269,   412,   298,   413,   357,   414,
     385,   415,   755,   773,   502,   147,   311,   147,   147,   417,
     418,   773,   773,   419,   772,   420,   564,   421,   422,   537,
     428,   429,   516,   430,   436,   437,   440,   450,   451,   441,
     452,   453,   454,   455,   457,   423,   459,   424,   460,   468,
     470,   474,   477,   475,   478,   479,   480,   481,   484,   482,
     483,   485,   486,   499,   508,   510,   504,   509,   511,   514,
     529,   515,   518,   513,   536,   535,   359,   537,   541,   543,
     544,   546,   547,   548,   549,   513,   513,   550,   551,   554,
     555,   513,   557,   568,   570,   558,   573,   575,   456,   563,
     577,   578,   580,   604,   612,   776,   614,   648,   365,   127,
     652,   623,   295,   469,   645,   653,   657,   655,   660,   471,
     618,   663,   677,   664,   294,   684,   688,   690,   694,   566,
     581,   699,   701,   565,   606,   704,   707,   465,   693,   708,
     709,   725,   641,   642,   729,   621,   489,   489,   731,   712,
     497,   705,   706,   713,   686,   498,   714,   711,   715,   718,
     719,   503,   720,   505,   721,   639,   724,   732,   735,   740,
     615,   737,   747,   270,   512,   739,   743,   741,   756,   622,
     517,   749,   761,   763,   764,   765,   775,   780,   782,   784,
     787,   777,   778,   127,   795,   270,   270,   799,   805,   798,
     534,   803,   822,   832,   824,   829,   830,   838,   682,   844,
     858,   840,   842,   539,   540,   845,   542,   638,   871,   545,
     847,   881,   885,   861,   867,   848,   879,   880,   888,   889,
     734,   863,   882,   895,   552,   904,   849,   850,   553,   917,
     913,   852,   556,   857,   851,   859,   559,   560,   561,   562,
     860,   700,   868,   898,   870,   365,   899,   874,   875,   876,
     910,   922,   916,   919,   567,   569,   571,   572,   574,   576,
     878,   894,   923,   897,   926,   579,   928,   929,   937,   942,
     943,   948,   950,   489,   955,   958,   967,   968,   972,   939,
     751,   752,   975,   947,   976,   951,   952,   956,   980,   608,
     587,   599,   588,   426,   605,   597,   607,   256,   609,   365,
     598,   600,   148,   957,   966,   613,   601,   807,   960,   616,
     962,   619,   620,   866,     0,   611,     0,   963,   624,   624,
     624,   629,   630,   631,   969,   970,   127,     0,     0,     0,
       0,     0,     0,   270,   270,     0,   646,   647,   757,     0,
       0,   758,   759,   654,     0,   656,   746,   658,   659,     0,
     745,   661,     0,     0,     0,   665,     0,     0,     0,     0,
       0,   672,     0,     0,     0,     0,     0,     0,     0,     0,
     683,     0,   685,   365,   687,     0,     0,     0,   689,     0,
     691,   794,     0,   695,   696,   697,   698,     0,     0,     0,
       0,   702,   703,     0,     0,     0,     0,     0,     0,     0,
     376,   378,   379,     0,     0,     0,   382,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   801,     0,     0,     0,     0,     0,     0,   806,
       0,     0,   405,   406,     0,     0,     0,   127,   127,   127,
       0,   730,   834,   836,     0,     0,   820,   733,     0,   365,
       0,   736,     0,     0,     0,   864,   865,   811,   814,   817,
       0,   810,   813,   816,     0,     0,     0,     0,     0,   742,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   884,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     760,     0,   762,     0,     0,     0,     0,   766,     0,   768,
     769,     0,     0,     0,     0,     0,     0,     0,   270,   270,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   779,     0,     0,     0,   781,     0,   783,     0,   785,
     920,   786,     0,     0,     0,     0,     0,     0,   788,     0,
       0,   789,     0,     0,   790,   791,   766,   793,     0,     0,
       0,     0,     0,     0,     0,     0,   891,     0,     0,     0,
       0,     0,   796,   797,     0,     0,     0,     0,   800,     0,
       0,   901,   802,     0,   804,     0,     0,   624,   808,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   821,     0,     0,     0,     0,   823,     0,
     825,     0,     0,     0,   828,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   835,   837,     0,   839,     0,   841,
       0,   843,     0,     0,   846,     0,     0,     0,     0,   828,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   862,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   974,     0,
       0,   869,     0,     0,     0,   978,     0,   872,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   766,     0,     0,     0,     0,     0,     0,   766,     0,
       0,     0,   886,     0,     0,   887,     0,     0,     0,     0,
     890,     0,     0,     0,     0,     0,     0,     0,   896,     0,
       0,     0,     0,     0,   828,     0,     0,     0,     0,     0,
     828,     0,     0,     0,     0,   907,   908,     0,     0,   909,
       0,     0,     0,     0,     0,   914,   915,     0,     0,   918,
       0,     0,   921,     0,     0,     0,     0,   924,   925,     0,
     927,     0,     0,   930,     0,   603,   938,     0,     0,   940,
     941,     0,     0,   944,     0,   945,   946,     0,     0,     0,
       0,     0,     0,     0,   949,     0,     0,     0,     0,   953,
     954,     0,     0,     0,     0,   959,     0,   961,     0,     0,
       0,     0,   964,   637,   640,     0,     0,     0,     0,     0,
       0,     0,   971,     0,   973,     0,     0,     0,     0,   977,
       0,     0,     0,   979,     0,     0,     0,   981,     0,     0,
     666,   667,   668,   669,     0,   673,   674,   675,   676,     0,
     669,   669,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   723,     0,
       0,   149,   150,     0,     0,     0,   151,     0,   152,   153,
       0,     0,     0,     0,     0,     0,     0,   154,     0,     0,
       0,   155,   156,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   341,     0,     0,     0,     0,     0,     0,   157,
     158,   159,   160,   161,   162,     0,   163,     0,     0,     0,
       0,     0,     0,     0,   164,     0,   744,     0,     0,   165,
     166,     0,     0,     0,     0,   167,     0,     0,     0,   168,
     169,   342,     0,   170,     0,     0,     0,   171,   172,   173,
       0,   174,   175,     0,     0,     0,     0,     0,     0,     0,
       0,   774,   343,   176,   177,    54,     0,     0,     0,     0,
     178,   179,     0,   180,     0,   181,   182,     0,     0,     0,
     183,   184,     0,   185,   344,     0,     0,   186,   187,   188,
     189,     0,   190,   191,     0,   192,   193,     0,     0,     0,
       0,     0,     0,   194,     0,   195,   196,   197,     0,     0,
       0,     0,     0,   198,     0,   199,     0,   201,   202,     0,
     203,   204,   205,     0,     0,     0,   345,     0,     0,     0,
       0,     0,   207,   208,   209,     0,     0,   809,   812,   815,
       0,     0,   210,   346,     0,     0,   347,   212,   213,     0,
       0,   214,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   831,     0,     0,   833,     0,   215,     0,
     216,     0,     0,     0,     0,     0,     0,     0,     0,   217,
       0,     0,     0,     0,   218,     0,   219,     0,   220,     0,
     221,     0,     0,     0,   348,   222,   223,   224,     0,     0,
       0,     0,   225,     0,     0,     0,     0,   349,     0,     0,
       0,     0,     0,   227,   228,   229,     0,   230,   149,   150,
     358,     0,   873,   151,   231,   152,   153,     0,     0,     0,
       0,     0,     0,     0,   154,     0,     0,     0,   155,   156,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     359,     0,     0,     0,     0,     0,   157,   158,   159,   160,
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
     208,   209,   360,   361,     0,     0,     0,     0,     0,   210,
     211,     0,     0,     0,   212,   213,     0,     0,   214,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   215,     0,   216,     0,     0,
       0,     0,     0,     0,     0,     0,   217,     0,     0,     0,
       0,   218,   253,   219,     0,   220,     0,   221,     0,     0,
       0,   362,   222,   223,   224,     0,     0,     0,     0,   225,
       0,     0,     0,     0,   226,     0,     0,     0,   149,   150,
     227,   228,   229,   151,   230,   152,   153,     0,     0,     0,
       0,   231,     0,     0,   154,     0,     0,     0,   155,   156,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     323,     0,     0,     0,     0,     0,   157,   158,   159,   160,
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
       0,     0,     0,     0,     0,     0,   217,     0,   324,     0,
       0,   218,   253,   219,     0,   220,   325,   221,     0,     0,
       0,     0,   222,   223,   224,     0,     0,     0,   326,   225,
       0,     0,     0,     0,   226,     0,     0,     0,     0,   402,
     227,   228,   229,     0,   230,   149,   150,     0,     0,     0,
     151,   231,   152,   153,     0,     0,     0,     0,     0,     0,
       0,   154,     0,     0,     0,   155,   156,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   323,     0,     0,
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
       0,     0,     0,   217,     0,   324,     0,     0,   218,     0,
     219,     0,   220,   325,   221,     0,     0,     0,     0,   222,
     223,   224,     0,     0,     0,   326,   225,     0,     0,     0,
       0,   226,     0,     0,     0,     0,   327,   227,   228,   229,
       0,   230,   149,   150,     0,     0,     0,   151,   231,   152,
     153,     0,     0,     0,     0,     0,     0,     0,   154,     0,
       0,     0,   155,   156,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   323,     0,     0,     0,     0,     0,
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
     217,     0,   324,     0,     0,   218,   253,   219,     0,   220,
     325,   221,     0,     0,     0,     0,   222,   223,   224,     0,
       0,     0,   326,   225,     0,     0,     0,     0,   226,     0,
       0,     0,   149,   150,   227,   228,   229,   151,   230,   152,
     153,     0,     0,     0,     0,   231,     0,     0,   154,     0,
       0,     0,   155,   156,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   359,     0,     0,     0,     0,   461,
     157,   158,   159,   160,   161,   162,     0,   163,     0,     0,
       0,     0,     0,     0,     0,   164,     0,     0,     0,     0,
     165,   166,     0,     0,     0,     0,   167,     0,     0,     0,
     168,   169,     0,     0,   170,     0,     0,     0,   171,   172,
     173,     0,   174,   175,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   176,   177,   462,     0,     0,     0,
       0,   178,   179,     0,   180,     0,   181,   182,     0,     0,
       0,   183,   184,     0,   185,     0,     0,     0,   186,   187,
     188,   189,     0,   190,   191,     0,   192,   193,     0,     0,
       0,     0,     0,     0,   194,     0,   195,   196,   197,     0,
       0,     0,     0,     0,   198,     0,   199,     0,   201,   202,
       0,   203,   204,   205,     0,     0,     0,   206,     0,     0,
       0,     0,     0,   207,   208,   209,   463,   464,     0,     0,
       0,     0,     0,   210,   211,     0,     0,     0,   212,   213,
       0,     0,   214,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   215,
       0,   216,     0,     0,     0,     0,     0,     0,     0,     0,
     217,     0,     0,     0,     0,   218,   253,   219,     0,   220,
       0,   221,     0,     0,     0,     0,   222,   223,   224,     0,
       0,     0,     0,   225,     0,     0,     0,     0,   226,     0,
       0,     0,   149,   150,   227,   228,   229,   151,   230,   152,
     153,     0,     0,     0,     0,   231,     0,     0,   154,     0,
       0,     0,   155,   156,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   359,     0,     0,     0,     0,     0,
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
       0,     0,     0,   299,   610,     0,   199,     0,   201,   202,
       0,   203,   204,   205,     0,     0,     0,   206,     0,     0,
       0,     0,     0,   207,   208,   209,   463,   464,     0,     0,
       0,     0,     0,   210,   211,     0,     0,     0,   212,   213,
       0,     0,   214,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   215,
       0,   216,     0,     0,     0,     0,     0,     0,     0,     0,
     217,     0,     0,     0,     0,   218,   253,   219,     0,   220,
       0,   221,     0,     0,     0,     0,   222,   223,   224,     0,
       0,     0,     0,   225,     0,     0,     0,     0,   226,     0,
       0,     0,   149,   150,   227,   228,   229,   151,   230,   152,
     153,     0,     0,     0,     0,   231,     0,     0,   154,     0,
       0,     0,   155,   156,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   323,     0,     0,     0,     0,     0,
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
     217,     0,   324,     0,     0,   218,     0,   219,     0,   220,
     325,   221,     0,     0,     0,     0,   222,   223,   224,     0,
       0,     0,   326,   225,     0,     0,     0,     0,   226,     0,
       0,     0,     0,   692,   227,   228,   229,     0,   230,   149,
     150,     0,     0,     0,   151,   231,   152,   153,     0,     0,
       0,     0,     0,     0,     0,   154,     0,     0,     0,   155,
     156,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   323,     0,     0,     0,     0,     0,   157,   158,   159,
     160,   161,   162,     0,   163,     0,     0,     0,     0,     0,
       0,     0,   164,     0,     0,     0,     0,   165,   166,     0,
       0,     0,     0,   167,     0,     0,     0,   168,   169,     0,
       0,   170,     0,     0,     0,   171,   172,   173,     0,   174,
     175,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   176,   177,    54,     0,     0,     0,     0,   178,   179,
       0,   180,     0,   181,   182,     0,     0,     0,   183,   184,
       0,   185,     0,     0,     0,   186,   187,   188,   189,     0,
     190,   191,     0,   192,   193,     0,     0,     0,     0,     0,
       0,   194,     0,   195,   196,   197,     0,     0,     0,     0,
       0,   198,     0,   199,     0,   201,   202,     0,   203,   204,
     205,     0,     0,     0,   206,     0,     0,     0,     0,     0,
     207,   208,   209,     0,     0,     0,     0,     0,     0,     0,
     210,   211,     0,     0,     0,   212,   213,     0,     0,   214,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   215,     0,   216,     0,
       0,     0,     0,     0,     0,     0,     0,   217,     0,   324,
       0,     0,   218,     0,   219,     0,   220,   325,   221,     0,
       0,     0,     0,   222,   223,   224,     0,     0,     0,   326,
     225,     0,     0,     0,     0,   226,     0,     0,     0,     0,
     710,   227,   228,   229,     0,   230,   149,   150,     0,     0,
       0,   151,   231,   152,   153,     0,     0,     0,     0,     0,
       0,     0,   154,     0,     0,     0,   155,   156,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   323,     0,
       0,     0,     0,     0,   157,   158,   159,   160,   161,   162,
       0,   163,     0,     0,     0,     0,     0,     0,     0,   164,
       0,     0,     0,     0,   165,   166,     0,     0,     0,     0,
     167,     0,     0,     0,   168,   169,     0,     0,   170,     0,
       0,     0,   171,   172,   173,     0,   174,   175,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   176,   177,
      54,     0,     0,     0,     0,   178,   179,     0,   180,     0,
     181,   182,     0,     0,     0,   183,   184,     0,   185,     0,
       0,     0,   186,   187,   188,   189,     0,   190,   191,     0,
     192,   193,     0,     0,     0,     0,     0,     0,   194,     0,
     195,   196,   197,     0,     0,     0,     0,     0,   198,     0,
     199,     0,   201,   202,     0,   203,   204,   205,     0,     0,
       0,   206,     0,     0,     0,     0,     0,   207,   208,   209,
       0,     0,     0,     0,     0,     0,     0,   210,   211,     0,
       0,     0,   212,   213,     0,     0,   214,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   215,     0,   216,     0,     0,     0,     0,
       0,     0,     0,     0,   217,     0,   324,     0,     0,   218,
       0,   219,     0,   220,   325,   221,     0,     0,     0,     0,
     222,   223,   224,     0,     0,     0,   326,   225,     0,     0,
       0,     0,   226,     0,     0,     0,   149,   150,   227,   228,
     229,   151,   230,   152,   153,     0,     0,     0,     0,   231,
       0,     0,   154,     0,     0,     0,   155,   156,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   157,   158,   159,   160,   161,   162,
       0,   163,     0,     0,     0,     0,     0,     0,     0,   164,
       0,     0,     0,     0,   165,   166,     0,     0,     0,     0,
     167,     0,     0,     0,   168,   169,     0,     0,   170,     0,
       0,     0,   171,   172,   173,     0,   174,   175,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   176,   177,
      54,     0,     0,     0,     0,   178,   179,     0,   180,     0,
     181,   182,     0,     0,     0,   183,   184,     0,   185,     0,
       0,     0,   186,   187,   188,   189,     0,   190,   191,     0,
     192,   193,     0,     0,     0,     0,     0,     0,   194,     0,
     195,   196,   197,     0,     0,     0,     0,     0,   198,     0,
     199,     0,   201,   202,     0,   203,   204,   205,     0,     0,
       0,   206,     0,     0,     0,     0,     0,   207,   208,   209,
       0,     0,     0,     0,     0,     0,     0,   210,   211,     0,
       0,     0,   212,   213,     0,     0,   214,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   215,     0,   216,     0,     0,     0,     0,
       0,     0,     0,     0,   217,     0,     0,     0,     0,   218,
     253,   219,     0,   220,     0,   221,     0,     0,     0,     0,
     222,   223,   224,     0,     0,     0,     0,   225,     0,     0,
       0,     0,   226,     0,     0,     0,     0,     0,   227,   228,
     229,     0,   230,   500,     0,   149,   150,     0,     0,   231,
     151,     0,   152,   153,     0,     0,     0,     0,     0,     0,
       0,   154,     0,     0,     0,   155,   156,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   826,     0,     0,
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
       0,     0,     0,   217,     0,   827,     0,     0,   218,     0,
     219,     0,   220,     0,   221,     0,     0,     0,     0,   222,
     223,   224,     0,     0,     0,     0,   225,     0,     0,     0,
       0,   226,     0,     0,     0,   149,   150,   227,   228,   229,
     151,   230,   152,   153,     0,     0,     0,     0,   231,     0,
       0,   154,     0,     0,     0,   155,   156,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
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
     200,   201,   202,     0,   203,   204,   205,     0,     0,     0,
     206,     0,     0,     0,     0,     0,   207,   208,   209,     0,
       0,     0,     0,     0,     0,     0,   210,   211,     0,     0,
       0,   212,   213,     0,     0,   214,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   215,     0,   216,     0,     0,     0,     0,     0,
       0,     0,     0,   217,     0,     0,     0,     0,   218,     0,
     219,     0,   220,     0,   221,     0,     0,     0,     0,   222,
     223,   224,     0,     0,     0,     0,   225,     0,     0,     0,
       0,   226,     0,     0,     0,   149,   150,   227,   228,   229,
     151,   230,   152,   153,     0,     0,     0,     0,   231,     0,
       0,   154,     0,     0,     0,   155,   156,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
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
       0,     0,     0,   217,     0,     0,     0,     0,   218,   253,
     219,     0,   220,     0,   221,     0,     0,     0,     0,   222,
     223,   224,     0,     0,     0,     0,   225,     0,     0,     0,
       0,   226,     0,     0,     0,   149,   150,   227,   228,   229,
     151,   230,   152,   153,     0,     0,     0,     0,   231,     0,
       0,   154,     0,     0,     0,   155,   156,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
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
       0,     0,     0,   321,     0,     0,     0,     0,     0,     0,
       0,     0,   215,     0,   216,     0,     0,     0,     0,     0,
       0,     0,     0,   217,     0,     0,     0,     0,   218,     0,
     219,     0,   220,     0,   221,     0,     0,     0,     0,   222,
     223,   224,     0,     0,     0,     0,   225,     0,     0,     0,
       0,   226,     0,     0,     0,   149,   150,   227,   228,   229,
     151,   230,   152,   153,     0,     0,     0,     0,   231,     0,
       0,   154,     0,     0,     0,   155,   156,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   359,     0,     0,
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
       0,     0,     0,   217,     0,     0,     0,     0,   218,     0,
     219,     0,   220,     0,   221,     0,     0,     0,     0,   222,
     223,   224,     0,     0,     0,     0,   225,     0,     0,     0,
       0,   226,     0,     0,     0,   149,   150,   227,   228,   229,
     151,   230,   152,   153,     0,     0,     0,     0,   231,     0,
       0,   154,     0,     0,     0,   155,   156,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
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
       0,     0,   215,     0,   216,     0,     0,     0,     0,   487,
       0,     0,     0,   217,     0,     0,     0,     0,   218,     0,
     219,     0,   220,     0,   221,     0,     0,     0,     0,   222,
     223,   224,     0,     0,     0,     0,   225,     0,     0,     0,
       0,   226,     0,     0,     0,   149,   150,   227,   228,   229,
     151,   230,   152,   153,     0,     0,     0,     0,   231,     0,
       0,   154,     0,     0,     0,   155,   156,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
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
     490,     0,     0,   217,     0,     0,     0,     0,   218,     0,
     219,     0,   220,     0,   221,     0,     0,     0,     0,   222,
     223,   224,     0,     0,     0,     0,   225,     0,     0,     0,
       0,   226,     0,     0,     0,   149,   150,   227,   228,   229,
     151,   230,   152,   153,     0,     0,     0,     0,   231,     0,
       0,   154,     0,     0,     0,   155,   156,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   538,     0,     0,
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
       0,     0,     0,   217,     0,     0,     0,     0,   218,     0,
     219,     0,   220,     0,   221,     0,     0,     0,     0,   222,
     223,   224,     0,     0,     0,     0,   225,     0,     0,     0,
       0,   226,     0,     0,     0,   149,   150,   227,   228,   229,
     151,   230,   152,   153,     0,     0,     0,     0,   231,     0,
       0,   154,     0,     0,     0,   155,   156,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
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
     582,     0,     0,   217,     0,     0,     0,     0,   218,     0,
     219,     0,   220,     0,   221,     0,     0,     0,     0,   222,
     223,   224,     0,     0,     0,     0,   225,     0,     0,     0,
       0,   226,     0,     0,     0,   149,   150,   227,   228,   229,
     151,   230,   152,   153,     0,     0,     0,     0,   231,     0,
       0,   154,     0,     0,     0,   155,   156,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
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
       0,     0,     0,   217,     0,     0,     0,     0,   218,     0,
     219,     0,   220,     0,   221,     0,     0,     0,     0,   222,
     223,   224,     0,     0,     0,     0,   225,     0,     0,     0,
       0,   226,     0,     0,     0,   149,   150,   227,   228,   229,
     151,   230,   152,   153,     0,     0,     0,     0,   231,     0,
       0,   154,     0,     0,     0,   155,   156,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
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
     206,     0,     0,     0,     0,     0,     0,   208,   209,     0,
       0,     0,     0,     0,     0,     0,   210,   211,     0,     0,
       0,   212,   213,     0,     0,   214,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   215,     0,   216,     0,     0,     0,     0,     0,
       0,     0,     0,   217,     0,     0,     0,     0,   218,     0,
     219,     0,   220,     0,   221,     0,     0,     0,     0,   222,
     223,   224,     0,     0,     0,     0,   225,     0,     0,     0,
       0,   226,     0,     0,     0,   149,   150,   227,   228,   229,
     151,   230,   152,   153,     0,     0,     0,     0,   231,     0,
       0,   154,     0,     0,     0,   155,   156,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
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
       0,   201,     0,     0,   203,   204,   205,     0,     0,     0,
     206,     0,     0,     0,     0,     0,     0,   208,   209,     0,
       0,     0,     0,     0,     0,     0,   210,   211,     0,     0,
       0,     0,   213,     0,     0,   214,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   215,     0,   216,     0,     0,     0,     0,     0,
       0,     0,     0,   217,     0,     0,     0,     0,   218,     0,
     219,     0,   220,     0,   221,     0,     0,     0,     0,   222,
     223,   224,     0,     0,     0,     0,   225,     0,     0,     0,
       0,   226,     0,     0,     0,     0,     0,   227,   228,   229,
       0,   230,     0,     1,     0,     0,     2,     0,   231,     3,
       4,     5,     6,     0,     7,     8,     9,     0,     0,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,     0,
      20,    21,    22,    23,    24,     0,     0,     0,     0,     0,
       0,    25,    26,    27,    28,    29,    30,    31,    32,     0,
      33,    34,    35,     0,    36,     0,     0,    37,    38,     0,
      39,     0,     0,     0,    40,     0,     0,    41,    42,     0,
      43,    44,    45,     0,     0,     0,    46,     0,     0,     0,
      47,    48,    49,    50,    51,    52,     0,     0,    53,     0,
       0,    54,     0,    55,     0,     0,     0,     0,    56,     0,
      57,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      58,    59,    60,     0,     0,     0,     0,    61,     0,     0,
       0,     0,     0,    62,    63,    64,    65,    66,    67,     0,
      68,     0,     0,     0,    69,    70,     0,     0,     0,     0,
       0,     0,    71,    72,     0,    73,     0,     0,     0,     0,
      74,    75,    76,    77,     0,    78,     0,    79,     0,     0,
       0,     0,    80,    81,    82,     0,    83,    84,     0,    85,
       0,     0,    86,     0,    87,    88,     0,     0,    89,    90,
      91,    92,    93,    94,    95,    96,    97,     0,    98,     0,
      99,   100,   101,   102,     0,   103,     0,   104,   105,   106,
       0,     0,     0,   107,   108,     0,     0,     0,   109,   110,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     111,     0,     0,     0,     0,   112,   113,     0,     0,   114,
       0,     0,     0,   115,     0,   116,   117,     0,     0,     0,
       0,     0,     0,   118,   119,     0,   120,   121,   122,   123,
     124,   125,   126,   635,     0,     0,     2,     0,     0,     3,
       4,     5,     6,     0,     7,     8,     9,     0,     0,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,     0,
      20,    21,    22,    23,    24,     0,     0,     0,     0,     0,
       0,    25,    26,    27,    28,    29,    30,    31,    32,     0,
     147,    34,    35,     0,    36,     0,     0,    37,    38,   636,
      39,     0,     0,     0,    40,     0,     0,    41,     0,     0,
      43,    44,    45,     0,     0,     0,    46,     0,     0,     0,
      47,    48,    49,    50,    51,    52,     0,     0,    53,     0,
       0,    54,     0,    55,     0,     0,     0,     0,    56,     0,
      57,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      58,    59,    60,     0,     0,     0,     0,    61,     0,     0,
       0,     0,     0,    62,    63,    64,    65,    66,    67,     0,
      68,     0,     0,     0,    69,    70,     0,     0,     0,     0,
       0,     0,    71,    72,     0,    73,     0,     0,     0,     0,
      74,    75,    76,    77,     0,    78,     0,    79,     0,     0,
       0,     0,    80,    81,    82,     0,    83,    84,     0,    85,
       0,     0,    86,     0,    87,    88,     0,     0,    89,    90,
      91,    92,    93,    94,    95,    96,    97,     0,    98,     0,
      99,   100,   101,   102,     0,   103,     0,   104,   105,   106,
       0,     0,     0,   107,   108,     0,     0,     0,   109,   110,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     111,     0,     0,     0,     0,   112,   113,     0,     0,   114,
       0,     0,     0,   115,     0,   116,   117,     0,     0,     0,
       0,     0,     0,   118,   119,     0,   120,   121,   122,   123,
     124,   125,   126,   635,     0,     0,     2,     0,     0,     3,
       4,     5,     6,     0,     7,     8,     9,     0,     0,    10,
      11,    12,    13,    14,    15,   262,    17,    18,    19,     0,
      20,    21,    22,    23,    24,     0,     0,     0,     0,     0,
       0,    25,    26,    27,    28,    29,    30,    31,    32,     0,
     147,    34,    35,     0,    36,     0,     0,    37,    38,     0,
      39,     0,     0,     0,    40,     0,     0,    41,     0,     0,
      43,    44,    45,     0,     0,     0,    46,     0,     0,     0,
      47,    48,    49,    50,    51,    52,     0,     0,    53,     0,
       0,    54,     0,    55,     0,     0,     0,     0,    56,     0,
      57,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      58,    59,    60,     0,     0,     0,     0,    61,     0,     0,
       0,     0,     0,    62,    63,    64,    65,    66,    67,     0,
      68,     0,     0,     0,    69,    70,     0,     0,     0,     0,
       0,     0,    71,    72,     0,    73,     0,     0,     0,     0,
      74,    75,    76,    77,     0,    78,     0,    79,     0,     0,
       0,     0,    80,    81,    82,     0,    83,    84,     0,    85,
       0,     0,    86,     0,    87,    88,     0,     0,    89,    90,
      91,    92,    93,    94,    95,    96,    97,     0,    98,     0,
      99,   100,   101,   102,     0,   103,     0,   104,   105,   106,
       0,     0,     0,   107,   108,     0,     0,     0,   109,   110,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     111,     0,     0,     0,     0,   112,   113,     0,     0,   114,
       0,     0,     0,   115,     0,   116,   117,     0,     0,     0,
       0,     0,     0,   118,   119,     0,   120,   121,   122,   123,
     124,   125,   126,     1,     0,     0,     2,     0,     0,     3,
       4,     5,     6,     0,     7,     8,     9,     0,     0,    10,
      11,    12,    13,    14,    15,   262,    17,    18,    19,     0,
      20,    21,    22,    23,    24,     0,     0,     0,     0,     0,
       0,    25,    26,    27,    28,    29,    30,    31,    32,     0,
       0,    34,    35,     0,    36,     0,     0,    37,    38,     0,
      39,     0,     0,     0,    40,     0,     0,    41,     0,     0,
      43,    44,    45,     0,     0,     0,    46,     0,     0,     0,
      47,    48,    49,    50,    51,    52,     0,     0,    53,     0,
       0,    54,     0,    55,     0,     0,     0,     0,    56,     0,
      57,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      58,    59,    60,     0,     0,     0,     0,    61,     0,     0,
       0,     0,     0,    62,    63,    64,    65,    66,    67,     0,
      68,     0,     0,     0,    69,    70,     0,     0,     0,     0,
       0,     0,    71,    72,     0,    73,     0,     0,     0,     0,
      74,    75,    76,    77,     0,    78,     0,    79,     0,     0,
       0,     0,    80,    81,    82,     0,    83,    84,     0,    85,
       0,     0,    86,     0,    87,    88,     0,     0,    89,    90,
      91,    92,    93,    94,    95,    96,    97,     0,    98,     0,
      99,   100,   101,   102,     0,   103,     0,   104,   105,   106,
       0,     0,     0,   107,   108,     0,     0,     0,   109,   110,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     111,     0,     0,     0,     0,   112,   113,     0,     0,   114,
       0,     0,     0,   115,     0,   116,   117,     0,     0,     0,
       0,     0,     0,   118,   119,     0,   120,   121,   122,   123,
     124,   125,   126,     1,     0,     0,     2,     0,     0,     3,
       4,     5,     6,     0,     7,     8,     9,     0,     0,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,     0,
      20,    21,    22,    23,    24,     0,     0,     0,     0,     0,
       0,    25,    26,    27,    28,    29,    30,    31,    32,     0,
       0,    34,    35,     0,    36,     0,     0,    37,    38,     0,
      39,     0,     0,     0,    40,     0,     0,    41,     0,     0,
      43,    44,    45,     0,     0,     0,    46,     0,     0,     0,
      47,    48,    49,    50,    51,    52,     0,     0,    53,     0,
       0,    54,     0,    55,     0,     0,     0,     0,    56,     0,
      57,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      58,    59,    60,     0,     0,     0,     0,    61,     0,     0,
       0,     0,     0,    62,    63,    64,    65,    66,    67,     0,
      68,     0,     0,     0,    69,    70,     0,     0,     0,     0,
       0,     0,    71,    72,     0,    73,     0,     0,     0,     0,
      74,    75,    76,    77,     0,    78,     0,    79,     0,     0,
       0,     0,    80,    81,    82,     0,    83,    84,     0,    85,
       0,     0,    86,     0,    87,    88,     0,     0,    89,    90,
      91,    92,    93,    94,    95,    96,    97,     0,    98,     0,
      99,   100,   101,   102,     0,   103,     0,   104,   105,   106,
       0,     0,     0,   107,   108,     0,     0,     0,   109,   110,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     111,     0,     0,     0,     0,   112,   113,     0,     0,   114,
       0,     0,     0,   115,     0,   116,   117,     0,     0,     0,
       0,     0,     0,   118,   119,     0,   120,   121,   122,   123,
     124,   125,   126
};

static const yytype_int16 yycheck[] =
{
       0,    65,    66,    56,    86,    33,    38,   364,     7,   329,
     253,     9,     6,    35,    35,     7,    16,    68,    43,   125,
      14,    21,    47,    35,     9,   131,    79,    35,    35,   709,
      35,    56,    35,    33,    34,     9,    16,    97,    35,    35,
      16,     9,    35,    35,    35,    35,    46,    97,    97,    89,
     407,    91,   134,   145,     0,    30,    56,     9,    56,   140,
      60,    86,    62,     0,    29,   145,    81,     9,    93,   341,
      70,   343,   344,   345,   346,   347,   348,   397,   350,    79,
     145,    68,    56,   299,   404,    31,   301,    54,    56,   145,
      36,    68,     9,    97,    31,    97,     9,   122,    82,    36,
     125,   145,   167,   168,    56,   105,   131,    31,    85,   466,
     114,   150,   112,    97,    56,    92,   167,   168,   145,    65,
      68,   230,   104,    89,   106,    91,    97,   342,    65,    35,
      97,   240,    97,   225,   202,   350,   217,   438,   439,    56,
     179,    65,    97,    56,   212,    97,    97,    68,   208,   126,
      89,    90,    91,   104,     7,   144,   145,   145,   145,    12,
      13,   226,   145,   145,   844,   142,   523,   217,   150,   225,
     217,   851,   171,   530,   531,   226,   150,   227,   227,   171,
      97,   225,   176,   160,   145,   184,   208,   208,   187,    42,
      43,    44,   184,   168,   437,   187,   236,   212,   225,    56,
     250,   213,    55,   177,   207,   213,   213,   564,   213,   177,
     145,   208,   208,   178,    67,   208,   162,   208,   208,   145,
     436,   163,   132,   217,    77,   162,    56,    80,    81,   227,
     245,    89,    90,    86,   219,   145,   261,   225,   144,   145,
      89,    90,   225,   225,   276,   167,   168,   167,   168,   167,
     168,   167,   168,   167,   168,   442,   443,   167,   168,   145,
     259,    97,   262,    56,   225,   167,   168,   259,     9,    56,
       9,     9,   444,   445,   446,   447,   448,   449,   482,   483,
     145,   134,   262,   530,   531,    56,   262,   145,    56,   314,
     225,   145,    68,   146,    35,   145,    35,    35,   145,   225,
      35,    31,    31,    36,   226,    58,   226,   162,   226,     0,
     226,    97,   226,   670,   314,    56,   226,    56,    56,    35,
     145,   678,   679,   145,   226,   145,   408,   145,   145,   686,
     145,   145,   332,   145,   145,    93,    13,     7,   171,   155,
     259,   101,    69,    35,   145,   198,    35,   200,    35,   145,
      35,    68,   150,    68,    36,    35,    35,    35,    68,    35,
      35,    35,    35,    68,   145,   145,    56,    35,   145,    68,
      68,    97,    97,   693,    35,   145,    35,   734,   145,   145,
      35,   145,    35,    35,    68,   705,   706,    35,    35,    35,
      35,   711,    35,   418,   419,    35,   421,   422,   251,    35,
     208,    35,    97,    35,    35,   677,    35,    35,   261,   409,
      35,    97,   240,   266,   208,    35,    97,   145,   213,   272,
     473,    35,   227,   208,   230,    35,    35,    35,    35,   409,
     430,    97,    35,   409,   459,    35,    35,   462,   544,    35,
     213,    35,   495,   496,    35,   477,   299,   300,    35,   208,
     303,   557,   558,   208,   536,   308,   208,   563,   208,   208,
     208,   314,   208,   316,   208,   493,   208,    35,    35,    35,
     470,    68,    65,   473,   327,    97,    97,   240,    35,   479,
     333,    65,    35,    35,   208,   208,   208,    35,    35,    35,
      35,    97,    97,   493,    35,   495,   496,   208,    68,    97,
     353,   208,   208,   775,    35,   208,    35,   208,   533,   213,
      35,   208,   208,   366,   367,   208,   369,   493,    68,   372,
     208,    35,    35,   150,   150,   208,   150,   150,    35,   145,
     612,   225,   150,   150,   387,    54,   208,   208,   391,    35,
      68,   208,   395,   208,   213,   208,   399,   400,   401,   402,
     208,   551,   208,   145,   208,   408,   145,   208,   208,   208,
     145,    35,   145,   145,   417,   418,   419,   420,   421,   422,
     208,   208,    35,   208,   145,   428,    35,    35,    35,    35,
      35,    35,    35,   436,    35,    35,    35,    35,    35,   208,
     643,   644,    35,   208,    35,   208,   208,   208,    35,   460,
     440,   452,   441,   207,   457,   450,   459,   460,   461,   462,
     451,   453,     2,   208,   958,   468,   454,   740,   208,   472,
     208,   474,   475,   821,    -1,   462,    -1,   208,   481,   482,
     483,   484,   485,   486,   208,   208,   636,    -1,    -1,    -1,
      -1,    -1,    -1,   643,   644,    -1,   499,   500,   648,    -1,
      -1,   651,   652,   506,    -1,   508,   636,   510,   511,    -1,
     636,   514,    -1,    -1,    -1,   518,    -1,    -1,    -1,    -1,
      -1,   524,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     533,    -1,   535,   536,   537,    -1,    -1,    -1,   541,    -1,
     543,   716,    -1,   546,   547,   548,   549,    -1,    -1,    -1,
      -1,   554,   555,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     100,   101,   102,    -1,    -1,    -1,   106,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   732,    -1,    -1,    -1,    -1,    -1,    -1,   739,
      -1,    -1,   132,   133,    -1,    -1,    -1,   747,   748,   749,
      -1,   604,   777,   778,    -1,    -1,   756,   610,    -1,   612,
      -1,   614,    -1,    -1,    -1,   818,   819,   747,   748,   749,
      -1,   747,   748,   749,    -1,    -1,    -1,    -1,    -1,   632,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   853,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     653,    -1,   655,    -1,    -1,    -1,    -1,   660,    -1,   662,
     663,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   818,   819,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   684,    -1,    -1,    -1,   688,    -1,   690,    -1,   692,
     904,   694,    -1,    -1,    -1,    -1,    -1,    -1,   701,    -1,
      -1,   704,    -1,    -1,   707,   708,   709,   710,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   866,    -1,    -1,    -1,
      -1,    -1,   725,   726,    -1,    -1,    -1,    -1,   731,    -1,
      -1,   881,   735,    -1,   737,    -1,    -1,   740,   741,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   756,    -1,    -1,    -1,    -1,   761,    -1,
     763,    -1,    -1,    -1,   767,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   777,   778,    -1,   780,    -1,   782,
      -1,   784,    -1,    -1,   787,    -1,    -1,    -1,    -1,   792,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   805,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   968,    -1,
      -1,   824,    -1,    -1,    -1,   975,    -1,   830,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   844,    -1,    -1,    -1,    -1,    -1,    -1,   851,    -1,
      -1,    -1,   855,    -1,    -1,   858,    -1,    -1,    -1,    -1,
     863,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   871,    -1,
      -1,    -1,    -1,    -1,   877,    -1,    -1,    -1,    -1,    -1,
     883,    -1,    -1,    -1,    -1,   888,   889,    -1,    -1,   892,
      -1,    -1,    -1,    -1,    -1,   898,   899,    -1,    -1,   902,
      -1,    -1,   905,    -1,    -1,    -1,    -1,   910,   911,    -1,
     913,    -1,    -1,   916,    -1,   455,   919,    -1,    -1,   922,
     923,    -1,    -1,   926,    -1,   928,   929,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   937,    -1,    -1,    -1,    -1,   942,
     943,    -1,    -1,    -1,    -1,   948,    -1,   950,    -1,    -1,
      -1,    -1,   955,   493,   494,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   965,    -1,   967,    -1,    -1,    -1,    -1,   972,
      -1,    -1,    -1,   976,    -1,    -1,    -1,   980,    -1,    -1,
     520,   521,   522,   523,    -1,   525,   526,   527,   528,    -1,
     530,   531,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   578,    -1,
      -1,     3,     4,    -1,    -1,    -1,     8,    -1,    10,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    19,    -1,    -1,
      -1,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    34,    -1,    -1,    -1,    -1,    -1,    -1,    41,
      42,    43,    44,    45,    46,    -1,    48,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    -1,   636,    -1,    -1,    61,
      62,    -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,    71,
      72,    73,    -1,    75,    -1,    -1,    -1,    79,    80,    81,
      -1,    83,    84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   671,    94,    95,    96,    97,    -1,    -1,    -1,    -1,
     102,   103,    -1,   105,    -1,   107,   108,    -1,    -1,    -1,
     112,   113,    -1,   115,   116,    -1,    -1,   119,   120,   121,
     122,    -1,   124,   125,    -1,   127,   128,    -1,    -1,    -1,
      -1,    -1,    -1,   135,    -1,   137,   138,   139,    -1,    -1,
      -1,    -1,    -1,   145,    -1,   147,    -1,   149,   150,    -1,
     152,   153,   154,    -1,    -1,    -1,   158,    -1,    -1,    -1,
      -1,    -1,   164,   165,   166,    -1,    -1,   747,   748,   749,
      -1,    -1,   174,   175,    -1,    -1,   178,   179,   180,    -1,
      -1,   183,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   773,    -1,    -1,   776,    -1,   200,    -1,
     202,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   211,
      -1,    -1,    -1,    -1,   216,    -1,   218,    -1,   220,    -1,
     222,    -1,    -1,    -1,   226,   227,   228,   229,    -1,    -1,
      -1,    -1,   234,    -1,    -1,    -1,    -1,   239,    -1,    -1,
      -1,    -1,    -1,   245,   246,   247,    -1,   249,     3,     4,
       5,    -1,   832,     8,   256,    10,    11,    -1,    -1,    -1,
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
     165,   166,   167,   168,    -1,    -1,    -1,    -1,    -1,   174,
     175,    -1,    -1,    -1,   179,   180,    -1,    -1,   183,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   200,    -1,   202,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   211,    -1,    -1,    -1,
      -1,   216,   217,   218,    -1,   220,    -1,   222,    -1,    -1,
      -1,   226,   227,   228,   229,    -1,    -1,    -1,    -1,   234,
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
      -1,   216,   217,   218,    -1,   220,   221,   222,    -1,    -1,
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
     211,    -1,   213,    -1,    -1,   216,   217,   218,    -1,   220,
     221,   222,    -1,    -1,    -1,    -1,   227,   228,   229,    -1,
      -1,    -1,   233,   234,    -1,    -1,    -1,    -1,   239,    -1,
      -1,    -1,     3,     4,   245,   246,   247,     8,   249,    10,
      11,    -1,    -1,    -1,    -1,   256,    -1,    -1,    19,    -1,
      -1,    -1,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    -1,    -1,    -1,    -1,    40,
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
      -1,    -1,    -1,   164,   165,   166,   167,   168,    -1,    -1,
      -1,    -1,    -1,   174,   175,    -1,    -1,    -1,   179,   180,
      -1,    -1,   183,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   200,
      -1,   202,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     211,    -1,    -1,    -1,    -1,   216,   217,   218,    -1,   220,
      -1,   222,    -1,    -1,    -1,    -1,   227,   228,   229,    -1,
      -1,    -1,    -1,   234,    -1,    -1,    -1,    -1,   239,    -1,
      -1,    -1,     3,     4,   245,   246,   247,     8,   249,    10,
      11,    -1,    -1,    -1,    -1,   256,    -1,    -1,    19,    -1,
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
      -1,    -1,    -1,   144,   145,    -1,   147,    -1,   149,   150,
      -1,   152,   153,   154,    -1,    -1,    -1,   158,    -1,    -1,
      -1,    -1,    -1,   164,   165,   166,   167,   168,    -1,    -1,
      -1,    -1,    -1,   174,   175,    -1,    -1,    -1,   179,   180,
      -1,    -1,   183,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   200,
      -1,   202,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     211,    -1,    -1,    -1,    -1,   216,   217,   218,    -1,   220,
      -1,   222,    -1,    -1,    -1,    -1,   227,   228,   229,    -1,
      -1,    -1,    -1,   234,    -1,    -1,    -1,    -1,   239,    -1,
      -1,    -1,     3,     4,   245,   246,   247,     8,   249,    10,
      11,    -1,    -1,    -1,    -1,   256,    -1,    -1,    19,    -1,
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
      -1,    -1,    -1,   244,   245,   246,   247,    -1,   249,     3,
       4,    -1,    -1,    -1,     8,   256,    10,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    19,    -1,    -1,    -1,    23,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    -1,    -1,    -1,    -1,    -1,    41,    42,    43,
      44,    45,    46,    -1,    48,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    56,    -1,    -1,    -1,    -1,    61,    62,    -1,
      -1,    -1,    -1,    67,    -1,    -1,    -1,    71,    72,    -1,
      -1,    75,    -1,    -1,    -1,    79,    80,    81,    -1,    83,
      84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    95,    96,    97,    -1,    -1,    -1,    -1,   102,   103,
      -1,   105,    -1,   107,   108,    -1,    -1,    -1,   112,   113,
      -1,   115,    -1,    -1,    -1,   119,   120,   121,   122,    -1,
     124,   125,    -1,   127,   128,    -1,    -1,    -1,    -1,    -1,
      -1,   135,    -1,   137,   138,   139,    -1,    -1,    -1,    -1,
      -1,   145,    -1,   147,    -1,   149,   150,    -1,   152,   153,
     154,    -1,    -1,    -1,   158,    -1,    -1,    -1,    -1,    -1,
     164,   165,   166,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     174,   175,    -1,    -1,    -1,   179,   180,    -1,    -1,   183,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   200,    -1,   202,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   211,    -1,   213,
      -1,    -1,   216,    -1,   218,    -1,   220,   221,   222,    -1,
      -1,    -1,    -1,   227,   228,   229,    -1,    -1,    -1,   233,
     234,    -1,    -1,    -1,    -1,   239,    -1,    -1,    -1,    -1,
     244,   245,   246,   247,    -1,   249,     3,     4,    -1,    -1,
      -1,     8,   256,    10,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    19,    -1,    -1,    -1,    23,    24,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,
      -1,    -1,    -1,    -1,    41,    42,    43,    44,    45,    46,
      -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,
      -1,    -1,    -1,    -1,    61,    62,    -1,    -1,    -1,    -1,
      67,    -1,    -1,    -1,    71,    72,    -1,    -1,    75,    -1,
      -1,    -1,    79,    80,    81,    -1,    83,    84,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    95,    96,
      97,    -1,    -1,    -1,    -1,   102,   103,    -1,   105,    -1,
     107,   108,    -1,    -1,    -1,   112,   113,    -1,   115,    -1,
      -1,    -1,   119,   120,   121,   122,    -1,   124,   125,    -1,
     127,   128,    -1,    -1,    -1,    -1,    -1,    -1,   135,    -1,
     137,   138,   139,    -1,    -1,    -1,    -1,    -1,   145,    -1,
     147,    -1,   149,   150,    -1,   152,   153,   154,    -1,    -1,
      -1,   158,    -1,    -1,    -1,    -1,    -1,   164,   165,   166,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   174,   175,    -1,
      -1,    -1,   179,   180,    -1,    -1,   183,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   200,    -1,   202,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   211,    -1,   213,    -1,    -1,   216,
      -1,   218,    -1,   220,   221,   222,    -1,    -1,    -1,    -1,
     227,   228,   229,    -1,    -1,    -1,   233,   234,    -1,    -1,
      -1,    -1,   239,    -1,    -1,    -1,     3,     4,   245,   246,
     247,     8,   249,    10,    11,    -1,    -1,    -1,    -1,   256,
      -1,    -1,    19,    -1,    -1,    -1,    23,    24,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    41,    42,    43,    44,    45,    46,
      -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,
      -1,    -1,    -1,    -1,    61,    62,    -1,    -1,    -1,    -1,
      67,    -1,    -1,    -1,    71,    72,    -1,    -1,    75,    -1,
      -1,    -1,    79,    80,    81,    -1,    83,    84,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    95,    96,
      97,    -1,    -1,    -1,    -1,   102,   103,    -1,   105,    -1,
     107,   108,    -1,    -1,    -1,   112,   113,    -1,   115,    -1,
      -1,    -1,   119,   120,   121,   122,    -1,   124,   125,    -1,
     127,   128,    -1,    -1,    -1,    -1,    -1,    -1,   135,    -1,
     137,   138,   139,    -1,    -1,    -1,    -1,    -1,   145,    -1,
     147,    -1,   149,   150,    -1,   152,   153,   154,    -1,    -1,
      -1,   158,    -1,    -1,    -1,    -1,    -1,   164,   165,   166,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   174,   175,    -1,
      -1,    -1,   179,   180,    -1,    -1,   183,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   200,    -1,   202,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   211,    -1,    -1,    -1,    -1,   216,
     217,   218,    -1,   220,    -1,   222,    -1,    -1,    -1,    -1,
     227,   228,   229,    -1,    -1,    -1,    -1,   234,    -1,    -1,
      -1,    -1,   239,    -1,    -1,    -1,    -1,    -1,   245,   246,
     247,    -1,   249,   250,    -1,     3,     4,    -1,    -1,   256,
       8,    -1,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,
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
     218,    -1,   220,    -1,   222,    -1,    -1,    -1,    -1,   227,
     228,   229,    -1,    -1,    -1,    -1,   234,    -1,    -1,    -1,
      -1,   239,    -1,    -1,    -1,     3,     4,   245,   246,   247,
       8,   249,    10,    11,    -1,    -1,    -1,    -1,   256,    -1,
      -1,    19,    -1,    -1,    -1,    23,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
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
     148,   149,   150,    -1,   152,   153,   154,    -1,    -1,    -1,
     158,    -1,    -1,    -1,    -1,    -1,   164,   165,   166,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   174,   175,    -1,    -1,
      -1,   179,   180,    -1,    -1,   183,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   200,    -1,   202,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   211,    -1,    -1,    -1,    -1,   216,    -1,
     218,    -1,   220,    -1,   222,    -1,    -1,    -1,    -1,   227,
     228,   229,    -1,    -1,    -1,    -1,   234,    -1,    -1,    -1,
      -1,   239,    -1,    -1,    -1,     3,     4,   245,   246,   247,
       8,   249,    10,    11,    -1,    -1,    -1,    -1,   256,    -1,
      -1,    19,    -1,    -1,    -1,    23,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
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
      -1,    -1,    -1,   211,    -1,    -1,    -1,    -1,   216,   217,
     218,    -1,   220,    -1,   222,    -1,    -1,    -1,    -1,   227,
     228,   229,    -1,    -1,    -1,    -1,   234,    -1,    -1,    -1,
      -1,   239,    -1,    -1,    -1,     3,     4,   245,   246,   247,
       8,   249,    10,    11,    -1,    -1,    -1,    -1,   256,    -1,
      -1,    19,    -1,    -1,    -1,    23,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
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
      -1,    -1,    -1,   191,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   200,    -1,   202,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   211,    -1,    -1,    -1,    -1,   216,    -1,
     218,    -1,   220,    -1,   222,    -1,    -1,    -1,    -1,   227,
     228,   229,    -1,    -1,    -1,    -1,   234,    -1,    -1,    -1,
      -1,   239,    -1,    -1,    -1,     3,     4,   245,   246,   247,
       8,   249,    10,    11,    -1,    -1,    -1,    -1,   256,    -1,
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
      -1,    -1,    -1,   211,    -1,    -1,    -1,    -1,   216,    -1,
     218,    -1,   220,    -1,   222,    -1,    -1,    -1,    -1,   227,
     228,   229,    -1,    -1,    -1,    -1,   234,    -1,    -1,    -1,
      -1,   239,    -1,    -1,    -1,     3,     4,   245,   246,   247,
       8,   249,    10,    11,    -1,    -1,    -1,    -1,   256,    -1,
      -1,    19,    -1,    -1,    -1,    23,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
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
      -1,    -1,   200,    -1,   202,    -1,    -1,    -1,    -1,   207,
      -1,    -1,    -1,   211,    -1,    -1,    -1,    -1,   216,    -1,
     218,    -1,   220,    -1,   222,    -1,    -1,    -1,    -1,   227,
     228,   229,    -1,    -1,    -1,    -1,   234,    -1,    -1,    -1,
      -1,   239,    -1,    -1,    -1,     3,     4,   245,   246,   247,
       8,   249,    10,    11,    -1,    -1,    -1,    -1,   256,    -1,
      -1,    19,    -1,    -1,    -1,    23,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
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
     208,    -1,    -1,   211,    -1,    -1,    -1,    -1,   216,    -1,
     218,    -1,   220,    -1,   222,    -1,    -1,    -1,    -1,   227,
     228,   229,    -1,    -1,    -1,    -1,   234,    -1,    -1,    -1,
      -1,   239,    -1,    -1,    -1,     3,     4,   245,   246,   247,
       8,   249,    10,    11,    -1,    -1,    -1,    -1,   256,    -1,
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
      -1,    -1,    -1,   211,    -1,    -1,    -1,    -1,   216,    -1,
     218,    -1,   220,    -1,   222,    -1,    -1,    -1,    -1,   227,
     228,   229,    -1,    -1,    -1,    -1,   234,    -1,    -1,    -1,
      -1,   239,    -1,    -1,    -1,     3,     4,   245,   246,   247,
       8,   249,    10,    11,    -1,    -1,    -1,    -1,   256,    -1,
      -1,    19,    -1,    -1,    -1,    23,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
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
     208,    -1,    -1,   211,    -1,    -1,    -1,    -1,   216,    -1,
     218,    -1,   220,    -1,   222,    -1,    -1,    -1,    -1,   227,
     228,   229,    -1,    -1,    -1,    -1,   234,    -1,    -1,    -1,
      -1,   239,    -1,    -1,    -1,     3,     4,   245,   246,   247,
       8,   249,    10,    11,    -1,    -1,    -1,    -1,   256,    -1,
      -1,    19,    -1,    -1,    -1,    23,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
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
      -1,    -1,    -1,   211,    -1,    -1,    -1,    -1,   216,    -1,
     218,    -1,   220,    -1,   222,    -1,    -1,    -1,    -1,   227,
     228,   229,    -1,    -1,    -1,    -1,   234,    -1,    -1,    -1,
      -1,   239,    -1,    -1,    -1,     3,     4,   245,   246,   247,
       8,   249,    10,    11,    -1,    -1,    -1,    -1,   256,    -1,
      -1,    19,    -1,    -1,    -1,    23,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
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
     158,    -1,    -1,    -1,    -1,    -1,    -1,   165,   166,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   174,   175,    -1,    -1,
      -1,   179,   180,    -1,    -1,   183,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   200,    -1,   202,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   211,    -1,    -1,    -1,    -1,   216,    -1,
     218,    -1,   220,    -1,   222,    -1,    -1,    -1,    -1,   227,
     228,   229,    -1,    -1,    -1,    -1,   234,    -1,    -1,    -1,
      -1,   239,    -1,    -1,    -1,     3,     4,   245,   246,   247,
       8,   249,    10,    11,    -1,    -1,    -1,    -1,   256,    -1,
      -1,    19,    -1,    -1,    -1,    23,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
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
      -1,   149,    -1,    -1,   152,   153,   154,    -1,    -1,    -1,
     158,    -1,    -1,    -1,    -1,    -1,    -1,   165,   166,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   174,   175,    -1,    -1,
      -1,    -1,   180,    -1,    -1,   183,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   200,    -1,   202,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   211,    -1,    -1,    -1,    -1,   216,    -1,
     218,    -1,   220,    -1,   222,    -1,    -1,    -1,    -1,   227,
     228,   229,    -1,    -1,    -1,    -1,   234,    -1,    -1,    -1,
      -1,   239,    -1,    -1,    -1,    -1,    -1,   245,   246,   247,
      -1,   249,    -1,     9,    -1,    -1,    12,    -1,   256,    15,
      16,    17,    18,    -1,    20,    21,    22,    -1,    -1,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    -1,
      36,    37,    38,    39,    40,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    48,    49,    50,    51,    52,    53,    54,    -1,
      56,    57,    58,    -1,    60,    -1,    -1,    63,    64,    -1,
      66,    -1,    -1,    -1,    70,    -1,    -1,    73,    74,    -1,
      76,    77,    78,    -1,    -1,    -1,    82,    -1,    -1,    -1,
      86,    87,    88,    89,    90,    91,    -1,    -1,    94,    -1,
      -1,    97,    -1,    99,    -1,    -1,    -1,    -1,   104,    -1,
     106,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     116,   117,   118,    -1,    -1,    -1,    -1,   123,    -1,    -1,
      -1,    -1,    -1,   129,   130,   131,   132,   133,   134,    -1,
     136,    -1,    -1,    -1,   140,   141,    -1,    -1,    -1,    -1,
      -1,    -1,   148,   149,    -1,   151,    -1,    -1,    -1,    -1,
     156,   157,   158,   159,    -1,   161,    -1,   163,    -1,    -1,
      -1,    -1,   168,   169,   170,    -1,   172,   173,    -1,   175,
      -1,    -1,   178,    -1,   180,   181,    -1,    -1,   184,   185,
     186,   187,   188,   189,   190,   191,   192,    -1,   194,    -1,
     196,   197,   198,   199,    -1,   201,    -1,   203,   204,   205,
      -1,    -1,    -1,   209,   210,    -1,    -1,    -1,   214,   215,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     226,    -1,    -1,    -1,    -1,   231,   232,    -1,    -1,   235,
      -1,    -1,    -1,   239,    -1,   241,   242,    -1,    -1,    -1,
      -1,    -1,    -1,   249,   250,    -1,   252,   253,   254,   255,
     256,   257,   258,     9,    -1,    -1,    12,    -1,    -1,    15,
      16,    17,    18,    -1,    20,    21,    22,    -1,    -1,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    -1,
      36,    37,    38,    39,    40,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    48,    49,    50,    51,    52,    53,    54,    -1,
      56,    57,    58,    -1,    60,    -1,    -1,    63,    64,    65,
      66,    -1,    -1,    -1,    70,    -1,    -1,    73,    -1,    -1,
      76,    77,    78,    -1,    -1,    -1,    82,    -1,    -1,    -1,
      86,    87,    88,    89,    90,    91,    -1,    -1,    94,    -1,
      -1,    97,    -1,    99,    -1,    -1,    -1,    -1,   104,    -1,
     106,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     116,   117,   118,    -1,    -1,    -1,    -1,   123,    -1,    -1,
      -1,    -1,    -1,   129,   130,   131,   132,   133,   134,    -1,
     136,    -1,    -1,    -1,   140,   141,    -1,    -1,    -1,    -1,
      -1,    -1,   148,   149,    -1,   151,    -1,    -1,    -1,    -1,
     156,   157,   158,   159,    -1,   161,    -1,   163,    -1,    -1,
      -1,    -1,   168,   169,   170,    -1,   172,   173,    -1,   175,
      -1,    -1,   178,    -1,   180,   181,    -1,    -1,   184,   185,
     186,   187,   188,   189,   190,   191,   192,    -1,   194,    -1,
     196,   197,   198,   199,    -1,   201,    -1,   203,   204,   205,
      -1,    -1,    -1,   209,   210,    -1,    -1,    -1,   214,   215,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     226,    -1,    -1,    -1,    -1,   231,   232,    -1,    -1,   235,
      -1,    -1,    -1,   239,    -1,   241,   242,    -1,    -1,    -1,
      -1,    -1,    -1,   249,   250,    -1,   252,   253,   254,   255,
     256,   257,   258,     9,    -1,    -1,    12,    -1,    -1,    15,
      16,    17,    18,    -1,    20,    21,    22,    -1,    -1,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    -1,
      36,    37,    38,    39,    40,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    48,    49,    50,    51,    52,    53,    54,    -1,
      56,    57,    58,    -1,    60,    -1,    -1,    63,    64,    -1,
      66,    -1,    -1,    -1,    70,    -1,    -1,    73,    -1,    -1,
      76,    77,    78,    -1,    -1,    -1,    82,    -1,    -1,    -1,
      86,    87,    88,    89,    90,    91,    -1,    -1,    94,    -1,
      -1,    97,    -1,    99,    -1,    -1,    -1,    -1,   104,    -1,
     106,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     116,   117,   118,    -1,    -1,    -1,    -1,   123,    -1,    -1,
      -1,    -1,    -1,   129,   130,   131,   132,   133,   134,    -1,
     136,    -1,    -1,    -1,   140,   141,    -1,    -1,    -1,    -1,
      -1,    -1,   148,   149,    -1,   151,    -1,    -1,    -1,    -1,
     156,   157,   158,   159,    -1,   161,    -1,   163,    -1,    -1,
      -1,    -1,   168,   169,   170,    -1,   172,   173,    -1,   175,
      -1,    -1,   178,    -1,   180,   181,    -1,    -1,   184,   185,
     186,   187,   188,   189,   190,   191,   192,    -1,   194,    -1,
     196,   197,   198,   199,    -1,   201,    -1,   203,   204,   205,
      -1,    -1,    -1,   209,   210,    -1,    -1,    -1,   214,   215,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     226,    -1,    -1,    -1,    -1,   231,   232,    -1,    -1,   235,
      -1,    -1,    -1,   239,    -1,   241,   242,    -1,    -1,    -1,
      -1,    -1,    -1,   249,   250,    -1,   252,   253,   254,   255,
     256,   257,   258,     9,    -1,    -1,    12,    -1,    -1,    15,
      16,    17,    18,    -1,    20,    21,    22,    -1,    -1,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    -1,
      36,    37,    38,    39,    40,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    48,    49,    50,    51,    52,    53,    54,    -1,
      -1,    57,    58,    -1,    60,    -1,    -1,    63,    64,    -1,
      66,    -1,    -1,    -1,    70,    -1,    -1,    73,    -1,    -1,
      76,    77,    78,    -1,    -1,    -1,    82,    -1,    -1,    -1,
      86,    87,    88,    89,    90,    91,    -1,    -1,    94,    -1,
      -1,    97,    -1,    99,    -1,    -1,    -1,    -1,   104,    -1,
     106,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     116,   117,   118,    -1,    -1,    -1,    -1,   123,    -1,    -1,
      -1,    -1,    -1,   129,   130,   131,   132,   133,   134,    -1,
     136,    -1,    -1,    -1,   140,   141,    -1,    -1,    -1,    -1,
      -1,    -1,   148,   149,    -1,   151,    -1,    -1,    -1,    -1,
     156,   157,   158,   159,    -1,   161,    -1,   163,    -1,    -1,
      -1,    -1,   168,   169,   170,    -1,   172,   173,    -1,   175,
      -1,    -1,   178,    -1,   180,   181,    -1,    -1,   184,   185,
     186,   187,   188,   189,   190,   191,   192,    -1,   194,    -1,
     196,   197,   198,   199,    -1,   201,    -1,   203,   204,   205,
      -1,    -1,    -1,   209,   210,    -1,    -1,    -1,   214,   215,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     226,    -1,    -1,    -1,    -1,   231,   232,    -1,    -1,   235,
      -1,    -1,    -1,   239,    -1,   241,   242,    -1,    -1,    -1,
      -1,    -1,    -1,   249,   250,    -1,   252,   253,   254,   255,
     256,   257,   258,     9,    -1,    -1,    12,    -1,    -1,    15,
      16,    17,    18,    -1,    20,    21,    22,    -1,    -1,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    -1,
      36,    37,    38,    39,    40,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    48,    49,    50,    51,    52,    53,    54,    -1,
      -1,    57,    58,    -1,    60,    -1,    -1,    63,    64,    -1,
      66,    -1,    -1,    -1,    70,    -1,    -1,    73,    -1,    -1,
      76,    77,    78,    -1,    -1,    -1,    82,    -1,    -1,    -1,
      86,    87,    88,    89,    90,    91,    -1,    -1,    94,    -1,
      -1,    97,    -1,    99,    -1,    -1,    -1,    -1,   104,    -1,
     106,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     116,   117,   118,    -1,    -1,    -1,    -1,   123,    -1,    -1,
      -1,    -1,    -1,   129,   130,   131,   132,   133,   134,    -1,
     136,    -1,    -1,    -1,   140,   141,    -1,    -1,    -1,    -1,
      -1,    -1,   148,   149,    -1,   151,    -1,    -1,    -1,    -1,
     156,   157,   158,   159,    -1,   161,    -1,   163,    -1,    -1,
      -1,    -1,   168,   169,   170,    -1,   172,   173,    -1,   175,
      -1,    -1,   178,    -1,   180,   181,    -1,    -1,   184,   185,
     186,   187,   188,   189,   190,   191,   192,    -1,   194,    -1,
     196,   197,   198,   199,    -1,   201,    -1,   203,   204,   205,
      -1,    -1,    -1,   209,   210,    -1,    -1,    -1,   214,   215,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     226,    -1,    -1,    -1,    -1,   231,   232,    -1,    -1,   235,
      -1,    -1,    -1,   239,    -1,   241,   242,    -1,    -1,    -1,
      -1,    -1,    -1,   249,   250,    -1,   252,   253,   254,   255,
     256,   257,   258
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
     263,   264,    68,    81,   212,   245,   150,   177,   265,   309,
     312,   308,   263,   293,   309,    97,   294,   286,   261,   286,
     286,   263,   261,    56,   230,   240,   167,   168,   226,   144,
     145,   286,   227,   250,   261,   264,    56,   132,   145,   167,
     168,   226,   263,   263,   104,   106,   145,   150,   225,   312,
     312,   191,   286,    35,   213,   221,   233,   244,   286,   296,
     300,   263,   145,   145,   167,   168,   226,   286,    30,   168,
     264,    34,    73,    94,   116,   158,   175,   178,   226,   239,
     286,   286,    97,   145,   225,   167,   168,   226,     5,    35,
     167,   168,   226,   261,   271,   286,   311,   145,   225,   145,
     225,    56,   145,   225,   261,    56,   265,   163,   265,   265,
     263,   227,   265,   167,   168,   226,   263,    68,   167,   168,
     226,   145,   140,   261,    56,   145,   261,   296,    56,    68,
     145,   145,   244,   261,   296,   265,   265,   271,    35,    31,
      31,    36,    58,   162,     0,    97,   286,    35,   145,   145,
     145,   145,   145,   286,   286,   273,   279,   273,   145,   145,
     145,     6,    14,   176,   217,   268,   145,    93,     9,   219,
      13,   155,   150,   179,    68,    85,    92,   126,   142,   160,
       7,   171,   259,   101,    69,    35,   286,   145,   269,    35,
      35,    40,    97,   167,   168,   261,   271,   315,   145,   286,
      35,   286,    68,   145,    68,    68,   309,   150,    36,    35,
      35,    35,    35,    35,    68,    35,    35,   207,   270,   286,
     208,   270,    89,   236,   298,    35,   213,   286,   286,    68,
     250,   261,   263,   286,    56,   286,   145,   225,   145,    35,
     145,   145,   286,   300,    68,    97,   263,   286,    97,    89,
     299,   298,   299,   299,   145,   299,   299,   299,   299,    68,
     298,   299,    82,    97,   286,   145,    35,   311,    35,   286,
     286,   145,   286,   145,    35,   286,   145,    35,    35,    68,
      35,    35,   286,   286,    35,    35,   286,    35,    35,   286,
     286,   286,   286,    35,   271,   306,   307,   286,   261,   286,
     261,   286,   286,   261,   286,   261,   286,   208,    35,   286,
      97,   263,   208,   270,   269,   274,   274,   275,   276,   277,
     277,   278,   278,   278,   278,   278,   278,   280,   281,   282,
     283,   284,    97,   265,    35,   286,   261,   286,   262,   286,
     145,   315,    35,   286,    35,   263,   286,   208,   264,   286,
     286,   309,   263,    97,   286,   290,   291,   291,   291,   286,
     286,   286,    35,   207,   208,     9,    65,   265,   306,   308,
     265,   264,   264,    35,   213,   208,   286,   286,    35,    35,
     213,   301,    35,    35,   286,   145,   286,    97,   286,   286,
     213,   286,    35,    35,   208,   286,   265,   265,   265,   265,
     310,   311,   286,   265,   265,   265,   265,   227,   310,   310,
      97,   104,   261,   286,    35,   286,   271,   286,    35,   286,
      35,   286,   244,   296,    35,   286,   286,   286,   286,    97,
     263,    35,   286,   286,    35,   296,   296,    35,    35,   213,
     244,   296,   208,   208,   208,   208,    35,   208,   208,   208,
     208,   208,    97,   265,   208,    35,    35,   208,   208,    35,
     286,    35,    35,   286,   271,    35,   286,    68,   208,    97,
      35,   240,   286,    97,   265,   306,   307,    65,    65,    65,
     227,   264,   264,   167,   168,   226,    35,   263,   263,   263,
     286,    35,   286,    35,   208,   208,   286,   297,   286,   286,
     167,   168,   226,   311,   265,   208,   299,    97,    97,   286,
      35,   286,    35,   286,    35,   286,   286,    35,   286,   286,
     286,   286,   297,   286,   261,    35,   286,   286,    97,   208,
     286,   263,   286,   208,   286,    68,   263,   290,   286,   265,
     306,   307,   265,   306,   307,   265,   306,   307,    35,   213,
     263,   286,   208,   286,    35,   286,    35,   213,   286,   208,
      35,   265,   299,   265,   261,   286,   261,   286,   208,   286,
     208,   286,   208,   286,   213,   208,   286,   208,   208,   208,
     208,   213,   208,    54,    97,    35,   208,   208,    35,   208,
     208,   150,   286,   225,   264,   264,   301,   150,   208,   286,
     208,    68,   286,   265,   208,   208,   208,   297,   208,   150,
     150,    35,   150,   297,   312,    35,   286,   286,    35,   145,
     286,   263,   145,   225,   208,   150,   286,   208,   145,   145,
     114,   263,   145,   225,    54,    35,   208,   286,   286,   286,
     145,   145,   225,    68,   286,   286,   145,    35,   286,   145,
     312,   286,    35,    35,   286,   286,   145,   286,    35,    35,
     286,     7,   171,   184,   187,   259,   287,    35,   286,   208,
     286,   286,    35,    35,   286,   286,   286,   208,    35,   286,
      35,   208,   208,   286,   286,    35,   208,   208,    35,   286,
     208,   286,   208,   208,   286,    35,   287,    35,    35,   208,
     208,   286,    35,   286,   263,    35,    35,   286,   263,   286,
      35,   286
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int16 yyr1[] =
{
       0,   260,   261,   262,   262,   262,   262,   263,   263,   263,
     263,   263,   264,   264,   265,   265,   266,   266,   267,   267,
     267,   267,   268,   268,   268,   268,   269,   269,   269,   269,
     269,   269,   269,   269,   269,   269,   269,   269,   269,   269,
     269,   269,   269,   269,   269,   269,   269,   269,   269,   269,
     269,   269,   269,   269,   269,   270,   270,   271,   271,   271,
     272,   272,   272,   272,   272,   272,   272,   272,   272,   272,
     272,   272,   272,   272,   272,   272,   272,   272,   272,   272,
     272,   272,   272,   272,   272,   272,   272,   272,   272,   272,
     272,   272,   272,   272,   272,   272,   272,   272,   272,   272,
     272,   272,   272,   272,   272,   272,   272,   272,   272,   272,
     272,   272,   272,   272,   272,   272,   272,   272,   272,   272,
     273,   273,   274,   274,   274,   275,   275,   275,   276,   276,
     277,   277,   278,   278,   278,   279,   279,   279,   279,   279,
     279,   279,   280,   280,   281,   281,   282,   282,   283,   283,
     284,   284,   285,   285,   286,   287,   287,   287,   287,   287,
     288,   288,   289,   289,   290,   291,   291,   292,   292,   292,
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
     292,   292,   292,   292,   292,   292,   293,   293,   294,   294,
     295,   295,   296,   296,   297,   297,   297,   297,   298,   298,
     299,   299,   300,   300,   300,   300,   300,   301,   301,   302,
     302,   302,   302,   302,   302,   302,   302,   302,   302,   302,
     302,   302,   302,   302,   302,   302,   302,   302,   302,   302,
     302,   302,   302,   302,   302,   302,   302,   302,   302,   302,
     302,   302,   302,   302,   302,   302,   302,   302,   302,   302,
     302,   302,   302,   302,   302,   302,   302,   302,   302,   302,
     302,   302,   302,   302,   302,   302,   302,   302,   302,   302,
     302,   302,   302,   302,   302,   303,   303,   303,   303,   303,
     303,   303,   303,   303,   303,   303,   303,   303,   303,   303,
     303,   303,   303,   303,   303,   304,   304,   304,   304,   304,
     304,   304,   304,   304,   304,   305,   305,   305,   305,   305,
     305,   305,   305,   306,   306,   306,   306,   306,   307,   307,
     307,   307,   308,   308,   308,   309,   309,   310,   310,   310,
     311,   311,   312,   312,   312,   312,   313,   313,   314,   314,
     314,   315,   315,   315,   315,   316,   316,   316,   316,   317,
     317,   317,   317
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     3,     3,     4,     4,     3,
       3,     1,     1,     3,     1,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     1,     1,     1,     4,     3,     1,     1,     4,     1,
       6,     4,     6,     8,    10,     4,     4,     4,     4,     4,
       4,     4,     4,     6,     4,     1,     3,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     2,     2,     1,     3,     3,     1,     3,
       1,     3,     1,     3,     3,     1,     3,     3,     3,     3,
       3,     3,     1,     2,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     3,     1,     2,     4,
       3,     7,     7,     5,     4,     4,     2,     1,     4,     4,
       2,     1,     5,     2,     1,     8,     6,     2,     1,     6,
       6,     6,     6,     4,     4,     5,     3,     5,     5,     2,
       8,     6,     2,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     6,     4,     7,     2,     2,     6,
       4,     3,     2,     3,     1,     2,     1,     4,     4,     2,
       7,     5,     7,     5,     4,     4,     3,     3,     2,     2,
       2,     1,     4,     2,     4,     2,     4,     2,     4,     2,
      15,    14,    17,    16,    13,    11,    14,    10,     8,    10,
       8,     5,     7,     5,     3,     4,     6,     4,     2,     4,
       6,     7,     2,     2,     2,     5,     5,     5,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     7,     6,     2,     1,
       1,     2,     1,     2,     1,     4,     2,     2,     1,     2,
       4,     2,     1,     4,     2,     2,     1,     2,     4,     1,
       4,     4,     4,     2,     1,     4,     4,     2,     4,     3,
       2,     1,     4,     4,     2,     1,     1,     3,     1,     3,
       1,     1,     1,     2,     1,     2,     2,     2,     1,     2,
       1,     2,     1,     4,     4,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     5,     5,     5,     2,     2,     2,     1,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     2,     2,
       2,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,    10,     8,     2,     2,     8,     7,    14,
      13,    13,    12,     8,     9,     6,     7,     7,     6,     7,
       6,     7,    12,    12,    12,     6,     6,     6,     6,     5,
       5,     6,     6,     5,     4,     6,     6,     6,     5,     4,
       4,     3,     4,     3,     2,     1,     1,     2,     3,     2,
       1,     2,     1,     1,     1,     1,     1,     1,     3,     2,
       1,     2,     3,     2,     2,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     3,     3,     2,     2,     1,     2,
       1,     2,     0
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
#line 3719 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 3:
#line 287 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_FILE_NUMBERS, { yyvsp[0] }); }
#line 3725 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 4:
#line 288 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_FILE_NUMBERS, { yyvsp[0] }); }
#line 3731 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 5:
#line 289 "parser.yy"
                                                        { yyval = yyvsp[-2]; yyval->push_back(yyvsp[0]); }
#line 3737 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 6:
#line 290 "parser.yy"
                                                        { yyval = yyvsp[-2]; yyval->push_back(yyvsp[0]); }
#line 3743 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 7:
#line 294 "parser.yy"
                                                                { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_LVALUE, { yyvsp[-3], yyvsp[-1] }); }
#line 3749 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 8:
#line 295 "parser.yy"
                                                                { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_LVALUE, { yyvsp[-3], yyvsp[-1] }); }
#line 3755 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 9:
#line 296 "parser.yy"
                                                                { vsk_targeting(yyvsp[-2]); yyval = vsk_ast(INSN_LVALUE, { yyvsp[-2], nullptr }); }
#line 3761 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 10:
#line 297 "parser.yy"
                                                                { vsk_targeting(yyvsp[-2]); yyval = vsk_ast(INSN_LVALUE, { yyvsp[-2], nullptr }); }
#line 3767 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 11:
#line 298 "parser.yy"
                                                                { yyval = yyvsp[0]; }
#line 3773 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 12:
#line 302 "parser.yy"
                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_LVALUE_LIST, { yyvsp[0] }); }
#line 3779 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 13:
#line 303 "parser.yy"
                                        { yyval = yyvsp[-2]; yyval->push_back(yyvsp[0]); }
#line 3785 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 14:
#line 307 "parser.yy"
                                { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_LABEL, { yyvsp[0] }); }
#line 3791 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 15:
#line 308 "parser.yy"
                                { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_LABEL, { yyvsp[0] }); }
#line 3797 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 16:
#line 312 "parser.yy"
                        { yyval = yyvsp[0]; yyvsp[0]->push_back(yyvsp[-1]); }
#line 3803 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 17:
#line 313 "parser.yy"
                        { yyval = yyvsp[0]; }
#line 3809 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 18:
#line 317 "parser.yy"
                        { yyval = yyvsp[0]; }
#line 3815 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 19:
#line 318 "parser.yy"
                        { yyval = yyvsp[0]; }
#line 3821 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 20:
#line 319 "parser.yy"
                        { yyval = yyvsp[0]; }
#line 3827 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 21:
#line 320 "parser.yy"
                        { yyval = yyvsp[0]; }
#line 3833 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 22:
#line 324 "parser.yy"
                        { yyval = yyvsp[0]; }
#line 3839 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 23:
#line 325 "parser.yy"
                        { yyval = yyvsp[0]; }
#line 3845 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 24:
#line 326 "parser.yy"
                        { yyval = yyvsp[0]; }
#line 3851 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 25:
#line 327 "parser.yy"
                        { yyval = yyvsp[0]; }
#line 3857 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 26:
#line 331 "parser.yy"
                                        { yyval = yyvsp[0]; }
#line 3863 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 27:
#line 332 "parser.yy"
                                        { yyval = yyvsp[0]; }
#line 3869 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 28:
#line 333 "parser.yy"
                                        { yyval = yyvsp[0]; }
#line 3875 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 29:
#line 334 "parser.yy"
                                        { yyval = yyvsp[-1]; }
#line 3881 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 30:
#line 335 "parser.yy"
                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_DATE_dollar_var); }
#line 3887 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 31:
#line 336 "parser.yy"
                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_TIME_dollar_var); }
#line 3893 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 32:
#line 337 "parser.yy"
                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_INKEY_dollar); }
#line 3899 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 33:
#line 338 "parser.yy"
                                                             { vsk_targeting(yyvsp[0]); yyval = yyvsp[0]; }
#line 3905 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 34:
#line 339 "parser.yy"
                                                             { vsk_targeting(yyvsp[-3]); yyval = yyvsp[-3]; yyval->children() = std::move(yyvsp[-1]->children()); }
#line 3911 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 35:
#line 340 "parser.yy"
                                                             { vsk_targeting(yyvsp[-2]); yyval = yyvsp[-2]; }
#line 3917 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 36:
#line 341 "parser.yy"
                                                             { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_ERL); }
#line 3923 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 37:
#line 342 "parser.yy"
                                                             { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_ERR); }
#line 3929 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 38:
#line 343 "parser.yy"
                                                             { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_RND, { yyvsp[-1] }); }
#line 3935 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 39:
#line 344 "parser.yy"
                                                             { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_RND); }
#line 3941 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 40:
#line 345 "parser.yy"
                                                                 { vsk_targeting(yyvsp[-5]); yyval = vsk_ast(INSN_VARPTR, { yyvsp[-3], yyvsp[-1] }); }
#line 3947 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 41:
#line 346 "parser.yy"
                                                                 { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_VARPTR, { yyvsp[-1] }); }
#line 3953 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 42:
#line 347 "parser.yy"
                                                                        {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_SEARCH, { yyvsp[-3], yyvsp[-1] });
    }
#line 3962 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 43:
#line 351 "parser.yy"
                                                                                            {
        vsk_targeting(yyvsp[-7]);
        yyval = vsk_ast(INSN_SEARCH, { yyvsp[-5], yyvsp[-3], yyvsp[-1] });
    }
#line 3971 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 44:
#line 355 "parser.yy"
                                                                                                                {
        vsk_targeting(yyvsp[-9]);
        yyval = vsk_ast(INSN_SEARCH, { yyvsp[-7], yyvsp[-5], yyvsp[-3], yyvsp[-1] });
    }
#line 3980 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 45:
#line 359 "parser.yy"
                                               { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_LOF, { yyvsp[-1] }); }
#line 3986 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 46:
#line 360 "parser.yy"
                                               { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_LOF, { yyvsp[-1] }); }
#line 3992 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 47:
#line 361 "parser.yy"
                                               { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_EOF, { yyvsp[-1] }); }
#line 3998 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 48:
#line 362 "parser.yy"
                                               { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_EOF, { yyvsp[-1] }); }
#line 4004 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 49:
#line 363 "parser.yy"
                                               { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_LOC, { yyvsp[-1] }); }
#line 4010 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 50:
#line 364 "parser.yy"
                                               { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_LOC, { yyvsp[-1] }); }
#line 4016 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 51:
#line 365 "parser.yy"
                                                { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_FPOS, { yyvsp[-1] }); }
#line 4022 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 52:
#line 366 "parser.yy"
                                                { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_FPOS, { yyvsp[-1] }); }
#line 4028 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 53:
#line 367 "parser.yy"
                                                                            { vsk_targeting(yyvsp[-5]); yyval = vsk_ast(INSN_INPUT_dollar, { yyvsp[-3], yyvsp[-1] }); }
#line 4034 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 54:
#line 368 "parser.yy"
                                                       { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_INPUT_dollar, { yyvsp[-1] }); }
#line 4040 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 55:
#line 372 "parser.yy"
                                         { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_PARAM_LIST, { yyvsp[0] }); }
#line 4046 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 56:
#line 373 "parser.yy"
                                         { yyval = yyvsp[-2]; yyval->push_back(yyvsp[0]); }
#line 4052 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 57:
#line 377 "parser.yy"
                                                                { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_PARAM_LIST, { yyvsp[0] }); }
#line 4058 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 58:
#line 378 "parser.yy"
                                                {
        yyval = yyvsp[-2];
        yyval->insert(yyval->end(), yyvsp[-1]->begin(), yyvsp[-1]->end());
        yyval->push_back(yyvsp[0]);
    }
#line 4068 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 59:
#line 383 "parser.yy"
                        {
        vsk_targeting(yyvsp[-1]);
        yyval = vsk_ast(INSN_PARAM_LIST);
        yyval->push_back(nullptr);
        yyval->insert(yyval->end(), yyvsp[-1]->begin(), yyvsp[-1]->end());
        yyval->push_back(yyvsp[0]);
    }
#line 4080 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 60:
#line 393 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_ABS); }
#line 4086 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 61:
#line 394 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_AKCNV_dollar); }
#line 4092 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 62:
#line 395 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_ASC); }
#line 4098 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 63:
#line 396 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_ATN); }
#line 4104 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 64:
#line 397 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_ATTR_dollar); }
#line 4110 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 65:
#line 398 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CDBL); }
#line 4116 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 66:
#line 399 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CHR_dollar); }
#line 4122 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 67:
#line 400 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CINT); }
#line 4128 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 68:
#line 401 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_COS); }
#line 4134 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 69:
#line 402 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CSNG); }
#line 4140 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 70:
#line 403 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CSRLIN); }
#line 4146 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 71:
#line 404 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CVD); }
#line 4152 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 72:
#line 405 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CVI); }
#line 4158 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 73:
#line 406 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CVS); }
#line 4164 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 74:
#line 407 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_DSKF); }
#line 4170 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 75:
#line 408 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_DSKI_dollar); }
#line 4176 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 76:
#line 409 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_EXP); }
#line 4182 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 77:
#line 410 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_FIX); }
#line 4188 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 78:
#line 411 "parser.yy"
                          { yyval = yyvsp[0]; }
#line 4194 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 79:
#line 412 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_FRE); }
#line 4200 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 80:
#line 413 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_HEX_dollar); }
#line 4206 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 81:
#line 414 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_INP); }
#line 4212 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 82:
#line 415 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_INSTR); }
#line 4218 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 83:
#line 416 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_INT); }
#line 4224 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 84:
#line 417 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_JIS_dollar); }
#line 4230 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 85:
#line 418 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_KACNV_dollar); }
#line 4236 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 86:
#line 419 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_KEXT_dollar); }
#line 4242 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 87:
#line 420 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_KINSTR); }
#line 4248 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 88:
#line 421 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_KLEN); }
#line 4254 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 89:
#line 422 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_KMID_dollar); }
#line 4260 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 90:
#line 423 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_KNJ_dollar); }
#line 4266 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 91:
#line 424 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_KPOS); }
#line 4272 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 92:
#line 425 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_KTYPE); }
#line 4278 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 93:
#line 426 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_LEFT_dollar); }
#line 4284 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 94:
#line 427 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_LEN); }
#line 4290 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 95:
#line 428 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_LOG); }
#line 4296 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 96:
#line 429 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_LPOS); }
#line 4302 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 97:
#line 430 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_MAP); }
#line 4308 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 98:
#line 431 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_MID_dollar_func); }
#line 4314 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 99:
#line 432 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_MKD_dollar); }
#line 4320 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 100:
#line 433 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_MKI_dollar); }
#line 4326 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 101:
#line 434 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_MKS_dollar); }
#line 4332 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 102:
#line 435 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_MOUSE_func); }
#line 4338 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 103:
#line 436 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_OCT_dollar); }
#line 4344 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 104:
#line 437 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_PEEK); }
#line 4350 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 105:
#line 438 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_PEN); }
#line 4356 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 106:
#line 439 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_POINT_func); }
#line 4362 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 107:
#line 440 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_POS); }
#line 4368 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 108:
#line 441 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_RIGHT_dollar); }
#line 4374 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 109:
#line 442 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_SGN); }
#line 4380 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 110:
#line 443 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_SIN); }
#line 4386 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 111:
#line 444 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_SPACE_dollar); }
#line 4392 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 112:
#line 445 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_SQR); }
#line 4398 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 113:
#line 446 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_STRING_dollar); }
#line 4404 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 114:
#line 447 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_STR_dollar); }
#line 4410 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 115:
#line 448 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_TAN); }
#line 4416 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 116:
#line 449 "parser.yy"
                          { yyval = yyvsp[0]; }
#line 4422 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 117:
#line 450 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_VAL); }
#line 4428 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 118:
#line 451 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_VIEW_func); }
#line 4434 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 119:
#line 452 "parser.yy"
                          { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_WINDOW_func); }
#line 4440 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 120:
#line 456 "parser.yy"
                                                         { yyval = yyvsp[0]; }
#line 4446 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 121:
#line 457 "parser.yy"
                                                         { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_HAT, { yyvsp[-2], yyvsp[0] }); }
#line 4452 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 122:
#line 460 "parser.yy"
                                       { yyval = yyvsp[0]; }
#line 4458 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 123:
#line 461 "parser.yy"
                                       { yyval = yyvsp[0]; }
#line 4464 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 124:
#line 462 "parser.yy"
                                       { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_UMINUS, { yyvsp[0] }); }
#line 4470 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 125:
#line 466 "parser.yy"
                                                             { yyval = yyvsp[0]; }
#line 4476 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 126:
#line 467 "parser.yy"
                                                             { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_MUL, { yyvsp[-2], yyvsp[0] }); }
#line 4482 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 127:
#line 468 "parser.yy"
                                                             { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_DIV, { yyvsp[-2], yyvsp[0] }); }
#line 4488 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 128:
#line 472 "parser.yy"
                                                                    { yyval = yyvsp[0]; }
#line 4494 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 129:
#line 473 "parser.yy"
                                                                    { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_IDIV, { yyvsp[-2], yyvsp[0] }); }
#line 4500 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 130:
#line 477 "parser.yy"
                                                       { yyval = yyvsp[0]; }
#line 4506 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 131:
#line 478 "parser.yy"
                                                       { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_MOD, { yyvsp[-2], yyvsp[0] }); }
#line 4512 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 132:
#line 482 "parser.yy"
                                                     { yyval = yyvsp[0]; }
#line 4518 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 133:
#line 483 "parser.yy"
                                                     { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_ADD, { yyvsp[-2], yyvsp[0] }); }
#line 4524 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 134:
#line 484 "parser.yy"
                                                     { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_SUB, { yyvsp[-2], yyvsp[0] }); }
#line 4530 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 135:
#line 488 "parser.yy"
                                                            { yyval = yyvsp[0]; }
#line 4536 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 136:
#line 489 "parser.yy"
                                                            { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_LT, { yyvsp[-2], yyvsp[0] }); }
#line 4542 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 137:
#line 490 "parser.yy"
                                                            { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_LE, { yyvsp[-2], yyvsp[0] }); }
#line 4548 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 138:
#line 491 "parser.yy"
                                                            { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_GT, { yyvsp[-2], yyvsp[0] }); }
#line 4554 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 139:
#line 492 "parser.yy"
                                                            { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_GE, { yyvsp[-2], yyvsp[0] }); }
#line 4560 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 140:
#line 493 "parser.yy"
                                                            { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_EQUAL, { yyvsp[-2], yyvsp[0] }); }
#line 4566 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 141:
#line 494 "parser.yy"
                                                            { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_NE, { yyvsp[-2], yyvsp[0] }); }
#line 4572 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 142:
#line 498 "parser.yy"
                                                        { yyval = yyvsp[0]; }
#line 4578 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 143:
#line 499 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_NOT, { yyvsp[0] });}
#line 4584 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 144:
#line 503 "parser.yy"
                                                        { yyval = yyvsp[0]; }
#line 4590 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 145:
#line 504 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_AND, { yyvsp[-2], yyvsp[0] }); }
#line 4596 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 146:
#line 508 "parser.yy"
                                                        { yyval = yyvsp[0]; }
#line 4602 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 147:
#line 509 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_OR, { yyvsp[-2], yyvsp[0] }); }
#line 4608 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 148:
#line 513 "parser.yy"
                                                        { yyval = yyvsp[0]; }
#line 4614 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 149:
#line 514 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_XOR, { yyvsp[-2], yyvsp[0] }); }
#line 4620 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 150:
#line 518 "parser.yy"
                                                        { yyval = yyvsp[0]; }
#line 4626 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 151:
#line 519 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_IMP, { yyvsp[-2], yyvsp[0] }); }
#line 4632 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 152:
#line 523 "parser.yy"
                                                        { yyval = yyvsp[0]; }
#line 4638 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 153:
#line 524 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_EQV, { yyvsp[-2], yyvsp[0] }); }
#line 4644 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 154:
#line 528 "parser.yy"
                                                        { yyval = yyvsp[0]; }
#line 4650 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 155:
#line 532 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast_str("AND"); }
#line 4656 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 156:
#line 533 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast_str("OR"); }
#line 4662 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 157:
#line 534 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast_str("XOR"); }
#line 4668 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 158:
#line 535 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast_str("PSET"); }
#line 4674 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 159:
#line 536 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast_str("PRESET"); }
#line 4680 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 160:
#line 540 "parser.yy"
                                                        { yyval = yyvsp[0]; }
#line 4686 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 161:
#line 541 "parser.yy"
                                                        { yyval = yyvsp[0]; }
#line 4692 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 162:
#line 545 "parser.yy"
                                                        { yyval = yyvsp[0]; }
#line 4698 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 163:
#line 546 "parser.yy"
                                                        { yyval = yyvsp[0]; }
#line 4704 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 164:
#line 550 "parser.yy"
                                                        { vsk_targeting(yyvsp[-2]); yyval = vsk_ast(INSN_FIELD_ITEM, { yyvsp[-2], yyvsp[-1], yyvsp[0] }); }
#line 4710 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 165:
#line 554 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_FIELD_ITEMS, { yyvsp[0] }); }
#line 4716 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 166:
#line 555 "parser.yy"
                                                        { yyval = yyvsp[-2]; yyval->push_back(yyvsp[0]); }
#line 4722 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 167:
#line 559 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_REM, yyvsp[0]->m_str); }
#line 4728 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 168:
#line 560 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_LABEL_DEF, yyvsp[0]->m_str); }
#line 4734 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 169:
#line 562 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_LET, { yyvsp[-2], yyvsp[0] }); }
#line 4740 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 170:
#line 563 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_LET, { yyvsp[-2], yyvsp[0] }); }
#line 4746 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 171:
#line 565 "parser.yy"
                                                                                         {
        vsk_targeting(yyvsp[-6]);
        yyval = vsk_ast(INSN_PRINT_USING, { yyvsp[-5], yyvsp[-2], yyvsp[0] });
    }
#line 4755 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 172:
#line 569 "parser.yy"
                                                                                      {
        vsk_targeting(yyvsp[-6]);
        yyval = vsk_ast(INSN_PRINT_USING, { yyvsp[-5], yyvsp[-2], yyvsp[0] });
    }
#line 4764 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 173:
#line 573 "parser.yy"
                                                             {
        vsk_targeting(yyvsp[-4]);
        yyval = vsk_ast(INSN_PRINT_USING, { nullptr, yyvsp[-2], yyvsp[0] });
    }
#line 4773 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 174:
#line 578 "parser.yy"
                                                      {
        vsk_targeting(yyvsp[-3]);
        yyval = vsk_ast(INSN_PRINT, { yyvsp[-2], yyvsp[0] });
    }
#line 4782 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 175:
#line 582 "parser.yy"
                                               {
        vsk_targeting(yyvsp[-3]);
        yyval = vsk_ast(INSN_PRINT, { yyvsp[-2], yyvsp[0] });
    }
#line 4791 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 176:
#line 586 "parser.yy"
                          {
        vsk_targeting(yyvsp[-1]);
        yyval = vsk_ast(INSN_PRINT, { nullptr, yyvsp[0] });
    }
#line 4800 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 177:
#line 590 "parser.yy"
            {
        vsk_targeting(yyvsp[0]);
        yyval = vsk_ast(INSN_PRINT, { nullptr, nullptr });
    }
#line 4809 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 178:
#line 595 "parser.yy"
                                                      {
        vsk_targeting(yyvsp[-3]);
        yyval = vsk_ast(INSN_WRITE, { yyvsp[-2], yyvsp[0] });
    }
#line 4818 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 179:
#line 599 "parser.yy"
                                                   {
        vsk_targeting(yyvsp[-3]);
        yyval = vsk_ast(INSN_WRITE, { yyvsp[-2], yyvsp[0] });
    }
#line 4827 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 180:
#line 603 "parser.yy"
                             {
        vsk_targeting(yyvsp[-1]);
        yyval = vsk_ast(INSN_WRITE, { nullptr, yyvsp[0] });
    }
#line 4836 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 181:
#line 607 "parser.yy"
               {
        vsk_targeting(yyvsp[0]);
        yyval = vsk_ast(INSN_WRITE, { nullptr, nullptr });
    }
#line 4845 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 182:
#line 612 "parser.yy"
                                                                 {
        vsk_targeting(yyvsp[-4]);
        yyval = vsk_ast(INSN_LPRINT_USING, { yyvsp[-2], yyvsp[0] });
    }
#line 4854 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 183:
#line 617 "parser.yy"
                              {
        vsk_targeting(yyvsp[-1]);
        yyval = vsk_ast(INSN_LPRINT, { yyvsp[0] });
    }
#line 4863 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 184:
#line 621 "parser.yy"
                {
        vsk_targeting(yyvsp[0]);
        yyval = vsk_ast(INSN_LPRINT, { nullptr });
    }
#line 4872 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 185:
#line 626 "parser.yy"
                                                                            {
        vsk_targeting(yyvsp[-7]);
        yyval = vsk_ast(INSN_FOR, { yyvsp[-6], yyvsp[-4], yyvsp[-2], yyvsp[0] });
    }
#line 4881 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 186:
#line 630 "parser.yy"
                                                         {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_FOR, { yyvsp[-4], yyvsp[-2], yyvsp[0], nullptr });
    }
#line 4890 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 187:
#line 635 "parser.yy"
                          {
        vsk_targeting(yyvsp[-1]);
        yyval = vsk_ast(INSN_NEXT);
        yyval->insert(yyval->end(), yyvsp[0]->begin(), yyvsp[0]->end());
    }
#line 4900 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 188:
#line 640 "parser.yy"
              {
        vsk_targeting(yyvsp[0]);
        yyval = vsk_ast(INSN_NEXT);
    }
#line 4909 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 189:
#line 644 "parser.yy"
                                                                        {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_OPEN, { yyvsp[-4], yyvsp[-2], yyvsp[-1], yyvsp[0] });
    }
#line 4918 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 190:
#line 648 "parser.yy"
                                                                   {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_OPEN, { yyvsp[-4], yyvsp[-2], yyvsp[-1], yyvsp[0] });
    }
#line 4927 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 191:
#line 652 "parser.yy"
                                                                       {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_OPEN, { yyvsp[-4], yyvsp[-2], yyvsp[-1], yyvsp[0] });
    }
#line 4936 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 192:
#line 656 "parser.yy"
                                                                  {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_OPEN, { yyvsp[-4], yyvsp[-2], yyvsp[-1], yyvsp[0] });
    }
#line 4945 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 193:
#line 660 "parser.yy"
                                                   {
        vsk_targeting(yyvsp[-3]);
        yyval = vsk_ast(INSN_OPEN, { yyvsp[-2], nullptr, yyvsp[-1], yyvsp[0] });
    }
#line 4954 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 194:
#line 664 "parser.yy"
                                                  {
        vsk_targeting(yyvsp[-3]);
        yyval = vsk_ast(INSN_OPEN, { yyvsp[-2], nullptr, yyvsp[-1], yyvsp[0] });
    }
#line 4963 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 195:
#line 668 "parser.yy"
                                                            {
        vsk_targeting(yyvsp[-4]);
        yyval = vsk_ast(INSN_LINE_INPUT, { yyvsp[-2], yyvsp[0] });
    }
#line 4972 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 196:
#line 672 "parser.yy"
                              {
        vsk_targeting(yyvsp[-2]);
        yyval = vsk_ast(INSN_LINE_INPUT, { nullptr, yyvsp[0] });
    }
#line 4981 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 197:
#line 676 "parser.yy"
                                                   {
        vsk_targeting(yyvsp[-4]);
        yyval = vsk_ast(INSN_LINE_INPUT_sharp, { yyvsp[-2], yyvsp[0] });
    }
#line 4990 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 198:
#line 680 "parser.yy"
                                                       {
        vsk_targeting(yyvsp[-4]);
        yyval = vsk_ast(INSN_LINE_INPUT_sharp, { yyvsp[-2], yyvsp[0] });
    }
#line 4999 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 199:
#line 684 "parser.yy"
                       {
        vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_KINPUT, { yyvsp[0] });
    }
#line 5007 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 200:
#line 687 "parser.yy"
                                                                                        {
        vsk_targeting(yyvsp[-7]);
        yyval = vsk_ast(INSN_LINE_INPUT_WAIT, { yyvsp[-4], yyvsp[-2], yyvsp[0] });
    }
#line 5016 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 201:
#line 691 "parser.yy"
                                                          {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_LINE_INPUT_WAIT, { yyvsp[-2], nullptr, yyvsp[0] });
    }
#line 5025 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 202:
#line 695 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_DIM, { yyvsp[0] }); }
#line 5031 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 203:
#line 696 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_DEF_SEG, { yyvsp[0] }); }
#line 5037 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 204:
#line 697 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_DEF_USR, { yyvsp[-2], yyvsp[0] }); }
#line 5043 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 205:
#line 698 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_ON_COM_GOSUB, { yyvsp[0] }); }
#line 5049 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 206:
#line 699 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_ON_ERROR_GOTO, { yyvsp[0] }); }
#line 5055 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 207:
#line 700 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_ON_EXPR_GOTO, { yyvsp[-2], yyvsp[0] }); }
#line 5061 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 208:
#line 701 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_ON_EXPR_GOSUB, { yyvsp[-2], yyvsp[0] }); }
#line 5067 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 209:
#line 702 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_ON_HELP_GOSUB, { yyvsp[0] }); }
#line 5073 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 210:
#line 703 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_ON_KEY_GOSUB, { yyvsp[0] }); }
#line 5079 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 211:
#line 704 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_ON_PEN_GOSUB, { yyvsp[0] }); }
#line 5085 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 212:
#line 705 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_ON_PLAY_GOSUB, { yyvsp[0] }); }
#line 5091 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 213:
#line 706 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_ON_STOP_GOSUB, { yyvsp[0] }); }
#line 5097 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 214:
#line 707 "parser.yy"
                                                                 {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_ON_TIME_dollar_GOSUB, { yyvsp[-2], yyvsp[0] });
    }
#line 5106 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 215:
#line 711 "parser.yy"
                                                                         {
        vsk_targeting(yyvsp[-3]);
        yyval = vsk_ast(INSN_ON_MOUSE_GOSUB, { nullptr, yyvsp[0] });
    }
#line 5115 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 216:
#line 715 "parser.yy"
                                                                         {
        vsk_targeting(yyvsp[-6]);
        yyval = vsk_ast(INSN_ON_MOUSE_GOSUB, { yyvsp[-3], yyvsp[0] });
    }
#line 5124 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 217:
#line 719 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_GOSUB, { yyvsp[0] }); }
#line 5130 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 218:
#line 720 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast_goto(yyvsp[0]); }
#line 5136 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 219:
#line 721 "parser.yy"
                                                         {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_CMD, { yyvsp[-4], yyvsp[-3], yyvsp[-2], yyvsp[0] });
    }
#line 5145 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 220:
#line 725 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_CMD, { yyvsp[-2], yyvsp[-1] }); yyval->insert(yyval->end(), yyvsp[0]->begin(), yyvsp[0]->end()); }
#line 5151 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 221:
#line 726 "parser.yy"
                                                        { vsk_targeting(yyvsp[-2]); yyval = vsk_ast(INSN_CMD, { yyvsp[-1] }); yyval->insert(yyval->end(), yyvsp[0]->begin(), yyvsp[0]->end()); }
#line 5157 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 222:
#line 727 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_CMD, { yyvsp[0] }); }
#line 5163 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 223:
#line 728 "parser.yy"
                                                        { yyval = yyvsp[-2]; yyval->insert(yyval->end(), yyvsp[0]->begin(), yyvsp[0]->end()); }
#line 5169 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 224:
#line 729 "parser.yy"
                                                        { yyval = yyvsp[0]; }
#line 5175 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 225:
#line 730 "parser.yy"
                                                        { yyval = yyvsp[-1]; yyval->insert(yyval->end(), yyvsp[0]->begin(), yyvsp[0]->end()); }
#line 5181 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 226:
#line 731 "parser.yy"
                                                        { yyval = yyvsp[0]; }
#line 5187 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 227:
#line 732 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_INPUT_semicolon, { yyvsp[-2], yyvsp[0] }); }
#line 5193 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 228:
#line 733 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_INPUT, { yyvsp[-2], yyvsp[0] }); }
#line 5199 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 229:
#line 734 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_INPUT, { nullptr, yyvsp[0] }); }
#line 5205 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 230:
#line 735 "parser.yy"
                                                                              {
        vsk_targeting(yyvsp[-6]);
        yyval = vsk_ast(INSN_INPUT_WAIT_semicolon, { yyvsp[-4], yyvsp[-2], yyvsp[0] });
    }
#line 5214 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 231:
#line 739 "parser.yy"
                                                                              {
        vsk_targeting(yyvsp[-4]);
        yyval = vsk_ast(INSN_INPUT_WAIT_semicolon, { yyvsp[-2], nullptr, yyvsp[0] });
    }
#line 5223 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 232:
#line 743 "parser.yy"
                                                                          {
        vsk_targeting(yyvsp[-6]);
        yyval = vsk_ast(INSN_INPUT_WAIT, { yyvsp[-4], yyvsp[-2], yyvsp[0] });
    }
#line 5232 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 233:
#line 747 "parser.yy"
                                                                          {
        vsk_targeting(yyvsp[-4]);
        yyval = vsk_ast(INSN_INPUT_WAIT, { yyvsp[-2], nullptr, yyvsp[0] });
    }
#line 5241 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 234:
#line 751 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_LSET, { yyvsp[-2], yyvsp[0] }); }
#line 5247 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 235:
#line 752 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_RSET, { yyvsp[-2], yyvsp[0] }); }
#line 5253 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 236:
#line 753 "parser.yy"
                                                        { vsk_targeting(yyvsp[-2]); yyval = vsk_ast(INSN_TIME_dollar, { yyvsp[0] }); }
#line 5259 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 237:
#line 754 "parser.yy"
                                                        { vsk_targeting(yyvsp[-2]); yyval = vsk_ast(INSN_DATE_dollar, { yyvsp[0] }); }
#line 5265 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 238:
#line 755 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_DELETE, { yyvsp[0] }); }
#line 5271 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 239:
#line 756 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_RESUME, { yyvsp[0] }); }
#line 5277 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 240:
#line 757 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_RESUME, { yyvsp[0] }); }
#line 5283 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 241:
#line 758 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_RESUME);}
#line 5289 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 242:
#line 760 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_GET_sharp, { yyvsp[-2], yyvsp[0] }); }
#line 5295 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 243:
#line 761 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_GET_sharp, { yyvsp[0], nullptr }); }
#line 5301 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 244:
#line 762 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_GET_sharp, { yyvsp[-2], yyvsp[0] }); }
#line 5307 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 245:
#line 763 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_GET_sharp, { yyvsp[0], nullptr }); }
#line 5313 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 246:
#line 765 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_PUT_sharp, { yyvsp[-2], yyvsp[0] });}
#line 5319 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 247:
#line 766 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_PUT_sharp, { yyvsp[0], nullptr });}
#line 5325 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 248:
#line 767 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_PUT_sharp, { yyvsp[-2], yyvsp[0] });}
#line 5331 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 249:
#line 768 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_PUT_sharp, { yyvsp[0], nullptr });}
#line 5337 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 250:
#line 770 "parser.yy"
                                                                                                                                                        {
        vsk_targeting(yyvsp[-14]);
        yyval = vsk_ast(INSN_GET_at_STEP, { yyvsp[-12], yyvsp[-10], yyvsp[-5], yyvsp[-3], yyvsp[0] });
    }
#line 5346 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 251:
#line 775 "parser.yy"
                                                                                                                                                        {
        vsk_targeting(yyvsp[-13]);
        yyval = vsk_ast(INSN_GET_at, { yyvsp[-11], yyvsp[-9], yyvsp[-5], yyvsp[-3], yyvsp[0] });
    }
#line 5355 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 252:
#line 779 "parser.yy"
                                                                                                                                                                                    {
        // PUT@(50,50),KANJI(...),OP,color1,color2
        vsk_targeting(yyvsp[-16]);
        yyval = vsk_ast(INSN_PUT_at_KANJI, { yyvsp[-14], yyvsp[-12], yyvsp[-7], yyvsp[-4], yyvsp[-2], yyvsp[0] });
    }
#line 5365 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 253:
#line 784 "parser.yy"
                                                                                                                                                                      {
        // PUT@(50,50),KANJI(...),,color1,color2
        vsk_targeting(yyvsp[-15]);
        yyval = vsk_ast(INSN_PUT_at_KANJI, { yyvsp[-13], yyvsp[-11], yyvsp[-6], yyvsp[-3], yyvsp[-2], yyvsp[0] });
    }
#line 5375 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 254:
#line 789 "parser.yy"
                                                                                                                                            {
        // PUT@(50,50),KANJI(...),OP
        vsk_targeting(yyvsp[-12]);
        yyval = vsk_ast(INSN_PUT_at_KANJI, { yyvsp[-10], yyvsp[-8], yyvsp[-3], yyvsp[0] });
    }
#line 5385 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 255:
#line 794 "parser.yy"
                                                                                                                     {
        // PUT@(50,50),KANJI(...)
        vsk_targeting(yyvsp[-10]);
        yyval = vsk_ast(INSN_PUT_at_KANJI, { yyvsp[-8], yyvsp[-6], yyvsp[-1] });
    }
#line 5395 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 256:
#line 799 "parser.yy"
                                                                                                                                                 {
        vsk_targeting(yyvsp[-13]);
        yyval = vsk_ast(INSN_PUT_at, { yyvsp[-11], yyvsp[-9], yyvsp[-6], yyvsp[-4], yyvsp[-2], yyvsp[0] });
    }
#line 5404 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 257:
#line 803 "parser.yy"
                                                                                                         {
        vsk_targeting(yyvsp[-9]);
        yyval = vsk_ast(INSN_PUT_at, { yyvsp[-7], yyvsp[-5], yyvsp[-2], yyvsp[0] });
    }
#line 5413 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 258:
#line 807 "parser.yy"
                                                                                  {
        vsk_targeting(yyvsp[-7]);
        yyval = vsk_ast(INSN_PUT_at, { yyvsp[-5], yyvsp[-3], yyvsp[0] });
    }
#line 5422 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 259:
#line 812 "parser.yy"
                                                                                                             {
        vsk_targeting(yyvsp[-9]);
        yyval = vsk_ast(INSN_CHAIN_MERGE, { yyvsp[-7], yyvsp[-5], yyvsp[-3], yyvsp[0] });
    }
#line 5431 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 260:
#line 816 "parser.yy"
                                                                                      {
        vsk_targeting(yyvsp[-7]);
        yyval = vsk_ast(INSN_CHAIN_MERGE, { yyvsp[-5], yyvsp[-3], nullptr, yyvsp[0] });
    }
#line 5440 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 261:
#line 820 "parser.yy"
                                                          {
        vsk_targeting(yyvsp[-4]);
        yyval = vsk_ast(INSN_CHAIN_MERGE, { yyvsp[-2], nullptr, yyvsp[0] });
    }
#line 5449 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 262:
#line 824 "parser.yy"
                                                                               {
        vsk_targeting(yyvsp[-6]);
        yyval = vsk_ast(INSN_CHAIN_MERGE, { yyvsp[-4], yyvsp[-2], yyvsp[0] });
    }
#line 5458 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 263:
#line 828 "parser.yy"
                                                        {
        vsk_targeting(yyvsp[-4]);
        yyval = vsk_ast(INSN_CHAIN_MERGE, { yyvsp[-2], yyvsp[0] });
    }
#line 5467 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 264:
#line 832 "parser.yy"
                                   {
        vsk_targeting(yyvsp[-2]);
        yyval = vsk_ast(INSN_CHAIN_MERGE, { yyvsp[0] });
    }
#line 5476 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 265:
#line 836 "parser.yy"
                                                 {
        vsk_targeting(yyvsp[-3]);
        yyval = vsk_ast(INSN_CHAIN, { yyvsp[-2], nullptr, yyvsp[0] });
    }
#line 5485 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 266:
#line 840 "parser.yy"
                                                                      {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_CHAIN, { yyvsp[-4], yyvsp[-2], yyvsp[0] });
    }
#line 5494 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 267:
#line 844 "parser.yy"
                                               {
        vsk_targeting(yyvsp[-3]);
        yyval = vsk_ast(INSN_CHAIN, { yyvsp[-2], yyvsp[0] });
    }
#line 5503 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 268:
#line 848 "parser.yy"
                          {
        vsk_targeting(yyvsp[-1]);
        yyval = vsk_ast(INSN_CHAIN, { yyvsp[0] });
    }
#line 5512 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 269:
#line 852 "parser.yy"
                                       {
        vsk_targeting(yyvsp[-3]);
        yyval = vsk_ast(INSN_DEF_FN, { yyvsp[-2], nullptr, yyvsp[0] });
    }
#line 5521 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 270:
#line 856 "parser.yy"
                                                             {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_DEF_FN, { yyvsp[-4], nullptr, yyvsp[0] });
    }
#line 5530 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 271:
#line 860 "parser.yy"
                                                                         {
        vsk_targeting(yyvsp[-6]);
        yyval = vsk_ast(INSN_DEF_FN, { yyvsp[-5], yyvsp[-3], yyvsp[0] });
    }
#line 5539 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 272:
#line 864 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_COM_OFF); }
#line 5545 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 273:
#line 865 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_COM_ON); }
#line 5551 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 274:
#line 866 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_COM_STOP); }
#line 5557 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 275:
#line 867 "parser.yy"
                                                        { vsk_targeting(yyvsp[-4]); yyval = vsk_ast(INSN_MOUSE_OFF, { yyvsp[-2] }); }
#line 5563 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 276:
#line 868 "parser.yy"
                                                        { vsk_targeting(yyvsp[-4]); yyval = vsk_ast(INSN_MOUSE_ON, { yyvsp[-2] }); }
#line 5569 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 277:
#line 869 "parser.yy"
                                                        { vsk_targeting(yyvsp[-4]); yyval = vsk_ast(INSN_MOUSE_STOP, { yyvsp[-2] }); }
#line 5575 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 278:
#line 870 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_MOUSE_OFF, { nullptr }); }
#line 5581 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 279:
#line 871 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_MOUSE_ON, { nullptr }); }
#line 5587 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 280:
#line 872 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_MOUSE_STOP, { nullptr }); }
#line 5593 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 281:
#line 873 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_PEN_OFF); }
#line 5599 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 282:
#line 874 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_PEN_ON); }
#line 5605 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 283:
#line 875 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_PEN_STOP); }
#line 5611 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 284:
#line 876 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_PLAY_OFF); }
#line 5617 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 285:
#line 877 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_PLAY_ON); }
#line 5623 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 286:
#line 878 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_PLAY_STOP); }
#line 5629 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 287:
#line 879 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_HELP_OFF); }
#line 5635 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 288:
#line 880 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_HELP_ON); }
#line 5641 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 289:
#line 881 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_HELP_STOP); }
#line 5647 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 290:
#line 882 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_TIME_dollar_OFF); }
#line 5653 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 291:
#line 883 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_TIME_dollar_ON); }
#line 5659 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 292:
#line 884 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_TIME_dollar_STOP); }
#line 5665 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 293:
#line 885 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_STOP_OFF); }
#line 5671 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 294:
#line 886 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_STOP_ON); }
#line 5677 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 295:
#line 887 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_STOP_STOP); }
#line 5683 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 296:
#line 888 "parser.yy"
                                                                            {
        vsk_targeting(yyvsp[-6]);
        yyval = vsk_ast(INSN_POINT_STEP, { yyvsp[-3], yyvsp[-1] });
    }
#line 5692 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 297:
#line 892 "parser.yy"
                                                                            {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_POINT, { yyvsp[-3], yyvsp[-1] });
    }
#line 5701 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 298:
#line 896 "parser.yy"
                                 {
        vsk_targeting(yyvsp[-1]);
        yyval = vsk_ast(INSN_EDIT, { yyvsp[0] });
    }
#line 5710 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 299:
#line 900 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_TROFF); }
#line 5716 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 300:
#line 901 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_TRON); }
#line 5722 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 301:
#line 902 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_LIST, { yyvsp[0] }); }
#line 5728 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 302:
#line 903 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_LIST); }
#line 5734 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 303:
#line 904 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_LLIST, { yyvsp[0] }); }
#line 5740 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 304:
#line 905 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_LLIST); }
#line 5746 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 305:
#line 906 "parser.yy"
                                                                     {
        vsk_targeting(yyvsp[-3]);
        yyvsp[0]->insert(yyvsp[0]->begin(), yyvsp[-2]);
        yyval = vsk_ast(INSN_CLOSE, { yyvsp[0] });
    }
#line 5756 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 306:
#line 911 "parser.yy"
                                {
        vsk_targeting(yyvsp[-1]);
        yyval = vsk_ast(INSN_CLOSE, { vsk_ast(INSN_FILE_NUMBERS, { yyvsp[0] }) });
    }
#line 5765 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 307:
#line 915 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_CLOSE, { yyvsp[0] }); }
#line 5771 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 308:
#line 916 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CLOSE, { nullptr }); }
#line 5777 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 309:
#line 917 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_RUN, { yyvsp[0], nullptr, nullptr }); }
#line 5783 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 310:
#line 918 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_RUN, { nullptr, yyvsp[-2], yyvsp[0] }); }
#line 5789 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 311:
#line 919 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_RUN, { nullptr, yyvsp[0], nullptr }); }
#line 5795 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 312:
#line 920 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_RUN, { nullptr, nullptr, nullptr }); }
#line 5801 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 313:
#line 921 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_LOAD, { yyvsp[-2], yyvsp[0] }); }
#line 5807 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 314:
#line 922 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_LOAD, { yyvsp[0], nullptr }); }
#line 5813 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 315:
#line 923 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_RESTORE, { yyvsp[0] }); }
#line 5819 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 316:
#line 924 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_RESTORE); }
#line 5825 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 317:
#line 925 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_ERASE, { yyvsp[0] }); }
#line 5831 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 318:
#line 926 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_SWAP, { yyvsp[-2], yyvsp[0] }); }
#line 5837 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 319:
#line 927 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_STOP); }
#line 5843 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 320:
#line 928 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_FIELD, { yyvsp[-2], yyvsp[0] }); }
#line 5849 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 321:
#line 929 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_FIELD, { yyvsp[-2], yyvsp[0] }); }
#line 5855 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 322:
#line 930 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_FIELD, { yyvsp[-2], yyvsp[0] }); }
#line 5861 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 323:
#line 931 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_RETURN, { yyvsp[0] }); }
#line 5867 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 324:
#line 932 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_RETURN); }
#line 5873 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 325:
#line 933 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_NAME, { yyvsp[-2], yyvsp[-1], yyvsp[0] }); }
#line 5879 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 326:
#line 934 "parser.yy"
                                                                   { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_PLAY, { yyvsp[-2], yyvsp[0] }); }
#line 5885 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 327:
#line 935 "parser.yy"
                                                                   { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_PLAY, { nullptr, yyvsp[0] }); }
#line 5891 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 328:
#line 936 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_AUTO, { yyvsp[-2], yyvsp[0] }); }
#line 5897 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 329:
#line 937 "parser.yy"
                                                        { vsk_targeting(yyvsp[-2]); yyval = vsk_ast(INSN_AUTO, { nullptr, yyvsp[0] }); }
#line 5903 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 330:
#line 938 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_AUTO, { yyvsp[0], nullptr }); }
#line 5909 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 331:
#line 939 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_AUTO, { nullptr, nullptr }); }
#line 5915 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 332:
#line 940 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_WIDTH_sharp, { yyvsp[-2], yyvsp[0] }); }
#line 5921 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 333:
#line 941 "parser.yy"
                                                        { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_WIDTH_sharp, { yyvsp[-2], yyvsp[0] }); }
#line 5927 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 334:
#line 942 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_COMMON); yyval->insert(yyval->end(), yyvsp[0]->begin(), yyvsp[0]->end()); }
#line 5933 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 335:
#line 943 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = yyvsp[0]; }
#line 5939 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 336:
#line 947 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_DIM_LIST, { yyvsp[0] }); }
#line 5945 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 337:
#line 948 "parser.yy"
                                                        { yyval = yyvsp[-2]; yyval->push_back(yyvsp[0]); }
#line 5951 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 338:
#line 952 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_IDENT_LIST, { yyvsp[0] }); }
#line 5957 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 339:
#line 953 "parser.yy"
                                                        { yyval = yyvsp[-2]; yyval->push_back(yyvsp[0]); }
#line 5963 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 340:
#line 957 "parser.yy"
                            { yyval = yyvsp[0]; }
#line 5969 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 341:
#line 958 "parser.yy"
                            { yyval = yyvsp[0]; }
#line 5975 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 342:
#line 962 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_PRINTING, { yyvsp[0] }); }
#line 5981 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 343:
#line 963 "parser.yy"
                                                        { yyval = yyvsp[-1]; yyval->push_back(yyvsp[0]); }
#line 5987 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 344:
#line 967 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_PRINTING, { yyvsp[0] }); }
#line 5993 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 345:
#line 968 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = yyvsp[-1]; yyval->push_back(yyvsp[0]); }
#line 5999 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 346:
#line 969 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = yyvsp[-1]; yyval->push_back(vsk_ast(INSN_COMMA)); }
#line 6005 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 347:
#line 970 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = yyvsp[-1]; yyval->push_back(vsk_ast(INSN_SEMICOLON)); }
#line 6011 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 348:
#line 974 "parser.yy"
                            { yyval = yyvsp[0]; }
#line 6017 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 349:
#line 975 "parser.yy"
                            { yyval = yyvsp[0]; }
#line 6023 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 350:
#line 979 "parser.yy"
                            { yyval = yyvsp[0]; }
#line 6029 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 351:
#line 980 "parser.yy"
                            { yyval = yyvsp[0]; }
#line 6035 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 352:
#line 984 "parser.yy"
                                                { yyval = yyvsp[0]; }
#line 6041 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 353:
#line 985 "parser.yy"
                                                { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_SPC, { yyvsp[-1] });}
#line 6047 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 354:
#line 986 "parser.yy"
                                                { vsk_targeting(yyvsp[-3]); yyval = vsk_ast(INSN_TAB, { yyvsp[-1] });}
#line 6053 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 355:
#line 987 "parser.yy"
                                                { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_COMMA); }
#line 6059 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 356:
#line 988 "parser.yy"
                                                { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_SEMICOLON); }
#line 6065 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 357:
#line 992 "parser.yy"
                                                { yyval = yyvsp[0]; }
#line 6071 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 358:
#line 993 "parser.yy"
                                                { yyval = yyvsp[0]; }
#line 6077 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 359:
#line 997 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_BEEP); }
#line 6083 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 360:
#line 998 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_BLOAD); }
#line 6089 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 361:
#line 999 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_BSAVE); }
#line 6095 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 362:
#line 1000 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CALL); }
#line 6101 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 363:
#line 1001 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CHILD); }
#line 6107 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 364:
#line 1002 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CLEAR); }
#line 6113 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 365:
#line 1003 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CLS); }
#line 6119 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 366:
#line 1004 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_COLOR); }
#line 6125 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 367:
#line 1005 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CONSOLE); }
#line 6131 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 368:
#line 1006 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CONT); }
#line 6137 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 369:
#line 1007 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_COPY); }
#line 6143 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 370:
#line 1008 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_DATA); }
#line 6149 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 371:
#line 1009 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_DEFDBL); }
#line 6155 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 372:
#line 1010 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_DEFINT); }
#line 6161 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 373:
#line 1011 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_DEFSNG); }
#line 6167 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 374:
#line 1012 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_DEFSTR); }
#line 6173 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 375:
#line 1013 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_DRAW); }
#line 6179 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 376:
#line 1014 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_DSKO_dollar); }
#line 6185 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 377:
#line 1015 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_END); }
#line 6191 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 378:
#line 1016 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_ERROR); }
#line 6197 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 379:
#line 1017 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_FILES); }
#line 6203 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 380:
#line 1018 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_KEY); }
#line 6209 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 381:
#line 1019 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_KEY_LIST); }
#line 6215 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 382:
#line 1020 "parser.yy"
                                                        { vsk_targeting(yyvsp[-4]); yyval = vsk_ast(INSN_KEY_OFF, { yyvsp[-2] }); }
#line 6221 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 383:
#line 1021 "parser.yy"
                                                        { vsk_targeting(yyvsp[-4]); yyval = vsk_ast(INSN_KEY_ON, { yyvsp[-2] }); }
#line 6227 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 384:
#line 1022 "parser.yy"
                                                        { vsk_targeting(yyvsp[-4]); yyval = vsk_ast(INSN_KEY_STOP, { yyvsp[-2] }); }
#line 6233 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 385:
#line 1023 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_KEY_OFF); }
#line 6239 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 386:
#line 1024 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_KEY_ON); }
#line 6245 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 387:
#line 1025 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_KEY_STOP); }
#line 6251 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 388:
#line 1026 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_KILL); }
#line 6257 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 389:
#line 1027 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_KPLOAD); }
#line 6263 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 390:
#line 1028 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_LFILES); }
#line 6269 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 391:
#line 1029 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_LOAD_question); }
#line 6275 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 392:
#line 1030 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_LOCATE); }
#line 6281 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 393:
#line 1031 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_MERGE); }
#line 6287 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 394:
#line 1032 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_MON); }
#line 6293 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 395:
#line 1033 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_MOTOR); }
#line 6299 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 396:
#line 1034 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_MOUSE_stmt); }
#line 6305 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 397:
#line 1035 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_NEW); }
#line 6311 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 398:
#line 1036 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_NEW_CMD); }
#line 6317 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 399:
#line 1037 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_NEW_ON); }
#line 6323 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 400:
#line 1038 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_OPTION_IDENT, { yyvsp[0] }); }
#line 6329 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 401:
#line 1039 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_OUT); }
#line 6335 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 402:
#line 1040 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_PLAY_ALLOC); }
#line 6341 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 403:
#line 1041 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_PLAY); }
#line 6347 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 404:
#line 1042 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_POKE); }
#line 6353 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 405:
#line 1043 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_RANDOMIZE); }
#line 6359 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 406:
#line 1044 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_READ); }
#line 6365 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 407:
#line 1045 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_RENUM); }
#line 6371 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 408:
#line 1046 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_ROLL); }
#line 6377 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 409:
#line 1047 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_SAVE); }
#line 6383 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 410:
#line 1048 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_SCREEN); }
#line 6389 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 411:
#line 1049 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_SET); }
#line 6395 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 412:
#line 1050 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_SET); }
#line 6401 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 413:
#line 1051 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_SYSTEM); }
#line 6407 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 414:
#line 1052 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_TERM); }
#line 6413 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 415:
#line 1053 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_WAIT); }
#line 6419 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 416:
#line 1054 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_WEND); }
#line 6425 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 417:
#line 1055 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_WHILE); }
#line 6431 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 418:
#line 1056 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_WIDTH); }
#line 6437 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 419:
#line 1057 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_CHDIR); }
#line 6443 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 420:
#line 1058 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_MKDIR); }
#line 6449 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 421:
#line 1059 "parser.yy"
                                                        { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_RMDIR); }
#line 6455 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 422:
#line 1060 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_WIDTH_LPRINT); }
#line 6461 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 423:
#line 1061 "parser.yy"
                                                                                                             {
        vsk_targeting(yyvsp[-9]);
        yyval = vsk_ast(INSN_MID_dollar_stmt, { yyvsp[-7], yyvsp[-5], yyvsp[-3], yyvsp[0] });
    }
#line 6470 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 424:
#line 1065 "parser.yy"
                                                                                                {
        vsk_targeting(yyvsp[-7]);
        yyval = vsk_ast(INSN_MID_dollar_stmt, { yyvsp[-5], yyvsp[-3], nullptr, yyvsp[0] });
    }
#line 6479 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 425:
#line 1072 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_INPUT_sharp, { yyvsp[0] });}
#line 6485 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 426:
#line 1073 "parser.yy"
                                                        { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_INPUT_sharp, { yyvsp[0] });}
#line 6491 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 427:
#line 1074 "parser.yy"
                                                                                    {
        // LINE -STEP(100,100) likely
        vsk_targeting(yyvsp[-7]);
        yyval = vsk_ast(INSN_LINE1, { nullptr, nullptr, yyvsp[-3], yyvsp[-1] });
    }
#line 6501 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 428:
#line 1079 "parser.yy"
                                                                            {
        // LINE -(100,100) likely
        vsk_targeting(yyvsp[-6]);
        yyval = vsk_ast(INSN_LINE0, { nullptr, nullptr, yyvsp[-3], yyvsp[-1] });
    }
#line 6511 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 429:
#line 1084 "parser.yy"
                                                                                                                                                 {
        // LINE STEP(0,0)-STEP(100,100) likely
        vsk_targeting(yyvsp[-13]);
        yyval = vsk_ast(INSN_LINE3, { yyvsp[-10], yyvsp[-8], yyvsp[-3], yyvsp[-1] });
    }
#line 6521 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 430:
#line 1089 "parser.yy"
                                                                                                                                         {
        // LINE STEP(0,0)-(100,100) likely
        vsk_targeting(yyvsp[-12]);
        yyval = vsk_ast(INSN_LINE2, { yyvsp[-9], yyvsp[-7], yyvsp[-3], yyvsp[-1] });
    }
#line 6531 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 431:
#line 1094 "parser.yy"
                                                                                                                                         {
        // LINE(0,0)-STEP(100,100) likely
        vsk_targeting(yyvsp[-12]);
        yyval = vsk_ast(INSN_LINE1, { yyvsp[-10], yyvsp[-8], yyvsp[-3], yyvsp[-1] });
    }
#line 6541 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 432:
#line 1099 "parser.yy"
                                                                                                                                 {
        // LINE(0,0)-(100,100) likely
        vsk_targeting(yyvsp[-11]);
        yyval = vsk_ast(INSN_LINE0, { yyvsp[-9], yyvsp[-7], yyvsp[-3], yyvsp[-1] });
    }
#line 6551 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 433:
#line 1104 "parser.yy"
                                                                                         {
        vsk_targeting(yyvsp[-7]);
        yyval = vsk_ast(INSN_CIRCLE, { yyvsp[-5], yyvsp[-3], yyvsp[0] });
    }
#line 6560 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 434:
#line 1108 "parser.yy"
                                                                                                 {
        vsk_targeting(yyvsp[-8]);
        yyval = vsk_ast(INSN_CIRCLE_STEP, { yyvsp[-5], yyvsp[-3], yyvsp[0] });
    }
#line 6569 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 435:
#line 1112 "parser.yy"
                                                                           {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_PSET, { yyvsp[-3], yyvsp[-1] });
    }
#line 6578 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 436:
#line 1116 "parser.yy"
                                                                           {
        vsk_targeting(yyvsp[-6]);
        yyval = vsk_ast(INSN_PSET_STEP, { yyvsp[-3], yyvsp[-1] });
    }
#line 6587 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 437:
#line 1120 "parser.yy"
                                                                             {
        vsk_targeting(yyvsp[-6]);
        yyval = vsk_ast(INSN_PRESET_STEP, { yyvsp[-3], yyvsp[-1] });
    }
#line 6596 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 438:
#line 1124 "parser.yy"
                                                                             {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_PRESET, { yyvsp[-3], yyvsp[-1] });
    }
#line 6605 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 439:
#line 1128 "parser.yy"
                                                                            {
        vsk_targeting(yyvsp[-6]);
        yyval = vsk_ast(INSN_PAINT_STEP, { yyvsp[-3], yyvsp[-1] });
    }
#line 6614 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 440:
#line 1132 "parser.yy"
                                                                            {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_PAINT, { yyvsp[-3], yyvsp[-1] });
    }
#line 6623 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 441:
#line 1136 "parser.yy"
                                                                             {
        vsk_targeting(yyvsp[-6]);
        yyval = vsk_ast(INSN_COLOR_equal, { yyvsp[-3], yyvsp[-1] });
    }
#line 6632 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 442:
#line 1142 "parser.yy"
    {
        vsk_targeting(yyvsp[-11]);
        yyval = vsk_ast(INSN_COLOR_at, { yyvsp[-9], yyvsp[-7], yyvsp[-3], yyvsp[-1] });
    }
#line 6641 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 443:
#line 1146 "parser.yy"
                                                                                                                                 {
        vsk_targeting(yyvsp[-11]);
        yyval = vsk_ast(INSN_VIEW_stmt, { yyvsp[-9], yyvsp[-7], yyvsp[-3], yyvsp[-1] });
    }
#line 6650 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 444:
#line 1150 "parser.yy"
                                                                                                                                   {
        vsk_targeting(yyvsp[-11]);
        yyval = vsk_ast(INSN_WINDOW_stmt, { yyvsp[-9], yyvsp[-7], yyvsp[-3], yyvsp[-1] });
    }
#line 6659 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 445:
#line 1157 "parser.yy"
                                                                           {
        vsk_targeting(yyvsp[-2]);
        auto go_to_0 = vsk_ast_goto(yyvsp[-2]);
        vsk_targeting(yyvsp[0]);
        auto go_to_1 = vsk_ast_goto(yyvsp[0]);
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-4], go_to_0, go_to_1 });
    }
#line 6672 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 446:
#line 1165 "parser.yy"
                                                                           {
        vsk_targeting(yyvsp[-2]);
        auto go_to_0 = vsk_ast_goto(yyvsp[-2]);
        vsk_targeting(yyvsp[0]);
        auto go_to_1 = vsk_ast_goto(yyvsp[0]);
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-4], go_to_0, go_to_1 });
    }
#line 6685 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 447:
#line 1173 "parser.yy"
                                                                           {
        vsk_targeting(yyvsp[-2]);
        auto go_to = vsk_ast_goto(yyvsp[-2]);
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-4], go_to, yyvsp[0] });
    }
#line 6696 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 448:
#line 1179 "parser.yy"
                                                                           {
        vsk_targeting(yyvsp[0]);
        auto go_to = vsk_ast_goto(yyvsp[0]);
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-4], yyvsp[-2], go_to });
    }
#line 6707 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 449:
#line 1185 "parser.yy"
                                                                           {
        vsk_targeting(yyvsp[0]);
        auto go_to = vsk_ast_goto(yyvsp[0]);
        vsk_targeting(yyvsp[-4]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-3], vsk_ast(INSN_MULTI), go_to });
    }
#line 6718 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 450:
#line 1191 "parser.yy"
                                                                           {
        vsk_targeting(yyvsp[-4]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-3], vsk_ast(INSN_MULTI), yyvsp[0] });
    }
#line 6727 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 451:
#line 1195 "parser.yy"
                                                                           {
        vsk_targeting(yyvsp[-2]);
        auto go_to = vsk_ast_goto(yyvsp[-2]);
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-4], go_to, yyvsp[0] });
    }
#line 6738 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 452:
#line 1201 "parser.yy"
                                                                           {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-4], yyvsp[-2], yyvsp[0] });
    }
#line 6747 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 453:
#line 1205 "parser.yy"
                                                                           {
        vsk_targeting(yyvsp[-4]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-3], yyvsp[-1], vsk_ast(INSN_MULTI) });
    }
#line 6756 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 454:
#line 1209 "parser.yy"
                                                                           {
        vsk_targeting(yyvsp[-3]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-2], vsk_ast(INSN_MULTI), vsk_ast(INSN_MULTI) });
    }
#line 6765 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 455:
#line 1216 "parser.yy"
                                                                             {
        vsk_targeting(yyvsp[-2]);
        auto go_to = vsk_ast_goto(yyvsp[-2]);
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-4], go_to, yyvsp[0] });
    }
#line 6776 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 456:
#line 1222 "parser.yy"
                                                                             {
        vsk_targeting(yyvsp[-2]);
        auto go_to = vsk_ast_goto(yyvsp[-2]);
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-4], go_to, yyvsp[0] });
    }
#line 6787 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 457:
#line 1228 "parser.yy"
                                                                             {
        vsk_targeting(yyvsp[-5]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-4], yyvsp[-2], yyvsp[0] });
    }
#line 6796 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 458:
#line 1232 "parser.yy"
                                                                             {
        vsk_targeting(yyvsp[-4]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-3], vsk_ast(INSN_MULTI), yyvsp[0] });
    }
#line 6805 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 459:
#line 1236 "parser.yy"
                                                                             {
        vsk_targeting(yyvsp[0]);
        auto go_to = vsk_ast_goto(yyvsp[0]);
        vsk_targeting(yyvsp[-3]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-2], go_to, nullptr });
    }
#line 6816 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 460:
#line 1242 "parser.yy"
                                                                             {
        vsk_targeting(yyvsp[-3]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-2], yyvsp[0], nullptr });
    }
#line 6825 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 461:
#line 1246 "parser.yy"
                                                                             {
        vsk_targeting(yyvsp[-2]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-1], vsk_ast(INSN_MULTI), nullptr });
    }
#line 6834 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 462:
#line 1250 "parser.yy"
                                                                             {
        vsk_targeting(yyvsp[0]);
        auto go_to = vsk_ast_goto(yyvsp[0]);
        vsk_targeting(yyvsp[-3]);
        yyval = vsk_ast(INSN_IF, { yyvsp[-2], go_to, nullptr });
    }
#line 6845 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 463:
#line 1259 "parser.yy"
                                                   {
        vsk_targeting(yyvsp[-2]);
        yyval = vsk_ast_multi(yyvsp[-2], yyvsp[0]);
    }
#line 6854 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 464:
#line 1263 "parser.yy"
                                 {
        yyval = yyvsp[0];
    }
#line 6862 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 465:
#line 1266 "parser.yy"
                           {
        yyval = yyvsp[0];
    }
#line 6870 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 466:
#line 1269 "parser.yy"
                        {
        yyval = yyvsp[0];
    }
#line 6878 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 467:
#line 1272 "parser.yy"
                                 {
        yyval = yyvsp[-1];
    }
#line 6886 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 468:
#line 1278 "parser.yy"
                                                     {
        yyval = vsk_ast_multi(yyvsp[-2], yyvsp[0]);
    }
#line 6894 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 469:
#line 1281 "parser.yy"
                                   {
        vsk_targeting(yyvsp[-1]); yyval = yyvsp[0];
    }
#line 6902 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 470:
#line 1284 "parser.yy"
                             {
        yyval = yyvsp[0];
    }
#line 6910 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 471:
#line 1287 "parser.yy"
                                   {
        yyval = yyvsp[-1];
    }
#line 6918 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 472:
#line 1293 "parser.yy"
                           { yyval = yyvsp[0]; }
#line 6924 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 473:
#line 1294 "parser.yy"
                           { yyval = yyvsp[0]; }
#line 6930 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 474:
#line 1295 "parser.yy"
                           { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_MULTI); }
#line 6936 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 475:
#line 1299 "parser.yy"
                                { yyval = yyvsp[0]; }
#line 6942 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 476:
#line 1300 "parser.yy"
                                { vsk_targeting(yyvsp[0]); yyval = yyval = vsk_ast(INSN_LABEL, { vsk_ast(INSN_PERIOD) }); }
#line 6948 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 477:
#line 1304 "parser.yy"
                  {
        vsk_targeting(yyvsp[0]);
        yyval = vsk_ast(INSN_LINE_NUMBERS, { yyvsp[0] });
    }
#line 6957 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 478:
#line 1308 "parser.yy"
                                      {
        yyval = yyvsp[-2];
        yyval->insert(yyvsp[-2]->end(), yyvsp[-1]->begin(), yyvsp[-1]->end());
        yyval->push_back(yyvsp[0]);
    }
#line 6967 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 479:
#line 1313 "parser.yy"
                         {
        vsk_targeting(yyvsp[-1]);
        yyval = vsk_ast(INSN_LINE_NUMBERS, { nullptr });
        yyval->insert(yyval->end(), yyvsp[-1]->begin(), yyvsp[-1]->end());
        yyval->push_back(yyvsp[0]);
    }
#line 6978 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 480:
#line 1322 "parser.yy"
                                         { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_COMMAS); }
#line 6984 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 481:
#line 1323 "parser.yy"
                                         { yyval = yyvsp[-1]; yyval->push_back(nullptr); }
#line 6990 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 482:
#line 1327 "parser.yy"
                                                     { vsk_targeting(yyvsp[-2]); yyval = vsk_ast(INSN_LINE_RANGE, { yyvsp[-2], yyvsp[0] }); }
#line 6996 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 483:
#line 1328 "parser.yy"
                                                     { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_LINE_RANGE, { yyvsp[-1], nullptr }); }
#line 7002 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 484:
#line 1329 "parser.yy"
                                                     { vsk_targeting(yyvsp[-1]); yyval = vsk_ast(INSN_LINE_RANGE, { nullptr, yyvsp[0] }); }
#line 7008 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 485:
#line 1330 "parser.yy"
                                                     { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_LINE_RANGE, { yyvsp[0], yyvsp[0] }); }
#line 7014 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 486:
#line 1334 "parser.yy"
                                         { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_DIRTY_8BIT); }
#line 7020 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 487:
#line 1335 "parser.yy"
                                         { yyval = yyvsp[-1]; }
#line 7026 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 488:
#line 1339 "parser.yy"
                            { yyval = yyvsp[0]; }
#line 7032 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 489:
#line 1340 "parser.yy"
                            { yyval = yyvsp[0]; }
#line 7038 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 490:
#line 1341 "parser.yy"
                            { yyval = yyvsp[0]; }
#line 7044 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 491:
#line 1345 "parser.yy"
                                                   { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_PARAM_LIST, { yyvsp[0] }); }
#line 7050 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 492:
#line 1346 "parser.yy"
                                                   { vsk_targeting(yyvsp[0]); yyval = vsk_ast(INSN_PARAM_LIST, { yyvsp[0] }); }
#line 7056 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 493:
#line 1347 "parser.yy"
                                                   { yyval = yyvsp[0]; }
#line 7062 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 494:
#line 1348 "parser.yy"
                                                   { yyval = yyvsp[0]; yyval->insert(yyval->begin(), yyvsp[-2]); }
#line 7068 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 495:
#line 1352 "parser.yy"
                                     {
        vsk_targeting(yyvsp[-2]);
        vsk_target_line = yyvsp[-2]->to_int();
        yyval = vsk_ast_multi(yyvsp[-1], yyvsp[0]);
        yyval->m_program_line = vsk_target_line;
    }
#line 7079 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 496:
#line 1358 "parser.yy"
                          {
        vsk_targeting(yyvsp[-1]);
        vsk_target_line = yyvsp[-1]->to_int();
        yyval = yyvsp[0];
        yyval->m_program_line = vsk_target_line;
    }
#line 7090 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 497:
#line 1364 "parser.yy"
                           {
        vsk_targeting(yyvsp[-1]);
        yyval = vsk_ast_multi(yyvsp[-1], yyvsp[0]);
    }
#line 7099 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 498:
#line 1368 "parser.yy"
                {
        yyval = yyvsp[0];
    }
#line 7107 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 499:
#line 1374 "parser.yy"
                                { yyval = yyvsp[-1]; result = yyval; }
#line 7113 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 500:
#line 1375 "parser.yy"
                                { yyval = yyvsp[0]; result = yyval; }
#line 7119 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 501:
#line 1376 "parser.yy"
                                { yyval = yyvsp[0]; result = yyval; }
#line 7125 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;

  case 502:
#line 1377 "parser.yy"
                                { yyval = vsk_ast(INSN_MULTI); }
#line 7131 "C:/dev/VeySickProject/VeySicK/parser.cpp"
    break;


#line 7135 "C:/dev/VeySickProject/VeySicK/parser.cpp"

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
