# include <iostream>
# include <string>
# include <string.h>
# include <vector>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <sstream>

using namespace std;

enum Type
{
  VOID,
  INT,
  FLOAT,
  CHAR,
  BOOL,
  STRING,
  FUN,
  COUT
};

struct TokenValue
{
  Type tokenType;
  int intValue;
  float floatValue;
  char charValue;
  bool trueORfalse;
  string stringValue;
  vector<string> functionContent;
};

struct TokenInfo
{
  string type;
  string name;
  string arraySize;
  TokenValue tokenValue;
};

int gErrorLine = 1;
vector<TokenInfo> ginputData;
vector<string> gtemp;
vector<TokenInfo> gfunVar;

char PeekChar() ;
string GetToken() ;
string PeekToken() ;

void UserInput() ;
void Definition() ;
bool Type_Specifier( string input ) ;
void FunDef_or_Declarator() ;
void Ro_Declarator() ;
void FunDef_wo_ID() ;
void FormalParaList() ;
void Compound_Statement() ;
void Declaration() ;
void Statement() ;
void Exp() ;
void BasicEXP() ;
void Ro_ID_start_BasicEXP() ;
void Ro_PPMM_ID_start_BasicExp() ;
bool Sign( string input ) ;
void ActualParaList() ;
bool Assigment_Operator( string input ) ;
void Romce_and_Romloe() ;
void Rom_logical_ORexp() ;
void M_logical_ANDexp() ;
void Rom_logical_ANDexp() ;
void M_bit_ORexp() ;
void Rom_bit_ORexp() ;
void M_bit_exORexp() ;
void Rom_bit_exORexp() ;
void M_bit_ANDexp() ;
void Rom_bit_ANDexp() ;
void M_EqualityExp() ;
void Rom_EqualityExp() ;
void M_RelationalExp() ;
void Rom_RelationalExp() ;
void M_ShiftExp() ;
void Rom_ShiftExp() ;
void M_AdditiveExp() ;
void Rom_AdditiveExp() ;
void M_MULTexp() ;
void Rom_MULTexp() ;
void UnaryExp() ;
void Signed_UnaryExp() ;
void Unsigned_UnaryExp() ;

void UpdateVector() ;
bool DefineOrNot( string input ) ;
void CheckSysFunction() ;
void ErrorMsg( string input ) ;

void Statement2( int &index ) ;
void Exp2( TokenValue &tempAns, int &index ) ;
void BasicEXP2( TokenValue &tempAns, int &index ) ;
void Ro_ID_start_BasicEXP2( string idName, TokenValue &tempAns, int &index ) ;
void Ro_PPMM_ID_start_BasicExp2( TokenValue &tempAns, int &index ) ;
bool Sign2( string input ) ;
void ActualParaList2( TokenValue &tempAns, int &index ) ;
bool Assigment_Operator2( string input ) ;
void Romce_and_Romloe2( TokenValue &tempAns, int &index ) ;
void Rom_logical_ORexp2( TokenValue &tempAns, int &index ) ;
void M_logical_ANDexp2( TokenValue &tempAns, int &index ) ;
void Rom_logical_ANDexp2( TokenValue &tempAns, int &index ) ;
void M_bit_ORexp2( TokenValue &tempAns, int &index ) ;
void Rom_bit_ORexp2( TokenValue &tempAns, int &index ) ;
void M_bit_exORexp2( TokenValue &tempAns, int &index ) ;
void Rom_bit_exORexp2( TokenValue &tempAns, int &index ) ;
void M_bit_ANDexp2( TokenValue &tempAns, int &index ) ;
void Rom_bit_ANDexp2( TokenValue &tempAns, int &index ) ;
void M_EqualityExp2( TokenValue &tempAns, int &index ) ;
void Rom_EqualityExp2( TokenValue &tempAns, int &index ) ;
void M_RelationalExp2( TokenValue &tempAns, int &index ) ;
void Rom_RelationalExp2( TokenValue &tempAns, int &index ) ;
void M_ShiftExp2( TokenValue &tempAns, int &index ) ;
void Rom_ShiftExp2( TokenValue &tempAns, int &index ) ;
void M_AdditiveExp2( TokenValue &tempAns, int &index ) ;
void Rom_AdditiveExp2( TokenValue &tempAns, int &index ) ;
void M_MULTexp2( TokenValue &tempAns, int &index ) ;
void Rom_MULTexp2( TokenValue &tempAns, int &index ) ;
void UnaryExp2( TokenValue &tempAns, int &index ) ;
void Signed_UnaryExp2( TokenValue &tempAns, int &index ) ;
void Unsigned_UnaryExp2( TokenValue &tempAns, int &index ) ;

int DefineOrNot2( string input ) ;
void Compare( string sign, TokenValue &tempAns, TokenValue temp ) ;
void Calculation( string sign, TokenValue &tempAns, TokenValue temp ) ;
void Output( TokenValue ans ) ;


class Exception
{
  public:
  string mMsg;
  Exception() { }

  Exception( string x )
  {
    mMsg = x;
  } // Exception()
}; // class Exception

class Unrecognized : public Exception
{
  public:
  Unrecognized( string x )
  {
    mMsg = x;
  } // Unrecognized()
}; // class Unrecognized

class Unexpected : public Exception
{
  public:
  Unexpected( string x )
  {
    mMsg = x;
  } // Unexpected()
}; // class Unexpected

class Undefined : public Exception
{
  public:
  Undefined( string x )
  {
    mMsg = x;
  } // Undefined()
}; // class Undefined

int main()
{
  int uTestNum = 0;
  char exceptionLine[256];

  cin >> uTestNum;
  cout << "Our-C running ..." << endl;
  char uTestLine = cin.get();

  while ( true )
  {
    try
    {
      cout << "> ";
      UserInput();
    } // try
    catch ( Unrecognized *e )
    {
      cout << "Line " << gErrorLine << " : unrecognized token with first char : '" << e->mMsg << "'" << endl;
      cin.getline( exceptionLine, 256 );
    } // catch Unrecognized
    catch ( Unexpected *e )
    {
      cout << "Line " << gErrorLine << " : unexpected token : '" << e->mMsg << "'" << endl;
      cin.getline( exceptionLine, 256 );
    } // catch Unexpected
    catch ( Undefined *e )
    {
      cout << "Line " << gErrorLine << " : undefined identifier : '" << e->mMsg << "'" << endl;
      cin.getline( exceptionLine, 256 );
    } // catch Undefined
    catch ( Exception *e )
    {
      cout << "Error" << endl;
      cin.getline( exceptionLine, 256 );
    } // catch Exception

    gErrorLine = 1;
    gtemp.clear();
    gfunVar.clear();
  }   // while()

  return 0;
} // main()

// TODO: skip white spaces & comment line and Peek first Token
char PeekChar()
{
  char ch = '\0';
  char whitespace = '\0';
  char commentLine[256];

  ch = cin.peek();
  while ( ch == ' ' || ch == '\n' || ch == '\t' || ch == '/' )
  {
    whitespace = cin.get();

    if ( whitespace == '\n' )
    {
      gErrorLine = gErrorLine + 1;
    } // if

    if ( whitespace == '/' ) // 判斷是註解還是除號
    {
      ch = cin.peek();
      if ( ch == '/' ) // comment sign -> ignore comment line
      {
        cin.getline( commentLine, 256 );
        gErrorLine = gErrorLine + 1;
      } // if
      else // division sign -> put back input & return '/'
      {
        cin.putback( whitespace );
        return '/';
      } // else
    } // if

    ch = cin.peek();
  } // while

  return ch;
} // PeekChar()

// TODO: get id, constant & sign
string GetToken()
{
  char ch = '\0';
  char inputChar = '\0';
  string token = "";

  ch = PeekChar();
  if ( ( ch >= 'a' && ch <= 'z' ) || ( ch >= 'A' && ch <= 'Z' ) ) // IDENT
  {
    while ( ( ch >= 'a' && ch <= 'z' ) || ( ch >= 'A' && ch <= 'Z' ) ||
            ( ch >= '0' && ch <= '9' ) || ch == '_' ) // digits or letters or underlines can be IDENT
    {
      inputChar = cin.get();
      token = token + inputChar;
      ch = cin.peek();
    } // while
  } // if
  else if ( ch == '.' || ( ch >= '0' && ch <= '9' ) ) // Num_Constant
  {
    inputChar = cin.get();
    token = token + inputChar;
    if ( token == "." ) // float start with point
    {
      ch = cin.peek();
      while ( ch >= '0' && ch <= '9' )
      {
        inputChar = cin.get();
        token = token + inputChar;
        ch = cin.peek();
      } // while
    } // if
    else // Int or Float start with num
    {
      ch = cin.peek();
      while ( ch >= '0' && ch <= '9' ) // INT
      {
        inputChar = cin.get();
        token = token + inputChar;
        ch = cin.peek();
      } // while

      if ( ch == '.' ) // 小數點後 再check是否有數字
      {
        inputChar = cin.get();
        token = token + inputChar;
        ch = cin.peek();
        while ( ch >= '0' && ch <= '9' )
        {
          inputChar = cin.get();
          token = token + inputChar;
          ch = cin.peek();
        } // while
      } // if
    } // else
  } // else if
  else if ( ch == '\'' || ch == '\"' ) // string_Constant
  {
    inputChar = cin.get();
    token = token + inputChar;
    if ( token == "\'" ) // 'content'
    {
      ch = cin.peek();
      while ( ch != '\'' ) // content
      {
        inputChar = cin.get();
        token = token + inputChar;
        ch = cin.peek();
      } // while

      inputChar = cin.get();
      token = token + inputChar;
    } // if
    else // "content"
    {
      ch = cin.peek();
      while ( ch != '\"' ) // content
      {
        inputChar = cin.get();
        token = token + inputChar;
        ch = cin.peek();
      } // while

      inputChar = cin.get();
      token = token + inputChar;
    } // else
  } // else if
  else if ( ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}' ||
            ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^' ||
            ch == '>' || ch == '<' ||
            ch == '&' || ch == '|' || ch == '=' || ch == '!' ||
            ch == ';' || ch == ',' || ch == '?' || ch == ':' ) // sign
  {
    inputChar = cin.get();
    token = token + inputChar;

    ch = cin.peek();
    if ( inputChar == '=' || inputChar == '!' ||
         inputChar == '*' || inputChar == '/' || inputChar == '%' ) // "==" "!=" "*=" "/=" "%="
    {
      if ( ch == '=' )
      {
        inputChar = cin.get();
        token = token + inputChar;
      } // if
    } // if
    else if ( inputChar == '>' ) // ">=" ">>"
    {
      if ( ch == '=' || ch == '>' )
      {
        inputChar = cin.get();
        token = token + inputChar;
      } // if
    } // else if
    else if ( inputChar == '<' ) // "<=" "<<"
    {
      if ( ch == '=' || ch == '<' )
      {
        inputChar = cin.get();
        token = token + inputChar;
      } // if
    } // else if
    else if ( inputChar == '+' ) // "+=" "++"
    {
      if ( ch == '=' || ch == '+' )
      {
        inputChar = cin.get();
        token = token + inputChar;
      } // if
    } // else if
    else if ( inputChar == '-' ) // "-=" "--"
    {
      if ( ch == '=' || ch == '-' )
      {
        inputChar = cin.get();
        token = token + inputChar;
      } // if
    }   // else if
    else if ( inputChar == '&' ) // "&&"
    {
      if ( ch == '&' )
      {
        inputChar = cin.get();
        token = token + inputChar;
      } // if
    } // else if
    else if ( inputChar == '|' ) // "||"
    {
      if ( ch == '|' )
      {
        inputChar = cin.get();
        token = token + inputChar;
      } // if
    } // else if
  } // else if
  else // unrecognized token
  {
    inputChar = cin.get();
    token = token + inputChar;
  } // else

  return token;
} // GetToken()

// TODO: Peek next Token
string PeekToken()
{
  string token = "";

  token = GetToken();
  for ( int i = token.length(); i > 0 ; i-- ) // putback token
  {
    cin.putback( token[i-1] );
  } // for

  return token;
} // PeekToken()

