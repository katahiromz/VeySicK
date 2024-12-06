// VeySicK Parser by katahiromz
// Copyright (C) 2024 Katayama Hirofumi MZ <katayama.hirofumi.mz@gmail.com>
// License: MIT

%{
    #include "coreapi.h"
    typedef VskAstPtr YYSTYPE;
    #define YYSTYPE_IS_DECLARED
    int yylex(yyscan_t yyscanner);
%}

// The driver is passed by reference to the parser and to the scanner. This
// provides a simple but effective pure interface, not relying on global
// variables.
%lex-param {yyscan_t yyscanner}
%parse-param {VskParseResult& result} {yyscan_t yyscanner}

%token TK_ABS
%token TK_AKCNV_dollar
%token TK_ALLOC
%token TK_AMPERSAND
%token TK_AND
%token TK_ASC
%token TK_ASTERISK
%token TK_ATN
%token TK_ATTR_dollar
%token TK_AUTO
%token TK_BACKSLASH
%token TK_BANG
%token TK_BEEP
%token TK_BLOAD
%token TK_BSAVE
%token TK_CALL
%token TK_CDBL
%token TK_CHAIN
%token TK_CHDIR
%token TK_CHILD
%token TK_CHR_dollar
%token TK_CINT
%token TK_CIRCLE
%token TK_CLEAR
%token TK_CLOSE
%token TK_CLOSE_SHARP
%token TK_CLS
%token TK_CMD
%token TK_COLON
%token TK_COLOR
%token TK_COLOR_at
%token TK_COM
%token TK_COMMA
%token TK_COMMENT
%token TK_COMMON
%token TK_CONSOLE
%token TK_CONT
%token TK_COPY
%token TK_COS
%token TK_CSNG
%token TK_CSRLIN
%token TK_CVD
%token TK_CVI
%token TK_CVS
%token TK_DATA
%token TK_DATE_dollar
%token TK_DEF
%token TK_DEFDBL
%token TK_DEFINT
%token TK_DEFSNG
%token TK_DEFSTR
%token TK_DELETE
%token TK_DELIM
%token TK_DIGITS
%token TK_DIM
%token TK_DIRTY_8BIT
%token TK_DOLLAR
%token TK_DRAW
%token TK_DSKF
%token TK_DSKI_dollar
%token TK_DSKO_dollar
%token TK_EDIT
%token TK_ELSE
%token TK_END
%token TK_EOF
%token TK_EQUAL
%token TK_EQV
%token TK_ERASE
%token TK_ERL
%token TK_ERR
%token TK_ERROR
%token TK_EVAL
%token TK_EXP
%token TK_FIELD
%token TK_FIELD_sharp
%token TK_FILES
%token TK_FIX
%token TK_FLOATING
%token TK_FN
%token TK_FOR
%token TK_FPOS
%token TK_FRE
%token TK_GE
%token TK_GET
%token TK_GET_at
%token TK_GET_sharp
%token TK_GO
%token TK_GOSUB
%token TK_GOTO
%token TK_GT
%token TK_HAT
%token TK_HELP
%token TK_HEXADECIMAL
%token TK_HEX_dollar
%token TK_IDENTIFIER
%token TK_IEEE
%token TK_IF
%token TK_IFC
%token TK_IMP
%token TK_INKEY_dollar
%token TK_INP
%token TK_INPUT
%token TK_INPUT_dollar
%token TK_INPUT_sharp
%token TK_INSTR
%token TK_INT
%token TK_INVALID_CHARS
%token TK_IRESET
%token TK_ISET
%token TK_JIS_dollar
%token TK_KACNV_dollar
%token TK_KANJI
%token TK_KEXT_dollar
%token TK_KEY
%token TK_KILL
%token TK_KINPUT
%token TK_KINSTR
%token TK_KLEN
%token TK_KMID_dollar
%token TK_KNJ_dollar
%token TK_KPLOAD
%token TK_KPOS
%token TK_KTYPE
%token TK_LE
%token TK_LEFT_dollar
%token TK_LEN
%token TK_LET
%token TK_LFILES
%token TK_LINE
%token TK_LIST
%token TK_LLIST
%token TK_LOAD
%token TK_LOC
%token TK_LOCATE
%token TK_LOF
%token TK_LOG
%token TK_LPOS
%token TK_LPRINT
%token TK_LSET
%token TK_LT
%token TK_L_BRACE
%token TK_L_BRACKET
%token TK_L_PAREN
%token TK_MAIL
%token TK_MAP
%token TK_MERGE
%token TK_MID_dollar
%token TK_MINUS
%token TK_MKDIR
%token TK_MKD_dollar
%token TK_MKI_dollar
%token TK_MKS_dollar
%token TK_MOD
%token TK_MON
%token TK_MOTOR
%token TK_MOUSE
%token TK_NAME
%token TK_NE
%token TK_NEW
%token TK_NEWLINE
%token TK_NEXT
%token TK_NOT
%token TK_OCTAL
%token TK_OCT_dollar
%token TK_OFF
%token TK_ON
%token TK_OPEN
%token TK_OPTION
%token TK_OR
%token TK_OUT
%token TK_PAINT
%token TK_PEEK
%token TK_PEN
%token TK_PERCENT
%token TK_PERIOD
%token TK_PLAY
%token TK_PLUS
%token TK_POINT
%token TK_POKE
%token TK_POLL
%token TK_POS
%token TK_PRESET
%token TK_PRINT
%token TK_PRINT_SHARP
%token TK_PSET
%token TK_PUT
%token TK_PUT_at
%token TK_PUT_sharp
%token TK_QUESTION
%token TK_RANDOMIZE
%token TK_RBYTE
%token TK_READ
%token TK_REM
%token TK_RENUM
%token TK_RESTORE
%token TK_RESUME
%token TK_RETURN
%token TK_RIGHT_dollar
%token TK_RMDIR
%token TK_RND
%token TK_ROLL
%token TK_RSET
%token TK_RUN
%token TK_R_BRACE
%token TK_R_BRACKET
%token TK_R_PAREN
%token TK_SAVE
%token TK_SCREEN
%token TK_SEARCH
%token TK_SEG
%token TK_SEMICOLON
%token TK_SET
%token TK_SET_SHARP
%token TK_SGN
%token TK_SHARP
%token TK_SIN
%token TK_SLASH
%token TK_SPACE_dollar
%token TK_SPC
%token TK_SQR
%token TK_SRQ
%token TK_STATUS
%token TK_STEP
%token TK_STOP
%token TK_STRING
%token TK_STRING_dollar
%token TK_STR_dollar
%token TK_SUB
%token TK_SWAP
%token TK_SYSTEM
%token TK_TAB
%token TK_TAN
%token TK_TERM
%token TK_THEN
%token TK_TILDA
%token TK_TIMEOUT
%token TK_TIME_dollar
%token TK_TO
%token TK_TROFF
%token TK_TRON
%token TK_UNDERLINE
%token TK_USING
%token TK_USR
%token TK_VAL
%token TK_VARPTR
%token TK_VBAR
%token TK_VIEW
%token TK_WAIT
%token TK_WBYTE
%token TK_WEND
%token TK_WHILE
%token TK_WIDTH
%token TK_WIDTH_sharp
%token TK_WINDOW
%token TK_WRITE
%token TK_WRITE_SHARP
%token TK_XOR

%start translation_unit

%%

// Grammar rules

file_number
    : TK_SHARP primary_expression                       { vsk_targeting($1); $$ = vsk_ast(INSN_FILE_NUMBER, { $2 }); }
    ;

file_numbers_or_expressions
    : file_number                                       { vsk_targeting($1); $$ = vsk_ast(INSN_FILE_NUMBERS, { $1 }); }
    | expression                                        { vsk_targeting($1); $$ = vsk_ast(INSN_FILE_NUMBERS, { $1 }); }
    | file_numbers_or_expressions TK_COMMA file_number  { $$ = $1; $$->push_back($3); }
    | file_numbers_or_expressions TK_COMMA expression   { $$ = $1; $$->push_back($3); }
    ;

lvalue
    : TK_IDENTIFIER TK_L_PAREN   parameter_list TK_R_PAREN      { vsk_targeting($1); $$ = vsk_ast(INSN_LVALUE, { $1, $3 }); }
    | TK_IDENTIFIER TK_L_BRACKET parameter_list TK_R_BRACKET    { vsk_targeting($1); $$ = vsk_ast(INSN_LVALUE, { $1, $3 }); }
    | TK_IDENTIFIER                                             { $$ = $1; }
    ;

lvalue_list
    : lvalue                            { vsk_targeting($1); $$ = vsk_ast(INSN_LVALUE_LIST, { $1 }); }
    | lvalue_list TK_COMMA lvalue       { $$ = $1; $$->push_back($3); }
    ;

line_number
    : TK_DIGITS                 { vsk_targeting($1); $$ = vsk_ast(INSN_LABEL, { $1 }); }
    | TK_ASTERISK TK_IDENTIFIER { vsk_targeting($2); $$ = vsk_ast(INSN_LABEL, { $2 }); }
    ;

casted_number
    : number cast       { $$ = $2; $2->push_back($1); }
    | number            { $$ = $1; }
    ;

number
    : TK_DIGITS         { $$ = $1; }
    | TK_OCTAL          { $$ = $1; }
    | TK_HEXADECIMAL    { $$ = $1; }
    | TK_FLOATING       { $$ = $1; }
    ;

cast
    : TK_PERCENT        { $$ = $1; }
    | TK_SHARP          { $$ = $1; }
    | TK_BANG           { $$ = $1; }
    | TK_AMPERSAND      { $$ = $1; }
    ;

