# Events
 A basic attempt of events in C++

The Event class is an attempt to copy the behaviour of Actions in C#. An event basically acts as a variable that can hold multiple functions (called callbacks). When the
Invoke method is called on an event, the event will call all of its associated callbacks.

If you would like to use the Event class, you willl need to add the Event.h, Delegate.h, StaticDelegate.h, and MemberDelegate.h files to your project. Please see the Example.cpp file for more info on how to use events.
