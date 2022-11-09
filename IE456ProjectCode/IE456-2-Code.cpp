#include <vector>
#include "string"
#include <fstream>
#include <iostream>
#include <chrono>
#include <cmath>
#include <filesystem>


using namespace std;
typedef vector<string> ArrString;

class Node { // Node class is defined to construct realizations of degree sequences
public:
	int ID;  // ID of the node
	int currentdeg; // Current degree of the node initially 0
	int desireddeg; // Desired degree assigned to the node by the degree sequence
	vector<int> adj_ver; // Vector of adjacent vertices

public:
	Node(int id,int desdeg) :ID(id),desireddeg(desdeg), currentdeg(0) {}

	void AddNeighbour(Node* n) {  // Given a node a link is created between the given node and the node itself by updating current, desired degrees and adjacency lists
		desireddeg--;
		currentdeg++;
		adj_ver.push_back(n->ID);
		n->desireddeg--;
		n->currentdeg++;
		n->adj_ver.push_back(ID);
	}
	bool IsNeighbor(Node* n) { // Returns true if the node is already neighbor with the given node
		bool isneighbor = false;
		for (auto a :adj_ver)
		{
			if (a == n->ID) { isneighbor = true; }
		}
		return isneighbor;
	}


};

// Elementary functions (sorting, summation, counting positives etc.)

void CreateNodes(vector<int> degreesequence, vector<Node*>& Nodes) { // Function to initialize the nodes with distinct ID's and given desired degrees
	for (int i = 0; i < degreesequence.size(); i++)
	{
		Nodes.push_back(new Node(i, degreesequence[i]));

	}

}

void ResetNodes(vector<Node*>& Nodes, vector<int> degreesequence) {		// Destroys the given nodes and creates nodes with the given degree sequences
	for (int i = 0; i < Nodes.size(); i++) {
		delete Nodes[i];
		Nodes.erase(Nodes.begin() + i);
		i--;
	}
	CreateNodes(degreesequence, Nodes);
}

void DeleteNodes(vector<Node*> Nodes) {			//Destroys the given nodes and the vector
	for (int i = 0; i < Nodes.size(); i++) {
		delete Nodes[i];
		Nodes.erase(Nodes.begin() + i);
		i--;
	}
}

void SortNodesDegree(vector<Node*>& Nodes) { //Sorts the vector of nodes with respect to their desired degrees in descending order (Bubble Sort)
	for (int i = 0; i < Nodes.size()-1;i++) {
		for (int j = i+1; j < Nodes.size(); j++) {
			if (Nodes[i]->adj_ver.size() < Nodes[j]->adj_ver.size()) {
				Node* temp = Nodes[i];
				Nodes[i]=Nodes[j];
				Nodes[j] = temp;
			}
		}
	}
}

void SortNodesID(vector<Node*>& Nodes) { //Sorts the vector of nodes with respect to their IDs in ascending order (Bubble Sort)
	for (int i = 0; i < Nodes.size() - 1; i++) {
		for (int j = i + 1; j < Nodes.size(); j++) {
			if (Nodes[i]->ID > Nodes[j]->ID) {
				Node* temp = Nodes[i];
				Nodes[i] = Nodes[j];
				Nodes[j] = temp;
			}
		}
	}
}

int Vectorsum(vector<int> values, int startindex, int endindex) { // Returns the sum of the elements in a vector
	int sum = 0;
	for (int i = startindex; i <= endindex; i++) {
		sum += values[i];
	}
	return sum;
}

int minVectorsum(vector<int> values, int startindex, int endindex) { // Function that returns the second (RHS) sum in the Erdös-Gallai Graphicality Condition
	if (startindex > endindex) { return 0; }
	int sum = 0;
	for (int i = startindex; i <= endindex; i++) {
		if (startindex  < values[i]) {
			sum += startindex;
		}
		else {
			sum += values[i];
		}
		
	}
	return sum;
}

