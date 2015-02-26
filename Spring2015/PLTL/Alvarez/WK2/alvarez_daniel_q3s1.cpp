#include<iostream>

using namespace std;
int main() {
          int b;
          int& a = b;
		  a = 10;
		  cout<<"\na="<<a<<" b="<<b<<"\n\n";
		  
		  int d;
          int *c = &d;
		  *c = 10;
		  cout<<"c="<<c<<" d="<<d<<endl;
		  return 0;
}

/*
   Line 4  Declares the variable b as a integer number
   Line 5  Declares variable a as an integer alias of b. a and b are now interchangeable.
   Line 6  Assigns a numerical value to the variable a, and therefore, to variable b
   Line 9  Indicates what the program is going to display.
   Line 10 declares variable d as an integer
   Line 11 Declares c as a pointer. Stores the address of d in c. d is pointed to by c. 
   Line 12 States that pointer c has a value of 10. Since c is pointing to d, the program
           assigns the value of 10 to d. Variable c only contains the address of d
   Line 13 Indicates what the program is going to display. 
*/   