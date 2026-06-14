#include<iostream>

/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include<iostream>

using namespace std;

template <typename T>
class unique_ptr
{
	private:
	T* data;

	public:
	explicit unique_ptr(T* ptr = nullptr): data(ptr)
	{
		
	}

	unique_ptr(const unique_ptr& other) noexcept = delete;
	unique_ptr& operator=(const unique_ptr& other) noexcept = delete;

	unique_ptr(unique_ptr&& other) noexcept
	{
		data = other.data;
		other.data = nullptr;
	}

	unique_ptr& operator=(unique_ptr&& other) noexcept
	{
		if(this == &other)
			return *this;

		data = other.data;
		other.data = nullptr;

		return *this;
	}

	T& operator*()
	{
		return *data;
	}

	T* operator->()
	{
		return data;
	}

	T& get()
	{
		if(data == nullptr) return NULL;
		
		return *data;
	}
};

int main()
{
    unique_ptr<int> p1(new int(2));
    //cout<<p1.getcount()<<endl;
    cout<<p1.get()<<endl;
    
    unique_ptr<int> p2 = std::move(p1);
    
    //cout<<p1.getcount()<<"  "<<p2.getcount()<<endl;
    cout<<p2.get()<<endl;
    
    unique_ptr<int> p3(std::move(p2));
    cout<<p3.get()<<endl;
    cout<<"p1: "<<p1.get()<<"  p2:"<<p2.get()<<"  p3:"<<p3.get()<<endl;
    
    
    return 0;
}