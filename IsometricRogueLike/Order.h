#pragma once
#include <queue>

__interface IOrder
{
	void onComplete();

};

class Orders
{
public:
	enum OrderTypes
	{
		Move,
		Attack,
		TakeItem,

	};

	Orders();
	~Orders();

	void addOrder(IOrder* order);


private:
	std::queue<IOrder*> mOrderQueue;
};