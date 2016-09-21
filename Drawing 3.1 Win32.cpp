#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>

using namespace std;


void print_map(string map[70][70])//Prints map on the screen
{
    int i,j;
    cout << "    ";
	for (i=0;i<70;i++)
	{
		cout << "_";
	}
	cout << "_\n";
	for(i=0;i<70;i++)
	{
	    if(i<9)
        {
            cout << i+1 << "  |";
        }
        else
        {
            cout << i+1 << " |";
        }

		for(j=0;j<70;j++)
      	{
		   cout << map[j][i];
	    }
	    cout << " |\n";
	}
	cout << "    ";
	for (i=0;i<70;i++)
	{
		cout << "-";
	}
	cout << "-\n";
}//End of func



void map_define(string map[70][70])//Fills map with empty spaces
{
	int i,j;
    for(i=0;i<70;i++)
	{
		for(j=0;j<70;j++)
      	{
		   map[i][j] = " ";
	    }
	}
}//End of func



void load_map(string map[70][70])//Load map
{
	string file_load,line;
	int count = 2;
	int count2 = 0;
	int x,y;
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
	cout << "Enter starting coordinate y: ";
	cin >> y;
	while (y > 70 || y < 1)
	{
		cout << "Enter starting coordinate x: ";
     	cin >> y;
	}
	map[x-1][y-1] = "o";
	print_map(map);
	cout << "Drawing from: " << x << "," << y << endl;
	while (true)
    {
      
	  
	  if (GetAsyncKeyState(VK_UP) < 0 && y != 1) 
	  {
	  	  if (GetAsyncKeyState(VK_SPACE) >= 0)
	      {
	  	    map[x-1][y-1] = " ";
	      }
	      y -= 1;
          map[x-1][y-1] = "o";
          print_map(map);
          cout << "Drawing from: " << x << "," << y << endl;
      }  
      else if (GetAsyncKeyState(VK_DOWN) < 0 && y != 70) 
	  {
	  	  if (GetAsyncKeyState(VK_SPACE) >= 0)
	      {
	  	    map[x-1][y-1] = " ";
	      }
	  	  y += 1;
          map[x-1][y-1] = "o";
          print_map(map);
          cout << "Drawing from: " << x << "," << y << endl;
      }  
      else if (GetAsyncKeyState(VK_LEFT) < 0 && x != 1) 
	  {
	  	  if (GetAsyncKeyState(VK_SPACE) >= 0)
	      {
	  	     map[x-1][y-1] = " ";
	      }
	  	  x -= 1;
          map[x-1][y-1] = "o";
          print_map(map);
          cout << "Drawing from: " << x << "," << y << endl;
      } 
      else if (GetAsyncKeyState(VK_RIGHT) < 0 && x != 70) 
	  {
	  	  if (GetAsyncKeyState(VK_SPACE) >= 0)
	      {
	  	    map[x-1][y-1] = " ";
	      }
	  	  x += 1;
          map[x-1][y-1] = "o";
          print_map(map);
          cout << "Drawing from: " << x << "," << y << endl;
      } 
      else if (GetAsyncKeyState(VK_ESCAPE) < 0)
      {
      	break;
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