void Sort(vector<int>& degreeseq) { //Sorts a vector of numbers in descending order (Bubble Sort)
	for (int i = 0; i < degreeseq.size() - 1; i++) {
		for (int j = i + 1; j < degreeseq.size(); j++) {
			if (degreeseq[i] < degreeseq[j]) {
				int temp = degreeseq[i];
				degreeseq[i] = degreeseq[j];
				degreeseq[j] = temp;
			}
		}
	}

}


int partition(vector<int>& values, int left, int right) { // Creates a partition of the vector to quicksort
	int pivotIndex = left + (right - left) / 2;
	int pivotValue = values[pivotIndex];
	int i = left, j = right;
	int temp;
	while (i <= j) {
		while (values[i] > pivotValue) {
			i++;
		}
		while (values[j] < pivotValue) {
			j--;
		}
		if (i <= j) {
			temp = values[i];
			values[i] = values[j];
			values[j] = temp;
			i++;
			j--;
		}
	}
	return i;
}

void quicksort(vector<int>& degreeseq, int startindex, int endindex) { //Sorts the vector of nodes with respect to their desired degrees in descending order (Quick Sort)
	if (startindex < endindex) {
		int pivotIndex = partition(degreeseq, startindex, endindex);
		quicksort(degreeseq, startindex, pivotIndex - 1);
		quicksort(degreeseq, pivotIndex, endindex);
	}
}

int CountPositiveDegree(vector<Node*>& Nodes) { // Returns the number of nodes with positive desired degree minus 1 (Since used in Havel Hakimi Test it does not count the node with max degree)
	int pos_count = 0;
	for (auto a : Nodes) {
		if (a->desireddeg > 0) { pos_count++; }
	}
	return pos_count - 1;
}

int CountPositive(vector<int>& degreeseq) {// Returns the number of positive numbers minus 1 (Since used in Havel Hakimi Test it does not count the max degree)
	int pos_count = 0;
	for (auto a : degreeseq) {
		if (a > 0) { pos_count++; }
	}
	return pos_count - 1;
}




// Input - Output Functions

ArrString readDelimated(string line)
{
	ArrString result;
	int index = 0;
	while (index != string::npos)
	{
		result.push_back(line.substr(0, index = line.find_first_of(" \t\n")));
		line = line.substr(index + 1);
	}
	return result;
}

void ReadSequence(string PathIn, vector<int>& Sequence)
{
	string Path = PathIn;

	ifstream myfile(Path);
	if (myfile.is_open())
	{
		string line;
		ArrString contents;
		//char delim[3] = { ' ', '\t', '\n' };

		getline(myfile, line); //discarding first line you can use it
		///
		while (getline(myfile, line)) // takes the input line by line
		{
			contents = readDelimated(line);
			for (string s : contents)
				Sequence.push_back(stoi(s));
		}
	}
	myfile.close();
}


bool ReadSequenceGenerateGraph(string PathIn, vector<int>& Sequence, vector<vector<int>>& AdjMatrix) {
	string Path = PathIn;

	ifstream myfile(Path);
	if (myfile.is_open())
	{
		string line;
		ArrString contents;
		//char delim[3] = { ' ', '\t', '\n' };

		getline(myfile, line); //discarding first line you can use it
		contents = readDelimated(line);
		if (contents[0]=="Failed"|| contents[0] == "N/A" ||stoi(contents[0]) == 0) {
			return false;
		}
							   
		///
		getline(myfile, line);
		contents = readDelimated(line);
		if (contents[contents.size() - 1] == "") {
			contents.pop_back();
		}
		for (string s : contents)
			Sequence.push_back(stoi(s));

		while (getline(myfile, line)) // takes the input line by line
		{
			contents = readDelimated(line);
			if (contents[contents.size() - 1] == "") {
				contents.pop_back();
			}
			int NodeIndex = stoi(contents[0])-1;
			AdjMatrix.push_back(vector <int> ());

			for (int j = 1; j < contents.size(); j++) {
				AdjMatrix[NodeIndex].push_back(stoi(contents[j]) - 1);
			}
		}
	}
	myfile.close();
	return true;
}


