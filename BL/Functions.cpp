#include "Header.h"
#include "User.h"
#include "Event.h"
#include "Functions.h"

using namespace std;


void removeMenu(User &user, vector<Event> &events)
{
	system("CLS");

	cout << "User: " << user.getUserName() << endl;
	cout << "Removing of your event" << endl;
	cout << "Event list:" << endl;

	for (int i = 0; i < events.size(); i++)
	{
		cout << " " << i + 1 << " - " << events[i].getTitle() << endl;
	}
	cout << " " << events.size() + 1 << " - " << "Back" << endl;
	cout << endl;
}

void mainMenu()
{
	cout << "Welcome" << endl;
	cout << "To start working you need to sign in of sign up" << endl;

	cout << "Option list:" << endl;
	cout << " 1 - Sign in" << endl;
	cout << " 2 - Sign up" << endl;
	cout << " 3 - Quit" << endl;
}

int eventReview(Event userEvent)
{
	system("CLS");
	cout << " Title: " << userEvent.getTitle() << endl;
	cout << " Plot:" << endl;
	cout << userEvent.getPlot() << endl;

	int endReview;
	while (true)
	{
		cout << "1 - back to list" << endl;
		cout << " Option > ";
		cin >> endReview;

		if (endReview == 1)
		{
			system("CLS");
			return 0;
		}
		else
		{
			cout << "Wrong option." << endl;
		}
	}
	return 0;
}

int reviewAllEvents(const User &user, vector<Event> &events)
{
	system("CLS");

	int pageNumber = 0;

	for (int i = (pageNumber - 1) * 3; i <= (pageNumber - 1) * 3 + 2; i++)
	{
		if (i >= events.size())
		{
			break;
		}
		cout << events[i].getTitle() << endl;
		cout << events[i].getShortPlot() << endl;
		cout << events[i].getDate() << events[i].getAuthor() << endl;
	}

	return 0;
}

int userEventsMenu(User &user, vector<Event> &events)
{
	system("CLS");
	while (true)
	{
		cout << "User: " << user.getUserName() << endl;
		cout << "List of your events:" << endl;

		for (int i = 0; i < events.size(); i++)
		{
			cout << i + 1 << ":" << endl;
			cout << " Title: " << events[i].getTitle() << endl;
			cout << " Short plot: " << events[i].getShortPlot() << endl;
			cout << " Date: " << events[i].getDate() << endl;
			cout << endl;
		}

		int option;

		cout << "Choose event for a full review. (Back to list - " << events.size() + 1 << ")" << endl;
		cout << " Option > ";
		cin >> option;

		if (option >= 1 && option <= events.size())
		{
			eventReview(events[option - 1]);
		}
		else if (option == (events.size() + 1))
		{
			system("CLS");
			return 0;
		}
		else
		{
			system("CLS");
			cout << "Option error. Wrong option." << endl;
		}
	}
	return 0;
}

void createEvent(User &user, vector<Event> &events)
{
	cin.ignore(1024, '\n');

	system("CLS");

	string title;
	string date;
	string plot;
	string shortPlot;
	Priorities priority;

	cout << "User: " << user.getUserName() << endl;
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
		cin >> choosePrior;
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

	cout << " Current date: ";
	getline(cin, date);

	Event newEvent(title, plot, shortPlot, date, priority, user.getUserName());

	//TODO create newEvent

	events.push_back(newEvent);

	system("CLS");
	cout << "New event has been created" << endl;
}

