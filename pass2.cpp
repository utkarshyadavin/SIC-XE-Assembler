#include <iostream>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <map>
#include <unistd.h>

#include <climits>
#include <fstream>

using namespace std ; 

#include "pass1.cpp"


// Initializing the output files 

ofstream object ; 
ofstream list ; 
ofstream modification ; 

ifstream intermediate ; 
int current_block_num ; 




// void open_files(){

// 	object.open("object.txt") ;
// 	modification.open("modification.txt") ; 
// 	list.open("list.txt") ; 
// 	intermediate.open("interm.txt") ; 
// }



void assemble_code(string[]);
string generate_code(string[]);
void modify_object_file() ; 

string text_s="",text_e="";
int text_length=0,base=INT_MAX;



bool imm,ind ;

// Method to take input into string form an intermediate file
void input(string a []){

	int i ; 

	for(i = 0 ; i<6 ; i++){
		getline(intermediate , a[i]) ;
	}

		// output to the screen
	cout<<"Input for line number: "<<a[0]<<"\n" ; 

	for( i = 1 ; i<6 ; ++i){
		cout<<a[i]<<"\n" ; 
	}
}





int main (){


    run() ;

    // this will be used to read input from intermediate file 
	string a [6] ; 
	string start_address ; 


    // Checking for errors during pass1 

	if(error_flag==1){

		cout<<"Some Error Occured. The program could not be assembled. No Listing file prepared\n" ; 
		cout<<"The error output is written down to the error.txt file\n" ; 

		// Exit the program 
		exit(1) ; 
	}

	object.open("object.txt") ;
	modification.open("modification.txt") ; 
	list.open("list.txt") ; 
	intermediate.open("interm.txt") ; 


	


	// Initializaing the list file with the header text 

	list<<"Line\tLoc   Block\t\tSource Statement\t\tobject Code"<<endl;
    list<<"----------------------------------------------------------------"<<endl<<endl;

	// Reading the input from the intermediate file in a 6 l3ngth string array 

	input(a) ; 

	// Initializing blocks 

	current_block_num = 0 ; 
	current_block = "DEFAULT" ; 



	// If the first line of input is comment. Can be checked by checking the '$' symbol in the input 
	  while(a[1]=="$")
    {	// Writing out the comment value in the list file 
         list<<a[0]<<"\t\t "<<a[2]<<endl;
         // Asking for another input which can be a comment as well 
         input(a);
    }



    // Detecting the start statement which will be present in a[2]

    if(a[2]=="START"){

    	list<<a[0]<<"\t"<<ExtendHexaCode(4,a[4])<<"  "<<current_block_num<<"\t\t"<<a[1]<<"\t\t"<<a[2]<<"\t\t"<<a[3]<<endl;
    	//Writing HH to the object file 
    	object<<"H^"; 

    	int i ; 
    	for(i = 0 ; i<a[1].length() ; i++){
    		object<<a[1][i] ; 

    	}

    	for(;i<6;++i)
            object<<" ";

         string temp=getBlock(block_number-1);
         string len;
         len=ToHexaDecimal(ToDecimal(BLOCK[temp].address)+ToDecimal(BLOCK[temp].length));
         object<<"^"<<ExtendHexaCode(6,a[3])<<"^"<<ExtendHexaCode(6,len)<<endl;
         start_address = a[3];



    }

    else{
    	error_flag = 1 ; 
    	errorFile<< "The generated error file has no start statement\n" ; 
    }


    while(true){

    	//Taking another input line
    	input(a);

        if(a[1]=="$")
        {
            list<<a[0]<<"\t\t "<<a[2]<<endl;
            continue ; 
            
        }

        // Checking for end of file 

        if(a[2]=="END")
        {
        	// Addidng END to list File
			list<<a[0]<<"\t\t\t\t\t\t"<<a[2]<<"\t\t"<<a[3]<<endl;

            if(text_length>0)
            {
                object<<text_s<<"^"<<ExtendHexaCode(2,ToHexaDecimal(text_length/2))<<text_e<<endl;
                cout<<"!!"<<endl;
            }

            text_length=0;
            text_s="";
            text_e="";


            //
            modify_object_file();
            //Writing to objject file
            object<<"E^"<<ExtendHexaCode(6,start_address)<<endl;
            break;
        }

         
        
        // Call the assembler method 
        assemble_code(a) ; 

        // Output the opcode 
        //cout<<"opcode: "<<a[2]<<"..." ; 
    
    }


    // Checking for error flag at the end of assembling 
    if(error_flag)
    {
        cout<<"Some errors was encountered during assemble. "<<endl;
        cout<<"Please check error file"<<endl;
    }
    else
    {
        cout<<"INPUT FILE ASSEMBLED SUCCESSFULY!!"<<endl;

    }

    list.close() ; 

}



