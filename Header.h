#pragma once
template<typename T>
class Iterator
{
protected:
	Iterator() {}
public:
	virtual ~Iterator() {};
	virtual void First() = 0;
	virtual void Next() = 0;
	virtual bool IsDone() const = 0;
	virtual T GetCurrent() const = 0;
};

template<typename T>
class StackArrayIterator : public Iterator<T>
{
private:
	T* StackArrayContainer;
	size_t Pos;
	size_t Size;
public:

	StackArrayIterator(T* container, size_t size) : StackArrayContainer(container), Pos(0), Size(size) {}

	virtual void First() override { Pos = 0; }
	virtual void Next() override { Pos++; }
	bool IsDone() const override { return  (Pos >= Size); }
	T GetCurrent() const override { return StackArrayContainer[Pos]; }
};

const size_t MaxSize = 100;
template <typename T>
class StackClass
{
private:
	T Items[MaxSize]{};

	size_t Top;

public:
	StackClass() : Top(0) {};

	bool IsEmpty() const { return (Top == 0); }

	size_t Size() const { return Top; }

	void Push(T newObject) { if (Top < MaxSize) Items[Top++] = newObject; else std::cout << "Stack overflow"; }

	T Pop() { return Items[--Top]; }

	T GetByIndex(size_t index) const { return Items[index]; }

	class Iterator<T>* GetIterator() { return new StackArrayIterator<T>(Items, Top); }
};


template <typename T>
class ArrayClass
{
private:
	T Items[MaxSize]{};

	size_t ArraySize;

public:

	ArrayClass() : ArraySize(0) {}

	void Add(T newObject) { Items[ArraySize++] = newObject; }

	T GetElement(size_t index) const { if (index < ArraySize) return Items[index]; else std::cout << "Array overfow"; }

	class Iterator<T>* GetIterator() { return new StackArrayIterator<T>(Items, ArraySize); }
};

template<typename T>
class IteratorDecorator : public Iterator<T>
{
protected:
	Iterator<T>* It;

public:
	IteratorDecorator(Iterator<T>* it) : It(it) {}
	virtual ~IteratorDecorator() { delete It; }
	virtual void First() { It->First(); }
	virtual void Next() { It->Next(); }
	virtual bool IsDone() const { return It->IsDone(); }
	virtual T GetCurrent() const { return It->GetCurrent(); }
};

template<typename ContainerType, typename ItemType>
class ConstIteratorAdapter : public Iterator<ItemType>
{
protected:
	ContainerType* Container;
	typename ContainerType::const_iterator It;

public:
	ConstIteratorAdapter(ContainerType* container) : Container(container) { It = Container->begin(); }

	virtual ~ConstIteratorAdapter() {}
	virtual void First() { It = Container->begin(); }
	virtual void Next() { It++; }
	virtual bool IsDone() const { return (It == Container->end()); }
	virtual ItemType GetCurrent() const { return *It; }
};

