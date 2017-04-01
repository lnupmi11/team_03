#pragma once
#include"../Utils/Header.h"
#include "../Entity/User.h"
#include "../Entity/Event.h"

// info:
// Generate and return current date of type 'string'.
string getCurrentDate();

// info:
// Main menu.
int mainMenu(vector<User>& allUsers, vector<Event>& allEvents);

// info:
// Create new comment.
void addComment(User& currentUser, Event& globalEvent, vector<Event>& currentUserEvents, vector<Event>& allEvents, vector<User>& allUsers);

// info:
// Delete comment. Can be done only if you are an author.
bool deleteComment(User& currentUser, Event& globalEvent, vector<Event>& currentUserEvents);

// info:
// Prints menu of removing events.
void printRemoveMenu(User& currentUser, vector<Event>& currentUserEvents);

// info:
// Prints menu for all event.
void printAllEventMenu();

// info:
// Prints main menu.
void printMainMenu();

// info:
// Prints title and plot of chosen event.
int eventReview(User& currentUser, Event& globalEvent, vector<Event>& currentUserEvents, vector<Event>& allEvents, vector<User>& allUsers);

// info:
// Prints user event without opportunity to comment.
int userEventReview(Event& currentUserEvent);

// info:
// Prints titles and short plot of each user event.
int userEventsMenu(User& currentUser, vector<Event>& currentUserEvents);

// info:
// Prints three events on one page.
void printPageWithEvents(int pageNumber, vector<Event>& allEvents);

// info:
// Option menu of all events.
int allEventsMenu(User& currentUser, vector<Event>& allEvents, vector<Event>& currentUserEvents, vector<User>& allUsers);

// info:
// Create new user event.
void createEvent(User& currentUser, vector<Event>& currentUserEvents, vector<Event>& allEvents);

// info:
// Update created event. Can be done only if you are an author.
void updateEvent(User& currentUser, vector<Event>& currentUserEvents, vector<Event>& allEvents);

// info:
// Delete created event. Can be done only if you are an author.
void removeEvent(User& currentUser, vector<Event>& currentUserEvents, vector<Event>& allEvents);

// info:
// Delete current event.
void removeCurrentEvent(vector<Event>& allEvents, Event& globalEvent, vector<Event>& currentUserEvents);

// info:
// Prints menu specially for user.
int userMenu(User& currentUser, vector<Event>& currentUserEvents, vector<Event>& allEvents, vector<User>& allUsers);

// info:
// New user registration.
void signUp(vector<User>& allUsers);

// info:
// User authorization.
void signIn(vector<User>& allUsers, vector<Event>& allEvents);

// info:
// input to int
int inputToInt(string input);

// info:
// Verification of exit.
bool quit();

// info:
// check if current user is in list.
bool checkUser(Event& currentEvent, User& currentUser);

// info:
// like the event.
void like(Event& currentEvent, User& currentUser);

// info:
// dislike the event.
void dislike(Event& currentEvent, User& currentUser, vector<Event>& allEvents, vector<Event>& currentUserEvents);

// info:
// Deleting of existing user.
bool deleteUserAccount(vector<User>& allUsers, User& currentUser);