// TODO: user_input ::= ( definition | statement )
void UserInput()
{
  string token = "";
  TokenInfo ans;

  token = PeekToken();
  if ( token == "void" ||
       token == "int" || token == "char" || token == "float" || token == "string" || token == "bool" )
  {
    Definition();
    UpdateVector();
  } // if
  else
  {
    Statement();
    CheckSysFunction();
    cout << "Statement executed ..." << endl;
  } // else

  char ch = '\0';
  char whitespace = '\0';
  char ignoreLine[256];

  ch = cin.peek();
  while ( ch == ' ' || ch == '\t' )
  {
    whitespace = cin.get();
    ch = cin.peek();
  } // while

  if ( ch == '/' ) // 判斷是註解還是除號
  {
    whitespace = cin.get();
    ch = cin.peek();
    if ( ch == '/' ) // comment sign -> ignore comment line
    {
      cin.getline( ignoreLine, 256, '\n' );
    } // if
    else // division sign -> put back input & return '/'
    {
      cin.putback( whitespace );
    } // else
  } // if
  else if ( ch == '\n' )
  {
    whitespace = cin.get();
  } // else if

} // UserInput()

// TODO: definition ::= VOID Identifier function_definition_without_ID |
//                      type_specifier Identifier function_definition_or_declarators
void Definition()
{
  char ch = '\0';
  string token = "";
  string type = "";
  string id = "";

  type = GetToken();
  gtemp.push_back( type );

  if ( type == "void" )
  {
    ch = PeekChar();
    if ( ( ch < 'a' || ch > 'z' ) && ( ch < 'A' || ch > 'Z' ) ) // Error Msg. // Unexpected
    {
      token = GetToken();
      ErrorMsg( token );
    } // if

    id = GetToken();
    gtemp.push_back( id );

    FunDef_wo_ID();
  } // if
  else if ( Type_Specifier( type ) )
  {
    ch = PeekChar();
    if ( ( ch < 'a' || ch > 'z' ) && ( ch < 'A' || ch > 'Z' ) ) // Error Msg. // Unexpected
    {
      token = GetToken();
      ErrorMsg( token );
    } // if

    id = GetToken();
    gtemp.push_back( id );

    FunDef_or_Declarator();
  } // else if
  else // Error Msg. // Unexpected
  {
    ErrorMsg( type );
  } // else
} // Definition()

// TODO: type_specifier ::= INT | CHAR | FLOAT | STRING | BOOL
bool Type_Specifier( string input )
{
  if ( input != "int" && input != "char" && input != "float" &&
       input != "string" && input != "bool" )
  {
    return false;
  } // if

  return true;
} // Type_Specifier()

// TODO: function_definition_or_declarators ::= function_definition_without_ID | rest_of_declarators
void FunDef_or_Declarator()
{
  string token = "";

  token = PeekToken();
  if ( token == "(" )
  {
    FunDef_wo_ID();
  } // if
  else
  {
    Ro_Declarator();
  } // else
} // FunDef_or_Declarator()

// TODO: rest_of_declarators ::= [ '[' Constant ']' ]
//                               { ',' Identifier [ '[' Constant ']' ] } ';'
void Ro_Declarator()
{
  char ch = '\0';
  string token = "";
  string sign = "";
  string id = "";
  string constant = "";

  token = PeekToken();
  if ( token == "[" ) // '[' Constant ']'
  {
    sign = GetToken();
    gtemp.push_back( sign );

    ch = PeekChar();
    token = PeekToken();

    if ( ch != '.' && ( ch < '0' || ch > '9' ) &&
         ch != '\'' && ch != '\"' &&
         token != "true" && token != "false" )  // Error Msg. // Unexpected
    {
      token = GetToken();
      ErrorMsg( token );
    } // if

    constant = GetToken();
    gtemp.push_back( constant );
    sign = GetToken();
    gtemp.push_back( sign );

    if ( sign != "]" ) // Error Msg. // Unexpected
    {
      ErrorMsg( sign );
    } // if

    token = PeekToken();
  } // if

  while ( token == "," ) // { ',' Identifier [ '[' Constant ']' ] }
  {
    sign = GetToken();
    gtemp.push_back( sign );

    ch = PeekChar();
    token = PeekToken();
    if ( ( ( ch < 'a' || ch > 'z' ) && ( ch < 'A' || ch > 'Z' ) ) ||
         token == "true" || token == "false" ) // Error Msg. // Unexpected
    {
      token = GetToken();
      ErrorMsg( token );
    } // if

    id = GetToken();
    gtemp.push_back( id );

    token = PeekToken();
    if ( token == "[" ) // '[' Constant ']'
    {
      sign = GetToken();
      gtemp.push_back( sign );

      ch = PeekChar();
      if ( ch != '.' && ( ch < '0' || ch > '9' ) &&
           ch != '\'' && ch != '\"' &&
           token != "true" && token != "false" ) // Error Msg. // Unexpected
      {
        token = GetToken();
        ErrorMsg( token );
      } // if

      constant = GetToken();
      gtemp.push_back( constant );
      sign = GetToken();
      gtemp.push_back( sign );

      if ( sign != "]" ) // Error Msg. // Unexpected
      {
        ErrorMsg( sign );
      } // if
    } // if

    token = PeekToken();
  } // while

  sign = GetToken();
  gtemp.push_back( sign );

  if ( sign != ";" ) // Error Msg. // Unexpected
  {
    ErrorMsg( sign );
  } // if
} // Ro_Declarator()

// TODO: function_definition_without_ID ::= '(' [ VOID | formal_parameter_list ] ')' compound_statement
void FunDef_wo_ID()
{
  string token = "";
  string type = "";
  string sign = "";

  sign = GetToken();
  gtemp.push_back( sign );

  if ( sign != "(" ) // Error Msg. // Unexpected
  {
    ErrorMsg( sign );
  } // if

  token = PeekToken();
  if ( token != ")" )
  {
    if ( token == "void" )
    {
      type = GetToken();
      gtemp.push_back( type );
    } // if
    else
    {
      FormalParaList();
    } // else
  } // if

  sign = GetToken();
  gtemp.push_back( sign );

  if ( sign != ")" ) // Error Msg. // Unexpected
  {
    ErrorMsg( sign );
  } // if

  Compound_Statement();
} // FunDef_wo_ID()

// TODO: formal_parameter_list ::=
//         type_specifier [ '&' ] Identifier [ '[' Constant ']' ]
//         { ',' type_specifier [ '&' ] Identifier [ '[' Constant ']' ] }
void FormalParaList()
{
  char ch = '\0';
  string token = "";
  string type = "";
  string sign = "";
  string id = "";
  string constant = "";
  TokenInfo localvar;

  type = GetToken();
  gtemp.push_back( type );

  if ( !Type_Specifier( type ) ) // Error Msg. // Unexpected
  {
    ErrorMsg( type );
  } // if

  token = PeekToken();
  if ( token == "&" )
  {
    sign = GetToken();
    gtemp.push_back( sign );
  } // if

  ch = PeekChar();
  token = PeekToken();
  if ( ( ( ch < 'a' || ch > 'z' ) && ( ch < 'A' || ch > 'Z' ) ) ||
       token == "true" || token == "false" )
  { // Error Msg. // Unexpected
    token = GetToken();
    ErrorMsg( token );
  } // if

  id = GetToken();
  gtemp.push_back( id );

  token = PeekToken();
  if ( token == "[" ) // '[' Constant ']'
  {
    sign = GetToken();
    gtemp.push_back( sign );

    ch = PeekChar();
    token = PeekToken();
    if ( ch != '.' && ( ch < '0' || ch > '9' ) &&
         ch != '\'' && ch != '\"' &&
         token != "true" && token != "false" )
    { // Error Msg. // Unexpected
      token = GetToken();
      ErrorMsg( token );
    } // if

    constant = GetToken();
    gtemp.push_back( constant );
    sign = GetToken();
    gtemp.push_back( sign );

    if ( sign != "]" ) // Error Msg. // Unexpected
    {
      ErrorMsg( sign );
    } // if

    token = PeekToken();
  } // if

  while ( token == "," ) // { ',' type_specifier [ '&' ] Identifier [ '[' Constant ']' ] }
  {
    sign = GetToken();
    type = GetToken();
    gtemp.push_back( sign );
    gtemp.push_back( type );

    if ( !Type_Specifier( type ) ) // Error Msg. // Unexpected
    {
      ErrorMsg( type );
    } // if

    token = PeekToken();
    if ( token == "&" )
    {
      sign = GetToken();
      gtemp.push_back( sign );
    } // if

    ch = PeekChar();
    token = PeekToken();
    if ( ( ( ch < 'a' || ch > 'z' ) && ( ch < 'A' || ch > 'Z' ) ) ||
         token == "true" || token == "false" ) // Error Msg. // Unexpected
    {
      token = GetToken();
      ErrorMsg( token );
    } // if

    id = GetToken();
    gtemp.push_back( id );

    token = PeekToken();
    if ( token == "[" ) // '[' Constant ']'
    {
      sign = GetToken();
      gtemp.push_back( sign );

      ch = PeekChar();
      token = PeekToken();
      if ( ch != '.' && ( ch < '0' || ch > '9' ) &&
           ch != '\'' && ch != '\"' &&
           token != "true" && token != "false" ) // Error Msg. // Unexpected
      {
        token = GetToken();
        ErrorMsg( token );
      } // if

      constant = GetToken();
      sign = GetToken();
      gtemp.push_back( constant );
      gtemp.push_back( sign );
      if ( sign != "]" ) // Error Msg. // Unexpected
      {
        ErrorMsg( sign );
      } // if
    } // if

    token = PeekToken();
  } // while

  for ( int i = 3; i < gtemp.size() ; i = i + 2 ) // 存進loacal var. vector中
  {
    localvar.type = gtemp[i];
    i++;
    if ( gtemp[i] == "&" )
    {
      i++;
    } // if

    if ( ( i + 1 ) < gtemp.size() && gtemp[i+1] == "[" )
    {
      localvar.name = gtemp[i];
      localvar.arraySize = gtemp[i+2];
      i = i + 3;
    } // if
    else
    {
      localvar.name = gtemp[i];
    } // else

    gfunVar.push_back( localvar );
  } // for
} // FormalParaList()

// TODO: compound_statement ::= '{' { declaration | statement } '}'
void Compound_Statement()
{
  string token = "";
  string type = "";
  string sign = "";
  TokenInfo localvar;

  sign = GetToken();
  gtemp.push_back( sign );

  if ( sign != "{" ) // Error Msg. // Unexpected
  {
    ErrorMsg( sign );
  } // if

  token = PeekToken();
  while ( token != "}" )
  {
    if ( token == "int" || token == "char" || token == "float" || token == "string" || token == "bool" )
    {
      int start = 0;
      int end = 0;
      start = gtemp.size();

      Declaration();

      end = gtemp.size();

      localvar.type = gtemp[start];
      for ( int i = start + 1; i < end ; i = i + 2 ) // 存入local var. vector
      {
        if ( ( i + 1 ) < gtemp.size() && gtemp[i + 1] == "[" )
        {
          localvar.name = gtemp[i];
          localvar.arraySize = gtemp[i + 2];
          i = i + 3;
        } // if
        else
        {
          localvar.name = gtemp[i];
        } // else

        gfunVar.push_back( localvar );
      } // for
    } // if
    else
    {
      Statement();
    } // else

    token = PeekToken();
  } // while

  sign = GetToken();
  gtemp.push_back( sign );

} // Compound_Statement()

// TODO: declaration ::= type_specifier Identifier rest_of_declarators
void Declaration()
{
  char ch = '\0';
  string type = "";
  string token = "";
  string id = "";

  type = GetToken();
  gtemp.push_back( type );

  if ( !Type_Specifier( type ) ) // Error Msg. // Unexpected
  {
    ErrorMsg( type );
  } // if

  ch = PeekChar();
  if ( ( ch < 'a' || ch > 'z' ) && ( ch < 'A' || ch > 'Z' ) ) // Error Msg. // Unexpected
  {
    token = GetToken();
    ErrorMsg( token );
  } // if

  id = GetToken();
  gtemp.push_back( id );

  Ro_Declarator();
} // Declaration()

