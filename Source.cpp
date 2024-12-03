#include "Config.h"
using namespace std;
using namespace pqxx;

static void log(const string& a)
{
	ofstream file("log.txt", ios::app);
	if (file.is_open())
	{
		file << a;
	}
	file.close();
}

class Category {
private:
	vector<string> category_info;
	const string conf;
public:

	Category(const string& myconfig, const int& id) : conf(myconfig) {
		try
		{
			connection conn(myconfig);
			work W(conn);
			result res = W.exec("SELECT * FROM categories WHERE categories_id = " + to_string(id) + ";");

			for (auto r : res)
			{
				for (auto a : r)
				{
					category_info.push_back(a.c_str());
				}
			}
				
			W.commit();
			conn.close();
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
	}

	friend static ostream& operator << (ostream& os, const Category& a)
	{
		for (string r : a.category_info)
		{
			os << r << " ";
		}
		return os;
	}

	void delete_category()
	{
		try
		{
				int st = clock();
				string query = "DELETE FROM categories WHERE categories_id = "+ category_info[0] + ";";
				log(query + "\n\n");
				connection conn(conf);


				work W(conn);
				result res = W.exec(query);

				for (auto r : res)
				{
					for (auto s : r)
					{
						cout << s.c_str() << endl;

					}
				}
				cout << endl;
				W.commit();
				conn.close();
				
				log("Query time: " + to_string(clock() - st) + "ms\n\n");
			}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;

		}
	}

	static void add_category(const string& myconfig)
	{
		try
		{
			cout << "Enter category info: category id, 'category name'\n[x]:Return to menu\n[Any key]:To add\n\n";
			char op;
			op = _getch();
			
			if (op != 'x')
			{
				cout << "<< ";
				string b;
				getline(cin, b);

				int st = clock();
				string query = "INSERT INTO categories(categories_id, category_name) VALUES (" + b + ");";
				log(query + "\n\n");
				connection conn(myconfig);


				work W(conn);
				result res = W.exec(query);

				for (auto r : res)
				{
					for (auto s : r)
					{
						cout << s.c_str() << endl;

					}
				}
				cout << endl;
				W.commit();
				conn.close();
				cout << "Query time: " << clock() - st << "ms\n\n";
				log("Query time: " + to_string(clock() - st) + "ms\n\n");
			}
			else
			{
				system("cls");
			}
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;

		}
	}

	static void view_categories(const string& myconfig)
	{
		try
		{
			int st = clock();
			cout << "Category info: category id, category name\n";

			connection conn(myconfig);
			string query = "SELECT * FROM categories;";
			log(query + "\n\n");
			work W(conn);
			result res = W.exec(query);

			for (auto r : res)
			{
				for (auto s : r)
				{
					cout << s.c_str() << " " ;
					
					log(to_string(s.c_str()) + " ");
				}
				
				cout << endl;
				log("\n");
			}
			cout << endl;
			log("\n");
			W.commit();

			conn.close();
			cout << "Query time: " << clock() - st << "ms\n\n";
			log("Query time: " + to_string(clock() - st) + "ms\n\n");
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;

		}
	}
		
	static void total_revenue(const string& myconfig)
	{

		try
		{
			int st = clock();
			cout << "Total revenue by categories like: category name, total revenue\n";

			string query = "SELECT categories.category_name, cat_sum.categories_sum FROM categories RIGHT JOIN cat_sum ON categories.categories_id = cat_sum.categories_id; ";
			log(query + "\n\n");
			connection conn(myconfig);

			work W(conn);
			result res = W.exec(query);

			for (auto r : res)
			{
				for (auto s : r)
				{
					cout << s.c_str() << " ";

					log(to_string(s.c_str()) + " ");
				}
				cout << endl;
				log("\n");
			}
			cout << endl;
			log("\n");
			W.commit();

			conn.close();
			cout << "Query time: " << clock() - st << "ms\n\n";
			log("Query time: " + to_string(clock() - st) + "ms\n\n");
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;

		}
	}
};

class Dish {
private:
	vector<string> dish_info;
	string conf;
public:

	Dish(const string& myconfig, const int& id) : conf(myconfig)
	{
		try
		{
			connection conn(myconfig);

			work W(conn);
			result res = W.exec("SELECT * FROM dishes WHERE dishes_id = " + to_string(id) + ";");

			for (auto a : res)
			{
				for (auto b : a)
				{
					dish_info.push_back(b.c_str());
				}
			}
			
			W.commit();
			conn.close();
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;

		}
	}

