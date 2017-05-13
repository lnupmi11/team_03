#include "Functions.h"
#include "../Utils/NiceOut.h"

using namespace std;

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

int mainMenu(vector<User>& allUsers, vector<Event> & allEvents)
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
			if (quit() == true)
			{
				return 0;
			}
			printMainMenu();
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

void signIn(vector<User>& allUsers, vector<Event> & allEvents)
{
	string login;
	string password;

	bool checkEntry = false;

	cout << "Login > ";
	cin >> login;
	cout << "Password > ";
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

void signUp(vector<User>& allUsers)
{
	string userName;
	string password;

	cout << "Creating new user account" << endl;

	cout << "Enter new username > ";
	cin >> userName;
	cout << "Enter new password > ";
	cin >> password;
	
	if (userName.size() <= 3)
	{
		CLS;
		cout << "Error: username must have more than three symbols" << endl;
	}
	else if(!isalpha(userName[0]) || !isalpha(password[0]))
	{
		CLS;
		cout << "Error: first symbol of username and password must be a letter" << endl;
	}
	else if(password.size() <= 3)
	{
		CLS;
		cout << "Error: password is too short" << endl;
	}
	else
	{
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
}

int userMenu(User& currentUser, vector<Event>& currentUserEvents, vector<Event>& allEvents, vector<User>& allUsers)
{
	CLS;
	printH("Welcome " + currentUser.getUserName());

	string deleteMsg;

	while (true)
	{
		cout << "   Menu" << endl;

		cout << " Options:" << endl;
		cout << "\t1 - Review all events" << endl;
		cout << "\t2 - Review my events" << endl;
		cout << "\t3 - Create new event" << endl;
		cout << "\t4 - Update event" << endl;
		cout << "\t5 - Remove event" << endl;
		cout << "\t6 - Delete account" << endl;
		cout << "\t7 - Sign out" << endl;

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
			updateEvent(currentUser, currentUserEvents, allEvents);
			break;
		case 5:
			removeEvent(currentUser, currentUserEvents, allEvents);
			break;
		case 6:
			if (deleteUserAccount(allUsers, currentUser))
			{
				CLS;
				cout << "Your account has been deleted successfully!" << endl;
				return 0;
			}
			else
			{
				CLS;
			}
			break;
		case 7:
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

int allEventsMenu(User& currentUser, vector<Event>& allEvents, vector<Event>& currentUserEvents, vector<User>& allUsers)
{
	CLS;

	int pageNumber = 1;

	printPageWithEvents(pageNumber, allEvents);

	int option;
	printPageEventMenu();
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
				CLS;
				printPageWithEvents(pageNumber, allEvents);
			}
			else
			{
				CLS;
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
			CLS;
			printPageWithEvents(pageNumber, allEvents);
		}
		else if (option == 5)
		{
			pageNumber++;
			if (pageNumber >(allEvents.size() / 3 + 1))
			{
				pageNumber = allEvents.size() / 3 + 1;
			}
			CLS;
			printPageWithEvents(pageNumber, allEvents);
		}
		else if (option == 6)
		{
			CLS;
			return 0;
		}
		else
		{
			CLS;
			printPageWithEvents(pageNumber, allEvents);
			cout << "Error: Wrong option" << endl;
		}

		printPageEventMenu();
		cout << " Option > ";
		cin >> input;
		option = inputToInt(input);
	}

	return 0;
}

int userEventsMenu(User& currentUser, vector<Event>& currentUserEvents)
{
	CLS;

	int pageNumber = 1;

	cout << "List of your events:" << endl;
	printPageWithEvents(pageNumber, currentUserEvents);

	int option;
	printPageEventMenu();
	cout << " Option > ";
	string input;
	cin >> input;
	option = inputToInt(input);

	while (true)
	{
		if (option >= 1 && option <= 3)
		{
			if (((pageNumber - 1) * 3 + option - 1) < currentUserEvents.size())
			{
				userEventReview(currentUserEvents[(pageNumber - 1) * 3 + option - 1]);
				cout << "List of your events:" << endl;
				printPageWithEvents(pageNumber, currentUserEvents);
			}
			else
			{
				cout << "List of your events:" << endl;
				printPageWithEvents(pageNumber, currentUserEvents);
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
			CLS;
			cout << "List of your events:" << endl;
			printPageWithEvents(pageNumber, currentUserEvents);
		}
		else if (option == 5)
		{
			pageNumber++;
			if (pageNumber >(currentUserEvents.size() / 3 + 1))
			{
				pageNumber = currentUserEvents.size() / 3 + 1;
			}
			CLS;
			cout << "List of your events:" << endl;
			printPageWithEvents(pageNumber, currentUserEvents);
		}
		else if (option == 6)
		{
			CLS;
			return 0;
		}
		else
		{
			CLS;
			cout << "List of your events:" << endl;
			printPageWithEvents(pageNumber, currentUserEvents);
			cout << "Error: Wrong option" << endl;
		}

		printPageEventMenu();
		cout << " Option > ";
		cin >> input;
		option = inputToInt(input);
	}
	return 0;
}

void createEvent(User& currentUser, vector<Event>& currentUserEvents, vector<Event>& allEvents)
{
	cin.ignore(1024, '\n');

	CLS;

	string title;
	string date;
	string plot;
	string shortPlot;
	Priority priority;

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

void updateEvent(User& currentUser, vector<Event>& currentUserEvents, vector<Event>& allEvents)
{
	CLS;

	string titleCheck;
	string title;
	string date;
	string plot;
	string shortPlot;
	Priority priority;

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
				allEvents[optionEvent - 1].setTitle(title);

				cout << " New short plot: ";
				getline(cin, shortPlot);
				currentUserEvents[optionEvent - 1].setShortPlot(shortPlot);
				allEvents[optionEvent - 1].setShortPlot(shortPlot);

				cout << " New plot: ";
				getline(cin, plot);
				currentUserEvents[optionEvent - 1].setPlot(plot);
				allEvents[optionEvent - 1].setPlot(plot);

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
				allEvents[optionEvent - 1].setPriority(priority);

				date = getCurrentDate();

				currentUserEvents[optionEvent - 1].setDate(date);
				allEvents[optionEvent - 1].setDate(date);

				//TODO update currentUserEvents[optionEvent - 1]
				//TODO update allEvents[optionEvent - 1]

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

void removeEvent(User& currentUser, vector<Event>& currentUserEvents, vector<Event>& allEvents)
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
				allEvents.erase(allEvents.begin() + (optionEvent - 1));

				//TODO delete currentUserEvents[optionEvent - 1]
				//TODO delete allEvents[optionEvent - 1]

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

void removeCurrentEvent(vector<Event>& allEvents, Event& globalEvent, vector<Event>& currentUserEvents)
{
	int position;
	for (int i = 0; i < allEvents.size(); i++)
	{
		if (globalEvent == allEvents[i])
		{
			position = i;
			break;
		}
	}
	allEvents.erase(allEvents.begin() + position);
	currentUserEvents.erase(currentUserEvents.begin() + position);
}

int eventReview(User& currentUser, Event& globalEvent, vector<Event>& currentUserEvents, vector<Event>& allEvents, vector<User>& allUsers)
{
	CLS;
	while (true)
	{
		cout << "Title: " << globalEvent.getTitle() << endl;
		cout << "Plot:" << endl;
		cout << " " << globalEvent.getPlot() << endl;
		cout << "Popularity: " << globalEvent.getPopularity() << endl;
		printRateUsers(globalEvent);
		for (int i = 0; i < globalEvent.getComments().size(); i++)
		{
			cout << "Comments:" << endl;
			cout << " " << i + 1 << ":" << endl;
			cout << globalEvent.getComments()[i] << endl;
		}
		int option;
		string input;

		cout << "1 - add comment" << endl;
		cout << "2 - remove comment" << endl;
		cout << "3 - like the event" << endl;
		cout << "4 - dislike the event" << endl;
		cout << "5 - back to list" << endl;
		cout << " Option > ";
		cin >> input;
		option = inputToInt(input);

		switch (option)
		{
		case 1:
			addComment(currentUser, globalEvent, currentUserEvents, allEvents, allUsers);
			CLS;
			cout << "Comment has been added" << endl;
			break;
		case 2:
			if (globalEvent.getComments().size() != 0)
			{
				if (deleteComment(currentUser, globalEvent, currentUserEvents) == true)
				{
					CLS;
					cout << "Comment has been deleted" << endl;
				}
				else
				{
					CLS;
					cout << "Comment has not been deleted" << endl;
				}
			}
			else
			{
				CLS;
				cout << "There is no comments to delete!" << endl;
			}
			break;
		case 3:
			like(globalEvent, currentUser);
			break;
		case 4:
			dislike(globalEvent, currentUser, allEvents, currentUserEvents);
			break;
		case 5:
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

int userEventReview(Event& currentUserEvent)
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

void addComment(User& currentUser, Event& globalEvent, vector<Event>& currentUserEvents, vector<Event>& allEvents, vector<User>& allUsers)
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

	globalEvent.addComment(newComment);

	for (int i = 0; i < currentUser.getPosts().size(); i++)
	{
		if (globalEvent == currentUser.getPosts()[i])
		{
			currentUserEvents[i].addComment(newComment);
		}
	}

	//TODO create 'newComment'
}

bool deleteComment(User& currentUser, Event& globalEvent, vector<Event>& currentUserEvents)
{
	cout << "Enter number of comment you want to delete (1 - " << globalEvent.getComments().size() << ")" << endl;

	int number;
	string input;

	while (true)
	{
		cout << "Number > ";
		cin >> input;
		number = inputToInt(input);

		if (number >= 1 && number <= globalEvent.getComments().size())
		{
			if (currentUser.getUserName() == globalEvent.getComments()[number - 1].getAuthor())
			{
				globalEvent.removeComment(number - 1);
				for (int i = 0; i < currentUser.getPosts().size(); i++)
				{
					if (globalEvent == currentUser.getPosts()[i])
					{
						currentUserEvents[i].removeComment(number - 1);
						break;
					}
				}
				break;
			}
			else
			{
				cout << "Error: only author can delete this comment!" << endl;
				return false;
			}
		}
		else
		{
			cout << "Incorrect number of comment!" << endl;
		}
	}
	return true;
}

void printPageWithEvents(int pageNumber, vector<Event>& allEvents)
{
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

void printRemoveMenu(User& currentUser, vector<Event>& currentUserEvents)
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
	printM("To start working you need to sign in or sign up");

	print("Option list:");
	print(" 1 - Sign in");
	print(" 2 - Sign up");
	print(" 3 - Quit");
}

void printPageEventMenu()
{
	print("Choose number of event to review or one of the following options:");
	print("4 - Previous page");
	print("5 - Next page");
	print("6 - Back");
}

int inputToInt(string input)
{
	int result = 0;
	try {
		result = stoi(input);
		return result;
	}
	catch (invalid_argument& ex) {
		return result;
	}
}

bool quit()
{
	int option;

	cout << "Do you really want to leave ?" << endl;
	cout << " 1 - Yes" << endl;
	cout << " 2 - No" << endl;

	cout << "Option > ";
	string input;
	cin >> input;
	option = inputToInt(input);

	switch (option)
	{
	case 1:
		return true;
		break;
	case 2:
		CLS;
		return false;
		break;
	default:
		CLS;
		alert("Incorrect option!");
		return false;
		break;
	}
}

void deleteRateUser(Event& currentEvent, User& currentUser, char rate)
{
	string user;
	int position = -1;
	vector<string> tempUsersVector;

	tempUsersVector = currentEvent.getPopularityUsers();
	user = rate + currentUser.getUserName();
	for (int i = 0; i < currentEvent.getPopularityUsers().size(); i++)
	{
		if (user == currentEvent.getPopularityUsers()[i])
		{
			position = i;
			break;
		}
	}
	if (position >= 0)
	{
		tempUsersVector.erase(tempUsersVector.begin() + position);
		currentEvent.addPopularityUsers(tempUsersVector);
	}
}

bool checkUser(Event& currentEvent, User& currentUser, char rate)
{
	bool check = true;
	string user;

	for (int i = 0; i < currentEvent.getPopularityUsers().size(); i++)
	{
		user = currentEvent.getPopularityUsers()[i];
		if (user[0] == rate)
		{
			user.erase(user.begin());
			if (currentUser.getUserName() == user)
			{
				check = false;
			}
		}
	}

	return check;
}

void like(Event& currentEvent, User& currentUser)
{
	if (checkUser(currentEvent, currentUser, '1'))
	{
		if (!checkUser(currentEvent, currentUser, '0') && currentEvent.getPopularityUsers().size() != 0)
		{
			currentEvent.setPopularity(currentEvent.getPopularity() + 1);
			deleteRateUser(currentEvent, currentUser, '0');
			CLS;
			cout << "You liked this event" << endl;
		}
		else
		{
			currentEvent.setPopularity(currentEvent.getPopularity() + 1);
			currentEvent.addPopularityUsers('1' + currentUser.getUserName());
			CLS;
			cout << "You liked this event" << endl;
		}
	}
	else
	{
		CLS;
		cout << "You have already rated this event" << endl;
	}
}

void dislike(Event& currentEvent, User& currentUser, vector<Event>& allEvents, vector<Event>& currentUserEvents)
{
	if (checkUser(currentEvent, currentUser,'0'))
	{
		if (!checkUser(currentEvent, currentUser, '1') && currentEvent.getPopularityUsers().size() != 0)
		{
			currentEvent.setPopularity(currentEvent.getPopularity() - 1);
			deleteRateUser(currentEvent, currentUser, '1');
			CLS;
			cout << "You liked this event" << endl;
		}
		else
		{
			currentEvent.setPopularity(currentEvent.getPopularity() - 1);
			currentEvent.addPopularityUsers('0' + currentUser.getUserName());
			CLS;
			cout << "You disliked this event" << endl;
		}
	}
	else
	{
		CLS;
		cout << "You have already rated this event" << endl;
	}
	if (currentEvent.getPopularity() == -2)
	{
		removeCurrentEvent(allEvents, currentEvent, currentUserEvents);
		cout << "Sorry, but the event was deleted, 'cause of a bad popularity" << endl;
	}
}

void printRateUsers(Event& currentEvent)
{
	if (currentEvent.getPopularityUsers().size() == 0)
	{
		cout << "Nobody rated this event." << endl;
	}
	if (currentEvent.getPopularityUsers().size() == 1)
	{
		string lastUser;

		lastUser = currentEvent.getPopularityUsers()[currentEvent.getPopularityUsers().size() - 1];
		lastUser.erase(lastUser.begin());

		cout << "/ " << lastUser << " \\" << endl;
	}
	if (currentEvent.getPopularityUsers().size() >= 2)
	{
		string lastUser;
		string preLastUser;

		lastUser = currentEvent.getPopularityUsers()[currentEvent.getPopularityUsers().size() - 1];
		lastUser.erase(lastUser.begin());
		preLastUser = currentEvent.getPopularityUsers()[currentEvent.getPopularityUsers().size() - 2];
		preLastUser.erase(preLastUser.begin());

		cout << "/ " << lastUser << " , " << preLastUser << " \\" << endl;
	}
}
bool deleteUserAccount(vector<User>& allUsers, User& currentUser)
{
	CLS;
	while (true)
	{
		cout << "Deleting account:" << endl << endl;
		cout << "Info:" << endl;
		cout << " Data about your account will be deleted." << endl;
		cout << " All your post and commets will be saved." << endl << endl;
		cout << "Do you really want to delete your account ?" << endl;
		cout << "\t1 - Yes" << endl;
		cout << "\t2 - No" << endl;
		cout << "Option > ";

		int option;
		string input;
		cin >> input;
		option = inputToInt(input);

		string password;

		switch (option)
		{
		case 1:
			cout << endl;
			cout << "Enter your password to countinue:" << endl;
			cout << "Password > ";
			cin >> password;

			if (password == currentUser.getPassword())
			{
				int userIndex = 0;

				while (allUsers[userIndex].getPassword() != password)
				{
					userIndex++;
				}
				allUsers.erase(allUsers.begin() + userIndex);
				return true;
			}
			else
			{
				CLS;
				cout << "Incorrect password!" << endl;
			}
			break;
		case 2:
			return false;
			break;
		default:
			CLS;
			cout << "Incorrect option!" << endl;
			break;
		}
	}
}