// TODO: statement ::= ';'
//                   | expression ';'
//                   | RETURN [ expression ] ';'
//                   | compound_statement
//                   | IF '(' expression ')' statement [ ELSE statement ]
//                   | WHILE '(' expression ')' statement
//                   | DO statement WHILE '(' expression ')' ';'
void Statement()
{
  char ch = '\0';
  string token = "";
  string type = "";
  string sign = "";

  token = PeekToken();
  if ( token == ";" ) // the null statement
  {
    sign = GetToken();
    gtemp.push_back( sign );
  } // if
  else if ( token == "return" ) // RETURN [ expression ] ';'
  {
    type = GetToken();
    gtemp.push_back( type );

    token = PeekToken();
    if ( token != ";" )
    {
      Exp();
    } // if

    sign = GetToken();
    gtemp.push_back( sign );

    if ( sign != ";" ) // Error Msg. // Unexpected
    {
      ErrorMsg( sign );
    } // if
  } // else if
  else if ( token == "{" ) // compound statement
  {
    Compound_Statement();
  } // else if
  else if ( token == "if" ) // IF '(' expression ')' statement [ ELSE statement ]
  {
    type = GetToken();
    sign = GetToken();
    gtemp.push_back( type );
    gtemp.push_back( sign );

    if ( sign != "(" ) // Error Msg. // Unexpected
    {
      ErrorMsg( sign );
    } // if

    Exp();
    sign = GetToken();
    gtemp.push_back( sign );

    if ( sign != ")" ) // Error Msg. // Unexpected
    {
      ErrorMsg( sign );
    } // if

    Statement();
    token = PeekToken();
    if ( token == "else" )
    {
      type = GetToken();
      gtemp.push_back( type );

      Statement();
    } // if
  } // else if
  else if ( token == "while" ) // WHILE '(' expression ')' statement
  {
    type = GetToken();
    sign = GetToken();
    gtemp.push_back( type );
    gtemp.push_back( sign );

    if ( sign != "(" ) // Error Msg. // Unexpected
    {
      ErrorMsg( sign );
    } // if

    Exp();
    sign = GetToken();
    gtemp.push_back( sign );

    if ( sign != ")" ) // Error Msg. // Unexpected
    {
      ErrorMsg( sign );
    } // if

    Statement();
  } // else if
  else if ( token == "do" ) // DO statement WHILE '(' expression ')' ';'
  {
    type = GetToken();
    gtemp.push_back( type );

    Statement();
    type = GetToken();
    gtemp.push_back( type );

    if ( type != "while" ) // Error Msg. // Unexpected
    {
      ErrorMsg( type );
    } // if

    sign = GetToken();
    gtemp.push_back( sign );

    if ( sign != "(" ) // Error Msg. // Unexpected
    {
      ErrorMsg( sign );
    } // if

    Exp();
    sign = GetToken();
    gtemp.push_back( sign );

    if ( sign != ")" ) // Error Msg. // Unexpected
    {
      ErrorMsg( sign );
    } // if

    sign = GetToken();
    gtemp.push_back( sign );

    if ( sign != ";" ) // Error Msg. // Unexpected
    {
      ErrorMsg( sign );
    } // if
  } // else if
  else // expression ';'
  {
    Exp();
    sign = GetToken();
    gtemp.push_back( sign );
    if ( sign != ";" ) // Error Msg. // Unexpected
    {
      ErrorMsg( sign );
    } // if
  } // else
} // Statement()

// TODO: expression ::= basic_expression { ',' basic_expression }
void Exp()
{
  string token = "";
  string sign = "";

  BasicEXP();
  token = PeekToken();
  while ( token == "," )
  {
    sign = GetToken();
    gtemp.push_back( sign );

    BasicEXP();

    token = PeekToken();
  } // while
} // Exp()

// TODO: basic_expression ::= Identifier rest_of_Identifier_started_basic_exp
//                          | ( PP | MM ) Identifier rest_of_PPMM_Identifier_started_basic_exp
//                          | sign { sign } signed_unary_exp romce_and_romloe
//                          | ( Constant | '(' expression ')' ) romce_and_romloe
void BasicEXP()
{
  char ch = '\0';
  string token = "";
  string sign = "";
  string id = "";
  string constant = "";

  token = PeekToken();
  if ( token == "++" || token == "--" ) // ( PP | MM ) Identifier rest_of_PPMM_Identifier_started_basic_exp
  {
    sign = GetToken();
    gtemp.push_back( sign );

    ch = PeekChar();
    token = PeekToken();

    if ( ( ( ch < 'a' || ch > 'z' ) && ( ch < 'A' || ch > 'Z' ) ) ||
         token == "true" || token == "false" ) // Error Msg. // Unexpected
    {
      token = GetToken();
      ErrorMsg( token );
    } // if

    id = GetToken();
    gtemp.push_back( id );

    if ( !DefineOrNot( id ) ) // Error Msg. // Undefine
    {
      throw new Undefined( id );
    } // if

    Ro_PPMM_ID_start_BasicExp();
  } // if
  else if ( Sign( token ) ) // sign { sign } signed_unary_exp romce_and_romloe
  {
    while ( Sign( token ) )
    {
      sign = GetToken();
      gtemp.push_back( sign );

      token = PeekToken();
    } // while

    Signed_UnaryExp();
    Romce_and_Romloe();
  } // else if
  else
  {
    ch = PeekChar();
    if ( ch == '.' || ( ch >= '0' && ch <= '9' ) || ch == '\'' || ch == '\"' ||
         ch == '(' ||
         token == "true" || token == "false" ) // ( Constant | '(' expression ')' ) romce_and_romloe
    {
      if ( ch == '(' )
      {
        sign = GetToken();
        gtemp.push_back( sign );

        Exp();
        sign = GetToken();
        gtemp.push_back( sign );

        if ( sign != ")" ) // Error Msg. // Unexpected
        {
          ErrorMsg( sign );
        } // if
      } // if
      else
      {
        constant = GetToken();
        gtemp.push_back( constant );
      } // else

      Romce_and_Romloe();
    } // if
    else // Identifier rest_of_Identifier_started_basic_exp
    {
      ch = PeekChar();
      if ( ( ( ch < 'a' || ch > 'z' ) && ( ch < 'A' || ch > 'Z' ) ) ||
           token == "true" || token == "false" ) // Error Msg. // Unexpected
      {
        token = GetToken();
        ErrorMsg( token );
      }   // if

      id = GetToken();
      gtemp.push_back( id );

      if ( id == "cin" || id == "cout" )
      {
        token = PeekToken();

        if ( id == "cin" )
        {
          if ( token != ">>" )
          {
            sign = GetToken();
            ErrorMsg( sign );
          } // if
        } // if
        else
        {
          if ( token != "<<" )
          {
            sign = GetToken();
            ErrorMsg( sign );
          } // if
        } // else
      } // if
      else
      {
        if ( !DefineOrNot( id ) ) // Error Msg. // Undefine
        {
          throw new Undefined( id );
        } // if
      } // else

      Ro_ID_start_BasicEXP();
    } // else
  } // else
} // BasicEXP()

// TODO: rest_of_Identifier_started_basic_exp ::=
//           [ '[' expression ']' ] ( assignment_operator basic_expression | [ PP | MM ] romce_and_romloe )
//         | '(' [ actual_parameter_list ] ')' romce_and_romloe
void Ro_ID_start_BasicEXP()
{
  char ch = '\0';
  string token = "";
  string sign = "";

  token = PeekToken();
  if ( token == "(" ) // '(' [ actual_parameter_list ] ')' romce_and_romloe
  {
    sign = GetToken();
    gtemp.push_back( sign );

    token = PeekToken();
    if ( token != ")" )
    {
      ActualParaList();
    } // if

    sign = GetToken();
    gtemp.push_back( sign );

    if ( sign != ")" ) // Error Msg. // Unexpected
    {
      ErrorMsg( sign );
    } // if

    Romce_and_Romloe();
  } // if
  else // [ '[' expression ']' ] ( assignment_operator basic_expression | [ PP | MM ] romce_and_romloe )
  {
    if ( token == "[" ) // [ '[' expression ']' ]
    {
      sign = GetToken();
      gtemp.push_back( sign );

      Exp();
      sign = GetToken();
      gtemp.push_back( sign );

      if ( sign != "]" ) // Error Msg. // Unexpected
      {
        ErrorMsg( sign );
      } // if

      token = PeekToken();
    } // if

    if ( Assigment_Operator( token ) ) // assignment_operator basic_expression
    {
      sign = GetToken();
      gtemp.push_back( sign );

      BasicEXP();
    } // if
    else // [ PP | MM ] romce_and_romloe
    {
      token = PeekToken();
      if ( token == "++" || token == "--" )
      {
        sign = GetToken();
        gtemp.push_back( sign );
      } // if

      Romce_and_Romloe();
    } // else
  } // else
} // Ro_ID_start_BasicEXP()

// TODO: rest_of_PPMM_Identifier_started_basic_exp ::= [ '[' expression ']' ] romce_and_romloe
void Ro_PPMM_ID_start_BasicExp()
{
  string token = "";
  string sign = "";

  token = PeekToken();
  if ( token == "[" ) // '[' expression ']'
  {
    sign = GetToken();
    gtemp.push_back( sign );

    Exp();
    sign = GetToken();
    gtemp.push_back( sign );

    if ( sign != "]" ) // Error Msg. // Unexpected
    {
      ErrorMsg( sign );
    } // if
  } // if

  Romce_and_Romloe();
} // Ro_PPMM_ID_start_BasicExp()

// TODO: sign ::= '+' | '-' | '!'
bool Sign( string input )
{
  if ( input == "+" || input == "-" || input == "!" )
  {
    return true;
  } // if
  else
  {
    return false;
  } // else
} // Sign()

// TODO: actual_parameter_list ::= basic_expression { ',' basic_expression }
void ActualParaList()
{
  string token = "";
  string sign = "";

  BasicEXP();
  token = PeekToken();
  while ( token == "," )
  {
    sign = GetToken();
    gtemp.push_back( sign );

    BasicEXP();
    token = PeekToken();
  } // while
} // ActualParaList()

// TODO: assignment_operator ::= '=' | TE | DE | RE | PE | ME
bool Assigment_Operator( string input )
{
  if ( input == "=" || input == "*=" || input == "/=" || input == "%=" || input == "+=" || input == "-=" )
  {
    return true;
  } // if
  else
  {
    return false;
  } // else
} // Assigment_Operator()

// TODO: rest_of_maybe_conditional_exp_and_rest_of_maybe_logical_OR_exp ::=
//           rest_of_maybe_logical_OR_exp [ '?' basic_expression ':' basic_expression ]
void Romce_and_Romloe()
{
  string token = "";
  string sign = "";

  Rom_logical_ORexp();

  token = PeekToken();
  if ( token == "?" )
  {
    sign = GetToken();
    gtemp.push_back( sign );

    BasicEXP();
    sign = GetToken();
    gtemp.push_back( sign );

    if ( sign != ":" ) // Error Msg. // Unexpected
    {
      ErrorMsg( sign );
    } // if

    BasicEXP();
  } // if
} // Romce_and_Romloe()

// TODO: rest_of_maybe_logical_OR_exp ::= rest_of_maybe_logical_AND_exp { OR maybe_logical_AND_exp }
void Rom_logical_ORexp()
{
  string token = "";
  string sign = "";

  Rom_logical_ANDexp();
  token = PeekToken();
  while ( token == "||" )
  {
    sign = GetToken();
    gtemp.push_back( sign );

    M_logical_ANDexp();
    token = PeekToken();
  } // while
} // Rom_logical_ORexp()

// TODO: maybe_logical_AND_exp ::= maybe_bit_OR_exp { AND maybe_bit_OR_exp }
void M_logical_ANDexp()
{
  string token = "";
  string sign = "";

  M_bit_ORexp();
  token = PeekToken();
  while ( token == "&&" )
  {
    sign = GetToken();
    gtemp.push_back( sign );

    M_bit_ORexp();
    token = PeekToken();
  } // while
} // M_logical_ANDexp()

