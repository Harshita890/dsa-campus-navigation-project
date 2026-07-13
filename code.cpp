#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <climits>
#include <algorithm>

using namespace std;

class SmartCampusNavigation
{
private:
    int V;
    vector<vector<pair<int, int>>> graph;
    vector<string> locations;

public:
    SmartCampusNavigation(int vertices)
    {
        V = vertices;
        graph.resize(V);
        locations.resize(V);
    }

    void setLocation(int id, string name)
    {
        locations[id] = name;
    }

    void addRoad(int source, int destination, int distance)
    {
        graph[source].push_back({destination, distance});
        graph[destination].push_back({source, distance});
    }

    void displayLocations()
    {
        cout << "\n========== Campus Locations ==========\n";
        for (int i = 0; i < V; i++)
        {
            cout << i << ". " << locations[i] << endl;
        }
    }

    void displayMap()
    {
        cout << "\n========== Campus Road Network ==========\n";

        for (int i = 0; i < V; i++)
        {
            cout << locations[i] << " -> ";

            for (auto edge : graph[i])
            {
                cout << "(" << locations[edge.first]
                     << ", " << edge.second << "m) ";
            }

            cout << endl;
        }
    }

    void shortestPath(int source, int destination)
    {
        vector<int> distance(V, INT_MAX);
        vector<int> parent(V, -1);

        priority_queue<pair<int, int>,
                       vector<pair<int, int>>,
                       greater<pair<int, int>>> pq;

        distance[source] = 0;
        pq.push({0, source});

        while (!pq.empty())
        {
            int current = pq.top().second;
            pq.pop();

            for (auto neighbour : graph[current])
            {
                int next = neighbour.first;
                int weight = neighbour.second;

                if (distance[current] + weight < distance[next])
                {
                    distance[next] = distance[current] + weight;
                    parent[next] = current;
                    pq.push({distance[next], next});
                }
            }
        }

        if (distance[destination] == INT_MAX)
        {
            cout << "\nNo path exists.\n";
            return;
        }

        vector<int> path;

        for (int v = destination; v != -1; v = parent[v])
            path
            
            .push_back(v);

        reverse(path.begin(), path.end());

        cout << "\n========== Shortest Path ==========\n";

        cout << "Distance : " << distance[destination] << " meters\n";

        cout << "Path : ";

        for (int i = 0; i < path.size(); i++)
        {
            cout << locations[path[i]];

            if (i != path.size() - 1)
                cout << " -> ";
        }

        cout << endl;
    }
};

int main()
{
    SmartCampusNavigation campus(6);

    // Locations
    campus.setLocation(0, "Library");
    campus.setLocation(1, "Canteen");
    campus.setLocation(2, "Admin Block");
    campus.setLocation(3, "Computer Lab");
    campus.setLocation(4, "Auditorium");
    campus.setLocation(5, "Hostel");

    // Roads
    campus.addRoad(0, 1, 100);
    campus.addRoad(0, 2, 50);
    campus.addRoad(1, 3, 70);
    campus.addRoad(2, 3, 80);
    campus.addRoad(3, 4, 60);
    campus.addRoad(4, 5, 90);
    campus.addRoad(2, 5, 150);

    int choice;

    do
    {
        cout << "\n======================================\n";
        cout << " SMART CAMPUS NAVIGATION SYSTEM\n";
        cout << "======================================\n";
        cout << "1. Display Campus Locations\n";
        cout << "2. Display Campus Map\n";
        cout << "3. Find Shortest Path\n";
        cout << "4. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            campus.displayLocations();
            break;

        case 2:
            campus.displayMap();
            break;

        case 3:
        {
            int source, destination;

            campus.displayLocations();

            cout << "\nEnter Source ID: ";
            cin >> source;

            cout << "Enter Destination ID: ";
            cin >> destination;

            if (source >= 0 && source < 6 && destination >= 0 && destination < 6)
            {
                campus.shortestPath(source, destination);
            }
            else
            {
                cout << "\nInvalid Location ID.\n";
            }

            break;
        }

        case 4:
            cout << "\nThank you for using Smart Campus Navigation System!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 4);

    return 0;
}
..