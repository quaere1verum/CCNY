#include<iostream>
using namespace std; 
int main(){
         string firstname;
		 string lastname;
		 string streetaddress;
		 string city;
		 string state;
		 string zipcode;
		 cout<<"Enter your first name: ";
		 getline(cin,firstname);
		 cout<<"Enter your last name: ";
		 getline(cin,lastname);
		 cout<<"Enter your street address: ";
		 getline(cin,streetaddress);
		 cout<<"Enter your city: ";
		 getline(cin,city);
		 cout<<"Enter your state: ";
		 getline(cin,state);
		 cout<<"Enter your zipcode: ";
		 getline(cin,zipcode);
		 cout<<"\n\n"<<firstname<<" "<<lastname<<"\n"<<streetaddress<<"\n"<<city<<", "<<state<<", "<<zipcode<<endl;
		 return 0;
}

/*
Good work! 
full points
*/		         
