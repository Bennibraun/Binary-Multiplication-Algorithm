#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string>
using namespace std;


/*
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
	int end = 15;

	while(start < end)  {
		int temp = bin_arr[start];
		bin_arr[start] = bin_arr[end];
		bin_arr[end] = temp;
		start++;
		end--;
	}

  return bin_arr;
}

int bin_to_dec(int * arr)
{
	int dec_val = 0;


	for (int i = 0; i < 16; i++) {
		int num = arr[i];
		if (num != 0) {
				while (num > 0) {
					dec_val *= 10;
					num /= 10;
				}
				dec_val += arr[i];
		}
		else {
				dec_val *= 10;
		}
	}
}

int main() {
  int* arr = dec_to_bin(35,16);
  cout << '\n';
  for(int i=0; i<16; i++) {
    cout << arr[i];
  }
  cout << '\n' << '\n';

	int arr2[4] = {1,1,1,1};
	cout << bin_to_dec(arr2);

	cout << '\n' << '\n';

  return 0;
}
*/


int * merge_arr(int arr1[], int arr2[], int c) {
	int arr[17];

	arr[0] = c;
	for(int i=1; i<9; i++) {
		arr[i] = arr1[i];
	}
	for(int i=9; i<17; i++) {
		arr[i] = arr2[i];
	}
	return arr;
}


int main() {
  int mq;
  int mdr;
  int c = 0;
  int acc = 0;

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

  cout << "\nc and acc set to 0\n";
  cout << "mq set to multiplier    =  " << mq << " decimal and ";
  prt_bin(mq,8);
  cout << " binary\n";
  cout << "mdr set to multiplicand =  " << mdr << " decimal and ";
  prt_bin(mdr,8);
  cout << " binary\n";


	int* acc_arr = dec_to_bin(acc,8);
	int* mq_arr = dec_to_bin(mq,8);
	int* mdr_arr = dec_to_bin(mdr,8);

	int step = 1;

	while(true) {
		cout << "---------------------------------------------------\n";
		cout << "step " << step << ":   " << c << " ";

		acc_arr = dec_to_bin(acc,8);
		for(int i=0; i<8; i++) {
	    cout << acc_arr[i];
	  }

		cout << " ";

		mq_arr = dec_to_bin(mq,8);
		for(int i=0; i<8; i++) {
	    cout << mq_arr[i];
	  }

		cout <<  "\n        +   ";

		mdr_arr = dec_to_bin(mdr,8);
		for(int i=0; i<8; i++) {
	    cout << mdr_arr[i];
	  }

		cout << "        ^ ";


/*
		if(mq_arr[7] == 1) {
			cout << "add based on lsb=1\n";
			cout << "          ----------\n";
			cout << "          " << c << " ";
			acc += mdr;
			if(acc >= 256) {
				c = 1;
			}

			acc_arr = dec_to_bin(acc,8);
			for(int i=0; i<8; i++) {
		    cout << acc_arr[i];
		  }

			cout << " ";

			mq_arr = dec_to_bin(mq,8);
			for(int i=0; i<8; i++) {
		    cout << mq_arr[i];
		  }
		}
    else {
      cout << "no add based on lsb=0\n";
    }

*/


		if(mq_arr[7] == 1) {
			cout << "add based on lsb=1\n";
			acc += mdr;
		}
		else {
			cout << "no add based on lsb=0\n";
		}


		if(acc >= 256) {
			c = 1;
		}

		int* full_arr = merge_arr(*acc_arr,*mq_arr,c);

		c = 0;

		cout << "\nTesting... the binary version of merge is as follows:\n";

		for(int i=0; i<16; i++) {
			cout << full_arr[i];
		}
		cout << "\n";

		int full_int = bin_to_dec(full_arr);

		cout << "The result is....:  " << full_int << "\n";

		//print result of addition
		cout << "          ----------\n";



//Note to self: Rearrange these if/else statements as follows:
//the if and else each need to contain only the 'add based on' statements
//and in the case of the if, add the acc.
//The printing of the next line (the added result) can be handled after
//the if/else stuff.
//Also, make sure to rewrite that print to use the merge function
//in order to accommodate carries more easily
//Write a function to either convert the merge array to decimal
//or to combine the int values of the three variables somehow (c,acc,mdr)
//Then use >>= to shift right one bit and print the merge again before loop

			cout << "\n       >>                     shift right\n";


		step++;
		if(step==3) {
			break;
		}
	}



  return 0;
}