primary_expression
    : lvalue                            { $$ = $1; }
    | casted_number                     { $$ = $1; }
    | TK_STRING                         { $$ = $1; }
    | TK_L_PAREN expression TK_R_PAREN  { $$ = $2; }
    | TK_DATE_dollar                    { vsk_targeting($1); $$ = vsk_ast(INSN_DATE_dollar_var); }
    | TK_TIME_dollar                    { vsk_targeting($1); $$ = vsk_ast(INSN_TIME_dollar_var); }
    | TK_INKEY_dollar                   { vsk_targeting($1); $$ = vsk_ast(INSN_INKEY_dollar); }
    | function_name                                          { vsk_targeting($1); $$ = $1; }
    | function_name TK_L_PAREN parameter_list TK_R_PAREN     { vsk_targeting($1); $$ = $1; $$->children() = std::move($3->children()); }
    | function_name TK_L_PAREN TK_R_PAREN                    { vsk_targeting($1); $$ = $1; }
    | TK_ERL                                                 { vsk_targeting($1); $$ = vsk_ast(INSN_ERL); }
    | TK_ERR                                                 { vsk_targeting($1); $$ = vsk_ast(INSN_ERR); }
    | TK_RND TK_L_PAREN expression TK_R_PAREN                { vsk_targeting($1); $$ = vsk_ast(INSN_RND, { $3 }); }
    | TK_RND                                                 { vsk_targeting($1); $$ = vsk_ast(INSN_RND); }
    | TK_VARPTR TK_L_PAREN lvalue TK_COMMA expression TK_R_PAREN { vsk_targeting($1); $$ = vsk_ast(INSN_VARPTR, { $3, $5 }); }
    | TK_VARPTR TK_L_PAREN lvalue                     TK_R_PAREN { vsk_targeting($1); $$ = vsk_ast(INSN_VARPTR, { $3 }); }
    | TK_SEARCH TK_L_PAREN TK_IDENTIFIER TK_COMMA expression TK_R_PAREN {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_SEARCH, { $3, $5 });
    }
    | TK_SEARCH TK_L_PAREN TK_IDENTIFIER TK_COMMA expression TK_COMMA expression TK_R_PAREN {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_SEARCH, { $3, $5, $7 });
    }
    | TK_SEARCH TK_L_PAREN TK_IDENTIFIER TK_COMMA expression TK_COMMA expression TK_COMMA expression TK_R_PAREN {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_SEARCH, { $3, $5, $7, $9 });
    }
    | TK_LOF TK_L_PAREN file_number TK_R_PAREN { vsk_targeting($1); $$ = vsk_ast(INSN_LOF, { $3 }); }
    | TK_LOF TK_L_PAREN expression  TK_R_PAREN { vsk_targeting($1); $$ = vsk_ast(INSN_LOF, { $3 }); }
    | TK_EOF TK_L_PAREN file_number TK_R_PAREN { vsk_targeting($1); $$ = vsk_ast(INSN_EOF, { $3 }); }
    | TK_EOF TK_L_PAREN expression  TK_R_PAREN { vsk_targeting($1); $$ = vsk_ast(INSN_EOF, { $3 }); }
    | TK_LOC TK_L_PAREN expression  TK_R_PAREN { vsk_targeting($1); $$ = vsk_ast(INSN_LOC, { $3 }); }
    | TK_LOC TK_L_PAREN file_number TK_R_PAREN { vsk_targeting($1); $$ = vsk_ast(INSN_LOC, { $3 }); }
    | TK_FPOS TK_L_PAREN file_number TK_R_PAREN { vsk_targeting($1); $$ = vsk_ast(INSN_FPOS, { $3 }); }
    | TK_FPOS TK_L_PAREN expression  TK_R_PAREN { vsk_targeting($1); $$ = vsk_ast(INSN_FPOS, { $3 }); }
    | TK_INPUT_dollar TK_L_PAREN expression TK_COMMA file_number TK_R_PAREN { vsk_targeting($1); $$ = vsk_ast(INSN_INPUT_dollar, { $3, $5 }); }
    | TK_INPUT_dollar TK_L_PAREN expression TK_R_PAREN { vsk_targeting($1); $$ = vsk_ast(INSN_INPUT_dollar, { $3 }); }
    ;

parameter_list
    : expression                         { vsk_targeting($1); $$ = vsk_ast(INSN_PARAM_LIST, { $1 }); }
    | parameter_list TK_COMMA expression { $$ = $1; $$->push_back($3); }
    ;

trailing_parameter_list
    : expression                                                { vsk_targeting($1); $$ = vsk_ast(INSN_PARAM_LIST, { $1 }); }
    | trailing_parameter_list commas expression {
        $$ = $1;
        $$->insert($$->end(), $2->begin(), $2->end());
        $$->push_back($3);
    }
    | commas expression {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_PARAM_LIST);
        $$->push_back(nullptr);
        $$->insert($$->end(), $1->begin(), $1->end());
        $$->push_back($2);
    }
    ;

function_name
    : TK_ABS              { vsk_targeting($1); $$ = vsk_ast(INSN_ABS); }
    | TK_AKCNV_dollar     { vsk_targeting($1); $$ = vsk_ast(INSN_AKCNV_dollar); }
    | TK_ASC              { vsk_targeting($1); $$ = vsk_ast(INSN_ASC); }
    | TK_ATN              { vsk_targeting($1); $$ = vsk_ast(INSN_ATN); }
    | TK_ATTR_dollar      { vsk_targeting($1); $$ = vsk_ast(INSN_ATTR_dollar); }
    | TK_CDBL             { vsk_targeting($1); $$ = vsk_ast(INSN_CDBL); }
    | TK_CHR_dollar       { vsk_targeting($1); $$ = vsk_ast(INSN_CHR_dollar); }
    | TK_CINT             { vsk_targeting($1); $$ = vsk_ast(INSN_CINT); }
    | TK_COS              { vsk_targeting($1); $$ = vsk_ast(INSN_COS); }
    | TK_CSNG             { vsk_targeting($1); $$ = vsk_ast(INSN_CSNG); }
    | TK_CSRLIN           { vsk_targeting($1); $$ = vsk_ast(INSN_CSRLIN); }
    | TK_CVD              { vsk_targeting($1); $$ = vsk_ast(INSN_CVD); }
    | TK_CVI              { vsk_targeting($1); $$ = vsk_ast(INSN_CVI); }
    | TK_CVS              { vsk_targeting($1); $$ = vsk_ast(INSN_CVS); }
    | TK_DSKF             { vsk_targeting($1); $$ = vsk_ast(INSN_DSKF); }
    | TK_DSKI_dollar      { vsk_targeting($1); $$ = vsk_ast(INSN_DSKI_dollar); }
    | TK_EXP              { vsk_targeting($1); $$ = vsk_ast(INSN_EXP); }
    | TK_FIX              { vsk_targeting($1); $$ = vsk_ast(INSN_FIX); }
    | TK_FN               { $$ = $1; }
    | TK_FRE              { vsk_targeting($1); $$ = vsk_ast(INSN_FRE); }
    | TK_HEX_dollar       { vsk_targeting($1); $$ = vsk_ast(INSN_HEX_dollar); }
    | TK_INP              { vsk_targeting($1); $$ = vsk_ast(INSN_INP); }
    | TK_INSTR            { vsk_targeting($1); $$ = vsk_ast(INSN_INSTR); }
    | TK_INT              { vsk_targeting($1); $$ = vsk_ast(INSN_INT); }
    | TK_JIS_dollar       { vsk_targeting($1); $$ = vsk_ast(INSN_JIS_dollar); }
    | TK_KACNV_dollar     { vsk_targeting($1); $$ = vsk_ast(INSN_KACNV_dollar); }
    | TK_KEXT_dollar      { vsk_targeting($1); $$ = vsk_ast(INSN_KEXT_dollar); }
    | TK_KINSTR           { vsk_targeting($1); $$ = vsk_ast(INSN_KINSTR); }
    | TK_KLEN             { vsk_targeting($1); $$ = vsk_ast(INSN_KLEN); }
    | TK_KMID_dollar      { vsk_targeting($1); $$ = vsk_ast(INSN_KMID_dollar); }
    | TK_KNJ_dollar       { vsk_targeting($1); $$ = vsk_ast(INSN_KNJ_dollar); }
    | TK_KPOS             { vsk_targeting($1); $$ = vsk_ast(INSN_KPOS); }
    | TK_KTYPE            { vsk_targeting($1); $$ = vsk_ast(INSN_KTYPE); }
    | TK_LEFT_dollar      { vsk_targeting($1); $$ = vsk_ast(INSN_LEFT_dollar); }
    | TK_LEN              { vsk_targeting($1); $$ = vsk_ast(INSN_LEN); }
    | TK_LOG              { vsk_targeting($1); $$ = vsk_ast(INSN_LOG); }
    | TK_LPOS             { vsk_targeting($1); $$ = vsk_ast(INSN_LPOS); }
    | TK_MAP              { vsk_targeting($1); $$ = vsk_ast(INSN_MAP); }
    | TK_MID_dollar       { vsk_targeting($1); $$ = vsk_ast(INSN_MID_dollar_func); }
    | TK_MKD_dollar       { vsk_targeting($1); $$ = vsk_ast(INSN_MKD_dollar); }
    | TK_MKI_dollar       { vsk_targeting($1); $$ = vsk_ast(INSN_MKI_dollar); }
    | TK_MKS_dollar       { vsk_targeting($1); $$ = vsk_ast(INSN_MKS_dollar); }
    | TK_MOUSE            { vsk_targeting($1); $$ = vsk_ast(INSN_MOUSE_func); }
    | TK_OCT_dollar       { vsk_targeting($1); $$ = vsk_ast(INSN_OCT_dollar); }
    | TK_PEEK             { vsk_targeting($1); $$ = vsk_ast(INSN_PEEK); }
    | TK_PEN              { vsk_targeting($1); $$ = vsk_ast(INSN_PEN); }
    | TK_POINT            { vsk_targeting($1); $$ = vsk_ast(INSN_POINT_func); }
    | TK_POS              { vsk_targeting($1); $$ = vsk_ast(INSN_POS); }
    | TK_RIGHT_dollar     { vsk_targeting($1); $$ = vsk_ast(INSN_RIGHT_dollar); }
    | TK_SGN              { vsk_targeting($1); $$ = vsk_ast(INSN_SGN); }
    | TK_SIN              { vsk_targeting($1); $$ = vsk_ast(INSN_SIN); }
    | TK_SPACE_dollar     { vsk_targeting($1); $$ = vsk_ast(INSN_SPACE_dollar); }
    | TK_SQR              { vsk_targeting($1); $$ = vsk_ast(INSN_SQR); }
    | TK_STRING_dollar    { vsk_targeting($1); $$ = vsk_ast(INSN_STRING_dollar); }
    | TK_STR_dollar       { vsk_targeting($1); $$ = vsk_ast(INSN_STR_dollar); }
    | TK_TAN              { vsk_targeting($1); $$ = vsk_ast(INSN_TAN); }
    | TK_USR              { $$ = $1; }
    | TK_VAL              { vsk_targeting($1); $$ = vsk_ast(INSN_VAL); }
    | TK_VIEW             { vsk_targeting($1); $$ = vsk_ast(INSN_VIEW_func); }
    | TK_WINDOW           { vsk_targeting($1); $$ = vsk_ast(INSN_WINDOW_func); }
    ;

