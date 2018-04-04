
#include <iostream>
#include <map>
#include <string>

using namespace std ; 


// Strucure of a register
struct reg{

 int number ; 
 char exist ; 

	reg(){
		exist = 'n' ; 

}};

// Structure of an opcode 
struct opcode{

string op ; 
int format ; 
char exist ; 

opcode(){
	exist = 'n' ; 

}} ; 


//Structure for a symbol table 

struct label{

//string address ; 
string value ;
string block ;  
char exist ; 

label(){
	exist = 'n' ; 
}};


// Strucutre for a code block 

struct block{

	string address ; 
	string length ; 
	int num ; 
	char exist ; 

	block(){
		exist = 'n' ; 
}};


//Declaring a map for the OPTAB

std::map<string , opcode> OPTABLE ; 
std::map<string , reg> REGISTER ; 
std::map<string , label> SYMTAB ; 
std::map<string , block> BLOCK ; 

void create() {


	//REGISTERS

	REGISTER["A"].number = 0 ;
	REGISTER["A"].exist = 'y' ;

	REGISTER["X"].number = 1 ;
	REGISTER["X"].exist = 'y' ; 

	REGISTER["L"].number = 2 ;
	REGISTER["L"].exist = 'y' ; 

	REGISTER["PC"].number = 8 ;
	REGISTER["PC"].exist = 'y' ; 

	REGISTER["SW"].number = 9 ;
	REGISTER["SW"].exist = 'y' ; 

	REGISTER["B"].number = 3 ;
	REGISTER["B"].exist = 'y' ;

	REGISTER["S"].number = 4 ;
	REGISTER["S"].exist = 'y' ;

	REGISTER["T"].number = 5 ;
	REGISTER["T"].exist = 'y' ;

	REGISTER["F"].number = 6 ;
	REGISTER["F"].exist = 'y' ;

	//OPCODE TABLE

OPTABLE["ADD"].op = "18" ; 
OPTABLE["ADD"].format = 3 ; 
OPTABLE["ADD"].exist = 'y' ; 

OPTABLE["ADDF"].op = "58" ; 
OPTABLE["ADDF"].format = 3 ; 
OPTABLE["ADDF"].exist = 'y' ; 

OPTABLE["ADDR"].op = "90" ; 
OPTABLE["ADDR"].format = 2 ; 
OPTABLE["ADDR"].exist = 'y' ; 

OPTABLE["AND"].op = "40" ; 
OPTABLE["AND"].format = 3 ; 
OPTABLE["AND"].exist = 'y' ; 

OPTABLE["CLEAR"].op = "B4" ; 
OPTABLE["CLEAR"].format = 2 ; 
OPTABLE["CLEAR"].exist = 'y' ; 

OPTABLE["COMP"].op = "28" ; 
OPTABLE["COMP"].format = 3 ; 
OPTABLE["COMP"].exist = 'y' ; 

OPTABLE["COMPF"].op = "88" ; 
OPTABLE["COMPF"].format = 3 ; 
OPTABLE["COMPF"].exist = 'y' ; 

OPTABLE["COMPR"].op = "A0" ; 
OPTABLE["COMPR"].format = 2 ; 
OPTABLE["COMPR"].exist = 'y' ; 

OPTABLE["DIV"].op = "24" ; 
OPTABLE["DIV"].format = 3 ; 
OPTABLE["DIV"].exist = 'y' ; 

OPTABLE["DIVF"].op = "64" ; 
OPTABLE["DIVF"].format = 3 ; 
OPTABLE["DIVF"].exist = 'y' ; 

OPTABLE["DIVR"].op = "9C" ; 
OPTABLE["DIVR"].format = 2 ; 
OPTABLE["DIVR"].exist = 'y' ; 

OPTABLE["FIX"].op = "C4" ; 
OPTABLE["FIX"].format = 1 ; 
OPTABLE["FIX"].exist = 'y' ; 

OPTABLE["FLOAT"].op = "C0" ; 
OPTABLE["FLOAT"].format = 1 ; 
OPTABLE["FLOAT"].exist = 'y' ; 

OPTABLE["HIO"].op = "F4" ; 
OPTABLE["HIO"].format = 1 ; 
OPTABLE["HIO"].exist = 'y' ; 

OPTABLE["J"].op = "3C" ; 
OPTABLE["J"].format = 3 ; 
OPTABLE["J"].exist = 'y' ; 

OPTABLE["JEQ"].op = "30" ; 
OPTABLE["JEQ"].format = 3 ; 
OPTABLE["JEQ"].exist = 'y' ; 

OPTABLE["JGT"].op = "34" ; 
OPTABLE["JGT"].format = 3 ; 
OPTABLE["JGT"].exist = 'y' ; 

OPTABLE["JLT"].op = "38" ; 
OPTABLE["JLT"].format = 3 ; 
OPTABLE["JLT"].exist = 'y' ; 

OPTABLE["JSUB"].op = "48" ; 
OPTABLE["JSUM"].format = 3 ; 
OPTABLE["JSUB"].exist = 'y' ; 

OPTABLE["LDA"].op = "00" ; 
OPTABLE["LDA"].format = 3 ; 
OPTABLE["LDA"].exist = 'y' ; 

OPTABLE["LDB"].op = "68" ; 
OPTABLE["LDB"].format = 3 ; 
OPTABLE["LDB"].exist = 'y' ; 

OPTABLE["LDCH"].op = "50" ; 
OPTABLE["LDCH"].format = 3 ; 
OPTABLE["LDCH"].exist = 'y' ; 

OPTABLE["LDF"].op = "70" ; 
OPTABLE["LDF"].format = 3 ; 
OPTABLE["LDF"].exist = 'y' ; 

OPTABLE["LDL"].op = "08" ; 
OPTABLE["LDL"].format = 3 ; 
OPTABLE["LDL"].exist = 'y' ; 

OPTABLE["LDS"].op = "6C" ; 
OPTABLE["LDS"].format = 3 ; 
OPTABLE["LDS"].exist = 'y' ; 

OPTABLE["LDT"].op = "74" ; 
OPTABLE["LDT"].format = 3 ; 
OPTABLE["LDT"].exist = 'y' ; 

OPTABLE["LDX"].op = "04" ; 
OPTABLE["LDX"].format = 3 ; 
OPTABLE["LDX"].exist = 'y' ; 

OPTABLE["LPS"].op = "D0" ; 
OPTABLE["LPS"].format = 3 ; 
OPTABLE["LPS"].exist = 'y' ; 

OPTABLE["MUL"].op = "20" ; 
OPTABLE["MUL"].format = 3 ; 
OPTABLE["MUL"].exist = 'y' ; 

OPTABLE["MULF"].op = "60" ; 
OPTABLE["MULF"].format = 3 ; 
OPTABLE["MULF"].exist = 'y' ; 

OPTABLE["MULR"].op = "98" ; 
OPTABLE["MULR"].format = 2; 
OPTABLE["MULR"].exist = 'y' ; 

OPTABLE["NORM"].op = "C8" ; 
OPTABLE["NORM"].format = 1 ; 
OPTABLE["NORM"].exist = 'y' ; 

OPTABLE["OR"].op = "44" ; 
OPTABLE["OR"].format = 3 ; 
OPTABLE["OR"].exist = 'y' ; 

OPTABLE["RD"].op = "D8" ; 
OPTABLE["RD"].format = 3 ; 
OPTABLE["RD"].exist = 'y' ; 

OPTABLE["RMO"].op = "AC" ; 
OPTABLE["RMO"].format = 2 ; 
OPTABLE["RMO"].exist = 'y' ; 

OPTABLE["RSUB"].op = "4C" ; 
OPTABLE["RSUB"].format = 3 ; 
OPTABLE["RSUB"].exist = 'y' ; 

OPTABLE["SHIFTL"].op = "A4" ; 
OPTABLE["SHIFTL"].format = 2 ; 
OPTABLE["SHIFTL"].exist = 'y' ; 

OPTABLE["SHIFTR"].op = "A8" ; 
OPTABLE["SHIFTR"].format = 2 ; 
OPTABLE["SHIFTR"].exist = 'y' ; 

OPTABLE["SIO"].op = "F0" ; 
OPTABLE["SIO"].format = 1 ; 
OPTABLE["SIO"].exist = 'y' ; 

OPTABLE["SSK"].op = "EC" ; 
OPTABLE["SSK"].format = 3 ; 
OPTABLE["SSK"].exist = 'y' ; 

OPTABLE["STA"].op = "0C" ;
OPTABLE["STA"].format = 3 ; 
OPTABLE["STA"].exist = 'y' ; 

OPTABLE["STB"].op = "78" ; 
OPTABLE["STB"].format = 3 ; 
OPTABLE["STB"].exist = 'y' ; 

OPTABLE["STCH"].op = "54" ; 
OPTABLE["STCH"].format = 3 ; 
OPTABLE["STCH"].exist = 'y' ; 

OPTABLE["STF"].op = "80" ; 
OPTABLE["STF"].format = 3 ; 
OPTABLE["STF"].exist = 'y' ; 

OPTABLE["STI"].op = "D4" ; 
OPTABLE["STI"].format = 3 ; 
OPTABLE["STI"].exist = 'y' ; 

OPTABLE["STL"].op = "14" ; 
OPTABLE["STL"].format = 3 ; 
OPTABLE["STL"].exist = 'y' ; 

OPTABLE["STS"].op = "7C" ; 
OPTABLE["STS"].format = 3 ; 
OPTABLE["STS"].exist = 'y' ; 

OPTABLE["STSW"].op = "E8" ; 
OPTABLE["STSW"].format = 3 ; 
OPTABLE["STSW"].exist = 'y' ;

OPTABLE["STT"].op = "84" ; 
OPTABLE["STT"].format = 3 ; 
OPTABLE["STT"].exist = 'y' ; 

OPTABLE["STX"].op = "10" ; 
OPTABLE["STX"].format = 3 ; 
OPTABLE["STX"].exist = 'y' ;  

OPTABLE["SUB"].op = "1C" ; 
OPTABLE["SUB"].format = 3 ; 
OPTABLE["SUB"].exist = 'y' ;

OPTABLE["SUBF"].op = "5C" ; 
OPTABLE["SUBF"].format = 3 ; 
OPTABLE["SUBF"].exist = 'y' ;  

OPTABLE["SUBR"].op = "94" ; 
OPTABLE["SUBR"].format = 2 ; 
OPTABLE["SUBR"].exist = 'y' ; 

OPTABLE["SVC"].op = "B0" ; 
OPTABLE["SVC"].format = 2 ; 
OPTABLE["SVC"].exist = 'y' ; 

OPTABLE["TD"].op = "E0" ; 
OPTABLE["TD"].format = 3 ; 
OPTABLE["TD"].exist = 'y' ; 

OPTABLE["TIO"].op = "F8" ; 
OPTABLE["TIO"].format = 1 ; 
OPTABLE["TIO"].exist = 'y' ; 

OPTABLE["TIX"].op = "2C" ; 
OPTABLE["TIX"].format = 3 ; 
OPTABLE["TIX"].exist = 'y' ; 

OPTABLE["TIXR"].op = "B8" ; 
OPTABLE["TIXR"].format = 2 ; 
OPTABLE["TIXR"].exist = 'y' ; 

OPTABLE["WD"].op = "DC" ; 
OPTABLE["WD"].format = 3 ; 
OPTABLE["WD"].exist = 'y' ; 

}



int reg_num(char a)
{
    if(a=='A') return 0;
    if(a=='X') return 1;
    if(a=='L') return 2;
    if(a=='B') return 3;
    if(a=='S') return 4;
    if(a=='T') return 5;
    if(a=='F') return 6;
}