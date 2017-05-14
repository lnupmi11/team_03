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
	int exitOption;

	exitOption = 1;

	while (true)
	{
		//Interface;
		while (exitOption != -1)
		{
			CLS;
			printStartMenu(exitOption);
			option = exitOption;
			exitOption = keySwitch(exitOption, 3, 1, 1);
		}
		switch (option)
		{
		case 1:
			signIn(allUsers, allEvents);
			break;
		case 2:
			signUp(allUsers);
			break;
		case 3:
			if (quit() == true)
			{
				return 0;
			}
			break;
		default:
			CLS;
			alert("Incorrect option!");
			system("pause");
			break;
		}
		exitOption = 1;
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
		alert("Error: Wrong login or password");
		system("pause");
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
		alert("Error: username must have more than three symbols");
		system("pause");
	}
	else if(!isalpha(userName[0]) || !isalpha(password[0]))
	{
		CLS;
		alert("Error: first symbol of username and password must be a letter");
		system("pause");
	}
	else if(password.size() <= 3)
	{
		CLS;
		alert("Error: password is too short");
		system("pause");
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
		int option;
		int exitOption;

		exitOption = 1;

		//Interface;
		while (exitOption != -1)
		{
			CLS;
			option = exitOption;
			printMainMenu(exitOption);
			exitOption = keySwitch(exitOption, 7, 1, 1);
		}
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
	int option;
	int exitOption;

	exitOption = 1;

	while (true)
	{
		//Interface;
		while (exitOption != -1)
		{
			CLS;
			printPageWithEvents(pageNumber, allEvents, exitOption);
			printPageEventMenu(exitOption);
			option = exitOption;
			exitOption = keySwitch(exitOption, 6, 4, 5);
		}

		if (option >= 1 && option <= 3)
		{
			if (((pageNumber - 1) * 3 + option - 1) < allEvents.size())
			{
				eventReview(currentUser, allEvents[(pageNumber - 1) * 3 + option - 1], currentUserEvents, allEvents, allUsers);
			}
			else
			{
				CLS;
				alert("Error: Wrong option");
				system("pause");
			}
		}
		else if (option == 4)
		{
			pageNumber--;
			if (pageNumber < 1)
			{
				pageNumber = 1;
			}
		}
		else if (option == 5)
		{
			pageNumber++;
			if (pageNumber >(allEvents.size() / 3 + 1))
			{
				pageNumber = allEvents.size() / 3 + 1;
			}
		}
		else if (option == 6)
		{
			CLS;
			return 0;
		}
		else
		{
			CLS;
			alert("Error: Wrong option");
			system("pause");
		}
		exitOption = 1;
	}

	return 0;
}

