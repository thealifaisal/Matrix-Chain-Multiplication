#include <iostream>
#include <sstream>

using namespace std;

class Matrix{
	
	private: 
		
		string name = "A";
		int x, y;
		
	public:
		
		void setMatrix(int i, int j, int matNum)
		{
			this->x = i;
			this->y = j;
			
			// converting int to string
			string sNum;
			stringstream ss;
			ss<<matNum;
			ss>>sNum;
			
			name += sNum;
		}
		
		void printMatrix()
		{
			cout<<"Name: "<<name<<"\tOrder: "<<x<<"x"<<y<<"\n";
		}
};

int MCM(int i, int j);
void createTable(int numMatrices);
void printTable(int numMatrices);

int d[] = {3,2,5,6,3};

int **M, **kTable;

int main()
{
	int nD = sizeof(d)/sizeof(int); // number of orders
	int matCount = nD-1;	// number of matrices
	
	Matrix arrMat[matCount+1];
	
	for(int i=1; i<=matCount; i++)
	{
		arrMat[i].setMatrix(d[i-1], d[i], i);
		arrMat[i].printMatrix();
	}
	
	createTable(matCount);
	
	cout<<"\n\nMinimum Cost Of Multiplying Matrices: "<<MCM(1, matCount)<<"\n\n";
	
	printTable(matCount);
}

int MCM(int i, int j)
{
	if(i == j)
	{
		return M[i][j] = 0;
	}
	
	int min = INT_MAX, kVal;
	
	for(int k=i; k<j; k++)
	{
		if(M[i][k] == -1)
		{
			M[i][k] = MCM(i, k);
		}
		
		if(M[k+1][j] == -1)
		{
			M[k+1][j] = MCM(k+1, j);
		}
		
		int x = M[i][k] + M[k+1][j] + d[i-1] * d[k] * d[j];
		
		if(x < min)
		{
			kVal = k;
			min = x;
		}
	}
	
	kTable[i][j] = kVal;
	return M[i][j] = min;
}

void createTable(int numMatrices)
{
	M = new int*[numMatrices+1];
	for(int i=0; i<numMatrices+1; i++)
	{
		M[i] = new int[numMatrices+1];
	}
	
	for(int i=1; i<=numMatrices; i++)
	{
		for(int j=1; j<=numMatrices; j++)
		{
			M[i][j] = -1;
		}
	}
	
	kTable = new int*[numMatrices+1];
	for(int i=0; i<numMatrices+1; i++)
	{
		kTable[i] = new int[numMatrices+1];
	}
	
	for(int i=1; i<=numMatrices; i++)
	{
		for(int j=1; j<=numMatrices; j++)
		{
			kTable[i][j] = 0;
		}
	}
}

void printTable(int numMatrices)
{
	cout<<"\n\nMemoization Table\n\n";
	for(int i=1; i<=numMatrices; i++)
	{
		for(int j=1; j<=numMatrices; j++)
		{
			cout<<M[i][j]<<"\t";
		}
		cout<<"\n\n";
	}
	
	cout<<"\n\nk Table\n\n";
	for(int i=1; i<=numMatrices; i++)
	{
		for(int j=1; j<=numMatrices; j++)
		{
			cout<<kTable[i][j]<<"\t";
		}
		cout<<"\n\n";
	}
}