// Method to assemble the code
void assemble_code(string a []) {

    string object_code;
    string loc_ctr;
    int format;
    if(a[2]=="USE")
    {
        current_block=a[3];
        current_block_num = BLOCK[current_block].num;
        list<< a[0] << "\t0000  "<<current_block_num<<"\t\t\t"<<a[2]<<"\t\t"<<a[3]<<endl;
        if(text_length>0)
        object << text_s<<"^"<<ExtendHexaCode(2,ToHexaDecimal(text_length/2))<<text_e<<endl;
        text_s="";
        text_e="";
        text_length=0;
        return;
    }

    if(a[2]=="RESB"||a[2]=="RESW")
    {
        list<<a[0]<<"\t"<<ExtendHexaCode(4,a[4])<<"  "<<current_block_num<<"\t\t"<<a[1]<<"\t"<<a[2]<<"\t\t"<<a[3]<<endl;
        if(text_length>0) 
        object<<text_s<<"^"<<ExtendHexaCode(2,ToHexaDecimal(text_length/2))<<text_e<<endl;
        text_s="";
        text_e="";
        text_length=0;
        return;
    }

    imm=ind=false;
    object_code = generate_code(a);
    cout<<"a[2]: "<<a[2]<<":::"<<object_code<<endl;

    
    if(a[2]=="BYTE"||a[2]=="WORD")
        list<< a[0] << "\t"<<ExtendHexaCode(4,a[4])<<"  "<<current_block_num<<"\t\t"<<a[1]<<"\t"<<a[2]<<"\t\t"<<a[3]<<endl;
    else
    {
        if(imm)      list<<a[0]<<"\t"<<ExtendHexaCode(4,a[4])<<"  "<<current_block_num<<"\t\t"<<a[1]<<"\t\t"<<a[2]<<"\t\t#"<<a[3]<<"\t\t"<<object_code<<endl;
        else if(ind) list<<a[0]<<"\t"<<ExtendHexaCode(4,a[4])<<"  "<<current_block_num<<"\t\t"<<a[1]<<"\t\t"<<a[2]<<"\t\t@"<<a[3]<<"\t\t"<<object_code<<endl;
        else         list<<a[0]<<"\t"<<ExtendHexaCode(4,a[4])<<"  "<<current_block_num<<"\t\t"<<a[1]<<"\t\t"<<a[2]<<"\t\t"<<a[3]<<"\t\t"<<object_code<<endl;
    }
    if(text_s=="")
    {
        loc_ctr=ToHexaDecimal(ToDecimal(BLOCK[current_block].address)+ToDecimal(a[4]));
        text_s="T^"+ExtendHexaCode(6,loc_ctr);
        text_e="^"+object_code;
        text_length=object_code.length();
    }
    else if(text_length+object_code.length()>60)
    {
        object<<text_s<<"^"<<ExtendHexaCode(2,ToHexaDecimal(text_length/2))<<text_e<<endl;
        loc_ctr=ToHexaDecimal(ToDecimal(BLOCK[current_block].address)+ToDecimal(a[4]));
        text_s="T^"+ExtendHexaCode(6,loc_ctr);
        text_e="^"+object_code;
        text_length=object_code.length();
    }
    else
    {
        text_e+="^"+object_code;
        text_length+=object_code.length();
    }
    if(a[2]=="LDB")
    {
        base=ToDecimal(SYMTAB[a[3]].value)+ToDecimal(BLOCK[SYMTAB[a[3]].block].address);
    }
}








void modify_object_file() {

	ifstream fin;
   fin.open("modification.txt");
   string s;
   while(true)
   {
       getline(fin,s);
       if(s=="") break;
       object<<s<<endl;
   }


}


