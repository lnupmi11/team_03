#include "Functions.h"
#include "../Utils/NiceOut.h"

using namespace std;
using namespace niceOut;

string getCurrentDate()
{
	time_t dateGet(0);
	time(&dateGet);

	struct tm * dateStruct;
	char dateCurrent[100];

	dateStruct = localtime(&dateGet);

	strftime(dateCurrent, 100, "%d/%m/%Y", dateStruct);

	return dateCurrent;
}

int mainMenu(vector<User> &allUsers, vector<Event> &allEvents)
{
	int option;
	CLS;
	printMainMenu();

	while (true)
	{
		cout << "Option > ";
		string input;
		cin >> input;
		option = inputToInt(input);
		
		switch (option)
		{
		case 1:
			signIn(allUsers, allEvents);
			printMainMenu();
			break;
		case 2:
			signUp(allUsers);
			printMainMenu();
			break;
		case 3:
			return 0;
			break;
		default:
			CLS;
			alert("Incorrect option!");
			printMainMenu();
			break;
		}
	}

	return 0;
}

void signIn(vector<User> &allUsers, vector<Event> &allEvents)
{
	string login;
	string password;

	bool checkEntry = false;

	cout << "Enter login > ";
	cin >> login;
	cout << "Enter password > ";
	cin >> password;

	for (int i = 0; i < allUsers.size(); i++)
	{
		if (login == allUsers[i].getUserName() && password == allUsers[i].getPassword())
		{
			checkEntry = true;
			vector<Event>& userPosts = allUsers[i].getPosts();
			userMenu(allUsers[i], userPosts, allEvents, allUsers);
			break;
		}
	}

	if (checkEntry == false)
	{
		CLS;
		cout << "Error: Wrong login or password" << endl;
	}
}

void signUp(vector<User> &allUsers)
{
	string userName;
	string password;

	cout << "Creating new user account" << endl;

	cout << "Enter new username > ";
	cin >> userName;
	cout << "Enter new password > ";
	cin >> password;

	bool isCreated = true;

	for (int i = 0; i < allUsers.size(); i++)
	{
		if (userName == allUsers[i].getUserName())
		{
			isCreated = false;
			break;
		}
	}

	if (isCreated == true)
	{
		User newUser(userName, password);

		//TODO newUser

		allUsers.push_back(newUser);

		CLS;
		cout << "Your account has been created" << endl;
	}
	else
	{
		CLS;
		cout << "Error: User with username " << userName << " already exists" << endl;
	}
}

int userMenu(User &currentUser, vector<Event> &currentUserEvents, vector<Event> &allEvents, vector<User> &allUsers)
{
	CLS;
	printH("Welcome " + currentUser.getUserName());

	while (true)
	{
		cout << "   Menu" << endl;

		cout << " Options:" << endl;
		cout << "\t1 - Review all events" << endl;
		cout << "\t2 - Review my events" << endl;
		cout << "\t3 - Create new event" << endl;
		cout << "\t4 - Update event" << endl;
		cout << "\t5 - Remove event" << endl;
		cout << "\t6 - Sign out" << endl;

		int option;

		cout << "Option > ";
		string input;
		cin >> input;
		option = inputToInt(input);

		switch (option)
		{
		case 1:
			allEventsMenu(currentUser, allEvents, currentUserEvents, allUsers);
			break;
		case 2:
			userEventsMenu(currentUser, currentUserEvents);
			break;
		case 3:
			createEvent(currentUser, currentUserEvents, allEvents);
			break;
		case 4:
			updateEvent(currentUser, currentUserEvents);
			break;
		case 5:
			removeEvent(currentUser, currentUserEvents);
			break;
		case 6:
			CLS;
			return 0;
			break;
		default:
			CLS;
			cout << "Error: Wrong option" << endl;
			break;
		}
	}
	return 0;
}