void updateEvent(User &user, vector<Event> &events)
{
	system("CLS");

	string titleCheck;
	string title;
	string date;
	string plot;
	string shortPlot;
	Priorities priority;

	cout << "User: " << user.getUserName() << endl;
	cout << "Updating of your event" << endl;
	cout << "Event list:" << endl;

	for (int i = 0; i < events.size(); i++)
	{
		cout << " " << i + 1 << " - " << events[i].getTitle() << endl;
	}
	cout << " " << events.size() + 1 << " - " << "Back" << endl;
	cout << endl;

	int optionEvent;

	while (true)
	{
		cout << " Option > ";
		cin >> optionEvent;

		cin.ignore(1024, '\n');

		if (optionEvent >= 1 && optionEvent <= events.size())
		{
			if (user.getUserName() == events[optionEvent - 1].getAuthor())
			{
				cout << " New title: ";
				getline(cin, title);
				events[optionEvent - 1].setTitle(title);

				cout << " New short plot: ";
				getline(cin, shortPlot);
				events[optionEvent - 1].setShortPlot(shortPlot);

				cout << " New plot: ";
				getline(cin, plot);
				events[optionEvent - 1].setPlot(plot);

				int choosePrior = 0;

				bool checkPrior = false;

				while (checkPrior == false)
				{
					cout << " New priority (1 - low, 2 - medium, 3 - high): ";
					cin >> choosePrior;

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
				events[optionEvent - 1].setPriority(priority);

				cout << " Current date: ";
				getline(cin, date);
				events[optionEvent - 1].setDate(date);

				//TODO update events[optionEvent - 1]

				cout << "Event has been updated." << endl;
			}
			else
			{
				cout << "Update error. Wrong event or author." << endl;
			}
		}
		else if (optionEvent == (events.size() + 1))
		{
			system("CLS");
			break;
		}
	}
}

void removeEvent(User &user, vector<Event> &events)
{
	removeMenu(user, events);

	int optionEvent;

	while (true)
	{
		cout << " Choose event to remove > ";
		cin >> optionEvent;

		if (optionEvent >= 1 && optionEvent <= events.size())
		{
			if (user.getUserName() == events[optionEvent - 1].getAuthor())
			{
				events.erase(events.begin() + (optionEvent - 1));

				//TODO delete events[optionEvent - 1]

				removeMenu(user, events);
				cout << "Event has been removed." << endl;
			}
			else
			{
				cout << "Removing error. Wrong event." << endl;
			}
		}
		else if (optionEvent == events.size() + 1)
		{
			break;
		}
	}
	system("CLS");
}

int userMenu(User &user, vector<Event> &events)
{
	system("CLS");

	cout << "Welcome " << user.getUserName() << endl;

	while (true)
	{
		cout << "   Menu" << endl;

		cout << " Options:" << endl;
		cout << "\t1 - Review my events" << endl;
		cout << "\t2 - Create new event" << endl;
		cout << "\t3 - Update event" << endl;
		cout << "\t4 - Remove event" << endl;
		cout << "\t5 - Sign out" << endl;

		int option;

		cout << "Option > ";
		cin >> option;

		switch (option)
		{
		case 1:
			userEventsMenu(user, events);
			break;
		case 2:
			createEvent(user, events);
			break;
		case 3:
			updateEvent(user, events);
			break;
		case 4:
			removeEvent(user, events);
			break;
		case 5:
			system("CLS");
			return 0;
			break;
		default:
			cout << "Option error. Wrong option." << endl;
			break;
		}
	}
	return 0;
}

void signUp(vector<User> &users)
{
	string userName;
	string password;

	cout << "Creating new user account" << endl;

	cout << "Enter new username > ";
	cin >> userName;
	cout << "Enter new password > ";
	cin >> password;
	
	bool isCreated = true;

	for (int i = 0; i < users.size(); i++)
	{
		if (userName == users[i].getUserName())
		{
			isCreated = false;
			break;
		}
	}

	if (isCreated == true)
	{
		User newUser(userName, password);

		//TODO newUser

		users.push_back(newUser);

		system("CLS");
		cout << "Your account has been created" << endl;
	}
	else
	{
		system("CLS");
		cout << "Creation error. User with username " << userName << " already exists." << endl;
	}
}

void signIn(vector<User> &users, vector<Event> &events)
{
	string login;
	string password;

	bool checkEntry = false;

	cout << "Enter login > ";
	cin >> login;
	cout << "Enter password > ";
	cin >> password;

	for (int i = 0; i < users.size(); i++)
	{
		if (login == users[i].getUserName() && password == users[i].getPassword())
		{
			checkEntry = true;
			userMenu(users[i], users[i].getPosts());
			break;
		}
	}

	if (checkEntry == false)
	{
		system("CLS");
		cout << "Entry error. Wrong login or password." << endl;
	}
}