#include <C:\Program Files\MySQL\MySQL Connector C++ 8.2\include\jdbc\mysql_driver.h>
#include <C:\Program Files\MySQL\MySQL Connector C++ 8.2\include\jdbc\mysql_connection.h>
#include <C:\Program Files\MySQL\MySQL Connector C++ 8.2\include\jdbc\cppconn\statement.h>
#include <iostream>
#include <C:\Program Files\MySQL\MySQL Connector C++ 8.2\include\jdbc\cppconn\resultset.h>
#include <C:\Program Files\MySQL\MySQL Connector C++ 8.2\include\jdbc\cppconn\exception.h>
#include <C:\Program Files\MySQL\MySQL Connector C++ 8.2\include\jdbc\cppconn\prepared_statement.h>
#include <string>


void Menu()
{
	std::cout << "1. Add product" << std::endl;
	std::cout << "2. Add stock" << std::endl;
	std::cout << "3. Minus stock" << std::endl;
	std::cout << "4. Completely delete product" << std::endl;
	std::cout << "5. Show all products" << std::endl;
	std::cout << "6. Menu" << std::endl;

}

class Product
{
private:
	std::string product_name;
	int product_stock;

public:
	Product() : product_name(""), product_stock(0) {}
	
	std::string get_product_name()
	{
		std::string product_name_x;
		std::cout << "Item name: ";
	    std::cin >> product_name_x;
		product_name = product_name_x;
		return product_name;
	}
	int get_product_stock()
	{
		int stock_x;
		std::cout << "Stock: ";
		std::cin >> stock_x;
		product_stock = stock_x;
		return product_stock;
	}

	void addProduct()
	{
		sql::mysql::MySQL_Driver* driver;
		sql::Connection* con;
		sql::Statement* stmt;
		sql::PreparedStatement* pstmt;
		driver = sql::mysql::get_mysql_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", "root", "");
		stmt = con->createStatement();
		stmt->execute("CREATE DATABASE IF NOT EXISTS items");
		con->setSchema("items");
		stmt->execute("CREATE TABLE IF NOT EXISTS items_data("
			"id INT PRIMARY KEY NOT NULL AUTO_INCREMENT,"
			"item_name VARCHAR(30) NOT NULL, "
			"stock int NOT NULL)");
		std::string product = get_product_name();
		int stock = get_product_stock();
		pstmt = con->prepareStatement("INSERT INTO items_data (item_name, stock) VALUES (?, ?)");
		pstmt->setString(1, product);
		pstmt->setInt(2, stock);
		pstmt->executeUpdate();
	}

	void ShowAllItems()
	{
		sql::mysql::MySQL_Driver* driver;
		sql::Connection* con;
		sql::Statement* stmt;
		sql::ResultSet* res;
		driver = sql::mysql::get_mysql_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", "root", "");
		stmt = con->createStatement();
		stmt->execute("CREATE DATABASE IF NOT EXISTS items");
		con->setSchema("items");
		res = stmt->executeQuery("SELECT * FROM items_data");
		int i = 1;
		while (res->next())
		{
			std::cout << "ID: " << i << std::endl;
			std::cout << "Item: " << res->getString("item_name") << std::endl;
			std::cout << "Stock: " << res->getInt("stock") << std::endl;
			std::cout << "------------------------------------" << std::endl;
			i++;
		}
	}