// TODO: rest_of_maybe_logical_AND_exp ::= rest_of_maybe_bit_OR_exp { AND maybe_bit_OR_exp }
void Rom_logical_ANDexp()
{
  string token = "";
  string sign = "";

  Rom_bit_ORexp();
  token = PeekToken();
  while ( token == "&&" )
  {
    sign = GetToken();
    gtemp.push_back( sign );

    M_bit_ORexp();
    token = PeekToken();
  } // while
} // Rom_logical_ANDexp()

// TODO: maybe_bit_OR_exp ::= maybe_bit_ex_OR_exp { '|' maybe_bit_ex_OR_exp }
void M_bit_ORexp()
{
  string token = "";
  string sign = "";

  M_bit_exORexp();
  token = PeekToken();
  while ( token == "|" )
  {
    sign = GetToken();
    gtemp.push_back( sign );

    M_bit_exORexp();
    token = PeekToken();
  } // while
} // M_bit_ORexp()

// TODO: rest_of_maybe_bit_OR_exp ::= rest_of_maybe_bit_ex_OR_exp { '|' maybe_bit_ex_OR_exp }
void Rom_bit_ORexp()
{
  string token = "";
  string sign = "";

  Rom_bit_exORexp();
  token = PeekToken();
  while ( token == "|" )
  {
    sign = GetToken();
    gtemp.push_back( sign );

    M_bit_exORexp();
    token = PeekToken();
  } // while
} // Rom_bit_ORexp()

// TODO: maybe_bit_ex_OR_exp ::= maybe_bit_AND_exp { '^' maybe_bit_AND_exp }
void M_bit_exORexp()
{
  string token = "";
  string sign = "";

  M_bit_ANDexp();
  token = PeekToken();
  while ( token == "^" )
  {
    sign = GetToken();
    gtemp.push_back( sign );

    M_bit_ANDexp();
    token = PeekToken();
  } // while
} // M_bit_exORexp()

// TODO: rest_of_maybe_bit_ex_OR_exp ::= rest_of_maybe_bit_AND_exp { '^' maybe_bit_AND_exp }
void Rom_bit_exORexp()
{
  string token = "";
  string sign = "";

  Rom_bit_ANDexp();
  token = PeekToken();
  while ( token == "^" )
  {
    sign = GetToken();
    gtemp.push_back( sign );

    M_bit_ANDexp();
    token = PeekToken();
  } // while
} // Rom_bit_exORexp()

// TODO: maybe_bit_AND_exp ::= maybe_equality_exp { '&' maybe_equality_exp }
void M_bit_ANDexp()
{
  string token = "";
  string sign = "";

  M_EqualityExp();
  token = PeekToken();
  while ( token == "&" )
  {
    sign = GetToken();
    gtemp.push_back( sign );

    M_EqualityExp();
    token = PeekToken();
  } // while
} // M_bit_ANDexp()

// TODO: rest_of_maybe_bit_AND_exp ::= rest_of_maybe_equality_exp { '&' maybe_equality_exp }
void Rom_bit_ANDexp()
{
  string token = "";
  string sign = "";

  Rom_EqualityExp();
  token = PeekToken();
  while ( token == "&" )
  {
    sign = GetToken();
    gtemp.push_back( sign );

    M_EqualityExp();
    token = PeekToken();
  } // while
} // Rom_bit_ANDexp()

// TODO: maybe_equality_exp ::= maybe_relational_exp { ( EQ | NEQ ) maybe_relational_exp }
void M_EqualityExp()
{
  string token = "";
  string sign = "";

  M_RelationalExp();
  token = PeekToken();
  while ( token == "==" || token == "!=" )
  {
    sign = GetToken();
    gtemp.push_back( sign );

    M_RelationalExp();
    token = PeekToken();
  } // while
} // M_EqualityExp()

// TODO: rest_of_maybe_equality_exp ::= rest_of_maybe_relational_exp { ( EQ | NEQ ) maybe_relational_exp }
void Rom_EqualityExp()
{
  string token = "";
  string sign = "";

  Rom_RelationalExp();
  token = PeekToken();
  while ( token == "==" || token == "!=" )
  {
    sign = GetToken();
    gtemp.push_back( sign );

    M_RelationalExp();
    token = PeekToken();
  } // while
} // Rom_EqualityExp()

// TODO: maybe_relational_exp ::= maybe_shift_exp { ( '<' | '>' | LE | GE ) maybe_shift_exp }
void M_RelationalExp()
{
  string token = "";
  string sign = "";

  M_ShiftExp();
  token = PeekToken();
  while ( token == "<" || token == ">" || token == "<=" || token == ">=" )
  {
    sign = GetToken();
    gtemp.push_back( sign );

    M_ShiftExp();
    token = PeekToken();
  } // while
} // M_RelationalExp()

// TODO: rest_of_maybe_relational_exp ::= rest_of_maybe_shift_exp { ( '<' | '>' | LE | GE ) maybe_shift_exp }
void Rom_RelationalExp()
{
  string token = "";
  string sign = "";

  Rom_ShiftExp();
  token = PeekToken();
  while ( token == "<" || token == ">" || token == "<=" || token == ">=" )
  {
    sign = GetToken();
    gtemp.push_back( sign );

    M_ShiftExp();
    token = PeekToken();
  } // while
} // Rom_RelationalExp()

// TODO: maybe_shift_exp ::= maybe_additive_exp { ( LS | RS ) maybe_additive_exp }
void M_ShiftExp()
{
  string token = "";
  string sign = "";

  M_AdditiveExp();
  token = PeekToken();
  while ( token == "<<" || token == ">>" )
  {
    sign = GetToken();
    gtemp.push_back( sign );

    M_AdditiveExp();
    token = PeekToken();
  } // while
} // M_ShiftExp()

// TODO: rest_of_maybe_shift_exp ::= rest_of_maybe_additive_exp { ( LS | RS ) maybe_additive_exp }
void Rom_ShiftExp()
{
  string token = "";
  string sign = "";

  Rom_AdditiveExp();
  token = PeekToken();
  while ( token == "<<" || token == ">>" )
  {
    sign = GetToken();
    gtemp.push_back( sign );

    M_AdditiveExp();
    token = PeekToken();
  } // while
} // Rom_ShiftExp()

// TODO: maybe_additive_exp ::= maybe_mult_exp { ( '+' | '-' ) maybe_mult_exp }
void M_AdditiveExp()
{
  string token = "";
  string sign = "";

  M_MULTexp();
  token = PeekToken();
  while ( token == "+" || token == "-" )
  {
    sign = GetToken();
    gtemp.push_back( sign );

    M_MULTexp();
    token = PeekToken();
  } // while
} // M_AdditiveExp()

// TODO: rest_of_maybe_additive_exp ::= rest_of_maybe_mult_exp { ( '+' | '-' ) maybe_mult_exp }
void Rom_AdditiveExp()
{
  string token = "";
  string sign = "";

  Rom_MULTexp();
  token = PeekToken();
  while ( token == "+" || token == "-" )
  {
    sign = GetToken();
    gtemp.push_back( sign );

    M_MULTexp();
    token = PeekToken();
  } // while
} // Rom_AdditiveExp()

// TODO: maybe_mult_exp ::= unary_exp rest_of_maybe_mult_exp
void M_MULTexp()
{
  UnaryExp();
  Rom_MULTexp();
} // M_MULTexp()

// TODO: rest_of_maybe_mult_exp ::= { ( '*' | '/' | '%' ) unary_exp }
void Rom_MULTexp()
{
  string token = "";
  string sign = "";

  token = PeekToken();
  while ( token == "*" || token == "/" || token == "%" )
  {
    sign = GetToken();
    gtemp.push_back( sign );

    UnaryExp();
    token = PeekToken();
  } // while
} // Rom_MULTexp()

// TODO: unary_exp ::= sign { sign } signed_unary_exp
//                   | unsigned_unary_exp
//                   | ( PP | MM ) Identifier [ '[' expression ']' ]
void UnaryExp()
{
  char ch = '\0';
  string token = "";
  string sign = "";
  string id = "";

  token = PeekToken();
  if ( Sign( token ) ) // sign { sign } signed_unary_exp
  {
    while ( Sign( token ) )
    {
      sign = GetToken();
      gtemp.push_back( sign );

      token = PeekToken();
    } // while

    Signed_UnaryExp();
  } // if
  else if ( token == "++" || token == "--" ) // ( PP | MM ) Identifier [ '[' expression ']' ]
  {
    sign = GetToken();
    gtemp.push_back( sign );

    ch = PeekChar();
    if ( ( ch < 'a' || ch > 'z' ) && ( ch < 'A' || ch > 'Z' ) ) // Error Msg. // Unexpected
    {
      token = GetToken();
      ErrorMsg( token );
    } // if

    id = GetToken();
    gtemp.push_back( id );

    if ( !DefineOrNot( id ) ) // Error Msg. // Undefine
    {
      throw new Undefined( id );
    } // if

    token = PeekToken();
    if ( token == "[" )
    {
      sign = GetToken();
      gtemp.push_back( sign );

      Exp();
      sign = GetToken();
      gtemp.push_back( sign );

      if ( sign != "]" ) // Error Msg. // Unexpected
      {
        ErrorMsg( sign );
      } // if
    } // if
  } // else if
  else // unsigned_unary_exp
  {
    Unsigned_UnaryExp();
  } // else
} // UnaryExp()

// TODO: signed_unary_exp ::= Identifier [ '(' [ actual_parameter_list ] ')' | '[' expression ']' ]
//                          | Constant
//                          | '(' expression ')'
void Signed_UnaryExp()
{
  char ch = '\0';
  string token = "";
  string sign = "";
  string id = "";
  string constant = "";

  ch = PeekChar();
  token = PeekToken();
  if ( ( ( ch >= 'a' && ch <= 'z' ) || ( ch >= 'A' && ch <= 'Z' ) ) &&
       token != "true" && token != "false" )
  { // Identifier [ '(' [ actual_parameter_list ] ')' | '[' expression ']' ]
    id = GetToken();
    gtemp.push_back( id );

    if ( !DefineOrNot( id ) ) // Error Msg. // Undefine
    {
      throw new Undefined( id );
    } // if

    token = PeekToken();
    if ( token == "(" || token == "[" )
    {
      sign = GetToken();
      gtemp.push_back( sign );

      if ( sign == "(" ) // '(' [ actual_parameter_list ] ')'
      {
        token = PeekToken();
        if ( token != ")" )
        {
          ActualParaList();
        } // if

        sign = GetToken();
        gtemp.push_back( sign );

        if ( sign != ")" ) // Error Msg. // Unexpected
        {
          ErrorMsg( sign );
        } // if
      } // if
      else // '[' expression ']'
      {
        Exp();
        sign = GetToken();
        gtemp.push_back( sign );

        if ( sign != "]" ) // Error Msg. // Unexpected
        {
          ErrorMsg( sign );
        } // if
      } // else
    } // if
  } // if
  else if ( ch == '.' || ( ch >= '0' && ch <= '9' ) ||
            ch == '\'' || ch == '\"' ||
            token == "true" || token == "false" ) // Constant
  {
    constant = GetToken();
    gtemp.push_back( constant );
  } // else if
  else if ( ch == '(' ) // '(' expression ')'
  {
    sign = GetToken();
    gtemp.push_back( sign );
    Exp();
    sign = GetToken();
    gtemp.push_back( sign );

    if ( sign != ")" ) // Error Msg. // Unexpected
    {
      ErrorMsg( sign );
    } // if
  } // else if
  else // Error Msg. // Unexpected
  {
    token = GetToken();
    ErrorMsg( token );
  } // else
} // Signed_UnaryExp()