bool OutputTest(vector<vector<int>> AdjMatrix, vector<int> Sequence) {
	
	vector<int> OutputDegreeSeq;
	bool IsLoop = false, IsMult = false;

	for (int i = 0; i < AdjMatrix.size(); i++)
	{
		for (int j = 0; j < AdjMatrix[i].size(); j++)
		{
			if (IsLoop && IsMult)
				break;

			if (AdjMatrix[i][j] == i && !IsLoop) {
				cout << "Node " << i + 1 << " contains a loop." << endl;
				IsLoop = true;
			}

			for (int k = j+1; k < AdjMatrix[i].size(); k++)
			{
				if (IsMult)
					break;
				if (AdjMatrix[i][j] == AdjMatrix[i][k]) {
					cout << "Node " << i + 1 << " contains multiple edges." << endl;
					IsMult = true;
				}

			}
		}
		OutputDegreeSeq.push_back(AdjMatrix[i].size());
	}
	OtherTest:
	if (Sequence.size() != OutputDegreeSeq.size()) {
		cout << "Input sequence order is " << Sequence.size() << endl;
		cout << "Output graph order is " << OutputDegreeSeq.size() << endl;
		return false;
	}

	Sort(OutputDegreeSeq);
	Sort(Sequence);

	for (int i = 0; i < Sequence.size(); i++) {
		if (Sequence[i] != OutputDegreeSeq[i]) {
			cout << "Degree Seq is not the same with the input" << endl;
			return false;
		}
	}

	if (IsLoop || IsMult)
		return false;

	return true;

}


void WriteOutput(string PathOut,vector<Node*> Nodes)
{
	ofstream fs;
	fs.open(PathOut, std::ios_base::app);
	fs << Nodes.size() <<endl;
	for (int i = 0; i < Nodes.size(); i++)
	{
		for ( int j = 0; j < Nodes[i]->adj_ver.size(); j++)
		{
			fs << Nodes[i]->adj_ver[j] + 1 << " ";
		}
		fs << endl;
	}
	fs.close();
}



// Havel Hakimi Alg. for generating realization of degree sequences

bool HavelHakimi(vector<Node*>& Nodes) {			// Havel Hakimi graph generation, returns false if the sequence is not graphical
	SortNodesDegree(Nodes);							// Sort the nodes with respect to their desired degrees in descending order
	int max_degree = Nodes[0]->desireddeg;			// Set max degree to the desired degree of the first node
	if (max_degree==0) {							// Stop if the max degree is zero the sequence is graphical and a realization is obtained 
		return true; }
	if (CountPositiveDegree(Nodes) < max_degree) { return false; }		//If the max degree sequence is larger than the number of other positive degrees stop, the sequence is not graphical
	for (int i = 1; i <= max_degree; i++)
	{
		Nodes[0]->AddNeighbour(Nodes[i]);   // Create link with nodes having the maximum desired degree until the first nodes desired degree reaches to 0
	}
	return HavelHakimi(Nodes); // Use recursion until all desired degrees are 0

}


// Graphicality Check Algorithms

bool HavelHakimiTest(vector<int> degreeseq) { //Havel Hakimi graphicality test that returns true if the degree sequence is graphical. 
	quicksort(degreeseq,0,degreeseq.size()-1); // Sort the sequence in descending order
	int max_degree = degreeseq[0]  ;     //Max degree is the first element in the sequence
	if (max_degree==0)
	{
		return true;					//Stop if the max degree is zero the sequence is graphical
	}
	if (CountPositive(degreeseq) < max_degree) { return false; }	// If the max degree sequence is larger than the number of other positive degrees stop, the sequence is not graphical
	degreeseq.erase(degreeseq.begin());
	for (int i = 0; i < max_degree; i++)
	{
		degreeseq[i]--;				//Extract 1 from maximum positive degrees, repeat "max degree" times.
	}
	return HavelHakimiTest(degreeseq); // Use recursion to check the remaining sequence.
}

