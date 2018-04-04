
#include <iostream>
#include <fstream> 
#include <string>
#include <map>
#include <cstdlib>
#include <cstdio>


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
	errorFile.open("error.txt");
}


string getBlock(int number){

	std::map<string , block>::const_iterator it ; 
	

	for (it = BLOCK.begin() ;  ; it++){
		if(it->second.num ==number)
			return it->first ; 
	}
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
	}


	else
		makepass(word , count) ; 

	while(true){


		getline(inFile , s) ; 
		getTokens(s , word , count );
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
 

 		string block_address ; 
 		string block_length  ; 
 		string block_name = getBlock(0) ; 
 		block_address = BLOCK[block_name].address ; 
 		block_length = BLOCK[block_name].length ; 

 		for(int i =  1 ; i< block_number ; ++i){
 			block_name = getBlock(i) ; 
 			BLOCK[block_name].address = ToHexaDecimal(ToDecimal(block_address) + ToDecimal(block_length)) ; 
 			block_address = BLOCK[block_name].address ; 
 			block_length = BLOCK[block_name].length ; 
 		}
 	


}

void makepass(string word[] , int count){

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
		cout<<"Format 4 instruction detected"<<"\n" ; 
		outFile<<""<<endl;
        outFile<<word[0]<<"\n";
        outFile<< word[1] <<"\n";
        outFile<< LOCCTR <<"\n" ;
        LOCCTR = ToHexaDecimal(ToDecimal(LOCCTR)+4) ; 
        outFile << LOCCTR << "\n" ;
	}

	if(OPTABLE[word[0]].exist=='y'){

		cout<<"OPCODE is at 0 Location"<<"\n";
		outFile <<"\n" ; 
		outFile <<word[0]<<"\n" ;
		outFile <<word[1]<<"\n" ;
		outFile <<LOCCTR << "\n" ; 
		LOCCTR = ToHexaDecimal(ToDecimal(LOCCTR) + OPTABLE[word[0]].format) ;
		outFile<<LOCCTR<< "\n"; 

	}

	if(OPTABLE[word[0]].exist == 'n'){

		if(SYMTAB[word[0]].exist=='y'){
			// Duplicate symbol , so generate error 
			errorFile <<"Line "<< line<<"Duplicate Symbol Detected"<<"\n" ; 
			error_flag = 1 ; 
		}

		else{

			SYMTAB[word[0]].value = LOCCTR;
            SYMTAB[word[0]].block = current_block;
            SYMTAB[word[0]].exist = 'y';

            // Writing instruction to output file 
            outFile<<word[0]<<"\n";
            outFile<<word[1]<<"\n";
            outFile<<word[2]<<"\n";
            outFile<<LOCCTR<<"\n";

            // Checking whether the instruction is an indirect addressing one
            if(word[1][0]=='+')
            	LOCCTR=ToHexaDecimal(ToDecimal(LOCCTR)+4);
            else if(OPTABLE[word[1]].exist == 'y'){
            	cout<<"............"<<OPTABLE[word[1]].format<<"\n " ; 
            	cout<<ToDecimal(LOCCTR)<<".............................." ; 
            	LOCCTR=ToHexaDecimal(ToDecimal(LOCCTR)+OPTABLE[word[1]].format);
            }
            else if(word[1]=="WORD")
            	LOCCTR = ToHexaDecimal(ToDecimal(LOCCTR) + 3) ; 
            else if(word[1]=="RESW")
            	 LOCCTR=ToHexaDecimal(ToDecimal(LOCCTR)+(atoi(word[2].c_str())*3));
            else if (word[1]=="RESB")
            	LOCCTR=ToHexaDecimal(ToDecimal(LOCCTR)+atoi(word[2].c_str()));
            else if (word[1] == "BYTE"){
				int len=word[1].length()-3;
                if(word[1][0]=='X') len/=2;
                LOCCTR=ToHexaDecimal(ToDecimal(LOCCTR)+len);
			}
			else {
				// This implies that the opcode was not found
				errorFile << "LINE " << line<<" : Opcode was not found"<<"\n" ; 
				error_flag = 1 ; 
			}
			outFile << LOCCTR <<"\n" ; 
		}
	}
}


 int main(){


	run() ; 


 }
