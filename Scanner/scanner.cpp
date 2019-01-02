#include<iostream>
#include<fstream>
#include<string>
using namespace std;

//Q0 = 0
//Qcon1 = 1
//Q0' = 2
//Qcon = 3
//QS = 4
//QT = 5
//QC = 6

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

  int state =0;
  int charpos = 0;

  while (s[charpos] != '\0')
    {
      // cout<<" [  " << s[charpos] <<"  ] Start State: "<< state;
      

//** q0 STATE **                                                                                                                                                                                           
      if (state == 0 && (s[charpos] == 'b' || s[charpos] == 'g' || s[charpos] == 'h' || s[charpos] == 'k' || s[charpos] == 'm' || s[charpos] == 'n' || s[charpos] == 'p' || s[charpos] == 'r') )
        {state = 1;}
      else if(state == 0 && (s[charpos] == 'a' || s[charpos] == 'i' || s[charpos] == 'u' || s[charpos] == 'e' || s[charpos] == 'o' || s[charpos] == 'I' || s[charpos] == 'E'))
        { state = 2;}
      else if(state == 0 && (s[charpos] == 'd' || s[charpos] == 'j' || s[charpos] == 'w' || s[charpos] == 'y' || s[charpos] == 'z'))
        { state = 3;}
      else if(state == 0 && s[charpos] == 's')
        { state = 4;}
	  else if(state == 0 && s[charpos] == 't')
		{ state = 5;}
	  else if(state == 0 && s[charpos] == 'c')
	    { state = 6;}
	  else
	     { //** Qcon1 STATE **                                                                                                                                                                                     
		  if (state == 1 && (s[charpos] == 'a' || s[charpos] == 'i' || s[charpos] == 'u' || s[charpos] == 'e' || s[charpos] == 'o' || s[charpos] == 'I' || s[charpos] == 'E'))
		  {state = 2;}
		  else if(state == 1 && s[charpos] == 'y')
		  { state = 3;}
		  else
		    { //** Q0' STATE **                                                                                                                                                                                         
              if(state == 2 && s[charpos] == 'n')
				{ state = 0; }
     		  else if (state == 2 && (s[charpos] == 'b' || s[charpos] == 'g' || s[charpos] == 'h' || s[charpos] == 'k' || s[charpos] == 'm' || s[charpos] == 'n' || s[charpos] == 'p' || s[charpos] == 'r') )
				{state = 3;}
		      else if(state == 2 && (s[charpos] == 'a' || s[charpos] == 'i' || s[charpos] == 'u' || s[charpos] == 'e' || s[charpos] == 'o' || s[charpos] == 'I' || s[charpos] == 'E'))
				{ state = 2;}
		      else if(state == 2 && (s[charpos] == 'd' || s[charpos] == 'j' || s[charpos] == 'w' || s[charpos] == 'y' || s[charpos] == 'z'))
				{ state = 3;}
		      else if(state == 2 && s[charpos] == 's')
				{ state = 4;}
			  else if(state == 2 && s[charpos] == 't')
				{ state = 5;}
			  else if(state == 2 && s[charpos] == 'c')
			    { state = 6;}
			  else
				{ //** Qcon STATE **                                                                                                                                                                         
				  if(state == 3 && (s[charpos] == 'a' || s[charpos] == 'i' || s[charpos] == 'u' || s[charpos] == 'e' || s[charpos] == 'o' || s[charpos] == 'I' || s[charpos] == 'E'))
				    { state = 2;}
				  else
				    { //** QS STATE **                                                                                                                                                                          
				      if(state == 4 && (s[charpos] == 'a' || s[charpos] == 'i' || s[charpos] == 'u' || s[charpos] == 'e' || s[charpos] == 'o' || s[charpos] == 'I' || s[charpos] == 'E'))
					  { state = 2;}
				      else if(state == 4 && s[charpos] == 'h')
					  { state = 3;}
					  else
					  { //** QT STATE **                                                                                                                                                                      
					    if(state == 5 && (s[charpos] == 'a' || s[charpos] == 'i' || s[charpos] == 'u' || s[charpos] == 'e' || s[charpos] == 'o' || s[charpos] == 'I' || s[charpos] == 'E'))
					      { state = 2;}
					    else if(state == 5 && s[charpos] == 's')
					      { state = 3;}
					    else
						  { //** QC STATE **                                                                                                                                                                  
							if(state == 6 && s[charpos] == 'h')
						      { state = 3;}
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
  if (state == 0 || state == 2) 
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
enum tokentype { WORD1, WORD2, PERIOD, ERROR, VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS, WAS, OBJECT, SUBJECT, DESTINATION, PRONOUN, CONNECTOR };
//word1, word2, in above enum                                                                                                                                                  
string tokenName[30] = { "WORD1", "WORD2", "PERIOD", "ERROR", "VERB", "VERBNEG","VERBPAST","VERBPASTNEG","IS","WAS", "OBJECT", "SUBJECT","DESTINATION", "PRONOUN", "CONNECTOR" };

// ** Need the reservedwords table to be set up here.                                                                                                                          
// ** Do not require any file input for this.                                                                                                                                  
// ** a.out should work without any additional files.                                                                                                                          
struct reserved
{
  const char* string;
  tokentype tokenT;
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
int scanner(tokentype& a, string& w)
{
	// ** Grab the next word from the file via fin
       
	fin >> w;

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

        cout<<"\n";

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

