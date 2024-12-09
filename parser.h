/* A Bison parser, made by GNU Bison 3.5.4.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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
