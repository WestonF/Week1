#include <iostream>
#include <vector>
#include <cassert>

class account;		//holds all the data associated with a single customer account. Currently, just name, ssn,ssn last four, date of creation, and account number;
class accountbank;	//this functions as a hybrid database/ database interface. Ideally, we'd have something like an SQL database or other quality db system, and accountbank would just serve as an interface helper class

void LogIn();
bool CheckCred(std::string i_user, std::string i_pass);
void ShowAccounts(accountbank* db);

void DisplayAccount(accountbank* db);
void SearchName(accountbank* db);
void NewAccount(accountbank* db);
void CloseAccount(accountbank* db);


int Exponentiate(int base, int power);
std::string NumberToString(int input);
int StringToNumber(std::string number);
std::string GetDate();


//Tests
void TestDisplay(accountbank* db);	//tests acc 0, "Joe Blow" and acc3, "Bob Parson"
void TestShow(accountbank* db);		//just displays everything
void TestSearch(accountbank* db, std::string testname);	//displays output vector from searching testname
void TestNew(accountbank* db);		//
void TestClose(accountbank* db);	//
void TestScore(accountbank* db, std::string testname);	//displays a score for all default accounts for the string testname
#define testmode false	//definition toggles main() between test mode and normal operation. Intentionally impossible to modify post-compile

const int DISPLAYCOUNT = 5;	//this is the maximum number of names displayed in response to a search

//this class holds all data associated with a given account. can be expanded later if an account is intended to hold more data or perform more functions
class account
{
	protected:
		std::string ssn = "";	//social security number, stored as a string
		std::string ssn4 = "";	//last four digits of ssn
	public:
		friend class accountbank;

		std::string custname = "";	//customer name
		std::string opendate = "";	//date account opened
		std::string numb = "";		//account number. Also index of accountbank's alist where account is stored
		
		account(std::string i_custname, std::string i_ssn, std::string i_opendate, std::string i_numb)
		{
			custname = i_custname;
			ssn = i_ssn;
			opendate = i_opendate;
			numb = i_numb;
			if(ssn.length() <= 4)
			{
				ssn4 = ssn;
			}
			else
			{
				unsigned int ssnend = ssn.length() - 4;
				assert(ssnend > 0 );	//shouldn't hit this block if this is untrue
				ssn4 = ssn.substr(ssnend);
			}
		}

		void Display()
		{
			std::cout << custname << ", " << numb << ", " << opendate << std::endl;
		}
		
		void DisplayMore()
		{
			std::cout << custname << ", "<< ssn4 << ", " << numb << ", " << opendate << std::endl;
		}
};




//This thing functions as a hybrid database/database interface. In a proper version, we'd probably be using an actual database we can encrypt and such, and accountbank would instead be just the interface, ideally using the same functions currently in use to provide a transition that requires no re-writing of external functions
class accountbank
{
	private:
		std::vector<account> alist;
	public:
		friend class account;
	accountbank()
	{
		alist.push_back(account("Joe Blow", "555555555", "Dec 12, 2021", "0"));	//this is where all the "pre-existing accounts" live. make more.	
		alist.push_back(account("Bob Parsons", "555555532", "Dec 12, 2021", "1"));
		alist.push_back(account("Bobby Parsons", "555442255", "April 22, 2021", "2"));
		alist.push_back(account("Bob Parson", "555225576", "Jan 14, 2001", "3"));
		alist.push_back(account("Steve Blob", "555552323", "Dec 11, 2012", "4"));
	}

	//output all the accounts
	void ShowAccounts()
	{
		for (unsigned int i = 0; i < alist.size(); i++)
		{
			alist.at(i).Display();
		}
	}
	
	//assign a score to each account to grade its similarity to a search term
	unsigned int ScoreName(std::string s_name, account subject)
	{
		unsigned int score = 0;
		if (subject.custname == s_name)
		{
			score = 9999; //this should exceed any other score 
			return score;
		}
		//implicit else
		unsigned int lastmatch = 0;
		for (unsigned int i = 0; i < s_name.length(); i++)	//for each letter of n_name
		{
			for (unsigned int j = lastmatch ; j < subject.custname.length(); j++) //compare against letters of subject name past the last matched location
			{
				if ( s_name[i] == subject.custname[j])	//if the letters match
				{
					score++;	//add one point to the score
					lastmatch = j + 1;	//save the location of the account name letter so next iteration starts past it
					break;	//exit this loop, advance to next letter of n_name to resume searching
				}
			}
		}

		return score;	//more letters matching in order makes a higher score
	}

