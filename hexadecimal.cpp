#include <iostream>
#include <string>
#include <cmath>

using namespace std; 




char DecimalToHexa(int value){

if(value==0)
	return '0' ; 
if(value==1)
	return '1' ; 
if(value==2)
	return '2' ; 
if(value==3)
	return '3' ; 
if(value==4)
	return '4' ; 
if(value==5)
	return '5' ; 
if(value==6)
	return '6' ; 
if(value==7)
	return '7' ; 
if(value==8)
	return '8' ; 
if(value==9)
	return '9' ; 
if(value==10) 
	return 'A' ; 
if(value==11)
	return 'B' ; 
if(value==12)
	return 'C' ; 
if(value==13)
	return 'D' ;
if(value==14) 
	return 'E' ; 
if(value==15)
	return 'F' ; 

}


int HexaToDecimal (char value){

if(value=='0')
	return 0 ; 
if(value=='1')
	return 1; 
if(value=='2')
	return 2 ; 
if(value=='3')
	return 3 ; 
if(value=='4')
	return 4 ; 
if(value=='5')
	return 5 ; 
if(value=='6')
	return 6 ; 
if(value=='7')
	return 7 ; 
if(value=='8')
	return 8 ; 
if(value=='9')
	return 9 ; 
if(value=='A')
	return 10 ; 
if(value=='B')
	return 11 ; 
if(value=='C')
	return 12 ; 
if(value=='D')
	return 13 ; 
if(value=='E')
	return 14 ; 
if(value=='F')
	return 15 ; 

}

// Converting a deciaml number to hexadecimal number 
string ToHexaDecimal(int value){
	string temp = "" ;
	if(value==0){
	temp = '0' ; 
	}
	else { 
	while(value!= 0 ){
		//cout<<value%16<<endl ; 
		//cout<<DecimalToHexa(value%16)<<endl ; 
		temp = DecimalToHexa(value%16) + temp ; 
		value = value/16 ; 
	}
	}
	return temp ;
}


// Convert a hexadecimal format to decimal value 
int ToDecimal(string value){
	
    int l=value.length()-1 ;
    int current=1  ;
    int temp = 0 ;
    while(l>=0)
    {
        temp+=(HexaToDecimal(value[l])*current);
        current=16;
        --l;
    }
    return temp ;

}


// Method for extending a generated hexa code to the required length by adding '0'

string ExtendHexaCode(int digits , string hexa){
  	string temp = "" ; 
 	for(int i = 0 ; i< digits - hexa.length() ; i++){
 		temp = "0" + temp ; 
 	}
	temp = temp + hexa ; 
 	return temp ; 
}