// TODO: unsigned_unary_exp ::=
//           Identifier [ '(' [ actual_parameter_list ] ')' | [ '[' expression ']' ] [ ( PP | MM ) ] ]
//         | Constant
//         | '(' expression ')'
void Unsigned_UnaryExp()
{
  char ch = '\0';
  string token = "";
  string sign = "";
  string id = "";
  string constant = "";

  ch = PeekChar();
  token = PeekToken();

  if ( ( ( ch >= 'a' && ch <= 'z' ) || ( ch >= 'A' && ch <= 'Z' ) ) &&
       token != "true" && token != "false" )
  {
    id = GetToken();
    gtemp.push_back( id );

    if ( !DefineOrNot( id ) ) // Error Msg. // Undefine
    {
      throw new Undefined( id );
    } // if

    token = PeekToken();
    if ( token == "(" || token == "[" )
    {
      sign = GetToken();
      gtemp.push_back( sign );

      if ( sign == "(" )
      {
        token = PeekToken();
        if ( token != ")" )
        {
          ActualParaList();
        } // if

        sign = GetToken();
        gtemp.push_back( sign );
        if ( sign != ")" ) // Error Msg. // Unexpected
        {
          ErrorMsg( sign );
        } // if
      } // if
      else
      {
        Exp();
        sign = GetToken();
        gtemp.push_back( sign );

        if ( sign != "]" ) // Error Msg. // Unexpected
        {
          ErrorMsg( sign );
        } // if

        token = PeekToken();
        if ( token == "++" || token == "--" )
        {
          sign = GetToken();
          gtemp.push_back( sign );
        } // if
      } // else
    } // if
  } // if
  else if ( ch == '.' || ( ch >= '0' && ch <= '9' ) ||
            ch == '\'' || ch == '\"' ||
            token == "true" || token == "false" ) // Constant
  {
    constant = GetToken();
    gtemp.push_back( constant );
  } // else if
  else if ( ch == '(' ) // '(' expression ')'
  {
    sign = GetToken();
    gtemp.push_back( sign );

    Exp();
    sign = GetToken();
    gtemp.push_back( sign );

    if ( sign != ")" ) // Error Msg. // Unexpected
    {
      ErrorMsg( sign );
    } // if
  } // else if
  else // Error Msg. // Unexpected
  {
    token = GetToken();
    ErrorMsg( token );
  } // else
} // Unsigned_UnaryExp()

// TODO: 把暫存的input data判斷有無定義過放入/更改vector
void UpdateVector()
{
  TokenInfo ans;

  if ( gtemp[2] == "(" ) // function definition
  {
    ans.type = gtemp[0];
    ans.name = gtemp[1];
    ans.tokenValue.tokenType = FUN;
    for ( int i = 2; i < gtemp.size() ; i++ )
    {
      ans.tokenValue.functionContent.push_back( gtemp[i] );
    } // for

    if ( DefineOrNot( ans.name ) == false )
    {
      ginputData.push_back( ans );
      cout << "Definition of " << ans.name << "() entered ..." << endl;
    } // if
    else
    {
      for ( int j = 0; j < ginputData.size() ; j++ )
      {
        if ( ans.name == ginputData[j].name )
        {
          ginputData[j] = ans;
        } // if
      } // for

      cout << "New definition of " << ans.name << "() entered ..." << endl;
    } // else
  } // if
  else // declaration
  {
    ans.type = gtemp[0];
    for ( int i = 1; i < gtemp.size() ; i = i + 2 )
    {
      if ( ( i + 1 ) < gtemp.size() && gtemp[i+1] == "[" )
      {
        ans.name = gtemp[i];
        ans.arraySize = gtemp[i+2];
        i = i + 3;
      } // else if
      else
      {
        ans.name = gtemp[i];
        ans.arraySize = "";
      } // else

      if ( DefineOrNot( ans.name ) == false )
      {
        ginputData.push_back( ans );
        cout << "Definition of " << ans.name << " entered ..." << endl;
      } // if
      else
      {
        for ( int j = 0; j < ginputData.size() ; j++ )
        {
          if ( ans.name == ginputData[j].name )
          {
            ginputData[j] = ans;
          } // if
        } // for

        cout << "New definition of " << ans.name << " entered ..." << endl;
      } // else
    } // for
  } // else
} // UpdateVector()

// TODO: id has defined or not
bool DefineOrNot( string input )
{
  if ( input == "if" || input == "else" || input == "while" )
  {
    throw new Unexpected( input );
  } // if

  if ( input == "ListAllVariables" || input == "ListAllFunctions" ||
       input == "ListVariable" || input == "ListFunction" ||
       input == "Done" ) // sys. supported Function name
  {
    return true;
  } // if

  for ( int i = 0; i < gfunVar.size() ; i++ ) // local variable
  {
    if ( input == gfunVar[i].name )
    {
      return true;
    } // if
  } // for

  for ( int i = 0; i < ginputData.size() ; i++ ) // global var.
  {
    if ( input == ginputData[i].name )
    {
      return true;
    } // if
  } // for

  return false;
} // DefineOrNot()

// TODO: system-supported functions
void CheckSysFunction()
{
  if ( gtemp[0] == "Done" && gtemp[3] == ";" )
  {
    cout << "Our-C exited ..." << endl;
    exit( 0 );
  } // if
  else if ( ( gtemp[0] == "ListAllVariables" && gtemp[3] == ";" ) ||
            ( gtemp[0] == "ListAllFunctions" && gtemp[3] == ";" ) )
  {
    for ( int i = 0; i < ginputData.size() - 1 ; i++ )
    {
      for ( int j = i + 1; j < ginputData.size() ; j++ )
      {
        if ( ginputData[i].name > ginputData[j].name )
        {
          TokenInfo temp;
          temp = ginputData[i];
          ginputData[i] = ginputData[j];
          ginputData[j] = temp;
        } // if
      } // for
    } // for

    for ( int n = 0; n < ginputData.size() ; n++ )
    {
      if ( gtemp[0] == "ListAllVariables" )
      {
        if ( ginputData[n].tokenValue.tokenType != FUN )
        {
          cout << ginputData[n].name << endl;
        } // if
      } // if
      else
      {
        if ( ginputData[n].tokenValue.tokenType == FUN )
        {
          cout << ginputData[n].name << "()" << endl;
        } // if
      } // else
    } // for
  } // else if
  else if ( gtemp[0] == "ListVariable" && gtemp[4] == ";" )
  {
    for ( int i = 0; i < ginputData.size() ; i++ )
    {
      if ( gtemp[2] == "\"" + ginputData[i].name + "\"" )
      {
        cout << ginputData[i].type << " " << ginputData[i].name;

        if ( ginputData[i].arraySize != "" ) // array
        {
          cout << "[ " << ginputData[i].arraySize << " ]";
        } // if

        cout << " ;" << endl;
      } // if
    } // for
  } // else if
  else if ( gtemp[0] == "ListFunction" && gtemp[4] == ";" ) // TODO: pretty print
  {
    for ( int i = 0; i < ginputData.size() ; i++ )
    {
      if ( gtemp[2] == "\"" + ginputData[i].name + "\"" )
      {
        int indent = 0;

        cout << ginputData[i].type << " " << ginputData[i].name;
        for ( int j = 0; j < ginputData[i].tokenValue.functionContent.size() ; j++ ) // 印內容
        {
          cout << ginputData[i].tokenValue.functionContent[j];

          if ( ginputData[i].tokenValue.functionContent[j] == "{" ) // 換行 & 縮排+2
          {
            indent = indent + 2;
            cout << endl;
            for ( int x = 0; x < indent ; x++ )
            {
              cout << " ";
            } // for
          } // if
          else if ( ginputData[i].tokenValue.functionContent[j] == ";" ) // 分號換行 & 縮排
          {
            cout << endl;
            if ( ( j + 1 ) < ginputData[i].tokenValue.functionContent.size() &&
                 ginputData[i].tokenValue.functionContent[j+1] != "}" ) // 下一個不是"}"
            {
              for ( int x = 0; x < indent ; x++ )
              {
                cout << " ";
              } // for
            } // if
          } // else if
          else if ( ginputData[i].tokenValue.functionContent[j] == "}" ) // 判斷是否是do while loop
          { // FIXME: maybe會有bug
            if ( ( j + 1 ) < ginputData[i].tokenValue.functionContent.size() &&
                 ginputData[i].tokenValue.functionContent[j+1] == "while" ) // 空格
            {
              cout << " ";
            } // if
            else // 直接換行
            {
              cout << endl;
              if ( ( j + 1 ) < ginputData[i].tokenValue.functionContent.size() &&
                   ginputData[i].tokenValue.functionContent[j+1] != "}" ) // 下一個是"}" 換行 縮排-2
              {
                for ( int x = 0; x < indent ; x++ )
                {
                  cout << " ";
                } // for
              } // if
            } // else
          } // else if
          else // 空白
          {
            if ( ( j + 1 ) < ginputData[i].tokenValue.functionContent.size() &&
                 ginputData[i].tokenValue.functionContent[j+1] == "(" ) // 後面是 "(" 判斷是否是if/while 決定是否空格
            {
              if ( ginputData[i].tokenValue.functionContent[j] != "if" &&
                   ginputData[i].tokenValue.functionContent[j] != "while" )
              {
                ;
              } // if
              else
              {
                cout << " ";
              } // else
            } // if
            else if ( ( j + 1 ) < ginputData[i].tokenValue.functionContent.size() &&
                      ( ginputData[i].tokenValue.functionContent[j+1] == "[" ||
                        ginputData[i].tokenValue.functionContent[j+1] == "++" ||
                        ginputData[i].tokenValue.functionContent[j+1] == "--" ||
                        ginputData[i].tokenValue.functionContent[j+1] == "," ) ) // 後面為 "[" "++" "--" ","
            {
              ;
            } // else if
            else
            {
              cout << " ";
            } // else
          } // else

          if ( ( j + 1 ) < ginputData[i].tokenValue.functionContent.size() &&
               ginputData[i].tokenValue.functionContent[j+1] == "}" ) // 下一個是"}" 換行 縮排-2
          {
            indent = indent - 2;
            for ( int x = 0; x < indent ; x++ )
            {
              cout << " ";
            } // for
          } // if

        } // for
      } // if
    } // for
  } // else if
  else
  {
    int index = 0;

    Statement2( index ); // FIXME:
  } // else

} // CheckSysFunction()

// TODO: Error Msg. : Unexpected or Unrecognized
void ErrorMsg( string input )
{
  if ( ( input[0] < 'a' || input[0] > 'z' ) && ( input[0] < 'A' || input[0] > 'Z' ) &&
       ( input[0] < '0' || input[0] > '9' ) && input[0] != '.' &&
       input[0] != '\'' && input[0] != '\"' &&
       input[0] != '(' && input[0] != ')' &&
       input[0] != '[' && input[0] != ']' &&
       input[0] != '{' && input[0] != '}' &&
       input[0] != '+' && input[0] != '-' && input[0] != '*' && input[0] != '/' &&
       input[0] != '%' && input[0] != '^' &&
       input[0] != '>' && input[0] != '<' &&
       input[0] != '&' && input[0] != '|' && input[0] != '=' && input[0] != '!' &&
       input[0] != ';' && input[0] != ',' && input[0] != '?' && input[0] != ':' )
  {
    throw new Unrecognized( input );
  } // if
  else
  {
    throw new Unexpected( input );
  } // else
} // ErrorMsg()

// //////////          ////////// //
// ////////// 運算部分 ////////// //
// //////////          ////////// //


// TODO: statement ::= ';'
//                   | expression ';'
//                   | RETURN [ expression ] ';'
//                   | compound_statement
//                   | IF '(' expression ')' statement [ ELSE statement ]
//                   | WHILE '(' expression ')' statement
//                   | DO statement WHILE '(' expression ')' ';'
void Statement2( int &index )
{
  string token = "";
  TokenValue tempAns;

  token = gtemp[index];

  if ( token == ";" ) // the null statement
  {
    index++; // ";"
  } // if
  /*
  else if ( token == "return" ) // RETURN [ expression ] ';'
  {
    index++; // return

    if ( gtemp[index] != ";" )
    {
      Exp2( tempAns, index );
    } // if

    index++; // ";"
  } // else if
  else if ( token == "{" ) // compound statement
  {
    // Compound_Statement( tempAns, index ); // FIXME: declaration
  } // else if
  else if ( token == "if" ) // IF '(' expression ')' statement [ ELSE statement ]
  {
    index = index + 2; // if "("

    Exp2( tempAns, index );

    index++; // ")"

    Statement2( index );

    if ( gtemp[index] == "else" )
    {
      index++; // else

      Statement2( index );
    } // if
  } // else if
  else if ( token == "while" ) // WHILE '(' expression ')' statement
  {
    index = index + 2; // while "("

    Exp2( tempAns, index);

    index++; // ")"

    Statement2( index );
  } // else if
  else if ( token == "do" ) // DO statement WHILE '(' expression ')' ';'
  {
    index++; // do

    Statement2( index );

    index = index + 2; // while "("

    Exp2( tempAns,index );

    index = index + 2; // ")" ";"
  } // else if
  */
  else // expression ';'
  {
    Exp2( tempAns, index );

    index++; // ";"
  } // else
} // Statement2()