	friend static ostream& operator << (ostream& os, const Dish& a)
	{
		for (string r : a.dish_info)
		{
			os << r << " ";
		}
		return os;
	}

	virtual void delete_dish()
	{
		try
		{
			int st = clock();
			string query = "DELETE FROM dishes WHERE dishes_id = " + dish_info[0] + ";";
			log(query + "\n\n");
			connection conn(conf);


			work W(conn);
			result res = W.exec(query);

			for (auto r : res)
			{
				for (auto s : r)
				{
					cout << s.c_str() << endl;

				}
			}
			cout << endl;
			W.commit();
			conn.close();

			log("Query time: " + to_string(clock() - st) + "ms\n\n");
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;

		}
	}

	static void add_dish(const string& myconfig)
	{
		try
		{
			cout << "Enter dish info like: dish id, 'dish name', category id , price\n[x]:Return to menu\n[Any key]:To add\n\n";
			char op;
			op = _getch();
			
			if (op != 'x')
			{
				cout << "<< ";
				string b;
				getline(cin, b);
		
				int st = clock();
				connection conn(myconfig);
				string query = "INSERT INTO dishes(dishes_id, dishes_name, categories_id, price) VALUES(" + b + "); ";
				log(query + "\n\n");
				work W(conn);
				result res = W.exec(query);

				for (auto r : res)
				{
					for (auto s : r)
					{
						cout << s.c_str() << endl;
					}
				}
				cout << endl;
				W.commit();


				conn.close();
				cout << "Query time: " << clock() - st << "ms\n\n";
				log("Query time: " + to_string(clock() - st) + "ms\n\n");
			}
			else
			{
				system("cls");
			}
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
			
		}
		
		
		
	}

	static void view_dishes(const string& myconfig)
	{
		try
		{
			int st = clock();
			cout << "Dish info like: dish id, dish name, category id , price\n";

			

			connection conn(myconfig);
			string query = "SELECT * FROM dishes;";
			log(query + "\n\n");

			work W(conn);
			result res = W.exec(query);

			for (auto r : res)
			{
				for (auto s : r)
				{
					cout << s.c_str() << " ";

					log(to_string(s.c_str()) + " ");
				}
				cout << endl;
				log("\n");
			}
			cout << endl;
			log("\n");
			W.commit();

			conn.close();
			cout << "Query time: " << clock() - st << "ms\n\n";
			log("Query time: " + to_string(clock() - st) + "ms\n\n");
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;

		}
	}

	static void top3_dishes(const string& myconfig)
	{
		try
		{
			int st = clock();
			cout << "Top 3 dish by portion count like: order count, dish name, price\n";

			string query = "SELECT tot.total, dishes.dishes_name, dishes.price FROM dishes RIGHT JOIN tot ON dishes.dishes_id = tot.dishes_id ORDER BY total DESC LIMIT 3;";
			log(query + "\n\n");

			connection conn(myconfig);

			work W(conn);
			result res = W.exec(query);

			for (auto r : res)
			{
				for (auto s : r)
				{
					cout << s.c_str() << " ";

					log(to_string(s.c_str()) + " ");
				}
				cout << endl;
				log("\n");
			}
			cout << endl;
			log("\n");
			W.commit();

			conn.close();
			cout << "Query time: " << clock() - st << "ms\n\n";
			log("Query time: " + to_string(clock() - st) + "ms\n\n");
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;

		}
	}

	static void top_dishes(const string& myconfig)
	{
		try
		{
			int st = clock();
			cout << "Top dish by order count like: order count, dish name, price\n";



			connection conn(myconfig);
			string query = "SELECT totcount.totalcount, dishes.dishes_name, dishes.price FROM dishes RIGHT JOIN totcount ON dishes.dishes_id = totcount.dishes_id ORDER BY totalcount DESC; ";
			log(query + "\n\n");

			work W(conn);
			result res = W.exec(query);

			for (auto r : res)
			{
				for (auto s : r)
				{
					cout << s.c_str() << " ";

					log(to_string(s.c_str()) + " ");
				}
				cout << endl;
				log("\n");
			}
			cout << endl;
			log("\n");
			W.commit();

			conn.close();
			cout << "Query time: " << clock() - st << "ms\n\n";
			log("Query time: " + to_string(clock() - st) + "ms\n\n");
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;

		}
	}
};

class Order {
private:
	vector<string> order_info;
	string conf;
public:

	Order(const string& myconfig, const int& id) : conf(myconfig)
	{
		try
		{
			connection conn(myconfig);

			work W(conn);
			result res = W.exec("SELECT * FROM orders WHERE orders_id = " + to_string(id) + ";");

			for (auto a : res)
			{
				for (auto b : a)
				{
					order_info.push_back(b.c_str());
				}
			}

			W.commit();
			conn.close();
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;

		}
	}

	friend static ostream& operator << (ostream& os, const Order& a)
	{
		for (string r : a.order_info)
		{
			os << r << " ";
		}
		return os;
	}

	void delete_dish()
	{
		try
		{
			int st = clock();
			string query = "DELETE FROM orders WHERE orders_id = " + order_info[0] + ";";
			log(query + "\n\n");
			connection conn(conf);


			work W(conn);
			result res = W.exec(query);

			for (auto r : res)
			{
				for (auto s : r)
				{
					cout << s.c_str() << endl;

				}
			}
			cout << endl;
			W.commit();
			conn.close();

			log("Query time: " + to_string(clock() - st) + "ms\n\n");
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;

		}
	}

	static void add_order(const string& myconfig)
	{
		try
		{
			cout << "Order info like: order id, dishes_id, 'order_date' (YYYY-MM-DD) , quantity\n[x]:Return to menu\n[Any key]:To add\n\n";

			vector<string> b;
			string o;
			char op;
			op = _getch();

			if (op != 'x')
			{
				cout << "<< ";
				while (b.size() < 3 && getline(cin, o, ',')) { b.push_back(o); }
				getline(cin, o);
				b.push_back(o);
				int st = clock();
				connection conn(myconfig);
				string query = "INSERT INTO orders(orders_id, dishes_id, order_date, quantity, total_price) VALUES (" + b[0] + ", " + b[1] + ", " + b[2] + ", " + b[3] + ", " + b[3] + " * (SELECT price FROM dishes WHERE dishes_id = " + b[1] + ")); ";
				log(query + "\n\n");
				work W(conn);
				result res = W.exec(query);

				for (auto r : res)
				{
					for (auto s : r)
					{
						cout << s.c_str() << endl;
					}
				}
				cout << endl;
				W.commit();
				conn.close();
				cout << "Query time: " << clock() - st << "ms\n\n";
				log("Query time: " + to_string(clock() - st) + "ms\n\n");

			}
			else
			{
				system("cls");
			}
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;

		}
	}

	static void view_orders(const string& myconfig)
	{
		try
		{
			int st = clock();
			cout << "Order info like: order id, dishe id, order date (YYYY-MM-DD), quantity, total_price\n";



			connection conn(myconfig);
			string query = "SELECT * FROM orders;";
			log(query + "\n\n");
			work W(conn);
			result res = W.exec(query);

			for (auto r : res)
			{
				for (auto s : r)
				{
					cout << s.c_str() << " ";

					log(to_string(s.c_str()) + " ");
				}
				cout << endl;
				log("\n");
			}
			cout << endl;
			log("\n");
			W.commit();

			conn.close();
			cout << "Query time: " << clock() - st << "ms\n\n";
			log("Query time: " + to_string(clock() - st) + "ms\n\n");
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;

		}
	}

	static void avarge_price(const string& myconfig)
	{
		try
		{
			int st = clock();
			cout << "Averge order price\n";



			connection conn(myconfig);
			string query = "SELECT AVG(total_price) FROM orders;";
			log(query + "\n\n");
			work W(conn);
			result res = W.exec(query);

			for (auto r : res)
			{
				for (auto s : r)
				{
					cout << s.c_str() << " ";

					log(to_string(s.c_str()) + " ");
				}
				cout << endl;
				log("\n");
			}
			cout << endl;
			log("\n");
			W.commit();

			conn.close();
			cout << "Query time: " << clock() - st << "ms\n\n";
			log("Query time: " + to_string(clock() - st) + "ms\n\n");
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;

		}
	}
};

class MainCourse : public Dish {
private:
	vector<string> MainCourse_info;
	string conf;
public:
	MainCourse(const string& myconfig, const int& id) : Dish(myconfig, id), conf(myconfig)
	{
		try
		{
			connection conn(myconfig);

			work W(conn);
			result res = W.exec("SELECT * FROM dishes WHERE categories_id = 3 AND dishes_id = " + to_string(id) + ";");

			for (auto a : res)
			{
				for (auto b : a)
				{
					MainCourse_info.push_back(b.c_str());
				}
			}

			W.commit();
			conn.close();
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;

		}
	}

	friend static ostream& operator << (ostream& os, const MainCourse& a)
	{
		for (string r : a.MainCourse_info)
		{
			os << r << " ";
		}
		return os;
	}