exponential_expression
    : primary_expression                                 { $$ = $1; }
    | exponential_expression TK_HAT primary_expression   { vsk_targeting($2); $$ = vsk_ast(INSN_HAT, { $1, $3 }); }

unary_expression
    : exponential_expression           { $$ = $1; }
    | TK_PLUS  exponential_expression  { $$ = $2; }
    | TK_MINUS exponential_expression  { vsk_targeting($1); $$ = vsk_ast(INSN_UMINUS, { $2 }); }
    ;

multiplicative_expression
    : unary_expression                                       { $$ = $1; }
    | multiplicative_expression TK_ASTERISK unary_expression { vsk_targeting($2); $$ = vsk_ast(INSN_MUL, { $1, $3 }); }
    | multiplicative_expression TK_SLASH unary_expression    { vsk_targeting($2); $$ = vsk_ast(INSN_DIV, { $1, $3 }); }
    ;

backslash_expression
    : multiplicative_expression                                     { $$ = $1; }
    | backslash_expression TK_BACKSLASH multiplicative_expression   { vsk_targeting($2); $$ = vsk_ast(INSN_IDIV, { $1, $3 }); }
    ;

mod_expression
    : backslash_expression                             { $$ = $1; }
    | mod_expression TK_MOD backslash_expression       { vsk_targeting($2); $$ = vsk_ast(INSN_MOD, { $1, $3 }); }
    ;

additive_expression
    : mod_expression                                 { $$ = $1; }
    | additive_expression TK_PLUS mod_expression     { vsk_targeting($2); $$ = vsk_ast(INSN_ADD, { $1, $3 }); }
    | additive_expression TK_MINUS mod_expression    { vsk_targeting($2); $$ = vsk_ast(INSN_SUB, { $1, $3 }); }
    ;

relational_expression
    : additive_expression                                   { $$ = $1; }
    | relational_expression TK_LT additive_expression       { vsk_targeting($2); $$ = vsk_ast(INSN_LT, { $1, $3 }); }
    | relational_expression TK_LE additive_expression       { vsk_targeting($2); $$ = vsk_ast(INSN_LE, { $1, $3 }); }
    | relational_expression TK_GT additive_expression       { vsk_targeting($2); $$ = vsk_ast(INSN_GT, { $1, $3 }); }
    | relational_expression TK_GE additive_expression       { vsk_targeting($2); $$ = vsk_ast(INSN_GE, { $1, $3 }); }
    | relational_expression TK_EQUAL additive_expression    { vsk_targeting($2); $$ = vsk_ast(INSN_EQUAL, { $1, $3 }); }
    | relational_expression TK_NE additive_expression       { vsk_targeting($2); $$ = vsk_ast(INSN_NE, { $1, $3 }); }
    ;

not_expression
    : relational_expression                             { $$ = $1; }
    | TK_NOT relational_expression                      { vsk_targeting($1); $$ = vsk_ast(INSN_NOT, { $2 });}
    ;

and_expression
    : not_expression                                    { $$ = $1; }
    | and_expression TK_AND not_expression              { vsk_targeting($2); $$ = vsk_ast(INSN_AND, { $1, $3 }); }
    ;

or_expression
    : and_expression                                    { $$ = $1; }
    | or_expression TK_OR and_expression                { vsk_targeting($2); $$ = vsk_ast(INSN_OR, { $1, $3 }); }
    ;

xor_expression
    : or_expression                                     { $$ = $1; }
    | xor_expression TK_XOR or_expression               { vsk_targeting($2); $$ = vsk_ast(INSN_XOR, { $1, $3 }); }
    ;

imp_expression
    : xor_expression                                    { $$ = $1; }
    | imp_expression TK_IMP xor_expression              { vsk_targeting($2); $$ = vsk_ast(INSN_IMP, { $1, $3 }); }
    ;

eqv_expression
    : imp_expression                                    { $$ = $1; }
    | eqv_expression TK_EQV imp_expression              { vsk_targeting($2); $$ = vsk_ast(INSN_EQV, { $1, $3 }); }
    ;

expression
    : eqv_expression                                    { $$ = $1; }
    ;

put_operation
    : TK_AND                                            { vsk_targeting($1); $$ = vsk_ast_str("AND"); }
    | TK_OR                                             { vsk_targeting($1); $$ = vsk_ast_str("OR"); }
    | TK_XOR                                            { vsk_targeting($1); $$ = vsk_ast_str("XOR"); }
    | TK_PSET                                           { vsk_targeting($1); $$ = vsk_ast_str("PSET"); }
    | TK_PRESET                                         { vsk_targeting($1); $$ = vsk_ast_str("PRESET"); }
    ;

put_at
    : TK_PUT_at                                         { $$ = $1; }
    | TK_PUT                                            { $$ = $1; }
    ;

get_at
    : TK_GET_at                                         { $$ = $1; }
    | TK_GET                                            { $$ = $1; }
    ;

field_item
    : expression TK_IDENTIFIER lvalue                   { vsk_targeting($1); $$ = vsk_ast(INSN_FIELD_ITEM, { $1, $2, $3 }); }
    ;

field_items
    : field_item                                        { vsk_targeting($1); $$ = vsk_ast(INSN_FIELD_ITEMS, { $1 }); }
    | field_items TK_COMMA field_item                   { $$ = $1; $$->push_back($3); }
    ;

