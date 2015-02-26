#include<iostream>

using namespace std;
int main() {
          int b;
          int& a = b;
		  cout<<"\nEnter a value: ";
		  cin>> a;
		  cout<<"a="<<a<<" b="<<b<<"\n\n";
		  
		  int d;
          int *c = &d;
		  cout<<"Enter a value: ";
		  cin>> *c;
		  cout<<"c="<<c<<" d="<<d<<endl;
		  return 0;
}