/******************************************************************************
Title       : observer.hpp
Author      : Dan Cambitsis
Created on  : 5/1/2017
Description : Header file for: abstract Subject + Observer & concrete Subject and Observers
******************************************************************************/

#ifndef _OBSERVER_H
#define _OBSERVER_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

///////////////// ABSTRACT SUBJECT *********************
class Subject { //this is the abstract Subject
public:
	virtual void Attach(class Observer *observer) = 0;
	virtual void Detach(class Observer *observer) = 0;
	virtual void Notify() = 0;
	virtual int GetState() const = 0;
	virtual void SetState(const int the_state) = 0;
	virtual bool ObserversEmpty() const = 0;
	virtual int ObserversSize() const = 0;
};

//////////////// SUBJECT *****************

class ConcreteSubject : public Subject { //the Subject
public:
	void SetState(const int the_state);
	int GetState() const;
	void Attach(Observer *observer);
	void Detach(Observer *observer);
	void Notify();
	bool ObserversEmpty() const;
	int ObserversSize() const;
private:
	int state_;
	vector<Observer*> observers_;
};

////////////////////////// ABSTRACT OBSERVER ******************

class Observer { //this is the abstract Observer
public:
	Observer(ConcreteSubject *subject) { //loaded constructor
		subject_ = subject;
		subject_ -> Attach(this); //attach the current observer object
	}
	ConcreteSubject* GetSubject() const {
		return subject_;
	}
	virtual void Update() = 0;
private:
	ConcreteSubject *subject_;
};

//////////////// OBSERVERS *****************
class ConcreteObserverA : public Observer { //Observer A
public:
	ConcreteObserverA(ConcreteSubject *subject) : Observer(subject) { }
	void Update() {
		int num = GetSubject() -> GetState();
		cout << "@ Observer A -> num: " << num << endl;
	}
};

class ConcreteObserverB: public Observer { //Observer B
public:
	ConcreteObserverB(ConcreteSubject *subject) : Observer(subject) { }
	void Update() {
		int num = GetSubject() -> GetState();
		cout << "@ Observer B -> num: " << num << endl;
	}
};

#endif //_OBSERVER_H