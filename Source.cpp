#include <iostream>

using namespace std;

class Pointer {
	int a;
public:
	Pointer(int a) {
		cout << "In Pointer's Constructor\n";
		this->a = a;
	}
	~Pointer() {
		cout << "In Pointer's Destructor\n";
	}
	void disp() {
		cout << "Pointer's disp\n";
	}
};
class Ref_Count {
	int count;
public:
	Ref_Count() {
		count = 1;
	}
	void add_ref() {
		count++;
	}
	int release() {
		count--;
		if (count > 0) {
			return 0;
		}
		return 1;
	}
	int get_ref() {
		return count;
	}
};

template<class T>
class SmartPointer {
	T* obj;
	Ref_Count* rc;
public:
	T& operator *() {
		return *obj;
	}
	/*T* operator &() {
		return obj;
	}*/
	T* operator ->() {
		return obj;
	}
	SmartPointer<T>& operator =(SmartPointer<T> &org_sp) {
		cout << "In Smart Pointer's Assignment operator\n";
		if (this != &org_sp) {
			if (!org_sp.rc)
				org_sp.rc = new Ref_Count();
			org_sp.rc->add_ref();
			rc = org_sp.rc;
		}
		cout << "Ref Count increment : " << org_sp.rc->get_ref() << endl;
		return *this;
	}
	SmartPointer(T * obj = NULL) {
		this->obj = obj;
		this->rc = NULL;
		cout << "In SmartPointer's Constructor\n";
	}
	~SmartPointer() {
		cout << "Deleting obj in SmartPoint's Destrctor\n";
		int release_res = rc->release();
		cout << "Ref Count decrement: " << rc->get_ref() << endl;
		if (release_res) {
			delete obj;
			delete rc;
		}
		rc = NULL;
	}
};


template <class T>
void pointer_details(T * p) {
	cout << "Poniter's address : " << &p << endl;
	cout << "Address stored in Pointer : " << p << endl;
	p->disp();
	(*p).disp();
}

template <class T>
void smart_pointer_details(T &sp) {
	cout << "Smart Pointer's Address : " << &sp << endl;
	sp->disp();
	(*sp).disp();
}

int main() {
	Pointer* p = new Pointer(11);
	
	SmartPointer<Pointer> sp(p);
	SmartPointer<Pointer> sp1, sp2;
	sp1 = sp;
	sp2 = sp;
	
	return 0;
}
