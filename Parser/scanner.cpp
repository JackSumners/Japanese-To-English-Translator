#include<iostream>
#include<fstream>
#include<string>
using namespace std;

//=====================================================
// File scanner.cpp written by: Group Number: 5
//=====================================================

// --------- DFAs ---------------------------------

// ** MYTOKEN DFA to be replaced by the WORD DFA
// ** Done by: Jack Sumners
// ** RE:  
bool mytoken(string s)
{
  //cout<<"Word: "<< s ;
  //cout<<"\n";

  string state ="Q0";
  int charpos = 0;

  while (s[charpos] != '\0')
    {
      // cout<<" [  " << s[charpos] <<"  ] Start State: "<< state;
      

//** q0 STATE **                                                                                                                                                                                           
      if (state == "Q0" && (s[charpos] == 'b' || s[charpos] == 'g' || s[charpos] == 'h' || s[charpos] == 'k' || s[charpos] == 'm' || s[charpos] == 'n' || s[charpos] == 'p' || s[charpos] == 'r') )
        {state = "Qcon1";}
      else if(state == "Q0" && (s[charpos] == 'a' || s[charpos] == 'i' || s[charpos] == 'u' || s[charpos] == 'e' || s[charpos] == 'o' || s[charpos] == 'I' || s[charpos] == 'E'))
        { state = "Q0'";}
      else if(state == "Q0" && (s[charpos] == 'd' || s[charpos] == 'j' || s[charpos] == 'w' || s[charpos] == 'y' || s[charpos] == 'z'))
        { state = "Qcon";}
      else if(state == "Q0" && s[charpos] == 's')
        { state = "QS";}
	  else if(state == "Q0" && s[charpos] == 't')
		{ state = "QT";}
	  else if(state == "Q0" && s[charpos] == 'c')
	    { state = "QC";}
	  else
	     { //** Qcon1 STATE **                                                                                                                                                                                     
		  if (state == "Qcon1" && (s[charpos] == 'a' || s[charpos] == 'i' || s[charpos] == 'u' || s[charpos] == 'e' || s[charpos] == 'o' || s[charpos] == 'I' || s[charpos] == 'E'))
		  {state = "Q0'";}
		  else if(state == "Qcon1" && s[charpos] == 'y')
		  { state = "Qcon";}
		  else
		    { //** Q0' STATE **                                                                                                                                                                                         
              if(state == "Q0'" && s[charpos] == 'n')
				{ state = "Q0"; }
     		  else if (state == "Q0'" && (s[charpos] == 'b' || s[charpos] == 'g' || s[charpos] == 'h' || s[charpos] == 'k' || s[charpos] == 'm' || s[charpos] == 'n' || s[charpos] == 'p' || s[charpos] == 'r') )
				{state = "Qcon";}
		      else if(state == "Q0'" && (s[charpos] == 'a' || s[charpos] == 'i' || s[charpos] == 'u' || s[charpos] == 'e' || s[charpos] == 'o' || s[charpos] == 'I' || s[charpos] == 'E'))
				{ state = "Q0'";}
		      else if(state == "Q0'" && (s[charpos] == 'd' || s[charpos] == 'j' || s[charpos] == 'w' || s[charpos] == 'y' || s[charpos] == 'z'))
				{ state = "Qcon";}
		      else if(state == "Q0'" && s[charpos] == 's')
				{ state = "QS";}
			  else if(state == "Q0'" && s[charpos] == 't')
				{ state = "QT";}
			  else if(state == "Q0'" && s[charpos] == 'c')
			    { state = "QC";}
			  else
				{ //** Qcon STATE **                                                                                                                                                                         
				  if(state == "Qcon" && (s[charpos] == 'a' || s[charpos] == 'i' || s[charpos] == 'u' || s[charpos] == 'e' || s[charpos] == 'o' || s[charpos] == 'I' || s[charpos] == 'E'))
				    { state = "Q0'";}
				  else
				    { //** QS STATE **                                                                                                                                                                          
				      if(state == "QS" && (s[charpos] == 'a' || s[charpos] == 'i' || s[charpos] == 'u' || s[charpos] == 'e' || s[charpos] == 'o' || s[charpos] == 'I' || s[charpos] == 'E'))
					  { state = "Q0'";}
				      else if(state == "QS" && s[charpos] == 'h')
					  { state = "Qcon";}
					  else
					  { //** QT STATE **                                                                                                                                                                      
					    if(state == "QT" && (s[charpos] == 'a' || s[charpos] == 'i' || s[charpos] == 'u' || s[charpos] == 'e' || s[charpos] == 'o' || s[charpos] == 'I' || s[charpos] == 'E'))
					      { state = "Q0'";}
					    else if(state == "QT" && s[charpos] == 's')
					      { state = "Qcon";}
					    else
						  { //** QC STATE **                                                                                                                                                                  
							if(state == "QC" && s[charpos] == 'h')
						      { state = "Qcon";}
						    else
						      { //cout<<"no token found!"<<endl;
							  return false;}
						  }
					  }
				  }
			    }
		    }
	     }
      
                //cout<< " || end state: " <<state<<endl;

	charpos++;

    }//end of while                                                                                                                                                                                           

	// where did I end up????                                                                                                                                                                                   
  if (state == "Q0" || state == "Q0'") 
  {
    // cout <<"We did it"<<endl; 
	  return true;
  }
  return false;
}


