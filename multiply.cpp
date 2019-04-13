/*
	Benjamin Braun (braun4)
	CPSC-2310-002
	Assignment 2
	03-13-19

	Description: This program asks the user for two integers, then
	prints the steps needed to perform hardware multiplication
	on the two integers.
*/



#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string>
using namespace std;


//prints a binary representation
//of "int value" with "int length" bits:
void prt_bin(int value, int length) {
  int i;
  for(i=(length-1); i>=0; i--) {
    if((value>>i)&1)
       cout << 1;
    else
       cout << 0;
  }
}


//returns an int array of 1s and 0s with 'length' bits
//converted from dec 'value'
int * dec_to_bin(int value, int length) {
  int i;
  int *bin_arr = new int[length];
  for(i=0; i<=length-1; i++) {
    if((value>>i)&1) {
      bin_arr[i] = 1;
    }
    else {
      bin_arr[i] = 0;
    }
  }

	int start = 0;
	int end = length-1;

	while(start < end)  {
		int temp = bin_arr[start];
		bin_arr[start] = bin_arr[end];
		bin_arr[end] = temp;
		start++;
		end--;
	}

  return bin_arr;
}


//takes a binary number in the form of an array
//and returns a decimal representation as an int
int bin_to_dec(int * arr)
{
	int dec_val = 0;
	int base = 1;
	for(int i=16; i>=0; i--) {
		dec_val += arr[i] * base;
		base *= 2;
	}

	return dec_val;
}

//takes two arrays and subtracts the values
//at each index from one another,
//returning these values in an array
int * sub_arr(int * arr1, int * arr2) {
	int * arr[8];
	int a;
	int b;

	for(int i=0; i<8; i++) {
		a = arr1[i];
		b = arr2[i];
		arr[i] = &a-b;
	}

	return *arr;
}

//takes and int and two arrays containing bits,
//then mreges the three into one array and returns this array
int * merge_arr(int arr1[], int arr2[], int c) {
	int *arr;
	arr = new int[17];

	arr[0] = c;
	for(int i=1; i<9; i++) {
		arr[i] = arr1[i-1];
	}
	for(int i=9; i<17; i++) {
		arr[i] = arr2[i-9];
	}
	return arr;
}


//takes user input, then performs a variety of console outputs
//and function calls to print the steps for hardware multiplication
int main() {
  int mq;
  int mdr;
  int c = 0;
  int acc = 0;


  //scanning for user input and validating it
  //ensuring that the numbers are ints between 0 and 255
  cout << "multiplicand: ";
  cin >> mdr;
  if(cin.fail() || 0>mdr || 255<mdr) {
    cout << "Please enter an integer in the range 0 to 255. Exiting...\n";
    exit(EXIT_FAILURE);
  }
  cout << "multiplier: ";
  cin >> mq;
  if(cin.fail() || 0>mq || 255<mq) {
    cout << "Please enter an integer in the range 0 to 255. Exiting...\n";
    exit(EXIT_FAILURE);
  }

  //store original values for output at the end
  int mq_hold = mq;
  int mdr_hold = mdr;

  //preliminary outputs
  cout << "\nc and acc set to 0\n";
  cout << "mq set to multiplier    =  " << mq << " decimal and ";
  prt_bin(mq,8);
  cout << " binary\n";
  cout << "mdr set to multiplicand =  " << mdr << " decimal and ";
  prt_bin(mdr,8);
  cout << " binary\n";

  
  //creating binary array version of register values
  int* acc_arr = dec_to_bin(acc,8);
  int* mq_arr = dec_to_bin(mq,8); 
  int* mdr_arr = dec_to_bin(mdr,8);

  int step = 1;

  //loops 8 times, printing out one step each time
  while(step < 9) {
		cout << "---------------------------------------------------\n";
		cout << "step " << step << ":   " << c << " ";
    
      //prints accumulator in binary
		acc_arr = dec_to_bin(acc,8);
		for(int i=0; i<8; i++) {
	    cout << acc_arr[i];
	  }

		cout << " ";
      
      //prints multiplier in binary
		mq_arr = dec_to_bin(mq,8);
		for(int i=0; i<8; i++) {
	    cout << mq_arr[i];
	  }

		cout << "\n        +   ";
      
      //prints multiplicand in binary
		mdr_arr = dec_to_bin(mdr,8);
		for(int i=0; i<8; i++) {
	    cout << mdr_arr[i];
	  }

		cout << "        ^ ";

      //checks whether addition should be performed in this step
      //by checking the least significant bit
		if(mq_arr[7] == 1) {
			cout << "add based on lsb=1\n";
			acc += mdr;
		}
		else {
			cout << "no add based on lsb=0\n";
		}

      //sets the carry value
		if(acc >= 256) {
			c = 1;
			acc -= 256;
		}
      
      //re-instantiate register value arrays
      //to accommodate accumulator addition
		int* acc_arr = dec_to_bin(acc,8);
		int* mq_arr = dec_to_bin(mq,8);
		int* mdr_arr = dec_to_bin(mdr,8);
      
      //merge acc, mq, and carry into one array for printing
		int* full_arr = merge_arr(acc_arr,mq_arr,c);
      
      //convert merged binary array to decimal for processing
		int full_int = bin_to_dec(full_arr);

		//print result of addition
		cout << "          ----------\n";

		cout << "          ";
      
		for(int i=0; i<17; i++) {
			cout << full_arr[i];
			if(i==0 || i==8)
				cout << " ";
		}
      
      //perform arithmetic shift right 1, then print again
		cout << "\n       >>                     shift right\n          ";

		full_int >>= 1;

		full_arr = dec_to_bin(full_int,17);

		for(int i=0; i<17; i++) {
			cout << full_arr[i];
			if(i==0 || i==8)
				cout << " ";
		}

		cout << "\n";

      //fix leading bits in mq and acc after shift
		mq >>= 1;
		if(acc_arr[7] == 1) {
			mq += 128;
		}
		mq_arr = dec_to_bin(mq,8);


		acc >>= 1;
		if(c == 1) {
			acc += 128;
			c = 0;
		}
		acc_arr = dec_to_bin(acc,8);

      //increment step counter
		step++;

      //after last step, print the multiplication check
		if(step==9) {
			cout << "---------------------------------------------------\n";

			cout << "check:                 binary   decimal\n";
        

         //print multiplicand in binary and decimal
			cout << "                     ";
			mdr_arr = dec_to_bin(mdr_hold,8);
			for(int i=0; i<8; i++) {
				cout << mdr_arr[i];
			}
			cout << "       " << mdr_hold;
        
         //print multiplier in binary and decimal
			cout << "\n           x         ";
			mq_arr = dec_to_bin(mq_hold,8);
			for(int i=0; i<8; i++) {
				cout << mq_arr[i];
			}
			cout << "  x    " << mq_hold;

			cout << "\n             ----------------    ------\n";
			cout << "             ";

         //print product in binary and decimal
			for(int i=1; i<17; i++) {
				cout << full_arr[i];
			}

			cout << "     " << (mq_hold*mdr_hold) << "\n";

		}
	}

  return 0;
}
