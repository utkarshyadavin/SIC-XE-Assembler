# SIC-XE-Assembler

The given codebase implements the two pass SIC-XE Assembler.

The following features of the SIC-XE Machine Assembler have been implemented: 
  - : Program Blocks
  - : Modification Records


How to run: 

1. There is no need to run pass1 separately. 
2. The pass1.cpp file is included in the Pass2 file. 
3. Directly run pass2.cpp by using the command "g++ pass2.cpp" . 
4. Then run the created a.out object file. 
5. After the Assembling of the code is finised, it will generate multiple file: 
   - interm.txt : It is the intermediate file which gets generated after pass1 is finished. 
   - error.txt  : Contains all the error statements generated during the run. 
   - object.txt : Contains the Object Code. 
   - modification.txt : Consists of the modification record. 
   - list.txt : This will contain the entire list of commands with the object code for each 
      command, line nimbers, program block number and address. 
     
   
