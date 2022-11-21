//============================================================================
// Name        : 31365_Assignment-04.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class First_fit
{
public:
	void first(int holes[], int processes[], int num_holes, int num_process)
	{
		int holes_f[num_holes];
		for(int i=0;i<num_holes;i++)
		{
			holes_f[i]=holes[i];
		}

		int proc[num_process];
		for(int i=0;i<num_process;i++)
		{
			proc[i]=processes[i];
		}

		int allocate[num_process];
		for(int i=0;i<num_process;i++)
		{
			allocate[i]=-1;
		}

		for(int i=0;i<num_process;i++)
		{
			for(int j=0;j<num_holes;j++)
			{
				if(proc[i]<=holes_f[j])
				{
					holes_f[j]=holes_f[j]-proc[i];
					allocate[i]=j;
					break;
				}
			}
		}
		cout<<"Process No.\tProcess Size\tBlock No."<<endl;
		for(int i=0;i<num_process;i++)
		{
			cout<<i+1<<"\t\t"<<proc[i]<<"\t\t";
			if(allocate[i]!=-1)
				cout<<allocate[i]+1;
			else
				cout<<"Not allocated";
			cout<<endl;
		}
	}
};

class Next_fit
{
public:
	void next(int holes[], int processes[], int num_holes, int num_process)
	{
		int holes_f[num_holes];
		for(int i=0;i<num_holes;i++)
		{
			holes_f[i]=holes[i];
		}

		int proc[num_process];
		for(int i=0;i<num_process;i++)
		{
			proc[i]=processes[i];
		}

		int allocate[num_process];
		for(int i=0;i<num_process;i++)
		{
			allocate[i]=-1;
		}

		int ptr=0,i=0;
		for(int j=0;j<num_process;j++)
		{
			//int i=0;
			if(ptr==num_holes-1)
				i=0;
			while(i<num_holes)
			{
				if(proc[j]<=holes_f[i])
				{
					holes_f[i]=holes_f[i]-proc[j];
					allocate[j]=i;
					ptr=i;
					break;
				}
				//i=(i+1)%num_holes;
				i++;
			}
		}
		cout<<"Process No.\t\tProcess Size\tBlock No."<<endl;
		for(int i=0;i<num_process;i++)
		{
			cout<<i+1<<"\t\t"<<proc[i]<<"\t\t";
			if(allocate[i]!=-1)
				cout<<allocate[i]+1;
			else
				cout<<"Not allocated";
			cout<<endl;
		}
	}
};

class Best_fit
{
public:
	void best(int holes[], int processes[], int num_holes, int num_process)
	{
		int holes_f[num_holes];
		for(int i=0;i<num_holes;i++)
		{
			holes_f[i]=holes[i];
		}

		int proc[num_process];
		for(int i=0;i<num_process;i++)
		{
			proc[i]=processes[i];
		}

		int allocate[num_process];
		for(int i=0;i<num_process;i++)
		{
			allocate[i]=-1;
		}

		for(int j=0;j<num_process;j++)
		{
			int best_block=-1;
			for(int i=0;i<num_holes;i++)
			{
				if(holes_f[i]>=proc[j])
				{
					if(best_block==-1)
						best_block=i;
					else if(holes_f[i]<holes_f[best_block])
						best_block=i;
				}
			}
			if(best_block!=-1)
			{
				allocate[j]=best_block;
				holes_f[best_block]=holes_f[best_block]-proc[j];
			}
		}
		cout<<"Process No.\tProcess Size\tBlock No."<<endl;
		for(int i=0;i<num_process;i++)
		{
			cout<<i+1<<"\t\t"<<proc[i]<<"\t\t";
			if(allocate[i]!=-1)
				cout<<allocate[i]+1;
			else
				cout<<"Not allocated";
			cout<<endl;
		}
	}
};

class Worst_fit
{
public:
	void worst(int holes[], int processes[], int num_holes, int num_process)
	{
		int holes_f[num_holes];
		for(int i=0;i<num_holes;i++)
		{
			holes_f[i]=holes[i];
		}

		int proc[num_process];
		for(int i=0;i<num_process;i++)
		{
			proc[i]=processes[i];
		}

		int allocate[num_process];
		for(int i=0;i<num_process;i++)
		{
			allocate[i]=-1;
		}

		for(int j=0;j<num_process;j++)
		{
			int max=-1;
			for(int i=0;i<num_holes;i++)
			{
				if(holes_f[i]>=proc[j])
				{
					if(max==-1)
						max=i;
					else if(holes_f[i]>holes_f[max])
						max=i;
				}
			}
			if(max!=-1)
			{
				allocate[j]=max;
				holes_f[max]=holes_f[max]-proc[j];
			}
		}
		cout<<"Process No.\tProcess Size\tBlock No."<<endl;
		for(int i=0;i<num_process;i++)
		{
			cout<<i+1<<"\t\t"<<proc[i]<<"\t\t";
			if(allocate[i]!=-1)
				cout<<allocate[i]+1;
			else
				cout<<"Not allocated";
			cout<<endl;
		}
	}
};
int main() {
	int nh,np;
	cout<<"Enter number of processes: "<<endl;
	cin>>np;
	int processes[np];
	for(int i=0;i<np;i++)
	{
		cout<<"Size of process"<<i+1<<endl;
		cin>>processes[i];
	}
	cout<<"Enter number of blocks/holes: "<<endl;
	cin>>nh;
	int holes[nh];
	for(int i=0;i<nh;i++)
	{
		cout<<"Size of hole"<<i+1<<endl;
		cin>>holes[i];
	}

	bool flag=true;
	int choice;
	while(flag)
	{
		cout<<"\n1.First\n2.Next\n3.Best\n4.Worst"<<endl;
		cin>>choice;
		switch(choice)
		{
		case 1:
			cout<<"First Fit\n";
			First_fit obj1;
			obj1.first(holes, processes, nh,np);
			cout<<endl;
			break;
		case 2:
			cout<<"Next Fit\n";
			Next_fit obj2;
			obj2.next(holes, processes, nh,np);
			cout<<endl;
			break;
		case 3:
			cout<<"Best Fit\n";
			Best_fit obj3;
			obj3.best(holes, processes, nh,np);
			cout<<endl;
			break;
		case 4:
			cout<<"Worst Fit\n";
			Worst_fit obj4;
			obj4.worst(holes, processes, nh,np);
			cout<<endl;
			break;

		}
	}

	return 0;
}
