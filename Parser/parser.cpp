#include<iostream>
#include<fstream>
#include<string>
#include "scanner.cpp"
#include <stdlib.h>
using namespace std;

// INSTRUCTION:  Complete all ** parts.
// You may use any method to connect this file to scanner.cpp
// that you had written.  
// You can copy scanner.cpp here by cp ../ScannerFiles/scanner.cpp .
// -----------------------------------------------------

//=================================================
// File parser.cpp written by Group Number: 5
//=================================================

// ----- Utility and Globals -----------------------------------

void s();
void afterSubject();
void afterNoun();
void afterObject();
void noun();
void verb();
void be();
void tense();

string saved_lexeme;
bool  token_available = false;
token_type saved_token;
// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
// ** Be sure to put the name of the programmer above each function
// i.e. Done by:

//Done By: Nick Garza
void syntax_error1(token_type expected, string saved_lexeme)
{
  cout<<"SYNTAX ERROR: expected "<< tokenName[expected]  << " but found "<<  saved_lexeme <<endl;
  exit (1); //halting
}

//Done By: Nick Garza
void syntax_error2(string saved_lexeme, string parserFunct)
{
  cout<<"SYNTAX ERROR: unexpected "<< saved_lexeme << " found in "<< parserFunct <<endl;
  exit (1); //halting
}

// ** Need the updated match and next_token (with 2 global vars)
// ** Be sure to put the name of the programmer above each function
// i.e. Done by:


//Done By: Eric Fink
token_type next_token()
{
  
  if (!token_available)   // if there is no saved token yet                                                  
    {
      scanner(saved_token, saved_lexeme);  // call scanner to grab a new token              
      cout<<"Scanner called using word: "<< saved_lexeme <<endl;
      token_available = true;                              // mark that fact that you have saved it          
    }
    return saved_token;    // return the saved token                                                           
}



//Done By: Eric Fink
bool match(token_type expected)
{
  if (next_token() != expected)  // mismatch has occurred with the next token
    {
      syntax_error1(expected, saved_lexeme);// calls a syntax error function here to  generate a syntax error message here and do recovery
     
    }
  else  // match has occurred
    { 
      cout<<"Matched "<< tokenName[expected] <<endl; //print the matched token type, when successful
      token_available = false;  // eat up the token
      return true;              // say there was a match
    }
}



// ----- RDP functions - one per non-term -------------------

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// i.e. Grammar: 
// ** Be sure to put the name of the programmer above each function
// i.e. Done by:


//Grammar:<story> ::= <s>{<s>}
//Done By: Jack Sumners
void story()
{
  cout<<"Processing <story>"<<endl;
  s();
  //while()  call more s()
  while (true && (saved_lexeme != "eofm"))  
    {
      s();
    }
  cout<<"\nSuccessfully parsed story"<<endl;
}

//Grammar:<s> ::= [CONNECTOR]<noun>SUBJECT<after subject>                       
//Done By: Jack Sumners  
void s()
{
  next_token();
  if(saved_lexeme != "eofm")
    {

      cout<<"Processing <s>"<<endl;

  
  if(next_token() == CONNECTOR)
    {
      match(CONNECTOR);
    }
  
  noun();
  match(SUBJECT);
  afterSubject();
  
  //orginal code, works but doesnt give right error funct.
  /* 
  switch(next_token())  // look ahead at next token                                                   
    {
    case  WORD1:
      noun();
      match(SUBJECT);
      afterSubject();
      break;
    case  PRONOUN:
      noun();
      match(SUBJECT);
      afterSubject();
      break;
    default:
      syntax_error2(saved_lexeme, "s");  // none of the alternatives found                                                     
      }*/
    }

}

//Grammar:<noun> ::= WORD1|PRONOUN
//Done By: Jack Sumners
void noun()
{
  cout<<"Processing <noun>"<<endl;
  switch(next_token())  // look ahead at next token                                                                        
    {
    case  WORD1:
      match(WORD1);
      break;
    case  PRONOUN:
      match(PRONOUN);
      break;
    default:
      syntax_error2(saved_lexeme, "noun");  // none of the alternatives found                                                                                                                            
    }
}

