#include <iostream>

class Person
{
private:
    std::string name;
    int age;

public:
    Person(const std::string& personName, int personAge) : name(personName), age(personAge)
    {
        std::cout << "Constructor called for " << name << "\n\n";
    }

    ~Person()
    {
        std::cout << "Destructor called for " << name << "\n\n";
    }

    /*
    * Class method to display person's information.
    * 
    * @return void const
    */
    void displayPersonInformation() const
    {
        std::cout << "Name: " << name << "\nAge: " << age << "\n\n";
    }

    /*
    * Class method to assign a person a new name.
    *
    * @param  const std::string& newPersonName Value of the previous person's name that will be changed
    * @return void  const
    */
    void setPersonName(const std::string& newPersonName)
    {
        this->name = newPersonName;

        std::cout << "Name has been changed to: " << newPersonName << "\n\n";
    }
};

/*
* Function to create an instance of Person class with pointer.
* 
* @param  const std::string& personName Person's name that will be assigned to an object
* @param  int                personAge  Person's age that will be assigned to an object 
* @return Person*
*/
Person* createPointerPerson(const std::string& personName, int personAge)
{
    return new Person(personName, personAge);
}

/*
* Function to delete an instance of Person class with pointer.
* 
* @param  const Person* person An instance of Person class with pointer
* @return void
*/
void deletePointerPerson(const Person* person)
{
    delete person;
    person = nullptr;

    std::cout << "Single object memory deallocated\n";
}

int main()
{
    std::cout << "Practice Project #2: Pointers and References\n";
    
    /* Creating an instance of Person class with and without pointer */

    Person firstPerson("John", 23);
    firstPerson.displayPersonInformation();

    Person* pointerPerson = createPointerPerson("Mike", 21);
    pointerPerson->displayPersonInformation();

    deletePointerPerson(pointerPerson);

    /* Creating unique_ptr<T> */

    std::unique_ptr<Person> uniquePointerPerson{ std::make_unique<Person>("Jane", 23) };

    // Since C++20 we can get pointer's address without function get()
    std::cout << "Address of uniquePointerPerson: " << uniquePointerPerson << "\n";  
    uniquePointerPerson->displayPersonInformation();

    uniquePointerPerson->setPersonName("Mary");
    uniquePointerPerson->displayPersonInformation();

    /* Creating shared_ptr<T> */

    std::shared_ptr<Person> sharedPointerPerson{ std::make_shared<Person>("Lina", 19) };
    sharedPointerPerson->displayPersonInformation();

    std::shared_ptr<Person> secondSharedPointerPerson{ sharedPointerPerson };
    std::cout << "Reference count: " << sharedPointerPerson.use_count() << "\n\n";

    /* Creating weak_ptr<T> */

    std::weak_ptr<Person> weakPointerPerson{ sharedPointerPerson };
    std::cout << "Number of shared pointers that manage this object: " << weakPointerPerson.use_count() << "\n\n";
    
    if (sharedPointerPerson = weakPointerPerson.lock()) 
    {
        std::cout << "sharedPointerPerson* is equal to " << sharedPointerPerson << "\n";
    }
    else
    {
        std::cout << "weakPointerPerson is expired\n\n";
    }

    return 0;
}