bool ErdosG(vector<int> degreeseq) {				//Erdös-Gallai Graphicality check, returns true if the sequence is graphical.
	quicksort(degreeseq,0,degreeseq.size()-1);		//Sort the sequence 
	int m = 0;										// To use the improvement proposed by the authors we defined the durfee number
	int sum = 0;
	for (int i = 0; i < degreeseq.size(); i++)		
	{
		if (degreeseq[i] >= (i - 1)) { m=i; }		// To determine Durfee number we look for the first index in which d(i) is larger than or equal to (i-1)
		sum += degreeseq[i];						// Moreover we calculate the sum of the degrees to check whether it is an even number
	}
	if (sum % 2 == 1) {
		return false;								// If sum is not even stop, the sequence is not graphical
	}
	for (int k = 1; k <= m; k++)					// Erdös Gallai inequality is checked for the first m indices
	{
		if (Vectorsum(degreeseq, 0, k - 1) > (k * (k - 1) + minVectorsum(degreeseq, k, degreeseq.size() - 1))) {
			return false;							// If the Erdös-Gallai inequality is not satisfied stop, the sequence is not graphical
		}
	}
	return true;									// Otherwise the sequence is graphical

}


//Pairing Algorithm for generating realization of degree sequences

bool Pairing(vector<Node*>& Nodes) {
	while(1){
		vector<Node*> AvailableNodes = {}; //Initialize the available nodes vector as empty
		for (auto a : Nodes)			   //Insert all Nodes with Desired Degree larger than 0
		{
			if (a->desireddeg > 0) { AvailableNodes.push_back(a); }
		}
		int  firstindex = rand() % AvailableNodes.size();   //Select a random indice for the first vertex to create an edge
		Node* FirstSelect = AvailableNodes[firstindex];		//Keep the pointer of the first selected vertex in First Select
		AvailableNodes.erase(AvailableNodes.begin() + firstindex); //Exclude the selected vertex from the vector to avoid loops

		for (int i = 0; i < AvailableNodes.size(); i++) {  //Eliminate the all neighbors of the selected vertex from available set to avoid multiple edges
			if (FirstSelect->IsNeighbor(AvailableNodes[i])) { AvailableNodes.erase(AvailableNodes.begin() + i); i--; }
		}
		if (AvailableNodes.size() == 0) { return false; }//In case one vertex do not have any other vertex to match with return false to restart the algorithm
		int secondindex = rand() % AvailableNodes.size();// Select random indice for the second vertex
		Node* SecondSelect = AvailableNodes[secondindex];// Keep the pointer of the second vertex
		FirstSelect->AddNeighbour(SecondSelect); // Create the edge
		int degree_sum = 0;		//If all vertices have 0 desired edge then stop
		for (auto a : Nodes)
		{
			degree_sum += a->desireddeg;
		}
		if (degree_sum == 0) { return true; }
	
	}
}



//Initial Sequential Algorithm

int SelectRandomIndex(vector<int> AvailableIndices, vector<int> degreeseq) { // Returns an index with probability proportional to its degree
	vector<float> AvailableDegrees; 
	float temp_sum = 0;
	for (auto a : AvailableIndices) { // Create a vector containing the degrees of available indices
		AvailableDegrees.push_back(float(degreeseq[a]));
		temp_sum += float(degreeseq[a]); // Calculate the sum of the degrees
	}
	for (int i = 0; i < AvailableDegrees.size();i++) {
		AvailableDegrees[i] = AvailableDegrees[i] / temp_sum; // Divide each degree to the sum of the degrees to obtain a probability distribution
	}
	float cum_prob = float(rand()) / float(RAND_MAX); //Create a random float between 0-1
	float prob_sum = 0;

	for (int i = 0; i < AvailableDegrees.size(); i++) { //Pick an index when prob_sum is larger than random float.
		prob_sum += AvailableDegrees[i];
		if (prob_sum > cum_prob) {
			return AvailableIndices[i];
			
		}
	}

}