string generate_code(string a []) {


	string ob1,ob2,ob3;
    string operand_addr,prgm_ctr;
    int format;
    if(a[2]=="BYTE")
    {
        int i;
        ob1="";
        if(a[3][0]=='X')
            for(i=2;i<a[3].length()-1;++i) ob1+=a[3][i];
        else //a[3][0]=='C'
            for(i=2;i<a[3].length()-1;++i)
                ob1+=ToHexaDecimal((int)a[3][i]);
        return ob1;
    }
    if(a[2]=="WORD")
    {
        ob1=ToHexaDecimal(atoi(a[3].c_str()));
        return ob1;
    }
    if(a[2]=="RSUB")
    {
        ob1="4F0000";
        return ob1;
    }
    if(a[2]=="+RSUB")
    {
        ob1="4F000000";
        return ob1;
    }
    if(a[2][0]=='+')
    {
        format=4;
        a[2]=a[2].substr(1);
    }
    else
        format=OPTABLE[a[2]].format;
    if(format==1)
    {
        cout<<"Format 1"<<endl;
        ob1=OPTABLE[a[2]].op;
        return ob1;
    }
    if(format==2)
    {
        cout<<"Format 2"<<endl;
        ob1=OPTABLE[a[2]].op;
        if(a[3].length()==3)
        {
            ob2=ToHexaDecimal(reg_num(a[3][0]));
            if(isdigit(a[3][2]))  ob2=ob2+DecimalToHexa(a[3][2]-1);
            else
            {
                ob2=ob2+DecimalToHexa(reg_num(a[3][2]));
            }
        }
        else  //a[3].length==1
        {
            if(isdigit(a[3][0]))
            {
                ob2=ToHexaDecimal(atoi(a[3].c_str()))+"0";
                cout<<"isdigit! ob2: "<<ob2<<endl;
            }
            else
            {
                cout<<ToHexaDecimal(reg_num(a[3][0]))<<endl;
                ob2=ToHexaDecimal(reg_num(a[3][0]))+"0";
                cout<<"Not Isdigit! ob2: "<<ob2<<endl;
            }
        }
        cout<<"a[2]: "<<a[2]<<" ob1:"<<ob1<<"ob2:"<<ob2<<endl;
        return (ob1+ExtendHexaCode(2,ob2));
    }
    if(format==3)
    {
        cout<<"Format 3"<<endl;
        cout<<a[2]<<endl;
        ob1=OPTABLE[a[2]].op;
        if(a[3][0]=='#')
        {
            imm=true;
            cout<<"Immediate!"<<endl;
            ob1=ToHexaDecimal(ToDecimal(ob1)+1);
            a[3]=a[3].substr(1);
            if(isdigit(a[3][0]))
            {
                ob2="0";
                ob3=ToHexaDecimal(atoi(a[3].c_str()));
                return ExtendHexaCode(2,ob1)+ob2+ExtendHexaCode(3,ob3);
            }
            //cout<<"ob1: "<<ob1<<endl;
        }
        else if(a[3][0]=='@')
        {
            ind=true;
            cout<<"Indirect!"<<endl;
            ob1=ToHexaDecimal(ToDecimal(ob1)+2);
            a[3]=a[3].substr(1);
        }
        else
            ob1=ToHexaDecimal(ToDecimal(ob1)+3);
        ob2="0";
        bool x=false;
        if(a[3][a[3].length()-2]==',')
        {
            x=true;
            ob2=ToHexaDecimal(ToDecimal(ob2)+8);
            a[3]=a[3].substr(0,a[3].length()-2);
        }
        //cout<<"ob1:"<<ob1<<"ob2:"<<ob2<<endl;
        prgm_ctr=ToHexaDecimal(ToDecimal(BLOCK[current_block].address)+ToDecimal(a[5]));
        operand_addr=ToHexaDecimal(ToDecimal(SYMTAB[a[3]].value)+ToDecimal(BLOCK[SYMTAB[a[3]].block].address));
        cout<<"prgm_ctr: "<<prgm_ctr<<" operand_addr: "<<operand_addr<<endl;
        if(x) a[3]+=",X";
        int disp=ToDecimal(operand_addr)-ToDecimal(prgm_ctr);
        cout<<"disp: "<<disp<<endl;
        if(disp>=-2048 && disp<2048)
        {
            ob2=ToHexaDecimal(ToDecimal(ob2)+2);
            if(disp<0) disp+=4096;
            ob3=ToHexaDecimal(disp);
            return ExtendHexaCode(2,ob1)+ExtendHexaCode(1,ob2)+ExtendHexaCode(3,ob3);
        }
        disp=ToDecimal(operand_addr)-base;
        if(disp>=-2048 && disp<2048)
        {
            ob2=ToHexaDecimal(ToDecimal(ob2)+4);
            if(disp<0) disp+=4096;
            ob3=ToHexaDecimal(disp);
            return ExtendHexaCode(2,ob1)+ExtendHexaCode(1,ob2)+ExtendHexaCode(3,ob3);
        }
        //If still here, means overflow
        error_flag=1;
        errorFile<<"Line "<<a[0]<<": Overflow detected"<<endl;
    }
    if(format==4)
    {
        ob1=OPTABLE[a[2]].op;
        if(a[3][0]=='#')
        {
            imm=true;
            ob1=ToHexaDecimal(ToDecimal(ob1)+1);
            a[3]=a[3].substr(1);
            if(isdigit(a[3][0]))
            {
                ob2="0";
                ob3=ToHexaDecimal(atoi(a[3].c_str()));
                a[2]="+"+a[2];
                return ob1+ob2+ExtendHexaCode(5,ob3);
            }
        }
        else if(a[3][0]=='@')
        {
            ind=true;
            ob1=ToHexaDecimal(ToDecimal(ob1)+2);
            a[3]=a[3].substr(1);
        }
        else
            ob1=ToHexaDecimal(ToDecimal(ob1)+3);
        bool x=false;
        ob2="1";
        if(a[3][a[3].length()-2]==',')
        {
            x=true;
            ob2=ToHexaDecimal(ToDecimal(ob2)+8);
            a[3]=a[3].substr(0,a[3].length()-2);
        }
        operand_addr=ToHexaDecimal(ToDecimal(SYMTAB[a[3]].value)+ToDecimal(BLOCK[SYMTAB[a[3]].block].address));
        if(x) a[3]+=",X";
        ob3=operand_addr;
        a[2]="+"+a[2];
        string loc_ctr=ToHexaDecimal(ToDecimal(BLOCK[current_block].address)+ToDecimal(a[4])+1);
        modification<<"M^"<<ExtendHexaCode(6,loc_ctr)<<"^05"<<endl;
        return ExtendHexaCode(2,ob1)+ExtendHexaCode(1,ob2)+ExtendHexaCode(5,ob3);
    }




}