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
		printM("Option > ");
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

	input("Enter login > ", login);
	input("Enter password > ", login);

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
		alert("Error: Wrong login or password");
	}
}

void signUp(vector<User>& allUsers)
{
	string userName;
	string password;

	printM("Creating new user account");

	input("Enter new username > ", username);
	input("Enter new password > ", password);

	if (userName.size() <= 3)
	{
		CLS;
		alert("Error: username must have more than three symbols")l;
	}
	else if (!isalpha(userName[0]) || !isalpha(password[0]))
	{
		CLS;
		alert("Error: first symbol of username and password must be a letter");
	}
	else if (password.size() <= 3)
	{
		CLS;
		alert("Error: password is too short");
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
			printH("Your account has been created");
		}
		else
		{
			CLS;
			alert("Error: User with username " + userName + " already exists");
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
		printM("Menu");

		print(" Options:");
		print("\t1 - Review all events");
		print("\t2 - Review my events");
		print("\t3 - Create new event");
		print("\t4 - Update event");
		print("\t5 - Remove event");
		print("\t6 - Sign out");
		printE;
		int option;

		print("Option > ");
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
				printM("Your account has been deleted successfully!");
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
			alert("Error: Wrong option");
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
	print(" Option > ");
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
				alert("Error: Wrong option");
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
			alert("Error: Wrong option");
		}

		printPageEventMenu();
		print(" Option > ");
		cin >> input;
		option = inputToInt(input);
	}

	return 0;
}

