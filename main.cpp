#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <ctime>
#include <iomanip>
#include "classfile.h"
#include "string.h"

using namespace std;
vector<Hotel> pool;

int nofHotels; //number of records
RBnode *RBroot = NULL;
RBtree treeObj;
digital_trie resNameTree;

void loadHotels_Res(char *sf) {
    
    ifstream f;
    char strID[15], hotelName[256], strStars[15], strNoR[15], noHot[5];
    char empty[] = "\0"; //this is used in order to manually erase another string
    f.open(sf);
    f.getline(noHot, 5, 59);
    nofHotels = atoi(noHot);
    
    for(int i=0; i<pool.size(); i++) pool.pop_back(); //aposdesmeush vector memory
    f.ignore(256,'\n');
    treeObj.clear(RBroot); //apodesmeuei RB tree memory
    for(int i=0; i<nofHotels; i++) {
                
                f.getline(strID, 1500, 59);
                f.getline(hotelName, 1500, 59);
                f.getline(strStars, 100, 59);
                f.getline(strNoR, 100, 59);
                vector<Reservation> pool_res;
                char Res_name[56], chDate[256], sDdays[15];
                for(int j=0; j<pool_res.size(); j++) pool_res.pop_back();
                for(int k=0; k<16; k++)	{
                	f.getline(Res_name, 1500, 59);
                	f.getline(chDate, 1500, 59);
                	if (k==15)
                		f.getline(sDdays, 1500);
                	else f.getline(sDdays, 1500, 59);
                	Reservation *res = new Reservation(Res_name, chDate, atoi(sDdays));
                	pool_res.push_back(*res);
                	strcpy(Res_name, empty);
                	strcpy(chDate, empty);
                	strcpy(sDdays, empty);
				}
                Hotel *h = new Hotel(atoi(strID), hotelName, atoi(strStars), atoi(strNoR));
                h->reservations = pool_res;
                pool.push_back(*h);
                treeObj.insert(h); //RB structure get updated
                for(int j=0; j<pool_res.size(); j++) resNameTree.insertTrie(h,string(h->reservations[j].res_name)); //insert to Trie structure
                
                strcpy(strID, empty);
                strcpy(hotelName, empty);
                strcpy(strStars, empty);
				strcpy(strNoR, empty);
				}
    cout << "\n**Hotels and Reservations are succesfully loaded from the file!**\n" << endl;
    f.close();}
    
    void save(char *sf) {
     ofstream f;
     f.open(sf, ios::trunc);//file opens for writing and old data gets deleted
     f << nofHotels << endl;
     for(int i = 0; i<pool.size(); i++){
             f << pool[i].id << (char)59;
             f << pool[i].h_name << (char)59;
             f << pool[i].stars << (char)59;
             f << pool[i].numberOfRooms << (char)59;
             for(int j=0; j<pool[i].reservations.size(); j++){
             	f << pool[i].reservations[j].res_name << (char)59;
             	f << pool[i].reservations[j].checkinDate << (char)59;
             	f << pool[i].reservations[j].stayDurationDays << (char)59;
             }
			 f << endl;
             }
     cout << "\n**Data are succesfully saved!**\n" << endl;
     f.close();
}
    
    void addNew() {
     char strID[15], hotelName[256], strStars[15], strNoR[15];
     char Res_name[56], chDate[256], sDdays[15], answer[56];
     vector<Reservation> pool_res;
     int i=0;
     cout << "\n**New Hotel and Reservations addition**" << endl;
     cout << "Type the ID of the Hotel: ";
     cin.ignore();
     cin.getline(strID, 50, '\n');
     do{
     	if (atoi(strID)==pool[i].id) {
     		cout << "\nThis ID is already exists.Please retype another ID of this Hotel: ";
     		cin.getline(strID, 50, '\n');
     		i=0;
     		continue;
		 }
		 else i++;	 
	}while(i<=(pool.size()-1));
     cout << "\nType the name of the Hotel: ";
     cin.getline(hotelName, 258, '\n');
     cout << "\nType the stars of the Hotel: ";
     cin.getline(strStars, 57, '\n');
     cout << "\nType the number of the rooms of the Hotel: ";
     cin.getline(strNoR, 57, '\n');
     do{
     	cout << "\nType the reservation name of this Hotel \n(the first letter better be capital): ";
     	cin.getline(Res_name, 57, '\n');
     	Res_name[0] = toupper(Res_name[0]);
     	cout << "\nType the check in date of this reservation: ";
     	cin.getline(chDate, 57, '\n');
     	cout << "\nType the stay duration days of this reservation: ";
     	cin.getline(sDdays, 57, '\n');
     	Reservation *res = new Reservation(Res_name, chDate, atoi(sDdays));
        pool_res.push_back(*res);
        strcpy(Res_name, "\0");
        strcpy(chDate, "\0");
        strcpy(sDdays, "\0");
     	cout << "\nDo you want to insert another reservation?(Reply with a 'yes' or 'no'): ";
     	cin.getline(answer, 56, '\n');
     }while(strcmp(answer,"yes")==0);
     Hotel *h = new Hotel(atoi(strID), hotelName, atoi(strStars), atoi(strNoR));
     h->reservations = pool_res;
     treeObj.insert(h); //insert to r-b tree
	 for(int j=0; j<pool_res.size(); j++) resNameTree.insertTrie(h,string(h->reservations[j].res_name)); //insert to Trie structure
     pool.push_back(*h);
     cout << "\n**Addition is completed succesfully!**\n" << endl;
     nofHotels++;
} 

 void show(int i) {
 	cout << "\n        HOTELS FOUND        " << endl;
 	cout << "Hotel id: " << pool[i].id << endl;
    cout << "Hotel Name: " << pool[i].h_name << endl;
    cout << "Stars of the hotel: " << pool[i].stars << endl;
    cout << "Number of rooms of the hotel: " << pool[i].numberOfRooms << endl << endl;
    cout << "---- Reservations of hotel " << pool[i].h_name << "----" << endl;
    for(int j=0; j<pool[i].reservations.size(); j++){
        cout << "Name of reservation: " << pool[i].reservations[j].res_name << endl;
        cout << "Check in date: " << pool[i].reservations[j].checkinDate << endl;
        cout << "Stay duration days: " << pool[i].reservations[j].stayDurationDays << endl;
    }
    cout << endl;
 }
    