	std::vector<account*> SearchNames(std::string s_custname)
	{
		std::vector<std::pair<int, unsigned int>> refscore;	//refscore = {index, score}
		for (int i = 0; i < alist.size(); i++)
		{
			std::pair<int, unsigned int> score;
			score.first = i;
			score.second = ScoreName(s_custname, alist.at(i));
			if (score.second >= 1 )		//if score is at least 1
			{
				if (refscore.size() == 0)	//if the vector is empty, create an element
				{
					refscore.push_back(score);
				}
				else	//if the vector is NOT empty, find where that score belongs
				{
					for (unsigned int j = 0; j < refscore.size(); j++)	//compare the score of the current name against the ones already on the list
					{
						if (refscore.at(j).second < score.second)
						{
							refscore.insert((refscore.begin() + j), score);	//put new element in appropriate location
							if(refscore.size() > DISPLAYCOUNT)
							{
								refscore.pop_back();	//keep it limited to DISPLAYCOUNT
							}

							break;
						}
					}
				}
			}
		}

		std::vector<account*> returnvect;

		for (int i = 0; i < refscore.size(); i++)
		{
			returnvect.push_back(&alist.at(refscore.at(i).first));	//grab the index from element i of refscore, use that index to fetch the appropriate account from alist, pass the address of that account to returnvect as a new element. repeat for each element of refscore
				
		}

		return returnvect; //should be a set of DISPLAYCOUNT addresses for accounts with the best name matches 
	}

	account* GetAccount(std::string n_numb)
	{
		for(unsigned int i = 0; i < alist.size(); i++)
		{
			if (alist.at(i).numb == n_numb)
			{
				return &alist.at(i);
			}
		}
		//number not found
		return NULL;
	}

	bool NewAccount(std::string n_custname, std::string n_ssn)
	{
		unsigned int size = alist.size();
		for (unsigned int i = 0; i < size; i++)
		{
			if ((alist.at(i).custname == n_custname)||(alist.at(i).ssn == n_ssn))
			{
				std::cout << "Account exists" << std::endl;
				return false;
			}
		}
		
		//if no existing account match
		std::string oldnumb = alist.back().numb;
		int i_newnum = StringToNumber(oldnumb);
		std::string s_newnum = NumberToString(i_newnum + 1);
		std::string newdate = GetDate();
		alist.push_back(account(n_custname, n_ssn, newdate, s_newnum ));	

		std::cout << "Account Created" << std::endl;

		return true;
	}

	void CloseAccount(std::string d_numb)
	{
		int delete_numb = StringToNumber(d_numb);
		if(GetAccount(d_numb) != NULL)
		{
			alist.erase((alist.begin() + delete_numb), (alist.begin() + delete_numb + 1));	//alist.begin() used to create an iterator, then the addition used to offset from the first position. deletes one element.
		}
	}
};



int main()
{
	accountbank not_database;
	
	if(testmode)	//I'm sure a hacker could exploit this, but real security is outside the scope of this demo
	{
		//do tests
		//TestShow(&not_database);
		//TestDisplay(&not_database);
		
		//TestScore(&not_database, "BobP");
		//TestSearch(&not_database, "BobP");
		//TestNew(&not_database);
		TestClose(&not_database);
		return 0;
	}
	
	//login
	LogIn();
	//"home console prompt"
	std::string command = "";

	while(true)
	{
	
		std::cout << "home >";

		std::getline(std::cin, command);	//there's a but that skips the "wait for input" part of this on loop one. not sure how to fix yet

		if (command == "show accounts")
		{
			ShowAccounts(&not_database);
		}
		else if (command == "display account")
		{
			DisplayAccount(&not_database);
		}
		else if (command == "search name")
		{
			SearchName(&not_database);
		}
		else if (command == "new account")
		{
			NewAccount(&not_database);
		}
		else if (command == "close account")
		{
			CloseAccount(&not_database);
		}
		else if (command == "help")
		{
			std::cout << "show accounts\n" << "display account\n" << "search name\n" << "new account\n" << "close account\n" << "quit" << std::endl;
		}
		else if (command == "quit")
		{
			break;
		}
	}
	return 0;
}