primary_statement
    : TK_COMMENT                                        { vsk_targeting($1); $$ = vsk_ast(INSN_REM, $1->m_str); }
    | TK_ASTERISK TK_IDENTIFIER                         { vsk_targeting($2); $$ = vsk_ast(INSN_LABEL_DEF, $2->m_str); }
    // LET
    | TK_LET lvalue TK_EQUAL expression                 { vsk_targeting($3); $$ = vsk_ast(INSN_LET, { $2, $4 }); }
    |        lvalue TK_EQUAL expression                 { vsk_targeting($2); $$ = vsk_ast(INSN_LET, { $1, $3 }); }
    // PRINT USING / PRINT# USING
    | TK_PRINT_SHARP TK_DIGITS TK_COMMA TK_USING expression TK_SEMICOLON printing_list_2 {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_PRINT_USING, { $2, $5, $7 });
    }
    | print file_number     TK_COMMA TK_USING expression TK_SEMICOLON printing_list_2 {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_PRINT_USING, { $2, $5, $7 });
    }
    | print TK_USING expression TK_SEMICOLON printing_list_2 {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_PRINT_USING, { nullptr, $3, $5 });
    }
    // PRINT / PRINT#
    | TK_PRINT_SHARP TK_DIGITS TK_COMMA printing_list {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_PRINT, { $2, $4 });
    }
    | print file_number TK_COMMA printing_list {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_PRINT, { $2, $4 });
    }
    | print printing_list {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_PRINT, { nullptr, $2 });
    }
    | print {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_PRINT, { nullptr, nullptr });
    }
    // WRITE / WRITE#
    | TK_WRITE_SHARP TK_DIGITS TK_COMMA printing_list {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_WRITE, { $2, $4 });
    }
    | TK_WRITE file_number  TK_COMMA printing_list {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_WRITE, { $2, $4 });
    }
    | TK_WRITE printing_list {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_WRITE, { nullptr, $2 });
    }
    | TK_WRITE {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_WRITE, { nullptr, nullptr });
    }
    // LPRINT USING
    | TK_LPRINT TK_USING expression TK_SEMICOLON parameter_list {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_LPRINT_USING, { $3, $5 });
    }
    // LPRINT
    | TK_LPRINT printing_list {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_LPRINT, { $2 });
    }
    | TK_LPRINT {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_LPRINT, { nullptr });
    }
    // FOR
    | TK_FOR lvalue TK_EQUAL expression TK_TO expression TK_STEP expression {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_FOR, { $2, $4, $6, $8 });
    }
    | TK_FOR lvalue TK_EQUAL expression TK_TO expression {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_FOR, { $2, $4, $6, nullptr });
    }
    // NEXT
    | TK_NEXT lvalue_list {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_NEXT);
        $$->insert($$->end(), $2->begin(), $2->end());
    }
    | TK_NEXT {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_NEXT);
    }
    | TK_OPEN expression TK_FOR TK_IDENTIFIER TK_IDENTIFIER file_number {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_OPEN, { $2, $4, $5, $6 });
    }
    | TK_OPEN expression TK_FOR TK_INPUT TK_IDENTIFIER file_number {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_OPEN, { $2, $4, $5, $6 });
    }
    | TK_OPEN expression TK_FOR TK_IDENTIFIER TK_IDENTIFIER expression {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_OPEN, { $2, $4, $5, $6 });
    }
    | TK_OPEN expression TK_FOR TK_INPUT TK_IDENTIFIER expression {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_OPEN, { $2, $4, $5, $6 });
    }
    | TK_OPEN expression TK_IDENTIFIER file_number {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_OPEN, { $2, nullptr, $3, $4 });
    }
    | TK_OPEN expression TK_IDENTIFIER expression {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_OPEN, { $2, nullptr, $3, $4 });
    }
    | TK_LINE TK_INPUT expression semicolon_or_comma lvalue {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_LINE_INPUT, { $3, $5 });
    }
    | TK_LINE TK_INPUT lvalue {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_LINE_INPUT, { nullptr, $3 });
    }
    | TK_LINE TK_INPUT file_number TK_COMMA lvalue {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_LINE_INPUT_sharp, { $3, $5 });
    }
    | TK_LINE TK_INPUT_sharp TK_DIGITS TK_COMMA lvalue {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_LINE_INPUT_sharp, { $3, $5 });
    }
    | TK_KINPUT lvalue {
        vsk_targeting($1); $$ = vsk_ast(INSN_KINPUT, { $2 });
    }
    | TK_LINE TK_INPUT TK_WAIT expression TK_COMMA expression semicolon_or_comma lvalue {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_LINE_INPUT_WAIT, { $4, $6, $8 });
    }
    | TK_LINE TK_INPUT TK_WAIT expression TK_COMMA lvalue {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_LINE_INPUT_WAIT, { $4, nullptr, $6 });
    }
    | TK_DIM dimension_list                             { vsk_targeting($1); $$ = vsk_ast(INSN_DIM, { $2 }); }
    | TK_DEF TK_SEG TK_EQUAL expression                 { vsk_targeting($1); $$ = vsk_ast(INSN_DEF_SEG, { $4 }); }
    | TK_DEF TK_USR TK_EQUAL expression                 { vsk_targeting($1); $$ = vsk_ast(INSN_DEF_USR, { $2, $4 }); }
    | TK_ON TK_COM go_sub line_number                   { vsk_targeting($1); $$ = vsk_ast(INSN_ON_COM_GOSUB, { $4 }); }
    | TK_ON TK_ERROR go_to line_number                  { vsk_targeting($1); $$ = vsk_ast(INSN_ON_ERROR_GOTO, { $4 }); }
    | TK_ON expression go_to line_numbers               { vsk_targeting($1); $$ = vsk_ast(INSN_ON_EXPR_GOTO, { $2, $4 }); }
    | TK_ON expression go_sub line_numbers              { vsk_targeting($1); $$ = vsk_ast(INSN_ON_EXPR_GOSUB, { $2, $4 }); }
    | TK_ON TK_HELP go_sub line_number                  { vsk_targeting($1); $$ = vsk_ast(INSN_ON_HELP_GOSUB, { $4 }); }
    | TK_ON TK_KEY go_sub  line_numbers                 { vsk_targeting($1); $$ = vsk_ast(INSN_ON_KEY_GOSUB, { $4 }); }
    | TK_ON TK_PEN go_sub  line_number                  { vsk_targeting($1); $$ = vsk_ast(INSN_ON_PEN_GOSUB, { $4 }); }
    | TK_ON TK_PLAY go_sub line_number                  { vsk_targeting($1); $$ = vsk_ast(INSN_ON_PLAY_GOSUB, { $4 }); }
    | TK_ON TK_STOP go_sub line_number                  { vsk_targeting($1); $$ = vsk_ast(INSN_ON_STOP_GOSUB, { $4 }); }
    | TK_ON TK_TIME_dollar TK_EQUAL TK_STRING go_sub line_number {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_ON_TIME_dollar_GOSUB, { $4, $6 });
    }
    | TK_ON TK_MOUSE                                  go_sub line_number {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_ON_MOUSE_GOSUB, { nullptr, $4 });
    }
    | TK_ON TK_MOUSE TK_L_PAREN expression TK_R_PAREN go_sub line_number {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_ON_MOUSE_GOSUB, { $4, $7 });
    }
    | go_sub line_number                                { vsk_targeting($1); $$ = vsk_ast(INSN_GOSUB, { $2 }); }
    | go_to line_number                                 { vsk_targeting($1); $$ = vsk_ast_goto($2); }
    | TK_CMD cmd_name cmd_parameter_list                { vsk_targeting($1); $$ = vsk_ast(INSN_CMD, { $2 }); $$->insert($$->end(), $3->begin(), $3->end()); }
    | TK_CMD cmd_name                                   { vsk_targeting($1); $$ = vsk_ast(INSN_CMD, { $2 }); }
    | lead_statement_1 TK_COMMA trailing_parameter_list { $$ = $1; $$->insert($$->end(), $3->begin(), $3->end()); }
    | lead_statement_1                                  { $$ = $1; }
    | lead_statement_0 trailing_parameter_list          { $$ = $1; $$->insert($$->end(), $2->begin(), $2->end()); }
    | lead_statement_0                                  { $$ = $1; }
    | TK_INPUT TK_STRING TK_SEMICOLON lvalue_list       { vsk_targeting($1); $$ = vsk_ast(INSN_INPUT_semicolon, { $2, $4 }); }
    | TK_INPUT TK_STRING TK_COMMA lvalue_list           { vsk_targeting($1); $$ = vsk_ast(INSN_INPUT, { $2, $4 }); }
    | TK_INPUT                    lvalue_list           { vsk_targeting($1); $$ = vsk_ast(INSN_INPUT, { nullptr, $2 }); }
    | TK_INPUT TK_WAIT expression TK_COMMA TK_STRING TK_SEMICOLON lvalue_list {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_INPUT_WAIT_semicolon, { $3, $5, $7 });
    }
    | TK_INPUT TK_WAIT expression                    TK_SEMICOLON lvalue_list {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_INPUT_WAIT_semicolon, { $3, nullptr, $5 });
    }
    | TK_INPUT TK_WAIT expression TK_COMMA TK_STRING TK_COMMA lvalue_list {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_INPUT_WAIT, { $3, $5, $7 });
    }
    | TK_INPUT TK_WAIT expression TK_COMMA                    lvalue_list {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_INPUT_WAIT, { $3, nullptr, $5 });
    }
    | TK_LSET lvalue TK_EQUAL expression                { vsk_targeting($1); $$ = vsk_ast(INSN_LSET, { $2, $4 }); }
    | TK_RSET lvalue TK_EQUAL expression                { vsk_targeting($1); $$ = vsk_ast(INSN_RSET, { $2, $4 }); }
    | TK_TIME_dollar TK_EQUAL expression                { vsk_targeting($1); $$ = vsk_ast(INSN_TIME_dollar, { $3 }); }
    | TK_DATE_dollar TK_EQUAL expression                { vsk_targeting($1); $$ = vsk_ast(INSN_DATE_dollar, { $3 }); }
    | TK_DELETE line_range                              { vsk_targeting($1); $$ = vsk_ast(INSN_DELETE, { $2 }); }
    | TK_RESUME TK_NEXT                                 { vsk_targeting($1); $$ = vsk_ast(INSN_RESUME, { $2 }); }
    | TK_RESUME line_number                             { vsk_targeting($1); $$ = vsk_ast(INSN_RESUME, { $2 }); }
    | TK_RESUME                                         { vsk_targeting($1); $$ = vsk_ast(INSN_RESUME);}
    // GET#
    | TK_GET file_number     TK_COMMA expression        { vsk_targeting($1); $$ = vsk_ast(INSN_GET_sharp, { $2, $4 }); }
    | TK_GET file_number                                { vsk_targeting($1); $$ = vsk_ast(INSN_GET_sharp, { $2, nullptr }); }
    | TK_GET_sharp TK_DIGITS TK_COMMA expression        { vsk_targeting($1); $$ = vsk_ast(INSN_GET_sharp, { $2, $4 }); }
    | TK_GET_sharp TK_DIGITS                            { vsk_targeting($1); $$ = vsk_ast(INSN_GET_sharp, { $2, nullptr }); }
    // PUT#
    | TK_PUT file_number     TK_COMMA expression        { vsk_targeting($1); $$ = vsk_ast(INSN_PUT_sharp, { $2, $4 });}
    | TK_PUT file_number                                { vsk_targeting($1); $$ = vsk_ast(INSN_PUT_sharp, { $2, nullptr });}
    | TK_PUT_sharp TK_DIGITS TK_COMMA expression        { vsk_targeting($1); $$ = vsk_ast(INSN_PUT_sharp, { $2, $4 });}
    | TK_PUT_sharp TK_DIGITS                            { vsk_targeting($1); $$ = vsk_ast(INSN_PUT_sharp, { $2, nullptr });}
    // GET@(0,0)-STEP(100,100)
    | get_at TK_L_PAREN expression TK_COMMA expression TK_R_PAREN TK_MINUS TK_STEP TK_L_PAREN expression TK_COMMA expression TK_R_PAREN TK_COMMA lvalue {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_GET_at_STEP, { $3, $5, $10, $12, $15 });
    }
    // GET@(0,0)-(100,100)
    | get_at TK_L_PAREN expression TK_COMMA expression TK_R_PAREN TK_MINUS         TK_L_PAREN expression TK_COMMA expression TK_R_PAREN TK_COMMA lvalue {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_GET_at, { $3, $5, $9, $11, $14 });
    }
    | put_at TK_L_PAREN expression TK_COMMA expression TK_R_PAREN TK_COMMA TK_KANJI TK_L_PAREN expression TK_R_PAREN TK_COMMA put_operation TK_COMMA expression TK_COMMA expression {
        // PUT@(50,50),KANJI(...),OP,color1,color2
        vsk_targeting($1);
        $$ = vsk_ast(INSN_PUT_at_KANJI, { $3, $5, $10, $13, $15, $17 });
    }
    | put_at TK_L_PAREN expression TK_COMMA expression TK_R_PAREN TK_COMMA TK_KANJI TK_L_PAREN expression TK_R_PAREN TK_COMMA TK_COMMA expression TK_COMMA expression {
        // PUT@(50,50),KANJI(...),,color1,color2
        vsk_targeting($1);
        $$ = vsk_ast(INSN_PUT_at_KANJI, { $3, $5, $10, $13, $14, $16 });
    }
    | put_at TK_L_PAREN expression TK_COMMA expression TK_R_PAREN TK_COMMA TK_KANJI TK_L_PAREN expression TK_R_PAREN TK_COMMA put_operation {
        // PUT@(50,50),KANJI(...),OP
        vsk_targeting($1);
        $$ = vsk_ast(INSN_PUT_at_KANJI, { $3, $5, $10, $13 });
    }
    | put_at TK_L_PAREN expression TK_COMMA expression TK_R_PAREN TK_COMMA TK_KANJI TK_L_PAREN expression TK_R_PAREN {
        // PUT@(50,50),KANJI(...)
        vsk_targeting($1);
        $$ = vsk_ast(INSN_PUT_at_KANJI, { $3, $5, $10 });
    }
    | put_at TK_L_PAREN expression TK_COMMA expression TK_R_PAREN TK_COMMA lvalue TK_COMMA put_operation TK_COMMA expression TK_COMMA expression {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_PUT_at, { $3, $5, $8, $10, $12, $14 });
    }
    | put_at TK_L_PAREN expression TK_COMMA expression TK_R_PAREN TK_COMMA lvalue TK_COMMA put_operation {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_PUT_at, { $3, $5, $8, $10 });
    }
    | put_at TK_L_PAREN expression TK_COMMA expression TK_R_PAREN TK_COMMA lvalue {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_PUT_at, { $3, $5, $8 });
    }
    // CHAIN
    | TK_CHAIN TK_MERGE expression TK_COMMA line_number TK_COMMA TK_IDENTIFIER TK_COMMA TK_DELETE line_range {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_CHAIN_MERGE_ALL_DELETE, { $3, $5, $10 });
    }
    | TK_CHAIN TK_MERGE expression TK_COMMA line_number TK_COMMA TK_IDENTIFIER {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_CHAIN_MERGE_ALL, { $3, $5 });
    }
    | TK_CHAIN TK_MERGE expression TK_COMMA line_number TK_COMMA TK_DELETE line_range {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_CHAIN_MERGE_DELETE, { $3, $5 });
    }
    | TK_CHAIN TK_MERGE expression TK_COMMA line_number {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_CHAIN_MERGE, { $3, $5 });
    }
    | TK_CHAIN TK_MERGE expression {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_CHAIN_MERGE, { $3 });
    }
    | TK_CHAIN expression TK_COMMA TK_IDENTIFIER {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_CHAIN, { $2, nullptr, $4 });
    }
    | TK_CHAIN expression TK_COMMA line_number TK_COMMA TK_IDENTIFIER {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_CHAIN, { $2, $4, $6 });
    }
    | TK_CHAIN expression TK_COMMA line_number {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_CHAIN, { $2, $4 });
    }
    | TK_CHAIN expression {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_CHAIN, { $2 });
    }
    | TK_DEF TK_FN TK_EQUAL expression {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_DEF_FN, { $2, nullptr, $4 });
    }
    | TK_DEF TK_FN TK_L_PAREN TK_R_PAREN TK_EQUAL expression {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_DEF_FN, { $2, nullptr, $6 });
    }
    | TK_DEF TK_FN TK_L_PAREN lvalue_list TK_R_PAREN TK_EQUAL expression {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_DEF_FN, { $2, $4, $7 });
    }
    | TK_COM TK_OFF                                     { vsk_targeting($1); $$ = vsk_ast(INSN_COM_OFF); }
    | TK_COM TK_ON                                      { vsk_targeting($1); $$ = vsk_ast(INSN_COM_ON); }
    | TK_COM TK_STOP                                    { vsk_targeting($1); $$ = vsk_ast(INSN_COM_STOP); }
    | TK_MOUSE TK_L_PAREN expression TK_R_PAREN TK_OFF  { vsk_targeting($1); $$ = vsk_ast(INSN_MOUSE_OFF, { $3 }); }
    | TK_MOUSE TK_L_PAREN expression TK_R_PAREN TK_ON   { vsk_targeting($1); $$ = vsk_ast(INSN_MOUSE_ON, { $3 }); }
    | TK_MOUSE TK_L_PAREN expression TK_R_PAREN TK_STOP { vsk_targeting($1); $$ = vsk_ast(INSN_MOUSE_STOP, { $3 }); }
    | TK_MOUSE                                  TK_OFF  { vsk_targeting($1); $$ = vsk_ast(INSN_MOUSE_OFF, { nullptr }); }
    | TK_MOUSE                                  TK_ON   { vsk_targeting($1); $$ = vsk_ast(INSN_MOUSE_ON, { nullptr }); }
    | TK_MOUSE                                  TK_STOP { vsk_targeting($1); $$ = vsk_ast(INSN_MOUSE_STOP, { nullptr }); }
    | TK_PEN TK_OFF                                     { vsk_targeting($1); $$ = vsk_ast(INSN_PEN_OFF); }
    | TK_PEN TK_ON                                      { vsk_targeting($1); $$ = vsk_ast(INSN_PEN_ON); }
    | TK_PEN TK_STOP                                    { vsk_targeting($1); $$ = vsk_ast(INSN_PEN_STOP); }
    | TK_PLAY TK_OFF                                    { vsk_targeting($1); $$ = vsk_ast(INSN_PLAY_OFF); }
    | TK_PLAY TK_ON                                     { vsk_targeting($1); $$ = vsk_ast(INSN_PLAY_ON); }
    | TK_PLAY TK_STOP                                   { vsk_targeting($1); $$ = vsk_ast(INSN_PLAY_STOP); }
    | TK_HELP TK_OFF                                    { vsk_targeting($1); $$ = vsk_ast(INSN_HELP_OFF); }
    | TK_HELP TK_ON                                     { vsk_targeting($1); $$ = vsk_ast(INSN_HELP_ON); }
    | TK_HELP TK_STOP                                   { vsk_targeting($1); $$ = vsk_ast(INSN_HELP_STOP); }
    | TK_TIME_dollar TK_OFF                             { vsk_targeting($1); $$ = vsk_ast(INSN_TIME_dollar_OFF); }
    | TK_TIME_dollar TK_ON                              { vsk_targeting($1); $$ = vsk_ast(INSN_TIME_dollar_ON); }
    | TK_TIME_dollar TK_STOP                            { vsk_targeting($1); $$ = vsk_ast(INSN_TIME_dollar_STOP); }
    | TK_STOP TK_OFF                                    { vsk_targeting($1); $$ = vsk_ast(INSN_STOP_OFF); }
    | TK_STOP TK_ON                                     { vsk_targeting($1); $$ = vsk_ast(INSN_STOP_ON); }
    | TK_STOP TK_STOP                                   { vsk_targeting($1); $$ = vsk_ast(INSN_STOP_STOP); }
    | TK_POINT TK_STEP TK_L_PAREN expression TK_COMMA expression TK_R_PAREN {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_POINT_STEP, { $4, $6 });
    }
    | TK_POINT         TK_L_PAREN expression TK_COMMA expression TK_R_PAREN {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_POINT, { $3, $5 });
    }
    | TK_EDIT line_number_or_dot {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_EDIT, { $2 });
    }
    | TK_TROFF                                          { vsk_targeting($1); $$ = vsk_ast(INSN_TROFF); }
    | TK_TRON                                           { vsk_targeting($1); $$ = vsk_ast(INSN_TRON); }
    | TK_LIST line_range                                { vsk_targeting($1); $$ = vsk_ast(INSN_LIST, { $2 }); }
    | TK_LIST                                           { vsk_targeting($1); $$ = vsk_ast(INSN_LIST); }
    | TK_LLIST line_range                               { vsk_targeting($1); $$ = vsk_ast(INSN_LLIST, { $2 }); }
    | TK_LLIST                                          { vsk_targeting($1); $$ = vsk_ast(INSN_LLIST); }
    | TK_CLOSE_SHARP expression TK_COMMA file_numbers_or_expressions {
        vsk_targeting($1);
        $4->insert($4->begin(), $2);
        $$ = vsk_ast(INSN_CLOSE, { $4 });
    }
    | TK_CLOSE_SHARP expression {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_CLOSE, { vsk_ast(INSN_FILE_NUMBERS, { $2 }) });
    }
    | TK_CLOSE file_numbers_or_expressions              { vsk_targeting($1); $$ = vsk_ast(INSN_CLOSE, { $2 }); }
    | TK_CLOSE                                          { vsk_targeting($1); $$ = vsk_ast(INSN_CLOSE, { nullptr }); }
    | TK_RUN line_number                                { vsk_targeting($1); $$ = vsk_ast(INSN_RUN, { $2, nullptr, nullptr }); }
    | TK_RUN TK_STRING TK_COMMA TK_IDENTIFIER           { vsk_targeting($1); $$ = vsk_ast(INSN_RUN, { nullptr, $2, $4 }); }
    | TK_RUN TK_STRING                                  { vsk_targeting($1); $$ = vsk_ast(INSN_RUN, { nullptr, $2, nullptr }); }
    | TK_RUN                                            { vsk_targeting($1); $$ = vsk_ast(INSN_RUN, { nullptr, nullptr, nullptr }); }
    | TK_LOAD expression TK_COMMA TK_IDENTIFIER         { vsk_targeting($1); $$ = vsk_ast(INSN_LOAD, { $2, $4 }); }
    | TK_LOAD expression                                { vsk_targeting($1); $$ = vsk_ast(INSN_LOAD, { $2, nullptr }); }
    | TK_RESTORE line_number                            { vsk_targeting($1); $$ = vsk_ast(INSN_RESTORE, { $2 }); }
    | TK_RESTORE                                        { vsk_targeting($1); $$ = vsk_ast(INSN_RESTORE); }
    | TK_ERASE identifier_list                          { vsk_targeting($1); $$ = vsk_ast(INSN_ERASE, { $2 }); }
    | TK_SWAP lvalue TK_COMMA lvalue                    { vsk_targeting($1); $$ = vsk_ast(INSN_SWAP, { $2, $4 }); }
    | TK_STOP                                           { vsk_targeting($1); $$ = vsk_ast(INSN_STOP); }
    | TK_FIELD expression        TK_COMMA field_items   { vsk_targeting($1); $$ = vsk_ast(INSN_FIELD, { $2, $4 }); }
    | TK_FIELD file_number       TK_COMMA field_items   { vsk_targeting($1); $$ = vsk_ast(INSN_FIELD, { $2, $4 }); }
    | TK_FIELD_sharp expression  TK_COMMA field_items   { vsk_targeting($1); $$ = vsk_ast(INSN_FIELD, { $2, $4 }); }
    | TK_RETURN line_number                             { vsk_targeting($1); $$ = vsk_ast(INSN_RETURN, { $2 }); }
    | TK_RETURN                                         { vsk_targeting($1); $$ = vsk_ast(INSN_RETURN); }
    | TK_NAME expression TK_IDENTIFIER expression       { vsk_targeting($1); $$ = vsk_ast(INSN_NAME, { $2, $3, $4 }); }
    | TK_PLAY file_number TK_COMMA trailing_parameter_list         { vsk_targeting($1); $$ = vsk_ast(INSN_PLAY, { $2, $4 }); }
    | TK_PLAY                      trailing_parameter_list         { vsk_targeting($1); $$ = vsk_ast(INSN_PLAY, { nullptr, $2 }); }
    | TK_AUTO line_number TK_COMMA expression           { vsk_targeting($1); $$ = vsk_ast(INSN_AUTO, { $2, $4 }); }
    | TK_AUTO             TK_COMMA expression           { vsk_targeting($1); $$ = vsk_ast(INSN_AUTO, { nullptr, $3 }); }
    | TK_AUTO line_number                               { vsk_targeting($1); $$ = vsk_ast(INSN_AUTO, { $2, nullptr }); }
    | TK_AUTO                                           { vsk_targeting($1); $$ = vsk_ast(INSN_AUTO, { nullptr, nullptr }); }
    | TK_WIDTH_sharp TK_DIGITS   TK_COMMA expression    { vsk_targeting($1); $$ = vsk_ast(INSN_WIDTH_sharp, { $2, $4 }); }
    | TK_WIDTH       file_number TK_COMMA expression    { vsk_targeting($1); $$ = vsk_ast(INSN_WIDTH_sharp, { $2, $4 }); }
    | dirty_8bit_sequence                               { vsk_targeting($1); $$ = $1; }
    ;