bool CheckIndicePair(int i, int j, vector<int> degreeseq, vector<Node*> Nodes) { // Returns true if index j is a candidate as neighbor 
	if (Nodes[i]->IsNeighbor(Nodes[j])) { return false; } // j is not a candidate if it is already a neighbor of i
	degreeseq[i]--;
	degreeseq[j]--;
	return HavelHakimiTest(degreeseq); // j is not a candidate if the sequence will not be graphical after the two vertices are linked

}

void SequentialAlg(vector<Node*>Nodes, vector<int> degreeseq) {
	int degreesum = 0;
	for (auto a : degreeseq)
	{
		degreesum += a;
	}
	if (degreesum == 0) { return; }  // Terminate algorithm when all degrees equal to zero (Step 2)

	int min_indice = 0;  //Set index of the minimum degree to the first non-zero element in the sequence
	for (int i = 0; i < degreeseq.size(); i++)
	{
		if (degreeseq[i] != 0) { min_indice = i; break; }
	}
	
	for (int i = min_indice; i < degreeseq.size();i++) { //Find the index with minimum non-zero degree in the sequence (Step 3)
		if (degreeseq[i] < degreeseq[min_indice]&&degreeseq[i]!=0) { min_indice = i; }
	}

	

	while (degreeseq[min_indice] != 0) { //Until the minimum non-zero degree becomes zero repeat adding edges (repeat steps 4-6 in the algortihm in paper)
		
		vector<int> AvailableIndices = {};
		for (int i = 0; i < degreeseq.size(); i++) //Find the available indices (Step 4 in the algorithm)
		{
			if (i != min_indice && degreeseq[i] != 0 && CheckIndicePair(min_indice, i, degreeseq, Nodes)) { AvailableIndices.push_back(i); }
		}
		if (AvailableIndices.size() == 0) { cout << "empty" << endl; return; }
		int SelectedIndice = SelectRandomIndex(AvailableIndices, degreeseq); // Select RandomIndice with proportional probability with its degree (Step 5 in the algorithm)
		Nodes[min_indice]->AddNeighbour(Nodes[SelectedIndice]); // Connect two vertices and update the degree sequence (Step 6 in the alg.)
		degreeseq[min_indice]--;
		degreeseq[SelectedIndice]--;
		
	}
	
	return SequentialAlg(Nodes, degreeseq); // Recall function until all degrees in the sequence are equal to zero (Step 8 in the alg.)
}




//Improved Sequential Algorithm

bool ImprovedCheckIndicePair(int i, int j, vector<int> degreeseq, vector<Node*> Nodes) { // Returns true if index j is a candidate as neighbor 
	if (Nodes[i]->IsNeighbor(Nodes[j])) { return false; } // j is not a candidate if it is already a neighbor of i
	degreeseq[i]--;
	degreeseq[j]--;
	return ErdosG(degreeseq); // j is not a candidate if the sequence will not be graphical after the two vertices are linked

}