int allEventsMenu(User &currentUser, vector<Event> &allEvents, vector<Event> &currentUserEvents, vector<User> &allUsers)
{
	CLS;

	int pageNumber = 1;

	printPageWithEvents(pageNumber, allEvents);

	int option;
	printAllEventMenu();
	cout << " Option > ";
	string input;
	cin >> input;
	option = inputToInt(input);

	while (true)
	{
		if (option >= 1 && option <= 3)
		{
			if (((pageNumber - 1) * 3 + option - 1) < allEvents.size())
			{
				eventReview(currentUser, allEvents[(pageNumber - 1) * 3 + option - 1], currentUserEvents, allEvents, allUsers);
				printPageWithEvents(pageNumber, allEvents);
			}
			else
			{
				printPageWithEvents(pageNumber, allEvents);
				cout << "Error: Wrong option" << endl;
			}
		}
		else if (option == 4)
		{
			pageNumber--;
			if (pageNumber < 1)
			{
				pageNumber = 1;
			}
			printPageWithEvents(pageNumber, allEvents);
		}
		else if (option == 5)
		{
			pageNumber++;
			if (pageNumber > (allEvents.size() / 3 + 1))
			{
				pageNumber = allEvents.size() / 3 + 1;
			}
			printPageWithEvents(pageNumber, allEvents);
		}
		else if (option == 6)
		{
			CLS;
			return 0;
		}
		else
		{
			printPageWithEvents(pageNumber, allEvents);
			cout << "Error: Wrong option" << endl;
		}

		printAllEventMenu();
		cout << " Option > ";	
		cin >> input;
		option = inputToInt(input);
	}

	return 0;
}

int userEventsMenu(User &currentUser, vector<Event> &currentUserEvents)
{
	CLS;

	while (true)
	{
		cout << "User: " << currentUser.getUserName() << endl;
		cout << "List of your events:" << endl;

		for (int i = 0; i < currentUserEvents.size(); i++)
		{
			cout << i + 1 << ":" << endl;
			cout << " Title: " << currentUserEvents[i].getTitle() << endl;
			cout << " Short plot: " << currentUserEvents[i].getShortPlot() << endl;
			cout << " Date: " << currentUserEvents[i].getDate() << endl;
			cout << endl;
		}

		int option;
		string input;

		cout << "Choose event for a full review. (Back to list - " << currentUserEvents.size() + 1 << ")" << endl;
		cout << " Option > ";
		cin >> input;
		option = inputToInt(input);

		if (option >= 1 && option <= currentUserEvents.size())
		{
			userEventReview(currentUserEvents[option - 1]);
		}
		else if (option == (currentUserEvents.size() + 1))
		{
			CLS;
			return 0;
		}
		else
		{
			CLS;
			cout << "Error. Wrong option." << endl;
		}
	}
	return 0;
}

void createEvent(User &currentUser, vector<Event> &currentUserEvents, vector<Event> &allEvents)
{
	cin.ignore(1024, '\n');

	CLS;

	string title;
	string date;
	string plot;
	string shortPlot;
	Priorities priority;

	cout << "User: " << currentUser.getUserName() << endl;
	cout << "Creation of new event" << endl;

	cout << " Title: ";
	getline(cin, title);
	cout << " Short plot: ";
	getline(cin, shortPlot);
	cout << " Plot: ";
	getline(cin, plot);

	int choosePrior = 0;

	bool checkPrior = false;

	while (checkPrior == false)
	{
		cout << " Priority (1 - low, 2 - medium, 3 - high): ";
		string input;
		cin >> input;
		choosePrior = inputToInt(input);
		cin.ignore(1024, '\n');

		switch (choosePrior)
		{
		case 1:
			priority = low;
			checkPrior = true;
			break;
		case 2:
			priority = medium;
			checkPrior = true;
			break;
		case 3:
			priority = high;
			checkPrior = true;
			break;
		default:
			cout << "Error. Wrong priority." << endl;
			break;
		}
	}

	date = getCurrentDate();

	Event newEvent(title, plot, shortPlot, date, priority, currentUser.getUserName());

	//TODO create 'newEvent'

	currentUserEvents.push_back(newEvent);
	allEvents.push_back(newEvent);

	CLS;
	cout << "New event has been created" << endl;
}