dimension_list
    : lvalue                                            { vsk_targeting($1); $$ = vsk_ast(INSN_DIM_LIST, { $1 }); }
    | dimension_list TK_COMMA lvalue                    { $$ = $1; $$->push_back($3); }
    ;

identifier_list
    : TK_IDENTIFIER                                     { vsk_targeting($1); $$ = vsk_ast(INSN_IDENT_LIST, { $1 }); }
    | identifier_list TK_COMMA TK_IDENTIFIER            { $$ = $1; $$->push_back($3); }
    ;

print
    : TK_PRINT              { $$ = $1; }
    | TK_QUESTION           { $$ = $1; }
    ;

printing_list
    : printing_expression                               { vsk_targeting($1); $$ = vsk_ast(INSN_PRINTING, { $1 }); }
    | printing_list printing_expression                 { $$ = $1; $$->push_back($2); }
    ;

printing_list_2
    : expression                                        { vsk_targeting($1); $$ = vsk_ast(INSN_PRINTING, { $1 }); }
    | printing_list_2 expression                        { vsk_targeting($2); $$ = $1; $$->push_back($2); }
    | printing_list_2 TK_COMMA                          { vsk_targeting($2); $$ = $1; $$->push_back(vsk_ast(INSN_COMMA)); }
    | printing_list_2 TK_SEMICOLON                      { vsk_targeting($2); $$ = $1; $$->push_back(vsk_ast(INSN_SEMICOLON)); }
    ;

