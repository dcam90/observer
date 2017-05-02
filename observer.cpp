/******************************************************************************
Title       : observer.cpp
Author      : Dan Cambitsis
Created on  : 5/1/2017
Description : Functions for ConcreteSubject + Catch testing framework execution
RUN WITH    : g++ -Wall -pedantic observer.cpp -o observer -std=c++11
******************************************************************************/
#define CATCH_CONFIG_MAIN

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "catch.hpp"
#include "observer.hpp"

using namespace std;

TEST_CASE("Observer patterns", "[pattern]") {
	ConcreteSubject *subject = new ConcreteSubject(); //create a new ConcreteSubject

	REQUIRE(subject -> ObserversEmpty() == true);
	REQUIRE(subject -> ObserversSize() == 0);

	ConcreteObserverA coA(subject); //first observer
	ConcreteObserverB coB(subject); //second observer

	REQUIRE(subject -> ObserversEmpty() == false); //the observers vector should no longer be empty
	REQUIRE(subject -> ObserversSize() == 2); //two observers (A and B)

	cout << "Setting state to 5: " << endl; //FOR A AND B
	subject -> SetState(5);
	REQUIRE(subject -> GetState() == 5);
	cout << "Setting state to 10: " << endl;
	subject -> SetState(10);
	REQUIRE(subject -> GetState() == 10);
	cout << "Setting state to 20: " << endl;
	subject -> SetState(20);
	REQUIRE(subject -> GetState() == 20);

	cout << endl;
	cout << "DETACHING OBSERVER B ... " << endl;
	subject -> Detach(&coB);
	cout << endl;

	REQUIRE(subject -> ObserversEmpty() == false); //the observers vector should no longer be empty
	REQUIRE(subject -> ObserversSize() == 1); //one observer (A)

	cout << "Setting state to 50: " << endl; //A ONLY 
	subject -> SetState(50);
	REQUIRE(subject -> GetState() == 50);
	cout << "Setting state to 100: " << endl; 
	subject -> SetState(100);
	REQUIRE(subject -> GetState() == 100);

	cout << endl;
	cout << "DETACHING OBSERVER A ... " << endl;
	subject -> Detach(&coA);
	cout << "ALL OBSERVERS HAVE BEEN REMOVED.";
	cout << endl;

	REQUIRE(subject -> ObserversEmpty() == true); //the observers vector should be empty
	REQUIRE(subject -> ObserversSize() == 0); //no more observers

}


////////////METHODS FOR CONCRETESUBJECT
void ConcreteSubject::SetState(const int the_state) {
	state_ = the_state; //set the incoming state to the class's state
	Notify(); //notify (update the observer vector)
}

int ConcreteSubject::GetState() const {
	return state_; //return the state
}

void ConcreteSubject::Attach(Observer *observer) {
	observers_.push_back(observer); //add the observer to the vector of observers
}

void ConcreteSubject::Detach(Observer *observer) {
	if (find(observers_.begin(), observers_.end(), observer) != observers_.end() == false) {
		return; //we didn't find the desired observer to detach
	}

	observers_.erase(remove(observers_.begin(), observers_.end(), observer), observers_.end());
	//remove the observer from the vector
}

void ConcreteSubject::Notify() {
	for (unsigned int i = 0; i < observers_.size(); ++i) {
		observers_[i] -> Update(); //for all observers, update each observer
	}
}

bool ConcreteSubject::ObserversEmpty() const {
	return observers_.empty(); //check to see if the vector is empty (returns true if empty)
}

int ConcreteSubject::ObserversSize() const {
	return observers_.size(); //return the size of the observers vector
}
