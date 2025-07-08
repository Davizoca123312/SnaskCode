/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_SNASK_PARSER_TAB_H_INCLUDED
# define YY_YY_SNASK_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    MAKE = 258,                    /* MAKE  */
    KEEP = 259,                    /* KEEP  */
    SET = 260,                     /* SET  */
    ZAP = 261,                     /* ZAP  */
    SHOO = 262,                    /* SHOO  */
    GRAB = 263,                    /* GRAB  */
    GRABNUM = 264,                 /* GRABNUM  */
    GRABTXT = 265,                 /* GRABTXT  */
    CRAFT = 266,                   /* CRAFT  */
    BACK = 267,                    /* BACK  */
    WHEN = 268,                    /* WHEN  */
    WHENN = 269,                   /* WHENN  */
    WHENEM = 270,                  /* WHENEM  */
    SPIN = 271,                    /* SPIN  */
    LOOPY = 272,                   /* LOOPY  */
    BREAKY = 273,                  /* BREAKY  */
    SKIPIT = 274,                  /* SKIPIT  */
    PACK = 275,                    /* PACK  */
    PACKADD = 276,                 /* PACKADD  */
    PACKGET = 277,                 /* PACKGET  */
    BOX = 278,                     /* BOX  */
    BOXGET = 279,                  /* BOXGET  */
    BOXSET = 280,                  /* BOXSET  */
    TO = 281,                      /* TO  */
    USE = 282,                     /* USE  */
    IDENTIFIER = 283,              /* IDENTIFIER  */
    INT_LITERAL = 284,             /* INT_LITERAL  */
    FLOAT_LITERAL = 285,           /* FLOAT_LITERAL  */
    STRING_LITERAL = 286,          /* STRING_LITERAL  */
    BOOL_LITERAL = 287,            /* BOOL_LITERAL  */
    NULL_LITERAL = 288,            /* NULL_LITERAL  */
    ADD = 289,                     /* ADD  */
    SUB = 290,                     /* SUB  */
    MUL = 291,                     /* MUL  */
    DIV = 292,                     /* DIV  */
    EQ = 293,                      /* EQ  */
    NEQ = 294,                     /* NEQ  */
    LT = 295,                      /* LT  */
    GT = 296,                      /* GT  */
    LE = 297,                      /* LE  */
    GE = 298,                      /* GE  */
    AND = 299,                     /* AND  */
    OR = 300,                      /* OR  */
    NOT = 301,                     /* NOT  */
    ASSIGN = 302,                  /* ASSIGN  */
    SEMICOLON = 303,               /* SEMICOLON  */
    LPAREN = 304,                  /* LPAREN  */
    RPAREN = 305,                  /* RPAREN  */
    LBRACE = 306,                  /* LBRACE  */
    RBRACE = 307,                  /* RBRACE  */
    LBRACKET = 308,                /* LBRACKET  */
    RBRACKET = 309,                /* RBRACKET  */
    COMMA = 310,                   /* COMMA  */
    DOT = 311,                     /* DOT  */
    COLON = 312                    /* COLON  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_SNASK_PARSER_TAB_H_INCLUDED  */