void updateEvent(User &currentUser, vector<Event> &currentUserEvents)
{
	CLS;

	string titleCheck;
	string title;
	string date;
	string plot;
	string shortPlot;
	Priorities priority;

	cout << "User: " << currentUser.getUserName() << endl;
	cout << "Updating of your event" << endl;
	cout << "Event list:" << endl;

	for (int i = 0; i < currentUserEvents.size(); i++)
	{
		cout << " " << i + 1 << " - " << currentUserEvents[i].getTitle() << endl;
	}
	cout << " " << currentUserEvents.size() + 1 << " - " << "Back" << endl;
	cout << endl;

	int optionEvent;

	while (true)
	{
		cout << " Option > ";
		string input;
		cin >> input;
		optionEvent = inputToInt(input);

		cin.ignore(1024, '\n');

		if (optionEvent >= 1 && optionEvent <= currentUserEvents.size())
		{
			if (currentUser.getUserName() == currentUserEvents[optionEvent - 1].getAuthor())
			{
				cout << " New title: ";
				getline(cin, title);
				currentUserEvents[optionEvent - 1].setTitle(title);

				cout << " New short plot: ";
				getline(cin, shortPlot);
				currentUserEvents[optionEvent - 1].setShortPlot(shortPlot);

				cout << " New plot: ";
				getline(cin, plot);
				currentUserEvents[optionEvent - 1].setPlot(plot);

				int choosePrior = 0;

				bool checkPrior = false;

				while (checkPrior == false)
				{
					cout << " New priority (1 - low, 2 - medium, 3 - high): ";
					string input;
					cin >> input;
					choosePrior = inputToInt(input);

					cin.ignore(1024, '\n');

					switch (choosePrior)
					{
					case 1:
						priority = low;
						checkPrior = true;
						break;
					case 2:
						priority = medium;
						checkPrior = true;
						break;
					case 3:
						priority = high;
						checkPrior = true;
						break;
					default:
						cout << "Error. Wrong priority." << endl;
						break;
					}
				}
				currentUserEvents[optionEvent - 1].setPriority(priority);

				date = getCurrentDate();

				currentUserEvents[optionEvent - 1].setDate(date);

				//TODO update currentUserEvents[optionEvent - 1]

				cout << "Event has been updated." << endl;
			}
			else
			{
				cout << "Error. Wrong event or author." << endl;
			}
		}
		else if (optionEvent == (currentUserEvents.size() + 1))
		{
			CLS;
			break;
		}
	}
}

void removeEvent(User &currentUser, vector<Event> &currentUserEvents)
{
	printRemoveMenu(currentUser, currentUserEvents);

	int optionEvent;

	while (true)
	{
		cout << " Choose event to remove > ";
		string input;
		cin >> input;
		optionEvent = inputToInt(input);

		if (optionEvent >= 1 && optionEvent <= currentUserEvents.size())
		{
			if (currentUser.getUserName() == currentUserEvents[optionEvent - 1].getAuthor())
			{
				currentUserEvents.erase(currentUserEvents.begin() + (optionEvent - 1));

				//TODO delete currentUserEvents[optionEvent - 1]

				printRemoveMenu(currentUser, currentUserEvents);
				cout << "Event has been removed." << endl;
			}
			else
			{
				cout << "Error: Wrong event." << endl;
			}
		}
		else if (optionEvent == currentUserEvents.size() + 1)
		{
			break;
		}
	}
	CLS;
}

