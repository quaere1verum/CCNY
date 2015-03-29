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

/*
 main function accepts values or rows and columns and creates
 a random matrix of real numbers with those dimensions.
 Then, the code creates an array that grabs values in matrix in 
 a zig zag manners and prints the values in the array to the screen

 @params 	assumes first argument is row in integers
		assumes second argument is columns in integers
 @return	int 0 for correct 
		int 1 for error
*/
int main(int argc, char* argv[])
{
	
	srand(time(0)); // current time as seed 	
	int  N = -1;	// row int
	int  M = -1;	// col int

	cout <<"argc = "<< argc<<"\n";	
	try{
		if (argc < 2)
		{
			cout<<"Nothing was entered!!\nUsing default matrix size 2.\n";
			N = 2;
		}	
		else{
			N = atoi(argv[1]);
			M = atoi(argv[2]);
		}
	}
	catch(const std::exception& e){
		cout << "Please, enter an integer parameter.\nError: "<<argv[1]<<
			" entered.\nException: "<<e.what();
	}

	int mat[N][M];
	for(int i =0;i<N;i++)
	{
		for (int j =0;j<M;j++)
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
	int cols = M;	
	int mat_size = N*M;
	int matrow = N;
	int i=0, j=0;
	int acc_i = 0;
	int acc_j = 0;
	int tmp[mat_size];
	
	// assign zeros to tmp array
	for(i=0;i<mat_size;i++) tmp[i]=0;
		
	i=0;
	int elem = 0;
	int elems = mat_size;	
 	
	// print mat
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
	// get first elem
	tmp[elem] = mat[0][0];
	elem++;
	
	int it = 0;
	while(elem < elems)
	{
		cout <<"Iteration : "<< it<<"\ni = "<<i<<"\tj = "<<j<<"\n\n\n\n";
		it++;		
	
		//==================================	
		// print info 
        cout<<"\n\n\nI.) elem = "<<elem<<"\n\ntmp = [";
		idx=0;
		while (idx<mat_size)
		{
			cout<<tmp[idx]<<", ";
			idx++;
		}
		cout<<"]\n";
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
		// if you are at row zero
		if (i==0)
		{
			//tmp[elem] = mat[i][j];
			//elem++;
			//cout<<"j = "<<j<<"\t elem = "<<elem<<"\n";
			
			// try right 
			if(j+1<cols)
			{	
				// you are in the upper row 
				// move right 

				j++;
				// get new elem
				tmp[elem] = mat[i][j];

				// restart count
				acc_j = j;
				acc_i = i;
		        
				cout<<"tmp = "<< tmp[elem] <<"\ti "<<i<<"\tj="<<j<<
						"\tacc_i="<<acc_i<<"\n\n";

				elem ++;
                 
				// go down the diagonal
                //   /
                //  v
				while(acc_j>0 &&  acc_i<N-1)
                // while(acc_j!=acc_i)
				{
                    cout<<"inside first while ... \n";
					// increase i
					i++;
					// decrease j
					j--;
					
					tmp[elem] = mat[i][j];
					
					acc_j = j;
					acc_i = i;	
					cout<<"tmp = "<< tmp[elem] <<"\ti "<<i<<"\tj="<<j<<
						"\tacc_i="<<acc_i<<"\n\n";
                    elem++;


				} 											
			}
			else{
				// you are in the matrix's upper right corner
				cout<<"Matrix upper right corner with mat[i][j = "<< mat[i][j]<<"\n\n";	
				//cout<<"j+1 = "<< j+1<<"\n";
				// move down
				i++;
				acc_j = j;
				acc_i = i;
				
				cout<<"i "<<i<<"\tj="<<j<<"\tacc_j="<<acc_j<<"\tacc_i="<<acc_i<<"\n\n";
				
				tmp[elem] = mat[i][j];
				elem++;
				
				while ( acc_i < N-1)
				{
						
					i++;
					j--;
					
					tmp[elem] = mat[i][j];
											

					acc_i = i;
					

					cout<<"tmp = "<< tmp[elem] <<"\ti "<<i<<"\tj="<<j<<
						"\tacc_i="<<acc_i<<"\n\n";



					//acc_j = j;		
					
					// NOTE: you don't always decrease j! 		
					if (acc_i == N)
					{

						cout<<"case when acc_i = N \treducing j from "<< j 
							<<" to "<< j+1<<"\n";
						j++;
					}

					
					elem++;
				}	
									

				//while(acc_j!=acc_i)
				/*{
					tmp[elem] = mat[i][j];
					i++;
					j--;

					acc_i += i;
					acc_j += j;		
					
					cout<<"tmp = "<< tmp[elem] <<"\ti "<<i<<"\tj="<<j<<
						"\tacc_j="<<acc_j<<"\tacc_i="<<acc_i<<"\n\n";
					
					elem++;
				
				} */// at this point mtrix has gone down diagonal /
				if (i==N) // if i ended up equal to rows
				{
					i = N-1;
									
				 	// j ++; 	
				}

				cout<<"Right before leaving else: ("<<i <<", "<< j<<")\n";
			}



		}
	
		// =================================
		cout<<"\n\n\nII. elem = "<<elem<<"\n\ntmp = [";
		idx=0;
		while (idx<mat_size)
		{
			cout<<tmp[idx]<<", ";
			idx++;
		}
		cout<<"]\n";
		idx=0;	
		cout<<"("<<i<<","<<j<<")\n\n\n\n";
		// =================================


			
		if(j==0) {
			cout<<"i+1 = "<<i+1<<"\nmatrow-1 = "<<matrow-1<<"\n";

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
				// TODO: modify while loop so it deals with non-square mats
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
            else{ // you are in column 0 and cannot move down.
                  // left bottom corner case 
                  
                //move right 
                j++;
                tmp[elem]=mat[i][j];
                elem++;
                acc_i = i;
                acc_j = j;
                // try move up the diagonal
                //   ^
                //  /
                
                cout<<"tmpp = "<<tmp[elem] <<"\t("<<i<<", "<<j<<")\n"; 
                while(acc_i >0 && acc_j < M-1)
                {
                    cout<<"inside new whiile lll... \n\n";
                    i--;
                    j++;
                    tmp[elem] = mat[i][j];
                    cout<<"tmpp = "<<tmp[elem] <<"\t("<<i<<", "<<j<<")\n"; 
                    elem++;
                    acc_i = i;
                    acc_j = j;

                }
                    
            }            
		}
		
		// ===========================================	
		cout<<"\n\n\nIII elem = "<<elem<<"\n\ntmp = [";
		idx=0;
		while (idx<mat_size)
		{
			cout<<tmp[idx]<<", ";
			idx++;
		}
		cout<<"]\n\n";
		idx=0;
		
			
		for(idx=0;idx< N;idx++)
		{
			for(jdx=0;jdx<M;jdx++)
			{
				cout<<", "<<mat[idx][jdx];
			}
			cout<<"\n";

		}		
		
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
	            
                //while(acc)
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
		
		// check if you can move one col right
		if(j+1 < cols )
		{
			// if you are last row
			if(i==N -1 ){
				cout<<"inside my construction ... ";
				//move right
				j++;
				//get element 
				tmp[elem]  = mat[i][j];	
				elem++;
				cout <<"i = "<<i <<" j = "<<j<<"\ntmp[elem] = "<<tmp[elem-1]<<"\n";
				
				// move in the diagonal in this form 	 ^
				// 					                    /
				// keep going while either or reaches a bound
				while(i >0 && j<M-1)	
				{
					cout<<"j = "<<j <<" < "<<"M = "<<M-1<<"\n";
	
					j++;
					i--;
					tmp[elem] = mat[i][j];
					cout<<"tmp ="<< tmp[elem]<<"\t(i,j)=("<<i<<","<<j<<")\n";
					elem++;			
				}	
			}			
			else{
                // you can move to the right and you are not last row
				// trying to move 
                //       /
                //      v
                
                cout <<"j+1<cols \tj= "<< j <<"\ti="<< i<<"\n";
				cout<<"mat["<<i<<"]["<<j<<"] =" <<mat[i][j]<<"\n";

				j++;
				
				cout<<"mat["<<i<<"]["<<j<<"] =" <<mat[i][j]<<"\n";
				tmp[elem] = mat[i][j];
				
				cout<<"Just assigned: \t"<<tmp[elem]<<"\n";
				
		
				elem++;
				acc_i = i;
				acc_j = j;			
				
				cout<<"acc_i = "<<acc_i<<"\tacc_j = "<<acc_j<<"\n";
				
                while(acc_i<N-1 && acc_j > 0 )
				//while(acc_i != acc_j)
				{
					i++;
					j--;
					tmp[elem]=mat[i][j];
					
				    cout<<"i = "<<i<<"\tj = "<<j<<"\ntmp = "<<tmp[elem]<<"\n";
                    elem++;
					acc_i = i;
					acc_j = j;

				}
				// at this point i = row  length -1
			}
		}
		else{
            // you can't move right  

			/* col = j+1 */	
			cout <<"j+1 >= cols\n"<<j+1<<">="<<cols<<"\ti = "<<i<<"\n";
			
			// if you can move down 
			if(i+1<rows)
			{
                // go down 
				i++;
			    // ij--;
			
				acc_i = i;
				acc_j = j;
				tmp[elem] = mat[i][j];
				elem++;
				
                // go down diagonal 
                //   /
                //  /
                // v
                while(acc_i < N-1  && acc_j >=0 )
                //while(acc_i!=acc_j)
				{
					i++;
					j--;
					tmp[elem]=mat[i][j];

				    cout<<" i = "<<i<<"\tj = "<<j<<"\n"<<
                        "tmpmat "<< tmp[elem]<<"\n";
					
                    elem++;
					acc_i=i;
					acc_j=j;
				}
			}
            // if you are by the right bound and can't go rith    
            //if
		}		
		
		// ===========================================	
		idx=0;	
		cout<<"\n\n\nIV elem = "<<elem<<"\n\ntmp = [";
		while (idx<mat_size)
		{
			cout<<tmp[idx]<<", ";
			idx++;
		}
		cout<<"]\n";
		idx=0;
		
	
		cout<<"("<<i<<","<<j<<")\nEnd of iteration\n";
			
		for(idx=0;idx< N;idx++)
		{
			for(jdx=0;jdx<M;jdx++)
			{
				cout<<", "<<mat[idx][jdx];
			}
			cout<<"\n";

		}		
		// ===========================================	
		
		// if you are in the last row	
		if(i==N-1)
		{

            cout <<"j+1 = "<< j+1 <<" < M = "<<M <<"\n"; 
			// if you can move to right 
			if(j+1 <M)
			{
				j++;
				tmp[elem] = mat[i][j];
				cout<<"assigned = tmp[elem] = "<<tmp[elem]<<"\n";

				elem++;
				
                
                acc_i = i;
				acc_j = j;
				
				cout<<"Before loop acc_i = "<<acc_i<<"\tacc_j = "<<acc_j<<"\n";
	

                // try to move right and up the diagonal 
                //   ^
                //  /
                while(acc_i >0 && acc_j <= M-1) 
				// while(acc_i!=acc_j)
				{	
				
					i--;
					j++;

					cout<<"inside while loop\ti = "<<i<<"\tj = "<<j<<"\n";

					acc_i=i;
					acc_j=j;
					tmp[elem] = mat[i][j];
					
					cout<<"tmp[elem] = "<< tmp[elem]<<"\n";
					elem++;


					cout<<"before comparison -- acc_i = "<<acc_i<<
						"\tacc_j = "<<acc_j<<"\n";
					
					// elem++	
					// consider the last run equal	acc
					/*if (acc_i==acc_j)
					{
						cout<<"inside last loop\t\telem  = "<<elem<<"\n";	
						i--;
						j++;
						tmp[elem] = mat[i][j];
						
						// some cases this is not needed 	
						elem++;
						
					}*/
				}//while(acc_i!=acc_j);
			
			}

		}

	} // PROGRAM DONE 

	idx=0;
	cout<<"\n\ntmp = [";
	while (idx< N*M)
	{
		cout<<tmp[idx]<<", ";
		idx++;
	}
	cout<<"]\n\n\n";



	for(idx=0;idx<N;idx++)
	{
		for(jdx=0;jdx<M;jdx++)
		{
			cout<<", "<<mat[idx][jdx];
		}
		cout<<"\n";

	}	
}
