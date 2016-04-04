%{
    #include<fstream>
    #include<string>
    #include "gmlparsestate.hpp"
    #define YYSTYPE int
    
    static std::ifstream* yyin;
    static int s,d,w;
    static graph::GMLParseState<graph::AdjacencyList<int,int>> s1;
    static int yylex (YYSTYPE *lvalp);
    static void yyerror(char* s);
    static int yyparse(void);
%}

%pure_parser
%token GRAPH_KEYWORD_TOKEN
%token DIR_KEYWORD_TOKEN
%token VERTEX_KEYWORD_TOKEN
%token NAME_KEYWORD_TOKEN
%token EDGE_KEYWORD_TOKEN
%token SRC_KEYWORD_TOKEN
%token DEST_KEYWORD_TOKEN
%token WEIGHT_KEYWORD_TOKEN
%token TRUE_OR_FALSE_TOKEN
%token NUM
%start expr

%%
expr: 
    /*Empty*/
    | GRAPH_KEYWORD_TOKEN '[' graph_decl ']'
;
graph_decl:
    /*Empty*/
    | dir_stmt vertex_blocks edge_blocks
;
dir_stmt:
    DIR_KEYWORD_TOKEN ':' TRUE_OR_FALSE_TOKEN {s1.addDirectedStatus($3);}
;
vertex_blocks:
    /*Empty*/
    | VERTEX_KEYWORD_TOKEN '[' vertex_decl ']' vertex_blocks
;
vertex_decl:
    vertex_name_stmt
;
vertex_name_stmt:
    NAME_KEYWORD_TOKEN ':' NUM {s1.addVertex($3);}
;
edge_blocks:
    /*Empty*/
    | EDGE_KEYWORD_TOKEN '[' edge_decl ']' edge_blocks
;
edge_decl:
    edge_src_stmt edge_dest_stmt edge_weight_stmt {s1.addEdge(s,d,w);}
;
edge_src_stmt:
    SRC_KEYWORD_TOKEN ':' NUM {s=$3;}
;
edge_dest_stmt:
    DEST_KEYWORD_TOKEN ':' NUM {d=$3;}
;
edge_weight_stmt:
    WEIGHT_KEYWORD_TOKEN ':' NUM {w=$3;}
;
%%

static bool isNumber(std::string s)
{
    for(int i=0;i<s.length();++i)
        if(!isdigit(s[i]))
            return false;
    return true;
}

static int yylex (YYSTYPE *lvalp)
{
    std::string input;
    *yyin>>input;
/*     std::cout<<input<<std::endl; */
    if(yyin->eof())
        return 0;
    if(input.length() == 1)
    {
        if(isNumber(input))
        {
            *lvalp = std::stoi(input);
            return NUM;
        }
        else
            return input[0];
    }
    if(input == "true")
    {
        *lvalp = 1;
        return TRUE_OR_FALSE_TOKEN;
    }
    if(input == "false")
    {
        *lvalp = 0;
        return TRUE_OR_FALSE_TOKEN;
    }
    if(input == "graph")
        return GRAPH_KEYWORD_TOKEN;
    if(input == "dir")
        return DIR_KEYWORD_TOKEN;
    if(input == "vertex")
        return VERTEX_KEYWORD_TOKEN;
    if(input == "name")
        return NAME_KEYWORD_TOKEN;
    if(input == "edge")
        return EDGE_KEYWORD_TOKEN;
    if(input == "src")
        return SRC_KEYWORD_TOKEN;
    if(input == "dest")
        return DEST_KEYWORD_TOKEN;
    if(input == "weight")
        return WEIGHT_KEYWORD_TOKEN;
    if(isNumber(input))
    {
        *lvalp = std::stoi(input);
        return NUM;
    }
    else
    {
        std::cout<<"Invalid token"<<input<<std::endl;
    }
}

static void yyerror (char* s) {}
