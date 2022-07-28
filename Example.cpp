#include <iostream>

#include "Event.h"

using namespace std;

void Func1();
void Func1WithParams(int param1, string param2);
void Func2();
void Func2WithParams(int param1, string param2);

int main()
{
    //Instantiate an event object. Specify the parameter type(s) of the 
    //callback funtion signatures the event will be calling in angle brackets.
    //Events are only compatible with callbacks with a return type of void.

    Event<> event;
    Event<int, string> eventWithParams;

    //Add callbacks with either the Event.Add function or the += operator.

    event.AddCallback(Func1);
    event += Func2;
    eventWithParams.AddCallback(Func1WithParams);
    eventWithParams += Func2WithParams;

    //Call Event.Invoke to call all callbacks registered to the event.

    int intParam = 5;
    string stringParam = "Chicken";

    cout << "Invoking events..." << endl;

    event.Invoke();
    eventWithParams.Invoke(intParam, stringParam);

    cout << endl;

    //Remove callbacks with either the Event.Remove function or the -= operator.
    //Be sure to remove callbacks that no longer exist (ie. functions that belong 
    //to deleted object) before calling Event.Invoke, otherwise
    //calling Event.Invoke might have undefined behaviour.

    event.RemoveCallback(Func1);
    eventWithParams -= (Func1WithParams);

    cout << "Invoking events after removing some callbacks..." << endl;

    event.Invoke();
    eventWithParams.Invoke(intParam, stringParam);

    cout << endl;
}

void Func1()
{
    cout << "Called Func1." << endl;
}

void Func2()
{
    cout << "Called Func2." << endl;
}

void Func1WithParams(int param1, string param2)
{
    cout << "Called Func1WithParams. Params are " << param1 << ", " << param2 << endl;
}

void Func2WithParams(int param1, string param2)
{
    cout << "Called Func2WithParams. Params are " << param1 << ", " << param2 << endl;
}