go_to
    : TK_GOTO               { $$ = $1; }
    | TK_GO TK_TO           { $$ = $2; }
    ;

go_sub
    : TK_GOSUB              { $$ = $1; }
    | TK_GO TK_SUB          { $$ = $2; }
    ;

printing_expression
    : expression                                { $$ = $1; }
    | TK_SPC TK_L_PAREN expression TK_R_PAREN   { vsk_targeting($1); $$ = vsk_ast(INSN_SPC, { $3 });}
    | TK_TAB TK_L_PAREN expression TK_R_PAREN   { vsk_targeting($1); $$ = vsk_ast(INSN_TAB, { $3 });}
    | TK_COMMA                                  { vsk_targeting($1); $$ = vsk_ast(INSN_COMMA); }
    | TK_SEMICOLON                              { vsk_targeting($1); $$ = vsk_ast(INSN_SEMICOLON); }
    ;

semicolon_or_comma
    : TK_SEMICOLON                              { $$ = $1; }
    | TK_COMMA                                  { $$ = $1; }
    ;

lead_statement_0
    : TK_BEEP                                           { vsk_targeting($1); $$ = vsk_ast(INSN_BEEP); }
    | TK_BLOAD                                          { vsk_targeting($1); $$ = vsk_ast(INSN_BLOAD); }
    | TK_BSAVE                                          { vsk_targeting($1); $$ = vsk_ast(INSN_BSAVE); }
    | TK_CALL                                           { vsk_targeting($1); $$ = vsk_ast(INSN_CALL); }
    | TK_CHILD                                          { vsk_targeting($1); $$ = vsk_ast(INSN_CHILD); }
    | TK_CLEAR                                          { vsk_targeting($1); $$ = vsk_ast(INSN_CLEAR); }
    | TK_CLS                                            { vsk_targeting($1); $$ = vsk_ast(INSN_CLS); }
    | TK_COLOR                                          { vsk_targeting($1); $$ = vsk_ast(INSN_COLOR); }
    | TK_COMMON                                         { vsk_targeting($1); $$ = vsk_ast(INSN_COMMON); }
    | TK_CONSOLE                                        { vsk_targeting($1); $$ = vsk_ast(INSN_CONSOLE); }
    | TK_CONT                                           { vsk_targeting($1); $$ = vsk_ast(INSN_CONT); }
    | TK_COPY                                           { vsk_targeting($1); $$ = vsk_ast(INSN_COPY); }
    | TK_DATA                                           { vsk_targeting($1); $$ = vsk_ast(INSN_DATA); }
    | TK_DEFDBL                                         { vsk_targeting($1); $$ = vsk_ast(INSN_DEFDBL); }
    | TK_DEFINT                                         { vsk_targeting($1); $$ = vsk_ast(INSN_DEFINT); }
    | TK_DEFSNG                                         { vsk_targeting($1); $$ = vsk_ast(INSN_DEFSNG); }
    | TK_DEFSTR                                         { vsk_targeting($1); $$ = vsk_ast(INSN_DEFSTR); }
    | TK_DRAW                                           { vsk_targeting($1); $$ = vsk_ast(INSN_DRAW); }
    | TK_DSKO_dollar                                    { vsk_targeting($1); $$ = vsk_ast(INSN_DSKO_dollar); }
    | TK_END                                            { vsk_targeting($1); $$ = vsk_ast(INSN_END); }
    | TK_ERROR                                          { vsk_targeting($1); $$ = vsk_ast(INSN_ERROR); }
    | TK_FILES                                          { vsk_targeting($1); $$ = vsk_ast(INSN_FILES); }
    | TK_KEY                                            { vsk_targeting($1); $$ = vsk_ast(INSN_KEY); }
    | TK_KEY TK_LIST                                    { vsk_targeting($1); $$ = vsk_ast(INSN_KEY_LIST); }
    | TK_KEY TK_L_PAREN expression TK_R_PAREN TK_OFF    { vsk_targeting($1); $$ = vsk_ast(INSN_KEY_OFF, { $3 }); }
    | TK_KEY TK_L_PAREN expression TK_R_PAREN TK_ON     { vsk_targeting($1); $$ = vsk_ast(INSN_KEY_ON, { $3 }); }
    | TK_KEY TK_L_PAREN expression TK_R_PAREN TK_STOP   { vsk_targeting($1); $$ = vsk_ast(INSN_KEY_STOP, { $3 }); }
    | TK_KEY TK_OFF                                     { vsk_targeting($1); $$ = vsk_ast(INSN_KEY_OFF); }
    | TK_KEY TK_ON                                      { vsk_targeting($1); $$ = vsk_ast(INSN_KEY_ON); }
    | TK_KEY TK_STOP                                    { vsk_targeting($1); $$ = vsk_ast(INSN_KEY_STOP); }
    | TK_KILL                                           { vsk_targeting($1); $$ = vsk_ast(INSN_KILL); }
    | TK_KPLOAD                                         { vsk_targeting($1); $$ = vsk_ast(INSN_KPLOAD); }
    | TK_LFILES                                         { vsk_targeting($1); $$ = vsk_ast(INSN_LFILES); }
    | TK_LOAD TK_QUESTION                               { vsk_targeting($1); $$ = vsk_ast(INSN_LOAD_question); }
    | TK_LOCATE                                         { vsk_targeting($1); $$ = vsk_ast(INSN_LOCATE); }
    | TK_MERGE                                          { vsk_targeting($1); $$ = vsk_ast(INSN_MERGE); }
    | TK_MON                                            { vsk_targeting($1); $$ = vsk_ast(INSN_MON); }
    | TK_MOTOR                                          { vsk_targeting($1); $$ = vsk_ast(INSN_MOTOR); }
    | TK_MOUSE                                          { vsk_targeting($1); $$ = vsk_ast(INSN_MOUSE_stmt); }
    | TK_NEW                                            { vsk_targeting($1); $$ = vsk_ast(INSN_NEW); }
    | TK_NEW TK_CMD                                     { vsk_targeting($1); $$ = vsk_ast(INSN_NEW_CMD); }
    | TK_NEW TK_ON                                      { vsk_targeting($1); $$ = vsk_ast(INSN_NEW_ON); }
    | TK_OPTION TK_IDENTIFIER                           { vsk_targeting($1); $$ = vsk_ast(INSN_OPTION_IDENT, { $2 }); }
    | TK_OUT                                            { vsk_targeting($1); $$ = vsk_ast(INSN_OUT); }
    | TK_PLAY TK_ALLOC                                  { vsk_targeting($1); $$ = vsk_ast(INSN_PLAY_ALLOC); }
    | TK_PLAY                                           { vsk_targeting($1); $$ = vsk_ast(INSN_PLAY); }
    | TK_POKE                                           { vsk_targeting($1); $$ = vsk_ast(INSN_POKE); }
    | TK_RANDOMIZE                                      { vsk_targeting($1); $$ = vsk_ast(INSN_RANDOMIZE); }
    | TK_READ                                           { vsk_targeting($1); $$ = vsk_ast(INSN_READ); }
    | TK_RENUM                                          { vsk_targeting($1); $$ = vsk_ast(INSN_RENUM); }
    | TK_ROLL                                           { vsk_targeting($1); $$ = vsk_ast(INSN_ROLL); }
    | TK_SAVE                                           { vsk_targeting($1); $$ = vsk_ast(INSN_SAVE); }
    | TK_SCREEN                                         { vsk_targeting($1); $$ = vsk_ast(INSN_SCREEN); }
    | TK_SET                                            { vsk_targeting($1); $$ = vsk_ast(INSN_SET); }
    | TK_SET_SHARP                                      { vsk_targeting($1); $$ = vsk_ast(INSN_SET); }
    | TK_SYSTEM                                         { vsk_targeting($1); $$ = vsk_ast(INSN_SYSTEM); }
    | TK_TERM                                           { vsk_targeting($1); $$ = vsk_ast(INSN_TERM); }
    | TK_WAIT                                           { vsk_targeting($1); $$ = vsk_ast(INSN_WAIT); }
    | TK_WEND                                           { vsk_targeting($1); $$ = vsk_ast(INSN_WEND); }
    | TK_WHILE                                          { vsk_targeting($1); $$ = vsk_ast(INSN_WHILE); }
    | TK_WIDTH                                          { vsk_targeting($1); $$ = vsk_ast(INSN_WIDTH); }
    | TK_CHDIR                                          { vsk_targeting($1); $$ = vsk_ast(INSN_CHDIR); }
    | TK_MKDIR                                          { vsk_targeting($1); $$ = vsk_ast(INSN_MKDIR); }
    | TK_RMDIR                                          { vsk_targeting($1); $$ = vsk_ast(INSN_RMDIR); }
    | TK_WIDTH TK_LPRINT                                { vsk_targeting($1); $$ = vsk_ast(INSN_WIDTH_LPRINT); }
    | TK_MID_dollar TK_L_PAREN lvalue TK_COMMA expression TK_COMMA expression TK_R_PAREN TK_EQUAL expression {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_MID_dollar_stmt, { $3, $5, $7, $10 });
    }
    | TK_MID_dollar TK_L_PAREN TK_IDENTIFIER TK_COMMA expression TK_R_PAREN TK_EQUAL expression {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_MID_dollar_stmt, { $3, $5, nullptr, $8 });
    }
    ;