bool ImprovedSequentialAlg(vector<Node*>Nodes, vector<int> degreeseq) {	// Improved version of the sequential Algorithm. 
	int degreesum = 0;
	for (auto a : degreeseq)
	{
		degreesum += a;
	}
	if (degreesum == 0) { return true; }								// Terminate algorithm when all degrees equal to zero (Step 2)

	int min_indice = 0;													//Set index of the minimum degree to the first non-zero element in the sequence
	for (int i = 0; i < degreeseq.size(); i++)
	{
		if (degreeseq[i] != 0) { min_indice = i; break; }
	}

	for (int i = min_indice; i < degreeseq.size(); i++) {				//Find the index with minimum non-zero degree in the sequence (Step 3)
		if (degreeseq[i] < degreeseq[min_indice] && degreeseq[i] != 0) { min_indice = i; }
	}

	vector<int> AvailableIndices = {};
	for (int i = 0; i < degreeseq.size(); i++)							//Find the available indices (Step 4 in the algorithm)
	{
		if (i != min_indice) {
			if (degreeseq[i] > 0) {
				if (ImprovedCheckIndicePair(min_indice, i, degreeseq, Nodes)) { // Erdös-Gallai (with Durfee number improvement) graphicality check is used instead of Havel-Hakimi
					AvailableIndices.push_back(i);
				}
			}
		}
	}
	if (AvailableIndices.size() == 0) {									// Safety check to stop if available indices is empty, 
		cout << "Available indices is empty." << endl;
		return false;
	}

	while (degreeseq[min_indice] != 0) { //Until the minimum non-zero degree becomes zero repeat adding edges (repeat steps 4-6 in the algortihm in paper)


		int SelectedIndice = AvailableIndices[rand()%AvailableIndices.size()]; // Another improvement proposed by the authors, select randomly among available indices
		Nodes[min_indice]->AddNeighbour(Nodes[SelectedIndice]); // Connect two vertices and update the degree sequence (Step 6 in the alg.)
		degreeseq[min_indice]--;
		degreeseq[SelectedIndice]--;
		for (int i = 0; i < AvailableIndices.size(); i++)
		{
			if (!ImprovedCheckIndicePair(min_indice, AvailableIndices[i], degreeseq, Nodes)) { AvailableIndices.erase(AvailableIndices.begin() + i); i--; }
		}


	}


	return ImprovedSequentialAlg(Nodes, degreeseq); // Recall function until all degrees in the sequence are equal to zero (Step 8 in the alg.)
}



// Tests for checking multiple edges, loops or whether the generated graph has same sequence with the given degree sequence

bool CheckMultipleEdges(vector<Node*> Nodes) { //If there are any duplicates in the adjacent vertices vector of a vertex then the graph has multiple edges
	for (auto a : Nodes) {
		if (a->adj_ver.size() <= 1) { continue; }
		else {
			for (int i = 0; i < a->adj_ver.size() - 1; i++)
			{
				for (int j = i + 1; j < a->adj_ver.size(); j++)
				{
					if (a->adj_ver[i] == a->adj_ver[j]) { return true; }

				}
			}
		}
	}
	return false;
}

bool CheckLoop(vector<Node*> Nodes) { //If a vertex has itself as an adjacent vertex then it has a loop
	for (auto a : Nodes) {
		for (int i = 0; i< a->adj_ver.size(); i++) {
			if (a->adj_ver[i] == a->ID) { return true; }
		}
	}
	
	return false;
}

bool CheckDegreeSeq(vector<Node*> Nodes,vector<int> degreeseq) //Check whether the degree sequence of the new graph is same with the given sequence
{  
	SortNodesID(Nodes);
	for (int i = 0; i < Nodes.size();i++) {
		if (degreeseq[i] != Nodes[i]->adj_ver.size()) { 
			cout << "Node " << Nodes[i]->ID << " does not have the required degree" << endl;
			cout << "Current degree is " << Nodes[i]->adj_ver.size() << endl;
			return false; }
	}
	
	return true;
}

void Tests(vector<Node*> Nodes, vector<int> Sequence) {   //Tests include loop, multiple edges and degree sequence check
	if (CheckLoop(Nodes)) {
		cout << "Current graph contains loops" << endl;
	}
	else {
		cout << "Current graph does not contain loops" << endl;
	}

	if (CheckMultipleEdges(Nodes)) {
		cout << "Current graph contains multiple edges" << endl;
	}
	else {
		cout << "Current graph does not contain multiple edges" << endl;
	}

	if (CheckDegreeSeq(Nodes, Sequence)) {
		cout << "Degree sequence of the new graph is the same with the given one." << endl;
	}
	else {
		cout << "Degree sequence of the new graph is different than the given one." << endl;
	}
}


// Degree Sequence creation algorithms for different graph types


