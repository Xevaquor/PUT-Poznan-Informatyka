#include "BstTree.h"
#include "AvlTree.h"
#include "PerfomanceCounter.h"
#include "RedBlackTree.h"

#include <vector>
#include <ctime>
#include <fstream>

using namespace std;

void GenerateRandomSequence(size_t n, vector<int> &seq)
{
	srand(time(NULL));
	for (size_t i = 0; i < n; i++)
	{
		seq.push_back(rand());
	}
}

const int REPEATS = 20;

void *gc;

void ProfileBstCreation(vector<int> &sequence)
{
	auto tree = new BstTree<int>();
	for (size_t i = 0; i < sequence.size(); i++)
	{
		tree->Add(sequence[i]);
	}
	gc = tree;
}

void ProfileAvlCreation(vector<int> &sequence)
{
	auto tree = new AvlTree<int>();
	for (size_t i = 0; i < sequence.size(); i++)
	{
		tree->Add(sequence[i]);
	}
	gc = tree;
}
void ProfileRBCreation(vector<int> &sequence)
{
	auto tree = new RedBlackTree<int>();
	for (size_t i = 0; i < sequence.size(); i++)
	{
		tree->Add(sequence[i]);
	}
	gc = tree;
}

void ProfileBstMinimize(BstTree<int> *tree)
{
	tree->MinimumValue();
}

void ProfileRBFind(RedBlackTree<int> *tree, int n )
{
	tree->Find(n);
}

void ProfileAvlMinimize(AvlTree<int> *tree)
{
	tree->GetMinimumValue();
}
void ProfileBstBalance(BstTree<int> *tree)
{
	tree->Balance();
}
void ProfileBstPrint(BstTree<int> *tree)
{
	tree->PrintAscending();
}
void ProfileAvlPrint(AvlTree<int> *tree)
{
	tree->PrintAscending();
}

PerfomanceCounter dyno;
//vector<size_t> probes = { 10, 100, 1000, 10000, 60000, 120000, 250000, 500000, 750000, 1000000, 1500000, 1750000, 2500000, 5000000, 10000000 };
//vector<size_t> probes = { 10, 100, 1000, 10000, 20000, 60000, 120000, 250000, 500000, 750000, 1000000 };
vector<size_t> probes = { 10, 100, 200, 500, 1000, 5000, 10000, 20000, 50000, 75000, 100000, 125000,150000,175000,200000,350000,500000,750000,1000000 };
void PerfCreationBst()
{
	ofstream f("BST.txt");
	for (size_t &probe : probes)
	{
		f << probe << ' ';
	}
	f << '\n';

	for (int repeat = 0; repeat < REPEATS; repeat++)
	{
		cout << "Repeat " << repeat << "/" << REPEATS << '\n';
		for (size_t &probe : probes)
		{
			cout << "Probe size: " << probe << "\n";
			vector<int> sequence;
			GenerateRandomSequence(probe, sequence);

			auto exeTime = dyno.MeasureExecutionTime(ProfileBstCreation, sequence);
			delete gc;
			f << exeTime << ' ';
			cout << exeTime << " s\n";

			f.flush();
		}
		f << endl;
	}
	f.close();
}
void PerfCreationAvl()
{
	ofstream f("AVL.txt");
	for (size_t &probe : probes)
	{
		f << probe << ' ';
	}
	f << '\n';

	for (int repeat = 0; repeat < REPEATS; repeat++)
	{
		cout << "Repeat " << repeat << "/" << REPEATS << '\n';
		for (size_t &probe : probes)
		{
			cout << "Probe size: " << probe << "\n";
			vector<int> sequence;
			GenerateRandomSequence(probe, sequence);

			auto exeTime = dyno.MeasureExecutionTime(ProfileAvlCreation, sequence);
			delete gc;
			f << exeTime << ' ';
			cout << exeTime << " s\n";

			f.flush();
		}
		f << endl;
	}
	f.close();
}

void PerfCreateRB()
{
	ofstream f("RB.txt");
	for (size_t &probe : probes)
	{
		f << probe << ' ';
	}
	f << '\n';

	for (int repeat = 0; repeat < REPEATS; repeat++)
	{
		cout << "Repeat " << repeat << "/" << REPEATS << '\n';
		for (size_t &probe : probes)
		{
			cout << "Probe size: " << probe << "\n";
			vector<int> sequence;
			GenerateRandomSequence(probe, sequence);

			auto exeTime = dyno.MeasureExecutionTime(ProfileRBCreation, sequence);
			delete gc;
			f << exeTime << ' ';
			cout << exeTime << " s\n";

			f.flush();
		}
		f << endl;
	}
	f.close();
}