int eventReview(User &currentUser, Event &globalEvent, vector<Event> &currentUserEvents, vector<Event> &allEvents, vector<User> &allUsers)
{
	CLS;

	cout << "Title: " << globalEvent.getTitle() << endl;
	cout << "Plot:" << endl;
	cout << " " << globalEvent.getPlot() << endl;
	for (int i = 0; i < globalEvent.getComments().size(); i++)
	{
		cout << "Comments:" << endl;
		cout << " " << i + 1 << ":" << endl;
		cout << globalEvent.getComments()[i] << endl;
	}

	int option;
	string input;
	cin >> input;
	option = inputToInt(input);
	while (true)
	{
		cout << "1 - add comment" << endl;
		cout << "2 - back to list" << endl;
		cout << " Option > ";
		cin >> input;
		option = inputToInt(input);

		switch (option)
		{
		case 1:
			addComment(currentUser, globalEvent, currentUserEvents, allEvents, allUsers);
			cout << "Comment has been added" << endl;
			break;
		case 2:
			CLS;
			return 0;
			break;
		default:
			cout << "Error: Wrong option" << endl;
			break;
		}
	}
	return 0;
}

int userEventReview(Event &currentUserEvent)
{
	CLS;

	cout << " Title: " << currentUserEvent.getTitle() << endl;
	cout << " Plot:" << currentUserEvent.getPlot() << endl;

	for (int i = 0; i < currentUserEvent.getComments().size(); i++)
	{
		cout << "Comments:" << endl;
		cout << " " << i + 1 << ":" << endl;
		cout << currentUserEvent.getComments()[i] << endl;
	}

	int option;

	while (true)
	{
		cout << "1 - back to list" << endl;
		cout << " Option > ";
		string input;
		cin >> input;
		option = inputToInt(input);

		if (option == 1)
		{
			CLS;
			return 0;
		}
		else
		{
			cout << "Error: Wrong option" << endl;
		}
	}
	return 0;
}

void addComment(User &currentUser, Event &globalEvent, vector<Event> &currentUserEvents, vector<Event> &allEvents, vector<User> &allUsers)
{
	cin.ignore(1024, '\n');

	string plotComment;
	string date;
	string author;

	cout << "Comment: ";
	getline(cin, plotComment);

	date = getCurrentDate();
	author = currentUser.getUserName();

	Comment newComment(author, plotComment, date);

	globalEvent.setComment(newComment);

	for (int i = 0; i < currentUser.getPosts().size(); i++)
	{
		if (globalEvent == currentUser.getPosts()[i])
		{
			currentUserEvents[i].setComment(newComment);
		}
	}

	//TODO create 'newComment'
}


void printPageWithEvents(int pageNumber, vector<Event> &allEvents)
{
	CLS;

	int numberOfEvent = 0;

	cout << "Page #" << pageNumber << endl;
	cout << endl;

	for (int i = (pageNumber - 1) * 3; i <= (pageNumber - 1) * 3 + 2; i++)
	{
		if (i >= allEvents.size())
		{
			break;
		}
		numberOfEvent++;

		cout << numberOfEvent << ") ";
		cout << "Title: " << allEvents[i].getTitle() << endl;
		cout << endl;
		cout << "   Short plot: " << allEvents[i].getShortPlot() << endl;
		cout << endl;
		cout << "   Date: " << allEvents[i].getDate() << "   Author: " << allEvents[i].getAuthor() << endl;
		cout << endl;
		cout << endl;
	}
}

void printRemoveMenu(User &currentUser, vector<Event> &currentUserEvents)
{
	CLS;

	cout << "User: " << currentUser.getUserName() << endl;
	cout << "Removing of your event" << endl;
	cout << "Event list:" << endl;

	for (int i = 0; i < currentUserEvents.size(); i++)
	{
		cout << " " << i + 1 << " - " << currentUserEvents[i].getTitle() << endl;
	}
	cout << " " << currentUserEvents.size() + 1 << " - " << "Back" << endl;
	cout << endl;
}

void printMainMenu()
{
	printH("Welcome");
	printM("To start working you need to sign in of sign up");

	print("Option list:");
	print(" 1 - Sign in");
	print(" 2 - Sign up");
	print(" 3 - Quit");
}

void printAllEventMenu()
{
	print("Choose number of event to review or one of the following options:");
	print("4 - Previous page");
	print("5 - Next page");
	print("6 - Back");
}

int inputToInt(string input)
{
	int result = 0;
	try{
		result = stoi(input);
		return result;
	}
	catch(invalid_argument& ex){
		return result;
	}
}
