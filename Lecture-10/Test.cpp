#include <iostream>
using namespace std;

template<typename T>
class node{
public:
	T key;
	int value;
	node<T>* next;
	node(T s,int v){
		key = s;
		value=v;
		next = NULL;
	}
};
template<typename T>
class hashmap{
	node<T>** Bucket;
	int cs;
	int ts;

	int hashFn(T key){
		int ans = 0;
		int mul_factor = 1;
		for(int i=0;key[i]!='\0';i++){
			ans += mul_factor*key[i];
			mul_factor *= 37;

			ans %= ts;
			mul_factor %= ts;
		}
		ans = ans%ts;
		return ans;
	}

	void rehash(){
		node<T> ** oldBucket = Bucket;
		int oldts = ts;

		Bucket = new node<T>*[2*ts];
		cs = 0;
		ts = 2*ts;
		for(int i=0;i<ts;i++){
			Bucket[i] = NULL;
		}

		for(int i=0;i<oldts;i++){
			node<T>* temp = oldBucket[i];
			while(temp!=NULL){
				insert(temp->key,temp->value);
				temp=temp->next;
			}
		}
		delete []oldBucket;
	}

public:
	hashmap(int s=7){
		ts = s;
		cs = 0;
		Bucket = new node<T>*[ts];
		for(int i=0;i<ts;i++){
			Bucket[i] = NULL;
		}
	}

	void insert(T key,int value){
		int i = hashFn(key);
		// i : hash_index 
		node<T>* n = new node<T>(key,value);
		n->next = Bucket[i];
		Bucket[i] = n;
		cs++;

		float load_factor = cs/(1.0*ts);
		if(load_factor>0.7){
			rehash();
		}
	}

	void Print(){
		for(int i=0;i<ts;i++){
			cout<<i<<"-->";
			node<T>* temp = Bucket[i];
			while(temp){
				cout<<temp->key<<",";
				temp=temp->next;
			}
			cout<<endl;
		}
	}
};

int main(){
	hashmap<string> h;

	h.insert("Apple",150);
	h.insert("PineApple",50);
	h.insert("Guava",30);
	h.insert("Kiwi",40);
	h.insert("Mango",100);

	h.Print();


	return 0;
}