void PerfMinimizeBst()
{
	ofstream f("BSTmin.txt");
	for (size_t &probe : probes)
	{
		f << probe << ' ';
	}
	f << '\n';

	for (int repeat = 0; repeat < REPEATS; repeat++)
	{
		cout << "Repeat " << repeat << "/" << REPEATS << '\n';
		for (size_t &probe : probes)
		{
			cout << "Probe size: " << probe << "\n";
			vector<int> sequence;
			GenerateRandomSequence(probe, sequence);

			BstTree<int> *tree = new BstTree<int>();
			for (size_t i = 0; i < sequence.size(); i++)
			{
				tree->Add(sequence[i]);
			}

			auto exeTime = dyno.MeasureExecutionTime(ProfileBstMinimize, tree);
			delete tree;
			f << exeTime << ' ';
			cout << exeTime << " s\n";

			f.flush();
		}
		f << endl;
	}
	f.close();
}
void PerfBalance()
{
	ofstream f("balance.txt");
	for (size_t &probe : probes)
	{
		f << probe << ' ';
	}
	f << '\n';

	for (int repeat = 0; repeat < REPEATS; repeat++)
	{
		cout << "Repeat " << repeat << "/" << REPEATS << '\n';
		for (size_t &probe : probes)
		{
			cout << "Probe size: " << probe << "\n";
			vector<int> sequence;
			GenerateRandomSequence(probe, sequence);

			BstTree<int> *tree = new BstTree<int>();
			for (size_t i = 0; i < sequence.size(); i++)
			{
				tree->Add(sequence[i]);
			}

			auto exeTime = dyno.MeasureExecutionTime(ProfileBstBalance, tree);
			delete tree;
			f << exeTime << ' ';
			cout << exeTime << " s\n";

			f.flush();
		}
		f << endl;
	}
	f.close();
}
void PerfMinimizeAvl()
{
	ofstream f("AVLmin.txt");
	for (size_t &probe : probes)
	{
		f << probe << ' ';
	}
	f << '\n';

	for (int repeat = 0; repeat < REPEATS; repeat++)
	{
		cout << "Repeat " << repeat << "/" << REPEATS << '\n';
		for (size_t &probe : probes)
		{
			cout << "Probe size: " << probe << "\n";
			vector<int> sequence;
			GenerateRandomSequence(probe, sequence);

			AvlTree<int> *tree = new AvlTree<int>();
			for (size_t i = 0; i < sequence.size(); i++)
			{
				tree->Add(sequence[i]);
			}

			auto exeTime = dyno.MeasureExecutionTime(ProfileAvlMinimize, tree);
			delete tree;
			f << exeTime << ' ';
			cout << exeTime << " s\n";

			f.flush();
		}
		f << endl;
	}
	f.close();
}void PerfPrintAvl()
{
	ofstream f("AVLprint.txt");
	for (size_t &probe : probes)
	{
		f << probe << ' ';
	}
	f << '\n';

	for (int repeat = 0; repeat < REPEATS; repeat++)
	{
		cout << "Repeat " << repeat << "/" << REPEATS << '\n';
		for (size_t &probe : probes)
		{
			cout << "Probe size: " << probe << "\n";
			vector<int> sequence;
			GenerateRandomSequence(probe, sequence);

			AvlTree<int> *tree = new AvlTree<int>();
			for (size_t i = 0; i < sequence.size(); i++)
			{
				tree->Add(sequence[i]);
			}

			auto exeTime = dyno.MeasureExecutionTime(ProfileAvlPrint, tree);
			delete tree;
			f << exeTime << ' ';
			cout << exeTime << " s\n";

			f.flush();
		}
		f << endl;
	}
	f.close();
}
void PerfPrintBst()
{
	ofstream f("BSTprint.txt");
	for (size_t &probe : probes)
	{
		f << probe << ' ';
	}
	f << '\n';

	for (int repeat = 0; repeat < REPEATS; repeat++)
	{
		cout << "Repeat " << repeat << "/" << REPEATS << '\n';
		for (size_t &probe : probes)
		{
			cout << "Probe size: " << probe << "\n";
			vector<int> sequence;
			GenerateRandomSequence(probe, sequence);

			BstTree<int> *tree = new BstTree<int>();
			for (size_t i = 0; i < sequence.size(); i++)
			{
				tree->Add(sequence[i]);
			}

			auto exeTime = dyno.MeasureExecutionTime(ProfileBstPrint, tree);
			delete tree;
			f << exeTime << ' ';
			cout << exeTime << " s\n";

			f.flush();
		}
		f << endl;
	}
	f.close();
}
void PerfFindRB()
{
	ofstream f("RBfind.txt");
	for (size_t &probe : probes)
	{
		f << probe << ' ';
	}
	f << '\n';

	for (int repeat = 0; repeat < REPEATS; repeat++)
	{
		cout << "Repeat " << repeat << "/" << REPEATS << '\n';
		for (size_t &probe : probes)
		{
			cout << "Probe size: " << probe << "\n";
			vector<int> sequence;
			GenerateRandomSequence(probe, sequence);
			int n = rand();
			RedBlackTree<int> *tree = new RedBlackTree<int>();
			for (size_t i = 0; i < sequence.size(); i++)
			{
				tree->Add(sequence[i]);
			}

			auto exeTime = dyno.MeasureExecutionTime(ProfileRBFind, tree, n);
			delete tree;
			f << exeTime << ' ';
			cout << exeTime << " s\n";

			f.flush();
		}
		f << endl;
	}
	f.close();
}

void PerfCreation()
{
	cout << "BST: \n";
	PerfCreationBst();
	cout << "AVL: \n";
	PerfCreationAvl();
}
void PerfMinimize()
{
	cout << "BST: \n";
	PerfMinimizeBst();
	cout << "AVL: \n";
	PerfMinimizeAvl();
}

void PerfRB()
{
	cout << "create: \n";
	PerfCreateRB();
	cout << "find: \n";
	PerfFindRB();
}

void PerfPrint()
{
	cout << "BST: \n";
	PerfPrintBst();
	cout << "AVL: \n";
	PerfPrintAvl();
}

void Perf()
{
	/*cout << "Profile creation:\n";
	PerfCreation();
	cout << "Minimize:n";
	PerfMinimize();
	PerfBalance();
*/
	//PerfPrint();

	PerfRB();


}