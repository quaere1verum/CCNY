#include<iostream>
#include<ctime>
#include<cstdlib>
#include<stdlib.h>
using namespace std;
/********************************************
* Javier Pajuelo			                *
* Prof. Jie Wei				                *
* Digital Libraries - Spring 2015	        *
* Assignment1 : Zig -zag			        *
*********************************************/


/********************************************************************
 main function accepts values or rows and columns and creates       *
 a random matrix of real numbers with those dimensions.             *
 Then, the code creates an array that grabs values in matrix in     *
 a zig zag manners and prints the values in the array to the screen *
                                                                    *
 @params 	    assumes first argument is row in integers           *
		        assumes second argument is columns in integers      *
                                                                    *
 @return	    int 0 for correct                                   *
		        int 1 for error                                     *
*********************************************************************/
int main(int argc, char* argv[])
{
    int DEBUG = 0;
	srand(time(0)); // current time as seed 	
	int  N = -1;	// row int
	int  M = -1;	// col int

	try{
		if (argc < 2)
		{
			cout<<"Nothing was entered!!\nPlease enter code as: $./test <row number> <col number>\n";
	        return 1;
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
    
    cout<<"\n\nRandom Matrix:\n";
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
 	
	int idx=0, jdx=0;
	
    elem =0;
	// get first elem
	tmp[elem] = mat[0][0];
	elem++;
	
	int it = 0;
	while(elem < elems)
	{

	
		//==================================	
		// print info 
        if (DEBUG==1){ 
            cout <<"Iteration : "<< it<<"\ni = "<<i<<"\tj = "<<j<<"\n\n\n\n";
            it++;		
            
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
        }
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
		        
			

				elem ++;
                 
				// go down the diagonal
                //   /
                //  v
				while(acc_j>0 &&  acc_i<N-1)
                // while(acc_j!=acc_i)
				{
					// increase i
					i++;
					// decrease j
					j--;
					
					tmp[elem] = mat[i][j];
					
					acc_j = j;
					acc_i = i;	
                    elem++;


				} 											
			}
			else{
				// you are in the matrix's upper right corner
				//cout<<"j+1 = "<< j+1<<"\n";
				// move down
				i++;
				acc_j = j;
				acc_i = i;
					
				tmp[elem] = mat[i][j];
				elem++;
				
				while ( acc_i < N-1)
				{		
					i++;
					j--;
					
					tmp[elem] = mat[i][j];
					acc_i = i;
					
					//acc_j = j;		
					
					// NOTE: you don't always decrease j! 		
					if (acc_i == N)
					{
                        j++;
					}
		
					elem++;
				}	
				if (i==N) // if i ended up equal to rows
				{
					i = N-1;
									
				 	// j ++; 	
				}

			}



		}
	
		// =================================
		if(DEBUG==1){
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
        }
		// =================================
			
		if(j==0) {

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
                //
                // go up on diagonal 
                while(acc_i > 0 && acc_j<M-1)
				{
                    
					i--;
					j++;

					tmp[elem]=mat[i][j];
	    			
                    elem++;
					acc_i=i;
					acc_j=j;
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
                
                while(acc_i >0 && acc_j < M-1)
                {
                    i--;
                    j++;
                    tmp[elem] = mat[i][j];
                    elem++;
                    acc_i = i;
                    acc_j = j;

                }
                    
            }            
		}
		
		// ===========================================	
		if(DEBUG==1)
        {
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
        }
		// ===========================================	
	
		// after this we are in the upper row 
		// or i =0
		// if there is a right neighbor
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

				tmp[elem] = mat[i][j];
				elem++;
	            
                //while(acc)
				while(acc_i!=acc_j)
				{
					//tmp[elem] = mat[i][j];
					i--;
					j++;
					acc_i+=i;
					acc_j+=j;

					tmp[elem] = mat[i][j];
					elem++;
				}
			}

		}
		
		// check if you can move one col right
		if(j+1 < cols )
		{
			// if you are last row
			if(i==N -1 ){
				//move right
				j++;
				//get element 
				tmp[elem]  = mat[i][j];	
				elem++;
				
				// move in the diagonal in this form 	 ^
				// 					                    /
				// keep going while either or reaches a bound
				while(i >0 && j<M-1)	
				{
	
					j++;
					i--;
					tmp[elem] = mat[i][j];
					elem++;			
				}	
			}			
			else{
                // you can move to the right and you are not last row
				// trying to move 
                //       /
                //      v
                

				j++;
				
				tmp[elem] = mat[i][j];
				
		
				elem++;
				acc_i = i;
				acc_j = j;			
                while(acc_i<N-1 && acc_j > 0 )
				//while(acc_i != acc_j)
				{
					i++;
					j--;
					tmp[elem]=mat[i][j];
					
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
                while(acc_i < N-1  && acc_j >0 )
                //while(acc_i!=acc_j)
				{
					i++;
					j--;
					tmp[elem]=mat[i][j];
	
                    elem++;
					acc_i=i;
					acc_j=j;
				}
			}
            // if you are by the right bound and can't go rith    
            //if
		}		
		
		// ===========================================	
		if(DEBUG==1){
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
        }
        // ===========================================	
		
		// if you are in the last row	
		if(i==N-1)
		{

			// if you can move to right 
			if(j+1 <M)
			{
				j++;
				tmp[elem] = mat[i][j];

				elem++;
				    
                acc_i = i;
				acc_j = j;
			
                // try to move right and up the diagonal 
                //   ^
                //  /
                while(acc_i >0 && acc_j < M-1) 
				// while(acc_i!=acc_j)
				{	
				
					i--;
					j++;


					acc_i=i;
					acc_j=j;
					tmp[elem] = mat[i][j];
					
					elem++;

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
	cout<<"\n\nzigzag = [";
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