int userEventsMenu(User& currentUser, vector<Event>& currentUserEvents)
{
	CLS;

	int pageNumber = 1;

	print("List of your events:");
	printPageWithEvents(pageNumber, currentUserEvents);

	int option;
	printPageEventMenu();
	print(" Option > ");
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
				print("List of your events:");
				printPageWithEvents(pageNumber, currentUserEvents);
			}
			else
			{
				print("List of your events:");
				printPageWithEvents(pageNumber, currentUserEvents);
				alert("Error: Wrong option");
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
			print("List of your events:");
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
			print("List of your events:");
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
			print("List of your events:");
			printPageWithEvents(pageNumber, currentUserEvents);
			alert("Error: Wrong option");
		}

		printPageEventMenu();
		input(" Option > ", input);
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

	printM("User: " + currentUser.getUserName());
	print("Creation of new event");

	input(" Title: ", title);
	input(" Short plot: ", shortPlot);
	input(" Plot: ", plot);

	int choosePrior = 0;

	bool checkPrior = false;

	while (checkPrior == false)
	{
		printM(" Priority (1 - low, 2 - medium, 3 - high): ");
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
			alert("Error. Wrong priority.");
			break;
		}
	}

	date = getCurrentDate();

	Event newEvent(title, plot, shortPlot, date, priority, currentUser.getUserName());

	//TODO create 'newEvent'

	currentUserEvents.push_back(newEvent);
	allEvents.push_back(newEvent);

	CLS;
	printH("New event has been created");
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

	printM("User: " + currentUser.getUserName());
	print("Updating of your event");
	print("Event list:");

	for (int i = 0; i < currentUserEvents.size(); i++)
	{
		print(" " + (i + 1) + " - " + currentUserEvents[i].getTitle());
	}
	print(" " + (currentUserEvents.size() + 1) + " - " + "Back");
	printE;

	int optionEvent;

	while (true)
	{
		print(" Option > ");
		string input;
		cin >> input;
		optionEvent = inputToInt(input);

		cin.ignore(1024, '\n');

		if (optionEvent >= 1 && optionEvent <= currentUserEvents.size())
		{
			if (currentUser.getUserName() == currentUserEvents[optionEvent - 1].getAuthor())
			{
				print(" New title: ");
				getline(cin, title);
				currentUserEvents[optionEvent - 1].setTitle(title);
				allEvents[optionEvent - 1].setTitle(title);

				print(" New short plot: ");
				getline(cin, shortPlot);
				currentUserEvents[optionEvent - 1].setShortPlot(shortPlot);
				allEvents[optionEvent - 1].setShortPlot(shortPlot);

				print(" New plot: ");
				getline(cin, plot);
				currentUserEvents[optionEvent - 1].setPlot(plot);
				allEvents[optionEvent - 1].setPlot(plot);

				int choosePrior = 0;

				bool checkPrior = false;

				while (checkPrior == false)
				{
					print(" New priority (1 - low, 2 - medium, 3 - high): ");
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
						alert("Error. Wrong priority.");
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

				print("Event has been updated.");
			}
			else
			{
				alert("Error. Wrong event or author.");
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
		print(" Choose event to remove > ");
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
				print("Event has been removed.");
			}
			else
			{
				alert("Error: Wrong event.");
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
		print("Title: " + globalEvent.getTitle());
		print("Plot:");
		print(" " + globalEvent.getPlot());
		print("Popularity: " + globalEvent.getPopularity());
		printRateUsers(globalEvent);
		for (int i = 0; i < globalEvent.getComments().size(); i++)
		{
			printM("Comments:");
			print(" " + (i + 1) + ":");
			print(globalEvent.getComments()[i]);
		}
		int option;
		string input;

		print("1 - add comment");
		print("2 - remove comment");
		print("3 - like the event");
		print("4 - dislike the event");
		print("5 - back to list");
		input(" Option > ", input);
		option = inputToInt(input);

		switch (option)
		{
		case 1:
			addComment(currentUser, globalEvent, currentUserEvents, allEvents, allUsers);
			CLS;
			print("Comment has been added");
			break;
		case 2:
			if (globalEvent.getComments().size() != 0)
			{
				if (deleteComment(currentUser, globalEvent, currentUserEvents) == true)
				{
					CLS;
					print("Comment has been deleted");
				}
				else
				{
					CLS;
					print("Comment has not been deleted");
				}
			}
			else
			{
				CLS;
				print("There is no comments to delete!");
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
			alert("Error: Wrong option");
			break;
		}
	}
	return 0;
}

int userEventReview(Event& currentUserEvent)
{
	CLS;

	print(" Title: " + currentUserEvent.getTitle());
	print(" Plot:" << currentUserEvent.getPlot());

	for (int i = 0; i < currentUserEvent.getComments().size(); i++)
	{
		print("Comments:");
		print(" " + (i + 1) + ":");
		print(currentUserEvent.getComments()[i]);
	}

	int option;

	while (true)
	{
		print("1 - back to list");
		print(" Option > ");
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
			alert("Error: Wrong option");
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

	print("Comment: ");
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
	print("Enter number of comment you want to delete (1 - " + globalEvent.getComments().size() + ")");

	int number;
	string input;

	while (true)
	{
		input("Number > ", input);
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
				alert("Error: only author can delete this comment!");
				return false;
			}
		}
		else
		{
			alert("Incorrect number of comment!");
		}
	}
	return true;
}

void printPageWithEvents(int pageNumber, vector<Event>& allEvents)
{
	int numberOfEvent = 0;

	print("Page #" + pageNumber);
	printE;

	for (int i = (pageNumber - 1) * 3; i <= (pageNumber - 1) * 3 + 2; i++)
	{
		if (i >= allEvents.size())
		{
			break;
		}
		numberOfEvent++;

		print(numberOfEvent + ") ");
		print("Title: " + allEvents[i].getTitle());
		printE;
		print("   Short plot: " + allEvents[i].getShortPlot());
		printE;
		print("   Date: " + allEvents[i].getDate() + "   Author: " + allEvents[i].getAuthor());
		printE;
		printE;
	}
}

void printRemoveMenu(User& currentUser, vector<Event>& currentUserEvents)
{
	CLS;

	print("User: " + currentUser.getUserName());
	print("Removing of your event");
	print("Event list:");

	for (int i = 0; i < currentUserEvents.size(); i++)
	{
		print(" " + (i + 1) + " - " + currentUserEvents[i].getTitle());
	}
	print(" " + (currentUserEvents.size() + 1) + " - " + "Back");
	printE;
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

	print("Do you really want to leave ?");
	print(" 1 - Yes");
	print(" 2 - No");

	print("Option > ");
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
			print("You liked this event");
		}
		else
		{
			currentEvent.setPopularity(currentEvent.getPopularity() + 1);
			currentEvent.addPopularityUsers('1' + currentUser.getUserName());
			CLS;
			print("You liked this event");
		}
	}
	else
	{
		CLS;
		alert("You have already rated this event");
	}
}