	void delete_dish() override
	{
		try
		{
			int st = clock();
			string query = "DELETE FROM dishes WHERE categories_id = 3 AND  dishes_id = " + MainCourse_info[0] + ";";
			log(query + "\n\n");
			connection conn(conf);


			work W(conn);
			result res = W.exec(query);

			for (auto r : res)
			{
				for (auto s : r)
				{
					cout << s.c_str() << endl;

				}
			}
			cout << endl;
			W.commit();
			conn.close();

			log("Query time: " + to_string(clock() - st) + "ms\n\n");
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;

		}
	}

};

class Dessert : public Dish {
private:
	vector<string> Dessert_info;
	string conf;
public:
	Dessert(const string& myconfig, const int& id) : Dish(myconfig, id), conf(myconfig)
	{
		try
		{
			connection conn(myconfig);

			work W(conn);
			result res = W.exec("SELECT * FROM dishes WHERE categories_id = 4 AND dishes_id = " + to_string(id) + ";");

			for (auto a : res)
			{
				for (auto b : a)
				{
					Dessert_info.push_back(b.c_str());
				}
			}

			W.commit();
			conn.close();
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;

		}
	}

	friend static ostream& operator << (ostream& os, const Dessert& a)
	{
		for (string r : a.Dessert_info)
		{
			os << r << " ";
		}
		return os;
	}

	void delete_dish() override
	{
		try
		{
			int st = clock();
			string query = "DELETE FROM dishes WHERE categories_id = 4 AND  dishes_id = " + Dessert_info[0] + ";";
			log(query + "\n\n");
			connection conn(conf);


			work W(conn);
			result res = W.exec(query);

			for (auto r : res)
			{
				for (auto s : r)
				{
					cout << s.c_str() << endl;

				}
			}
			cout << endl;
			W.commit();
			conn.close();

			log("Query time: " + to_string(clock() - st) + "ms\n\n");
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;

		}
	}

};

template <class dish_name, class quantity>
class Pair {
private:
	dish_name dish_name;
	quantity quantity;
public:
	Pair(const string& myconfig, const int& id)
	{
		try
		{
		

		string query = "SELECT tot.total, dishes.dishes_name FROM dishes FULL JOIN tot ON dishes.dishes_id = tot.dishes_id WHERE tot.dishes_id = " + to_string(id) + " ORDER BY total DESC ;";
		

		connection conn(myconfig);

		work W(conn);
		result res = W.exec(query);

		quantity = stoi(to_string(res[0][0].c_str()));
		dish_name = to_string(res[0][1].c_str());
		
		W.commit();

		conn.close();
		
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;

		}
	}

	friend static ostream& operator << (ostream& os, const Pair& a)
	{
		os << a.dish_name << " " << a.quantity;
		return os;
	}
};

static void menu(const string& myconfig)
{
	char op;
	
	while (true)
	{
		cout << "Operations:\n[a]:Add category\n[s]:Add dish\n[d]:Add order\n[q]:View all categories\n[w]:View all dishes\n[e]:View all orders\n[r]:Total revenue by categories\n[t]:Top 3 dish by portion count\n[y]:Avarge order price\n[u]:Top dish by order count";
		op = _getch();
		
		system("cls");

		switch (op)
		{
		case 'a':
			Category::view_categories(myconfig);
			Category::add_category(myconfig);
			break;
		case 's':
			Dish::view_dishes(myconfig);
			Dish::add_dish(myconfig);
			break;
		case 'd':
			Order::view_orders(myconfig);
			Order::add_order(myconfig);
			break;
		case 'q':
			Category::view_categories(myconfig);
			break;
		case 'w':
			Dish::view_dishes(myconfig);
			break;
		case 'e':
			Order::view_orders(myconfig);
			break;
		case 'r':
			Category::total_revenue(myconfig);
			break;
		case 't':
			Dish::top3_dishes(myconfig);
			break;
		case 'y':
			Order::avarge_price(myconfig);
			break;
		case 'u':
			Dish::top_dishes(myconfig);
			break;
		default:
			cout << "Wrong operation!\n\n";
			break;
		}
		
	}
}

int main()
{
	for (int i = 0; i < 9; i++)
	{
		Category a(config, i);
		Dish b(config, i);
		Order c(config, i);
		MainCourse d(config, i);
		Dessert e(config, i);
		Pair<string, int> f(config, i);

		cout << a << endl << b << endl << c << endl << d << endl << e << endl << f << endl;
	}
	
	menu(config);
	

}