vector<int> CreateRandomSequence(int n, float p) { //Create a random graphical sequence of size n with Bernoulli probability p (Erdös-Rényi model)
	vector<int> degreeseq;
	for (int i = 0; i < n; i++)
	{
		degreeseq.push_back(0);  // Start with an empty graph
		for (int j = 0; j < degreeseq.size()-1; j++)
		{
			if (float(rand()) / float(RAND_MAX) < p) { //Each time a vertex is added it has probability p to be linked with the existing edges
				degreeseq[degreeseq.size() - 1]++;
				degreeseq[j]++;
			}
		}
	}
	return degreeseq;

}

vector<int> CreateScalefreeSequence(int n, double rate) { // Create a scale-free degree sequence of size n in line with Preferential Attachment Model (Barabási & Albert)
	while (1) {
		vector<int> degreeseq = {};
		for (int i = 0; i < n; i++)
		{
			int r = 1+rand() % 1000;
			for (int j = 1; j < n/2; j++)  // Create random sequence using power-law distribution
			{
				if (r <= (1000 * pow(rate ,(1 - j))) && r > (1000 * pow(rate, (0 - j)))) { degreeseq.push_back(j); break; }
			}
		}
		if (ErdosG(degreeseq)) { return degreeseq; } // Return the sequence if it is graphical, repeat otherwise
	}
}

vector<int> CreateRegularSequence(int n,int d) { // Create a d-regular degree sequnce of size n 
	vector<int> degreeseq = {};
	for (int i = 0; i < n; i++)
	{
		degreeseq.push_back(d);
	}
	return degreeseq;
}


