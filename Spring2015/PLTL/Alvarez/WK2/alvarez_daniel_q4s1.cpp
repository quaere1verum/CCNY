#include <iostream>
using namespace std;
int main(){
	int z = 20;
	char x = 'a';
	double y = 5.25;
	int *p = &z;
	char *o = &x;
	double *l = &y;
cout << "\nTable illustrating the number of bytes that the computer "
     << "\nuses to store a data type and the address of that data type"
	 << "\n-----------------------------------------------------------"
	 << "\n";
cout << "\nData Type    Bytes"
     << "\n----------   -----"
     << "\nint            " <<sizeof(20) 
     << "\nchar           " <<sizeof('a')
     << "\ndoble          " <<sizeof(5.25)
     << "\n";
cout
	 << "\nAddress of   Bytes"
	 << "\n----------   -----"
	 << "\nint            " << sizeof(p)
	 << "\nchar           " << sizeof(o)
	 << "\ndoble          " << sizeof(l)
	 << "\n";
     return 0;
}