void dislike(Event& currentEvent, User& currentUser, vector<Event>& allEvents, vector<Event>& currentUserEvents)
{
	if (checkUser(currentEvent, currentUser, '0'))
	{
		if (!checkUser(currentEvent, currentUser, '1') && currentEvent.getPopularityUsers().size() != 0)
		{
			currentEvent.setPopularity(currentEvent.getPopularity() - 1);
			deleteRateUser(currentEvent, currentUser, '1');
			CLS;
			print("You liked this event");
		}
		else
		{
			currentEvent.setPopularity(currentEvent.getPopularity() - 1);
			currentEvent.addPopularityUsers('0' + currentUser.getUserName());
			CLS;
			print("You disliked this event");
		}
	}
	else
	{
		CLS;
		alert("You have already rated this event");
	}
	if (currentEvent.getPopularity() == -2)
	{
		removeCurrentEvent(allEvents, currentEvent, currentUserEvents);
		print("Sorry, but the event was deleted, 'cause of a bad popularity")
	}
}

void printRateUsers(Event& currentEvent)
{
	if (currentEvent.getPopularityUsers().size() == 0)
	{
		print("Nobody rated this event.");
	}
	if (currentEvent.getPopularityUsers().size() == 1)
	{
		string lastUser;

		lastUser = currentEvent.getPopularityUsers()[currentEvent.getPopularityUsers().size() - 1];
		lastUser.erase(lastUser.begin());

		print("/ " + lastUser + " \\");
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
		printM("Deleting account:");
		printE;
		print("Info:");
		print(" Data about your account will be deleted.");
		print(" All your post and commets will be saved.");
		printE;
		print("Do you really want to delete your account ?");
		print("\t1 - Yes");
		print("\t2 - No");
		print("Option > ");

		int option;
		string input;
		cin >> input;
		option = inputToInt(input);

		string password;

		switch (option)
		{
		case 1:
			cout << endl;
			printM("Enter your password to countinue:");
			print("Password > ");
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
				alert("Incorrect password!");
			}
			break;
		case 2:
			return false;
			break;
		default:
			CLS;
			alert"Incorrect option!");
			break;
		}
	}
}

int keySwitch(int startValue, int maxValue, int leftValue, int rightValue)
{
	int switchOption;
	int value;

	value = startValue;
	switchOption = 0;
	// do while enter hasn't been pressed; 
	switchOption = _getch();
	switch (switchOption)
	{
		//Up arrow;
	case 72:
		value--;
		if (value < 1)
		{
			value = maxValue;
		}
		return value;
		//Down arrow;
	case 80:
		value++;
		if (value > maxValue)
		{
			value = 1;
		}
		return value;
		//Right arrow;
	case 77:
		return rightValue;
		//Left arrow;
	case 75:
		return leftValue;
		//Enter
	case 13:
		return value = -1;
		//Numbers (1-9);
	case 49:
		return 1 % (maxValue + 1);
	case 50:
		return 2 % (maxValue + 1);
	case 51:
		return 3 % (maxValue + 1);
	case 52:
		return 4 % (maxValue + 1);
	case 53:
		return 5 % (maxValue + 1);
	case 54:
		return 6 % (maxValue + 1);
	case 55:
		return 7 % (maxValue + 1);
	case 56:
		return 8 % (maxValue + 1);
	case 57:
		return 9 % (maxValue + 1);
		//escape and 0 to return;
	case 27:case 48:
		return maxValue;
	default:
		break;
	}
	return value;
}