//Class called NumberBox
//Class will store one intger and live in dynamic memory
//private data member that is a pointer to an int
//public constructor that recieves an int
//A public function that: returns the stored number
//Use new to allocate memory for one integer
//Store the given value inside that dynamically allocated memory
//when NumberBox object destroyed use delete to free the allocated int
//Ensure no memory leaks occur

#include <iostream>

class NumberBox {
    private:
      int* ptr;  //A pointer to an intefger in dynamic memory
 
    public:
      //constructor: allocates memory and stores the value
      NumberBox(int val) {
        ptr = new int(val);
      }

      //destructor(Deallocation)
      ~NumberBox(){
        delete ptr; //Free the allocated integer memory
        ptr = nullptr; //Good practice prevent dangling pointers
      }

    //Function to return the stored value
    int getNumber() {
        return *ptr;
    }   
};

int main() {
    {
        NumberBox tempBox(500);
        std::cout << "Inside scope:" << tempBox.getNumber() << std::endl;
    } //<-- tempBox is destroyed here, 'delete' automatically called
}