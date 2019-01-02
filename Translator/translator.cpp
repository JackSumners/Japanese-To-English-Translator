#include<iostream>
#include<fstream>
#include<string>
#include "scanner.cpp"
#include <stdlib.h>
#include <vector>
using namespace std;

// INSTRUCTION:  copy and edit your parser.cpp to create this file.
// cp ../ParserFiles/parser.cpp .
// Complete all ** parts.
// --------------------------------------------------------

//=================================================
// File translator.cpp written by Group Number: 5
//=================================================

// ----- Changes to the parser.cpp ---------------------

// ** Declare dictionary that will hold the content of lexicon.txt
// Make sure it is easy and fast to look up the translation
// Do not change the format or content of lexicon.txt 

// ** Additions to parser.cpp here:
//    getEword - using the current lexeme, look up the English word
//               in the Lexicon if it is there -- save the result   
//               in saved_E_word
//    gen(line_type) - using the line type,
//                     sends a line of an IR to translated.txt
//                     (saved_E_word or saved_token is used)



// ** Be sure to put the name of the programmer above each function

// ** Be sure to put the corresponding grammar 
//    rule with semantic routines
//    above each non-terminal function

//================================================================



void s();
void afterSubject();
void afterNoun();
void afterObject();
void noun();
void verb();
void be();
void tense();

ofstream outFile;

string saved_lexeme;
bool  token_available = false;
token_type saved_token;

string savedEword;

//Table for translation
//Done By: Jack Sumners
vector<string> wordJ ;
vector <string> wordE ;



//Done By: Eric Fink
//Function getEword: takes the current saved lexeme and checks it aganst the translation table
void getEword()
{
  //outFile<< "GETTING EWORD USING:   "<< saved_lexeme <<endl;
  bool found = false;
  for(int a =0;a< wordJ.size(); a++)
    {
      if(wordJ[a]==saved_lexeme)
	{
	  savedEword = wordE[a];
	  found = true;
	}
    }
  if(found == false)
    {savedEword = saved_lexeme;}
  //outFile<<"new saved E word  "<< savedEword <<endl;
}


//Done By: Nick Garza
//Function gen: generates a file output based on our saved line and our token or savedEword
void gen(string line_type)
{
  if(line_type == "TENSE")
    {outFile<< line_type<< "  "<< tokenName[saved_token] <<endl;}
  else{
  outFile<< line_type<< "  "<< savedEword <<endl;
  }
}



// INSTRUCTION:  Complete all ** parts.                                                                    
// You may use any method to connect this file to scanner.cpp                                              
// that you had written.                                                                                   
// You can copy scanner.cpp here by cp ../ScannerFiles/scanner.cpp .                                       
// -----------------------------------------------------                                                   

//=================================================                                                        
// File parser.cpp written by Group Number: 5                                                              
//=================================================                                                        

// ----- Utility and Globals -----------------------------------  

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
      outFile<<endl;
      s();
    }
  cout<<"\nSuccessfully parsed story"<<endl;
}

//Grammar:<s> ::= [CONNECTOR #getEword# #gen("CONNECTOR")]<noun> #getEword# SUBJECT #gen("ACTOR")<after subject>                       
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
	  getEword();
	  gen("CONNECTOR");
	}
  
      noun();
      match(SUBJECT);
      gen("ACTOR");
      afterSubject();
  

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
      getEword();
      break;
    case  PRONOUN:
      match(PRONOUN);
      getEword();
      break;
    default:
      syntax_error2(saved_lexeme, "noun");  // none of the alternatives found                                                                                                                            
    }
}

//Grammar: <after subject> ::= <verb> #getEword# #gen("ACTION")# <tense> #gen("TENSE")# PERIOD | <noun> #getEword# <after noun>   
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
      getEword();
      gen("ACTION");
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
  //outFile<< "Before Desc:   "<< savedEword <<endl;
  gen("DESCRIPTION");
  switch(next_token())  // look ahead at next token                                         
    {
    case  IS:
      match(IS);
      //   gen("DESCRIPTION");
      gen("TENSE");
      break;
    case  WAS:
      match(WAS);
      // gen("DESCRIPTION");
      gen("TENSE");
      break;
    default:
      syntax_error2(saved_lexeme, "be");  // none of the alternatives found                
    }
}



//Grammar:<after noun> ::= <be> #gen("DESCRIPTION")# #gen("TENSE")# PERIOD  | DESTINATION #gen("TO")#<verb> #getEword# #gen("ACTION")# <tense> #gen("Tense")# PERIOD | OBJECT #gen("OBJECT")# <after object>
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
      gen("TO");
      verb();
      tense();
      match(PERIOD);
      break;
    case OBJECT:
      match(OBJECT);
      gen("OBJECT");
      afterObject();
      break;
    default:
      syntax_error2(saved_lexeme, "afterNoun");  // none of the alternatives found                
    }
  
}

//Grammar:<after object> ::= <verb> #getEword# #gen("ACTION")#<tense> #gen("TENSE")# PERIOD | <noun> #getEword# DESTINATION #gen("TO")# <verb> #getEword# #gen("ACTION")# <tense> #gen("TENSE")# PERIOD
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
      gen("TO");
      verb();
      tense();
      match(PERIOD);
      break;
    case PRONOUN:
      noun();
      match(DESTINATION);
      gen("TO");
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
      gen("TENSE");
      break;
    case  VERBPASTNEG:
      match(VERBPASTNEG);
      gen("TENSE");
      break;
    case  VERB:
      match(VERB);
      gen("TENSE");
      break;
    case  VERBNEG:
      match(VERBNEG);
      gen("TENSE");
      break;
    default:
      syntax_error2(saved_lexeme, "tense");  // none of the alternatives found                                                              
    }
}








// -------------------------------------------

// The final test driver to start the translator
// Done by  **
int main()
{
  //** opens the lexicon.txt file and reads it in
  ifstream input;
  string tJ;
  string tE;
  input.open("lexicon.txt");
  cout<<"opening file"<<endl;
  while(input)
    {
      
      input>> tJ;
      input>> tE;
      wordJ.push_back(tJ);
      wordE.push_back(tE);
    }



  input.close();
  //** closes lexicon.txt 

  //** opens the output file translated.txt
  
  outFile.open("translated.txt");

  string filename;
  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());

  //** calls the <story> to start parsing
  story();
  //** closes the input file 
  fin.close();
  //** closes translated.txt
  outFile.close();
}// end