void LogIn()
{
	bool valid = false;
	std::string user, pass;

	while(valid!= true)
	{
		std::cout << "Username:" << std::endl;
		std::cin >> user;
		std::cout << "Password:" << std::endl;
		std::cin >> pass;
		valid = CheckCred(user, pass);	//this should be some fancy encrypted high-security process. Instead it just checks against a single user/pass combination explicitly defined in the current implementation of CheckCred
		if (!valid)
		{
			std::cout << "Incorrect User" << std::endl;
		}

	}
}

bool CheckCred(std::string i_user, std::string i_pass)
{
	//this is mostly a placeholder for a real way to deal with credentials
	bool valid = false;
	if (i_user == "admin")
	{
		if (i_pass == "password")
		{
			valid = true;
		}
	}
	return valid;
}

void ShowAccounts(accountbank* db)
{
	//where am I supposed to be storing these accounts? where do they live, where do I get them from?
	db->ShowAccounts();
}



void DisplayAccount(accountbank* db)
{
	std::string input;
	std::cout << "account >";
	std::cin >> input;
	account* acc = db->GetAccount(input);
	if (acc == NULL)
	{
		std::cout << "Invalid account number" << std::endl;
	}
	else
	{
	acc->DisplayMore();
	}
}


void SearchName(accountbank* db)
{
	const std::string romnum[] = {"i" , "ii", "iii", "iv", "v" , "vi"};
	std::string input;

	while(1)
	{
		std::cout << "enter name >" << std::endl;
		std::cin >> input;
		std::vector<account*> list = db->SearchNames(input);
		unsigned int size = list.size();
		unsigned int index = 0;
		for (unsigned int i = index; i < size; i++)
		{
			std::cout << romnum[i] << ". " << list.at(i)->custname << std::endl;
			index = i;
		}
		std::cout << romnum[index] << ". Home" << std::endl << "Select number >" << std::endl;
		std::cin >> input;
		if(input == "Home")
		{
			return;
		}
		else if(input.length() == 1)
		{
			if((input[0] >= '1')&&(input[0] <= '9'))	//ensure the character in input[0] is a numeral
			{
				int selection = input[0] - '0';	//convert a single digit number in a string into an appropriate integer value
				selection--; //this is to convert from the 1-indexed display to the zero-indexed list
				if (selection < size)
				{
					list.at(selection)->Display();
					break;
				}
				else if (selection == size)	//this is the numerical value assigned to "home"
				{
					break;
				}
				else
				{
					std::cout << "invalid number" <<std::endl;
					continue; //returns to the "enter name" prompt
				}
			}
			else	//if the entry is neither "Home" nor a single-character string
			{
				std::cout << "invalid number" <<std::endl;	//returns to the "enter name" prompt
			}
		}
	}
}

void NewAccount(accountbank* db)
{

	std::string n_name, n_ssn;

	//GET NAME
	std::cout << "Customer Name >";
	std::getline(std::cin, n_name);
	for (int i = 0; i < n_name.length(); i++)	//make sure all characters are spaces or letters
	{
		if (n_name[i] == ' ')
		{
			continue;
		}
		else if ((n_name[i] >= 'A') && (n_name[i] <= 'Z'))
		{
			continue;
		}
		else if ((n_name[i] >= 'a') && (n_name[i] <= 'z'))
		{
			continue;
		}
		else	//could leave this as implicit, but that looked suspicious and accidental
		{
			std::cout << "Invalid Name" << std::endl;
			return;
		}
	}



	// GET SSN
	std::cout << "SSN >";
	std::cin >> n_ssn;

	for (int i = 0; i < n_ssn.length(); i++)	//make sure all characters are numeric
	{
		if ((n_ssn[i] >= '0') && (n_ssn[i] <= '9'))
		{
			continue;
		}
		else if(n_ssn[i] == ' ')
		{
			n_ssn.erase(i,1);	//erase the space character, but then proceed
			i--;	//decrement i so that the next pass checks the new character that is now in position i after it increments at the end of loop
			continue;
		}
		else	//could leave this as implicit, but that looked suspicious and accidental
		{
			std::cout << "Invalid SSN" << std::endl;
			return;
		}

	}

		n_ssn.resize(9); //truncates ssn to 9 digits, because the specification said to limit it


	//CHECK IF NAME OR SSN EXIST
	db->NewAccount(n_name, n_ssn);

}