lead_statement_1
    : TK_INPUT_sharp TK_DIGITS                          { vsk_targeting($1); $$ = vsk_ast(INSN_INPUT_sharp, { $2 });}
    | TK_INPUT file_number                              { vsk_targeting($1); $$ = vsk_ast(INSN_INPUT_sharp, { $2 });}
    | TK_LINE TK_MINUS TK_STEP TK_L_PAREN expression TK_COMMA expression TK_R_PAREN {
        // LINE -STEP(100,100) likely
        vsk_targeting($1);
        $$ = vsk_ast(INSN_LINE1, { nullptr, nullptr, $5, $7 });
    }
    | TK_LINE TK_MINUS TK_L_PAREN expression TK_COMMA expression TK_R_PAREN {
        // LINE -(100,100) likely
        vsk_targeting($1);
        $$ = vsk_ast(INSN_LINE0, { nullptr, nullptr, $4, $6 });
    }
    | TK_LINE TK_STEP TK_L_PAREN expression TK_COMMA expression TK_R_PAREN TK_MINUS TK_STEP TK_L_PAREN expression TK_COMMA expression TK_R_PAREN {
        // LINE STEP(0,0)-STEP(100,100) likely
        vsk_targeting($1);
        $$ = vsk_ast(INSN_LINE3, { $4, $6, $11, $13 });
    }
    | TK_LINE TK_STEP TK_L_PAREN expression TK_COMMA expression TK_R_PAREN TK_MINUS TK_L_PAREN expression TK_COMMA expression TK_R_PAREN {
        // LINE STEP(0,0)-(100,100) likely
        vsk_targeting($1);
        $$ = vsk_ast(INSN_LINE2, { $4, $6, $10, $12 });
    }
    | TK_LINE TK_L_PAREN expression TK_COMMA expression TK_R_PAREN TK_MINUS TK_STEP TK_L_PAREN expression TK_COMMA expression TK_R_PAREN {
        // LINE(0,0)-STEP(100,100) likely
        vsk_targeting($1);
        $$ = vsk_ast(INSN_LINE1, { $3, $5, $10, $12 });
    }
    | TK_LINE TK_L_PAREN expression TK_COMMA expression TK_R_PAREN TK_MINUS TK_L_PAREN expression TK_COMMA expression TK_R_PAREN {
        // LINE(0,0)-(100,100) likely
        vsk_targeting($1);
        $$ = vsk_ast(INSN_LINE0, { $3, $5, $9, $11 });
    }
    | TK_CIRCLE TK_L_PAREN expression TK_COMMA expression TK_R_PAREN TK_COMMA expression {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_CIRCLE, { $3, $5, $8 });
    }
    | TK_CIRCLE TK_STEP TK_L_PAREN expression TK_COMMA expression TK_R_PAREN TK_COMMA expression {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_CIRCLE_STEP, { $4, $6, $9 });
    }
    | TK_PSET         TK_L_PAREN expression TK_COMMA expression TK_R_PAREN {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_PSET, { $3, $5 });
    }
    | TK_PSET TK_STEP TK_L_PAREN expression TK_COMMA expression TK_R_PAREN {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_PSET_STEP, { $4, $6 });
    }
    | TK_PRESET TK_STEP TK_L_PAREN expression TK_COMMA expression TK_R_PAREN {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_PRESET_STEP, { $4, $6 });
    }
    | TK_PRESET         TK_L_PAREN expression TK_COMMA expression TK_R_PAREN {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_PRESET, { $3, $5 });
    }
    | TK_PAINT TK_STEP TK_L_PAREN expression TK_COMMA expression TK_R_PAREN {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_PAINT_STEP, { $4, $6 });
    }
    | TK_PAINT         TK_L_PAREN expression TK_COMMA expression TK_R_PAREN {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_PAINT, { $3, $5 });
    }
    | TK_COLOR TK_EQUAL TK_L_PAREN expression TK_COMMA expression TK_R_PAREN {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_COLOR_equal, { $4, $6 });
    }
    | TK_COLOR_at TK_L_PAREN expression TK_COMMA expression TK_R_PAREN TK_MINUS
                  TK_L_PAREN expression TK_COMMA expression TK_R_PAREN
    {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_COLOR_at, { $3, $5, $9, $11 });
    }
    | TK_VIEW TK_L_PAREN expression TK_COMMA expression TK_R_PAREN TK_MINUS TK_L_PAREN expression TK_COMMA expression TK_R_PAREN {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_VIEW_stmt, { $3, $5, $9, $11 });
    }
    | TK_WINDOW TK_L_PAREN expression TK_COMMA expression TK_R_PAREN TK_MINUS TK_L_PAREN expression TK_COMMA expression TK_R_PAREN {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_WINDOW_stmt, { $3, $5, $9, $11 });
    }
    ;

