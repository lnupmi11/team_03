#pragma once
#include"Header.h"
#include "User.h"


// info:
// Prints menu of removing events
void removeMenu(User &user, vector<Event> &events);

// info:
// Prints main menu
void mainMenu();

// info:
// Prints title and plot of chosen event.
int eventReview(Event userEvent);

// info:
// Prints titles and short plot of each user event.
int userEventsMenu(User &user, vector<Event> &events);

// info:
// Prints all events.
int reviewAllEvents(const User &user, vector<Event> &events);

// info:
// Create new user event.
void createEvent(User &user, vector<Event> &events);

// info:
// Update created event. Can be done only if you are an author.
void updateEvent(User &user, vector<Event> &events);

// info:
// Delete created event. Can be done only if you are an author.
void removeEvent(User &user, vector<Event> &events);

// info:
// Prints menu specially for user.
int userMenu(User &user, vector<Event> &events);

// info:
// New user registration.
void signUp(vector<User> &users);

// info:
// User authorization.
void signIn(vector<User> &users, vector<Event> &events);