// ** Add the PERIOD DFA here 

bool periodtoken(string s)
{
	int state = 0;
	int charpos = 0;

	//checks each character of the word to test if is a expression of a single period "."
	while (s[charpos] != '\0')
	{
		if (state == 0 && s[charpos] == '.')
			state = 1;
		else
			return(false);

		++charpos;
	}

	if (state == 1) return(true);
	else return(false);
}
                                                                                                                                                 
// ** Done by: Nicholas Garza-Elsperger                                                                                                                                        

// -----  Tables -------------------------------------  
// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, etc.                                                                                                             
// Feel free to add a tokentype for the end-of-file marker.                                                                                                                    
enum token_type { WORD1, WORD2, PERIOD, ERROR, VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS, WAS, OBJECT, SUBJECT, DESTINATION, PRONOUN, CONNECTOR };
//word1, word2, in above enum                                                                                                                                                  
string tokenName[30] = { "WORD1", "WORD2", "PERIOD", "ERROR", "VERB", "VERBNEG","VERBPAST","VERBPASTNEG","IS","WAS", "OBJECT", "SUBJECT","DESTINATION", "PRONOUN", "CONNECTOR" };

// ** Need the reservedwords table to be set up here.                                                                                                                          
// ** Do not require any file input for this.                                                                                                                                  
// ** a.out should work without any additional files.                                                                                                                          
struct reserved
{
  const char* string;
  token_type tokenT;
}

//reserved table including string and tokentypes

reserved[] = {
  { "masu",VERB},
  {"masen",VERBNEG},
  {"mashita",VERBPAST},
  {"masendeshita",VERBPASTNEG},
  {"desu",IS},
  {"deshita",WAS},
  {"o", OBJECT},
  {"wa", SUBJECT},
  {"ni", DESTINATION},
  {"watashi",PRONOUN},
  {"anata",PRONOUN},
  {"kare",PRONOUN},
  {"kanojo", PRONOUN},
  {"sore", PRONOUN},
  {"mata",CONNECTOR},
  {"soshite", CONNECTOR},
  {"shikashi", CONNECTOR},
  { "dakara", CONNECTOR}
};

// ------------ Scaner and Driver ----------------------- 

ifstream fin;  // global stream for reading from the input file

// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
// ** Done by: Eric Fink
int scanner(token_type& a, string& w)
{
	// ** Grab the next word from the file via fin
       
        fin >> w;
	
	//SNANNER.CPP SOLO USES: fin >> w;
	//SCANNER.CPP w/ Parser USES: non fin, call from parser

  /* 
  2. Call the token functions one after another (if-then-else)
     And generate a lexical error message if both DFAs failed.
     Let the token_type be ERROR in that case.
  3. Make sure WORDs are checked against the reservedwords list
     If not reserved, token_type is WORD1 or WORD2.

  4. Return the token type & string  (pass by reference)
  */
     


	int rowCount = sizeof reserved/ sizeof reserved[0];
	//cout<<"Row Count"<< rowCount <<endl;

        //cout<<"\n";

	if(mytoken(w)) //checking step 2, part 1
	  {
	    for (int i = 0; i < rowCount; i++)
		{
		  if (w == reserved[i].string) //checking step 3, part 1
			{
			        //cout << "Word is reserved.\n";
				//cout << "token_type: " << reserved[i][1] << endl;
				a = reserved[i].tokenT;
				return 0;
			}
		}
	    
	    char lastLetter = ' ';
	      lastLetter = w[(w.length()-1)];

	      //checking step 3, part 2
	    if (lastLetter == 'I' || lastLetter == 'E')
	      {
		//cout << "token_type: WORD2\n";
		a = WORD2;
	      }
	    else
	      {
		//cout << "token_type: WORD1\n";
		a = WORD1;
	      }




	}
	else if(periodtoken(w)) //checking step 2, part 2
	  {
	    //cout<<"token_type: PERIOD\n";
	    a = PERIOD;
	  }
	else if(w == "eofm")
	  { //do nothing
	  }
	else
	  {
	    cout << "LEXICAL ERROR: "<< w <<" is not a valid token \n";
	    a = ERROR;
	  }


	return 0;
}//the end of scanner



// The temporary test driver to just call the scanner repeatedly  
// This will go away after this assignment
// DO NOT CHANGE THIS!!!!!! 
// Done by:  Rika

/***USED BY PARSER
int main()
{
  tokentype thetype;
  string theword; 
  string filename;

  cout << "Enter the input file name: ";
  cin >> filename;

  fin.open(filename.c_str());

  // the loop continues until eofm is returned.
   while (true)
    {
       scanner(thetype, theword);  // call the scanner
       if (theword == "eofm") break;  // stop now

       cout << "Type is:" << tokenName[thetype] << endl;
       cout << "Word is:" << theword << endl;   
    }

   cout << "End of file is encountered." << endl;
   fin.close();

}// end

*********/
 //USED BY PARSER