	void MinusStock()
	{
		sql::mysql::MySQL_Driver* driver;
		sql::Connection* con;
		sql::Statement* stmt;
		sql::ResultSet* res;
		driver = sql::mysql::get_mysql_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", "root", "");
		stmt = con->createStatement();
		stmt->execute("CREATE DATABASE IF NOT EXISTS items");
		con->setSchema("items");
		res = stmt->executeQuery("SELECT * FROM items_data");
        std::string item_minus_stock;
		std::cout << "Item: ";
		std::cin >> item_minus_stock;
		int stock_actual;
		bool item_find = false;
		while (res->next())
		{
			if (item_minus_stock == res->getString("item_name"))
			{
				stock_actual = res->getInt("stock");
				std::cout << "Stock of this item: " << stock_actual << std::endl;
				std::cout << "How much do you want to delete: ";
				int stock_minus;
				std::cin >> stock_minus;
				if (stock_minus >= stock_actual)
				{
					std::cout << "U cant do that. Its better to use item delete." << std::endl;
					break;
				}
				else
				{
					int stock_new = stock_actual - stock_minus;
					sql::PreparedStatement* pstmt;
					pstmt = con->prepareStatement("UPDATE items_data SET stock = ? WHERE item_name = ?");
					pstmt->setInt(1, stock_new);
					pstmt->setString(2, item_minus_stock);
					pstmt->executeUpdate();
					item_find = true;
					break;
				}

			}
		
		}
	
		if (item_find)
		{
			std::cout << "Stock updated sucessfully" << std::endl;
		}
		else
		{
			std::cout << "Cant update stock" << std::endl;
		}

	}
	void AddStock()
	{
		sql::mysql::MySQL_Driver* driver;
		sql::Connection* con;
		sql::Statement* stmt;
		sql::ResultSet* res;
		driver = sql::mysql::get_mysql_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", "root", "");
		stmt = con->createStatement();
		stmt->execute("CREATE DATABASE IF NOT EXISTS items");
		con->setSchema("items");
		res = stmt->executeQuery("SELECT * FROM items_data");
		std::string item_plus_stock;
		std::cout << "Item: ";
		std::cin >> item_plus_stock;
		int stock_actual;
		bool item_find = false;
		while (res->next())
		{
			if (item_plus_stock == res->getString("item_name"))
			{
				stock_actual = res->getInt("stock");
				std::cout << "Stock of this item: " << stock_actual << std::endl;
				std::cout << "How much do you want to add: ";
				int stock_add;
				std::cin >> stock_add;
				int stock_new = stock_actual + stock_add;
				sql::PreparedStatement* pstmt;
				pstmt = con->prepareStatement("UPDATE items_data SET stock = ? WHERE item_name = ?");
				pstmt->setInt(1, stock_new);
				pstmt->setString(2, item_plus_stock);
				pstmt->executeUpdate();


			}
		}
	}

	void DeleteItem()
	{
		sql::mysql::MySQL_Driver* driver;
		sql::Connection* con;
		sql::Statement* stmt;
		sql::ResultSet* res;
		driver = sql::mysql::get_mysql_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", "root", "");
		stmt = con->createStatement();
		stmt->execute("CREATE DATABASE IF NOT EXISTS items");
		con->setSchema("items");
		res = stmt->executeQuery("SELECT * FROM items_data");
		std::cout << "What item do you want to delete?: ";
		std::string delete_item_name;
		std::cin >> delete_item_name;
		bool item_del = false;

		while (res->next())
		{
			if (delete_item_name == res->getString("item_name"))
			{
				sql::PreparedStatement* pstmt;
				pstmt = con->prepareStatement("DELETE FROM items_data WHERE item_name = ?");
				pstmt->setString(1, delete_item_name);
				pstmt->executeUpdate();
				item_del = true;
				break;
			}
		}
		if (item_del)
		{
			std::cout << "Item sucessfully deleted" << std::endl;
		}
		else
		{
			std::cout << "Item not deleted" << std::endl;
		}
	}


	
};





int main()
{
	Product product;
	Menu();
	while (true)
	{
		int x;
		std::cout << "choose number: ";
		std::cin >> x;

		switch (x)
		{
		case 1:
		{
			product.addProduct();
			break;
		}
		case 2:
		{
			product.AddStock();
			break;
		}
		case 3:
		{
			product.MinusStock();
			break;
		}
		case 4:
		{
			product.DeleteItem();
			break;
		}
		case 5:
		{
			product.ShowAllItems();
			break;
		}
		case 6:
		{
			Menu();
		}
		default:
		{
			std::cout << "Wybierz numer z listy" << std::endl;
			break;
		}




		}
	}

}