// TODO: expression ::= basic_expression { ',' basic_expression }
void Exp2( TokenValue &tempAns, int &index )
{
  TokenValue temp;

  BasicEXP2( tempAns, index );

  while ( gtemp[index] == "," )
  {
    index++; // ","

    BasicEXP2( tempAns, index );
  } // while
} // Exp2()

// TODO: basic_expression ::= Identifier rest_of_Identifier_started_basic_exp
//                          | ( PP | MM ) Identifier rest_of_PPMM_Identifier_started_basic_exp
//                          | sign { sign } signed_unary_exp romce_and_romloe
//                          | ( Constant | '(' expression ')' ) romce_and_romloe
void BasicEXP2( TokenValue &tempAns, int &index )
{
  int i = 0;
  char ch = '\0';
  TokenValue temp;

  if ( gtemp[index] == "++" || gtemp[index] == "--" )
  { // ( PP | MM ) Identifier rest_of_PPMM_Identifier_started_basic_exp
    // FIXME: ++ -- 要拿來使用ㄇ？
    index++; // "++" or "--"

    i = DefineOrNot2( gtemp[index] );
    tempAns = ginputData[i].tokenValue;
    index++; // id

    Ro_PPMM_ID_start_BasicExp2( tempAns, index );
  } // if
  else if ( Sign2( gtemp[index] ) ) // sign { sign } signed_unary_exp romce_and_romloe
  {
    int x = 1;
    bool inverse = false;

    while ( Sign2( gtemp[index] ) )
    {
      if ( gtemp[index] == "-" )
      {
        x = x * -1;
      } // if

      if ( gtemp[index] == "!" )
      {
        inverse = true;
      } // if
      else
      {
        inverse = false;
      } // else

      index++; // sign
    } // while

    Signed_UnaryExp2( tempAns, index );

    if ( tempAns.tokenType == INT )
    {
      tempAns.intValue = tempAns.intValue * x;
    } // if
    else if ( tempAns.tokenType == FLOAT )
    {
      tempAns.floatValue = tempAns.floatValue * x;
    } // else if
    else if ( tempAns.tokenType == BOOL )
    {
      if ( inverse )
      {
        tempAns.trueORfalse = !tempAns.trueORfalse;
      } // if
    } // else if

    Romce_and_Romloe2( tempAns, index );
  } // else if
  else
  {
    ch = gtemp[index][0];
    if ( ch == '.' || ( ch >= '0' && ch <= '9' ) || ch == '\'' || ch == '\"' ||
         ch == '(' || gtemp[index] == "true" || gtemp[index] == "false" )
    { // ( Constant | '(' expression ')' ) romce_and_romloe
      if ( ch == '(' )
      {
        index++; // "("

        Exp2( tempAns, index );

        index++; // ")"
      } // if
      else // Constant
      {
        if ( ch == '\'' || ch == '\"' ) // FIXME: char???
        {
          string s1 = "";

          s1 = gtemp[index];
          // 去頭去尾
          s1.erase( 0, 1 ) ;
          s1.erase( s1.length( ) - 1, s1.length( ) ) ;

          tempAns.tokenType = STRING;
          tempAns.stringValue = s1;
        } // if
        else if ( gtemp[index] == "true" || gtemp[index] == "false" )
        {
          tempAns.tokenType = BOOL;
          if ( gtemp[index] == "true" )
          {
            tempAns.trueORfalse = true;
          } // if
          else
          {
            tempAns.trueORfalse = false;
          } // else
        } // else if
        else
        {
          bool isFloat = false;
          for ( int j = 0; j < gtemp[index].size( ) ; j++ )
          {
            if ( gtemp[index][j] == '.' )
            {
              isFloat = true;
            } // if
          } // for

          if ( isFloat == false )
          {
            tempAns.tokenType = INT;
            tempAns.intValue = atoi( gtemp[index].c_str() );
          } // if
          else
          {
            tempAns.tokenType = FLOAT;
            tempAns.floatValue = atof( gtemp[index].c_str() );
          } // else
        } // else

        index++; // constant
      } // else

      Romce_and_Romloe2( tempAns, index );
    } // if
    else // Identifier rest_of_Identifier_started_basic_exp
    {
      string idName = "";

      if ( gtemp[index] == "cin" || gtemp[index] == "cout" )
      {
        tempAns.tokenType = COUT; // FIXME:
      } // if
      else
      {
        idName = gtemp[index];
        i = DefineOrNot2( idName );
        tempAns = ginputData[i].tokenValue;
      } // else

      index++; // id

      Ro_ID_start_BasicEXP2( idName, tempAns, index );
    } // else
  } // else
} // BasicEXP2()

// TODO: rest_of_Identifier_started_basic_exp ::=
//           [ '[' expression ']' ] ( assignment_operator basic_expression | [ PP | MM ] romce_and_romloe )
//         | '(' [ actual_parameter_list ] ')' romce_and_romloe
void Ro_ID_start_BasicEXP2( string idName, TokenValue &tempAns, int &index )
{
  string op = "";
  TokenValue temp;

  if ( gtemp[index] == "(" ) // '(' [ actual_parameter_list ] ')' romce_and_romloe
  {
    index++; // "("

    if ( gtemp[index] != ")" )
    {
      ActualParaList2( tempAns, index );
    } // if

    index++; // ")"

    Romce_and_Romloe2( tempAns, index );
  } // if
  else // [ '[' expression ']' ] ( assignment_operator basic_expression | [ PP | MM ] romce_and_romloe )
  {
    /*
    if ( gtemp[index] == "[" ) // [ '[' expression ']' ]
    {
      index++; // "["

      Exp2( tempAns, index );

      index++; // "]"
    } // if
    */

    if ( Assigment_Operator2( gtemp[index] ) ) // assignment_operator basic_expression
    {
      op = gtemp[index];
      index++; // assignment_operator

      BasicEXP2( temp, index );

      if ( op == "=" )
      {
        tempAns = temp;
      } // if
      else if ( op == "*=" )
      {
        Calculation( "*", tempAns, temp );
      } // else if
      else if ( op == "/=" )
      {
        Calculation( "/", tempAns, temp );
      } // else if
      else if ( op == "%=" )
      {
        Calculation( "%", tempAns, temp );
      } // else if
      else if ( op == "+=" )
      {
        Calculation( "+", tempAns, temp );
      } // else if
      else if ( op == "-=" )
      {
        Calculation( "-", tempAns, temp );
      } // else if

      for ( int i = 0; i < ginputData.size() ; i++ ) // 存回 ginputData
      {
        if ( idName == ginputData[i].name )
        {
          ginputData[i].tokenValue = tempAns;
        } // if
      }   // for
    } // if
    else // [ PP | MM ] romce_and_romloe
    {
      if ( gtemp[index] == "++" || gtemp[index] == "--" )
      {
        // ++ -- 運用？
        index++; // "++" or "--"
      } // if

      Romce_and_Romloe2( tempAns, index );
    } // else
  } // else
} // Ro_ID_start_BasicEXP2()

// TODO: rest_of_PPMM_Identifier_started_basic_exp ::= [ '[' expression ']' ] romce_and_romloe
void Ro_PPMM_ID_start_BasicExp2( TokenValue &tempAns, int &index )
{
  if ( gtemp[index] == "[" ) // '[' expression ']'
  {
    index++; // "["

    Exp2( tempAns, index );

    index++; // "]"
  } // if

  Romce_and_Romloe2( tempAns, index );
} // Ro_PPMM_ID_start_BasicExp2()

// TODO: sign ::= '+' | '-' | '!'
bool Sign2( string input )
{
  if ( input == "+" || input == "-" || input == "!" )
  {
    return true;
  } // if
  else
  {
    return false;
  } // else
} // Sign2()

// TODO: actual_parameter_list ::= basic_expression { ',' basic_expression }
void ActualParaList2( TokenValue &tempAns, int &index )
{
  BasicEXP2( tempAns, index );

  while ( gtemp[index] == "," )
  {
    index++; // ","

    BasicEXP2( tempAns, index );
  } // while
} // ActualParaList2()

// TODO: assignment_operator ::= '=' | TE | DE | RE | PE | ME
bool Assigment_Operator2( string input )
{
  if ( input == "=" || input == "*=" || input == "/=" || input == "%=" || input == "+=" || input == "-=" )
  {
    return true;
  } // if
  else
  {
    return false;
  } // else
} // Assigment_Operator2()

// TODO: rest_of_maybe_conditional_exp_and_rest_of_maybe_logical_OR_exp ::=
//           rest_of_maybe_logical_OR_exp [ '?' basic_expression ':' basic_expression ]
void Romce_and_Romloe2( TokenValue &tempAns, int &index )
{
  TokenValue temp1;
  TokenValue temp2;

  Rom_logical_ORexp2( tempAns, index );

  if ( gtemp[index] == "?" )
  {
    index++; // "?"

    BasicEXP2( temp1, index );

    index++; // ":"

    BasicEXP2( temp2, index );

    if ( tempAns.trueORfalse ) // FIXME: 假設只有 Ｔ/F
    {
      tempAns = temp1;
    } // if
    else
    {
      tempAns = temp2;
    } // else
  } // if
} // Romce_and_Romloe2()

// TODO: rest_of_maybe_logical_OR_exp ::= rest_of_maybe_logical_AND_exp { OR maybe_logical_AND_exp }
void Rom_logical_ORexp2( TokenValue &tempAns, int &index )
{
  TokenValue temp;

  Rom_logical_ANDexp2( tempAns, index );

  while ( gtemp[index] == "||" )
  {
    index++; // "||"

    M_logical_ANDexp2( temp, index );

    tempAns.trueORfalse = tempAns.trueORfalse || temp.trueORfalse; // FIXME: 假設只有 Ｔ/F
  } // while
} // Rom_logical_ORexp2()

// TODO: maybe_logical_AND_exp ::= maybe_bit_OR_exp { AND maybe_bit_OR_exp }
void M_logical_ANDexp2( TokenValue &tempAns, int &index )
{
  TokenValue temp;

  M_bit_ORexp2( tempAns, index );

  while ( gtemp[index] == "&&" )
  {
    index++;

    M_bit_ORexp2( temp, index );

    tempAns.trueORfalse = tempAns.trueORfalse && temp.trueORfalse; // FIXME: 假設只有 Ｔ/F
  } // while
} // M_logical_ANDexp2()

// TODO: rest_of_maybe_logical_AND_exp ::= rest_of_maybe_bit_OR_exp { AND maybe_bit_OR_exp }
void Rom_logical_ANDexp2( TokenValue &tempAns, int &index )
{
  TokenValue temp;

  Rom_bit_ORexp2( tempAns, index );

  while ( gtemp[index] == "&&" )
  {
    index++;

    M_bit_ORexp2( temp, index );

    tempAns.trueORfalse = tempAns.trueORfalse && temp.trueORfalse; // FIXME: 假設只有 Ｔ/F
  } // while
} // Rom_logical_ANDexp2()

// TODO: maybe_bit_OR_exp ::= maybe_bit_ex_OR_exp { '|' maybe_bit_ex_OR_exp }
void M_bit_ORexp2( TokenValue &tempAns, int &index )
{
  TokenValue temp;

  M_bit_exORexp2( tempAns, index );

  while ( gtemp[index] == "|" )
  {
    index++;

    M_bit_exORexp2( temp, index );

    // tempAns.trueORfalse = tempAns.trueORfalse | temp.trueORfalse; // FIXME: 假設只有 Ｔ/F
  } // while
} // M_bit_ORexp2()

