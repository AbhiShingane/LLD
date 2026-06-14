template <typename T>
class Weakptr;

template <typename T>
struct controlblock
{
	T* ptr;
	size_t strongcount;
	size_t weakcount;

	public:
	controlblock(T* p): ptr(p), strongcount(1), weakcount(0){}
};


template <typename T>
class sharedptr
{
	private:
	controlblock *cb;

	void release()
	{
		if(cb)
		{
			--cb->strongcount;
			if(strongcount == 0)
			{
				delete[] cb->ptr;
				cb->weakcount = 0;
				cb = nullptr;
			}
		}
	}

	
	explicit sharedptr(controlblock<T> *cb): cb(cb)
	{
		if(cb)
			cb->strongcount++;
	}


	public:
	explicit shareptr(T *ptr)
	{
		cb = ptr ? new controlblock<T>(ptr): nullptr;
	}


	~sharedptr()
	{
		release();
	}


	sharedptr(const sharedptr &other) noexcept
	{
		cb = other.cb;

		if(cb)
			++strongcount;
	}

	sharedptr& operator=(const sharedptr &other) noexcept
	{
		if(this == &other)
			return *this;

		cb = other.cb;

		if(cb)
			++strongcount;

		return *this;
	}

	sharedptr(const sharedptr &&other) noexcept = delete;
	sharedptr(const sharedptr &&other) noexcept = delete;

	T& operator*()
	{
		return *(cb->ptr);
	}

	T* operator->()
	{
		return cb->ptr;
	}


	int use_count()
	{

		return cb ? cb->strongcount : 0;
	}

	T* get()
	{
		return cb->ptr;
	}

	friend class weakptr<T>;
};



template <typename T>
class weakptr
{
	private:
		Controlblock *cb;


	public:
		explicit weakptr(const sharedPtr<T> ptr)
		{
			cb = ptr.cb;
			if(cb)
				++weakcount;
		}

		explicit weakptr(const weakptr& other)
		{
			cb = other.cb;
			if(cb)
				++weakcount;
		}

		weakptr& operator=(const weakptr& other)
		{
			if(this == &other) return *this;

			release();
			cb = other.cb;
			if(cb)
				++weakcount;

			return *this;
		}

		explict weakptr(const weakptr&& other)
		{
			cb = other.cb;
			other.cb = nullptr;
		}

		weakptr& operator=(const weakptr&& other)
		{
			if(this == &other) return *this;

			release();
			cb = other.cb;
			if(cb)
				++weakcount;

			other.cb = nullptr;

			return *this;

		}

		T& operator*()
		{
			return cb->data;
		}

		T* opeartor->()
		{
			return *(cb->data);
		}

		T& get()
		{
			return cb->data;
		}

		int use_count()
		{
			return cb ? cb->strongcount : 0;
		}

		bool expired()
		{
			if(!cb 	|| cb->strongcount == 0) return true;

			else
				return false;
		}
};