/** 
Pseudo drawing program
Copyright (C) 2016 Stefan Ivanovic 

This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>
**/


#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;


void print_map(string map[70][70])//Prints map on the screen
{
    int i,j;
	for(i=0;i<70;i++)
	{
	    if(i<9)
        {
            cout << i+1 << "   ";
        }
        else
        {
            cout << i+1 << "  ";
        }

		for(j=0;j<70;j++)
      	{
		   cout << map[j][i];
	    }
	    cout << "\n";
	}
}//End of func



void map_define(string map[70][70])//Fills map with empty spaces
{
	int i,j;
    for(i=0;i<70;i++)
	{
		for(j=0;j<70;j++)
      	{
		   map[i][j] = "-";
	    }
	}
}//End of func



void load_map(string map[70][70])//Load map
{
	string file_load,line;
	int count = 2;
	int count2 = 0;
	int x,y;
	string arr[500];
	cout << "SAVED MAZES:\n";
	ifstream file ("saves.txt");
	while ( getline (file,line) )
    {
      cout << line << "\n";
    }
    file.close();
    cout << "\n\nType in the name of the file you wish to load: ";
    cin >> file_load;
    file_load += ".txt";
    fstream file2;
	file2.open(file_load, ios_base::out | ios_base::in);
	while (!file2.is_open())
	{
		cout << "File does not exist\n";
		cout << "Type in the name of the file you wish to load: ";
        cin >> file_load;
        file_load += ".txt";
	    file2.open(file_load, ios_base::out | ios_base::in);
	}
	file2.close();
	file2.open(file_load, ios_base::in);
	while ( getline (file2,line) )
    {
       istringstream buffer(line);
       int value;
       buffer >> value;
       if (count2 >=2 && count2 %2 == 0)
       {
       	 map[x][y] = "o";
       	 
       }
       if (count%2 == 0)
       {
       	  x = value;
       }
       else
       {
       	 y = value;
       }
       count2++;
       count++;
       
    }
    map[x][y] = "o";
    file2.close();
}//End of func



void save_map(string map[70][70])//Saves map
{
	bool ovrw = false;
	int choice,j,i;
	string file_name,file_name_alt;
	cout << "Enter file name: ";
	cin >> file_name;
	file_name_alt = file_name + ".txt";
	
	fstream file;
	file.open(file_name_alt, ios_base::out | ios_base::in);
	while (file.is_open())
	{
		cout << "File already exists. Overwrite?(1=yes, 2=no): ";
		cin >> choice;
		if (choice == 1)
		{
			file.clear();
            ovrw = true;
            file.close();
            
		}
		else
		{
			file.close();
			cout << "Enter file name: ";
        	cin >> file_name;
        	file_name_alt = file_name + ".txt";
	        file.open(file_name_alt, ios_base::out | ios_base::in);
		}
	}
	if(!file.is_open())
	{
	    file.open(file_name_alt, ios_base::out);
	}
	if (ovrw == false)
	{
	  ofstream save;
	  save.open("saves.txt",ios::app);
	  save << file_name + "\n";
	  save.close();
	}
	
	for(j=0;j<70;j++)
	{
		for(i=0;i<70;i++)
		{
			if(map[i][j] == "o")
			{
				file << i << "\n" << j << "\n";
			}
		}
	}
	file.close();
}//End of func



void maze_draw(string map[70][70])//User draws maze
{
	int cont;
	int d,x,y,i;
	string coord;
	cout << "Enter starting coordinate x: ";
	cin >> x;
	while (x > 70 || x < 1)
	{
		cout << "Enter starting coordinate x: ";
     	cin >> x;
	}
	x--;
	cout << "Enter starting coordinate y: ";
	cin >> y;
	while (y > 70 || y < 1)
	{
		cout << "Enter starting coordinate x: ";
     	cin >> y;
	}
	y--;
	map[x][y] = "o";
	print_map(map);
	while (true)
    {
      cout << "Drawing from: " << x+1 << "," << y+1 << endl;
	  cout << "Enter coo-line you want to draw on(x or y): ";
	  cin >> coord;
	  while (coord != "x" && coord != "X" && coord != "y" && coord != "Y")
	  {
	 	cout << "Enter coo-line you want to draw on(x or y): ";
	    cin >> coord;
	  }
	  cout << "Enter coordinate number to draw to: ";
	  cin >> d;
	  while (d < 1 || d > 70)
	  {
	  	cout << "Enter coordinate number to draw to: ";
	    cin >> d;
	  }
	  d--;
	  if (coord == "x" || coord == "X")
	  {
		if (d > x)
		{
			for (i=0;i<=d-x;i++)
			{
			map[x+i][y] = "o";
		    }
		    x += i-1;
		}
		else if(d <= x)
		{
			for (i=1;i<=x-d;i++)
			{
			map[x-i][y] = "o";
		    }
		    x -= i-1;
		}
		print_map(map);
	    cout << "Continue drawing?(1=yes, 2=no): ";
	    cin >> cont;
	    if (cont == 2)
	    {
	  	  break;
	    }
	  }
	  else if (coord == "y" || coord == "Y")
	  {
		if (d > y)
		{
			for (i=0;i<=d-y;i++)
			{
			map[x][y+i] = "o";
		    }
		    y += i-1;
		}
		else if(d <= y)
		{
			for (i=0;i<=y-d;i++)
			{
			map[x][y-i] = "o";
		    }
		    y -= i-1;
		}
		print_map(map);
	    cout << "Continue drawing?(1=yes, 2=no): ";
	    cin >> cont;
	    if (cont == 2)
	    {
	  	  break;
	    }
	  }
	  else 
	  {
	  	cout << "Invalid entry\n\n";
	  }	  
	}
	int choice;
	cout << "Would you like to save the maze?(1=yes, 2=no): ";
	cin >> choice;
	if (choice == 1)
	{
		save_map(map);
	}

}//End of func



int main()
{
	string map[70][70];
	int choose_map;
	map_define(map);
	cout<<"Choose an option(1=Draw new maze, 2=Load maze): ";
	cin >> choose_map;
	while (choose_map < 1 || choose_map > 2)
	{
		cout<<"\nInvalid option" << endl;
		cout<<"Choose an option(1=Draw new maze, 2=Load maze): ";
	    cin >> choose_map;
	}
	if (choose_map == 1)
	{
		maze_draw(map);
	}
	else 
	{
		load_map(map);
		print_map(map);
	}
	
	
	
	
	return 0;
}
