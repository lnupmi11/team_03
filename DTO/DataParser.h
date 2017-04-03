#pragma once
#include <string>
#include "../Entity/User.h"
#include "../Entity/Event.h"
using namespace std;

vector<User> parseUsersToList(string data);

vector<Event> parseEventsToList(string data);

string composeUsersToList(vector<User> users);

string composeEventsToList(vector<Event> events);

User parseUser(string data);

Event parseEvent(string data);

string composeUser(User user);

string composeEvent(Event event);

vector<string> split(char delim, string toSplit);
