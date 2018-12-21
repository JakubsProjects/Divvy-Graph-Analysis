/*main.cpp*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

#include "graph.h"

using namespace std;

#define _CRT_SECURE_NO_WARNINGS  // ignore C-related security warnings in Visual Studio:


//
// Defines a Divvy Station:
//
class Station
{
public:
	string Name;
	int    ID;
	double Latitude;
	double Longitude;
	int    Capacity;

	Station(string name, int id, double latitude, double longitude, int capacity)
	{
		Name = name;
		ID = id;
		Latitude = latitude;
		Longitude = longitude;
		Capacity = capacity;
	}
};


//
// Inputs the stations from the given file, adding each station name as a
// vertex to the graph, and storing a new Station object into the vector.
// The graph is passed by reference --- note the & --- so that the changes
// made by the function are returned back.  The vector of Station objects is
// returned by the function.
//
vector<Station> InputStations(Graph& G, string filename)
{
	string line;
	vector<Station> V;

	ifstream input(filename);
	if (!input.good())  // failed to open:
		return V;

	getline(input, line);  // skip first line: column headers
	getline(input, line);  // first line of real data

	while (!input.eof())  // for each line of input:
	{
		stringstream  ss(line);

		// format:
		//   id,name,latitude,longitude,dpcapacity,online_date
		//   456,2112 W Peterson Ave,41.991178,-87.683593,15,5/12/2015
		//   101,63rd St Beach,41.78101637,-87.57611976,23,4/20/2015
		//
		string  stationID, name, latitude, longitude, capacity;

		//
		// parse the line:
		//
		getline(ss, stationID, ',');
		getline(ss, name, ',');
		getline(ss, latitude, ',');
		getline(ss, longitude, ',');
		getline(ss, capacity, ',');

		//
		// Create a new station object:
		//
		Station S(name,
			stoi(stationID),
			stod(latitude),
			stod(longitude),
			stoi(capacity));
		//
		// TODO:
		//   1. add station object to vector
		V.push_back(S);
		//   2. add vertex to graph
		//
		G.AddVertex(S.Name);



		getline(input, line);
	}

	return V;
}


//
// Inputs the trips, adding / updating the edges in the graph.  The graph is
// passed by reference --- note the & --- so that the changes made by the 
// function are returned back.  The vector of stations is needed so that 
// station ids can be mapped to names; it is passed by reference only for 
// efficiency (so that a copy is not made).
//
void ProcessTrips(string filename, Graph& G, vector<Station>& stations)
{
	string line;

	ifstream input(filename);
	if (!input.good())  // failed to open:
		return;

	getline(input, line);  // skip first line: column headers
	getline(input, line);  // first line of real data

	while (!input.eof())  // for each line of input:
	{
		stringstream  ss(line);

		// format:
		//   trip_id,starttime,stoptime,bikeid,tripduration,from_station_id,from_station_name,to_station_id,to_station_name,usertype,gender,birthyear
		//   10426561,6/30/2016 23:35,7/1/2016 0:02,5229,1620,329,Lake Shore Dr & Diversey Pkwy,307,Southport Ave & Clybourn Ave,Subscriber,Male,1968
		//
		string  tripID, fromID, toID, skip;

		//
		// parse the input line:
		//
		getline(ss, tripID, ',');
		getline(ss, skip, ',');
		getline(ss, skip, ',');
		getline(ss, skip, ',');
		getline(ss, skip, ',');
		getline(ss, fromID, ',');
		getline(ss, skip, ',');
		getline(ss, toID, ',');
		getline(ss, skip, ',');

		//
		// NOTE: don't trust the names in the trips file, not always accurate.  Trust the 
		// from and to station ids, and then lookup in our vector of stations:
		//


		//
		// TODO:
		//  - add new edge or update existing edge for this trip
		//
		string from, to;

		for (auto D : stations) {
			if (stoi(fromID) == D.ID) {
				from = D.Name;
			}
			if (stoi(toID) == D.ID) {
				to = D.Name;
			}
		}
		G.AddEdge(from, to, 1);


		getline(input, line);
	}
}


//
// getFileName: 
//
// Inputs a filename from the keyboard, checks that the file can be
// opened, and returns the filename if so.  If the file cannot be 
// opened, an error message is output and the program is exited.
//
string getFileName()
{
	string filename;

	// input filename from the keyboard:
	getline(cin, filename);

	// make sure filename exists and can be opened:
	ifstream file(filename);
	if (!file.good())
	{
		cout << "**Error: unable to open '" << filename << "'" << endl << endl;
		std::terminate();
	}

	return filename;
}

//Function to retrieve returns an ID
int retrieveID(vector<Station> *stations, string g) {

	//For the stations, loop through them 
	for (Station S : *stations) {

		//If the string g matches one from stations S
		if (S.Name == g) {

			//Then return the ID of that station
			return S.ID;
		}
	}

	//Otherwise return -1
	return -1;
}

//Getting specificStation
Station getSpecificStation(vector<Station> *stations, int ID) {
	//Creating empty station to return if desired station not found
	Station Empty("Does Not Exist", -999, -999, -999, -999);

	//For the stations, loop through them 
	for (Station B : *stations) {

		//If the ID matches one from stations B
		if (B.ID == ID) {

			//Then return that ID
			return B;
		}
	}

	//Otherwise return the empty station
	return Empty;
}

int main()
{
	int    N = 1000;
	Graph  DivvyGraph(N);

	cout << "** Divvy Graph Analysis **" << endl;

	string stationsFilename = getFileName();
	string tripsFilename = getFileName();

	vector<Station> stations = InputStations(DivvyGraph, stationsFilename);
	ProcessTrips(tripsFilename, DivvyGraph, stations);

	cout << ">> Graph:" << endl;
	cout << "   # of vertices: " << DivvyGraph.GetNumVertices() << endl;
	cout << "   # of edges:    " << DivvyGraph.GetNumEdges() << endl;
	cout << ">> Ready:" << endl;

	string cmd;
	int    fromID, toID;

	cout << ">> ";
	cin >> cmd;

	while (cmd != "exit")
	{
		if (cmd == "info")
		{
			//Reading in ID number
			cin >> fromID;
			//Searching and returning a station with that ID number
			Station returned1 = getSpecificStation(&stations, fromID);
			//Declaring variables
			int count = 0;
			int weight = 0;
			Station Empty("Does Not Exist", -999, -999, -999, -999);

			

			//If the neighbors size is not 0
			if (returned1.Name != Empty.Name) 
			{
				//Getting the neighbors that pertain to a specific station
				set<string> gettingNeigh = DivvyGraph.GetNeighbors(returned1.Name, count, weight);
				//Then print out all this information
				cout << returned1.Name << endl;
				cout << "(" << returned1.Latitude << ", " << returned1.Longitude << ")" << endl;
				cout << "Capacity: " << returned1.Capacity << endl;
				cout << " # of destination stations: " << count << endl;
				cout << " # of trips to those stations: " << weight << endl;
				cout << "Station: trips" << endl;
				//Loop through the neighbors and
				for (auto g : gettingNeigh) 
				{
					//Get the ID number pertaining to a double
					int fromID = retrieveID(&stations, g);
					//Then print out those doubles( these are lat & long cords)
					cout << "     " << g << "(" << fromID << ")" << ": ";

					//Getting the weight from the Edges
					vector<int> getWeight = DivvyGraph.GetEdgeWeights(returned1.Name, g);
					//Printing out the weight
					for (int gw : getWeight) 
					{
						cout << gw << endl;
					}
				}
			}
			//otherwise
			else 
			{
				//Give a print error
				cout << "** No such station..." << endl;
			}


		}
		else if (cmd == "trips")
		{
			//Reading in values
			cin >> fromID;
			cin >> toID;
			//Creating empty station to compare output to
			Station Empty("Does Not Exist", -999, -999, -999, -999);
			//Getting the station from first value
			Station from1 = getSpecificStation(&stations, fromID);
			//Getting the station from second value
			Station to1 = getSpecificStation(&stations, toID);

			//If they don't match the empty set then,
			if (from1.Name != Empty.Name && to1.Name != Empty.Name) 
			{
				//Get the number of trips between the two verticies
				int NumOfTrips = DivvyGraph.NumTrips(from1.Name, to1.Name);
				//Then print out the information
				cout << from1.Name << "->" << to1.Name << endl;
				cout << "# of trips: " << NumOfTrips << endl;
			}
			else
			{
				//Otherwise print out an error
				cout << "** One of those stations doesn't exist..." << endl;

			}
		}
		else if (cmd == "bfs")
		{
			//Reading in an ID number
			cin >> fromID;
			//setting count to 1
			int count = 1;
			//Getting that specific station with that ID
			Station returned1 = getSpecificStation(&stations, fromID);

			//Creating empty station to compare output to
			Station Empty("Does Not Exist", -999, -999, -999, -999);

			//If the returned id matches that fo an empty station
			if (returned1.ID == Empty.ID) {
				//Print out this error
				cout << "** No such station..." << endl;
			}
			//otherwise
			else {
				//Perform a BFS search to count the number of stations
				vector<string> variable = DivvyGraph.BFS(returned1.Name, count);

				//Print out the number of stations
				cout << "# of stations: " << count << endl;
				//cout << "  " << returned1.ID << endl;

				//Loop through the strong
				for (auto v : variable)
				{
					//Retrieve the ID for each verticy
					int verticyID = retrieveID(&stations, v);
					//and then print out that verticy
					cout << verticyID << ", ";
				}
				cout << "#" << endl;
			}
		}
		else if (cmd == "debug")
		{
			//Printing out graph to see if everything is correct
			DivvyGraph.PrintGraph("Divvy Graph");
		}
		else
		{
			//error for command
			cout << "**Invalid command, try again..." << endl;
		}

		cout << ">> ";
		cin >> cmd;
	}

	cout << "**Done**" << endl;
	return 0;
}