matched_if_statement
    : TK_IF expression TK_THEN line_number       TK_ELSE line_number       {
        vsk_targeting($4);
        auto go_to_0 = vsk_ast_goto($4);
        vsk_targeting($6);
        auto go_to_1 = vsk_ast_goto($6);
        vsk_targeting($1);
        $$ = vsk_ast(INSN_IF, { $2, go_to_0, go_to_1 });
    }
    | TK_IF expression go_to   line_number       TK_ELSE line_number       {
        vsk_targeting($4);
        auto go_to_0 = vsk_ast_goto($4);
        vsk_targeting($6);
        auto go_to_1 = vsk_ast_goto($6);
        vsk_targeting($1);
        $$ = vsk_ast(INSN_IF, { $2, go_to_0, go_to_1 });
    }
    | TK_IF expression TK_THEN line_number       TK_ELSE matched_statement {
        vsk_targeting($4);
        auto go_to = vsk_ast_goto($4);
        vsk_targeting($1);
        $$ = vsk_ast(INSN_IF, { $2, go_to, $6 });
    }
    | TK_IF expression TK_THEN matched_statement TK_ELSE line_number       {
        vsk_targeting($6);
        auto go_to = vsk_ast_goto($6);
        vsk_targeting($1);
        $$ = vsk_ast(INSN_IF, { $2, $4, go_to });
    }
    | TK_IF expression TK_THEN                   TK_ELSE line_number       {
        vsk_targeting($5);
        auto go_to = vsk_ast_goto($5);
        vsk_targeting($1);
        $$ = vsk_ast(INSN_IF, { $2, vsk_ast(INSN_MULTI), go_to });
    }
    | TK_IF expression TK_THEN                   TK_ELSE matched_statement {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_IF, { $2, vsk_ast(INSN_MULTI), $5 });
    }
    | TK_IF expression go_to   line_number       TK_ELSE matched_statement {
        vsk_targeting($4);
        auto go_to = vsk_ast_goto($4);
        vsk_targeting($1);
        $$ = vsk_ast(INSN_IF, { $2, go_to, $6 });
    }
    | TK_IF expression TK_THEN matched_statement TK_ELSE matched_statement {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_IF, { $2, $4, $6 });
    }
    | TK_IF expression TK_THEN matched_statement TK_ELSE                   {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_IF, { $2, $4, vsk_ast(INSN_MULTI) });
    }
    | TK_IF expression TK_THEN                   TK_ELSE                   {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_IF, { $2, vsk_ast(INSN_MULTI), vsk_ast(INSN_MULTI) });
    }
    ;

unmatched_if_statement
    : TK_IF expression TK_THEN line_number       TK_ELSE unmatched_statement {
        vsk_targeting($4);
        auto go_to = vsk_ast_goto($4);
        vsk_targeting($1);
        $$ = vsk_ast(INSN_IF, { $2, go_to, $6 });
    }
    | TK_IF expression go_to   line_number       TK_ELSE unmatched_statement {
        vsk_targeting($4);
        auto go_to = vsk_ast_goto($4);
        vsk_targeting($1);
        $$ = vsk_ast(INSN_IF, { $2, go_to, $6 });
    }
    | TK_IF expression TK_THEN matched_statement TK_ELSE unmatched_statement {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_IF, { $2, $4, $6 });
    }
    | TK_IF expression TK_THEN                   TK_ELSE unmatched_statement {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_IF, { $2, vsk_ast(INSN_MULTI), $5 });
    }
    | TK_IF expression TK_THEN line_number                                   {
        vsk_targeting($4);
        auto go_to = vsk_ast_goto($4);
        vsk_targeting($1);
        $$ = vsk_ast(INSN_IF, { $2, go_to, nullptr });
    }
    | TK_IF expression TK_THEN statement                                     {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_IF, { $2, $4, nullptr });
    }
    | TK_IF expression TK_THEN                                               {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_IF, { $2, vsk_ast(INSN_MULTI), nullptr });
    }
    | TK_IF expression go_to line_number                                     {
        vsk_targeting($4);
        auto go_to = vsk_ast_goto($4);
        vsk_targeting($1);
        $$ = vsk_ast(INSN_IF, { $2, go_to, nullptr });
    }
    ;

matched_statement
    : matched_statement TK_COLON matched_statement {
        vsk_targeting($1);
        $$ = vsk_ast_multi($1, $3);
    }
    | TK_COLON matched_statement {
        vsk_targeting($1); $$ = $2;
    }
    | matched_if_statement {
        $$ = $1;
    }
    | primary_statement {
        $$ = $1;
    }
    ;

unmatched_statement
    : matched_statement TK_COLON unmatched_statement {
        $$ = vsk_ast_multi($1, $3);
    }
    | TK_COLON unmatched_statement {
        vsk_targeting($1); $$ = $2;
    }
    | unmatched_if_statement {
        $$ = $1;
    }
    ;

statement
    : matched_statement    { $$ = $1; }
    | unmatched_statement  { $$ = $1; }
    | TK_COLON             { vsk_targeting($1); $$ = vsk_ast(INSN_MULTI); }
    ;

line_number_or_dot
    : line_number               { $$ = $1; }
    | TK_PERIOD                 { vsk_targeting($1); $$ = $$ = vsk_ast(INSN_LABEL, { vsk_ast(INSN_PERIOD) }); }
    ;

line_numbers
    : line_number {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_LINE_NUMBERS, { $1 });
    }
    | line_numbers commas line_number {
        $$ = $1;
        $$->insert($1->end(), $2->begin(), $2->end());
        $$->push_back($3);
    }
    | commas line_number {
        vsk_targeting($1);
        $$ = vsk_ast(INSN_LINE_NUMBERS, { nullptr });
        $$->insert($$->end(), $1->begin(), $1->end());
        $$->push_back($2);
    }
    ;

commas
    : TK_COMMA                           { vsk_targeting($1); $$ = vsk_ast(INSN_COMMAS); }
    | commas TK_COMMA                    { $$ = $1; $$->push_back(nullptr); }
    ;

line_range
    : line_number_or_dot TK_MINUS line_number_or_dot { vsk_targeting($1); $$ = vsk_ast(INSN_LINE_RANGE, { $1, $3 }); }
    | line_number_or_dot TK_MINUS                    { vsk_targeting($1); $$ = vsk_ast(INSN_LINE_RANGE, { $1, nullptr }); }
    |                    TK_MINUS line_number_or_dot { vsk_targeting($1); $$ = vsk_ast(INSN_LINE_RANGE, { nullptr, $2 }); }
    | line_number_or_dot                             { vsk_targeting($1); $$ = vsk_ast(INSN_LINE_RANGE, { $1, $1 }); }
    ;

dirty_8bit_sequence
    : TK_DIRTY_8BIT                      { vsk_targeting($1); $$ = vsk_ast(INSN_DIRTY_8BIT); }
    | dirty_8bit_sequence TK_DIRTY_8BIT  { $$ = $1; }
    ;

cmd_name
    : TK_CLS                { $$ = $1; }
    | TK_PLAY               { $$ = $1; }
    | TK_IDENTIFIER         { $$ = $1; }
    ;

cmd_parameter_list
    : TK_ON                                        { vsk_targeting($1); $$ = vsk_ast(INSN_PARAM_LIST, { $1 }); }
    | TK_OFF                                       { vsk_targeting($1); $$ = vsk_ast(INSN_PARAM_LIST, { $1 }); }
    | TK_COPY                                      { vsk_targeting($1); $$ = vsk_ast(INSN_PARAM_LIST, { $1 }); }
    | trailing_parameter_list                      { $$ = $1; }
    | file_number TK_COMMA trailing_parameter_list { $$ = $3; $$->insert($$->begin(), $1); }
    ;

line
    : TK_DIGITS statement TK_COMMENT {
        vsk_targeting($1);
        vsk_target_line = $1->to_int();
        $$ = vsk_ast_multi($2, $3);
        $$->m_program_line = vsk_target_line;
    }
    | TK_DIGITS statement {
        vsk_targeting($1);
        vsk_target_line = $1->to_int();
        $$ = $2;
        $$->m_program_line = vsk_target_line;
    }
    | statement TK_COMMENT {
        vsk_targeting($1);
        $$ = vsk_ast_multi($1, $2);
    }
    | statement {
        $$ = $1;
    }
    ;

translation_unit
    : line TK_NEWLINE           { $$ = $1; result = $$; }
    | line                      { $$ = $1; result = $$; }
    | TK_EVAL expression        { $$ = $2; result = $$; }
    | %empty                    { $$ = vsk_ast(INSN_MULTI); }
    ;
