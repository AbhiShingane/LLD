#include<iostream>

using namespace std;

template<typename T>
class shared_ptr
{
	private:
		T* data;
		size_t* refcount;
	
	void release()
	{
		if(refcount)
		{
			--(*refcount);

			if(refcount == 0)
			{
				data = nullptr;
				refcount = nullptr;
			}
		}
	}

	public:
		explicit shared_ptr()
		{
			refcount = nullptr;
			data = nullptr;
		}

		explicit shared_ptr(T* ptr):data(ptr)
		{
			refcount = new size_t(1);
		}

		~shared_ptr()
		{
			release();
		}

		shared_ptr(const shared_ptr& other)
		{
			data = other.data;
			refcount = other.refcount;

			if(refcount)
				++(*refcount);
		}

		shared_ptr& operator=(const shared_ptr& other)
		{
			if(this == &other)
				return *this;

			data = other.data;
			refcount = other.refcount;

			if(refcount)
				++(*refcount);

			return *this;

		}

		shared_ptr(const shared_ptr&& other) noexcept = delete;
		shared_ptr& operator=(const shared_ptr&& other) = delete;


		T& operator*()
		{
			return *data;
		}

		T* operator->()
		{
			return data;
		}

		T& get() const
		{
			return *data;
		}

		int getcount() const
		{
			return refcount ? *refcount : 0;
		}


};

int main()
{
    shared_ptr<int> p1(new int(2));
    cout<<p1.getcount()<<endl;
    cout<<p1.get()<<endl;
    
    shared_ptr<int> p2 = p1;
    cout<<p1.getcount()<<"  "<<p2.getcount()<<endl;
    cout<<p1.get()<<"  "<<p2.get()<<endl;
    
    shared_ptr<int> p3(new int(9));
    cout<<p3.getcount()<<endl;
    cout<<p3.get()<<endl;

    return 0;
}