void main()
{
	chrono::high_resolution_clock::time_point startTime; //time storing variable
	startTime = chrono::high_resolution_clock::now(); //store current time
	double elapsedTime;

	string path = "C:/Users/orkun/Desktop/Github Page Content/IE _456_Project_Code/output";
	vector<int> Sequence;
	vector<vector<int>> AdjMatrix;

	for (const auto& entry : filesystem::directory_iterator(path))
	{
		if (!ReadSequenceGenerateGraph(entry.path().u8string(), Sequence, AdjMatrix)) {
			continue;
		}; //  Use the name of the specific input file you want to run code with


		if (!OutputTest(AdjMatrix, Sequence)) {
			cout << entry.path() << std::endl;

			/*cout << "The degree sequence is:" << endl;
			for (int a : Sequence)
			{
				cout << a << " ";
			}

			cout << endl;
			for (int a = 0; a < AdjMatrix.size();a++) {
				cout << a + 1 << " ";
				for (int b=0;b<AdjMatrix[a].size();b++)
				{
					cout << AdjMatrix[a][b] + 1 << " ";
				}
				cout << endl;
			}*/


		}

		Sequence.clear();
		AdjMatrix.clear();

	}

		

	

	

	
	//CreateNodes(Sequence, Nodes_HavelHakimi);

	////Havel Hakimi graph generation start

	//startTime = chrono::high_resolution_clock::now(); //store current time

	//if (HavelHakimi(Nodes_HavelHakimi)) { cout << "the sequence is graphical"<<endl; 
	//	SortNodesID(Nodes_HavelHakimi);
	//	for (auto a : Nodes_HavelHakimi) {
	//		cout << "Node " << a->ID << ":";
	//		for (auto i : a->adj_ver)
	//		cout << i << "\t";
	//		cout << endl;
	//	}
	//}
	//else {
	//	cout << "The sequence is not graphical" << endl;
	//	return;
	//}

	//elapsedTime = chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - startTime).count(); //calculate duration in seconds
	//cout << "\n" << "It took : " << elapsedTime << " seconds to complete Havel Hakimi graph generation." << "\t" <<endl;

	//Tests(Nodes_HavelHakimi, Sequence);	

	////ofstream outfile5("O-2-size-index-HH.txt");
	////WriteOutput("O-2-size-index-HH.txt", Nodes_HavelHakimi);


	////Havel Hakimi graph generation end
	//


	////Pairing graph generation start

	//double av_time = 0;
	//double av_trails = 0;
	//CreateNodes(Sequence, Nodes_Pairing);


	//for (int j = 0; j < 10; j++) // Take the average of 10 replications
	//{
	//	ResetNodes(Nodes_Pairing, Sequence); 

	//	startTime = chrono::high_resolution_clock::now(); //store current time
	//	int trialcount = 1;
	//	while (!Pairing(Nodes_Pairing)) {
	//		ResetNodes(Nodes_Pairing, Sequence); //If the algorithm get stuck reset nodes;
	//		trialcount++;
	//		if (trialcount > 5000) { cout << "Algorithm took too long to converge" << endl; break; }
	//	}

	//	av_trails += trialcount;

	//	SortNodesID(Nodes_Pairing);
	//	cout << "The adjacency matrix is:" << endl;
	//	for (auto a : Nodes_Pairing) {
	//		for (auto i : a->adj_ver)
	//			cout << i << "\t";
	//		cout << endl;
	//	}

	//	cout << "Algorithm has called " << trialcount << " times." << endl;
	//	
	//	elapsedTime = chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - startTime).count(); //calculate duration in seconds
	//	av_time += elapsedTime;
	//	cout << "\n" << "It took : " << elapsedTime << " seconds to complete Pairing graph generation." << "\t" << endl;

	//	Tests(Nodes_Pairing, Sequence);

	//}

	//av_time = av_time / 10;
	//av_trails = av_trails / 10;
	//cout << "The average running time of the algorithm is: " << av_time;
	//cout << "The average number of trials is: " << av_trails;


	////ofstream outfile2("O-2-size-index-PM.txt");
	////WriteOutput("O-2-size-index-PM.txt", Nodes_Pairing);


	////Pairing graph generation end
	//
	//
	////Sequential Algorithm start

	//
	//CreateNodes(Sequence, Nodes_Sequential);
	//startTime = chrono::high_resolution_clock::now(); //store current time

	//SequentialAlg(Nodes_Sequential, Sequence);
	//cout << "The adjacency matrix is:" << endl;
	//for (auto a : Nodes_Sequential) {
	//	cout << "Node " << a->ID << ":";
	//	for (auto i : a->adj_ver)
	//		cout << i << "\t";
	//	cout << endl;
	//}

	//elapsedTime = chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - startTime).count(); //calculate duration in seconds
	//cout << "\n" << "It took : " << elapsedTime << " seconds to complete Sequential Algorithm graph generation." << "\t" << endl;

	//Tests(Nodes_Sequential, Sequence);

	////ofstream outfile3("O-2-size-index-SA.txt");
	////WriteOutput("O-2-size-index-SA.txt", Nodes_Sequential);
	//
	////Sequential Algorithm end
	//


	////ImprovedSequential Algorithm start

	//	CreateNodes(Sequence, Nodes_ImpSequential);



	//	startTime = chrono::high_resolution_clock::now(); //store current time

	//	cout << "The adjacency matrix is:" << endl;
	//	if (ImprovedSequentialAlg(Nodes_ImpSequential, Sequence)) {
	//		for (auto a : Nodes_ImpSequential) {
	//			cout << "Node " << a->ID << ":";
	//			for (auto i : a->adj_ver)
	//				cout << i << "\t";
	//			cout << endl;
	//		}
	//	}
	//	else { cout << "The algorithm has stopped working"; }
	//	elapsedTime = chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - startTime).count(); //calculate duration in seconds
	//	cout << "\n" << "It took : " << elapsedTime << " seconds to complete Improved Sequential Algorithm graph generation." << "\t" << endl;

	//	Tests(Nodes_ImpSequential, Sequence);

		
		//ofstream outfile4("O-2-size-index-ISA.txt");
		//WriteOutput("O-2-size-index-ISA.txt", Nodes_ImpSequential);
		
		//DeleteNodes(Nodes_ImpSequential);
		//ImprovedSequential Algorithm end

}