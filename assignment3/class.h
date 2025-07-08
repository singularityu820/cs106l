class MyClass {
public:
    MyClass();
	MyClass(int initialValue);
    ~MyClass();
	void myMethod();
	int getMyAttribute() const;
	void setMyAttribute(int value);

private:
    int myAttribute;
	void helperMethod();
};