//Grammar: <after subject> ::= <verb> <tense> PERIOD | <noun> <after noun>   
//Done By: Eric Fink
void afterSubject()
{
  cout<<"Processing <afterSubject>"<<endl;
  
  switch(next_token())  // look ahead at next token                                          
      {
    case  WORD2:
      verb();
      tense();
      match(PERIOD);
      break;
    case  WORD1:
      noun();
      afterNoun();
      break;
    case PRONOUN:
      noun();
      afterNoun();
      break;
    default:
      syntax_error2(saved_lexeme, "afterSubject");  // none of the alternatives found    
      }
}


//Grammar: <verb> ::= WORD2
//Done By: Eric Fink
void verb()
{
  cout<<"Processing <verb>"<<endl;

  switch(next_token())  // look ahead at next token                                                                                                             
    {
    case  WORD2:
      match(WORD2);
      break;
    default:
      syntax_error2(saved_lexeme, "verb");  // none of the alternatives found                         
    }
}

//Grammar: <be> ::= IS | WAS
//Done By: Eric Fink
void be()
{
  cout<<"Processing <be>"<<endl;
  
  switch(next_token())  // look ahead at next token                                         
    {
    case  IS:
      match(IS);
      break;
    case  WAS:
      match(WAS);
      break;
    default:
      syntax_error2(saved_lexeme, "be");  // none of the alternatives found                
    }
}



//Grammar:<after noun> ::= <be> PERIOD  | DESTINATION <verb> <tense> PERIOD | OBJECT  <after object>
//Done By: Nick Garza
void afterNoun()
{
  cout<<"Processing <afterNoun>"<<endl;

  
  switch(next_token())  // look ahead at next token       
    {
    case  IS:
      be();
      match(PERIOD);
      break;
    case  WAS:
      be();
      match(PERIOD);
      break;
    case DESTINATION:
      match(DESTINATION);
      verb();
      tense();
      match(PERIOD);
      break;
    case OBJECT:
      match(OBJECT);
      afterObject();
      break;
    default:
      syntax_error2(saved_lexeme, "afterNoun");  // none of the alternatives found                
    }
  
}

//Grammar:<after object> ::= <verb><tense> PERIOD | <noun>DESTINATION <verb> <tense> PERIOD
//Done By: Nick Garza 
void afterObject()
{
  cout<<"Processing <afterObject>"<<endl;
  
  switch(next_token())
    {
    case WORD2:
      verb();
      tense();
      match(PERIOD);
      break;
    case WORD1:
      noun();
      match(DESTINATION);
      verb();
      tense();
      match(PERIOD);
      break;
    case PRONOUN:
      noun();
      match(DESTINATION);
      verb();
      tense();
      match(PERIOD);
      break;
    default:
      syntax_error2(saved_lexeme, "afterObject");  // none of the alternatives found    
    }
}


//Grammar: <tense> ::= VERBPAST | VERBPASTNEG | VERB | VERBNEG
//Done By: Nick Garza
void tense()
{
  cout<<"Processing <tense>"<<endl;

  switch(next_token())  // look ahead at next token                                                                    
    {
    case  VERBPAST:
      match(VERBPAST);
      break;
    case  VERBPASTNEG:
      match(VERBPASTNEG);
      break;
    case  VERB:
      match(VERB);
      break;
    case  VERBNEG:
      match(VERBNEG);
      break;
    default:
      syntax_error2(saved_lexeme, "tense");  // none of the alternatives found                                                              
    }
}




//---------------------------------------

// The new test driver to start the parser
// Done by: Jack Sumners
int main()
{
  string filename;
  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());

 
  //** calls the <story> to start parsing
   story();
  //** closes the input file 
   fin.close();
}// end
//** require no other input files!
//** syntax error EC requires producing errors.text of messages