void show_res(int i, int j) {
    cout << "Hotel Name: " << pool[i].h_name << endl;
    cout << "Name of reservation: " << pool[i].reservations[j].res_name << endl;
    cout << "Check in date: " << pool[i].reservations[j].checkinDate << endl;
    cout << "Stay duration days: " << pool[i].reservations[j].stayDurationDays << endl;
    cout << endl;
 }
    
    void showAll(){
     for(int i=0; i<pool.size(); i++) show(i);
}
    
void displayID_LINEAR() {
     char strID[15];
     int i=0, flag=0;
     cout << "**Display a hotel by id (using linear search)**" << endl;
     cout << "Type the ID of the hotel: ";
     cin.ignore();
     cin.getline(strID, 13, '\n');
     do{	 
     	do{
     		if (atoi(strID)==pool[i].id) {
     			flag=1;
     			break;
		 	}
		 	else i++;	 
		}while(i<=(pool.size()-1));
		if(flag==0){
			cout << "This ID is not exists.Please retype another ID of a hotel: ";
			cin.getline(strID, 13, '\n');
			i=0;
		}
		else  break;
	}while(1);
    show(i);
    cout << endl;
}

bool search_ID_Lin(int id)	{
	int i=0, flag=0;
	do{	 
     	do{
     		if (id==pool[i].id) {
     			flag=1;
     			break;
		 	}
		 	else i++;	 
		}while(i<=(pool.size()-1));
		if(flag==0){
			return false;
		}
		else  break;
	}while(1);
    return true;
}

    void display_res_by_name_LIN() {
     char Res_name[56];
     int count=0, flag=0;
     cout << "**Display hotels by surname**" << endl;
     cout << "Type the name of the reservation: ";
     cin.ignore();
     cin.getline(Res_name, 56, '\n');
     cout << "\n        RESERVATIONS FOUND        " << endl;
     cout << "The reservations with surname " << "'" << Res_name << "'" << "are: " << endl;
     do{	 
     	for(int i=0;i<pool.size(); i++){		 
     		for(int j=0; j<pool[i].reservations.size(); j++){
			 	if (strcmp(Res_name, pool[i].reservations[j].res_name)==0) {
     				flag=1;
     				count++;
     				show_res(i, j);	
		 		}
			}
		}
		if(flag==0){
			cout << "This surname is not exists.Please retype another surname of a reservation: ";
			cin.getline(Res_name, 56, '\n');
		}
		else break;
	}while(1);
	cout << "\nTotal reservations found with this surname: " << count << endl;
	cout << endl;
}
    
    int res_name_Lin(char* str)	{
    	int count=0;
    	for(int i=0;i<pool.size(); i++){		 
     		for(int j=0; j<pool[i].reservations.size(); j++){
			 	if (strcmp(str, pool[i].reservations[j].res_name)==0) {
     				count++;
		 		}
			}
		}
	}
    
    void display_by_stars_res() {
     char strStars[15], nofRes[15];
     int count=0, flag=0;
     cout << "**Display hotels by stars category and number of reservations**" << endl;
     cout << "Type the stars category of the hotel: ";
     cin.ignore();
     cin.getline(strStars, 15, '\n');
     cout << "Type the number of reservations of the hotel: ";
     cin.getline(nofRes, 15, '\n');
     do{	 
     	for(int i=0;i<pool.size(); i++){		 
			if ((atoi(strStars)==pool[i].stars)&&(atoi(nofRes)==pool[i].reservations.size())) {
     				flag=1;
     				count++;
     				cout << "Hotel id: " << pool[i].id << endl;
   					cout << "Hotel Name: " << pool[i].h_name << endl;	
		 	}
		}
		if(flag==0){
			cout << "This number of stars category or number of reservations is not exists." << endl << "Please retype another number of stars category of the hotel: ";
			cin.getline(strStars, 15, '\n');
			cout << "And another number of reservations of the hotel: ";
     		cin.getline(nofRes, 15, '\n');
		}
		else break;
	}while(1);
	cout << "\nTotal hotels found with this specific stars category and number of reservations: " << count << endl;
}
 
 int search_stars_res(int stars, int nofRes)	{
 	int count=0;
 	for(int i=0;i<pool.size(); i++){		 
			if ((stars==pool[i].stars)&&(nofRes==pool[i].reservations.size())) {
     				count++;
		 	}
		}
	return count;
 }
 
 void quickSort(int left, int right) {
     int i = left, j = right;
     Hotel pivot = pool[(left + right) / 2];
     Hotel temp = pool[(left + right) / 2];
     while (i <= j) {
           while (pool[i].id < pivot.id) i++;
           	while (pool[j].id > pivot.id) j--;
           	if (i <= j) {
                temp = pool[i];
                pool[i] = pool[j];
                pool[j] = temp;
                i++;
                j--;
            }
      }
     if (left < j) quickSort(left, j);
     if (i < right) quickSort(i, right);
}
 
 int binarySearch(int value, int left, int right) {
      if (left > right)
            return -1;
      int middle = (left + right) / 2;
      if (pool[middle].id == value)
            return middle;
      else if (pool[middle].id > value)
            return binarySearch(value, left, middle - 1);
      else
            return binarySearch(value, middle + 1, right);           
}
 
  void displayID_BIN() {
  	quickSort(0, pool.size() - 1);
  	char strID[15];
     int i=0, found=-2;
     cout << "**Display a hotel by id (using binary search) **" << endl;
     cout << "Type the ID of the hotel: ";
     cin.ignore();
     cin.getline(strID, 13, '\n');
     do{	 
     	found = binarySearch(atoi(strID), 0, pool.size() - 1);
     	if(found == -1){
			cout << "This ID is not exists.Please retype another ID of a hotel: ";
			cin.getline(strID, 13, '\n');
		}
		else if((found>=0)&&(found<pool.size())) {	
			show(found);
			break;
		}
	}while(1);
  }
    
  int interpolation_search (int value) {
  	int low = 0;
  	int high = pool.size() - 1;
  	int mid;
  	while ((pool[low].id <= value) && (pool[high].id >= value)) {
    	mid = low + ((value - pool[low].id) * (high - low)) / (pool[high].id - pool[low].id);
    	if (pool[mid].id < value)	low = mid + 1;
    	else if (pool[mid].id > value)	low = mid - 1;
    	else	return mid;
  	}
	if (pool[low].id == value)    return low;
  	else	return -1;
}
    
    void displayID_IS(){
  	quickSort(0, pool.size() - 1);
  	char strID[15];
     int i=0, found=-2;
     cout << "**Display a hotel by id (using interpolation search)**" << endl;
     cout << "Type the ID of the hotel: ";
     cin.ignore();
     cin.getline(strID, 13, '\n');
     do{	 
     	found = interpolation_search(atoi(strID));
		if(found == -1){
			cout << "This ID is not exists.Please retype another ID of a hotel: ";
			cin.getline(strID, 13, '\n');
		}
		else if((found>=0)&&(found<pool.size())) {	
			show(found);
			break;
		}
	}while(1);
  }
    
    void displayID_RBtree(){
  	char strID[15];
     int i=0, found=-3;
     cout << "**Display a hotel by id (RBtree search)**" << endl;
     cout << "Type the ID of the hotel: ";
     cin.ignore();
     cin.getline(strID, 13, '\n');
     do{	 
     	found = treeObj.search(atoi(strID));
		if(found == -1){
			cout << "This ID is not exists.Please retype another ID of a hotel: ";
			cin.getline(strID, 13, '\n');
		}
		else if((found>=0)&&(found<pool.size())) 
			
			break;
	}while(1);
  }