// TODO: rest_of_maybe_bit_OR_exp ::= rest_of_maybe_bit_ex_OR_exp { '|' maybe_bit_ex_OR_exp }
void Rom_bit_ORexp2( TokenValue &tempAns, int &index )
{
  TokenValue temp;

  Rom_bit_exORexp2( tempAns, index );

  while ( gtemp[index] == "|" )
  {
    index++;

    M_bit_exORexp2( temp, index );

    // tempAns.trueORfalse = tempAns.trueORfalse | temp.trueORfalse; // FIXME: 假設只有 Ｔ/F
  } // while
} // Rom_bit_ORexp2()

// TODO: maybe_bit_ex_OR_exp ::= maybe_bit_AND_exp { '^' maybe_bit_AND_exp }
void M_bit_exORexp2( TokenValue &tempAns, int &index )
{
  TokenValue temp;

  M_bit_ANDexp2( tempAns, index );

  while ( gtemp[index] == "^" )
  {
    index++;

    M_bit_ANDexp2( temp, index );

    // tempAns.trueORfalse = tempAns.trueORfalse ^ temp.trueORfalse; // FIXME: 假設只有 Ｔ/F
  } // while
} // M_bit_exORexp2()

// TODO: rest_of_maybe_bit_ex_OR_exp ::= rest_of_maybe_bit_AND_exp { '^' maybe_bit_AND_exp }
void Rom_bit_exORexp2( TokenValue &tempAns, int &index )
{
  TokenValue temp;

  Rom_bit_ANDexp2( tempAns, index );

  while ( gtemp[index] == "^" )
  {
    index++;

    M_bit_ANDexp2( temp, index );

    // tempAns.trueORfalse = tempAns.trueORfalse ^ temp.trueORfalse;
  } // while
} // Rom_bit_exORexp2()

// TODO: maybe_bit_AND_exp ::= maybe_equality_exp { '&' maybe_equality_exp }
void M_bit_ANDexp2( TokenValue &tempAns, int &index )
{
  TokenValue temp;

  M_EqualityExp2( tempAns, index );

  while ( gtemp[index] == "&" )
  {
    index++;

    M_EqualityExp2( temp, index );

    // tempAns.trueORfalse = tempAns.trueORfalse & temp.trueORfalse; // FIXME: 假設只有 Ｔ/F
  } // while
} // M_bit_ANDexp2()

// TODO: rest_of_maybe_bit_AND_exp ::= rest_of_maybe_equality_exp { '&' maybe_equality_exp }
void Rom_bit_ANDexp2( TokenValue &tempAns, int &index )
{
  TokenValue temp;

  Rom_EqualityExp2( tempAns, index );

  while ( gtemp[index] == "&" )
  {
    index++;

    M_EqualityExp2( temp, index );

    // tempAns.trueORfalse = tempAns.trueORfalse & temp.trueORfalse; // FIXME: 假設只有 Ｔ/F
  } // while
} // Rom_bit_ANDexp2()

// TODO: maybe_equality_exp ::= maybe_relational_exp { ( EQ | NEQ ) maybe_relational_exp }
void M_EqualityExp2( TokenValue &tempAns, int &index )
{
  string sign = "";
  TokenValue temp;

  M_RelationalExp2( tempAns, index );

  while ( gtemp[index] == "==" || gtemp[index] == "!=" )
  {
    sign = gtemp[index];
    index++; // sign

    M_RelationalExp2( temp, index );

    Compare( sign, tempAns, temp );
  } // while
} // M_EqualityExp2()

// TODO: rest_of_maybe_equality_exp ::= rest_of_maybe_relational_exp { ( EQ | NEQ ) maybe_relational_exp }
void Rom_EqualityExp2( TokenValue &tempAns, int &index )
{
  string sign = "";
  TokenValue temp;

  Rom_RelationalExp2( tempAns, index );

  while ( gtemp[index] == "==" || gtemp[index] == "!=" )
  {
    sign = gtemp[index];
    index++; // sign

    M_RelationalExp2( temp, index );

    Compare( sign, tempAns, temp );
  } // while
} // Rom_EqualityExp2()

// TODO: maybe_relational_exp ::= maybe_shift_exp { ( '<' | '>' | LE | GE ) maybe_shift_exp }
void M_RelationalExp2( TokenValue &tempAns, int &index )
{
  string sign = "";
  TokenValue temp;

  M_ShiftExp2( tempAns, index );

  while ( gtemp[index] == "<" || gtemp[index] == ">" || gtemp[index] == "<=" || gtemp[index] == ">=" )
  {
    sign = gtemp[index];
    index++; // sign

    M_ShiftExp2( temp, index );

    Compare( sign, tempAns, temp );
  } // while
} // M_RelationalExp2()

// TODO: rest_of_maybe_relational_exp ::= rest_of_maybe_shift_exp { ( '<' | '>' | LE | GE ) maybe_shift_exp }
void Rom_RelationalExp2( TokenValue &tempAns, int &index )
{
  string sign = "";
  TokenValue temp;

  Rom_ShiftExp2( tempAns, index );

  while ( gtemp[index] == "<" || gtemp[index] == ">" || gtemp[index] == "<=" || gtemp[index] == ">=" )
  {
    sign = gtemp[index];
    index++; // sign

    M_ShiftExp2( temp, index );

    Compare( sign, tempAns, temp );
  } // while
} // Rom_RelationalExp2()

// TODO: maybe_shift_exp ::= maybe_additive_exp { ( LS | RS ) maybe_additive_exp }
void M_ShiftExp2( TokenValue &tempAns, int &index )
{
  string sign = "";
  TokenValue temp;

  M_AdditiveExp2( tempAns, index );

  while ( gtemp[index] == "<<" || gtemp[index] == ">>" )
  {
    sign = gtemp[index];
    index++; // LS or RS

    M_AdditiveExp2( temp, index );

    if ( tempAns.tokenType == COUT ) // cout
    {
      Output( temp );
    } // if
    else // shift
    {
      if ( sign == "<<" )
      {
        tempAns.intValue = tempAns.intValue << temp.intValue;
      } // if
      else
      {
        tempAns.intValue = tempAns.intValue >> temp.intValue;
      } // else
    } // else
  } // while
} // M_ShiftExp2()

// TODO: rest_of_maybe_shift_exp ::= rest_of_maybe_additive_exp { ( LS | RS ) maybe_additive_exp }
void Rom_ShiftExp2( TokenValue &tempAns, int &index )
{
  string sign = "";
  TokenValue temp;

  Rom_AdditiveExp2( tempAns, index );

  while ( gtemp[index] == "<<" || gtemp[index] == ">>" )
  {
    sign = gtemp[index];
    index++; // LS or RS

    M_AdditiveExp2( temp, index );

    if ( tempAns.tokenType == COUT ) // cout
    {
      Output( temp );
    } // if
    else // shift
    {
      if ( sign == "<<" )
      {
        tempAns.intValue = tempAns.intValue << temp.intValue;
      } // if
      else
      {
        tempAns.intValue = tempAns.intValue >> temp.intValue;
      } // else
    } // else

  } // while
} // Rom_ShiftExp2()

// TODO: maybe_additive_exp ::= maybe_mult_exp { ( '+' | '-' ) maybe_mult_exp }
void M_AdditiveExp2( TokenValue &tempAns, int &index )
{
  string sign = "";
  TokenValue temp;

  M_MULTexp2( tempAns, index );

  while ( gtemp[index] == "+" || gtemp[index] == "-" )
  {
    sign = gtemp[index];
    index++; // sign

    M_MULTexp2( temp, index );

    if ( tempAns.tokenType == STRING || temp.tokenType == STRING )
    {
      tempAns.tokenType = STRING;
      tempAns.stringValue = tempAns.stringValue + temp.stringValue;
    } // if
    else
    {
      Calculation( sign, tempAns, temp );
    } // else

  } // while
} // M_AdditiveExp2()

// TODO: rest_of_maybe_additive_exp ::= rest_of_maybe_mult_exp { ( '+' | '-' ) maybe_mult_exp }
void Rom_AdditiveExp2( TokenValue &tempAns, int &index )
{
  string sign = "";
  TokenValue temp;

  Rom_MULTexp2( tempAns, index );

  while ( gtemp[index] == "+" || gtemp[index] == "-" )
  {
    sign = gtemp[index];
    index++; // sign

    M_MULTexp2( temp, index );

    if ( tempAns.tokenType == STRING || temp.tokenType == STRING )
    {
      tempAns.tokenType = STRING;
      tempAns.stringValue = tempAns.stringValue + temp.stringValue;
    } // if
    else
    {
      Calculation( sign, tempAns, temp );
    } // else
  } // while
} // Rom_AdditiveExp2()

// TODO: maybe_mult_exp ::= unary_exp rest_of_maybe_mult_exp
void M_MULTexp2( TokenValue &tempAns, int &index )
{
  UnaryExp2( tempAns, index );
  Rom_MULTexp2( tempAns, index );
} // M_MULTexp2()

// TODO: rest_of_maybe_mult_exp ::= { ( '*' | '/' | '%' ) unary_exp }
void Rom_MULTexp2( TokenValue &tempAns, int &index )
{
  string sign = "";
  TokenValue temp;

  while ( gtemp[index] == "*" || gtemp[index] == "/" || gtemp[index] == "%" )
  {
    sign = gtemp[index];
    index++; // sign

    UnaryExp2( temp, index );

    Calculation( sign, tempAns, temp );
  } // while
} // Rom_MULTexp2()

// TODO: unary_exp ::= sign { sign } signed_unary_exp
//                   | unsigned_unary_exp
//                   | ( PP | MM ) Identifier [ '[' expression ']' ]
void UnaryExp2( TokenValue &tempAns, int &index )
{
  int i = 0;

  if ( Sign2( gtemp[index] ) ) // sign { sign } signed_unary_exp
  {
    int x = 1;
    bool inverse = false;

    while ( Sign2( gtemp[index] ) )
    {
      if ( gtemp[index] == "-" )
      {
        x = x * -1;
      } // if

      if ( gtemp[index] == "!" )
      {
        inverse = true;
      } // if
      else
      {
        inverse = false;
      } // else

      index++; // sign
    } // while

    Signed_UnaryExp2( tempAns, index );

    if ( tempAns.tokenType == INT )
    {
      tempAns.intValue = tempAns.intValue * x;
    } // if
    else if ( tempAns.tokenType == FLOAT )
    {
      tempAns.floatValue = tempAns.floatValue * x;
    } // else if
    else if ( tempAns.tokenType == BOOL )
    {
      if ( inverse )
      {
        tempAns.trueORfalse = !tempAns.trueORfalse;
      } // if
    } // else if

  } // if
  else if ( gtemp[index] == "++" || gtemp[index] == "--" ) // ( PP | MM ) Identifier [ '[' expression ']' ]
  {
    // FIXME: PP MM
    index++; // PP or MM

    i = DefineOrNot2( gtemp[index] );
    tempAns = ginputData[i].tokenValue;
    index++;

    if ( gtemp[index] == "[" )
    {
      index++; // "["

      Exp2( tempAns, index );

      index++; // "]"
    } // if
  } // else if
  else // unsigned_unary_exp
  {
    Unsigned_UnaryExp2( tempAns, index );
  } // else
} // UnaryExp2()

