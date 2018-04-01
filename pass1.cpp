
#include <iostream>
#include <fstream> 
#include <string>
#include <map>


using namespace std ; 




#include "hexadecimal.cpp"
#include "hashtables.cpp"







// Boolean method for checking whitespaces in a given line

bool checkWhiteSpace(char a) {
	if(a==' ')
		return true ; 
	if(a=='\t')
		return true ; 
	return false ; 
}







// Helper method to split a given line by whitespaces 

void getTokens (string line , string word[] , int& count){

int i ; 

//Initializaing the word ; 
for (int i = 0 ; i<5 ; i++){
	word[i] = ""; 
}

count = 0 ; 
i = 0 ; 

while(checkWhiteSpace(line[i])&& i<line.length()){
	++i ; 
	continue ;
}
//Comment Detected
if(i==line.length()|| line[i]=='.')
return ; 

	for( ; i<line.length() ; ){

 		while(checkWhiteSpace(line[i])&&i<line.length()) 
 			{++i;continue;}

        	if(i==line.length())
        	 break;

        	for(; !checkWhiteSpace(line[i]) && i<line.length() ; ++i) word[count]+=line[i];
        	++count;
	}
}





// Some GLobal Variables

ifstream inFile ; 
ofstream outFile ; 
ofstream errorFile ; 

int block_number ; 
int line ; 
string current_block ; 
string LOCCTR ; 
bool error_flag = 0 ;



// Creating tables and opening files

void open(){
	create() ; 
	inFile.open("input.txt");
	outFile.open("interm.txt");
	outFile.open("error.txt");
}


void makepass (string[] , int) ; 

void run(){

	open() ; 
	string s ; 
	string word[5] ; 
	int count =  0 ; 
	line = 5 ; 
	getline(inFile , s) ; 
	char ch ; 

	getTokens(s , word , count);

	//while(count==0){

	//}
	LOCCTR = "0" ; 
	BLOCK["DEFAULT"].num = 0 ;
	BLOCK["DEFAULT"].address = LOCCTR ;  
	BLOCK["DEFAULT"].length = "0" ; 
	BLOCK["DEFAULT"].exist = 'y' ; 


	current_block = "DEFAULT" ; 
	block_number = 1 ; 
	line = 5 ; 


	if(word[0]=="START"){

		LOCCTR = word[1] ; 
		outFile << line<<"\n" ; 
		outFile << "START"<<"\n" ; 
		outFile <<LOCCTR <<"\n" ; 
		outFile <<LOCCTR <<"\n" ;
		outFile<<""<<endl ; 
		cout<<"0 is start"<<"\n" ;
	}

	else if(word[1]=="START"){

		LOCCTR = word[2] ; 
		outFile << line<<"\n";
		outFile << word[0]<<"\n" ; 
		outFile << "START"<<"\n" ; 
		outFile << LOCCTR<<"\n" ; 
		outFile << LOCCTR<<"\n" ; 
		outFile << ""<<"\n" ; 
		cout<<"1 is start"<<"\n" ; 


	else
		execute(word , count) ; 

	while(true){


		getline(inFile , s) ; 
		getTokens(s , word , count ; );
		line+=5 ; 
		cout<<"s: "<<s<<endl;
		outFile << line << "\n" ; 


		if(count == 0 ){
			cout<<"A comment is present here"<<"\n" ; 
			outFile<<"$"<<"\n" ;
			outFile<<s<<"\n" ; 
			outFile<<""<<endl;
            outFile<<""<<endl;
            outFile<<""<<endl;
            continue ; 
        }

        if(word[0]=="END"){
        	BLOCK[current_block].length = LOCCTR ; 
        	outFile<<""<<"\n" ; 
        	outFile<< word[0]<<"\n" ; 
        	outFile<< word[1]<<"\n" ;
        	outFile<<LOCCTR<<"\n";
            outFile<<"" << "\n" ;
            break;
		}

		makepass(word , count) ; 
	}
 
 	// hexa addr,len;
  //    string temp=find_block(0);
  //    addr=BLOCK[temp].address;
  //    len=BLOCK[temp].length;
  //    for(int i=1;i<block_num;++i)
  //    {
  //           temp=find_block(i);
  //           BLOCK[temp].address=toHex(toDec(addr)+toDec(len));
  //           addr=BLOCK[temp].address;
  //           len=BLOCK[temp].length;

  //    }



}

void makepass(strign word[] , int count){

	cout<<"word[0]: "<<word[0]<<" LOCCTR: "<<LOCCTR<<"\n";

	if(word[0]=="USE"){
		cout<<"USE"<<"\n";	
		BLOCK[current_block].length = LOCCTR ; 

		// Checking whether the use is of the defaut block or other.
		if(word[1]==""){

			// Set the current block to default block
			current_block = "DEFAULT" ; 
			LOCCTR = BLOCK["DEFAULT"].length ;
		
		}
		// Checking whether the block with the givenname exists or not 
		else if (BLOCK[word[1]].exist=='y'){
			// if block exists then update current block and block length ; 
			current_block = word[1] ; 
			LOCCTR = BLOCK[word[1]].length ; 

		}

		else{

			BLOCK[word[1]].num = block_number ; 
			BLOCK[word[1]].exist = 'y' ; 
			BLOCK[word[1]].length = '0' ; 
			current_block = word[1] ; 
			LOCCTR = "0" ; 
			++block_number ; 

		}

		outFile<<""<<endl;
        outFile<<word[0]<<endl;
        outFile<<word[1]<<endl;
        outFile<<LOCCTR<<endl;
        outFile<< "" <<endl;
        
        return;

	}

	if(word[0][0] == '+'){
		cout<<"Format 4 instruction detected" ; 
		 fout1<<""<<endl;
        outFile<<word[0]<<"\n";
        outFile<< word[1] <<"\n";
        outFile<< LOCCTR <<"\n" ;
        LOCCTR = ToHexaDecimal(ToDecimal(LOCCTR)+4) ; 
        outFile << LOCCTR << "\n" ;
	}


}







int main(){


	string word[5] ; 
	int count = 0 ; 
	string s = "    HEy my name is Utkarsh" ; 
	getTokens(s , word , count);

	for (int i = 0 ; i<5 ; i++){
		cout<<word[i]<<"\n" ; 
	}



}