void displayName_TRIE(){
     char strName[257];
     bool found = false;
     cout << "**display a hotel by reservation name**" << endl;
     cout << "Type the reservation name: ";
     cin.ignore();
     cin.getline(strName, 257, '\n');
	 strName[0] = toupper(strName[0]);
     string resname(strName);
     do{
	 	found = resNameTree.searchTrie(resname);
		if(!found){
			cout << "This reservation name does not exist.\nPlease retype another reservation name: ";
			cin.getline(strName, 257, '\n');
			cout << strName << endl;
			strName[0] = toupper(strName[0]);
			cout << strName << endl;
			resname = strName;
		}
		else break;
	 }while(1);
} 
 
  void exp_eval(){
  	double S[7], f[7];
	for(int i=0;i<7;i++)	S[i] =0.000000000000000;
  	bool rtrn_val0 = false;
  	char names[3][50];
  	strcpy(names[0], "Ray");
  	strcpy(names[1], "Rivera");
  	strcpy(names[2], "Hopkins");
  	cout << "Estimating average time of each search algorithm..." << endl;
    for(int i=0; i<1000; i++){
    		clock_t t[6];
            do{
            	srand(time(NULL));
				int id = rand() % pool[pool.size()-2].id;
				id++;
            	t[0] = clock();
            	//linear search id
            	rtrn_val0 = search_ID_Lin(id);
            	t[0] = clock() - t[0];
            	quickSort(0, pool.size() - 1);
            	t[1] = clock();
            	//binary search id
            	int rtrn_val1 = binarySearch(id, 0, pool.size() - 1);
            	t[1] = clock() - t[1];
            	t[2] = clock();
            	//interpolation search id
            	int rtrn_val2 = interpolation_search(id);
            	t[2] = clock() - t[2];
            	t[6] = clock();
            	//RBtree search id
            	int rtrn_val6 = treeObj.search2(id);
            	t[6] = clock() - t[6];
            	srand(time(NULL));
				int stars = rand() % 4;
				stars++;
            	t[3] = clock();
            	//linear search stars and no of res
            	int rtrn_val3 = search_stars_res(stars, 16);
            	t[3] = clock() - t[3];
            	srand(time(NULL));
            	int num = rand() % 3;
            	t[4] = clock();
            	//linear search res name
            	int rtrn_val4 = res_name_Lin(names[num]);
            	t[4] = clock() - t[4];
            	t[5] = clock();
            	//trie search res name
            	int rtrn_val5 = resNameTree.searchTrie2(string(names[num]));
            	t[5] = clock() - t[5];
            }while(rtrn_val0==false);
            for(int j=0;j<7;j++){
				f[j] = ((double)t[j])/CLOCKS_PER_SEC;
            	S[j] += f[j];
        	}
    }
    for(int i=0;i<7;i++)	S[i] = S[i] / 1000.000000000000000;
	cout << "Average linear search time by id: " << setprecision(10) << S[0] << " secs" << endl;
	cout << "Average binary search time by id: " << setprecision(400) << S[1] << " secs" << endl;
	cout << "Average interpolation search time by id: " << setprecision(400) << S[2] << " secs" << endl;
	cout << "Average Red-Black tree based search time by id: " << setprecision(10) << S[6] << " secs" << endl;
	cout << "Average linear search time by number of stars and number of reservations: " << setprecision(10) << S[3] << " secs" << endl;
	cout << "Average linear search time by reservation name: " << setprecision(10) << S[4] << " secs" << endl;
	cout << "Average Trie-based search time by reservation name: " << setprecision(10) << S[5] << " secs" << endl;
  }
  
    
    int main(int argc, char *argv[])
{
    char selectedFile[20];
    if (argc == 1) strcpy(selectedFile, "data.csv");
    else strcpy(selectedFile, argv[1]);
    char savedFile[20];
    strcpy(savedFile, "data_saved.csv");
    cout << "/*-------Hotel data base application--------*\n";
    int sel=0;
    while(sel != 8){
	    cout << "\nSelect an operation:\n";
	    cout << "1. Load Hotels and Reservations from file\n";
	    cout << "2. Save Hotels and Reservations to file\n";
	    cout << "3. Add a Hotel (along with its Reservations)\n";
	    cout << "4. Search and Display a Hotel by id\n";
	    cout << "5. Display all Hotels of specific stars category and number of reservations\n";
	    cout << "6. Display Reservations by surname search\n";
	    cout << "7. Experimental evaluation of the search algorithms\n";
	    cout << "8. Exit\n";
	    cout << "Input: ";
	    cin >> sel;
	    cout << endl;
	    while((sel<=0) || (sel>8)) {cout << "Invalid entry. Try again!\n"; cin >> sel;} 
	    if(sel==1) loadHotels_Res(selectedFile);
	    else if(sel==2) save(savedFile);
	    else if(sel==3) addNew();
	    else if(sel==4) {
	    	int ch=0;
	    	cout << "Select one of the following search algorithms:\n";
	    	cout << "1. Linear search\n";
		    cout << "2. Binary search\n";
		    cout << "3. Interpolation search\n";
	    	cout << "4. Search using Red-Black trees\n";
	    	cout << "Input: ";
	    	cin >> ch;
	    	cout << endl;
	    	while((ch<=0) || (ch>4)) {cout << "Invalid entry. Try again!\n"; cin >> ch;} 
	    	if(ch==1) displayID_LINEAR();
	    	else if(ch==2) displayID_BIN();
	    	else if(ch==3) displayID_IS();
	    	else if(ch==4) displayID_RBtree();
		}
	    else if(sel==5) display_by_stars_res();
	    else if(sel==6) {
	    	int ch=0;
	    	cout << "Select one of the following search algorithms:\n";
	    	cout << "1. Linear search\n";
		    cout << "2. Search using digital Tries\n";
		    cout << "Input: ";
	    	cin >> ch;
	    	cout << endl;
	    	while((ch<=0) || (ch>2)) {cout << "Invalid entry. Try again!\n"; cin >> ch;} 
	    	if(ch==1) display_res_by_name_LIN();
	    	else if(ch==2) displayName_TRIE();
		}
	    else if(sel==7) {
	    	loadHotels_Res(selectedFile);
	    	exp_eval();
		}
	}
    system("PAUSE");
    return EXIT_SUCCESS;
}