// TODO: signed_unary_exp ::= Identifier [ '(' [ actual_parameter_list ] ')' | '[' expression ']' ]
//                          | Constant
//                          | '(' expression ')'
void Signed_UnaryExp2( TokenValue &tempAns, int &index )
{
  int i = 0;
  char ch = '\0';
  string s1 = "";
  TokenValue temp;

  ch = gtemp[index][0];
  if ( ( ( ch >= 'a' && ch <= 'z' ) || ( ch >= 'A' && ch <= 'Z' ) ) &&
       gtemp[index] != "true" && gtemp[index] != "false" )
  { // Identifier [ '(' [ actual_parameter_list ] ')' | '[' expression ']' ]
    i = DefineOrNot2( gtemp[index] );
    tempAns = ginputData[i].tokenValue;
    index++; // id

    if ( gtemp[index] == "(" || gtemp[index] == "[" )
    {
      if ( gtemp[index] == "(" ) // '(' [ actual_parameter_list ] ')'
      {
        index++; // "("

        if ( gtemp[index] != ")" )
        {
          ActualParaList2( temp, index );
        } // if

        index++; // ")"
      } // if
      else // '[' expression ']'
      {
        index++; // "["

        Exp2( temp, index );

        index++; // "]"
      } // else
    } // if
  } // if
  else if ( ch == '.' || ( ch >= '0' && ch <= '9' ) ||
            ch == '\'' || ch == '\"' ||
            gtemp[index] == "true" || gtemp[index] == "false" ) // Constant
  {
    if ( ch == '\'' || ch == '\"' ) // FIXME: char???
    {
      s1 = gtemp[index];
      // 去頭去尾
      s1.erase( 0, 1 ) ;
      s1.erase( s1.length( ) - 1, s1.length( ) ) ;

      tempAns.tokenType = STRING;
      tempAns.stringValue = s1;
    } // if
    else if ( gtemp[index] == "true" || gtemp[index] == "false" )
    {
      tempAns.tokenType = BOOL;
      if ( gtemp[index] == "true" )
      {
        tempAns.trueORfalse = true;
      } // if
      else
      {
        tempAns.trueORfalse = false;
      } // else
    } // else if
    else
    {
      bool isFloat = false;
      for ( int j = 0; j < gtemp[index].size() ; j++ )
      {
        if ( gtemp[index][j] == '.' )
        {
          isFloat = true;
        } // if
      } // for

      if ( isFloat == false )
      {
        tempAns.tokenType = INT;
        tempAns.intValue = atoi( gtemp[index].c_str() );
      } // if
      else
      {
        tempAns.tokenType = FLOAT;
        tempAns.floatValue = atof( gtemp[index].c_str() );
      } // else
    } // else

    index++;
  } // else if
  else if ( ch == '(' ) // '(' expression ')'
  {
    index++; // "("

    Exp2( tempAns, index );

    index++; // "("
  } // else if

} // Signed_UnaryExp2()

// TODO: unsigned_unary_exp ::=
//           Identifier [ '(' [ actual_parameter_list ] ')' | [ '[' expression ']' ] [ ( PP | MM ) ] ]
//         | Constant
//         | '(' expression ')'
void Unsigned_UnaryExp2( TokenValue &tempAns, int &index ) // FIXME:
{
  int i = 0;
  char ch = '\0';
  string sign = "";
  string s1 = "";
  TokenValue temp;

  ch = gtemp[index][0];
  if ( gtemp[index] == "true" || gtemp[index] == "false" )
  {
    tempAns.tokenType = BOOL;
    if ( gtemp[index] == "true" )
    {
      tempAns.trueORfalse = true;
    } // if
    else
    {
      tempAns.trueORfalse = false;
    } // else

    index++;
  } // if
  else if ( ( ch >= 'a' && ch <= 'z' ) || ( ch >= 'A' && ch <= 'Z' ) )
  {
    i = DefineOrNot2( gtemp[index] );
    tempAns = ginputData[i].tokenValue;
    index++; // id

    if ( gtemp[index] == "(" || gtemp[index] == "[" )
    {
      sign = gtemp[index];
      index++; // "(" or "["

      if ( sign == "(" )
      {
        if ( gtemp[index] != ")" )
        {
          ActualParaList2( tempAns, index );
        } // if

        index++; // ")"
      } // if
      else
      {
        Exp2( temp, index );

        index++; // "]"

        if ( gtemp[index] == "++" || gtemp[index] == "--" )
        {
          // FIXME:
          index++; // "++" or "--"
        } // if
      } // else
    } // if
  } // else if
  else if ( ch == '.' || ( ch >= '0' && ch <= '9' ) ||
            ch == '\'' || ch == '\"' ) // Constant
  {
    if ( ch == '\'' || ch == '\"' ) // FIXME: char???
    {
      s1 = gtemp[index];
      // 去頭去尾
      s1.erase( 0, 1 ) ;
      s1.erase( s1.length( ) - 1, s1.length( ) ) ;

      tempAns.tokenType = STRING;
      tempAns.stringValue = s1;
    } // if
    else
    {
      bool isFloat = false;
      for ( int j = 0; j < gtemp[index].size() ; j++ )
      {
        if ( gtemp[index][j] == '.' )
        {
          isFloat = true;
        } // if
      } // for

      if ( isFloat == false )
      {
        tempAns.tokenType = INT;
        tempAns.intValue = atoi( gtemp[index].c_str() );
      } // if
      else
      {
        tempAns.tokenType = FLOAT;
        tempAns.floatValue = atof( gtemp[index].c_str() );
      } // else
    } // else

    index++;
  } // else if
  else if ( ch == '(' ) // '(' expression ')'
  {
    index++; // "("

    Exp2( tempAns, index );

    index++; // "("
  } // else if

} // Unsigned_UnaryExp2()

int DefineOrNot2( string input )
{
  /*
  if ( input == "ListAllVariables" || input == "ListAllFunctions" ||
       input == "ListVariable" || input == "ListFunction" ||
       input == "Done" ) // sys. supported Function name
  {
    return true;
  } // if
  // FIXME: 不確定是否會出現


  for ( int i = 0; i < gfunVar.size() ; i++ ) // local variable
  {
    if ( input == gfunVar[i].name )
    {
      return i;
    } // if
  } // for
  // FIXME: 暫時只考慮簡單運算
  */
  for ( int i = 0; i < ginputData.size() ; i++ ) // global var.
  {
    if ( input == ginputData[i].name )
    {
      return i;
    } // if
  } // for

  return -1;
} // DefineOrNot2()

void Compare( string sign, TokenValue &tempAns, TokenValue temp )
{
  float temp1 = 0.0;
  float temp2 = 0.0;

  if ( tempAns.tokenType == INT )
  {
    temp1 = tempAns.intValue;
  } // if
  else
  {
    temp1 = tempAns.floatValue;
  } // else

  if ( temp.tokenType == INT )
  {
    temp2 = temp.intValue;
  } // if
  else
  {
    temp2 = temp.floatValue;
  } // else

  if ( sign == "==" )
  {
    if ( temp1 == temp2 )
    {
      tempAns.trueORfalse = true;
    } // if
    else
    {
      tempAns.trueORfalse = false;
    } // else
  } // if
  else if ( sign == "!=" )
  {
    if ( temp1 != temp2 )
    {
      tempAns.trueORfalse = true;
    } // if
    else
    {
      tempAns.trueORfalse = false;
    } // else
  } // else if
  else if ( sign == "<" )
  {
    if ( temp1 < temp2 )
    {
      tempAns.trueORfalse = true;
    } // if
    else
    {
      tempAns.trueORfalse = false;
    } // else
  } // else if
  else if ( sign == ">" )
  {
    if ( temp1 > temp2 )
    {
      tempAns.trueORfalse = true;
    } // if
    else
    {
      tempAns.trueORfalse = false;
    } // else
  } // else if
  else if ( sign == "<=" )
  {
    if ( temp1 <= temp2 )
    {
      tempAns.trueORfalse = true;
    } // if
    else
    {
      tempAns.trueORfalse = false;
    } // else
  } // else if
  else if ( sign == ">=" )
  {
    if ( temp1 >= temp2 )
    {
      tempAns.trueORfalse = true;
    } // if
    else
    {
      tempAns.trueORfalse = false;
    } // else
  } // else if

  tempAns.tokenType = BOOL;
} // Compare()

// TODO: 四則運算
void Calculation( string sign, TokenValue &tempAns, TokenValue temp )
{
  if ( sign == "+" )
  {
    if ( tempAns.tokenType == INT && temp.tokenType == INT )
    {
      tempAns.tokenType = INT;
      tempAns.intValue = tempAns.intValue + temp.intValue;
    } // if // 整數運算
    else
    {
      if ( tempAns.tokenType == INT ) // 如果tempAns是int temp一定為float
      {
        tempAns.floatValue = tempAns.intValue + temp.floatValue;
        tempAns.intValue = -1;
      } // if // int + float
      else
      {
        if ( temp.tokenType == INT )
        {
          tempAns.floatValue = tempAns.floatValue + temp.intValue;
        } // if // float + int
        else
        {
          tempAns.floatValue = tempAns.floatValue + temp.floatValue;
        } // else // float + float
      } // else

      tempAns.tokenType = FLOAT;
    } // else // 小數運算
  } // if // ADD
  else if ( sign == "-" )
  {
    if ( tempAns.tokenType == INT && temp.tokenType == INT )
    {
      tempAns.tokenType = INT;
      tempAns.intValue = tempAns.intValue - temp.intValue;
    } // if // 整數運算
    else
    {
      if ( tempAns.tokenType == INT )
      {
        tempAns.floatValue = tempAns.intValue - temp.floatValue;
        tempAns.intValue = -1;
      } // if // int - float
      else
      {
        if ( temp.tokenType == INT )
        {
          tempAns.floatValue = tempAns.floatValue - temp.intValue;
        } // if // float - int
        else
        {
          tempAns.floatValue = tempAns.floatValue - temp.floatValue;
        } // else // float - float
      } // else

      tempAns.tokenType = FLOAT;
    } // else // 小數運算
  } // else if // SUB
  else if ( sign == "*" )
  {
    if ( tempAns.tokenType == INT && temp.tokenType == INT )
    {
      tempAns.tokenType = INT;
      tempAns.intValue = tempAns.intValue * temp.intValue;
    } // if // 整數運算
    else
    {
      if ( tempAns.tokenType == INT )
      {
        tempAns.floatValue = tempAns.intValue * temp.floatValue;
        tempAns.intValue = -1;
      } // if // int * float
      else
      {
        if ( temp.tokenType == INT )
        {
          tempAns.floatValue = tempAns.floatValue * temp.intValue;
        } // if // float * int
        else
        {
          tempAns.floatValue = tempAns.floatValue * temp.floatValue;
        } // else // float * float
      } // else

      tempAns.tokenType = FLOAT;
    } // else // 小數運算
  } // else if // MUL
  else if ( sign == "/" )
  {
    if ( ( temp.tokenType == INT && temp.intValue == 0 ) ||
         ( temp.tokenType == FLOAT && temp.floatValue == 0 ) )
    {
      throw new Exception( sign );
    } // if // ERROR Msg. // divide by zero

    if ( tempAns.tokenType == INT && temp.tokenType == INT )
    {
      tempAns.tokenType = INT;
      tempAns.intValue = tempAns.intValue / temp.intValue;
    } // if // 整數運算
    else
    {
      if ( tempAns.tokenType == INT )
      {
        tempAns.floatValue = tempAns.intValue / temp.floatValue;
        tempAns.intValue = -1;
      } // if // int / float
      else
      {
        if ( temp.tokenType == INT )
        {
          tempAns.floatValue = tempAns.floatValue / temp.intValue;
        } // if // float / int
        else
        {
          tempAns.floatValue = tempAns.floatValue / temp.floatValue;
        } // else // float / float
      } // else

      tempAns.tokenType = FLOAT;
    } // else // 小數運算
  } // else if // DIV
  else if ( sign == "%" )
  {
    if ( tempAns.tokenType == INT && temp.tokenType == INT )
    {
      tempAns.tokenType = INT;
      tempAns.intValue = tempAns.intValue % temp.intValue;
    } // if // 整數運算
  } // else if // 取餘數
} // Calculation()

// TODO: print answer
void Output( TokenValue ans )
{
  if ( ans.tokenType == INT )
  {
    cout << ans.intValue;
  } // if
  else if ( ans.tokenType == FLOAT )
  {
    cout << ans.floatValue;
  } // else if
  else if ( ans.tokenType == CHAR )
  {
    cout << ans.charValue;
  } // else if
  else if ( ans.tokenType == STRING )
  {
    if ( ans.stringValue == "\\n" )
    {
      cout << endl;
    } // if
    else
    {
      for ( int k = 0; k < ans.stringValue.length() ; k++ )
      {
        if ( ans.stringValue[k] == '\\' )
        {
          if ( ( ( k + 1 ) < ans.stringValue.length( ) ) && ans.stringValue[k+1] == 'n' )
          {
            cout << endl;
            k++;
          } // if
        } // if
        else
        {
          cout << ans.stringValue[k];
        } // else
      } // for
    } // else
  } // else if
  else
  {
    if ( ans.trueORfalse == true )
    {
      cout << "true";
    } // if
    else
    {
      cout << "false";
    } // else
  } // else
} // Output()