int userEventsMenu(User& currentUser, vector<Event>& currentUserEvents)
{
	CLS;

	int pageNumber = 1;

	cout << "List of your events:" << endl;

	int option;
	int exitOption;

	exitOption = 1;

	while (true)
	{
		//Interface;
		while (exitOption != -1)
		{
			CLS;
			cout << "List of your events:" << endl;
			printPageWithEvents(pageNumber, currentUserEvents, exitOption);
			printPageEventMenu(exitOption);
			option = exitOption;
			exitOption = keySwitch(exitOption, 6, 4, 5);
		}

		if (option >= 1 && option <= 3)
		{
			if (((pageNumber - 1) * 3 + option - 1) < currentUserEvents.size())
			{
				userEventReview(currentUserEvents[(pageNumber - 1) * 3 + option - 1]);
			}
			else
			{
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
		}
		else if (option == 5)
		{
			pageNumber++;
			if (pageNumber >(currentUserEvents.size() / 3 + 1))
			{
				pageNumber = currentUserEvents.size() / 3 + 1;
			}
		}
		else if (option == 6)
		{
			CLS;
			return 0;
		}
		else
		{
			CLS;
			alert("Error: Wrong option");
			system("pause");

		}
		exitOption = 1;
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
				CLS;
				alert("Error. Wrong event or author.");
				system("pause");
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
				CLS;
				alert("Error: Wrong event.");
				system("pause");
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
	while (true)
	{
		int option;
		int exitOption;

		exitOption = 1;

		while (exitOption != -1)
		{
			CLS;
			printEventMenu(globalEvent, exitOption);
			option = exitOption;
			exitOption = keySwitch(exitOption, 7, 4, 3);
		}
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
			if (globalEvent.getComments().size() != 0)
			{
				exitOption = 1;
				while (exitOption != -1)
				{
					CLS;
					printCommentLikeMenu(globalEvent, exitOption);
					option = exitOption;
					if (option == 0)
					{
						option = 1;
					}
					exitOption = keySwitch(exitOption, globalEvent.getComments().size(), 0, 0);
				}
				likeComment(globalEvent, globalEvent.getComments()[option - 1], currentUser, (option - 1));
			}
			break;
		case 6:
			//dislikeComment;
			break;
		case 7:
			CLS;
			return 0;
			break;
		default:
			CLS;
			alert("Error: Wrong option");
			system("pause");
			break;
		}
	}
	return 0;
}

int userEventReview(Event& currentEvent)
{
	CLS;

	cout << " Title: " << currentEvent.getTitle() << endl;
	cout << " Plot:" << currentEvent.getPlot() << endl;

	for (int i = 0; i < currentEvent.getComments().size(); i++)
	{
		cout << "Comments:" << endl;
		cout << " " << i + 1 << ":" << endl;
		cout << currentEvent.getComments()[i] << endl;
		cout << "Popularuty: " << currentEvent.getComments()[i].getPopularity() << endl;
		printRateUsers(currentEvent.getComments()[i]);
	}

	int option;

	option = 1;

	while (true)
	{
		cout << "1 - back to list" << endl;
		option = keySwitch(option, 1, 1, 1);

		if (option == 1)
		{
			CLS;
			return 0;
		}
		else
		{
			CLS;
			alert("Error: Wrong option");
			system("pause");
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
	int number;
	string input;

	while (true)
	{
		cout << "Enter number of comment you want to delete (1 - " << globalEvent.getComments().size() << ")" << endl;
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
				CLS;
				alert("Error: only author can delete this comment!");
				system("pause");
				return false;
			}
		}
		else
		{
			CLS;
			alert("Incorrect number of comment!");
			system("pause");
		}
	}
	return true;
}

void removeCurrentComment(Event& globalEvent, Comment& globalComment)
{
	int position;
	vector<Comment> comments;
	comments = globalEvent.getComments();
	for (int i = 0; i < comments.size(); i++)
	{
		if (globalComment == comments[i])
		{
			position = i;
			break;
		}
	}
	comments.erase(comments.begin() + position);
	globalEvent.setComments(comments);
}

void printPageWithEvents(int pageNumber, vector<Event>& allEvents, int value)
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

		numberOfEvent == value ? cout << "-> " : cout << "   ";
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

void printPageEventMenu(int value)
{
	print("Choose number of event to review or one of the following options:");
	print(value == 4 ? "-> 4. Previous page " : "   4. Previous page ");
	print(value == 5 ? "-> 5. Next page " : "   5. Next page ");
	print(value == 6 ? "-> 6. Back " : "   6. Back ");
}

void printStartMenu(int value)
{
	printH("Welcome");
	printM("To start working you need to sign in or sign up");

	print("Option list:");
	print(value == 1?"-> 1. Sign in":"   1. Sign in");
	print(value == 2 ? "-> 2. Sign up" : "   2. Sign up");
	print(value == 3 ? "-> 3. Quit" : "   3. Quit");
}

void printMainMenu(int value)
{
	printH("  Menu  ");

	print(" Options:");
	print(value == 1 ? "-> 1. Review all events ":"   1. Review all events ");
	print(value == 2 ? "-> 2. Review my events ":"   2. Review my events ");
	print(value == 3 ? "-> 3. Create new event ":"   3. Create new event ");
	print(value == 4 ? "-> 4. Update event ":"   4. Update event ");
	print(value == 5 ? "-> 5. Remove event ":"   5. Remove event ");
	print(value == 6 ? "-> 6. Delete account ":"   6. Delete account ");
	print(value == 7 ? "-> 7. Sign out ":"   7. Sign out ");
}

void printEventMenu(Event& currentEvent,int value)
{
	cout << "Title: " << currentEvent.getTitle() << endl;
	cout << "Plot:" << endl;
	cout << " " << currentEvent.getPlot() << endl;
	cout << "Popularity: " << currentEvent.getPopularity() << endl;
	printRateUsers(currentEvent);
	cout << endl;
	cout << "Comments:" << endl;
	for (int i = 0; i < currentEvent.getComments().size(); i++)
	{
		cout << " " << i + 1 << ":" << endl;
		cout << currentEvent.getComments()[i];
		cout << "Popularuty: " << currentEvent.getComments()[i].getPopularity() << endl;
		printRateUsers(currentEvent.getComments()[i]);
	}
	cout << endl;
	value == 1 ? cout << "-> 1. add comment" : cout << "   1. add comment" ;
	cout << endl;
	value == 2 ? cout << "-> 2. remove comment" : cout << "   2. remove comment" ;
	cout << endl;
	value == 3 ? cout << "-> 3. like the event" : cout << "   3. like the event";
	cout << endl;
	value == 4 ? cout << "-> 4. dislike the event" : cout << "   4. dislike the event";
	cout << endl;
	value == 5 ? cout << "-> 5. like comment" : cout << "   5. like comment";
	cout << endl;
	value == 6 ? cout << "-> 6. dislike comment" : cout << "   6. dislike comment";
	cout << endl;
	value == 7 ? cout << "-> 7. back to list" : cout << "   7. back to list";
	cout << endl;
}

void printCommentLikeMenu(Event& currentEvent, int value)
{
	cout << "Title: " << currentEvent.getTitle() << endl;
	cout << "Plot:" << endl;
	cout << " " << currentEvent.getPlot() << endl;
	cout << "Popularity: " << currentEvent.getPopularity() << endl;
	printRateUsers(currentEvent);
	cout << endl;
	cout << "Comments:" << endl;
	for (int i = 0; i < currentEvent.getComments().size(); i++)
	{
		value == i+1 ? cout << "-> " : cout << "   ";
		cout << " " << i + 1 << ":" << endl;
		cout << currentEvent.getComments()[i];
		cout << "Popularuty: " << currentEvent.getComments()[i].getPopularity() << endl;
		printRateUsers(currentEvent.getComments()[i]);
	}
	cout << endl;
	cout << "   1. add comment";
	cout << endl;
	cout << "   2. remove comment";
	cout << endl;
	cout << "   3. like the event";
	cout << endl;
	cout << "   4. dislike the event";
	cout << endl;
	cout << "   5. like comment";
	cout << endl;
	cout << "   6. dislike comment";
	cout << endl;
	cout << "   7. back to list";
	cout << endl;
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

	option = keySwitch(1, 2, 1, 1);

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
		system("pause");
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

void deleteRateUser(Comment& currentComment, User& currentUser, char rate)
{
	string user;
	int position = -1;
	vector<string> tempUsersVector;
	tempUsersVector = currentComment.getPopularityUsers();
	user = rate + currentUser.getUserName();
	for (int i = 0; i < currentComment.getPopularityUsers().size(); i++)
	{
		if (user == currentComment.getPopularityUsers()[i])
		{
			position = i;
			break;
		}
	}
	if (position >= 0)
	{
		tempUsersVector.erase(tempUsersVector.begin() + position);
		currentComment.addPopularityUsers(tempUsersVector);
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

bool checkUserComment(Comment& currentComment, User& currentUser, char rate)
{
	bool check = true;
	string user;
	for (int i = 0; i < currentComment.getPopularityUsers().size(); i++)
	{
		user = currentComment.getPopularityUsers()[i];
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
		}
		else
		{
			currentEvent.setPopularity(currentEvent.getPopularity() + 1);
			currentEvent.addPopularityUsers('1' + currentUser.getUserName());
		}
	}
	else
	{
		CLS;
		alert("You have already liked this event");
		system("pause");
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
		}
		else
		{
			currentEvent.setPopularity(currentEvent.getPopularity() - 1);
			currentEvent.addPopularityUsers('0' + currentUser.getUserName());
		}
	}
	else
	{
		CLS;
		alert("You have already disliked this event");
		system("pause");
	}
	if (currentEvent.getPopularity() == -2)
	{
		removeCurrentEvent(allEvents, currentEvent, currentUserEvents);
		CLS;
		alert("Sorry, but the event was deleted, 'cause of a bad popularity");
		system("pause");
	}
}

void likeComment(Event& currentEvent, Comment& currentComment, User& currentUser, int position)
{
	if (checkUserComment(currentComment, currentUser, '1'))
	{
		if (!checkUserComment(currentComment, currentUser, '0') && currentComment.getPopularityUsers().size() != 0)
		{
			currentComment.setPopularity(currentComment.getPopularity() + 1);
			deleteRateUser(currentComment, currentUser, '0');
			currentEvent.setComment(currentComment, position);
			CLS;
			cout << "You liked this comment" << endl;
		}
		else
		{
			currentComment.setPopularity(currentComment.getPopularity() + 1);
			currentComment.addPopularityUsers('1' + currentUser.getUserName());
			currentEvent.setComment(currentComment, position);
			CLS;
			cout << "You liked this comment" << endl;
		}
	}
	else
	{
		CLS;
		cout << "You have already rated this comment" << endl;
	}
}

void printRateUsers(Event& currentEvent)
{
	if (currentEvent.getPopularityUsers().size() == 0)
	{
		cout << "Be the First to Like This." << endl;
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

void printRateUsers(Comment& currentComment)
{
	if (currentComment.getPopularityUsers().size() == 0)
	{
		cout << "Nobody rated this comment." << endl;
	}
	if (currentComment.getPopularityUsers().size() == 1)
	{
		string lastUser;

		lastUser = currentComment.getPopularityUsers()[currentComment.getPopularityUsers().size() - 1];
		lastUser.erase(lastUser.begin());
		cout << "/ " << lastUser << " \\" << endl;
	}
	if (currentComment.getPopularityUsers().size() >= 2)
	{
		string lastUser;
		string preLastUser;

		lastUser = currentComment.getPopularityUsers()[currentComment.getPopularityUsers().size() - 1];
		lastUser.erase(lastUser.begin());
		preLastUser = currentComment.getPopularityUsers()[currentComment.getPopularityUsers().size() - 2];
		preLastUser.erase(preLastUser.begin());
		cout << "/ " << lastUser << " , " << preLastUser << " \\" << endl;
	}
}

bool deleteUserAccount(vector<User>& allUsers, User& currentUser)
{
	CLS;
	while (true)
	{
		int option;

		option = 1;

		cout << "Deleting account:" << endl << endl;
		cout << "Info:" << endl;
		cout << " Data about your account will be deleted." << endl;
		cout << " All your post and commets will be saved." << endl << endl;
		cout << "Do you really want to delete your account ?" << endl;
		cout << "1. Yes" << endl;
		cout << "2. No" << endl;
		
		option = keySwitch(option, 2, 1, 1);

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
			alert("Incorrect option!");
			system("pause");
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