#include<iostream>
#include<ctime>
#include<cstdlib>
#include<stdlib.h>
using namespace std;
/****************************************
* Javier Pajuelo			*
* Prof. Jie Wei				*
* Digital Libraries - Spring 2015	*
*					*
*****************************************/

int main(int argc, char* argv[])
{
	srand(time(0)); // current time as seed 	
	int  N = -1;
	cout <<"argc = "<< argc<<"\n";	
	try{
		if (argc < 2)
		{
			cout<<"Nothing was entered!!\nUsing default matrix size 2.\n";
			N = 2;
		}	
		else
			N = atoi(argv[1]);
	}
	catch(const std::exception& e){
		cout << "Please, enter an integer parameter.\nError: "<<argv[1]<<
			" entered.\nException: "<<e.what();
	}

	int mat[N][N];
	for(int i =0;i<N;i++)
	{
		for (int j =0;j<N;j++)
		{
			mat[i][j]=rand();
			cout<<mat[i][j]<<", ";
		}
		cout<<"\n";
	}
	cout<<"\n\n\n";

	/*
	(0,0)	(0,1) 	(0,2)	(0,3)
	(1,0)	(1,1)  	(1,2)	(1,3)
	(2,0)	(2,1),  (2,2)	(2,3)
	(3,0)	(3,1)	(3,2)	(3,4)	
	

	(4,0)	(4,1)	(4,2)	(4,3)

	path to follow 
	*---------*  *
	   	 /  /|
	      /    / |
	   /      /  |
	/*      *    *
	|*  -- /   * - *

	* = (i,j) 


	*-* *-*
	 / / /
	* * * *
        |/ / /|
	* * * *
	 / / /
	*-* *-*

	bounds  i = 0
		j = 0
		j = cols -1 
		i = rows -1 
	*/	
	
	int rows = N;
	int cols = N;	
	int mat_size = N*N;
	int matrow = N;
	int i=0, j=0;
	int acc_i = 0;
	int acc_j = 0;
	int tmp[mat_size];
	for(i=0;i<mat_size;i++) tmp[i]=0;
	i=0;
	int elem = 0;
	int elems = mat_size;	
 
	int idx=0, jdx=0;
	for(idx=0;idx<N;idx++)
	{
		for(jdx=0;jdx<N;jdx++)
		{
			cout<<", "<<mat[idx][jdx];
		}
		cout<<"\n";

	}	
	elem =0;
	tmp[elem] = mat[0][0];
	elem++;
	
	int it = 0;
	while(elem < elems)
	{
		cout <<"Iteration : "<< it<<"\n";
		it++;		
	
		//==================================	
		cout<<"I.) elem = "<<elem<<"\n\ntmp = [";
		idx=0;
		while (idx<mat_size)
		{
			cout<<tmp[idx]<<", ";
			idx++;
		}
		cout<<"]\n\n\n";
		idx=0;
		
		cout<<"("<<i<<","<<j<<")\n";
	 	if(i>=rows)		
		{
			cout<<"i>=rows";
			break;
		}
		if(j>=cols)
			break;	
		//==================================	


		// if, try to take right 
		if (i==0)
		{
			//tmp[elem] = mat[i][j];
			//elem++;
			//cout<<"j = "<<j<<"\t elem = "<<elem<<"\n";

			if(j+1<cols)
			{	
				// you are in the upper row 
				// move right 

				j++;
				// get new elem
				tmp[elem] = mat[i][j];
				elem ++;
				// restart count
				acc_j = j;
				acc_i = i;
				
				// go down the diagonal
				while(acc_j!=acc_i)
				{
					// increase i
					i++;
					// decrease j
					j--;
					
					tmp[elem] = mat[i][j];
					elem++;

					acc_j += j;
					acc_i += i;	
				} 											
			}
			else{
				// you are in the matrix's upper right corner
			
				cout<<"j+1 = "<< j+1<<"\n";
				// move down
				i++;
				acc_j = j;
				acc_i = i;
				
	
				while(acc_j!=acc_i)
				{
					tmp[elem] = mat[i][j];
					i++;
					j--;
					elem++;
					acc_i += i;
					acc_j += j;		
					
				}	
			}


		}
	
		// =================================
		cout<<"II. elem = "<<elem<<"\n\ntmp = [";
		idx=0;
		while (idx<mat_size)
		{
			cout<<tmp[idx]<<", ";
			idx++;
		}
		cout<<"]\n\n\n";
		idx=0;	
		cout<<"("<<i<<","<<j<<")\n";
		// =================================


			
		if(j==0) {
			cout<<"i+1 = "<<i+1<<"\tmatrow-1 = "<<matrow-1<<"\n";

			if(i+1 <= matrow-1)
			{
				// go one below
				i++;
				// remain in col
				// j=j
				
				tmp[elem] = mat[i][j];
				elem++;
				acc_i=i;
				acc_j=j;
				// go on diagonal and compare
				while(acc_i!=acc_j)
				{

					i--;
					j++;

					tmp[elem]=mat[i][j];
					elem++;
					acc_i+=i;
					acc_j+=j;
				}
			}			
		}
		
		// ===========================================	
		cout<<"III elem = "<<elem<<"\n\ntmp = [";
		idx=0;
		while (idx<mat_size)
		{
			cout<<tmp[idx]<<", ";
			idx++;
		}
		cout<<"]\n\n\n";
		idx=0;
		
		cout<<"("<<i<<","<<j<<")\n";
		// ===========================================	
		

		// after this we are in the upper row 
		// or i =0
		// if there is a right neighbor
		cout<<"code about to break\n";
		if (j==0)
		{
			
			// if you are on the LFSide bound
			// check if you can move down
			if(i+1 < matrow)
			{
				// go one below
				i++;
				// remain in col
				// j=j
				
				tmp[elem] = mat[i][j];
				elem++;
				// start counting again 
				acc_i=i;
				acc_j=j;
				
				while(acc_i!=acc_j)
				{
					i--;
					j++;
					tmp[elem] = mat[i][j];
					acc_i+=i;
					acc_j+=j;
					elem++;
				}

			}			
			else { 
				// you are in the LF most south corner and
				// there's no way down.
				// move right
				
				
				j++;
				acc_i = i;
				acc_j = j;
				// tmp[elem] = 
				cout<<"i= "<<i<<"\tj = "<<j<<"\n";

				tmp[elem] = mat[i][j];
				elem++;
				cout <<"acc_i before loo\t"<<acc_i<<"\tacc_j= "<<acc_j<<"\n";

				cout<<"assigning = tmp["<<elem<<"] = "<<mat[i][j]<<"\n";	
	
				while(acc_i!=acc_j)
				{
					cout<<"assigning = tmp["<<elem<<"] = "<<mat[i][j]<<"\n";		
					//tmp[elem] = mat[i][j];
					i--;
					j++;
					cout<<"adding "<< i << " to "<<acc_i <<"\t j= "<<j<<" to acc_j\n";		
					acc_i+=i;
					acc_j+=j;

					tmp[elem] = mat[i][j];
					cout<<"acc_i = "<< acc_i<<"\tacc_j = "<<acc_j<<"\n";
					elem++;
				}
			}

		}
		cout <<"Out of j ==0\n";		

		if(j+1 < cols )
		{
			cout <<"j+1<cols\n";

			j++;
			tmp[elem] = mat[i][j];
			elem++;
			acc_i = i;
			acc_j =j;			
			
			while(acc_i != acc_j)
			{
				i++;
				j--;
				tmp[elem]=mat[i][j];
				elem++;
				acc_i += i;
				acc_j += j;

			}
			// at this point i = row  length -1
		}
		else{ 
			// Fundamental statement in dimension >2, but not 
			// <=2

			/* col = j+1 */	
			cout <<"j+1 >= cols\n"<<j+1<<">="<<cols<<"\ti = "<<i<<"\n";
			
			// if Lower rightmost corner 	
			if(i+1<rows)
			{
				i++;
			// ij--;
			
				acc_i = i;
				acc_j = j;
				tmp[elem] = mat[i][j];
				elem++;
				while(acc_i!=acc_j)
				{
					i++;
					j--;
					tmp[elem]=mat[i][j];
					elem++;
					acc_i+=i;
					acc_j+=j;
				}
			}	
		}		
		
		// ===========================================	
		idx=0;	
		cout<<"IV elem = "<<elem<<"\n\ntmp = [";
		while (idx<mat_size)
		{
			cout<<tmp[idx]<<", ";
			idx++;
		}
		cout<<"]\n\n\n";
		idx=0;
		
	
		cout<<"("<<i<<","<<j<<")\nEnd of iteration\n";
			
		for(idx=0;idx< N;idx++)
		{
			for(jdx=0;jdx<N;jdx++)
			{
				cout<<", "<<mat[idx][jdx];
			}
			cout<<"\n";

		}		
		// ===========================================	
		
		if(i==N-1)
		{
			if(j+1 <N)
			{
				j++;
				tmp[elem] = mat[i][j];
				elem++;
				acc_i = i;
				acc_j = j;
				
				while(acc_i!=acc_j)
				{
					i--;
					j++;
					tmp[elem] = mat[i][j];
					elem++;
					acc_i+=i;
					acc_j+=j;
		
				}
			
			}

		}

	}

	idx=0;
	cout<<"\n\ntmp = [";
	while (idx< N*N)
	{
		cout<<tmp[idx]<<", ";
		idx++;
	}
	cout<<"]\n\n\n";



	for(idx=0;idx<N;idx++)
	{
		for(jdx=0;jdx<N;jdx++)
		{
			cout<<", "<<mat[idx][jdx];
		}
		cout<<"\n";

	}	
}