void CloseAccount(accountbank* db)
{
	std::string input;
	account* to_delete;
	std::cout << "account >";
	std::cin >> input;
	to_delete = db->GetAccount(input);

	if (to_delete != NULL)
	{
		char confirm = static_cast<char>(NULL);
		std::cout << "Are you sure you wish to close this account? (y/n) >";
		std::cin >> confirm;
		if(confirm == 'y')
		{
			db->CloseAccount(input);
			std::cout << "Account closed" << std::endl;
			return;
		}
		else
		{
			std::cout <<"Account not closed" << std::endl;
		}
	}
	else
	{
		std::cout << "Account not found" << std::endl;
	}

}

//on second thought, I don't think I actually need this function for this assignment
//only works for positive integer powers (including 0) and integer bases
int Exponentiate(int base, int power)
{
	int accumulator = 1;	//anything to the zero-th power = 1
	for (int i = 1; i <= power; i++)
	{
		accumulator *= base;
	}
	return accumulator;
}

std::string NumberToString(int input)
{
	std::string accumulator = "";
	int destructible = input;
	while(destructible != 0)
	{
		accumulator = static_cast<char>((destructible % 10) + '0') + accumulator;
		destructible /= 10;
	}
	return accumulator;
}

int StringToNumber(std::string number)
{ 
	int accumulator = 0;
        int length = static_cast<int>(number.length()) - 1;
        for (int i = 0; i <= length; i++)
        {
            int index = length - i;
            int temp = static_cast<int>(number[index]) - static_cast<int>('0');
            
            if ((temp > 9) || (temp < 0))
            {
                continue;
            }

            int j = 0;

            while (j < i)
            {
                temp = temp * 10;
                j++;
            }
            accumulator = accumulator + temp;
        }

        return accumulator;
    }

//this function should check system time and convert it to my preferred format. I don't know how to do that, and did not have time to learn before this task was due.
std::string GetDate()
{
	return "Dec 13, 2021";
}


//TEST FUNCTIONS

void TestDisplay(accountbank* db)
{
	std::cout << "Expected output:\nJoe Blow, 0, Dec 12 2021" << std::endl;
	account* acc = db->GetAccount("0");
	acc->Display();

	std::cout << "Expected output:\nJoe Blow, 5555, 0, Dec 12 2021" << std::endl;
	acc->DisplayMore();


	std::cout << "Expected output:\nBob Parson, 3, Jan 12 2121" << std::endl;
	acc = db->GetAccount("3");
	acc->Display();

	std::cout << "Expected output:\nBob Parson, 5576, 3, Jan 12 2121" << std::endl;
	acc->DisplayMore();
}

void TestShow(accountbank* db)
{

	db->ShowAccounts();
}

void TestSearch(accountbank* db, std::string testname)
{
	std::vector<account*> list = db->SearchNames(testname);
	for (int i = 0; i < list.size(); i++)
	{
		list.at(i)->Display();
		std::cout << std::endl;
	}
}
void TestNew(accountbank* db)
{
	db->NewAccount("Bob Parson", "88888888888");	//this should truncate the ssn, and be refused on grounds of duplicate account
	db->NewAccount("Someguy Trashdata", "123456789");
	db->ShowAccounts();
}	
void TestClose(accountbank* db)
{
	db->CloseAccount("3");
	db->ShowAccounts();
}
void TestScore(accountbank* db, std::string testname)
{
	account* acc = db->GetAccount("0");
	int score = db->ScoreName(testname, *acc);
	acc->Display();
	std::cout << score << std::endl;

	acc = db->GetAccount("1"); 
	score = db->ScoreName(testname, *acc);
	acc->Display();
	std::cout << score << std::endl;
	
	acc = db->GetAccount("2"); 
	score = db->ScoreName(testname, *acc);
	acc->Display();
	std::cout << score << std::endl;
	
	acc = db->GetAccount("3"); 
	score = db->ScoreName(testname, *acc);
	acc->Display();
	std::cout << score << std::endl;
	
	acc = db->GetAccount("4"); 
	score = db->ScoreName(testname, *acc);
	acc->Display();
	std::cout << score << std::endl;
}

