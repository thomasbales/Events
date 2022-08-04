#include <iostream>

#include "Event.h"

using namespace std;

void FuncWithParams(int param1);

class TestClass
{
public:
    void ClassMethod(int param)
    {
        cout << "Called ClassMethod. Param is: " << param << endl;
    }
};

int main()
{
    //Declare an event by specifying its parameters in angle brackets<>.
    Event<int> myEvent;

    //Add static or member function listeners with the AddListener function
        //Adding a static function only requires the function's pointer.
        //Adding a member function requires the function's pointer, and the 
        //class instance it's attached to.
            //Member function pointer syntax: &ClassName::ClassMethodName
    TestClass* testClass = new TestClass();

    myEvent.AddListener(FuncWithParams);
    myEvent.AddListener(testClass, &TestClass::ClassMethod);

    //Call all listeners attached to the function with the Invoke method, or 
    //the () operator.
    myEvent.Invoke(1);
    myEvent(2);

    //Remove listeners with the RemoveListener function.
        //Removing a static function only requires the function's pointer.
        //Removing a member function requires the function's pointer, and the 
        //instance it's attached to.
    myEvent.RemoveListener(FuncWithParams);
    myEvent.RemoveListener(testClass, &TestClass::ClassMethod);

    //Events are implemented as a wrapper class for a list of delegates. A delegate is like a 
    //variable that can hold a single function.
        //Declare an event by specifying its return type followed by its
        //parameters in angle brackets<>.
    Delegate<void, int> myDelegate;
    Delegate<void, int> anotherDelegate;

    //Attach a function to the delegate with the Bind method. This is similar to Event.AddListener.
    myDelegate.Bind(FuncWithParams);
    anotherDelegate.Bind(testClass, &TestClass::ClassMethod);

    //Call the bound function with the Invoke function or () operator.
    myDelegate.Invoke(3);
    anotherDelegate(4);

    //Remove an attached function with the Unbind method. This is similar to Event.RemoveListener.
    myDelegate.Unbind();
    anotherDelegate.Unbind();

    //Delegates are implemented as a wrapper class for two more specialized delegate classes.
        //StaticDelegates function like delegates, except they can only hold static functions.
        //MemberDelegates function like delegates, except they can only hold member functions.
    //Eventually, delegate functionality could be expanded to support lambda functions by implementing
    //a LambdaDelegate class.

    StaticDelegate<void, int> staticDelegate;
    MemberDelegate<TestClass, void, int> memberDelegate;
   
    staticDelegate.Bind(FuncWithParams);
    memberDelegate.Bind(testClass, &TestClass::ClassMethod);

    staticDelegate.Invoke(5);
    memberDelegate(6);
}

void FuncWithParams(int param1)
{
    cout << "Called Func1WithParams. Params are " << param1 << endl;
}
